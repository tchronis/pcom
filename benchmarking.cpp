/*
 * benchmarking.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: tchr
 */


#include <iostream>
#include <time.h>
#include <stdint.h>
#include <ctime>

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/gamma_distribution.hpp>

#include <boost/random/uniform_int_distribution.hpp>

#include "randn.h"
#include "permutations.h"

using namespace std;

double benchmarking() {

	//double a=0.0;
	double a=0;

	uint8_t i,j,k,l;

	cout<<"\nBenchmarking one core - please wait...\n";

	clock_t t1,t2;


// Adding numbers

	t1=clock();

		/*
		One thing that can slow any loop, and often does:
		The post- increment/decrement, when a pre- increment/decrement will do the job.
		The post- version requires an anonymous variable be created, while the pre- version does not.
		*/

	for(i=125;i!=0;--i){
		for(j=200;j!=0;--j){
			for(k=200;k!=0;--k){
				for(l=200;l!=0;--l){
				a+=0.01;
				}}}}

	t2=clock();

    cout<<"\nAdded 1 billion numbers in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.\n";

//Creating Permutations

	vector <int> p;

	t1=clock();

	for ( long counter = 1000000; counter!=0; --counter ) {
		permutation(16,p);
		p.clear();
	}

	t2=clock();

    cout<<"\n1 Million Permutations of 16 numbers in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.\n";

//------------------------------------------------------------------------
//		Random Distributions
//------------------------------------------------------------------------
	int n=10;

	cout<<"\nCreating "<<n<<" million random numbers of several Distributions";

	double g;
// Creating Normal Distributed random numbers ("Polar" version without trigonometric calls)
	g=0;
	t1=clock();
	for ( long counter = n*1000000; counter!=0; --counter ) g+=randn_notrig();
	t2=clock();
	cout<<"\n\t(Normal Distr. Notrig) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 6; counter!=0; --counter ) cout<<randn_notrig()<<"   ";

// Creating Normal Distributed random numbers (Standard version with trigonometric calls)
	g=0;
	t1=clock();
	for ( long counter = n*1000000; counter!=0; --counter ) g+=randn_trig();
	t2=clock();
	cout<<"\n\t(Normal Distr. Trig) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 6; counter!=0; --counter ) cout<<randn_trig()<<"   ";

// Boost Libraries
	typedef boost::mt11213b RNGType;
    RNGType rng;
//------------------------

// Creating Normal Distribution numbers (Boost)

	g=0;

    boost::random::normal_distribution<> norm(0,1);
    boost::variate_generator< RNGType, boost::random::normal_distribution<> >
                    normal(rng, norm);
	t1=clock();
	  for ( long counter = n*1000000; counter!=0; --counter ) g+=normal();
	t2=clock();

	cout<<"\n\t(Normal Distr. (Boost)) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 6; counter!=0; --counter ) cout<<normal()<<"   ";

// Creating Gamma Distribution numbers (Boost)
	g=0;

    boost::random::gamma_distribution<> gamma(1,1);
    boost::variate_generator< RNGType, boost::random::gamma_distribution<> >
                    gammanum(rng, gamma);
	t1=clock();
	  for ( long counter = n*1000000; counter!=0; --counter ) g+=gammanum();
	t2=clock();

	cout<<"\n\t(Gamma Distr. (Boost)) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 6; counter!=0; --counter ) cout<<gammanum()<<"   ";

// Creating Uniform Distribution integer numbers (Boost)
	g=0;

	boost::random::uniform_int_distribution<> unif(1, 6);

	t1=clock();
	  for ( long counter = n*1000000; counter!=0; --counter ) g+=unif(rng);
	t2=clock();

	cout<<"\n\t(Unif.Distr. (Boost)) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 20; counter!=0; --counter ) cout<<unif(rng)<<"   ";

// Creating Poisson Distribution numbers (Boost)
	g=0;

	boost::random::poisson_distribution<> pois(10);

	t1=clock();
	  for ( long counter = n*1000000; counter!=0; --counter ) g+=pois(rng);
	t2=clock();

	cout<<"\n\t(Poisson Distr. (Boost)) in "<<(float)(1.0*(t2-t1)/(1.0*CLOCKS_PER_SEC))<<" seconds.";
	//cout<<endl;for ( long counter = 20; counter!=0; --counter ) cout<<pois(rng)<<"   ";

// -------------------------------------------------------------------------------------------
	cout<<"\n\nRunning a typical simulation with required characteristics to estimate which functions and parameters to use during execution time. This waiting time will be rewarded due to minimal total time execution.\n";
	cout<<"Additionally you will be informed with good accuracy about the estimated remaining time for your simulations.\n";
	cout<<"--------------------------------------------------------------------------------\n";

	return a;
};
// Validity Check
// Simulations Benchmark

