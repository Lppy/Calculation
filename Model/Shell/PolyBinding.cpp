#include "PolyBinding.h"
#include "Model/Model.h"

PolyBinding::PolyBinding(Model *m):pm(m)
{

}

void PolyBinding::exec(string &in){
    string polys=in.substr(5);
    pm->resolve_polynomial(polys);
    for(int i=9;i>=0;i--)
        cout<<coefficient[i]<<" ";
    cout<<endl;
    pm->getPolynomialRoot(pm->MAXD,coefficient,(double)0.01);
}
