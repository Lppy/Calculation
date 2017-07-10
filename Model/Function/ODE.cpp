#include "ODE.h"
#include "math.h"


ODE::ODE()
{
}


ODE::~ODE()
{
}

vector<Point> ODE::ode45(double(*f)(double t0, double w0), double a, double b, const int step, double ya)
{
	vector<Point> res;
	double h = fabs(b - a) / step;
	double t = a, w = ya , k[4];
	res.push_back(Point(t,w));
	for (int i = 1;i <= step;i++) {
		k[0] = h*f(t, w);
		k[1] = h*f(t + 0.5*h, w + 0.5*k[0]);
		k[2] = h*f(t + 0.5*h, w + 0.5*k[1]);
		k[3] = h*f(t + h, w + k[2]);
		w += (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
		t += h;
		res.push_back(Point(t, w));
	}
	return res;
}
