#include <PathDependentAsian.h>
#include <Arrays.h>
#include <cmath>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

double PathDependentGeometricAsian::geometric_average(const MJArray& spot_values) const{
	double product = 1.0;
	for(int i=0; i< number_of_times; i++){
		product *= spot_values[i]; 
	}
	return pow(product,double(1.)/number_of_times);
}

unsigned long PathDependentGeometricAsian::MaxNumberOfCashFlows() const{
	return 1UL;
}

MJArray PathDependentGeometricAsian::PossibleCashFlowTimes() const{
	MJArray times(1);
	times[0] = delivery_time;
	return times;
}

unsigned long PathDependentGeometricAsian::CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const{
	double mean = geometric_average(spot_values);
	#ifdef DEBUG
	cout << "PathDepedentAsian.cpp: The mean of spot prices for one realization: " << mean << endl;
	#endif 
	generated_flows[0].amount = (*pay_off_ptr)(mean);
	generated_flows[0].time_index = 0UL;
	#ifdef DEBUG
	cout << "PathDependentAsian.cpp: generated_flows.amount =" << generated_flows[0].amount << endl;
	#endif
	return 1UL;
}

PathDependent* PathDependentGeometricAsian::clone() const{
	return new PathDependentGeometricAsian(*this);
}



