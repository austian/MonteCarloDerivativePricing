#include<iostream>
#include "Parameters.h"
#include "Stats.h"
#include "Option.h"
#include "PathGenerator.h"
#include "MonteCarloEngine.h"
#include "BSImpliedVol.h"
#include <fstream>
using namespace std;

double Expiry;
double Rate;
double Strike;
double Spot;
double Vol;
double Jump;
long NumberOfPaths;
long NumberOfSteps;

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

	cout << "Input jump intensity\n";
	cin >> Jump;

	cout << "Input number of paths\n";
	cin >> NumberOfPaths;

	cout << "Input number of steps\n";
	cin >> NumberOfSteps;

	Parameters CurrentParameters(Expiry, Rate, Spot, Vol, NumberOfPaths, NumberOfSteps, Jump);
	
	PathJumpTotal JumpTotal;
	PathApproxBrown ApproxBrown;

	Stats Stats;
	
	CallOption Call(Strike);
	vector<double>* Data;

	//ofstream Out("ImpliedVol.txt");
	//for(int i = 0; i <= 24; i++)	{
	//	Out << 50 + 5*i << "		" << BSImpliedVol(CurrentParameters, 50 + 5*i, 5) << endl;
	//}

	cout << "Formulas:\n";
	cout << "BS = " << Call.BSPrice(CurrentParameters, Call) << endl;
	cout << "JD = " << Call.JDPrice(20, CurrentParameters, Call) << endl;
	
	cout << "ApproxBrown:\n";
	Data = MonteCarlo(Call, CurrentParameters, ApproxBrown);
	Call.MontePrice(Data, Stats, CurrentParameters);
	
	cout << "JumpTotal:\n";
	Data = MonteCarlo(Call, CurrentParameters, JumpTotal);
	Call.MontePrice(Data, Stats, CurrentParameters);

	cout << "ImpliedVol:\n";
	cout << BSImpliedVol(CurrentParameters, Strike, 10) << endl;
	
	int tmp;
	cin >> tmp;

}