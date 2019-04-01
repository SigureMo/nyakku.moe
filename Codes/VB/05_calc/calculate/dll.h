#include <iostream>

using namespace std;

#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

class DLLIMPORT DllClass
{
	public:
		DllClass();
		virtual ~DllClass();
		DLLIMPORT void checkVars();
    DLLIMPORT void fillArithmeticUnitVector(string expression);
    DLLIMPORT void computePostfixExpressionQueue();
    DLLIMPORT float computeValue();
};

#endif
