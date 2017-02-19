#include <PayOff.h>

// call option pay off
CallPayOff::CallPayOff(double strike_){
	strike = strike_;
}

double CallPayOff::operator()(double spot) const{
	return spot - strike>0? spot - strike : 0;
}

std::unique_ptr<PayOff> CallPayOff::clone() const{
	return std::unique_ptr<PayOff> ( new CallPayOff(*this) );
}

// put option payoff
PutPayOff::PutPayOff(double strike_){
	strike = strike_;
}

double PutPayOff::operator() (double spot) const{
	return strike-spot>0? strike-spot : 0.;
}

std::unique_ptr<PayOff> PutPayOff::clone() const{
	return std::unique_ptr<PayOff> ( new PutPayOff(*this) );;
}

// forward payoff

ForwardPayOff::ForwardPayOff(double strike_){
	strike = strike_;
}

double ForwardPayOff::operator() (double spot) const{
	return spot - strike;
}

std::unique_ptr<PayOff> ForwardPayOff::clone() const{
	return std::unique_ptr<PayOff> ( new ForwardPayOff(*this) );
}




