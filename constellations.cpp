/*
 * constellations.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */


#include<iostream>
#include<cmath>
#include "symbol.h"
#include "statistics.h"

#define pi 3.14159265358979323846

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
	//-------------------------
	void create_circle(double radius,double theta,int number_of_symbols);
	bool set(string modulation,vector <double> pars);
	int select(double max_energy); // to do ....................................
	void del();
};


void constellation::normalize() {

	find_mean_energy(); //priority of course

	double temp=sqrt(mean_energy);
	if(flag_normalize==1) {
	for(int i=0;i<(int)(s.size());i++) {
		s[i].x=s[i].x/temp;s[i].y=s[i].y/temp;
		s[i].radius=s[i].radius/temp;
	};
	};
};

void constellation::find_dmin(){
	double temp,min=(s[0].x-s[1].x)*(s[0].x-s[1].x)+(s[0].y-s[1].y)*(s[0].y-s[1].y);
	for(int i=0;i<(int)(s.size());i++)
		for(int j=i+1;j<(int)(s.size());j++)
		{
			temp=(s[i].x-s[j].x)*(s[i].x-s[j].x)+(s[i].y-s[j].y)*(s[i].y-s[j].y);
			if(temp<min) min=temp;
		}
	dmin=min;
};

void constellation::find_dmean(){
	double temp=0;
	for(int i=0;i<(int)(s.size());i++) temp+=s[i].neighboors[0].second;
	dmean=temp/s.size();
}

void constellation::find_max_energy(){
	double temp=0,max=0;
	for(int i=0;i<(int)(s.size());i++)
			{
			temp=s[i].x*s[i].x+s[i].y*s[i].y;
			if(temp>max) max=temp;
			}

	max_energy=max;
};

void constellation::find_mean_energy(){
	double temp=0;
	for(int i=0;i<(int)(s.size());i++)

		temp+=s[i].x*s[i].x+s[i].y*s[i].y;

	mean_energy=temp/s.size();
};

void constellation::find_allcharacteristics(){
	for(int i=0;i<(int)(s.size());i++) s[i].find_neighboors(s,max_nei_dist);
	find_dmin();
	find_dmean();
	find_max_energy();
	find_mean_energy();
	cout<<"\nN="<<s.size()<<";";
	cout<<"\n{mean_energy , dmin , dmean , max_energy}= {";
	cout<<mean_energy<<","<<dmin<<","<<dmean<<","<<max_energy<<"};";
};

void constellation::print(){

	cout<<"\n-------------------------------------------------------------------------------";

	cout<<"\nconstellation={";cout<<"{"<<s[0].x<<","<<s[0].y<<"}";
	for(int i=1;i<(int)(s.size());i++) cout<<",{"<<s[i].x<<","<<s[i].y<<"}";
	cout<<"};";

	cout<<"\nneighboors={";
	cout<<"{"<<s[0].neighboors[0].first;
	for(int j=1;j<(int)(s[0].neighboors.size());j++) cout<<","<<s[0].neighboors[j].first;
	cout<<"}";

	for(int i=1;i<(int)s.size();i++)
	{
	cout<<",{"<<s[i].neighboors[0].first;
	for(int j=1;j<(int)(s[i].neighboors.size());j++) cout<<","<<s[i].neighboors[j].first;
	cout<<"}";
	}
	cout<<"};";

	cout<<"\n-------------------------------------------------------------------------------";
};

void constellation::modify_symbol(int k,symbol neo){
	s[k]=neo;
	//..............................
};

constellation::constellation(bool f) {
  flag_normalize=f;
  //symbol temp;temp.x=0;temp.y=0;
  //for(int i=0;i<N;i++) s.push_back(temp);
};

constellation::constellation(vector <symbol> si) {
    symbol temp;temp.x=0;temp.y=0;
	for(int i=0;i<(int)(si.size());i++) {s.push_back(temp);s[i]=si[i];}
};

void constellation::create_circle(double radius,double theta,int number_of_symbols){
	symbol temp;
	for(int i=0;i<number_of_symbols;i++){
		temp.x=radius*cos(theta+(i*360/number_of_symbols)*pi/180);
		temp.y=radius*sin(theta+(i*360/number_of_symbols)*pi/180);
		s.push_back(temp);
	};
};

bool constellation::set(string modulation,vector <double> pars){

	symbol temp;
	double c;
	int i,j;

	if(modulation=="BPSK")
	{
		if(pars.size()!=0) return 0;
		temp.x=1;temp.y=0;s.push_back(temp);
		temp.x=-1;temp.y=0;s.push_back(temp);
		return 1;
	}
	else if(modulation=="QPSK")
	{
		if(pars.size()!=0) return 0;
		c=0.7071067811865475;
		temp.x=c;temp.y=c;s.push_back(temp);
		temp.x=-c;temp.y=c;s.push_back(temp);
		temp.x=-c;temp.y=-c;s.push_back(temp);
		temp.x=c;temp.y=-c;s.push_back(temp);
		return 1;
	}
	else if(modulation=="PSK")
		//pars[0]:Number of symbols
		//pars[1]:Initial Angle
	{
		if(pars.size()!=2) return 0;
		for(i=0;i<pars[0];i++){
		temp.create(1,pars[1]+i*360/pars[0]);
		s.push_back(temp);};
		return 1;
	}
	else if(modulation=="M-PAM")
		//pars[0]:Number of symbols (M)
	{
		if(pars.size()!=1 || ((int)pars[0]%2)!=0) return 0;
		for(i=-(int)(pars[0]/2);i<(int)(pars[0]/2);i++) {
			temp.x=i+0.5;temp.y=0;s.push_back(temp);
		};
		normalize();
		return 1;
	}
	else if(modulation=="M-QAM")
		//pars[0]:Number of symbols (M) in vertical (even)
		//pars[1]:Number of symbols (N) in horizontal (even)
	{
		if(pars.size()!=2 || ((int)pars[0])%2!=0 || ((int)pars[1])%2!=0) return 0;
		for(i=-(int)(pars[0]/2);i<(int)(pars[0]/2);i++)
			for(j=-(int)(pars[1]/2);j<(int)(pars[1]/2);j++)
			{temp.x=i+0.5;temp.y=j+0.5;s.push_back(temp);};

		normalize();
		return 1;
	}
	else if(modulation=="APSK")
		//pars[3*i]:r
		//pars[3*i+1]:theta
		//pars[3*i+2]:no_of_points
	{
		if(pars.size()%3!=0) return 0;// div((int)(pars.size()),3).quot
		for(i=0;i<(int)(pars.size()/3);i++) create_circle(pars[3*i],pars[3*i+1],(int)(pars[3*i+2]));

		normalize();
		return 1;
	}
	else if(modulation=="XY")
		//pars[2*i]:x
		//pars[2*i+1]:y
	{
		if(pars.size()%2!=0) return 0;
		for(i=0;i<(int)(pars.size()/2);i++)
			{temp.x=pars[2*i];temp.y=pars[2*i+1];
			s.push_back(temp);
			}
			normalize();
			return 1;
	}
	else if(modulation=="HEX")
		//
		//
	{
		if(pars.size()!=3 || ((int)pars[0])%2!=0 || ((int)pars[1])%2!=0) return 0;
		for(i=-(int)(pars[0]/2);i<(int)(pars[0]/2);i++)
			for(j=-(int)(pars[1]/2);j<(int)(pars[1]/2);j++)
			{
				temp.x=i+j*cos(pars[2]);
				temp.y=j*sin(pars[2]);
				s.push_back(temp);
			};
		s.erase(s.begin());
		normalize();
		return 1;
	}
	else
	{
		cout<<"\nI don't know what to do...\n";
		return 0;
	}
};

int constellation::select(double max_energy){
	int counter=0;
	for(int i=0;i<(int)(s.size());i++) if(s[i].x*s[i].x+s[i].y*s[i].y<=max_energy) counter++;
	return counter;
};

void constellation::del(){
	s.erase(s.begin(),s.end());
};


