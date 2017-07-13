#ifndef VIEW_H_
#define VIEW_H_

#include "Common/Notification.h"
#include "Common/icommand.h"
#include "Common/params.h"
#include "iqwidget.h"
#include <QMainWindow>
#include <memory>
#include <vector>
#include <QString>
#include <string>
using namespace std;

namespace Ui {
class View;
}

class View : public QMainWindow,
             public iEventClass,
             public INotification
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();

    void setInputString(shared_ptr<QString> in);
    void setOutputString(shared_ptr<QString> out);
    void setButtonRun(shared_ptr<iEventClass> iE);
    void setPoints(shared_ptr<Data> p);
    shared_ptr<QString>& getInputString();

    void refreshDisplay();
    void execEvent();
    void show();
    void update(const string& type);
    void setCalculateCommand(shared_ptr<iCommand> command);
private:
    Ui::View *ui;
    shared_ptr<QString> in_ptr, out_ptr;
    shared_ptr<Data> points;
    shared_ptr<iCommand> calculateCommand;
    iQPushButton* button;
    void setWidget();
};

#endif
