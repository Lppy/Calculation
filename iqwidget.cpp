#include "iqwidget.h"
#include <QDebug>

iEventClass::~iEventClass(){}

iDataClass::~iDataClass(){}

iQPushButton::iQPushButton(QWidget *parent, shared_ptr<iEventClass> iEV, shared_ptr<iEventClass> iEVM) : QPushButton(parent)
{
    this->setMouseTracking(true);
    iEventForView = iEV;
    iEventForViewModel = iEVM;
}

void iQPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);

    iEventForView->execEvent();
  //  iEventForViewModel->execEvent();
  //  iEventForView->refreshDisplay();
}

