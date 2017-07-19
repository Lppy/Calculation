#ifndef MATRIXBINDING_H
#define MATRIXBINDING_H
#include "iBinding.h"
#include "Common/params.h"
class Model;

class MatrixBinding:public iBinding
{
private:
    Model* pm;
public:
    MatrixBinding(Model* m);
    virtual void exec(string &in);
};

#endif // MATRIXBINDING_H
