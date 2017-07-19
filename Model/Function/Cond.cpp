#include "Cond.h"
#include <cstring>
#include <iostream>
using namespace std;

void Matrix(const int n, const double a[][MAXM]) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

void Vector(const int n, const double b[]) {
	for (int i = 0;i < n;i++)
		cout << b[i] << endl;
	cout << endl;
}

bool Cond::inverse_Matrix(const double a[][MAXM], double inva[][MAXM], const int n)
{
	double col[MAXM];  //col=(A^-1)^t
	LU lu;
	int i, j;
	for (j = 0;j < n;j++) {
		memset(col, 0, n * sizeof(double));
		col[j] = 1;
		if (lu.LU_decom(n, a, col) == false)
			return false;
		for (i = 0;i < n;i++)
			inva[i][j] = col[i];
		
	}
	return true;
}

Cond::Cond()
{
}


Cond::~Cond()
{
}

double Cond::cond_2(const double a[][MAXM], const int n)
{
	double inva[MAXM][MAXM];
	Norm norm;
	if (inverse_Matrix(a, inva, n) == true) {
		return norm.norm_2(a, n)*norm.norm_2(inva, n);
	}
	else {
		cout << "singular" << endl;
		return -1;
	}
}

double Cond::cond_inf(const double a[][MAXM], const int n)
{
	double inva[MAXM][MAXM];
	Norm norm;
	if (inverse_Matrix(a, inva, n) == true) {
		return norm.norm_inf(a, n)*norm.norm_inf(inva, n);
	}
	else {
		cout << "singular" << endl;
		return -1;
	}
}


Norm::Norm()
{
}

Norm::~Norm()
{
}

double Norm::max(double a[], int n)
{
	double m = 0;
	int i;
	for (i = 0;i<n;i++) {
		if (fabs(a[i])>fabs(m)) m = a[i];
	}
	return m;
}

void Norm::divide(double b[], double a[], double p, int n)
{
	int i;
	for (i = 0;i<n;i++)
		b[i] = a[i] / p;
}

double Norm::max_eigenvalue(int n, double a[][MAXM], double &lambda, double v[], double TOL, int MAXN)
{
	double x[MAXM];
	double y[MAXM];
	double b[MAXM];
	double tmp[MAXM];
	double pm[MAXM][MAXM];  //permutation matrix
	double l[MAXM][MAXM];
	double c[MAXM][MAXM];
	double x1[MAXM];
	double e[MAXM];
	int i, j, k, it, maxi, flag;
	double xp, yp, q, u, numer = 0, deno = 0, maxvalue, error, ratio;
	memcpy(x, v, n * sizeof(double));

	//initialize u and l
	for (i = 0;i<n;i++) {
		memset(pm[i], 0, n * sizeof(double));
		pm[i][i] = 1;
		memset(l[i], 0, n * sizeof(double));
	}
	
	//q = *lambda;
	//initialize q= Xt*A*X/Xt*X
	for (i = 0;i < n;i++) {  //Xt*A
		tmp[i] = 0;
		for (j = 0;j < n;j++) {
			tmp[i] += v[j] * a[i][j];
		}
	}
	for (i = 0;i < n;i++) {
		numer += tmp[i] * v[i];
		deno += v[i] * v[i];
	}
	lambda = q = numer / deno;

	xp = max(v, n);
	divide(x, x, xp, n);

	//C=A-qI
	for (i = 0;i<n;i++) {
		for (j = 0;j<n;j++) {
			if (i == j) c[i][j] = a[i][j] - q;
			else c[i][j] = a[i][j];
		}
	}

	//check if A-qI has a unique solution
	for (i = 0;i<n;i++) {
		for (j = i + 1;j<n;j++) {
			flag = 1;
			for (k = 0;k<n;k++) {
				if (c[i][k] == 0 && c[j][k] == 0) continue;
				else if (c[i][k] != 0 && c[j][k] != 0) {
					ratio = c[j][k] / c[i][k];break;
				}
				else { flag = 0;break; }
			}
			if (flag == 0) break;
			for (;k<n;k++) {
				if (c[i][k] == 0 && c[j][k] == 0) continue;
				else if (c[i][k] == 0 || c[j][k] / c[i][k] != ratio) {
					flag = 0;break;
				}
			}
			if (flag == 1) return -1;
		}
	}

	//pivoting A-qI
	for (j = 0;j<n;j++) {
		maxvalue = 0;
		for (i = j;i<n;i++) {
			if (fabs(c[i][j])>maxvalue) {
				maxi = i;maxvalue = fabs(c[i][j]);
			}
		}
		if (maxvalue != 0) {
			if (i != j) {
				memcpy(tmp, c[j], n * sizeof(double));
				memcpy(c[j], c[maxi], n * sizeof(double));
				memcpy(c[maxi], tmp, n * sizeof(double));

				//permutation matrix
				memcpy(tmp, pm[j], n * sizeof(double));
				memcpy(pm[j], pm[maxi], n * sizeof(double));
				memcpy(pm[maxi], tmp, n * sizeof(double));
			}
		}
		else {
			for (i = j - 1;i >= 0;i--) {
				if (fabs(c[i][j])>maxvalue) {
					maxi = i;maxvalue = fabs(c[i][j]);
				}
			}
			if (maxvalue != 0) {
				for (k = 0;k<n;k++)
					c[i][k] += c[maxi][k];
				pm[i][maxi] += 1;
			}
			else return -1;  //there is one column of all 0, so the solution is not unique and *lambda is the eigenvalue
		}
	}

	//a=LU LUy=x z=Uy Lz=x 
	//a=LU a-->u
	for (j = 0;j<n;j++) {
		l[j][j] = 1;
		for (i = j + 1;i<n;i++) {
			l[i][j] = c[i][j] / c[j][j];
			if (l[i][j]>PINF) return -1;
			for (k = j;k<n;k++) c[i][k] -= c[j][k] * l[i][j];
		}
		if (fabs(c[j][j])<1e-10) return -1;
	}

	for (it = 0;it<MAXN;it++) {
		//x1=pm*x
		flag = 1;
		for (i = 0;i<n;i++) {
			if (x[i] != 0) {
				flag = 0;break;
			}
		}
		if (flag == 1) return -1;


		for (i = 0;i<n;i++) {
			x1[i] = 0;
			for (j = 0;j<n;j++) {
				x1[i] += pm[i][j] * x[j];
			}
		}

		memcpy(tmp, x, n * sizeof(double));  //tmp=x save x
		memcpy(x, x1, n * sizeof(double));

		//a=LU LUy=x z=Uy Lz=x
		//Lz=x  x-->z
		for (j = 0;j<n;j++) {
			for (i = j + 1;i<n;i++) {
				x[i] -= l[i][j] * x[j];
				//	l[i][j]=0;
			}
		}

		//Uy=x  ay=x  x-->y
		for (j = n - 1;j >= 0;j--) {
			x[j] /= c[j][j];
			for (i = j - 1;i >= 0;i--) {
				x[i] -= x[j] * c[i][j];
			}
		}

		memcpy(y, x, n * sizeof(double));
		memcpy(x, tmp, n * sizeof(double)); //restore x
		for (i = 0;i<n;i++)
			if (x[i] >= PINF || x[i] <= NINF) return -1;

		for (i = 0;i<n;i++)
			if (y[i] >= PINF || y[i] <= NINF) return -1;

		yp = max(y, n);
		u = yp;
		for (i = 0;i<n;i++)
			e[i] = x[i] - y[i] / yp;
		error = fabs(max(e, n));
		divide(x, y, yp, n);

		if (1.0 / u + q >= PINF) return 0;

		if (error<TOL) {
			lambda = 1.0 / u + q;
			memcpy(v, x, n * sizeof(double));
			return 1;
		}
	}
	return 0;
}

double Norm::norm_2(const double a[][MAXM], const int n)
{
	int i, j, k;
	double at[MAXM][MAXM]; //at=A^t transverse
	for (i = 0;i < n;i++) {
		for (j = 0;j < n;j++)
			at[i][j] = a[j][i];
	}

	double pow[MAXM][MAXM];  //pow = At*A
	for (i = 0;i < n;i++) {
		for (j = 0;j < n;j++) {
			pow[i][j] = 0;
			for (k = 0;k < n;k++)
				pow[i][j] += at[i][k] * a[k][j];
		}
	}

	double lambda=0, TOL = 1e-6, MAXN = 1e5, res;
	double *v = new double[n];
	double maxeig = 0;
	for (i = 0;i < n;i++)
		v[i] = 1;
	//pseudo-random initial vector
	for (int it = -199;it <= 200;it += 40) {
		v[it%n] = it;
		if (max_eigenvalue(n, pow, lambda, v, TOL, MAXN) && lambda > maxeig)
			maxeig = lambda;
	}
	res = sqrt(maxeig);
	return res;
}

double Norm::norm_inf(const double a[][MAXM], const int n)
{
	double sum, max = 0;
	int i, j, k;
	for (i = 0;i < n;i++) {
		sum = 0;
		for (j = 0;j < n;j++) {
			sum += fabs(a[i][j]);
		}
		if (sum > max)
			max = sum;
	}
	return max;
}

//LU_decompose with pivoting 
bool LU::LU_decom(const int n, const double A[][MAXM], double b[])
{
	int i, j, k;
	double l[MAXM][MAXM], m, e[MAXM], c[MAXM][MAXM],tmp[MAXM],pm[MAXM][MAXM];
	//a=A
	for (i = 0;i < n;i++) {
		memcpy(c[i], A[i], n * sizeof(double));
		memset(pm[i], 0, n * sizeof(double));
		pm[i][i] = 1;
	}

	int maxi;
	double maxvalue;
	//pivoting A
	for (j = 0;j<n;j++) {
		maxvalue = 0;
		for (i = j;i<n;i++) {
			if (fabs(c[i][j])>maxvalue) {
				maxi = i;maxvalue = fabs(c[i][j]);
			}
		}
		if (maxvalue != 0) {
			if (maxi != j) {
				memcpy(tmp, c[j], n * sizeof(double));
				memcpy(c[j], c[maxi], n * sizeof(double));
				memcpy(c[maxi], tmp, n * sizeof(double));

				//permutation matrix
				memcpy(tmp, pm[j], n * sizeof(double));
				memcpy(pm[j], pm[maxi], n * sizeof(double));
				memcpy(pm[maxi], tmp, n * sizeof(double));

				int tmpb = b[maxi];
				b[maxi] = b[j];
				b[j] = tmpb;
			}
		}
		else {
			for (i = j - 1;i >= 0;i--) {
				if (fabs(c[i][j])>maxvalue) {
					maxi = i;maxvalue = fabs(c[i][j]);
				}
			}
			if (maxvalue != 0) {
				for (k = 0;k<n;k++)
					c[i][k] += c[maxi][k];
				pm[i][maxi] += 1;
				b[i] += b[maxi];
			}
			else return false;  //there is one column of all 0, so the solution is not unique and *lambda is the eigenvalue
		}
	}

	//a=LU LUy=x z=Uy Lz=x 
	//a=LU a-->u
	for (j = 0;j<n;j++) {
		l[j][j] = 1;
		for (i = j + 1;i<n;i++) {
			l[i][j] = c[i][j] / c[j][j];
			if (l[i][j]>PINF) return -1;
			for (k = j;k<n;k++) c[i][k] -= c[j][k] * l[i][j];
		}
		if (fabs(c[j][j])<1e-10) return -1;
	}

		//a=LU LUy=x z=Uy Lz=x
		//Lz=x  x-->z
	for (j = 0;j < n;j++) {
		for (i = j + 1;i < n;i++) {
			b[i] -= l[i][j] * b[j];
		}
	}

	//Uy=x  ay=x  x-->y
	for (j = n - 1;j >= 0;j--) {
		b[j] /= c[j][j];
		for (i = j - 1;i >= 0;i--) {
			b[i] -= b[j] * c[i][j];
		}
	}
	return true;
}
