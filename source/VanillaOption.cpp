#include <VanillaOption.h>

VanillaOption::VanillaOption(const PayOff& pay_off_, double expiry_):
expiry(expiry_){
	pay_off_ptr = pay_off_.clone();
}

double VanillaOption::get_expiry() const{
	return expiry;
}

double VanillaOption::option_pay_off(double spot) const{
	return (*pay_off_ptr)(spot);
}