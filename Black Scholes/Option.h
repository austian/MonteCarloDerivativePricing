#ifndef Option_h
#define Option_h
#include <vector>
#include "PathGenerator.h"
#include "Parameters.h"
#include "Stats.h"

class Option	{
public:
	virtual double Payoff(Option& Option, Parameters& Parameters, Path& Path) = 0;
};

class CallOption	: public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	void Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	CallOption(double Strike);
private:
	double Strike;
};

class PutOption	:	public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	void Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	PutOption(double Strike);
private:
	double Strike;
};

class AsianCallOption	:	public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	void Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	AsianCallOption(double Strike, std::vector<double>* Times);
private:
	double Strike;
	std::vector<double>* Times;
};

class DnOCallOption	:	public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	void Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	DnOCallOption(double Strike, double Barrier, std::vector<double>* Times);
private:
	double Strike;
	double Barrier;
	std::vector<double>* Times;
};

class DnICallOption	:	public Option	{
public:
	double Payoff(Option& Option, Parameters& Parameters, Path& Path);
	void Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters);
	DnICallOption(double Strike, double Barrier, std::vector<double>* Times);
private:
	double Strike;
	double Barrier;
	std::vector<double>* Times;
};
#endif