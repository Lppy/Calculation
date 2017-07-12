#ifndef PARAMS_H
#define PARAMS_H
#include "iqwidget.h"
#include "./Model/Function/matrix.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>

using namespace std;
typedef pair<double,double> Point;

class Data : public iDataClass{
private:
    vector<Point> point;
public:
    Data(vector<Point>& point):point(point)
    {
       dataType=Curve;
    }
    ~Data(){}
};




#endif // PARAMS_H
