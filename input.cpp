#include "input.h"

void input :: sort_rollno()
{
	// Reading roll nos from file
	infile.open("expand-rollno.out");
	//cout<<"expand-rollno.out";
	infile >> t_branches;
	for(i=0; i<t_branches; i++)
	{
		infile >> roll_size[i];
		for(int j=0; j<roll_size[i]; j++)
		{
			infile >> roll_no[i][j];
			cout<<roll_no[i][j];
		}
		cout<<"\n";
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
		{
			roll_no[i][j] = rno[j];
		}
	}		
		// Writing into file(input_sorted.out)
	outfile.open("sort-rollno.out");
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


void input :: rm_duplicate_rollno()
{
	// Reading roll nos from file
	infile.open("sort-rollno.out");
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
	
	for(i=0;i<t_branches;i++)
	{
		for(j=0; j<roll_size[i]; j++)
		{
			rno[j] = roll_no[i][j];
		}
		
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
	outfile.open("non-redundant-rollno.out");
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

