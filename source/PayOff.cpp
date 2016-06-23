#include <PayOff.h>

PayOffBridge::PayOffBridge(const PayOffBridge& original){
	PayOffPtr = original.PayOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff){
	PayOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge(){
	delete PayOffPtr;
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& other){
	if (&other != this){
		delete PayOffPtr;
		PayOffPtr = other.PayOffPtr->clone();
	}
	return (*this);
}

// call option pay off
CallPayOff::CallPayOff(double strike_){
	strike = strike_;
}

double CallPayOff::operator()(double spot) const{
	return spot - strike>0? spot - strike : 0;
}

PayOff* CallPayOff::clone() const{
	return new CallPayOff(*this);
}

// put option payoff
PutPayOff::PutPayOff(double strike_){
	strike = strike_;
}

double PutPayOff::operator() (double spot) const{
	return strike-spot>0? strike-spot : 0.;
}

PayOff* PutPayOff::clone() const{
	return new PutPayOff(*this);
}

// forward payoff

ForwardPayOff::ForwardPayOff(double strike_){
	strike = strike_;
}

double ForwardPayOff::operator() (double spot) const{
	return spot - strike;
}

PayOff* ForwardPayOff::clone() const{
	return new ForwardPayOff(*this);
}




