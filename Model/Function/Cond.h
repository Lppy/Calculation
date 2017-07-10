#pragma once
#include <math.h>
#include <vector>
#define MAXM 30  /*max matrix 30*30*/
#define ZERO 1e-8
using namespace std;

class Cond
{
	friend class LU;
private:
	/*@param   inva: return the inverse of the matrix
	  @return  true if a is nonsingular, false if not 
	*/
	bool inverse_Matrix(const double a[][MAXM], double inva[][MAXM], const int n);
public:
	Cond();
	~Cond();
	double cond_2(const double a[][MAXM], const int n);
	double cond_inf(const double a[][MAXM], const int n);
};

class Norm {
private:
	const double PINF = pow(2, 127);
	const double NINF = -pow(2, 127);
	double max(double a[], int n);
	void divide(double b[], double a[], double p, int n);
	double max_eigenvalue(int n, double a[][MAXM], double &lambda, double v[], double TOL, int MAXN);
public:
	Norm();
	~Norm();
	double norm_2(const double a[][MAXM], const int n);
	double norm_inf(const double a[][MAXM], const int n);
};

class LU {
public:
	LU(){}
	~LU(){}
	const double PINF = pow(2, 127);
	const double NINF = -pow(2, 127);
	const double MAXN = 1e5;
	/*@param b[] return the result of Ax=b if A is nonsingular
	  @return ture if A is nonsingular, false if not
	*/
	bool LU_decom(const int n, const double A[][MAXM], double b[]);
};

