#include "iqwidget.h"
#include "View/View.h"
#include <QDebug>

iDataClass::~iDataClass(){}

iQPushButton::iQPushButton(QWidget *parent, shared_ptr<View> v) : QPushButton(parent)
{
    this->setMouseTracking(true);
    pv=v;
}

void iQPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    pv->execEvent();
}

