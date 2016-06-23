#include <BinomialTree.h>
#include <cmath>

void SimpleBinomialTree::BuildTree(){
	if (tree_built == true) return;
	the_tree.resize(steps+1);
	double initial_log_spot = log(spot);

	for (unsigned long i = 0; i <= steps; i++){
		double this_time = i*time_to_expiry/steps;
		double moved_log_spot = initial_log_spot + r.Integral(0,this_time)
		-d.Integral(0,this_time) -0.5*vol*vol*this_time;
		double sd = vol*sqrt(time_to_expiry/steps);

		the_tree[i].resize(i+1);
		for (long j=-static_cast<long>(i), k=0; 
			j<=static_cast<long>(i); j = j + 2, k++)
			{
			the_tree[i][k].first = exp(moved_log_spot + sd*j);
		}

		for(unsigned long j=0; j < steps; j++){
			discounts[j] = exp(-r.Integral(j*time_to_expiry/steps,(j+1)*time_to_expiry/steps));
		}
		tree_built = true;
	}
}


double SimpleBinomialTree::GetThePrice(const TreeProduct& the_product){
	if (!tree_built) BuildTree();

	if (the_product.GetExpiry() != time_to_expiry)
		throw("mismatched product in SimpleBinomialTree!");

	for (unsigned long j=0; j<=steps; j++){
		double this_spot = the_tree[steps][j].first;
		the_tree[steps][j].second = the_product.FinalPayOff(this_spot);
	}

	for (unsigned long i=1; i <= steps; i++){
		unsigned long index = steps - i;
		double this_time = index*time_to_expiry/steps;
		for (unsigned long j=0; j <= index; j++){
			double this_spot = the_tree[index][j].first;
			double future_discount_value = (0.5*the_tree[index+1][j].second +
				0.5*the_tree[index+1][j+1].second)*discounts[index];
			the_tree[index][j].second = the_product.PreFinalValue(this_spot,this_time,future_discount_value);
		}
	}

	return the_tree[0][0].second;


}