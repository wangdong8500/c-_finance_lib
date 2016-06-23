#ifndef BISECTION_H
#define BISECTION_H
#include <cmath>

#include <iostream>
using namespace std;

template <class T> 
double Bisection(double target, T the_function, 
	double low, double high, double tolerance = 1e-7){

	double f_low = the_function(low) - target;
	double f_high = the_function(high) - target;
	if (f_low*f_high > 0)
		throw("no simple solution between this low and high!");

	double mid = 0.5*(low + high);
	double f_mid = the_function(mid) - target;
	
	while(fabs(f_mid)>tolerance){

		cout << mid << "," << f_low << "," << f_mid << "," << f_high <<endl;

		if(f_mid*f_low < 0){ 
			high = mid;
			f_high = f_mid;
		}
		else{
			low = mid;
			f_low = f_mid;
		}
		mid = 0.5*(low + high);
		f_mid = the_function(mid) - target;
	}

	return mid;
}

#endif