#include "input.h"

void input :: room_details()	// get room details
{
    //file.open(in, ios::in, ios::out);
	infile>>t_rooms;
	for(i=0; i<t_rooms; i++)
	{
		infile >> room_no[i] >> rows[i] >> cols[i];
	}
}

void input :: rollno_details()	// get roll no details
{
	infile>>t_branches;
	for(i=0; i<t_branches; i++)
	{
		infile >> branch_name[i] >> exam_subject[i] >> rollno[i];
	}
}

void input ::  input_in_details()	// read input(input.in) file
{
	cout<<"\n\t Enter input file name: ";
	cin>>input_file;
	//input_file = "input.in";
	infile.open(input_file);//"input.in");//, ios::in, ios::out);
	room_details();
	rollno_details();
	infile.close();
}


void input :: expand(string rno)	// process input.in file and 
{								// generate input_sort.out file
	istringstream rollNo(rno);
	deque<int> v;
	//int k = 0;
	bool success = parse_number_list_with_ranges(rollNo, back_inserter(v));
	if (success)
	{
		outfile << v.size()<<endl;
		copy(v.begin(), v.end()-1, ostream_iterator<int>(outfile, " "));
		
		outfile << v.back()<<endl;
	}
	else
	outfile << "an error occured.\n";
	
}


// Writing expanded form of roll nos in file
void input :: expand_rollno()
{	
	outfile.open("input_expand.out");
	outfile << t_branches <<endl;
	for(i=0; i<t_branches; i++)
	{
		expand(rollno[i]);
	}
	outfile.close();
}

//putting all the rooms detail into a file
void input :: rooms_detail()
{
	outfile.open("rooms_detail.out");//, ios::out, ios::in, ios::app);
	cout<<"hello";
	outfile<<t_rooms<<endl;
	for(i=0; i<t_rooms; i++)
	{
		outfile<<room_no[i]<<" "<<rows[i]<<" "<<cols[i]<<endl;
	}
	outfile.close();
}



void input :: sort_rollno()
{
	// Reading roll nos from file
	infile.open("input_expand.out");
	infile >> t_branches;
	for(i=0; i<t_branches; i++)
	{
		infile >> roll_size[i];
		for(int j=0; j<roll_size[i]; j++)
		{
			infile >> roll_no[i][j];
		}
	}
	infile.close();
	//outfile.open("input_sorted.out");	
	// Sorting of roll nos.
	for(i=0;i<t_branches;i++)
	{
		for(j=0; j<roll_size[i]; j++)
		{
			rno[j] = roll_no[i][j];
		}
		
		sort(rno, rno+roll_size[i]);	// Sort function
		
		for(j=0; j<roll_size[i]; j++)
		{	// Removing duplicate values
			if(rno[j]==rno[j+1])// || rno[j+1]==rno[j+2])
			{
				for(k=j; k<=roll_size[i]; k++) 
     		 	{
          			rno[k] = rno[k+1];  //shifts each element one position above
     			}
     			roll_size[i]--;
     			j=0;
			}
		}
		
		for(j=0; j<roll_size[i]; j++)
		{
			roll_no[i][j] = rno[j];
		}
	}		
		// Writing into file(input_sorted.out)
	outfile.open("input_sorted.out");
	outfile << t_branches <<endl;
	for(int i=0; i<t_branches; i++)
	{
		outfile << roll_size[i] <<endl;
		for(int j=0; j<roll_size[i]; j++)
		{
			 outfile << roll_no[i][j] << " ";
		}
		outfile <<endl;
	}
	outfile.close();
}


void input :: remove_rollno()
{
	// Reading roll nos from file
	infile.open("input_sorted.out");
	infile >> t_branches;
	for(i=0; i<t_branches; i++)
	{
		infile >> roll_size[i];
		for(int j=0; j<roll_size[i]; j++)
		{
			infile >> roll_no[i][j];
		}
	}
	
	infile.close();
	// Sorting of roll nos.
	for(i=0;i<t_branches;i++)
	{
		for(j=0; j<roll_size[i]; j++)
		{
			rno[j] = roll_no[i][j];
		}
		
		// Removing roll nos that are not for exam
		for(j=0; j<roll_size[i]; j++)
		{
			if(rno[j]<0)	
			{
				int a,b;
				a = rno[j];
				b = -1 * a;
			
				for(k=0; k<roll_size[i]; k++)
				{
					if(rno[k] == a || rno[k] == b)
					{
						//rno[j+1]=0;
						for (int l=k; l<=roll_size[i]; l++) 
    		 			{
    		      			rno[l] = rno[l+1];  //shifts each element one position above
    		 			}
    		 			roll_size[i]--;
    		 			//k=0;
					}
				}
				j--;
			}
		}
		for(j=0; j<roll_size[i]; j++)
		{
			roll_no[i][j] = rno[j];
		}
	}
	// Writing into file
	outfile.open("input_processed.out");
	outfile << t_branches <<endl;
	for(int i=0; i<t_branches; i++)
	{
		outfile << roll_size[i] <<endl;
		for(int j=0; j<roll_size[i]; j++)
		{
			 outfile << roll_no[i][j] << " ";
		}
		outfile <<endl;
	}
	outfile.close();
}
template<typename OutIter>
bool input :: parse_number_list_with_ranges(istream& is, OutIter out)
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
