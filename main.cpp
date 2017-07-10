#include "View/View.h"
#include "View/subview.h"
#include <QApplication>
#include "iqwidget.h"
#include <QSharedPointer>
#include <QDebug>

class Data : public iDataClass{
public:
    Data(){dataType=Curve;}
    ~Data(){}
};

class iModel{

};

class iViewModel : public iEventClass{
public:
    iViewModel(){
        in = QSharedPointer<QString>(new QString("Input here")) ;
        out = QSharedPointer<QString>(new QString("Output here"));
    }

    void execEvent(){
        *out = *in; //处理数据

        //若需要可视化数据
        SubView sw;
        QSharedPointer<iDataClass> d(new Data());
        sw.show(d);
    }

    QSharedPointer<QString> getInputString(){return in;}
    QSharedPointer<QString> getOutputString(){return out;}
    ~iViewModel(){}

private: //viewmodel层应包含model对象共享指针，供其调用model处理数据
    QSharedPointer<QString> in, out;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    iViewModel iWm;
    View w;

    w.setInputString(iWm.getInputString());
    w.setOutputString(iWm.getOutputString());
    w.setButtonRun(QSharedPointer<iEventClass>(&iWm));

    w.show();

    return a.exec();
}
