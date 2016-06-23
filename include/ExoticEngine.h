#ifndef EXOTICENGINE_H
#define EXOTICENGINE_H

#include <wrapper.h>
#include <Parameter.h>
#include <PathDependent.h>
#include <StatisticsMC.h>
#include <vector>
#include <Terminator.h>

class ExoticEngine
{
public:

    ExoticEngine(const Wrapper<PathDependent>& the_product_,
                 const Parameter& r_);

    virtual void GetOnePath(MJArray& spot_values)=0;

    void DoSimulation(StatisticsMC& the_gatherer, const TerminatorBase& terminator_);

    virtual ~ExoticEngine(){}

    double DoOnePath(const MJArray& spot_values) const;

private:

    Wrapper<PathDependent> the_product;
    Parameter r;
    MJArray discounts;
    mutable std::vector<CashFlow> these_cash_flows;
};

#endif

