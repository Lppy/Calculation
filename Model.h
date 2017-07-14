#pragma once
#include "Common/Notification.h"
#include "Function/matrix.h"
#include "Common/Params.h"
#include "Function/Integral.h"
#include "Function/ODE.h"
#include "Function/Root_of_Polynomial.h"
//#include "Function/curve_fitting.h"
#include "Function/baseInterpreter.h"
#include "Function/Cond.h"
#include "Function/Cubic_Spline.h"
#include <QString>
#include <memory>
#include <map>
//#include "Function/eigenvalue.h"
//#include "Function/curve_fitting.h"
//#include "Function/root_of_matrix.h"
using namespace std;

extern map<string, Matrix> matrix_table;
extern double coefficient[10];

class Model:public Proxy_Notification
{
protected:
    shared_ptr<Data> points;
    shared_ptr<QString> res;
    vector<Action> DoneList;  //for undo and redo
    int pos;  //current position in DoneList
public:
	Model();
	~Model();
    shared_ptr<Data>& getPoints();
    shared_ptr<QString>& getRes();

    void Calculate(string &in);
    void Redo();
    void Undo();

private:
    void main();

    const int MAXD=9;   //maximum degree
    bool is_legal_param(const string&);
    Matrix shell_save_matrix(string&, istringstream&);
    void shell_derivative(string&);
    void shell_integrate(string&,double&,double&);
    void resolve_polynomial(string&);
    void shell_eig(string&);
    void shell_equation(string&);
    void shell_ode(string&,double&,double&,double&);
    vector<Point> shell_point(string &in);

    string double2string(double res);
    double string2double(string str);

    static double poly(double x,double coe[]);
    static double f(double x);
    static double ff(double t,double w);

    void DisplayAction(const Action& a);
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
//   void getEigenvalue(Matrix a);
    //求解AX=b
    void getMatrixRoot(Matrix a,Matrix b);
    //曲线拟合
    void getCubicSpline(vector<Point> p,int Type);
//  void CurveFitting(double* x, double* y, size_t length, int PolyN);*/
    //画折线
    void getBrokenLine(vector<Point> p);
    //画曲线
    void getCurve(vector<Point> p);

};

