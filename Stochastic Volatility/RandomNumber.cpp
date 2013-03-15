#include "RandomNumber.h"
#include <cmath>

const double pi = 3.14159265358979325;

//inverse cumulative normal function (Moro algo)

const double a_0 = 2.50662823884;
const double a_1 = -18.61500062529;
const double a_2 = 41.39119773534;
const double a_3 = -25.44106049637;
const double b_0 = -8.47351093090;
const double b_1 = 23.08336743743;
const double b_2 = -21.06224101826;
const double b_3 = 3.13082909833;
const double c_0 = 0.3374754822726147;
const double c_1 = 0.9761690190917186;
const double c_2 = 0.1607979714918209;
const double c_3 = 0.0276438810333863;
const double c_4 = 0.0038405729373609;
const double c_5 = 0.0003951896511919;
const double c_6 = 0.0000321767881768;
const double c_7 = 0.0000002888167364;
const double c_8 = 0.0000003960315187;

double NInv(double x)	{
	double y = x - 0.5;
	if(-0.42 < y && y < 0.42)	{
		double r = y*y;
		double p = (y*(a_0 + a_1*r + a_2*r*r + a_3*r*r*r))/(b_0*r + b_1*r*r + b_2*r*r*r + b_3*r*r*r*r + 1);
		return p;
	}
	else	{
		double r;
		if(y < 0)
			r = x;
		else
			r = 1-x;
		double s = log(-log(r));
		double t = c_0 + c_1*s + c_2*s*s + c_3*s*s*s + c_4*pow(s,4) + c_5*pow(s,5) + c_6*pow(s,6) + c_7*pow(s,7) + c_8*pow(s,8);
		if(x > 0.5)
			return t;
		else
			return -t;
	}
}

//cumulative normal function

double N(double x)	{
	if(x > 0)	{
		double k = 1 / (1 + 0.2316419*x);
		double z = 1 - 1 / (sqrt(2*pi))*exp(-(x*x) / 2)*k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));
		return z;
	}
	else	{
		double k = 1 / (1 - 0.2316419*x);
		double z = 1 - 1 / (sqrt(2*pi))*exp(-(x*x) / 2)*k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));
		return 1 - z;
	}
}

//Gaussian by inverse CDF
double RandNorm()	{
	double r = rand();
	double u = r / static_cast<double>(RAND_MAX);
	return NInv(u);
}

//Gaussian by Box-Muller
double Gaussian()	{
	double result;
	double x;
	double y;
	double SizeSquared;
	do	{
	x = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
	y = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
	SizeSquared = x*x + y*y;
	}
	while(SizeSquared >=1.0);
	result = x*sqrt(-2*log(SizeSquared)/SizeSquared);
	return result;
}

//Poisson
double Poisson(double Lambda, double Time)	{
	double L = exp(-1*Lambda*Time);
	int k = 0;
	double p = 1;
	do	{
		k += 1;
		p *= (rand()/static_cast<double>(RAND_MAX));
	}	
	while(p > L);
	return k - 1;
}


