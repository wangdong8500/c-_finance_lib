#include <cmath>
#include <SimpleMC.h>
#include <Arrays.h>

void SimpleMC(double spot, const Parameter& r, const Parameter& d, const Parameter& vol, const VanillaOption& vanilla_option, 
	TerminatorBase& loop_terminator, RandomBase& generator, StatisticsMC& gatherer){

	double expiry = vanilla_option.get_expiry();
	double variance = vol.Integral_Squared(0,expiry);
	double root_variance = sqrt(variance);
	double moved_spot = spot*exp(r.Integral(0,expiry)-d.Integral(0,expiry)-0.5*variance);
	double discount = exp(-r.Integral(0,expiry));

	MJArray gaussian_variate(1);

	while(true){
		generator.GetGaussians(gaussian_variate);
		double this_spot = moved_spot*exp(root_variance*gaussian_variate[0]);
		double payoff = vanilla_option.option_pay_off(this_spot);
		gatherer.DumpOneResult(payoff*discount);
		if (loop_terminator.terminate()) break;		
	}

	return;
}