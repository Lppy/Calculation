#include "RedoCommand.h"
#include "ViewModel/viewmodel.h"

RedoCommand::RedoCommand(ViewModel* vm):pvm(vm)
{

}

void RedoCommand::exec(){
    pvm->Redo();
}
