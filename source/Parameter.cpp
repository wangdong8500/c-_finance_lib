#include <Parameter.h>


// Parameter class wrapper
Parameter::Parameter(const ParameterBase& parameter){
	ParaPtr = parameter.clone();
}

Parameter::Parameter(const Parameter& original){
	ParaPtr = original.ParaPtr->clone();
}

Parameter::~Parameter(){
	delete ParaPtr;
}

Parameter& Parameter::operator= (const Parameter& other){
	if (&other != this){
		delete ParaPtr;
		ParaPtr = other.ParaPtr->clone();
	}
	return (*this);
}


// constant parameter class
ParameterConstant::ParameterConstant(double constant_):
constant(constant_), constant_squared(constant_*constant_) 
{}

double ParameterConstant::Integral(double t1, double t2) const {
	return constant*(t2-t1);
}

double ParameterConstant::Integral_Squared(double t1, double t2) const {
	return constant_squared*(t2- t1);
}

ParameterBase* ParameterConstant::clone() const{
	return new ParameterConstant(*this);
}



