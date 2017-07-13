#include "UndoCommand.h"
#include "ViewModel/viewmodel.h"

UndoCommand::UndoCommand(ViewModel* vm):pvm(vm)
{

}

void UndoCommand::exec(){
    pvm->Undo();
}
