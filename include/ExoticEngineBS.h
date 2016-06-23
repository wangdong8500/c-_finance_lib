#ifndef EXOTIC_ENGINE_BS_H
#define EXOTIC_ENGINE_BS_H

#include <Parameter.h>
#include <wrapper.h>
#include <Random2.h>
#include <ExoticEngine.h>

class ExoticEngineBS: public ExoticEngine{
public:
	ExoticEngineBS(const Parameter& r_,
		const Parameter& d_,
		const Parameter& vol_,
		const Wrapper<PathDependent>& the_product_,
		const Wrapper<RandomBase>& generator_,
		double spot_);
	virtual void GetOnePath(MJArray& spot_values);

private:
	MJArray drift;
	MJArray standard_deviation;
	double log_spot;
	unsigned long num_of_times;
	MJArray random_variates;
	Wrapper<RandomBase> the_generator;
};

#endif