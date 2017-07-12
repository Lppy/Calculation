#include "View/View.h"
#include "View/subview.h"
#include "Common/Params.h"
#include "Common/Notification.h"
#include "ViewModel/ViewModel.h"
#include <QApplication>
#include "iqwidget.h"
#include <memory>
#include <QDebug>

class iModel{

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    shared_ptr<View> pv(new View());
    shared_ptr<Model> pm(new Model());
    shared_ptr<ViewModel> pvm(new ViewModel(pm));

    pm->AddNotification(static_pointer_cast<INotification,ViewModel>(pvm));

    pv->setInputString(pvm->getInputString());
    pvm->AddNotification(static_pointer_cast<INotification,View>(pv));
    pvm->setOutputString(pm->getRes());
    pv->setOutputString(pvm->getOutputString());
    pv->setButtonRun(static_pointer_cast<iEventClass,View>(pv));

    pv->setButtonRunClickCommand(pvm->getButtonRunClickCommand());
    pvm->setPoints(pm->getPoints());
    pv->setPoints(pvm->getPoints());

    pv->show();

    return a.exec();
}