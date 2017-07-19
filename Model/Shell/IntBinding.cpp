#include "IntBinding.h"
#include "Model/Model.h"

IntBinding::IntBinding(Model *m):pm(m)
{

}

void IntBinding::exec(string &in){
    double lower,upper;
    pm->shell_integrate(in,lower,upper);
    pm->getIntegral(pm->f,lower,upper,(double)0.01);
}

