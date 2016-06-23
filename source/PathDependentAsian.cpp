#include <PathDependentAsian.h>
#include <Arrays.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

unsigned long PathDependentAsian::MaxNumberOfCashFlows() const{
	return 1UL;
}

MJArray PathDependentAsian::PossibleCashFlowTimes() const{
	MJArray times(1);
	times[0] = delivery_time;
	return times;
}

unsigned long PathDependentAsian::CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const{
	double mean = spot_values.sum()/number_of_times;
	#ifdef DEBUG
	cout << "PathDepedentAsian.cpp: The mean of spot prices for one realization: " << mean << endl;
	#endif 
	generated_flows[0].amount = pay_off_ptr->operator()(mean);
	generated_flows[0].time_index = 0UL;
	#ifdef DEBUG
	cout << "PathDependentAsian.cpp: generated_flows.amount =" << generated_flows[0].amount << endl;
	#endif
	return 1UL;
}

PathDependent* PathDependentAsian::clone() const{
	return new PathDependentAsian(*this);
}



