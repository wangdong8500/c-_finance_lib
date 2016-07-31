#ifndef PATH_DEPENDENT_LOOKBACK_H
#define PATH_DEPENDENT_LOOKBACK_H

#include <PathDependent.h>
#include <Arrays.h>
#include <wrapper.h>
#include <PayOff.h>

class FixedKLookback: public PathDependent{
public:
	FixedKLookback(const MJArray& look_at_times_, 
		double& delivery_time_, 
		const Wrapper<PayOff>& pay_off_ptr_):
	PathDependent(look_at_times_), 
	delivery_time(delivery_time_),
	pay_off_ptr(pay_off_ptr_),
	number_of_times(look_at_times_.size())
	{}

	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const;
	virtual PathDependent* clone() const;
private:
	double delivery_time;
	Wrapper<PayOff> pay_off_ptr;
	unsigned long number_of_times;

};

#endif