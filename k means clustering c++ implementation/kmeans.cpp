#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <math.h>
using namespace std;

/*
double print_arr(double ap[500][500],int row,int col)
{
	for (int i=0;i<row;i++)
	{
	for (int j=0;j<col;j++)
	cout<<ap[i][j]<<" ";
	cout<<"\n";
	}
}
*/
// This code can run for 500 data points having 500 dimensions max
//Randomly intialize the cluster centroids for first iteration
double rand_inti(double ar[500][500],int num,int col)
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

//Calculate Euclidean Distance
double euclid_dis(double a[500], double b[500],int dim)
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
	double a[500][500];
	int num_data_points,dim;
	int clus_size = atoi(argv[2]);
	double b[500][500];
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

	//print_arr(b,clus_size,dim);
	double min_dis;
	int index;
	double c[500];
	double d[500];

//For 5 iterations

	for (int itt = 0; itt<5;itt++)
{
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
	//cout<<d[i]<<" ";
	}
	//cout<<"\n";
	double e[500] = {0};
	int count = 0; 
	for (int i=0;i<clus_size;i++)
	{
		for (int j=0;j<num_data_points;j++)
		{	
			if (d[j]==i)
			{
			count++;
			for (int k=0;k<dim;k++)
			e[k] += a[j][k];	
			}
		}
		for (int l=0;l<dim;l++)
		{
			b[i][l]= e[l]/count;	
		}

	}
}
ofstream myfile1("cluster.txt");
	if (myfile1.is_open())
	{
		for (int i=0;i<clus_size;i++)
		{
			for (int j=0;j<dim;j++)
				myfile1 << b[i][j]<<" ";
			myfile1 <<"\n";
		}

	}
	myfile1.close();
//print_arr(b,clus_size,dim);
return 0;
}

