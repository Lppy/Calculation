#include "CalculateCommand.h"
#include "ViewModel/viewmodel.h"

CalculateCommand::CalculateCommand(ViewModel* vm):pvm(vm)
{

}

void CalculateCommand::exec(){
    shared_ptr<StringParam> sp= static_pointer_cast<StringParam, Param>(param);
    pvm->Calculate(sp->getString());
}

void CalculateCommand::setParam(const shared_ptr<Param>& p){
    param=p;
}
