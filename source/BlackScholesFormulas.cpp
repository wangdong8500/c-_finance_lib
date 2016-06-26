//
//
//                        BlackScholesFormulas.cpp
//
//


#include <BlackScholesFormulas.h>
#include <Normals.h>
#include <cmath>

#if !defined(_MSC_VER)
using namespace std;
#endif

#include <iostream>

double BlackScholesCall( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry)
{
    // avoid the log of 0
    if (Vol == 0.) Vol = 1e-6;
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1 - standardDeviation;
    return Spot*exp(-d*Expiry) * CumulativeNormal(d1) - Strike*exp(-r*Expiry)*CumulativeNormal(d2);
}


double BlackScholesPut( double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1 - standardDeviation;
    return Strike*exp(-r*Expiry)*(1.0-CumulativeNormal(d2)) - Spot*exp(-d*Expiry) * (1-CumulativeNormal(d1));
}

double BlackScholesDigitalCall( double Spot,
                                double Strike,
                                double r,
                                double d,
                                double Vol,
                                double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d2 =( moneyness +  (r-d)*Expiry-0.5* standardDeviation*standardDeviation)/standardDeviation;
    return exp(-r*Expiry)*CumulativeNormal(d2);
}

double BlackScholesDigitalPut( double Spot,
                               double Strike,
                               double r,
                               double d,
                               double Vol,
                               double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d2 =( moneyness +  (r-d)*Expiry-0.5* standardDeviation*standardDeviation)/standardDeviation;
    return exp(-r*Expiry)*(1.0-CumulativeNormal(d2));
}


double BlackScholesCallVega( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation; 
    return Spot*exp(-d*Expiry) * sqrt(Expiry)*NormalDensity(d1);


}

// @c Dong Wang, 2016 
double BlackScholesCallGeometricAsian(double spot,
                                      double strike,
                                      double r,
                                      double d,
                                      double vol,
                                      double expiry,
                                      unsigned n
                                      ){
    double m = double(n);
    double new_vol = sqrt((m+1)*(2*m+1)/(6*m*m))*vol;
    double new_spot = spot * exp((r-d-0.5*vol*vol)*expiry*(m+1)/(2*m) - (r-d-0.5*new_vol*new_vol)*expiry);

    return BlackScholesCall(new_spot,strike,r,d,new_vol,expiry);

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

