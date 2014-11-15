/*
 * distances.h
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#ifndef DISTANCES_H_
#define DISTANCES_H_

#include<vector>

using namespace std;

unsigned hamdist(unsigned x, unsigned y);

template <class T>
T euclidean_sqrdist(vector <T> a,vector <T> b);

template <class T>
T manhattan_dist(vector <T> a,vector <T> b);

template <class T>
T chebychev_dist(vector <T> a,vector <T> b,int &position);

#endif /* DISTANCES_H_ */
