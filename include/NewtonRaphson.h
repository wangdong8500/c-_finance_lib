#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <cmath>

template <class T, double (T::*value) (double) const, double (T::*derivative) (double) const>
double NewtonRaphson(double target, const T& the_object, double start, double tolerance){
	double y = (the_object.*value)(start)-target;
	double x = start;
	double d;
	while(fabs(y)>tolerance){
		d = (the_object.*derivative)(x);
		x = x - y/d;
		y = (the_object.*value)(x)-target;
	}
	return x;
} 

#endif
