/*
 * console.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

//#include <boost/lambda/lambda.hpp> //ðñÝðåé íá åßíáé óôçí êïñõöÞ ãéá íá ìçí ìðëÝêåôáé ìå ôçí std_lib_facilities.h

#include<iostream>

#include "symbol.h"
#include "constellations.h"
#include "constellation.h"
#include <time.h>
#include "QAP.h"
#include<cmath>

using namespace std;

void help_console()
{
	cout<<"\nSet Noise target : \"n stdev_phase_noise awgn_db\" ex: \"n 0.01 25\"";
	cout<<"\n\nSet Noise range  : ";
	cout<<"\n\n \"N pn_min pn_max pn_step awgn_min awgn_max awgn_step fading_kappa fading_theta\"";
	cout<<"\n         ex: \"N 0 0.02 0.05 10 35 1 0 0\" the last two 0 imply no-fading";
	cout<<"\n\nSet neighborhood : \"k 3\" sets max_nei_dist=3*mind;";
	cout<<"\n\nFlag normalize   : \"f 1\" default \"f 0\" normalize off";
	cout<<"\n\nCreating the Constellation  :";
	cout<<"\n                    \"c BPSK -1\"";
	cout<<"\n                    \"c QPSK -1\"";
	cout<<"\n                    \"c PSK n phi -1\"";
	cout<<"\n                    \"c M-PAM n -1\"  (n must be even)";
	cout<<"\n                    \"c M-QAM m n -1\"  (both n and m are even)";
	cout<<"\n                    \"c APSK r1 theta1 n1 r2 theta2 n2 ... rk thetak nk -1\"";
	cout<<"\n                    \"c XY I1 Q1 I2 Q2 ... Ik Qk -1\"";
	cout<<"\n                    \"c HEX m n theta -1\"  (both n and m are even, theta in rad)";

	cout<<"\n\nPrecision :\"a value\" ex: \"a 7\" default";
	cout<<"\nSimulate : \"s -1\" for all symbol or \"s 4\" for the forth symbol only. ";
	cout<<"\nSimulate ptable : \"t\"";

	cout<<"\n\nPrint Constellation : \"p\"";
	cout<<"\n\nCount number of symbols inside a circle : \"m radius\"";
	cout<<"\n\nExit : \"e\"\n";

	cout<<"\nNEW FUNCTION! - you must create a QAP.txt file";
	cout<<"\nSolving QAP bitmap problem with hamming distances :";
	cout<<"\n                    \"b noftimes randreps targetmin filename\"";
	cout<<"\n                    \"b 100 1000 -1 qap.txt\"";

	cout<<"\n";
};


void console(){

constellation A(1);

double sdb,noise,pn;

double pn_min=0,pn_max=0,pn_step=1,awgn_min=10,awgn_max=10,awgn_step=1;

double kappa,theta; // fading parameters

string modulation="QPSK",temp;

char first_arg='1';

double result,par;

int precision=7,k=3;//max_nei_dist= k times mind

int symb;

bool f;

vector <double> pars;

long noftimes,randreps;
double targetmin;
char* qap_filename;
vector <int> bitmap;

cout<<"Welcome to basic console interface.\nType \"h\" to learn how to use the commands , or type \"e\" to exit!:-)\n";
cout<<"\n";


while(first_arg!='e')
{
	pars.erase(pars.begin(),pars.end());

	cout<<"\n:>";

	cin>>first_arg;

	switch (first_arg)
	{
	case 'b':
		cin>>noftimes;cin>>randreps;cin>>targetmin;cin>>qap_filename;
		bitmap=QAPproblem(noftimes,randreps,targetmin,qap_filename);
		cout<<"{";
		for(int i=0;i<(int)(bitmap.size()-1);i++) cout<<bitmap[i]<<",";
		cout<<bitmap[bitmap.size()-1]<<"}\n";
		break;
	case 'a':
		cin>>precision;break;
	case 'p':
		A.print();break;
	case 'h':
		help_console();break;
	case 'n':
		cin>>pn_min;pn_max=pn_min;pn_step=1;
		cin>>awgn_min;awgn_max=awgn_min;awgn_step=1;
		kappa=0;theta=0;break;
	case 'N':
		cin>>pn_min>>pn_max>>pn_step;
		cin>>awgn_min>>awgn_max>>awgn_step;
		cin>>kappa>>theta;
		break;
	case 'k' :
		cin>>k;
		break;
	case 'f' :
		cin>>f;
		A.flag_normalize=f;
		break;
	case 'c':
		cin>>modulation;
		cin>>par;

		while(par!=-1)	{pars.push_back(par);cin>>par;}  //ends when par equals -1

		A.del();

		if(A.set(modulation,pars))
			{
			A.find_dmin();cout<<"\ndmin = "<<A.dmin;
			A.max_nei_dist=k*A.dmin;
			cout<<"\nmax_nei_dist= "<<A.max_nei_dist;

			//cout<<"\n-"<<time(NULL);
			//int ss;
			//cin>>ss;
			//cout<<"\nExpected time completion : "<<(1.0*A.s.size()*A.s.size())/(ss*ss);

			A.find_allcharacteristics();

		//cout<<"\n-"<<time(NULL);
		}
		else cout<<"\nPlease give the correct number of parameters...";
		break;
	case 's':
		cin>>symb;
		for(pn=pn_min;pn<=pn_max;pn+=pn_step)
		{
			for(noise=awgn_min;noise<=awgn_max;noise+=awgn_step)
			{
				sdb=sqrt((1/pow(10.,noise/10.))/2);      // noise=10*log(1/(2*s^2))

				//cout<<"\n-"<<time(NULL);
				result=SER_ML(A.s,pn,sdb,precision,kappa,theta,symb);
				//cout<<"\n-"<<time(NULL);
				cout<<"\t"<<pn<<"\t"<<noise;
				if(result==0) break;
			};
		};
		break;
	case 'm':
		double max_energy;
		cin>>max_energy;
		cout<<"\nNo of symbols : "<<A.select(max_energy);
		break;
	default:
		if(first_arg!='e') cout<<"\nI don't understand this command... (yet :-P)";
		break;
	}
};
cout<<"\nExiting ... i hope you enjoyed many simulations!\n";
cin.clear();
}

/*

std::string line;
while (std::getline(std::cin, line))
{
    std::cout << line << std::endl;
}

*/

/* strtod example */
/*
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  char szOrbits[] = "365.24 29.53";
  char * pEnd;
  double d1, d2;
  d1 = strtod (szOrbits,&pEnd);
  d2 = strtod (pEnd,NULL);
  printf ("The moon completes %.2lf orbits per Earth year.\n", d1/d2);
  return 0;
}

*/

/*

getline( std::cin, in, '\n' );

if(in.substr(0,2)=="n "){
	temp=in.substr(2,in.length());
	noise=strtod(temp.c_str(),&pEnd);
	sdb=sqrt((1/pow(10.,noise/10.))/2);
	pn=strtod(pEnd,NULL);
};

}
*/



