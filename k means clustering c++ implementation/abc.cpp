#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

double int_mean(double minn, double maxx)
{
double f = (double)rand() / RAND_MAX;
return minn + f * (maxx-minn);
}

int main(int argc, char *argv[])
{
	srand(time(0));
	string line;
	double a[50][50];
	int num_data_points,dim;
	char *clus = argv[2];
	fstream myfile (argv[1]);
	if (myfile.is_open())
	{	num_data_points=0;
		while (getline (myfile,line))
		{	dim=0;
			istringstream iss(line);
			double val;
			while(iss >> val)
			{
				a[num_data_points][dim] = val;
				dim++;
			}
		num_data_points++;
		}
	myfile.close();
	cout<<num_data_points<<"  "<<dim<<"\n";
	}
	else
	cout<<"Unable to open file";

	


	return 0;
}
