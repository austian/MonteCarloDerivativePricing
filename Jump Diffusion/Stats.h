#ifndef Stats_h
#define Stats_h
#include <vector>

class Stats	{
public:
	double Expectation(std::vector<double>* Data);

	double Variance(std::vector<double>* Data, double Expectation);
	double StandDev(double Variance);
	double StandError(double StandDev, double NumberOfTrials);
};

#endif