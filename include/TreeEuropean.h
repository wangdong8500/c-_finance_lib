#ifndef TREE_EUROPEAN_H
#define TREE_EUROPEAN_H

#include <TreeProducts.h>
#include <PayOff.h>

class TreeEuropean: public TreeProduct {
public:
	TreeEuropean(double expiry_, PayOffBridge the_pay_off_):
	TreeProduct(expiry_), the_pay_off(the_pay_off_)
	{}

	virtual double FinalPayOff(double spot) const;
	virtual double PreFinalValue(double, double, double discounted_future_value) const;
	virtual TreeProduct* clone() const;

	virtual ~TreeEuropean(){}

private:
	PayOffBridge the_pay_off;
};

#endif