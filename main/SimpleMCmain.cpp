/*
main program for a simple monte carlo option pricer
@c Dong Wang 2016
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
using namespace std; 

int main(){
	double spot,r,vol,expiry,strike;
	unsigned long number_of_path;
	cout << "\nEnter Expiry:\n";
	cin >> expiry;
	cout << "\nEnter Strike:\n";
	cin >> strike;
	cout << "\nEnter spot:\n";
	cin >> spot;
	cout << "\nEnter interest rate:\n";
	cin >> r;
	cout << "\nEnter Volatility:\n";
	cin >> vol;
	cout << "\nEnter the number of path:\n";
	cin >> number_of_path;

	ParameterConstant r_parameter(r);
	ParameterConstant vol_parameter(vol);

	CallPayOff call_pay_off(strike);
	VanillaOption call_vanilla_option(call_pay_off,expiry);

	StatisticsMoments moments_gatherer(1);
	ConvergenceTable moments_convergence_table(moments_gatherer);

	StatisticsSTE STE_gatherer;
	ConvergenceTable STE_convergence_table(STE_gatherer);
	
	TerminatorPath terminator_path(number_of_path);
	double max_time = 20;
	TerminatorTime terminator_time(max_time);
	TerminatorCombine terminator_path_time(terminator_path,terminator_time);

	RandomParkMiller inner_generator(1);
	// Antithetic generator(inner_generator);
	
	SimpleMC(spot, r_parameter, vol_parameter, call_vanilla_option, terminator_path_time, inner_generator, moments_convergence_table);

    cout << "Here are the results"<< endl;
    cout << "Call statistics: " << endl;
	vector< vector<double> > call_results = moments_convergence_table.GetResultsSoFar();

	for (unsigned long i=0; i< call_results.size(); i++){
		cout << "The " << i <<"th results:" <<endl;
		for (unsigned long j=0; j < call_results[i].size(); j++){
			cout << call_results[i][j] << endl;
		}
	}

	return 0;
}
