/*
 * QAP.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#include "distances.h"
#include "permutations.h"
#include<fstream>
#include<iostream>

double QAP_sum(double** p,vector <int> x,double** d){

	double sum=0;

	long dim=(long)(x.size());

	for(long i=0;i<dim;i++) for(long j=0;j<dim;j++) sum+=p[i][j]*d[x[i]][x[j]];

	return sum;
}

vector <int> QAPproblem(long noftimes=100,long randreps=1000,double targetmin=-1,char* filename="QAP.txt"){

	ifstream input;
    input.open(filename);

	int n;
	input>>n;

	double **p=0,**d=0;
	p=new double *[n];d=new double *[n];
	for(int i = 0 ; i < n ; i++) {p[i] = new double[n];d[i] = new double[n];};

	cout<<endl;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++) {input>>p[i][j];cout<<p[i][j]<<"  "; /*d[i][j]=hamdist(i,j);*/}
		cout<<endl;
	}
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++) {input>>d[i][j];cout<<d[i][j]<<"  ";}
		cout<<endl;
	}
	cout<<endl;

	input.close();

	cout<<filename<<endl;
	cout.precision(10);

	vector <int> q,best,bestbest;
	vector <int> perm;

	double minmin=1000000000,min;
	long double sum;
	int counter,ii,jj;

	int temp;

	for(int times=0;times<noftimes;times++)
	{
	permutation(n,q);
	best=q;

	//----------------
	counter=1;min=1000000000;
	while(counter!=0)
	{
		counter=0;
		for(int i=0;i<n;i++) for(int j=i+1;j<n;j++)
		{
			perm=best;
			temp=perm[i];perm[i]=perm[j];perm[j]=temp;

			sum=QAP_sum(p,perm,d);

			if(sum<min) {min=sum;best=perm;counter++;}
		}
	};
	//----------------
	for(int dos=0;dos<randreps;dos++){

		ii=rand() % n;
		jj=rand() % n;
		temp=best[ii];best[ii]=best[jj];best[jj]=temp;

		for(int i=0;i<n;i++) for(int j=i+1;j<n;j++)
		{
			perm=best;
			temp=perm[i];perm[i]=perm[j];perm[j]=temp;

			sum=QAP_sum(p,perm,d);

			if(sum<=min) {min=sum;best=perm;}

		}
	}

	if(min<minmin) {minmin=min;bestbest=best;}
	cout<<"["<<times+1<<"/"<<noftimes<<"]"<<1*min<<"("<<1*minmin<<")  ";
	q.clear();
	if(minmin<=targetmin) break;
	}
	cout<<"\nMin="<<minmin<<"\n";

	vector <int> result;

	for(int i=0;i<n-1;i++) result.push_back(bestbest[i]);
	result.push_back(bestbest[n-1]);

	for( int i = 0 ; i < n ; i++ ) delete [] p[i] ;
	delete [] p ;

	return result;
}


