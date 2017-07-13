#ifndef CALCULATECOMMAND_H
#define CALCULATECOMMAND_H
#include "Common/icommand.h"
#include "Common/params.h"
class ViewModel;
using namespace std;

class CalculateCommand:public iCommand
{
private:
    ViewModel* pvm;
    shared_ptr<Param> param;
public:
    CalculateCommand(ViewModel* vm);
    virtual void exec();
    virtual void setParam(const shared_ptr<Param>& p);
};

#endif // CALCULATECOMMAND_H
