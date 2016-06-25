/*
Statistics Gathering Class
@c Dong Wang, 2016 
*/

#ifndef STATISTICSMC_H
#define STATISTICSMC_H

#include <vector>

// base class for gathering statistics
class StatisticsMC{
public:
	StatisticsMC(){};
	virtual ~StatisticsMC(){};
	virtual StatisticsMC* clone() const = 0;
	// some interface
	virtual void DumpOneResult(double x) = 0;
	virtual std::vector< std::vector<double> > GetResultsSoFar() const = 0; 
	virtual void ResetGatherer() =0;
private:

};

class StatisticsMean: public StatisticsMC{
public:
	StatisticsMean():running_sum(0.0), path_done(0UL) {};
	virtual ~StatisticsMean(){};
	virtual StatisticsMC* clone() const;
	// interface
	virtual void DumpOneResult(double x);
	virtual std::vector< std::vector<double> > GetResultsSoFar() const;
	virtual void ResetGatherer();
private:
	double running_sum;
	unsigned long path_done;
};

class StatisticsMeanSTE: public StatisticsMC{
public:
	StatisticsMeanSTE():running_sum(0.0), running_squared_sum(0.0), path_done(0UL) {};
	virtual ~StatisticsMeanSTE(){};
	virtual StatisticsMC* clone() const;
	// interface
	virtual void DumpOneResult(double x);
	virtual std::vector< std::vector<double> > GetResultsSoFar() const;
	virtual void ResetGatherer();
private:
	double running_sum;
	double running_squared_sum;
	unsigned long path_done;
};

class StatisticsMoments: public StatisticsMC{
public:
	StatisticsMoments(unsigned short power_index_): 
	power_index(power_index_),running_sum(0UL),path_done(0UL){}
	// interface
	virtual StatisticsMC* clone() const;
	virtual void DumpOneResult(double x);
	virtual std::vector< std::vector<double> > GetResultsSoFar() const; 
	virtual void ResetGatherer();
private:
	const unsigned short power_index;
	double running_sum;
	unsigned long path_done;
};
#endif