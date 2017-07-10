#ifndef IQLABLE_H
#define IQLABLE_H

#include <QLabel>
#include <QPushButton>
#include <QSharedPointer>

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
    explicit iQPushButton(QWidget *parent, QSharedPointer<iEventClass> iEV, QSharedPointer<iEventClass> iEVM);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QSharedPointer<iEventClass> iEventForView;
    QSharedPointer<iEventClass> iEventForViewModel;
};

#endif // IQLABLE_H
