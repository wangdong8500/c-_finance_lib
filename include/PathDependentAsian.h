#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H

#include <PathDependent.h>
#include <Arrays.h>
#include <wrapper.h>
#include <PayOff.h>

class PathDependentAsian: public PathDependent{
public:
	PathDependentAsian(const MJArray& look_at_times_, 
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

class PathDependentGeometricAsian: public PathDependent{
public:
	PathDependentGeometricAsian(const MJArray& look_at_times_, 
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
protected:
	double geometric_average(const MJArray& spot_values) const;
};

#endif