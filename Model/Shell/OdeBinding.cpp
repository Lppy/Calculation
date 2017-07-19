#include "OdeBinding.h"
#include "Model/Model.h"
#include <iostream>
using namespace std;

OdeBinding::OdeBinding(Model *m):pm(m)
{

}

void OdeBinding::exec(string &in){
    double lower,upper,ya;
    string sin=in.substr(4);
    cout<<"here1"<<endl;
    pm->shell_ode(sin,lower,upper,ya);
    int step=(upper-lower)/0.2;
    cout<<"here2"<<endl;
    pm->getODE(pm->ff,lower,upper,step,ya);
    cout<<"there"<<endl;
}

