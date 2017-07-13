#pragma once
#include "Common/Notification.h"
#include "Function/matrix.h"
#include "Common/Params.h"
#include "Function/Integral.h"
#include "Function/ODE.h"
#include "Function/Root_of_Polynomial.h"
#include "Function/Cond.h"
#include <QString>
#include <memory>
//#include "Function/eigenvalue.h"
//#include "Function/curve_fitting.h"
//#include "Function/root_of_matrix.h"
using namespace std;

class Model:public Proxy_Notification
{
protected:
    shared_ptr<Data> points;
    shared_ptr<QString> res;
public:
	Model();
	~Model();
    //for test
    static double f(double x);
    //for test
    static double ff(double t,double w);
    void Calculate(string &in);
    /*
    @param n   the degree of the polynomial
    @param c[]   an array of n+1 coefficients from n to 0 of the polynomials
    @param EPS  the accuracy of the root
    @return   the value of root
    @Note   It is guaranteed that a unique real number r exists in the given interval such that p(r)=0.
    @Note   p(x)=c_n*x^n+c_(n-1)*x^(n-1)+...+c_0*x^0  多项式求根
    */
    void getPolynomialRoot(const int n, const double c[], const double EPS);
    /*
     * @param a   the input Matrix
     * @note      求2的条件数
    */
    void getCond_2(Matrix a);
    /*
     * @param a   the input Matrix
     * @note      求无穷条件数
    */
    void getCond_inf(Matrix a);
    /*@param f(t0,w0)   the right side of y'=f(t,y)=f(t0,w0)
      @param a			the lower bound of the sample point
      @param b			the upper bound of the sample point
      @param step		the number of sample point -1
      @param ya			the initial condition  y(a)=ya
      @return			(step+1) sample point of y(ti) in the form of (ti,y(ti))
      @note				 y'=f(t,y)   a<=t<=b  y(a)=ya
      @note              解如上形式的常微分方程
    */
    void getODE(double(*f)(double t0, double w0), double a, double b, const int step, double ya);
    /*@param f(x)    the function to be integrate
      @param a    the lower bound of the integral
      @param b    the upper bound of the integral
      @param eps  the maximum error of the result
      @return     the result of the integral
      @note       using method of integral of Romberg  积分*/
    void getIntegral(double(*f)(double x), const double a, const double b, const double eps);
    /*@param f(x)    the function to be integrate
    @param a    the lower bound of the integral
    @param b    the upper bound of the integral
    @return     the result of the integral
    @note       using method of integral of composite Simpson  积分*/
    void getIntegral(double(*f)(double x), const double a, const double b);
    //求特征值
    void getEigenvalue(Matrix a);
    //求解AX=b
    void getMatrixRoot(Matrix a);
    shared_ptr<Data>& getPoints();
    shared_ptr<QString>& getRes();
    string double2string(double res);
};

