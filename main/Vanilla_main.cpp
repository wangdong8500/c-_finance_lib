/*
main program for a monte carlo non-pathdependent option pricer
need source files:

Arrays.cpp
BlackScholesFormulas.cpp
Normals.cpp
Parameter.cpp
ParkMiller.cpp
PayOff.cpp
Random2.cpp
SimpleMC.cpp
StatisticsMC.cpp
Terminator.cpp
VanillaOption.cpp
*/

#include <iostream>
#include <vector>
#include <PayOff.h>
#include <VanillaOption.h>
#include <Parameter.h>
#include <StatisticsMC.h>
#include <ConvergenceTable.h>
#include <Terminator.h>
#include <ParkMiller.h>
#include <Antithetic.h>
#include <SimpleMC.h>
#include <BlackScholesFormulas.h>
using namespace std; 

int main(){

	// input parameters
	double spot,r,d,vol,expiry,strike;
	unsigned long number_of_path;
	cout << "\nEnter Expiry:\n";
	cin >> expiry;
	cout << "\nEnter Strike:\n";
	cin >> strike;
	cout << "\nEnter Spot:\n";
	cin >> spot;
	cout << "\nEnter interest rate:\n";
	cin >> r;
	cout << "\nEnter dividend rate:\n";
	cin >> d;
	cout << "\nEnter Volatility:\n";
	cin >> vol;
	cout << "\nEnter the number of path:\n";
	cin >> number_of_path;

    // underlying dynamics parameters setup
	ParameterConstant r_parameter(r);
	ParameterConstant vol_parameter(vol);
	ParameterConstant d_parameter(d);

	// statistics gatherer setup
	StatisticsMeanSTE gatherer;
	
	// random number generator setup
	RandomParkMiller inner_generator(1);

	// terminating condition setup
	TerminatorPath terminator_path(number_of_path);
	double max_time = 20;
	TerminatorTime terminator_time(max_time);
	TerminatorCombine terminator_path_time(terminator_path,terminator_time);
	
	/************************** for call option ******************/
	CallPayOff call_pay_off(strike);
	VanillaOption call_option(call_pay_off,expiry);

	SimpleMC(spot, r_parameter, d_parameter, vol_parameter, call_option, terminator_path_time, inner_generator, gatherer);

    cout << "\nCall Option:"<< endl;
	vector< vector<double> > call_results = gatherer.GetResultsSoFar();
	cout << "MC price with 1 sigma standard error:" << call_results[0][0] << "+-" << call_results[1][0] <<endl;

    double BS_call_price = BlackScholesCall(spot,strike,r,d,vol,expiry);
    cout << "Black Scholes Price: " << BS_call_price <<endl;
	
	/******************************* for put option ******************/
	PutPayOff put_pay_off(strike);
	VanillaOption put_option(put_pay_off,expiry);

	// need to reset terminator and statistics gatherer, and random number generator
	terminator_path_time.reset();
	gatherer.ResetGatherer();
	inner_generator.Reset();
	SimpleMC(spot, r_parameter, d_parameter, vol_parameter, put_option, terminator_path_time, inner_generator, gatherer);

	cout << "\nPut Option:"<< endl;
	vector< vector<double> > put_results = gatherer.GetResultsSoFar();
	cout << "MC price with 1 sigma standard error:" << put_results[0][0] << "+-" << put_results[1][0] <<endl;

    double BS_put_price = BlackScholesPut(spot,strike,r,d,vol,expiry);
    cout << "Black Scholes Price: " << BS_put_price <<endl;
	
	return 0;
}
