#include <TreeEuropean.h>

double TreeEuropean::FinalPayOff(double spot) const{
	return the_pay_off(spot);
}

double TreeEuropean::PreFinalValue(double, double, double discounted_future_value) const{
	return discounted_future_value;
}

TreeProduct* TreeEuropean::clone() const{
	return new TreeEuropean(*this);
}



