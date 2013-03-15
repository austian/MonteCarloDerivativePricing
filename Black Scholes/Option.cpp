#include <algorithm>
#include "Option.h"
#include <vector>
#include "PathGenerator.h"
#include "Parameters.h"
#include <cmath>
#include <iostream>
using namespace std;

CallOption::CallOption(double Strike)	:	Strike(Strike)	{}

double CallOption::Payoff(Option& Option, Parameters& Parameters, Path& Path)	{
	double CurrentSpot = Path.PathGenerator(Path, Parameters);
	return max(CurrentSpot - Strike, 0.0);
}

void CallOption::Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The call price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
}

PutOption::PutOption(double Strike)	:	Strike(Strike)	{}

double PutOption::Payoff(Option& Option, Parameters& Parameters, Path& Path)	{
	double CurrentSpot = Path.PathGenerator(Path, Parameters);
	return max(Strike - CurrentSpot, 0.0);
}

void PutOption::Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The put price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
}

AsianCallOption::AsianCallOption(double Strike, vector<double>* Times)	:	Strike(Strike), Times(Times)	{}

double AsianCallOption::Payoff(Option& Option, Parameters& Parameters_, Path& Path)	{
	vector<double>& TimesRef = *Times;
	vector<double> Spots;
	Parameters* Clone = new Parameters(Parameters_.Expiry, Parameters_.Rate, Parameters_.Spot, Parameters_.Vol, Parameters_.NumberOfPaths, Parameters_.NumberOfSteps);
	(*Clone).Expiry = TimesRef[0];
	Spots.push_back(Path.PathGenerator(Path, (*Clone)));
	for(int i = 0; i < TimesRef.size()-1; i++)	{
		(*Clone).Expiry = TimesRef[i+1] - TimesRef[i];
		Spots.push_back(Path.PathGenerator(Path, (*Clone)));
		(*Clone).Spot = Path.PathGenerator(Path, (*Clone));
	}
	double RunningSum = 0;
	for(int i = 0; i < TimesRef.size(); i++)	{
		RunningSum += Spots[i];
	}
	return max((RunningSum / TimesRef.size()) - Strike, 0.0);
	delete Clone;
}

void AsianCallOption::Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The Asian call price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
}

DnOCallOption::DnOCallOption(double Strike, double Barrier, vector<double>* Times)	:	Strike(Strike), Barrier(Barrier), Times(Times)	{}

double DnOCallOption::Payoff(Option& Option, Parameters& Parameters_, Path& Path)	{
	vector<double>& TimesRef = *Times;
	vector<double> Spots;
	Parameters* Clone = new Parameters(Parameters_.Expiry, Parameters_.Rate, Parameters_.Spot, Parameters_.Vol, Parameters_.NumberOfPaths, Parameters_.NumberOfSteps);
	(*Clone).Expiry = TimesRef[0];
	Spots.push_back(Path.PathGenerator(Path, (*Clone)));
	for(int i = 0; i < TimesRef.size()-1; i++)	{
		(*Clone).Expiry = TimesRef[i+1] - TimesRef[i];
		Spots.push_back(Path.PathGenerator(Path, (*Clone)));
		(*Clone).Spot = Path.PathGenerator(Path, (*Clone));
	}
	double Price;
	for(int i = 0; i < Spots.size(); i++)	{
		if(Spots[i] <= Barrier)	{	
			Price = 0;
			break;
		}
		else 
			Price = max(Spots[i] - Strike, 0.0);
	}
	return Price;
	delete Clone;
}

void DnOCallOption::Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The down and out call price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
}

DnICallOption::DnICallOption(double Strike, double Barrier, vector<double>* Times)	:	Strike(Strike), Barrier(Barrier), Times(Times)	{}

double DnICallOption::Payoff(Option& Option, Parameters& Parameters_, Path& Path)	{
	vector<double>& TimesRef = *Times;
	vector<double> Spots;
	Parameters* Clone = new Parameters(Parameters_.Expiry, Parameters_.Rate, Parameters_.Spot, Parameters_.Vol, Parameters_.NumberOfPaths, Parameters_.NumberOfSteps);
	(*Clone).Expiry = TimesRef[0];
	Spots.push_back(Path.PathGenerator(Path, (*Clone)));
	for(int i = 0; i < TimesRef.size()-1; i++)	{
		(*Clone).Expiry = TimesRef[i+1] - TimesRef[i];
		Spots.push_back(Path.PathGenerator(Path, (*Clone)));
		(*Clone).Spot = Path.PathGenerator(Path, (*Clone));
	}
	double Price;
	for(int i = 0; i < Spots.size(); i++)	{
		if(Spots[i] <= Barrier)	{	
			Price = max(Spots[Spots.size() -1] - Strike, 0.0);
			break;
		}
		else 
			Price = 0;
	}
	return Price;
	delete Clone;
}

void DnICallOption::Price(std::vector<double>* Data, Stats& Stats, Parameters& Parameters)	{
	double Expectation = Stats.Expectation(Data);
	double DiscountedExpectation = exp(-1*Parameters.Rate*Parameters.Expiry)*Expectation;
	cout << "The down and in call price is " << DiscountedExpectation << endl;
	double Variance = Stats.Variance(Data, Expectation);
	double StandDev = Stats.StandDev(Variance);
	double StandError = Stats.StandError(StandDev, Parameters.NumberOfPaths);
	cout << "The standard error is " << StandError << endl;
}