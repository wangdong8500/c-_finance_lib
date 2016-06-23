#ifndef PATHDEPENDENT_H
#define PATHDEPENDENT_H

#include <Arrays.h>
#include <vector>

class CashFlow{
public:
	unsigned long time_index;
	double amount;
	CashFlow(unsigned long time_index_ = 0UL, double amount_ = 0.0):
	time_index(time_index_), amount(amount_) {}
};


class PathDependent{
public:
	PathDependent(const MJArray& look_at_times);

	const MJArray& GetLookAtTimes() const;

	virtual unsigned long MaxNumberOfCashFlows() const = 0;
	virtual MJArray PossibleCashFlowTimes() const = 0;
	virtual unsigned long CashFlows(const MJArray& spot_values, 
		std::vector<CashFlow>& generated_flows) const = 0;
	virtual PathDependent* clone() const = 0;

	virtual ~PathDependent(){}


private:
	MJArray look_at_times;
};

#endif