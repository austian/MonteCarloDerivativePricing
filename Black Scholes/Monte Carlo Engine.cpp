#include "Parameters.h"
#include "Option.h"
#include "Random Number.h"
#include "PathGenerator.h"
#include "Stats.h"
#include <vector>
#include <iostream>
using namespace std;

vector<double>* MonteCarlo(Option& Option, Parameters& Parameters, Path& Path)	{
	vector<double>* Data = new vector<double>;
	vector<double>& DataRef = *Data;
	double CurrentTrial;
	for(int i = 0; i < Parameters.NumberOfPaths; i++)	{
		CurrentTrial = Option.Payoff(Option, Parameters, Path);
		DataRef.push_back(CurrentTrial);
	}
	return Data; 
}
