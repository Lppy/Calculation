#include "CurveBinding.h"
#include "Model/Model.h"

CurveBinding::CurveBinding(Model *m):pm(m)
{

}

void CurveBinding::exec(string &in){
    string str=in.substr(6);
    vector<Point> p=pm->shell_point(str);
    pm->getCurve(p);
}
