#ifndef CURVEBINDING_H
#define CURVEBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class CurveBinding:public iBinding
{
private:
    Model* pm;
public:
    CurveBinding(Model* m);
    virtual void exec(string &in);
};

#endif // CURVEBINDING_H
