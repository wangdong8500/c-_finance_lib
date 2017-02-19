#ifndef PAYOFF_H
#define PAYOFF_H

#include <memory>

// PayOff base class
class PayOff{
public:
	PayOff(){};

	virtual ~PayOff(){}

	virtual double operator()(double spot) const = 0;

	virtual std::unique_ptr<PayOff> clone() const = 0;

private:

};

/************************************************************/

// call option pay off
class CallPayOff: public PayOff{
public:
	CallPayOff(double strike_);

	virtual double operator()(double spot) const;

	virtual std::unique_ptr<PayOff> clone() const;

	virtual ~CallPayOff(){};

private:
	double strike;
};

// put option pay off
class PutPayOff: public PayOff{
public:
	PutPayOff(double strike_);
	virtual ~PutPayOff(){};
	virtual double operator() (double spot) const;
	virtual std::unique_ptr<PayOff> clone() const;
private:
	double strike;
};

//forward pay off
class ForwardPayOff: public PayOff{
public:
	ForwardPayOff(double strike_);
	virtual ~ForwardPayOff(){};
	virtual double operator() (double spot) const;
	virtual std::unique_ptr<PayOff> clone() const;
private:
	double strike;

};

#endif

