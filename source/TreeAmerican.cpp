#include <algorithm>
#include <TreeAmerican.h> 

double TreeAmerican::FinalPayOff(double spot) const{
	return the_pay_off(spot);
}

double TreeAmerican::PreFinalValue(double spot, double, double discounted_future_value) const{
	return std::max(the_pay_off(spot),discounted_future_value);
}

TreeProduct* TreeAmerican::clone() const{
	return new TreeAmerican(*this);
}



