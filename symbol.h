/*
 * symbol.h
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include<vector>
#include<string>

using namespace std;

class symbol {
public:

	double x,y,radius,theta;
	vector <double> xi;

	vector <pair<int, double> > neighboors;

	void create(double,double);
	void find_neighboors(vector <symbol>,double);
	string bitmap;
	long bit_map;

	long *p;
	long errors;

	double distance(symbol a,symbol b);
};

#endif /* SYMBOL_H_ */
