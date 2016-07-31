/*
    uses source files 
    Arrays.cpp,
    BlackScholesFormulas.cpp  
    ConvergenceTable.cpp, 
    ExoticEngineBS.cpp
    ExoticEngine.cpp
    StatisticsMC.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp,
    PathDependent.cpp
    PathDependentAsian.cpp
    PathDependentGeometricAsian.cpp
    PayOff.cpp
    Random2.cpp,
    Terminator.cpp
  */

#include <ParkMiller.h>
#include <iostream>
#include <iomanip>
using namespace std;
#include <StatisticsMC.h>
#include <ConvergenceTable.h>
#include <AntiThetic.h>
#include <PathDependentAsian.h>
#include <ExoticEngineBS.h>
#include <BlackScholesFormulas.h>
#include <cmath>

int main()
{

	double expiry;
	double strike; 
	double spot; 
	double vol; 
	double r;
    double d;
	unsigned long number_of_paths;
    unsigned number_of_dates;

	cout << "\nEnter expiry\n";
	cin >> expiry;


	cout << "\nStrike\n";
	cin >> strike;


	cout << "\nEnter spot\n";
	cin >> spot;

	cout << "\nEnter vol\n";
	cin >> vol;


	cout << "\nr\n";
	cin >> r;

    cout << "\nd\n";
    cin >> d;

    cout << "\nNumber of dates\n";
    cin >> number_of_dates;

	cout << "\nNumber of paths\n";
	cin >> number_of_paths;

    CallPayOff the_pay_off(strike);

    MJArray times(number_of_dates);

    for (unsigned long i=0; i < number_of_dates; i++)
        times[i] = (i+1.0)*expiry/number_of_dates;

    ParameterConstant vol_param(vol);
    ParameterConstant r_param(r);
    ParameterConstant d_param(d);

    StatisticsMean gatherer;
    ConvergenceTable convergence_gatherer(gatherer);

    RandomParkMiller generator(number_of_dates);
    
    //Antithetic generator_antithetic(generator);

    TerminatorPath terminator_path(number_of_paths);
    TerminatorTime terminator_time(10.);
    TerminatorCombine terminator(terminator_path,terminator_time);

    /*************************Arithmetic Asian call option***************************************/
    {

    PathDependentAsian the_option(times, expiry, the_pay_off);
    ExoticEngineBS the_engine(r_param, d_param, vol_param, the_option, generator, spot);
    the_engine.DoSimulation(convergence_gatherer, terminator);
    vector<vector<double> > results =convergence_gatherer.GetResultsSoFar();

	cout <<"\nFor the Arithmetic Asian call option the convergence table is \n";
    int width = 15;
    cout << setw(width) << "Price" << setw(width) << "No. of Path" << endl;  
    
    for (unsigned long i=0; i < results.size(); i++)
    {
        for (unsigned long j=0; j < results[i].size(); j++)
            cout << setw(width) << results[i][j];

        cout << "\n";
    } 

    }
    /*************************Geometric Asian call option***************************************/
    {

    generator.Reset();
    PathDependentGeometricAsian the_option(times, expiry, the_pay_off);
    ExoticEngineBS the_engine(r_param,d_param, vol_param, the_option, generator, spot);
    convergence_gatherer.ResetGatherer();
    terminator.reset();
    the_engine.DoSimulation(convergence_gatherer, terminator);
    vector<vector<double> > results = convergence_gatherer.GetResultsSoFar();

    cout <<"\nFor the Geometric Asian call option the convergence table is \n";
    int width = 15;
    cout << setw(width) << "Price" << setw(width) << "No. of Path" << endl;  
    
    for (unsigned long i=0; i < results.size(); i++)
    {
        for (unsigned long j=0; j < results[i].size(); j++)
            cout << setw(width) << results[i][j];

        cout << "\n";
    }

    cout << "The corresponding analytical Geometric Asian Option price is: ";
    double BS_price = BlackScholesCallGeometricAsian(spot,strike,r,d,vol,expiry,number_of_dates);
    cout << BS_price <<endl;

    cout << "In the continous limit, the Geometric Asian Option price is: ";
    double BS_price_limit = BlackScholesCall(spot*exp(-1./12.*vol*vol*expiry),strike,r,d,vol*sqrt(2./3.),expiry/2.);
    cout << BS_price_limit <<endl;

    }

	return 0;

}
