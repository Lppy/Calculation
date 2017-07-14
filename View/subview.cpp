#include "subview.h"
#include "View/qcustomplot/qcustomplot.h"
#include <QDebug>

void SubView::show(shared_ptr<iDataClass> iD)
{
    iData = iD;
    switch(iData->dataType)
    {
    case iDataClass::Brokenline:
        paintBrokenline();
        break;
    case iDataClass::Curve:
        paintCurve();
        break;
    }
}
void SubView::paintBrokenline()
{
    qDebug()<<"Brokenline"<<endl;

    QCustomPlot *customPlot = new QCustomPlot;

    shared_ptr<Data> dp=static_pointer_cast<Data,iDataClass>(iData);
    vector<Point> point=dp->getPoint();
    int dataCount=point.size();
    QVector<QCPGraphData> x(dataCount);
    double minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (int i=0; i<dataCount; ++i)
    {
      x[i].key=point[i].first;
      x[i].value=point[i].second;
      if(x[i].value>maxY) maxY = x[i].value;
      if(x[i].value<minY) minY = x[i].value;
      if(x[i].key>maxX) maxX = x[i].key;
      if(x[i].key<minX) minX = x[i].key;
    }

    customPlot->addGraph();
    customPlot->graph(0)->data()->set(x);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);

    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");

    customPlot->xAxis->setRange(minX, maxX);
    customPlot->yAxis->setRange(minY, maxY);

    /*

    //customPlot->legend->setVisible(true); //图示
    //customPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
    //customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    */

    customPlot->resize(500,500);
    customPlot->show();
}

void SubView::paintCurve()
{
    qDebug()<<"Curve"<<endl;

    QCustomPlot *customPlot = new QCustomPlot;

    shared_ptr<Data> dp=static_pointer_cast<Data,iDataClass>(iData);
    vector<Point> point=dp->getPoint();
    int dataCount=point.size();
    QVector<QCPGraphData> x(dataCount);
    double minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (int i=0; i<dataCount; ++i)
    {
      x[i].key=point[i].first;
      x[i].value=point[i].second;
      if(x[i].value>maxY) maxY = x[i].value;
      if(x[i].value<minY) minY = x[i].value;
      if(x[i].key>maxX) maxX = x[i].key;
      if(x[i].key<minX) minX = x[i].key;
    }

    customPlot->addGraph();
    customPlot->graph(0)->data()->set(x);

    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");

    customPlot->xAxis->setRange(minX, maxX);
    customPlot->yAxis->setRange(minY, maxY);

    customPlot->resize(500,500);
    customPlot->show();
}
