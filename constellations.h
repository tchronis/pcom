/*
 * constellations.h
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#ifndef CONSTELLATIONS_H_
#define CONSTELLATIONS_H_

#include<vector>

using namespace std;

class constellation {

public:

	vector <symbol> s;
	double mean_energy; //ok
	double dmin; //ok
	double dmean;
	double max_energy; //ok
	double awgn,pn,fading; //noise models   s->Function(s,Noise,Interference,Fading,...)
	double max_nei_dist; //ïðùóäÞðïôå ðñÝðåé íá áñ÷éêïðïéÞôáé
	double SER,BER;
	bool flag_normalize;
	//-------------------------
	void normalize(); //ok
	//-------------------------
	void find_dmin(); //ok
	void find_dmean(); //ok
	void find_max_energy(); //ok
	void find_mean_energy(); //ok
	//-------------------------
	void find_allcharacteristics(); //on-going
	//-------------------------
	void print(); // to add more
	//-------------------------
	void modify_symbol(int k,symbol neo); // to parametrize more
	//-------------------------
	constellation(bool f); //ok
	constellation(vector <symbol> si); //ok
	void create_circle(double radius,double theta,int number_of_symbols);
	bool set(string modulation,vector <double> pars);
	int select(double max_energy);
	void del();
};


#endif /* CONSTELLATIONS_H_ */
