#include "ButtonRunClickCommand.h"
#include "ViewModel/viewmodel.h"

ButtonRunClickCommand::ButtonRunClickCommand(ViewModel* vm):pvm(vm)
{

}

void ButtonRunClickCommand::exec(){
    pvm->execEvent();
}
