#ifndef TREE_PRODUCTS_H
#define TREE_PRODUCTS_H

#include <PayOff.h>

class TreeProduct{
public:
	TreeProduct(double expiry_):
	expiry(expiry_)
	{}

	virtual double FinalPayOff(double spot) const = 0;
	virtual double PreFinalValue(double spot, double time, double discounted_future_value) const = 0;

	virtual ~TreeProduct(){}
	virtual TreeProduct* clone() const = 0;

	double GetExpiry() const{
		return expiry;
	}

private:
	double expiry;

};
#endif