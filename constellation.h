/*
 * constellation.h
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#ifndef CONSTELLATION_H_
#define CONSTELLATION_H_

#include<vector>

using namespace std;

double meanenergy(vector <symbol>);

double dmin(vector <symbol>);

double diameter(vector <symbol>);

void normalize(vector <symbol>&);

void create_circle(double,double,int,vector <symbol> &);

int hd(string const&, string const&);

void print(vector <symbol>);

long double SER_ML(vector <symbol>& s,double sigma,double sdb,int precision,double kappa,double theta,int symb=-1);

long double BER(vector <symbol>);

void stat_SER_ML(vector <symbol>,double,double,int);

#endif /* CONSTELLATION_H_ */
