/*
 * QAP.h
 *
 *  Created on: Jul 19, 2014
 *      Author: tchr
 */

#ifndef QAP_H_
#define QAP_H_

#include<vector>

using namespace std;

double QAP_sum(double** p,vector <int> x,unsigned (*dist)(unsigned,unsigned),bool symmetric=0 );

vector <int> QAPproblem(long noftimes=100,long randreps=1000,double targetmin=-1,char* filename="QAP.txt");

#endif /* QAP_H_ */
