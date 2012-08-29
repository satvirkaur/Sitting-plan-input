#include <iostream>
#include <sstream>
#include <iterator>
#include <climits>
#include <deque>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

int roll_no[30],t_b, branch_size[40],total_rooms,rows[10],cols[10], total_student[30];//, total_subject[30]; 
string roll[30],branch_name[20], subject_name[20], room_name[20];
fstream file; 
static int n;

template<typename OutIter>
bool parse_number_list_with_ranges(istream& is, OutIter out)
{
  int number;
  // the list always has to start with a number
  while (is >> number)
  {
    *out++ = number;

    char c;
    if (is >> c)
      switch(c)
      {
      case ',':
        continue;
      case '-':
        {
          int number2;
          if (is >> number2)
          {
            if (number2 < number)
              return false;
            while (number < number2)
              *out++ = ++number;
            char c2;
            if (is >> c2)
              if (c2 == ',')
                continue;
              else
                return false;
            else
              return is.eof();
          }
          else
            return false;
        }
      default:
        return is.eof();
      }
    else
      return is.eof();
  }
  // if we get here, something went wrong (otherwise we would have
  // returned from inside the loop)
  return false;
}


//To get inputs from file
void input()
{
	ifstream infile; 
    infile.open("input.in", ios::in); 
    infile >> total_rooms;
    for(int i=0; i<total_rooms; i++)
    {
    	infile >> room_name[i] >>rows[i] >>cols[i];
    }
	infile>>t_b;
	getline(infile, roll[0], '\n');
	cout<<"roll[0]" << roll[0];
	for(int i=0; i<t_b; i++)
	{
		infile >>branch_name[i] >> subject_name[i];
		getline(infile, roll[i], '\n');
		//cout 
	}
	infile.close();
}

void split()
{
    input();
    string a="0";
    //char largchars[] = "1-10 12 34 15 20 25";
    cout<<"INPUT\n";
    for(int i=0; i<t_b; i++)
	{
		//cout<<"i="<<i<<"\t"<<roll[i]<<endl;
	}
	cout<<"\nSTRTOK\n";
    for(int i=0; i<t_b; i++)
    {
        int sz = roll[i].size()+1;
        char largchar[sz];// = roll[i].c_str();//"1-10 12 34 15 20 25-30";
        strcpy(largchar,roll[i].c_str());
        char* chars_array = strtok(largchar, " ");
        int size = 70;
        //int a = 0, b = 0, c[size], n = 0;
        a="0";
        while(chars_array)
        {
        		if(chars_array!="-")
        		{
        			a.append(",");
        			a.append(chars_array);//atoi (chars_array));//n++;
        		}
        	chars_array = strtok(NULL, " ");
        }
       // cout<<a<<endl;
       // cout<<endl<<"\n";
      // int j = i-1;
        roll[i] = a;
    }
}
 
 void remove_zero()
{
	int remove[40][100];
	ifstream infile;
	infile.open("expand-rollno.out");
	infile >> t_b;
	for(int i=0; i<t_b; i++)
	{
		infile >> branch_size[i];
		for(int j=0; j<branch_size[i]; j++)
		{
			infile >> remove[i][j];
		}
	}
	infile.close();
	for(int i=0; i<t_b; i++)
	{
		for(int j=0; j<branch_size[i]-1; j++)
		{
			remove[i][j] = remove[i][j+1];
			//infile >> remove[j];
		}
		branch_size[i]--;
	}
	ofstream outfile;
	outfile.open("expand-rollno.out");
	
	outfile << t_b <<"\n";
	for(int i=0; i<t_b; i++)
	{
		//outfile<< branch_name[i] <<" " << subject_name[i] <<" " 
		outfile <<total_student[i]<<"\n";
		for(int j=0; j<branch_size[i]; j++)
		{
			
			outfile << remove[i][j] << " " ;
			//cout << remove[i][j] << " " ;
		}
		outfile << "\n";
		cout<<"\n";
		branch_size[i]--;
	}
	outfile.close();
	outfile.open("rooms_detail.out");
	outfile<< total_rooms <<"\n";
	for(int i=0; i<total_rooms; i++)
	{
		outfile << room_name[i] <<" " <<rows[i]<<" " << cols[i]<<" \n";
	}
	for(int i=0; i<t_b; i++)
	{
		outfile<< branch_name[i] <<" " << subject_name[i] <<"\n";
	} 
	outfile.close();
}
	
 
int main()
{
	//input();
	split();
	
	ofstream outfile;
   outfile.open("expand-rollno.out", ios::out);
   outfile << t_b << endl;
	
	char largechars[30];
	
	cout<<"\n EXPAND\n";
	for(int i=0; i<t_b; i++)
	{
		//char intp[30] = roll[i];
		//istringstream example("0,-6,-3--1,3-5,7-11,14,15,17-20,25-30");
//		istringstream example("-6 -3--1 3-5 7-11 14 15 17-20 25-30");
		istringstream example(roll[i]);
  	deque<int> v;
	  bool success = parse_number_list_with_ranges(example, back_inserter(v));
	  if (success)
	  {
	  	outfile << v.size() << endl;
	  	total_student[i]=v.size()-1;
	    copy(v.begin(), v.end()-1,
	              ostream_iterator<int>(outfile, " "));
	    outfile << v.back() <<endl;
	    //cout<<sizeof(v.back)<<endl;
	    cout << v.back() << "\n";
	   // int s = v.size();
    	
	  }
	  else
	    cout << "an error occured.\n";
  }
  outfile.close();
  remove_zero();
}


