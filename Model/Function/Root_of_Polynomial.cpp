#include "Root_of_Polynomial.h"

double Root_of_Polynomial::Polynomial_Root(const int n, const double c[], const double EPS) {
	double interval, div = 10, root[30], fx[30], fmin, s;
	int i = 0, j, min;
	interval = (b - a) / div;
	for (s = a;s <= b;s += interval) {
		if (find_Root(n, c, s, EPS, &(root[i]))) {
			fx[i] = f(c, n, root[i]);
				//	printf("root[%d]:%lf\n",i,root[i]);
			i++;
		}
			//	else printf("fail\n");

	}
	fmin = fabs(fx[0]);
	min = 0;
	for (j = 1;j < i;j++)
		if (fmin > fabs(fx[j])) {
			fmin = fabs(fx[j]);
			min = j;
		}
	return root[min];
}

int Root_of_Polynomial::find_Root(const int n, const double c[], const double s, const double EPS, double* root) {
	//double p0,q0,r=1.0,p1,q1,p,q,pre;
	double p = s, q = s, d[30], dd[30];
	//	printf("s=%lf\n",s);
	int i = 0;
	for (i = 1;i <= n;i++) {
		d[i - 1] = c[i] * i;
		//		printf("d[%d]:%lf ",i-1,d[i-1]);
	}
	for (i = 2;i <= n;i++)
		dd[i - 2] = c[i] * (i - 1)*i;

	if (fabs(f(c, n, s))<ZERO) {
		*root = s;
		return 1;
	}
	for (i = 0;i<1000;i++) {
		p = q;
		double funcVal = f(c, n, p);
		double firstd = f(d, n - 1, p);  //first difference
		double secondd = f(dd, n - 2, p);  //second difference
		double deno = firstd*firstd - secondd*funcVal;   //denominator
		if (fabs(deno)<ZERO) {
			//     	printf("deno\n");
			return 0;
		}
		q = p - firstd*funcVal / deno;  //multiple root
										//	printf("times:%d p:%lf q:%lf f:%lf f':%lf\n",i,p,q,f(c,n,p),f(d,n-1,p));
		if (q<a || q>b) {
			//		printf("%lf is out of bound\n",q);
			return 0;
		}
		if (fabs(q - p)<EPS || fabs(f(c, n, q))<ZERO) {
			*root = q;
			return 1;
		}
	}
	//	printf("no convergence\n");
	return 0;
}

double Root_of_Polynomial::f(const double coe[], const double cn, const double x) {
	int i;
	double res = 0.0, sq = 1.0;
	for (i = 0;i <= cn;i++) {
		res += sq*coe[i];
		sq *= x;
	}
	//	printf("f:%lf\n",res);
	return res;
}
