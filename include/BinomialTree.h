#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

#include <Parameter.h>
#include <vector>
#include <TreeProducts.h>
#include <utility>
#include <Arrays.h>

class SimpleBinomialTree{
public:
	SimpleBinomialTree(double spot_, const Parameter& r_, const Parameter& d_, 
		double vol_, double time_to_expiry_, unsigned long steps_):
	spot(spot_),r(r_),d(d_),vol(vol_), time_to_expiry(time_to_expiry_),
	steps(steps_),tree_built(false),discounts(steps)
	{}

	double GetThePrice(const TreeProduct& the_product);

protected:
	void BuildTree();

private:
	double spot;
	Parameter r;
	Parameter d;
	double vol;
	double time_to_expiry;
	unsigned long steps;
	bool tree_built;

	std::vector< std::vector< std::pair<double,double> > > the_tree;
	MJArray discounts;
};

#endif