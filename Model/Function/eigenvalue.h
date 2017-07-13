#pragma once
#include "matrix.h"

class Eigenvalue
{
private:
	static const int MAX_N = 30;
public:
	Eigenvalue();
	~Eigenvalue();
	
	void swap(double &a, double &b);
	
	void MatrixToArray(Matrix a, double * A);
	void MatrixHessenberg(double * A, int n, double * result);
	bool MatrixEigenValue(Matrix a, int n, int LoopNumber, double *result);

};

