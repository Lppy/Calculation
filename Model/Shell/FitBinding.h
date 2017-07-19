#ifndef FITBINDING_H
#define FITBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class FitBinding:public iBinding
{
private:
    Model* pm;
public:
    FitBinding(Model* m);
    virtual void exec(string &in);
};

#endif // FITBINDING_H
