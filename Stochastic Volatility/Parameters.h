#ifndef Parameters_h
#define Parameters_h
#include <vector>

class Parameters	{
public:
	Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfPaths, long NumberOfSteps, double Jump, double VolVol);
	double Expiry;
	double Rate;
	double Spot;
	double Vol;
	long NumberOfPaths;
	long NumberOfSteps;
	double Jump;
	double VolVol;
	double Integral(std::vector<double>* SamplePoints, double LB, double UB);
};

#endif