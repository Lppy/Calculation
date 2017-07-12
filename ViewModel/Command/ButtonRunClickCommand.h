#ifndef BUTTONRUNCLICKCOMMAND_H
#define BUTTONRUNCLICKCOMMAND_H
#include "Common/icommand.h"
class ViewModel;
using namespace std;

class ButtonRunClickCommand:public iCommand
{
private:
    ViewModel* pvm;
 //   shared_ptr<Param> param;
public:
    ButtonRunClickCommand(ViewModel* vm);
    virtual void exec();
};

#endif // BUTTONRUNCLICKCOMMAND_H
