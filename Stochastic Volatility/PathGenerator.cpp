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
	//cout << NumberOfJumps << endl;
	double J = 0;
	double JumpSum = 0;
	for(int i = 1; i < NumberOfJumps + 1; i++)	{
		J = 0.1*Gaussian();
		JumpSum += J;
	}
	//cout << JumpSum << endl;
	double Mu = Parameters.Rate - (-0.1)*Parameters.Jump;
	double CurrentSpot = Parameters.Spot*exp(Mu*Parameters.Expiry - 0.5*Parameters.Vol*Parameters.Vol*Parameters.Expiry + 
		Parameters.Vol*sqrt(Parameters.Expiry)*Gaussian() + NumberOfJumps*log(0.9) - 0.5*(0.1)*(0.1)*NumberOfJumps + JumpSum);
	//cout << CurrentSpot << endl;
	return max(CurrentSpot, 0.0);	
}

//PathApproxVolSpot Vol Drift = Reversion, alpha = 0.5
double PathApproxVolSpot::PathGenerator(Path& Path, Parameters& Parameters)	{
	double Increment = Parameters.Expiry / Parameters.NumberOfSteps;
	double CurrentSpot = Parameters.Spot;
	double CurrentVol = Parameters.Vol;
	double NextSpot;
	double NextVol;
	for(int i = 0; i < Parameters.NumberOfSteps; i++)	{
		NextVol = CurrentVol + 1*(0.1 - CurrentVol)*Increment + Parameters.VolVol*sqrt(CurrentVol)*sqrt(Increment)*Gaussian();
		NextSpot = CurrentSpot * exp((Parameters.Rate - 0.5*CurrentVol)*Increment) * exp(sqrt(CurrentVol)*sqrt(Increment)*Gaussian());
		CurrentVol = NextVol;
		CurrentSpot = NextSpot;
	}
	return CurrentSpot;
}

//PathApproxVolRMSLongSpot
 double PathApproxVolRMSLongSpot::PathGenerator(Path& Path, Parameters& Parameters)	{
	double CurrentVol = Parameters.Vol;
	double NextVol;
	double Increment = Parameters.Expiry / Parameters.NumberOfSteps;
	vector<double>* PVol = new vector<double>;
	vector<double>& PVolRef = *PVol;
	for(int i = 0; i < Parameters.NumberOfSteps; i++)	{
		PVolRef.push_back(CurrentVol);
		NextVol = CurrentVol + 1*(0.1 - CurrentVol)*Increment + Parameters.VolVol*sqrt(CurrentVol)*sqrt(Increment)*Gaussian();
		CurrentVol = NextVol;
	}
	double RMSVol = sqrt((1 / Parameters.Expiry)*Parameters.Integral(PVol, 0, Parameters.Expiry));
	double CurrentSpot = Parameters.Spot*exp((Parameters.Rate - 0.5*RMSVol*RMSVol)*Parameters.Expiry + RMSVol*sqrt(Parameters.Expiry)*Gaussian());
	return CurrentSpot;
 }

 //PathApproxVolRMS
 double PathApproxVolRMS::PathGenerator(Path& Path, Parameters& Parameters)	{
	double CurrentVol = Parameters.Vol;
	double NextVol;
	double Increment = Parameters.Expiry / Parameters.NumberOfSteps;
	vector<double>* PVol = new vector<double>;
	vector<double>& PVolRef = *PVol;
	for(int i = 0; i < Parameters.NumberOfSteps; i++)	{
		PVolRef.push_back(CurrentVol);
		NextVol = CurrentVol + 1*(0.1 - CurrentVol)*Increment + Parameters.VolVol*sqrt(CurrentVol)*sqrt(Increment)*Gaussian();
		CurrentVol = NextVol;
	}
	double RMSVol = sqrt((1 / Parameters.Expiry)*Parameters.Integral(PVol, 0, Parameters.Expiry));
	return RMSVol;
 }

		



