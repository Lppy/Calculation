#include "iqwidget.h"
#include <QDebug>

iEventClass::~iEventClass(){}

iDataClass::~iDataClass(){}

iQPushButton::iQPushButton(QWidget *parent, QSharedPointer<iEventClass> iE) : QPushButton(parent)
{
    this->setMouseTracking(true);
    iEvent = iE;
}
void iQPushButton::mouseMoveEvent(QMouseEvent *event)
{
    QPushButton::mouseMoveEvent(event);
}
void iQPushButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
}
void iQPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    iEvent->execEvent();
}

