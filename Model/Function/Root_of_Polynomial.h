#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class Root_of_Polynomial {
private:
	const double ZERO = 1e-13; /* X is considered to be 0 if |X|<ZERO */
	const double a = -1e10;
	const double b = 1e10;  // a and b  the two end-points of the given interval; 
	const int MAXN = 11;  //maximum degree of the polynomial
	double f(const double coe[], const double cn, const double x);
	int find_Root(const int n, const double c[], const double s, const double EPS, double *root);
public:
	Root_of_Polynomial() {}
	~Root_of_Polynomial() {}
	/*
	@param n   the degree of the polynomial
	@param c[]   an array of n+1 coefficients from n to 0 of the polynomials
	@param EPS  the accuracy of the root
	@return   the value of root
	@Note   It is guaranteed that a unique real number r exists in the given interval such that p(r)=0.
	@Note   p(x)=c_n*x^n+c_(n-1)*x^(n-1)+...+c_0*x^0
	*/
	double Polynomial_Root(const int n, const double c[], const double EPS);
};


