#ifndef VIEW_H_
#define VIEW_H_

#include "iqwidget.h"
#include <QMainWindow>
#include <QSharedPointer>
#include <QString>

namespace Ui {
class View;
}

class View : public QMainWindow, public iEventClass
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();

    void setInputString(QSharedPointer<QString> in);
    void setOutputString(QSharedPointer<QString> out);
    void setButtonRun(QSharedPointer<iEventClass> iE);

    void refreshDisplay();
    void execEvent();
    void show();

private:
    Ui::View *ui;
    QSharedPointer<QString> in_ptr, out_ptr;
    iQPushButton* button;

    void setWidget();
};
















#endif
