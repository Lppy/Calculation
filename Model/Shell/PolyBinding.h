#ifndef POLYBINDING_H
#define POLYBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class PolyBinding:public iBinding
{
private:
    Model* pm;
public:
    PolyBinding(Model* m);
    virtual void exec(string &in);
};

#endif // POLYBINDING_H
