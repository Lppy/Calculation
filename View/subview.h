#ifndef SUBVIEW_H
#define SUBVIEW_H

#include "iqwidget.h"
#include <memory>

class SubView
{
public:
    SubView(){}
    void show(shared_ptr<iDataClass> iD);

private:
    shared_ptr<iDataClass> iData;

    void paintBrokenline();
    void paintCurve();
};

#endif // SUBVIEW_H
