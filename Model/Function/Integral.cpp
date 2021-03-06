#include "Integral.h"
#include <math.h>
#include <iostream>
using namespace std;

Integral::Integral()
{
}


Integral::~Integral()
{
}

double Integral::Romberg(double(*f)(double x), const double a, const double b, const double eps) {
	double r[2][MAX_N];
	double hsum, error, h, ni, p, q;
	int i, j, flag = 0;
	//get the first triangle i=1,2
	hsum = f(a) + f(b);
	h = b - a;
	r[0][0] = 0.5*h*hsum;
	q = 1;

	for (i = 1;i<MAX_N;i++) {
		h /= 2;
		ni = a - h;
		for (j = 1;j <= q;j++)
			hsum += 2 * f(ni + h * 2 * j);
		q *= 2;
		r[1][0] = 0.5*h*hsum;
		p = 4;
	//	cout << "r[1][0]=" << r[1][0] << endl;
		for (j = 1;j <= i;j++) {
			r[1][j] = r[1][j - 1] + (r[1][j - 1] - r[0][j - 1]) / (p - 1);
			p *= 4;
		}
		if (i >= 20 && fabs(r[1][i] - r[0][i - 1])<eps) {
			if (flag == 1)
				return r[1][i];
			else flag = 1;
		}
		else flag = 0;
		//		memcpy(r[0],r[1],(i+1)*sizeof(double));
		for (j = 0;j <= i;j++)
			r[0][j] = r[1][j];

	}
}

double Integral::quad(double(*f)(double x), const double a, const double b)
{
    int step = fabs(b - a) / 0.01;
	double h = 0.01;
	double xi[3],x;
	xi[0] = f(a) + f(b);
	xi[1] = xi[2] = 0;
	for (int i = 0;i < step;i++) {
		x = a + i*h;
		if (i % 2) {
			xi[2] += f(x);
			xi[1] += f(x);
		}
	}
	return h*(xi[0]+2*xi[2]+4*xi[1])/3;
}


