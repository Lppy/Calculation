#pragma once
class Integral
{
private:
	static const int MAX_N = 30;
	double f(const int n, const double coe[], const double x);
public:
	Integral();
	~Integral();
	/*@param n    the degree of polynomial
	  @param coe  an array of the coneffient from 0 to n
	  @param a    the lower bound of the integral
	  @param b    the upper bound of the integral
	  @param eps  the maximum error of the result
	  @return     the result of the integral
	  @note       using method of integral of Romberg*/
	double Romberg(const int n, const double coe[], const double a, const double b, const double eps);
	/*@param n    the degree of polynomial
	@param coe  an array of the coneffient from 0 to n
	@param a    the lower bound of the integral
	@param b    the upper bound of the integral
	@return     the result of the integral
	@note       using method of integral of composite Simpson*/
	double quad(const int n, const double coe[], const double a, const double b);
};

