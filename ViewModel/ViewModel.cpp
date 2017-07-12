#include "viewmodel.h"

ViewModel::ViewModel(shared_ptr<Model> p_model):pm(p_model)
{
    in = shared_ptr<QString>(new QString("Input here"));
    out = shared_ptr<QString>(new QString("Output here"));
    points=shared_ptr<vector<Point>>(new vector<Point>);
    /*command*/
    showGraphCommand=static_pointer_cast<iCommand,ShowGraphCommand>(shared_ptr<ShowGraphCommand>(new ShowGraphCommand(this)));
    buttonRunClickCommand=static_pointer_cast<iCommand,ButtonRunClickCommand>(shared_ptr<ButtonRunClickCommand>(new ButtonRunClickCommand(this)));

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
void ViewModel::showGraph(){

}

//for test
double ViewModel::f(double x){
    return x;
}

//for test
double ViewModel::ff(double t,double w){
    return w;
}

void ViewModel::execEvent(){
    int n=2;
    double c[3]={1,2,1};
    double eps=0.1;
  //  pm->getPolynomialRoot(n,c,eps);
    pm->getIntegral(f,(double)1,(double)2,(double)0.0001);
//     pm->getODE(ff,(double)1,(double)2,(double)19,(double)0);

}

shared_ptr<iCommand> ViewModel::getButtonRunClickCommand(){
    return buttonRunClickCommand;
}
