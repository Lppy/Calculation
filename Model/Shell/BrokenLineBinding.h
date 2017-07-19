#ifndef BROKENLINEBINDING_H
#define BROKENLINEBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class BrokenLineBinding:public iBinding
{
private:
    Model* pm;
public:
    BrokenLineBinding(Model* m);
    virtual void exec(string &in);
};

#endif // BROKENLINEBINDING_H
