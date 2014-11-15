/*
 * permutations.h
 *
 *  Created on: Jul 17, 2014
 *      Author: tchr
 */

#ifndef PERMUTATIONS_H_
#define PERMUTATIONS_H_

#include<vector>
#include<cstdlib>

// Random Permutation of 0,1,2,.....,(n-1)

using namespace std;

void permutation(int n,vector <int> &perm);

// Random Sample of {0,1,2,...,(n-1)) take at random m of n;

vector <int> randomsample(int n,int m);

//Permute m elements of a vector v

void random_perm(int m,vector <int> &v);

//Print a permutation

void print_perm(vector <int> v);

#endif /* PERMUTATIONS_H_ */
