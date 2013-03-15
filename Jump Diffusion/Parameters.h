#ifndef Parameters_h
#define Parameters_h

class Parameters	{
public:
	Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfPaths, long NumberOfSteps, double Jump);
	double Expiry;
	double Rate;
	double Spot;
	double Vol;
	long NumberOfPaths;
	long NumberOfSteps;
	double Jump;
};

#endif