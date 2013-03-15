#include <algorithm>
#include "Option.h"
#include <vector>
#include "PathGenerator.h"
#include "Parameters.h"
#include <cmath>
#include "RandomNumber.h"
#include <iostream>
using namespace std;

const double pi = 3.14159265358979325;

CallOption::CallOption(double Strike)	:	Strike(Strike)	{}

double CallOption::Payoff(Option& Option, Parameters& Parameters, Path& Path)	{
	double CurrentSpot = Path.PathGenerator(Path, Parameters);
	return max(CurrentSpot - Strike, 0.0);
}

double CallOption::MontePrice(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The call price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
	return DiscountedExpectation;
}

double CallOption::BSPrice(Parameters& Parameters, Option& Option)	{
	double d1 = (log(Parameters.Spot / Strike) + (Parameters.Rate + 0.5 * Parameters.Vol * Parameters.Vol)*Parameters.Expiry) / (Parameters.Vol * sqrt(Parameters.Expiry));
	double d2 = (log(Parameters.Spot / Strike) + (Parameters.Rate - 0.5 * Parameters.Vol * Parameters.Vol)*Parameters.Expiry) / (Parameters.Vol * sqrt(Parameters.Expiry));
	return Parameters.Spot*N(d1) - Strike* exp(-1*Parameters.Rate*Parameters.Expiry)*N(d2);
}

//nu = 0.1, m = 0.9
double CallOption::JDPrice(long DegOfAcc, Parameters& _Parameters, Option& Option)	{
	double RunningSum = 0;
	long Factorial = 1;
	double JumpPrime = _Parameters.Jump*0.9;
	Parameters* Clone = new Parameters(_Parameters.Expiry, _Parameters.Rate, _Parameters.Spot, _Parameters.Vol, _Parameters.NumberOfPaths, _Parameters.NumberOfSteps, _Parameters.Jump, _Parameters.VolVol);
	for(int n = 0; n <= DegOfAcc; n++)	{
		if(n>=1)
			Factorial *= n;
		double Sigma = sqrt(_Parameters.Vol*_Parameters.Vol + n*0.1*0.1/_Parameters.Expiry);
		double R = _Parameters.Rate - _Parameters.Jump*(0.9-1) + n*log(0.9)/_Parameters.Expiry;
		(*Clone).Vol = Sigma;
		(*Clone).Rate = R;
		RunningSum += ((exp(-1*JumpPrime*_Parameters.Expiry)*pow(JumpPrime*_Parameters.Expiry, n))/ Factorial)*Option.BSPrice(*Clone, Option);
	}
	delete Clone;
	return RunningSum;
}

double CallOption::Vega(Parameters& Parameters, Option& Option)	{
	double d1 = (log(Parameters.Spot / Strike) + (Parameters.Rate + 0.5 * Parameters.Vol * Parameters.Vol)*Parameters.Expiry) / (Parameters.Vol * sqrt(Parameters.Expiry));
	return Parameters.Spot*sqrt(Parameters.Expiry)*(1/sqrt(2*pi))*exp(-1*0.5*d1*d1);
	
}
