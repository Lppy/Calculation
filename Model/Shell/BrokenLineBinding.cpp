#include "BrokenLineBinding.h"
#include "Model/Model.h"

BrokenLineBinding::BrokenLineBinding(Model *m):pm(m)
{

}

void BrokenLineBinding::exec(string &in){
    string str=in.substr(11);
    vector<Point> p=pm->shell_point(str);
    pm->getBrokenLine(p);
}
