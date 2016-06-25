#ifndef CONVERGENCETABLE_H
#define CONVERGENCETABLE_H
#include <StatisticsMC.h>
#include <wrapper.h>

class ConvergenceTable: public StatisticsMC{
public:
	ConvergenceTable(const Wrapper<StatisticsMC>& inner_):
	inner(inner_),stopping_point(2UL),path_done(0UL){}
	// common interface
	virtual StatisticsMC* clone() const;
	virtual void DumpOneResult(double x);
	virtual std::vector< std::vector<double> > GetResultsSoFar() const;
	virtual void ResetGatherer();
private:
	Wrapper<StatisticsMC> inner;
	std::vector< std::vector<double> > table;
	unsigned long stopping_point;
	unsigned long path_done;
};

#endif