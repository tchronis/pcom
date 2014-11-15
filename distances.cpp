/*
 * distances.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#include<vector>

using namespace std;

// Hamming Distance (Code from wikipedia)

unsigned hamdist(unsigned x, unsigned y)
{
  unsigned dist = 0, val = x ^ y;

  // Count the number of set bits
  while(val)
  {
    ++dist;
    val &= val - 1;
  }

  return dist;
}

//Euclidean Distance (without square rooting)

template <class T>
T euclidean_sqrdist(vector <T> a,vector <T> b){

	long l=(long)(a.size());
	T temp,s=0;

	for(long i=0;i<l;i++) {temp=a[i]-b[i];s+=temp*temp;}

	return s;

}

//The Manhattan distance function computes the distance that would be traveled to get
//from one data point to the other if a grid-like path is followed.
//The Manhattan distance between two items is the sum of the differences of their corresponding components.

template <class T>
T manhattan_dist(vector <T> a,vector <T> b){

	long l=(long)(a.size());
	T s=0;

	for(long i=0;i<l;i++) s+=abs(a[i]-b[i]);

	return s;

}

//The Chebychev distance between two points is the maximum distance between the points in any single dimension

template <class T>
T chebychev_dist(vector <T> a,vector <T> b,int &position){

	long l=(long)(a.size());
	T temp,max=abs(a[0]-b[0]);
	int pos=0;

	for(long i=1;i<l;i++){
		temp=abs(a[i]-b[i]);
		if(temp>max) {max=temp;pos=i;}
	}

	position=pos;

	return max;

}


