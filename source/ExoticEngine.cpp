#include <ExoticEngine.h>
#include <cmath>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& the_product_,
	const Parameter& r_):
the_product(the_product_),
r(r_), 
discounts(the_product_->PossibleCashFlowTimes()){
	
	for (unsigned long i = 0; i < discounts.size();i++){
		discounts[i] = exp(-r.Integral(0.,discounts[i]));
	}
	these_cash_flows.resize(the_product->MaxNumberOfCashFlows());

}

void ExoticEngine::DoSimulation(StatisticsMC& the_gatherer, const TerminatorBase& terminator_){
	Wrapper<TerminatorBase> terminator(terminator_);
	MJArray spot_values(the_product->GetLookAtTimes().size());
	double this_value;
	while(true){
		GetOnePath(spot_values);
		this_value = DoOnePath(spot_values);
		the_gatherer.DumpOneResult(this_value);
		#ifdef DEBUG
		cout << "ExoticEngine.cpp: The discounted cashflows for one realization: " << this_value << endl;
		#endif
		if(terminator->terminate()) break;
	}

	return;
}

double ExoticEngine::DoOnePath(const MJArray& spot_values) const{
	unsigned long number_of_flows = the_product->CashFlows(spot_values,these_cash_flows);
	double value = 0.;
	for (unsigned long i=0; i< number_of_flows; i++){
		value += these_cash_flows[i].amount*
		discounts[these_cash_flows[i].time_index];
	}
	return value;
}



