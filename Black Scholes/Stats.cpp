#include "Stats.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

double Stats::Expectation(std::vector<double>* Data)	{
	vector<double> DataVector = *Data;
	double RunningSum = 0;
	for(int i = 0; i < DataVector.size(); i++)
		RunningSum += DataVector[i];
	double Expectation = RunningSum / DataVector.size();
	return Expectation;
}

double Stats::Variance(std::vector<double>* Data, double Expectation)	{
	vector<double> DataVector = *Data;
	double RunningSum = 0;
	double CurrentSummand;
	for(int i = 0; i < DataVector.size(); i++)	{
		CurrentSummand = (DataVector[i] - Expectation) * (DataVector[i] - Expectation);
		RunningSum += CurrentSummand;
	}
	double Variance = (1 / (double)DataVector.size())* RunningSum;
	return Variance;
}

double Stats::StandDev(double Variance)	{
	return sqrt(Variance);
}

double Stats::StandError(double StandDev, double NumberOfTrials)	{
	return (StandDev / sqrt(NumberOfTrials));
}