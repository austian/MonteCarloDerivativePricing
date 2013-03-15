#ifndef Option_h
#define Option_h
#include <vector>
#include "PathGenerator.h"
#include "Parameters.h"
#include "Stats.h"

class Option	{
public:
	virtual double Payoff(Option& Option, Parameters& Parameters, Path& Path) = 0;
	virtual double BSPrice(Parameters& Parameters, Option& Option) = 0;
	virtual double Vega(Parameters& Parameters, Option& Option) = 0;
	double Strike;
};

class CallOption	: public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	double MontePrice(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	double BSPrice(Parameters& Parameters, Option& Option);
	double JDPrice(long DegOfAcc, Parameters& Parameters, Option& Option);
	double Vega(Parameters& Parameters, Option& Option);
	CallOption(double Strike);
	double Strike;
};

#endif