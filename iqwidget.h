#ifndef IQLABLE_H
#define IQLABLE_H

#include <QLabel>
#include <QPushButton>
#include <memory>
using namespace std;

class iEventClass //event's abstract class
{
public:
    virtual void execEvent() = 0;
    virtual void refreshDisplay(){}
    virtual ~iEventClass() = 0;
};

class iDataClass //data's abstract class
{
public:
    virtual ~iDataClass() = 0;

    enum { Brokenline, Curve } dataType;
};

class iQPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit iQPushButton(QWidget *parent, shared_ptr<iEventClass> iEV, shared_ptr<iEventClass> iEVM);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    shared_ptr<iEventClass> iEventForView;
    shared_ptr<iEventClass> iEventForViewModel;
};

#endif // IQLABLE_H
