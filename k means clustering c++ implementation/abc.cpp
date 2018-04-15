#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <math.h>
using namespace std;

double print_arr(double ap[50][50],int row,int col)
{
	for (int i=0;i<row;i++)
	{
	for (int j=0;j<col;j++)
	cout<<ap[i][j]<<" ";
	cout<<"\n";
	}
}

double rand_inti(double ar[50][50],int num,int col)
{	double aa;
	double min_v = numeric_limits<double>::max();
	double max_v = numeric_limits<double>::min();
	for (int j=0;j<num;j++)
	{
		min_v = min(ar[j][col],min_v);
		max_v = max(ar[j][col],max_v);
	}
	double f = (double)rand() / RAND_MAX;
	aa = min_v + f * (max_v-min_v);
return aa;
}


double euclid_dis(double a[50], double b[50],int dim)
{
	double dis = 0;
	for (int i=0;i<dim;i++)
		dis = dis+ pow((a[i]-b[i]),2);
	return pow(dis,0.5);
}


int main(int argc, char *argv[])
{
	srand(time(0));
	string line;
	double a[50][50];
	int num_data_points,dim;
	char *clus = argv[2];
	int clus_size = 2;
	double b[50][50];
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
	//cout<<num_data_points<<"  "<<dim<<"\n";
	}
	else
	cout<<"Unable to open file";

	double min_1,max_1;
	for(int i=0;i<clus_size;i++)
	{
	for (int j=0;j<dim;j++)
	b[i][j] = rand_inti(a,num_data_points,j);
	}	

	print_arr(b,clus_size,dim);
	double min_dis;
	int index;
	double c[50];
	double d[50];
	for (int i=0;i<num_data_points;i++)
	{
	for (int j=0;j<clus_size;j++)
	c[j] = euclid_dis(a[i],b[j],dim);
	min_dis = c[0];	
	index= 0;
	for (int k=1;k<clus_size;k++)
	{
		if (min_dis>c[k])
		{
			index= k;
			min_dis = c[k];
		}
	}
	d[i]=index;
	}

	for (int i = 0; i<num_data_points;i++)
	cout<<d[i]<<" ";

	return 0;
}
