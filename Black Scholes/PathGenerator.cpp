//responsible for stock evolution

#include "Random Number.h"
#include <cmath>
#include "Parameters.h"
#include "PathGenerator.h"


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

//PathSDETotal
double PathSDETotal::PathGenerator(Path& Path, Parameters& Parameters)	{
	double CurrentSpot = Parameters.Spot*exp(Parameters.Rate * Parameters.Expiry - 
		0.5*Parameters.Vol*Parameters.Vol*Parameters.Expiry + 
		Parameters.Vol*sqrt(Parameters.Expiry)*Gaussian());
	return CurrentSpot;
}

//PathSDEIncrement
double PathSDEIncrement::PathGenerator(Path& Path, Parameters& Parameters)	{
	double CurrentIncrement = Parameters.Spot;
	double NextIncrement;
	double Increment = Parameters.Expiry / Parameters.NumberOfSteps;
	for(int i = 0; i < Parameters.NumberOfSteps; i++)	{
		NextIncrement = CurrentIncrement*exp(Parameters.Rate * Increment - 
		0.5*Parameters.Vol*Parameters.Vol*Increment + 
		Parameters.Vol*sqrt(Increment)*Gaussian());
		CurrentIncrement = NextIncrement;
	}
	return CurrentIncrement;
}
	