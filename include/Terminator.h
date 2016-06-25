#ifndef TERMINATOR_H
#define TERMINATOR_H

#include <ctime>
#include <iostream>
#include <wrapper.h>

class TerminatorBase{
public:
	TerminatorBase(){}
	virtual ~TerminatorBase(){};
	// interface
	virtual TerminatorBase* clone() const = 0;
	virtual bool terminate() = 0; 
	virtual void reset() = 0;
private:

};

// use the number of path for terminating loop
class TerminatorPath: public TerminatorBase{
public:
	TerminatorPath(unsigned long max_path_): 
	max_path(max_path_), path_done(0UL) {}

	virtual TerminatorBase* clone() const;

	virtual bool terminate(){
		++path_done;
		if (path_done == max_path) return true;
		else return false; 
	} 

	virtual void reset(){
		path_done = 0UL;
	}

private:
	unsigned long path_done;
	const unsigned long max_path;
};

// use time to decide whether to terminate the loop
// better not to call in each loop. could be slow. 
class TerminatorTime: public TerminatorBase{
public:
	TerminatorTime(double max_time_)
	:max_time(max_time_){
		start_time = std::time(NULL);
	}

	virtual TerminatorBase* clone() const;

	virtual bool terminate(){
		 if (std::difftime(std::time(NULL),start_time) > max_time){
		 	std::cout << "loop terminated becasue of time limit, excedding " << max_time << "s" <<std::endl;
		 	return true;
		 }
		 else
		 	return false;
	}

	virtual void reset(){
		start_time = std::time(NULL);
	}
private:
	std::time_t start_time;
	const double max_time; 
};

// comnine two terminators together to mimic the or operation
// either one directing termination leads to termination
class TerminatorCombine: public TerminatorBase{
public:
	TerminatorCombine(const Wrapper<TerminatorBase>& t1, const Wrapper<TerminatorBase>& t2):
	terminator_1(t1), terminator_2(t2){}

	virtual TerminatorBase* clone() const;

	virtual bool terminate(){
		if (terminator_1->terminate() or terminator_2->terminate()) return true;
		else return false;
	}

	virtual void reset(){
		terminator_1->reset();
		terminator_2->reset();
	}

private:
	Wrapper<TerminatorBase> terminator_1;
	Wrapper<TerminatorBase> terminator_2;
};

#endif
