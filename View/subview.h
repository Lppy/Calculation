#ifndef SUBVIEW_H
#define SUBVIEW_H

#include "iqwidget.h"
#include <QSharedPointer>

class SubView
{
public:
    SubView(){}
    void show(QSharedPointer<iDataClass> iD);

private:
    QSharedPointer<iDataClass> iData;

    void paintBrokenline();
    void paintCurve();
};

#endif // SUBVIEW_H
