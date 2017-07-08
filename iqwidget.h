#ifndef IQLABLE_H
#define IQLABLE_H

#include <QLabel>
#include <QPushButton>
#include <QSharedPointer>

class iEventClass //event's abstract class
{
public:
    virtual void execEvent() = 0;
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
    explicit iQPushButton(QWidget *parent, QSharedPointer<iEventClass> iE);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QSharedPointer<iEventClass> iEvent;
};

#endif // IQLABLE_H
