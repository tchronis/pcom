/*
 * permutations.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: tchr
 */

#include<iostream>
#include<cstdlib>
#include<list>
#include<vector>

// Random Permutation of 0,1,2,.....,(n-1)

using namespace std;

void permutation(int n, vector <int> &perm){

	srand((unsigned)time(NULL));

	list <int> range;
    list <int>::iterator it;

	for(int i=0;i<n;i++) range.push_back(i);

	int member,j=n;

	//cout<<endl;

	for(j=n;j!=0;--j){

		it = range.begin();

		member = rand() % j;

		advance (it,member);

		//cout<<*it<<"  ";

		perm.push_back(*it);

		range.erase(it);
	}
	//cout<<"\n";
};

//---------------------------------------------------------------------
// Random Sample of {0,1,2,...,(n-1)) take at random m of n;

vector <int> randomsample(int n,int m){

	srand((unsigned)time(NULL));

	list <int> range;
    list <int>::iterator it;

	for(int i=0;i<n;i++) range.push_back(i);

	int member;
	vector <int> sample;
	//cout<<endl;

	for(int i=n;i!=n-m;--i){

		it = range.begin();

		member = rand() % i;

		advance (it,member);

		//cout<<*it<<"  ";

		sample.push_back(*it);

		range.erase(it);
	}

	return sample;
	//cout<<"\n";
};

//Permute m elements of a vector v (v is a permutation of {0,1,...,(n-1)}

void random_perm(int m,vector <int> &v){

	vector <int> rm,perm;
	rm=randomsample(v.size(),m);   // take randomly m from {0,1,...,(n-1)}

	int temp;

	for(int i=0;i<m-1;i++) { //m-1 interchanges
		temp=v[rm[i]];
		v[rm[i]]=v[rm[i+1]];
		v[rm[i+1]]=temp;
	}

}
//---------------------------------------------------------------------

//Print a permutation

void print_perm(vector <int> v){
cout<<"\n{";
for(int i=0;i<(int)(v.size())-1;i++) cout<<v[i]<<",";
cout<<v[v.size()-1]<<"}";
}


