#ifndef ODEBINDING_H
#define ODEBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class OdeBinding:public iBinding
{
private:
    Model* pm;
public:
    OdeBinding(Model* m);
    virtual void exec(string &in);
};

#endif // ODEBINDING_H
