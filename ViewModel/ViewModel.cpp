#include "viewmodel.h"

ViewModel::ViewModel(){
    in = shared_ptr<QString>(new QString("Input here"));
    /*command*/
    calculateCommand=static_pointer_cast<iCommand,CalculateCommand>(shared_ptr<CalculateCommand>(new CalculateCommand(this)));
}

ViewModel::ViewModel(shared_ptr<Model> p_model):pm(p_model)
{
    in = shared_ptr<QString>(new QString("Input here"));
    /*command*/
    calculateCommand=static_pointer_cast<iCommand,CalculateCommand>(shared_ptr<CalculateCommand>(new CalculateCommand(this)));

}
void ViewModel::setModel(shared_ptr<Model> p_model){
    pm=p_model;
}
shared_ptr<Model>& ViewModel::getModel(){
    return pm;
}
shared_ptr<vector<Point>>& ViewModel::getPoints(){
    return points;
}
void ViewModel::setPoints(shared_ptr<vector<Point>> p){
    points=p;
}

shared_ptr<QString> ViewModel::getInputString(){
    return in;
}
shared_ptr<QString>& ViewModel::getOutputString(){
    return out;
}

void ViewModel::update(const string& type){
    notify(type);
}
void ViewModel::setInputString(shared_ptr<QString> in)
{
    this->in = in;
}
void ViewModel::setOutputString(shared_ptr<QString> out)
{
    this->out = out;
}

//for test
double ViewModel::f(double x){
    return x;
}

//for test
double ViewModel::ff(double t,double w){
    return w;
}

void ViewModel::Calculate(string &in){
    pm->Calculate(in);
}

shared_ptr<iCommand> ViewModel::getCalculateCommand(){
    return calculateCommand;
}
