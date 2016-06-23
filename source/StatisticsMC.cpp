#include <StatisticsMC.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// implementation of StatisticsMean class
StatisticsMC* StatisticsMean::clone() const{
	return new StatisticsMean(*this);
}

void StatisticsMean::DumpOneResult(double x){
	running_sum += x;
	path_done++;
}

vector< vector<double> > StatisticsMean::GetResultsSoFar() const{
	vector< vector<double> > results(1);
	results[0].resize(1);
	results[0][0] = running_sum/path_done;
	return results;
}

// implementation of StatisticsSTE, the standard deviation of sample mean from population mean
StatisticsMC* StatisticsSTE::clone() const{
	return new StatisticsSTE(*this);
}

void StatisticsSTE::DumpOneResult(double x){
	running_sum += x;
	running_squared_sum += x*x;
	path_done++;
}

vector< vector<double> > StatisticsSTE::GetResultsSoFar() const{
	vector< vector<double> > results(1);
	results[0].resize(1);
	results[0][0] = sqrt((running_squared_sum/path_done - running_sum*running_sum/path_done/path_done)/path_done);
	return results;
}

// implementation of StatisticsMoments
StatisticsMC* StatisticsMoments::clone() const{
	return new StatisticsMoments(*this);
}

void StatisticsMoments::DumpOneResult(double x){
	running_sum += pow(x,power_index);
	path_done++;
}

vector< vector<double> > StatisticsMoments::GetResultsSoFar() const{
	vector< vector<double> > results(1);
	results[0].resize(1);
	results[0][0] = running_sum/path_done;
	return results;
}

