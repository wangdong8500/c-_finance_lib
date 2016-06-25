/*
require
    BlackScholesFormulas.cpp
    BSCallClass.cpp
    BSCallTwo.cpp
    Normals.cpp
*/

#include <Bisection.h>
#include <NewtonRaphson.H>
#include <cmath>
#include <iostream>
#include <BSCallClass.h>
#include <BSCallTwo.h>
#include <BlackScholesFormulas.h>

using namespace std;

int main()
{
  	double Expiry;
	double Strike; 
	double Spot; 
	double r;
    double d;
    double Price;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter price\n";
	cin >> Price;

	cout << "\nr\n";
	cin >> r;

    cout << "\nd\n";
    cin >> d;
    
    /*************************************************************************************/
    {
    cout << "\nCalculating implied volatility using bisection solver:\n";

    double low,high;

    cout << "\nlower guess\n";
    cin >> low;

    cout << "\nhigh guess\n";
    cin >> high;

    double tolerance;

    cout << "\nTolerance\n";
    cin >> tolerance;

    BSCall theCall(r,d,Expiry,Spot,Strike);

    double vol=Bisection(Price,theCall,low,high,tolerance);
    double PriceTwo = BlackScholesCall(Spot,Strike,r,d,vol,Expiry);

    cout << "\nThe implied volatility is " << vol << endl;
    cout << "The option price using implied volatility: "<< PriceTwo << "\n";
    }
    /*************************************************************************************/
    {
    cout << "\nCalculating implied volatility using NewtonRaphson Method:\n";
    
    double start;

    cout << "\nstart guess choosen as 0.5\n";
    //cin >> start;
    start = 0.5;
    
    double tolerance;

    cout << "\nTolerance\n";
    cin >> tolerance;
    

    BSCallTwo theCall(r,d,Expiry,Spot,Strike);

    double vol=NewtonRaphson<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price,theCall,
                                                                           start,
                                                                           tolerance
                                                                           );

    double PriceTwo = BlackScholesCall(Spot,Strike,r,d,vol,Expiry);

    cout << "\nThe implied volatility is " << vol << endl;
    cout << "The option price using implied volatility: "<< PriceTwo << "\n";
    }
	return 0;
}