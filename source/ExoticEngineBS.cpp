#include <ExoticEngine.h>
#include <ExoticEngineBS.h>
#include <Arrays.h>
#include <cmath>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

ExoticEngineBS::ExoticEngineBS(const Parameter& r_,
		const Parameter& d_,
		const Parameter& vol_,
		const Wrapper<PathDependent>& the_product_,
		const Wrapper<RandomBase>& generator_,
		double spot_):
	ExoticEngine(the_product_,r_),
	the_generator(generator_)
{
	MJArray times(the_product_->GetLookAtTimes());
	num_of_times = times.size();

	the_generator->ResetDimensionality(num_of_times);

	log_spot = log(spot_);

	drift.resize(num_of_times);
	standard_deviation.resize(num_of_times);

	double this_variance = vol_.Integral_Squared(0,times[0]);
	drift[0] = r_.Integral(0,times[0]) - d_.Integral(0,times[0])
	-0.5*this_variance;
	standard_deviation[0] = sqrt(this_variance);

	for (unsigned long i=1; i< num_of_times; i++){
		this_variance = vol_.Integral_Squared(times[i-1],times[i]);
		drift[i] = r_.Integral(times[i-1],times[i]) -
		d_.Integral(times[i-1],times[i]) -
		0.5*this_variance;
		standard_deviation[i] = sqrt(this_variance);
	}

	random_variates.resize(num_of_times);
}

void ExoticEngineBS::GetOnePath(MJArray& spot_values){
	the_generator->GetGaussians(random_variates);
	double current_log_spot = log_spot;

	#ifdef DEBUG
	cout << "the spot values are: ";
	#endif

	for(unsigned long i = 0; i< num_of_times; i++){
		current_log_spot += drift[i] + standard_deviation[i]*random_variates[i];
		spot_values[i] = exp(current_log_spot);

		#ifdef DEBUG
		cout << spot_values[i] << ",";
		if (i == num_of_times - 1)
			cout <<endl;
		#endif 

	}
	return;
}


