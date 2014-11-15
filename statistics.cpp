/*
 * statistics.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#include<vector>
#include<cmath>

using namespace std;

long double min(vector <long double> r){

	long double minimum=r[0];

	for(long i=1;i<(long)r.size();i++)
		if(r[i]<minimum) minimum=r[i];

	return minimum;
};

long double max(vector <long double> r){

	long double maximum=r[0];

	for(long i=1;i<(long)r.size();i++)
		if(r[i]>maximum) maximum=r[i];

	return maximum;
};

long double mean(vector <long double> r){

	long double sum=0;

	for(long i=0;i<(long)r.size();i++) sum+=r[i];

	return sum/r.size();
};

long double st_dev(vector <long double> r){

	long double sum=0,m=mean(r);

	for(long i=0;i<(long)r.size();i++) sum+=pow(r[i]-m,2);

	return sqrt(sum/(r.size()-1));
};

long double adev(vector <long double> r){

	long double sum=0,m=mean(r);

	for(long i=0;i<(long)r.size();i++) sum+=abs(r[i]-m);

	return sqrt(sum/(r.size()));
};

long double skew(vector <long double> r){

	long double sum=0,m=mean(r);

	for(long i=0;i<(long)r.size();i++) sum+=pow(r[i]-m,3);

	return sum/(r.size()*pow(st_dev(r),3));
};


