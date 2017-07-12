#include "ShowGraphCommand.h"
#include "ViewModel/viewmodel.h"

ShowGraphCommand::ShowGraphCommand(ViewModel* vm):pvm(vm){

}

void ShowGraphCommand::exec(){
    pvm->showGraph();
}
