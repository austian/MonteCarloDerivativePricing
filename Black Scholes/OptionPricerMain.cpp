#include<iostream>
#include "Parameters.h"
#include "Stats.h"
#include "Option.h"
#include "PathGenerator.h"
#include "MonteCarloEngine.h"
using namespace std;

double Expiry;
double Rate;
double Strike;
double Spot;
double Vol;
double Barrier;
long NumberOfPaths;
long NumberOfSteps;
long NumberOfTimesAsian;
long NumberOfTimesBarrier;

int main()	{

	cout << "Input time to expiry:\n";
	cin >> Expiry;

	cout << "Input interest rate\n";
	cin >> Rate;

	cout << "Input strike\n";
	cin >> Strike;

	cout << "Input spot\n";
	cin >> Spot;

	cout << "Input volatility\n";
	cin >> Vol;

	cout << "Input barrier\n";
	cin >> Barrier;

	cout << "Input number of paths\n";
	cin >> NumberOfPaths;

	cout << "Input number of steps\n";
	cin >> NumberOfSteps;

	cout << "How many times for Asian option\n";
	cin >> NumberOfTimesAsian;
	vector<double>* TimesAsian = new vector<double>;
	double IncrementTime = Expiry / NumberOfTimesAsian;
	double RunningSumTimes = 0;
	for(int i = 0; i < NumberOfTimesAsian; i++)	{
		RunningSumTimes += IncrementTime;
		(*TimesAsian).push_back(RunningSumTimes);
	}

	cout << "How many times to check the barrier\n";
	cin >> NumberOfTimesBarrier;
	vector<double>* TimesBarrier = new vector<double>;
	IncrementTime = Expiry / NumberOfTimesBarrier;
	RunningSumTimes = 0;
	for(int i = 0; i < NumberOfTimesBarrier; i++)	{
		RunningSumTimes += IncrementTime;
		(*TimesBarrier).push_back(RunningSumTimes);
	}

	Parameters CurrentParameters(Expiry, Rate, Spot, Vol, NumberOfPaths, NumberOfSteps);
	
	PathSDETotal SDETotal;
	PathApproxBrown ApproxBrown;
	PathSDEIncrement SDEIncrement;
	Stats Stats;
	
	CallOption Call(Strike);
	PutOption Put(Strike);
	AsianCallOption AsianCall(Strike, TimesAsian);
	DnOCallOption DnOCall(Strike, Barrier, TimesBarrier);
	DnICallOption DnICall(Strike, Barrier, TimesBarrier);
	vector<double>* Data;

	cout << "SDE total:\n";
	Data = MonteCarlo(Call, CurrentParameters, SDETotal);
	Call.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(Put, CurrentParameters, SDETotal);
	Put.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(AsianCall, CurrentParameters, SDETotal);
	AsianCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnOCall, CurrentParameters, SDETotal);
	DnOCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnICall, CurrentParameters, SDETotal);
	DnICall.Price(Data, Stats, CurrentParameters);

	cout << "ApproxBrown:\n";
	Data = MonteCarlo(Call, CurrentParameters, ApproxBrown);
	Call.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(Put, CurrentParameters, ApproxBrown);
	Put.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(AsianCall, CurrentParameters, ApproxBrown);
	AsianCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnOCall, CurrentParameters, ApproxBrown);
	DnOCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnICall, CurrentParameters, ApproxBrown);
	DnICall.Price(Data, Stats, CurrentParameters);

	cout << "SDEIncrement:\n";
	Data = MonteCarlo(Call, CurrentParameters, SDEIncrement);
	Call.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(Put, CurrentParameters, SDEIncrement);
	Put.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(AsianCall, CurrentParameters, SDEIncrement);
	AsianCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnOCall, CurrentParameters, SDEIncrement);
	DnOCall.Price(Data, Stats, CurrentParameters);
	Data = MonteCarlo(DnICall, CurrentParameters, SDEIncrement);
	DnICall.Price(Data, Stats, CurrentParameters);


	int tmp;
	cin >> tmp;

}