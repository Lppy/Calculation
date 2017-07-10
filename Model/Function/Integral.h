#pragma once
class Integral
{
private:
	static const int MAX_N = 30;
public:
	Integral();
	~Integral();
	/*@param f(x)    the function to be integrate
	  @param a    the lower bound of the integral
	  @param b    the upper bound of the integral
	  @param eps  the maximum error of the result
	  @return     the result of the integral
	  @note       using method of integral of Romberg*/
	double Romberg(double(*f)(double x), const double a, const double b, const double eps);
	/*@param f(x)    the function to be integrate
	@param a    the lower bound of the integral
	@param b    the upper bound of the integral
	@return     the result of the integral
	@note       using method of integral of composite Simpson*/
	double quad(double(*f)(double x), const double a, const double b);
};

