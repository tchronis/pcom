/*
 * constellation.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
//#include <boost/random/gamma_distribution.hpp>

#include<iostream>
#include<vector>

#include "symbol.h"
#include "randn.h"
#include "statistics.h"
#include <time.h>

using namespace std;

double meanenergy(vector <symbol> s){
	double me=0;
	for(int i=0;i<(int)s.size();i++){me=me+s[i].x*s[i].x+s[i].y*s[i].y;}
	return me/s.size();
};

double dmin(vector <symbol> s){
	double temp,dmin2=(s[0].x-s[1].x)*(s[0].x-s[1].x)+(s[0].y-s[1].y)*(s[0].y-s[1].y);
	for(int i=0;i<(int)s.size();i++)
		for(int j=i+1;j<(int)s.size();j++)
		{
			temp=(s[i].x-s[j].x)*(s[i].x-s[j].x)+(s[i].y-s[j].y)*(s[i].y-s[j].y);
			if(temp<dmin2) dmin2=temp;
		}
		return sqrt(dmin2);
};

double diameter(vector <symbol> s){
int N=(int)s.size();
double diam=0,temp;
for(int i=0;i<N;i++){
	for(int j=i+1;j<N;j++){
		temp=(s[i].x-s[j].x)*(s[i].x-s[j].x)+(s[i].y-s[j].y)*(s[i].y-s[j].y);
		if(temp>diam) diam=temp;
	}}
return sqrt(diam);
};

void normalize(vector <symbol>& s) {
	double mean_power=sqrt(meanenergy(s));
	for(int i=0;i<(int)s.size();i++)
	{s[i].x=s[i].x/mean_power;s[i].y=s[i].y/mean_power;s[i].radius=s[i].radius/mean_power;}
};

void create_circle(double radius,double theta,int number_of_symbols,vector <symbol> &s){
	symbol temp;
	for(int i=0;i<number_of_symbols;i++){
		temp.create(radius,theta+i*360/number_of_symbols);
		s.push_back(temp);
	};
};

int hd(string const& s1, string const& s2)
{
    // hd stands for "Hamming Distance"
    int dif = 0;

    for (int i = 0; i <(int)(s1.size()); i++ )
    {
        char b1 = s1[i];
        char b2 = s2[i];

        dif += (b1 != b2)?1:0;
    }

    return dif;
};

void print(vector <symbol> s){

	cout<<"\n---------------------------------------------------------\n";

	cout<<"\nNumber of symbols = "<<s.size()<<"\n";

	cout<<"\nConstellation's diameter = "<<diameter(s)<<"\n";

	cout<<"\n{";
	for(int i=0;i<(int)s.size();i++) cout<<"{"<<s[i].x<<","<<s[i].y<<"},";
	cout<<"\b}\n";

	cout<<"\nSymbols neighboors!\n";
	for(int i=0;i<(int)s.size();i++) {
		cout<<i<<"={"<<s[i].x<<","<<s[i].y<<"} has "<<s[i].neighboors.size()<<" neis --> ";
		for(int j=0;j<(int)(s[i].neighboors.size());j++) cout<<s[i].p[j]<<" ("<<s[i].neighboors[j].first<<") ";
		cout<<"\n";};

	cout<<"\n---------------------------------------------------------\n";

};

long double SER_ML(vector <symbol>& s,double sigma,double sdb,int precision,double kappa,double theta,int symb=-1){//kappa , theta --> fading parameters
	long long samples=(long long)pow(10.,1.0*precision);
	const int N=(int)s.size();
	double phase_noise,cs,sn;
	double rx,ry;
	long long errors=0,counter;
	int i,j;
	int t,nei,arg;
	double min;
	//time_t seconds_start=time(NULL);
	long max_errors,count_errors;

	  typedef boost::mt11213b RNGType; //10% faster than :  mt19937 RNGType;  which is 10% slower than randn_notrig
      RNGType rng;
     /*
      boost::random::gamma_distribution<> gamma(kappa,theta);
      boost::variate_generator< RNGType, boost::random::gamma_distribution<> >
                    dice(rng, gamma);
                    */

	  boost::random::normal_distribution<> awgn_norm(0,sdb);
	  boost::variate_generator< RNGType, boost::random::normal_distribution<> >
                    AWGN(rng, awgn_norm);

	  boost::random::normal_distribution<> pn_norm(0,sigma);
	  boost::variate_generator< RNGType, boost::random::normal_distribution<> >
                    PN(rng, pn_norm);

	double hx,hy;


	// if symb== -2 then calculate ptable

	if(symb==-2) {//###
					for(i=0;i<N;i++) s[i].p=new long[N]; //###
					for(i=0;i<N;i++) for(j=0;j<N;j++) s[i].p[j]=0; // zero ptable at the beginning //###
				}//###

	max_errors=(long)(20*(pow(10,1.0*(abs(precision-7))))*(N+48));

    for(t=0;t<N;t++) s[t].errors=0; // zero errors at the beginning

		for(counter=0;counter<samples && errors<max_errors;counter++){

		if(symb==-1 || symb==-2) t=rand()%N;
		else t=symb-1;

		if(kappa==0 && theta==0) {hx=1;hy=1;}
		//else {hx=sqrt(dice());hy=sqrt(dice());}//PROBLEM IN GAMMA DISTRIBUTION OLDER LIBRARY


			phase_noise=PN();//randn_notrig(0,sigma);
			cs=cos(phase_noise);sn=sin(phase_noise);
			rx=hx*(s[t].x*cs-s[t].y*sn)+AWGN();//randn_notrig(0,sdb);
			ry=hy*(s[t].x*sn+s[t].y*cs)+AWGN();//randn_notrig(0,sdb);

			min=(rx-hx*s[t].x)*(rx-hx*s[t].x)+(ry-hy*s[t].y)*(ry-hy*s[t].y);

			arg=t;

			count_errors=0; //This exists to count SER errors only once
			for(int k=0;k<(int)s[t].neighboors.size();k++) {
				nei=s[t].neighboors[k].first;
				if(((rx-hx*s[nei].x)*(rx-hx*s[nei].x)+(ry-hy*s[nei].y)*(ry-hy*s[nei].y))<min)
					{
						count_errors++;
						if(count_errors==1) {
											s[t].errors++;errors++;
											}//###
						if(symb==-1) break; //### ONLY SER

						arg=nei;//###
				};

			};

			if(symb==-2) s[t].p[arg]++; // don't break if symb==-2 //###

			/* Without neighbooring

			for(int j=t-1;j>=0;j--) {
								if((rx-s[j].x)*(rx-s[j].x)+(ry-s[j].y)*(ry-s[j].y)<min) {errors++;goto gobreak;}
				};

			for(int j=t+1;j<N;j++) {
								if((rx-s[j].x)*(rx-s[j].x)+(ry-s[j].y)*(ry-s[j].y)<min) {errors++;break;}
				};

		gobreak: //goto label
		*/

		};

		//###
		double temp;
		if(symb==-2) {cout<<"\n\n";
						for(i=0;i<N;i++) {temp=0;
							for(j=0;j<N;j++) {cout<<s[i].p[j]<<"   ";temp=temp+s[i].p[j];}
							cout<<" --> "<<temp<<"  --- SER["<<i<<"]="<<(1-1.0*s[i].p[i]/temp);cout<<endl;
						}
		}

		if(symb==-2) {for(i=0;i<N;i++) delete s[i].p;} //###

		std::cout.precision(precision+1);
		cout<<"\n"<<1.0*errors/counter<<"\t"<<counter<<"\t";
		//cout<<" simulation time = "<<time(NULL)-seconds_start<<" sec."; // samples

	return 1.0*errors/counter;
};


long double BER(vector <symbol> s){ // to be completed

	int N=s.size();

	double ber=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<(int)s[i].neighboors.size();j++)
			if(i!=j)
				ber=ber+hd(s[i].bitmap,s[s[i].neighboors[j].first].bitmap)*s[i].p[j];

	return ber/(N*log(1.0*N)/log(2.0));
};

void stat_SER_ML(vector <symbol> s,double sigma,double db,int precision){

	double sdb=sqrt((1/pow(10.,(db/10.)))/2);
	normalize(s);

	vector <long double> r;

	for(long i=0;i<25;i++) r.push_back(SER_ML(s,sigma,sdb,precision,0,0));

	cout<<"\nMin = "<<min(r)<<" , Max = "<<max(r)<<" , Max-Min = "<<(max(r)-min(r));
	cout<<"\nMean = "<<mean(r)<<" , STD = "<<st_dev(r)<<" , relative deviation = "<<100*(max(r)-min(r))/mean(r)<<" %";
	cout<<"\nADev = "<<adev(r)<<" , Skew = "<<skew(r);
	cout<<"\n";

}


