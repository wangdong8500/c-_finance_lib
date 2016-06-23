//
//
//                      TreeMain.cpp
//
//
//      
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
    TreeProducts.cpp
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
    cout << "euro price " << euro_price << " amer price " << american_price << "\n";

    double BSPrice = BlackScholesCall(spot,strike,r,d,vol,expiry);
    cout << "BS formula euro price " << BSPrice << "\n";
    
    ForwardPayOff forward_pay_off(strike);
    TreeEuropean forward(expiry,forward_pay_off);

    double forward_price = the_tree.GetThePrice(forward);
    cout << "forward price by tree " << forward_price << "\n";

    double actual_forward_price = exp(-r*expiry)*(spot*exp((r-d)*expiry)-strike);
    cout << "forward price " << actual_forward_price << "\n";

    steps++; // now redo the trees with one more step
    SimpleBinomialTree the_new_tree(spot,r_param,d_param,vol,expiry,steps);

    double euro_new_price = the_new_tree.GetThePrice(european_option);
    double american_new_price = the_new_tree.GetThePrice(american_option);

    cout << "euro new price " << euro_new_price << " amer new price " << american_new_price << "\n";

    double forward_new_price = the_new_tree.GetThePrice(forward);

    cout << "forward price by new tree " << forward_new_price << "\n";

    double average_euro = 0.5*(euro_price + euro_new_price);
    double average_amer = 0.5*(american_price + american_new_price);
    double average_forward = 0.5*(forward_price + forward_new_price);

    cout << "euro av price " << average_euro << " amer av price " << average_amer << "\n";
    cout << "av forward " << average_forward << "\n";

    double tmp;
    cin >> tmp;

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

