#ifndef CONDINFBINDING_H
#define CONDINFBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class CondInfBinding:public iBinding
{
private:
    Model* pm;
public:
    CondInfBinding(Model* m);
    virtual void exec(string &in);
};

#endif // CONDINFBINDING_H
