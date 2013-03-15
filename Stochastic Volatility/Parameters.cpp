#include "Parameters.h"
#include <vector>

using namespace std;

Parameters::Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfPaths, long NumberOfSteps, double Jump, double VolVol)	:	
Expiry(Expiry), Rate(Rate), Spot(Spot), Vol(Vol), NumberOfPaths(NumberOfPaths), NumberOfSteps(NumberOfSteps), Jump(Jump), VolVol(VolVol) 	{}

double Parameters::Integral(vector<double>* SamplePoints, double LB, double UB)	{
	double Increment = (UB - LB) / (*SamplePoints).size();
	double RunningSum = 0;
	for(int i = 0; i < (*SamplePoints).size(); i++)	{
		RunningSum += (*SamplePoints)[i];
	}
	return RunningSum*Increment;
}
