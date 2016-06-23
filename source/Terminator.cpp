#include <Terminator.h>
#include <iostream>
using namespace std;

TerminatorBase* TerminatorPath::clone() const{
	return new TerminatorPath(*this);
}

TerminatorBase* TerminatorTime::clone() const{
	return new TerminatorTime(*this);
}

TerminatorBase* TerminatorCombine::clone() const{
	return new TerminatorCombine(*this);
}

