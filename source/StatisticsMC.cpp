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

void StatisticsMean::ResetGatherer(){
	running_sum = 0.0;
	path_done = 0UL;
}

// implementation of StatisticsSTE, the standard deviation of sample mean from population mean
StatisticsMC* StatisticsMeanSTE::clone() const{
	return new StatisticsMeanSTE(*this);
}

void StatisticsMeanSTE::DumpOneResult(double x){
	running_sum += x;
	running_squared_sum += x*x;
	path_done++;
}

vector< vector<double> > StatisticsMeanSTE::GetResultsSoFar() const{
	vector< vector<double> > results(2);
	results[0].resize(1);
	results[0][0] = running_sum/path_done;
	results[1].resize(1);
	results[1][0] = sqrt((running_squared_sum/path_done - running_sum*running_sum/path_done/path_done)/path_done);
	return results;
}

void StatisticsMeanSTE::ResetGatherer(){
	running_sum = 0.0;
	running_squared_sum = 0.0;
	path_done = 0UL;
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

void StatisticsMoments::ResetGatherer(){
	running_sum = 0.0;
	path_done = 0UL;
}
