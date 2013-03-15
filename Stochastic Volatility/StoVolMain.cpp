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
double VolVol;
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

	cout << "Input volatility of volatility\n";
	cin >> VolVol;

	cout << "Input jump intensity\n";
	cin >> Jump;

	cout << "Input number of paths\n";
	cin >> NumberOfPaths;

	cout << "Input number of steps\n";
	cin >> NumberOfSteps;

	Parameters CurrentParameters(Expiry, Rate, Spot, Vol, NumberOfPaths, NumberOfSteps, Jump, VolVol);
	
	PathJumpTotal JumpTotal;
	PathApproxBrown ApproxBrown;
	PathApproxVolSpot ApproxVolSpot;
	PathApproxVolRMSLongSpot ApproxVolRMSLongSpot;
	PathApproxVolRMS ApproxVolRMS;

	Stats Stats;
	
	CallOption Call(Strike);
	vector<double>* Data;

	//ofstream Out("ImpliedVol.txt");
	//for(int i = 0; i <= 20; i++)	{
	//	Call.Strike = 50+5*i;
	//	Data = MonteCarlo(Call, CurrentParameters, ApproxVolSpot);
	//	double Price = Call.MontePrice(Data, Stats, CurrentParameters);
	//	Out << 50 + 5*i << "		" << BSImpliedVol(CurrentParameters, 50 + 5*i, 10, Price) << endl;
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

	cout << "ApproxVolSpot:\n";
	Data = MonteCarlo(Call, CurrentParameters, ApproxVolSpot);
	double VolPrice = Call.MontePrice(Data, Stats, CurrentParameters);

	cout << "ApproxVolRMSLongSpot:\n";
	Data = MonteCarlo(Call, CurrentParameters, ApproxVolRMSLongSpot);
	Call.MontePrice(Data, Stats, CurrentParameters);

	cout << "ApproxVolRMS BS:\n";
	vector<double> DataVol;
	vector<double> DataPrice;
	double RMSVol;
	Parameters CloneVol(Expiry, Rate, Spot, Vol, NumberOfPaths, NumberOfSteps, Jump, VolVol);
	for(int i = 0; i < NumberOfPaths; i++)	{
		RMSVol = ApproxVolRMS.PathGenerator(ApproxVolRMS, CurrentParameters);
		DataVol.push_back(RMSVol);
		CloneVol.Vol = RMSVol;
		DataPrice.push_back(Call.BSPrice(CloneVol, Call));
	}
	vector<double>* DataPricePointer = &DataPrice;
	Call.MontePrice(DataPricePointer, Stats, CurrentParameters);

	cout << "Implied Vol:\n";
	cout << BSImpliedVol(CurrentParameters, Strike, 10, VolPrice) << endl;

	int tmp;
	cin >> tmp;

}