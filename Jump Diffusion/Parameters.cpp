#include "Parameters.h"

Parameters::Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfPaths, long NumberOfSteps, double Jump)	:	
Expiry(Expiry), Rate(Rate), Spot(Spot), Vol(Vol), NumberOfPaths(NumberOfPaths), NumberOfSteps(NumberOfSteps), Jump(Jump) 	{}