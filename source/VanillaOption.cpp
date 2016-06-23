#include <VanillaOption.h>

VanillaOption::VanillaOption(const PayOffBridge& pay_off_, double expiry_):
pay_off(pay_off_), expiry(expiry_){}

double VanillaOption::get_expiry() const{
	return expiry;
}

double VanillaOption::option_pay_off(double spot) const{
	return pay_off(spot);
}