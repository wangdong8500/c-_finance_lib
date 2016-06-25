/*
requires
    Arrays.cpp
    BinomialTree.cpp
    BlackScholesFormulas.cpp
    Normals.cpp
    Parameters.cpp
    PayOff.cpp
    TreeAmerican.cpp
    TreeEuropean.cpp
    TreeMain.cpp
  */

#include <BinomialTree.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>
#include <BlackScholesFormulas.h>
#include <PayOff.h>
#include <iostream>
using namespace std;
#include <cmath>
int main()
{

	double expiry;
	double strike; 
	double spot; 
	double vol; 
	double r;
    double d;
	unsigned long steps;

	cout << "\nEnter expiry\n";
	cin >> expiry;

	cout << "\nStrike\n";
	cin >> strike;

	cout << "\nEnter spot\n";
	cin >> spot;

	cout << "\nEnter vol\n";
	cin >> vol;

	cout << "\nr\n";
	cin >> r;

    cout << "\nd\n";
    cin >> d;

    cout << "\nNumber of steps\n";
	cin >> steps;

    CallPayOff the_pay_off(strike);

    ParameterConstant r_param(r);
    ParameterConstant d_param(d);

    TreeEuropean european_option(expiry,the_pay_off);
    TreeAmerican american_option(expiry,the_pay_off);

    SimpleBinomialTree the_tree(spot,r_param,d_param,vol,expiry,steps);
    double euro_price = the_tree.GetThePrice(european_option);
    double american_price = the_tree.GetThePrice(american_option);
    //cout << "euro price " << euro_price << " amer price " << american_price << "\n";
    
    ForwardPayOff forward_pay_off(strike);
    TreeEuropean forward(expiry,forward_pay_off);

    double forward_price = the_tree.GetThePrice(forward);
    //cout << "forward price by tree " << forward_price << "\n";

    steps++; // now redo the trees with one more step
    SimpleBinomialTree the_new_tree(spot,r_param,d_param,vol,expiry,steps);

    double euro_new_price = the_new_tree.GetThePrice(european_option);
    double american_new_price = the_new_tree.GetThePrice(american_option);

    //cout << "euro new price " << euro_new_price << " amer new price " << american_new_price << "\n";

    double forward_new_price = the_new_tree.GetThePrice(forward);

    // cout << "forward price by new tree " << forward_new_price << "\n";

    double average_euro = 0.5*(euro_price + euro_new_price);
    double average_amer = 0.5*(american_price + american_new_price);
    double average_forward = 0.5*(forward_price + forward_new_price);

    cout << "\nPricing using binomial tree:"<<endl;
    cout << "euro option price " << average_euro << " amer option price " << average_amer << "\n";

    double BSPrice = BlackScholesCall(spot,strike,r,d,vol,expiry);
    cout << "BS formula euro option price " << BSPrice << "\n";

    cout << "forward price:" << average_forward << "\n";

    double actual_forward_price = exp(-r*expiry)*(spot*exp((r-d)*expiry)-strike);
    cout << "exact forward price " << actual_forward_price << "\n";

	return 0;
}
