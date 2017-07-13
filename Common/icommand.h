#ifndef ICOMMAND_H
#define ICOMMAND_H
#include "Common/Params.h"
#include <memory>
class ViewModel;

/*base Class of command*/
class iCommand{
protected:
public:
    virtual void setParam(const shared_ptr<Param> &p){}
    virtual void exec()=0;
};

#endif // ICOMMAND_H
