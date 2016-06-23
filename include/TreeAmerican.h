#ifndef TREE_AMERICAN_H
#define TREE_AMERICAN_H

#include <TreeProducts.h>
#include <PayOff.h>

class TreeAmerican: public TreeProduct {
public:
	TreeAmerican(double expiry_, PayOffBridge the_pay_off_):
	TreeProduct(expiry_), the_pay_off(the_pay_off_)
	{}

	virtual double FinalPayOff(double spot) const;
	virtual double PreFinalValue(double spot, double, double discounted_future_value) const;
	virtual TreeProduct* clone() const;

	virtual ~TreeAmerican(){}

private:
	PayOffBridge the_pay_off;
};

#endif