#ifndef PARAMETER_H
#define PARAMETER_H

class ParameterBase{
public:
	ParameterBase(){};
	virtual ~ParameterBase(){};
	virtual double Integral(double t1, double t2) const = 0;
	virtual double Integral_Squared(double t1, double t2) const = 0;
	virtual ParameterBase* clone() const = 0;

private:

};


class Parameter{
public:
	Parameter(const ParameterBase& parameter);
	Parameter(const Parameter& original);
	~Parameter();
	Parameter& operator= (const Parameter& other);

	inline double Integral(double t1, double t2) const;
	inline double Integral_Squared(double t1, double t2) const;

private:
	ParameterBase* ParaPtr;
};

inline double Parameter::Integral(double t1, double t2) const{
	return ParaPtr->Integral(t1,t2);
}

inline double Parameter::Integral_Squared(double t1, double t2) const {
	return ParaPtr->Integral_Squared(t1,t2);
}

class ParameterConstant: public ParameterBase{
public:
	ParameterConstant(double constant_);
	~ParameterConstant(){};
	virtual double Integral(double t1, double t2) const;
	virtual double Integral_Squared(double t1, double t2) const;
	virtual ParameterBase* clone() const; 

private:
	double constant;
	double constant_squared; 
};



#endif