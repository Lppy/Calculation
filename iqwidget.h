#ifndef IQLABLE_H
#define IQLABLE_H

#include <QLabel>
#include <QPushButton>
#include <memory>
using namespace std;
class View;

class iQPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit iQPushButton(QWidget *parent, shared_ptr<View> pv);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    shared_ptr<View> pv;
};

#endif // IQLABLE_H
