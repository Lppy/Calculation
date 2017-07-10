#pragma once
#include "type.h"
#include <vector>
using namespace std;
class ODE   //ordinary differential equation  常微分方程
{
public:
	ODE();
	~ODE();
	/*@param f(t0,w0)   the right side of y'=f(t,y)=f(t0,w0)
	  @param a			the lower bound of the sample point
	  @param b			the upper bound of the sample point
	  @param step		the number of sample point -1
	  @param ya			the initial condition  y(a)=ya
	  @return			(step+1) sample point of y(ti) in the form of (ti,y(ti))
	  @note				 y'=f(t,y)   a<=t<=b  y(a)=ya 
	*/
	vector<point> ode45(double(*f)(double t0, double w0), double a, double b, const int step, double ya);
};

