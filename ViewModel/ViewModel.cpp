#include "viewmodel.h"

ViewModel::ViewModel(){
    /*command*/
    calculateCommand=static_pointer_cast<iCommand,CalculateCommand>(shared_ptr<CalculateCommand>(new CalculateCommand(this)));
    redoCommand=static_pointer_cast<iCommand,RedoCommand>(shared_ptr<RedoCommand>(new RedoCommand(this)));
    undoCommand=static_pointer_cast<iCommand,UndoCommand>(shared_ptr<UndoCommand>(new UndoCommand(this)));

}

ViewModel::ViewModel(shared_ptr<Model> p_model):pm(p_model)
{
    /*command*/
    calculateCommand=static_pointer_cast<iCommand,CalculateCommand>(shared_ptr<CalculateCommand>(new CalculateCommand(this)));
    redoCommand=static_pointer_cast<iCommand,RedoCommand>(shared_ptr<RedoCommand>(new RedoCommand(this)));
    undoCommand=static_pointer_cast<iCommand,UndoCommand>(shared_ptr<UndoCommand>(new UndoCommand(this)));
}
void ViewModel::setModel(shared_ptr<Model> p_model){
    pm=p_model;
}
shared_ptr<Model>& ViewModel::getModel(){
    return pm;
}
shared_ptr<Data>& ViewModel::getPoints(){
    return points;
}
void ViewModel::setPoints(shared_ptr<Data> p){
    points=p;
}

shared_ptr<QString>& ViewModel::getOutputString(){
    return out;
}

void ViewModel::update(const string& type){
    notify(type);
}

void ViewModel::setOutputString(shared_ptr<QString> out)
{
    this->out = out;
}

void ViewModel::Calculate(string &in){
    pm->Calculate(in);
}

void ViewModel::Redo(){
    pm->Redo();
}

void ViewModel::Undo(){
    pm->Undo();
}

shared_ptr<iCommand> ViewModel::getCalculateCommand(){
    return calculateCommand;
}

shared_ptr<iCommand> ViewModel::getRedoCommand(){
    return redoCommand;
}

shared_ptr<iCommand> ViewModel::getUndoCommand(){
    return undoCommand;
}
