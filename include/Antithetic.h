#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include <Random2.h>
#include <wrapper.h>
#include <Arrays.h>

class Antithetic: public RandomBase{
public:
	Antithetic(const Wrapper<RandomBase>& inner_generator_):
	inner_generator(inner_generator_), 
	RandomBase(*inner_generator_){
		inner_generator->Reset();
		odd_path = true;
		next_path.resize(GetDimensionality());
	}
	//interface
	virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();

    virtual void ResetDimensionality(unsigned long NewDimensionality);
private:
	Wrapper<RandomBase> inner_generator;
	bool odd_path;
	MJArray next_path;
};
#endif