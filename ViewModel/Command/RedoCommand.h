#ifndef REDOCOMMAND_H
#define REDOCOMMAND_H
#include "Common/icommand.h"
#include "Common/params.h"
class ViewModel;
using namespace std;

class RedoCommand:public iCommand
{
private:
    ViewModel* pvm;
public:
    RedoCommand(ViewModel* vm);
    virtual void exec();
};

#endif // REDOCOMMAND_H
