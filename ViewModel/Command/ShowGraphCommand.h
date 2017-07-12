#ifndef SHOWGRAPHCOMMAND_H
#define SHOWGRAPHCOMMAND_H
#include "Common/icommand.h"
class ViewModel;
using namespace std;

class ShowGraphCommand:public iCommand
{
private:
    ViewModel* pvm;
 //   shared_ptr<Param> param;
public:
    ShowGraphCommand(ViewModel* vm);
    virtual void exec();
//    virtual void setParam(const shared_ptr<Param> &p);
};

#endif // SHOWGRAPHCOMMAND_H
