#ifndef VANILLAOPTION_H
#define VANILLAOPTION_H

#include <PayOff.h>
#include <memory>

class VanillaOption{

public:
	VanillaOption(const PayOff& pay_off_, double expiry_);
	double get_expiry() const;
	double option_pay_off(double spot) const;

private:
	std::unique_ptr<PayOff> pay_off_ptr;
	double expiry;
};

#endif