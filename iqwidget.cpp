#include "iqwidget.h"
#include "View/View.h"
#include <QDebug>
#include <QKeyEvent>

iDataClass::~iDataClass(){}

iQPushButton::iQPushButton(QWidget *parent, shared_ptr<View> v) : QPushButton(parent)
{
    this->setMouseTracking(true);
    pv=v;
}

void iQPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    if(this->text()=="RUN")
        pv->execRun();
    else if(this->text()=="REDO")
        pv->execRedo();
    else if(this->text()=="UNDO")
        pv->execUndo();
}

void iQTextEdit::keyPressEvent(QKeyEvent *event)
{
    QTextEdit::keyPressEvent(event);

    if(event->key()&Qt::Key_Enter)
        pv->execRun();
}

