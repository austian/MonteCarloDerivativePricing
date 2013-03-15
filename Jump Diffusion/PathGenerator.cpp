//responsible for stock evolution

#include "RandomNumber.h"
#include <cmath>
#include "Parameters.h"
#include "PathGenerator.h"
#include <iostream>
#include <algorithm>
using namespace std;


//PathApproxBrown
double PathApproxBrown::PathGenerator(Path& Path, Parameters& Parameters)	{
	double CurrentIncrement = Parameters.Spot;
	double NextIncrement;
	double Increment = Parameters.Expiry / Parameters.NumberOfSteps;
	for(int i = 0; i < Parameters.NumberOfSteps; i++)	{
		NextIncrement = CurrentIncrement + Parameters.Rate*CurrentIncrement*Increment + CurrentIncrement*Parameters.Vol*sqrt(Increment)*Gaussian();
		CurrentIncrement = NextIncrement;
	}
	return CurrentIncrement;
}

//PathJumpTotal m = .9, nu = .1
double PathJumpTotal::PathGenerator(Path& Path, Parameters& Parameters)	{
	double NumberOfJumps = Poisson(Parameters.Jump, Parameters.Expiry);
	double J = 0;
	double JumpSum = 0;
	for(int i = 1; i < NumberOfJumps + 1; i++)	{
		J = 0.1*Gaussian();
		JumpSum += J;
	}
	double Mu = Parameters.Rate - (-0.1)*Parameters.Jump;
	double CurrentSpot = Parameters.Spot*exp(Mu*Parameters.Expiry - 0.5*Parameters.Vol*Parameters.Vol*Parameters.Expiry + 
		Parameters.Vol*sqrt(Parameters.Expiry)*Gaussian() + NumberOfJumps*log(0.9) - 0.5*(0.1)*(0.1)*NumberOfJumps + JumpSum);
	return max(CurrentSpot, 0.0);	
}
