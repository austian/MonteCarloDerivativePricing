#ifndef PathGenerator_h
#define PathGenerator_h
#include "Parameters.h"

class Path	{
public:
	virtual double PathGenerator(Path& Path, Parameters& Parameters)=0;
};

class PathApproxBrown	: public Path	{
public:
	double PathGenerator(Path& Path, Parameters& Parameters);
};

class PathJumpTotal	:	public Path	{
public:
	double PathGenerator(Path& Path, Parameters& Parameters);
};

class PathApproxVolSpot	:	public	Path	{
public:
	double PathGenerator(Path& Path, Parameters& Parameters);
};

class PathApproxVolRMSLongSpot	:	public	Path	{
public:
	double PathGenerator(Path& Path, Parameters& Parameters);
};

class PathApproxVolRMS	:	public	Path	{
public:
	double PathGenerator(Path& Path, Parameters& Parameters);
};

#endif