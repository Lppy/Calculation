#ifndef INTBINDING_H
#define INTBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class IntBinding:public iBinding
{
private:
    Model* pm;
public:
    IntBinding(Model* m);
    virtual void exec(string &in);
};



#endif // INTBINDING_H
