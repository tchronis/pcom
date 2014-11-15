/*
 * main.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: tchr
 */


#include<iostream>
#include <time.h>
#include<cstdlib>


#include "randn.h"
#include "benchmarking.h"
//#include "symbol.h"
//#include "constellation.h"
//#include "optimization.h"
//#include "input_files.h"
//#include "noise.h"
#include "console.h"
//#include "boost.h"
#include "permutations.h"
//#include "distances.h"
//#include "QAP.h"
#include "boost_t.h"

using namespace std;

int main ( int argc, char *argv[] ) {

	cout<<"-------------------------------------------------------------------------------\n";
	cout<<"\tProgramming Communication Software (pcom ver. 0.40) 31 July 2014\n";
	cout<<"-------------------------------------------------------------------------------\n";

	//myt(10);

	srand((unsigned)time(NULL));

	//benchmarking();

	time_t seconds_start=time(NULL);

	console();

	cout<<"\n\nTotal running time was "<<(time(NULL)-seconds_start)<<" seconds\n";

//	keep_window_open();

	return (int)(time(NULL)-seconds_start);
}
