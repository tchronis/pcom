/*
 * symbol.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#include<vector>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

#define pi 3.14159265358979323846

class symbol {
public:

	double x,y,radius,theta;
	vector <double> xi;

	double distance(symbol a,symbol b);

	vector <pair<int, double> > neighboors;

	void create(double,double);
	void find_neighboors(vector <symbol>,double);
	string bitmap;
	long bit_map;

	long *p;
	long errors;
};


double distance(symbol a,symbol b){

	double temp=0;
	for(int i=0;i<(int)(a.xi.size());i++)
		temp+=(a.xi[i]-b.xi[i])*(a.xi[i]-b.xi[i]);

	return temp;
};

void symbol::create(double r,double th) {
	x=r*cos(th*pi/180);
	y=r*sin(th*pi/180);
	radius=r;
	theta=th;
	errors=0;
};

bool cmp (const pair<int,double> &left,const pair<int,double> &right) {
	return left.second<right.second;
};

void symbol::find_neighboors(vector <symbol> s,double neighboor_max_dist) {

	double dist;

	for(int i=0;i<(int)s.size();i++){
		dist=(x-s[i].x)*(x-s[i].x)+(y-s[i].y)*(y-s[i].y);
		if(dist<=neighboor_max_dist && dist>0)
			neighboors.push_back(pair<int,double>(i,dist));
	};

	sort(neighboors.begin(),neighboors.end(),cmp);
	//p=new long[neighboors.size()];
};




