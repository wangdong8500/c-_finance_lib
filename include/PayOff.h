#ifndef PAYOFF_H
#define PAYOFF_H

// PayOff base class
class PayOff{
public:
	PayOff(){};

	virtual ~PayOff(){}

	virtual double operator()(double spot) const = 0;

	virtual PayOff* clone() const = 0;

private:

};

// handle the memory management when cloning a PayOff object
class PayOffBridge{
public:
	PayOffBridge(const PayOffBridge& original);
	PayOffBridge(const PayOff& innerPayOff);
	~PayOffBridge();
	PayOffBridge& operator= (const PayOffBridge& other);
	inline double operator() (double spot) const;
private:
	PayOff* PayOffPtr;
};

inline double PayOffBridge::operator() (double spot) const{
	return PayOffPtr -> operator() (spot);
}

/************************************************************/

// call option pay off
class CallPayOff: public PayOff{
public:
	CallPayOff(double strike_);

	virtual double operator()(double spot) const;

	virtual PayOff* clone() const;

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
	virtual PayOff* clone() const;
private:
	double strike;
};

//forward pay off
class ForwardPayOff: public PayOff{
public:
	ForwardPayOff(double strike_);
	virtual ~ForwardPayOff(){};
	virtual double operator() (double spot) const;
	virtual PayOff* clone() const;
private:
	double strike;

};

#endif

