#include "Option.h"
#include "Parameters.h"
#include <iostream>

using namespace std;

const double pi = 3.14159265358979325;

double BSImpliedVol(Parameters& _Parameters, double Strike, long DegOfAcc)	{
	CallOption* CClone = new CallOption(Strike);
	double Price = (*CClone).JDPrice(10, _Parameters, (*CClone));
	Parameters* PClone = new Parameters(_Parameters.Expiry, _Parameters.Rate, _Parameters.Spot, _Parameters.Vol, _Parameters.NumberOfPaths, _Parameters.NumberOfSteps, _Parameters.Jump);
	Parameters& PCloneRef = *PClone;
	double Root = 0.2;
	PCloneRef.Vol = 0.2;
	for(int i = 0; i < DegOfAcc; i++)	{		
		double CurrentVega = (*CClone).Vega(PCloneRef, (*CClone));
		Root = Root - (((*CClone).BSPrice(PCloneRef, (*CClone)) - Price)/(CurrentVega));
		PCloneRef.Vol = Root;
	}
	delete PClone;
	delete CClone;
	return Root;
}