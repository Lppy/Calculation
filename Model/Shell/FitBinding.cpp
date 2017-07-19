#include "FitBinding.h"
#include "Model/Model.h"

FitBinding::FitBinding(Model *m):pm(m)
{

}

void FitBinding::exec(string &in){
    string str=in.substr(4);
    vector<Point> p=pm->shell_point(str);
    pm->getCubicSpline(p,2);
}
