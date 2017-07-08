#include<iostream>
#include<cstdlib>
#include<cmath>

// swap two values
void swap(double &a, double &b) {
	double temp;
	temp = a;
	a = b;
	b = temp;
}

// switch matrix into Hessenberg matrix
void MatrixHessenberg(double * A, int n, double * result) {
	int max;
	int k,i,j;
	double temp;

	double *Atemp;
	Atemp = new double[n*n];

	for (i = 0; i<n; i++) {

		k = i*n;
		for (j = 0; j<n; j++) {
			Atemp[k + j] = A[k + j];
		}
	}

	for (k = 1; k<n - 1; k++) {
		i = k - 1;
		max = k;
		temp = abs(Atemp[k*n + i]);

		for (j = k + 1; j<n; j++) {
			if (abs(Atemp[j*n + i]) > temp) {
				temp = abs(A[j*n + i]);
				max = j;
			}
		}

		result[0] = Atemp[max*n + i];
		i = max;
		if (result[0] != 0) {
			if (i != k) {
				for (j = k - 1;j<n;j++)
					swap(Atemp[j*n + i], Atemp[j*n + k]);

				for (j = 0; j<n; j++)
					swap(Atemp[j*n + i], Atemp[j*n + k]);

			}

			for (i = k + 1; i<n; i++) {
				temp = Atemp[i*n + k - 1] / result[0];
				Atemp[i*n + k - 1] = 0;

				for (j = k; j<n; j++)
					Atemp[i*n + j] -= temp * Atemp[k*n + j];

				for (j = 0; j<n; j++)
					Atemp[j*n + k] += temp * Atemp[j*n + i];
			}
		}
	}

	for (i = 0; i<n; i++) {
		k = i*n;
		for (j = 0; j<n; j++)
			result[k + j] = Atemp[k + j];
	}

	delete[] Atemp;

}




// calculate the eigen value
bool MatrixEigenValue(double *A, int n, int LoopNumber, double Error, double *result) {
	
	double x, y, temp;
	double tempb, tempc, tempd;
	double p, q, r;
	double u, s, e, f, z, g;
	int t, i, j, k;

	double* Atemp;
	Atemp = new double(n*n);
	MatrixHessenberg(A, n, Atemp);
	int loop = LoopNumber;
	int m = n;

	while (m != 0) {
		t = m - 1;

		while (t>0) {
			temp = abs(A[(t - 1)*n + t - 1]);
			temp += abs(A[t*n + t]);
			temp = temp * Error;
			if (abs(A[t*n + t - 1]) > temp)
				t--;
			else
				break;
		}

		if (t == m - 1) {
			result[(n - 1) * 2] = Atemp[(m - 1)*n + m - 1];
			result[(n - 1) * 2 + 1] = 0;
			m -= 1;
			loop = LoopNumber;
		}
		else if (t == m - 2) {
			tempb = -Atemp[(m - 1)*n + m - 1] - Atemp[(m - 2)*n + m - 2];
			tempc = Atemp[(m - 1)*n + m - 1] * Atemp[(m - 2)*n + m - 2] - Atemp[(m - 1)*n + m - 2] * Atemp[(m - 2)*n + m - 1];
			tempd = tempb*tempb - 4 * tempc;
			y = sqrt(abs(tempd));
			if (tempd > 0) {
				x = 1;
				if (tempb < 0)
					x = -1;
				result[(m - 1) * 2] = -(tempb + x*y) / 2;
				result[(m - 1) * 2 + 1] = 0;
				result[(m - 2) * 2] =tempc/result[(m - 1) * 2];
				result[(m - 2) * 2 + 1] = 0;

			}

			else {
				result[(m - 1) * 2] = -tempb/ 2;
				result[(m - 1) * 2 + 1] = y/2;
				result[(m - 2) * 2] =-tempb/2;
				result[(m - 2) * 2 + 1] = -y/2;
			}

			m -= 2;
			loop = LoopNumber;
		}
		else {
			if (loop < 1)
				return false;
			
			loop--;

			j = t + 2;
			while (j < m) {
				Atemp[j*n + j - 2] = 0;
				j++;
			}

			j = t + 3;
			while (j < m) {
				Atemp[j*n + j - 3] = 0;
				j++;
			}

			k = t;
			while (k < m - 1) {
				if (k != t) {
					p = Atemp[k*n + k - 1];
					q = Atemp[(k + 1)*n + k - 1];
					if (k != m - 2)
						r = Atemp[(k + 2)*n + k - 1];
					else
						r = 0;
				}
				else {
					tempb = Atemp[(m - 1)*n + m - 1];
					tempc = Atemp[(m - 2)*n + m - 2];
					x = tempb + tempc;
					y = tempb*tempc - Atemp[(m - 2)*n + m - 1] * Atemp[(m - 1)*n + m - 2];
					p = Atemp[t*n + t] * (Atemp[t*n + t] - x) + Atemp[t*n + t + 1] * Atemp[(t + 1)*n + t] + y;
					q = Atemp[(t + 1)*n + t] * (Atemp[t*n + t] + Atemp[(t + 1)*n + t + 1] - x);
					r = Atemp[(t + 1)*n + t] * Atemp[(t + 2)*n + t + 1];

				}
				if (p != 0 || q != 0 || r != 0)
				{
					if (p<0)
					{
						x = -1;
					}
					else
					{
						x = 1;
					}
					s = x*sqrt(p*p + q*q + r*r);
					if (k != t)
					{
						Atemp[k*n + k - 1] = -s;
					}
					e = -q / s;
					f = -r / s;
					u = -p / s;
					y = -u - f*r / (p + s);
					g = e*r / (p + s);
					z = -x - e*q / (p + s);
					for (j = k;j<m;j++)
					{
						tempb = Atemp[k*n + j];
						tempc = Atemp[(k + 1)*n + j];
						p = x*tempb + e*tempc;
						q = e*tempb + y*tempc;
						r = f*tempb + g*tempc;
						if (k != m - 2)
						{
							tempb = Atemp[(k + 2)*n + j];
							p += f*tempb;
							q += g*tempb;
							r += z*tempb;
							Atemp[(k + 2)*n + j] = r;
						}
						Atemp[(k + 1)*n + j] = q;
						Atemp[k*n + j] = p;
					}
					j = k + 3;
					if (j>m - 2)
					{
						j = m - 1;
					}
					for (i = t;i<j + 1;i++)
					{
						tempb = Atemp[i*n + k];
						tempc = Atemp[i*n + k + 1];
						p = x*tempb + e*tempc;
						q = e*tempb + y*tempc;
						r = f*tempb + g*tempc;
						if (k != m - 2)
						{
							tempb = Atemp[i*n + k + 2];
							p += f*tempb;
							q += g*tempb;
							r += z*tempb;
							Atemp[i*n + k + 2] = r;
						}
						Atemp[i*n + k + 1] = q;
						Atemp[i*n + k] = p;
					}
				}
				k++;

			}

		}


	}
	delete[] Atemp;
	return true;
}



