#ifndef SIMPLEMC_H
#define SIMPLEMC_H

#include <VanillaOption.h>
#include <Parameter.h>
#include <StatisticsMC.h>
#include <Terminator.h>
#include <Random2.h>

void SimpleMC(double spot, const Parameter& r, const Parameter& d, const Parameter& vol, const VanillaOption& vanilla_option, 
	TerminatorBase& loop_terminator, RandomBase& generator, StatisticsMC& gatherer);

#endif