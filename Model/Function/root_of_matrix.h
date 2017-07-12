#pragma once
#include<iostream>
using namespace std;

const int n = 3;
//矩阵的ALU分解
double*  ALU(double a[n][n], double b[n], double s[n])
{
    double l[n][n] = { 0 };
    double u[n][n] = { 0 };
    int i, r, k;
    //进行U的第一行的赋值
    for (i = 0; i<n; i++)
    {
        u[0][i] = a[0][i];
    }

    //进行L的第一列的赋值
    for (i = 1; i<n; i++)
    {
        l[i][0] = a[i][0] / u[0][0];
    }

    //计算U的剩下的行数和L的剩下的列数
    for (r = 1; r<n; r++)
    {
        for (i = r; i <n; i++)
        {
            double sum1 = 0;
            for (k = 0; k < r; k++)
            {
                sum1 += l[r][k] * u[k][i];
                //cout << "" << r << "" << sum1 << endl;
            }
            u[r][i] = a[r][i] - sum1;
        }


        if(r!=n)
        for(i=r+1;i<n;i++)
        {
            double sum2 = 0;
              for (k = 0; k<r; k++)
            {
                  sum2 += l[i][k] * u[k][r];
            }
                l[i][r] = (a[i][r] - sum2) / u[r][r];
        }

    }

    double y[n] = { 0 };
    y[0] = b[0];
    for (i = 1; i<n; i++)
    {
        double sum3 = 0;
        for (k = 0; k<i; k++)
            sum3 += l[i][k] * y[k];
        y[i] = b[i] - sum3;
    }

    double x[n] = { 0 };
    x[n - 1] = y[n - 1] / u[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        double sum4 = 0;
        for (k = i + 1; k<n; k++)
            sum4 += u[i][k] * x[k];
        x[i] = (y[i] - sum4) / u[i][i];
    }
    for (i = 0; i<n; i++)
    s[i+1] = x[i];
  //      cout << "x[" << i + 1 << "]=" << x[i] << endl;
    return s;
}

/*
int main()
{
    double a[3][3] = { 1,2,3,2,5,2,3,1,5 };
    double b[3] = { 14,18,24 };
    double x[3] = {0};
    ALU(a, b, x);
 //   cout<<  x[0]<<endl;
  //  cout<<  x[1]<<endl;
   // cout<<  x[2]<<endl;
    return 0;
}  */
