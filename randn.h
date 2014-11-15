/*
 * randn.h
 *
 *  Created on: Jul 17, 2014
 *      Author: tchr
 */

#ifndef RANDN_H_
#define RANDN_H_

//	"Polar" version without trigonometric calls

double randn_notrig(double mu=0.0, double sigma=1.0);

//	Standard version with trigonometric calls

double randn_trig(double mu=0.0, double sigma=1.0);

#endif /* RANDN_H_ */
