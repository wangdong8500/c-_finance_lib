#include <PathDependentBarrier.h>
#include <Arrays.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

unsigned long UpAndOutBarrier::MaxNumberOfCashFlows() const{
	return 1UL;
}

MJArray UpAndOutBarrier::PossibleCashFlowTimes() const{
	MJArray times(1);
	times[0] = delivery_time;
	return times;
}

unsigned long UpAndOutBarrier::CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const{
	double max_spot_value = spot_values.max();
	#ifdef DEBUG
	cout << "PathDepedentBarrier.cpp: The max of spot prices for one realization: " << max_spot_value << endl;
	#endif 
	if (max_spot_value <= barrier){ 
		generated_flows[0].amount = pay_off_ptr->operator()(spot_values[number_of_times-1]);
		generated_flows[0].time_index = 0UL;
	}
	else{
		generated_flows[0].amount = 0.;
		generated_flows[0].time_index = 0UL;
	}
	#ifdef DEBUG
	cout << "PathDependentBarrier.cpp: generated_flows.amount =" << generated_flows[0].amount << endl;
	#endif
	return 1UL;
}

PathDependent* UpAndOutBarrier::clone() const{
	return new UpAndOutBarrier(*this);
}


unsigned long UpAndInBarrier::MaxNumberOfCashFlows() const{
	return 1UL;
}

MJArray UpAndInBarrier::PossibleCashFlowTimes() const{
	MJArray times(1);
	times[0] = delivery_time;
	return times;
}

unsigned long UpAndInBarrier::CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const{
	double max_spot_value = spot_values.max();
	#ifdef DEBUG
	cout << "PathDepedentBarrier.cpp: The max of spot prices for one realization: " << max_spot_value << endl;
	#endif 
	if (max_spot_value > barrier){ 
		generated_flows[0].amount = pay_off_ptr->operator()(spot_values[number_of_times-1]);
		generated_flows[0].time_index = 0UL;
	}
	else{
		generated_flows[0].amount = 0.;
		generated_flows[0].time_index = 0UL;
	}
	#ifdef DEBUG
	cout << "PathDependentBarrier.cpp: generated_flows.amount =" << generated_flows[0].amount << endl;
	#endif
	return 1UL;
}

PathDependent* UpAndInBarrier::clone() const{
	return new UpAndInBarrier(*this);
}
