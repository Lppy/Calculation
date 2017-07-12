#ifndef CURVE_FITTING
#define CURVE_FITTING
#include <vector>
#include <cstddef>
#include <cmath>
using namespace std;

class Fit {
	vector<double> factor;
	double ssr;
	double sse;
	double rmse;
	vector<double> fitedY;

public:
	Fit() :ssr(0), sse(0), rmse(0) {
		factor.resize(2, 0);
	}

    ~Fit() {}

//直线拟合，一元回归，默认数据不保存
	template<typename T>
	bool linearFit(const vector<T>& x,
		const vector<T>& y,
		bool isSaveFitY = false){
		return linearFit(&x[0], &y[0], getSeriesLength(x, y), isSaveFitY);
}

   template<typename T>
   bool linearFit(const T* x, const T* y, size_t length, bool isSaveFitY = false
   ) {
	   factor.resize(2, 0);
	   T t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	   for (int i = 0; i < length; ++i) {
		   t1 += x[i] * x[i];
		   t2 += x[i];
		   t3 += x[i] * y[i];
		   t4 += y[i];
	   }
	   factor[0] = (t1*t4 - t2*t3) / (t1*length - t2*t2);
	   factor[1] = (t3*length - t2*t4) / (t1*length - t2*t2);

	   calculateError(x, y, length, this->ssr, this->sse, this->rmse, isSaveFitY);
	   return true;
   }

   //多项式拟合，默认数据保存
   template<typename T>
   void polyfit(const vector<T>& x,
	   const vector<T>& y,
	   int PolyN,
	   bool isSaveFitY = true) {
	   polyfit(&x[0], &y[0], getSeriesLength(x, y), PolyN, isSaveFitY);
   }
   
   template<typename T>
   void polyfit(const T* x, const T* y, size_t length, int PolyN, bool isSaveFitY = true) {
	   factor.resize(PolyN + 1, 0);
	   int i, j;

	   vector<double> tempx(length, 1.0);
	   vector<double> tempy(y, y + length);
	   vector<double> sumxx(PolyN * 2 + 1);
	   vector<double> sumxy(PolyN + 1);
	   vector<double> ata((PolyN + 1)*(PolyN + 1));

	   for (i = 0;i < 2 * PolyN + 1;i++) {
		   for (sumxx[i] = 0, j = 0;j < length;j++) {
			   sumxx[i] += tempx[j];
			   tempx[j] *= x[j];
		   }
	   }

	   for (i = 0;i < PolyN + 1;i++) {
		   for (sumxy[i] = 0, j = 0;j < length;j++) {
			   sumxy[i] += tempy[j];
			   tempy[j] *= x[j];
		   }
	   }

	   for (i = 0;i < PolyN + 1;i++) 
		   for (j = 0;j < PolyN + 1;j++) 
			   ata[i*(PolyN + 1) + j] = sumxx[i + j];

			   gauss_solve(PolyN + 1, ata, factor, sumxy);
			   fitedY.reserve(length);
			   calculateError(&x[0], &y[0], length, this->ssr, this->sse, this->rmse, isSaveFitY);

   }

   //获取系数
   void getFactor(vector<double>& factor) { factor = this->factor; }

   //获取拟合方程y值
   void getFitedY(vector<double>& fitedY) { fitedY = this->fitedY; }

   template<typename T>
   double getY(const T x) const {
	   double ans(0);
	   for (size_t i = 0; i < factor.size(); ++i)
		   ans += factor[i] * pow((double)x,(int)i);

	   return ans;
   }

   //斜率
   double getSlope() {
	   return factor[1];  
   }

   //截距
   double getIntercept() {
	   return factor[0];
   }

   //剩余平方和
   double getSSE() {
	   return sse;
   }

   //回归平方和
   double getSSR() {
	   return ssr;
   }

   //均方根误差
   double getRMSE() {
	   return rmse;
   }

   //确定系数
   double getR_square() {
	   return 1 - (sse / (sse + ssr));
   }

   //取size
   template<typename T>
   size_t getSeriesLength(const vector<T>&x, const vector<T>& y) {
	   return (x.size() > y.size() ? y.size() : x.size());
   }

   //均值
   template<typename T>
   static T Mean(const vector<T>& v) {
	   return Mean(&v[0], v.size());
   }

   template<typename T>
   static T Mean(const T* v, size_t length) {
	   T total(0);
	   for (size_t i = 0;i < length;++i)
		   total += v[i];
	   return (total / length);
	  
   }

   //拟合方程系数个数
   size_t getFactorSize() {
	   return factor.size();
   }
   double getFactor(size_t i) {
	   return  factor.at(i);
   }

   private:
	   template<typename T>
	   void calculateError(const T* x, const T* y, size_t length,
		   double& r_ssr, double& r_sse, double& r_rmse, bool isSaveFitY = true) {
		   T mean_y = Mean<T>(y, length);
		   T yi(0);
		   fitedY.reserve(length);
		   for (int i = 0; i < length; ++i) {
			   yi = getY(x[i]);
			   r_ssr += ((yi - mean_y)*(yi - mean_y));
			   r_sse += ((yi - y[i])*(yi - y[i]));
			   if (isSaveFitY) {
				   fitedY.push_back(double(yi));
			   }
		   }
		   r_rmse = sqrt(r_sse / (double(length)));
	   }

	   template<typename T>
	   void gauss_solve(int n
		   , vector<T>& A
		   , vector<T>& x
		   , vector<T>& b)
	   {
		   gauss_solve(n, &A[0], &x[0], &b[0]);
	   }

	   template<typename T>
	   void gauss_solve(int n
		   , T* A
		   , T* x
		   , T* b)
	   {
		   int i, j, k, r;
		   double max;
		   for (k = 0;k<n - 1;k++)
		   {
			   max = fabs(A[k*n + k]); /*find maxmum*/
			   r = k;
			   for (i = k + 1;i<n - 1;i++) {
				   if (max<fabs(A[i*n + i]))
				   {
					   max = fabs(A[i*n + i]);
					   r = i;
				   }
			   }
			   if (r != k) {
				   for (i = 0;i<n;i++)         /*change array:A[k]&A[r] */
				   {
					   max = A[k*n + i];
					   A[k*n + i] = A[r*n + i];
					   A[r*n + i] = max;
				   }
			   }
			   max = b[k];                    /*change array:b[k]&b[r]     */
			   b[k] = b[r];
			   b[r] = max;
			   for (i = k + 1;i<n;i++)
			   {
				   for (j = k + 1;j<n;j++)
					   A[i*n + j] -= A[i*n + k] * A[k*n + j] / A[k*n + k];
				   b[i] -= A[i*n + k] * b[k] / A[k*n + k];
			   }
		   }

		   for (i = n - 1;i >= 0;x[i] /= A[i*n + i], i--)
			   for (j = i + 1, x[i] = b[i];j<n;j++)
				   x[i] -= A[i*n + j] * x[j];
	   }


};

#endif

