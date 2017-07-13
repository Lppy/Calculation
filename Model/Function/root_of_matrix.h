#pragma once
#include <iostream>
#include <math.h>
#include<matrix.h>

using namespace std;

class Root_of_Matrix {
private:

	const int MAXN = 10;  //maximum degree of the polynomial
	//const int n = 3;
public:
	Root_of_Matrix() {}
	~Root_of_Matrix() {}

	double*  Matrix_root(Matrix a, double b[n], double s[n]);
	double* ALU(double a[n][n], double b[n], double s[n]);
};


