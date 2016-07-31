#include <PathDependentLookback.h>
#include <Arrays.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

unsigned long FixedKLookback::MaxNumberOfCashFlows() const{
	return 1UL;
}

MJArray FixedKLookback::PossibleCashFlowTimes() const{
	MJArray times(1);
	times[0] = delivery_time;
	return times;
}

unsigned long FixedKLookback::CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const{
	double max_spot_value = spot_values.max();
	#ifdef DEBUG
	cout << "PathDepedentLookback.cpp: The max of spot prices for one realization: " << max_spot_value << endl;
	#endif 
	generated_flows[0].amount = pay_off_ptr->operator()(max_spot_value);
	generated_flows[0].time_index = 0UL;
	#ifdef DEBUG
	cout << "PathDependentLookback.cpp: generated_flows.amount =" << generated_flows[0].amount << endl;
	#endif
	return 1UL;
}

PathDependent* FixedKLookback::clone() const{
	return new FixedKLookback(*this);
}



