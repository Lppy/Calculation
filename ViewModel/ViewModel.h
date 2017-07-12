#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "Common/Notification.h"
#include "Command/ShowGraphCommand.h"
#include "Command/ButtonRunClickCommand.h"
#include "Model/Model.h"
#include <memory>

class ViewModel: public Proxy_Notification, //public iEventClass,
                 public INotification
{
public:
    ViewModel(shared_ptr<Model> p_model);
    void setModel(shared_ptr<Model> p_model);
    shared_ptr<Model>& getModel();
    shared_ptr<vector<Point>>& getPoints();
    void setPoints(shared_ptr<vector<Point>> p);

    shared_ptr<QString> getInputString();
    shared_ptr<QString>& getOutputString();

    void update(const string& type);
    void setInputString(shared_ptr<QString> in);
    void setOutputString(shared_ptr<QString> out);
    void showGraph();

    //for test
    static double f(double x);

    //for test
    static double ff(double t,double w);

    void execEvent();

    shared_ptr<iCommand> getButtonRunClickCommand();

    ~ViewModel(){}
private:
    shared_ptr<Model> pm;
    shared_ptr<QString> in, out;
    shared_ptr<vector<Point>> points;
    shared_ptr<iCommand> showGraphCommand,buttonRunClickCommand;
};

#endif // VIEWMODEL_H
