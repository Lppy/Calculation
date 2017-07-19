#ifndef COND2BINDING_H
#define COND2BINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class Cond2Binding:public iBinding
{
private:
    Model* pm;
public:
    Cond2Binding(Model* m);
    virtual void exec(string &in);
};
#endif // COND2BINDING_H
