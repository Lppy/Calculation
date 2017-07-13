#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H
#include "Common/icommand.h"
#include "Common/params.h"
class ViewModel;
using namespace std;

class UndoCommand:public iCommand
{
private:
    ViewModel* pvm;
public:
    UndoCommand(ViewModel* vm);
    virtual void exec();
};

#endif // UNDOCOMMAND_H
