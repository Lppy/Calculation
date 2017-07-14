#include "Common/params.h"
#include <string.h>
#define MAX_N 30

class Cubic_Spline{
public:
    Cubic_Spline(){}
    ~Cubic_Spline(){}
    vector<Point> cubic_Spline(vector<Point> p, int Type);
private:
    void get_Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);
	double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[]);	
};
