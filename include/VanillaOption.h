#ifndef VANILLAOPTION_H
#define VANILLAOPTION_H

#include <PayOff.h>

class VanillaOption{

public:
	VanillaOption(const PayOffBridge& pay_off_, double expiry_);
	double get_expiry() const;
	double option_pay_off(double spot) const;

private:
	PayOffBridge pay_off;
	double expiry;
};

#endif