#include "subview.h"
#include "View/qcustomplot/qcustomplot.h"
#include <QDebug>

void SubView::show(QSharedPointer<iDataClass> iD)
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


    const int dataCount = 200;
    const int dataFactorialCount = 21;
    QVector<QCPGraphData> dataLinear(dataCount), dataMinusSinExp(dataCount), dataPlusSinExp(dataCount), dataFactorial(dataFactorialCount);
    for (int i=0; i<dataCount; ++i)
    {
      dataLinear[i].key = i;
      dataLinear[i].value = (int)dataLinear[i].key%2==0?10:19;
      dataMinusSinExp[i].key = i;//10.0;
      dataMinusSinExp[i].value = -qSin(dataMinusSinExp[i].key)*qExp(dataMinusSinExp[i].key);
      dataPlusSinExp[i].key = i;//10.0;
      dataPlusSinExp[i].value = qSin(dataPlusSinExp[i].key)*qExp(dataPlusSinExp[i].key);
    }
    for (int i=0; i<dataFactorialCount; ++i)
    {
      dataFactorial[i].key = i;
      dataFactorial[i].value = 1.0;
      for (int k=1; k<=i; ++k) dataFactorial[i].value *= k; // factorial
    }


    QCustomPlot *customPlot = new QCustomPlot;
    // 生成数据，画出的是抛物线
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // 添加数据曲线（一个图像可以有多个数据曲线）
    customPlot->addGraph();

    // graph(0);可以获取某个数据曲线（按添加先后排序）
    // setData();为数据曲线关联数据
    customPlot->graph(0)->data()->set(dataLinear);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine); //形状 折线

    customPlot->xAxis->setLabel("x"); //坐标轴标签
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0, 20.0); //坐标轴的范围
    customPlot->yAxis->setRange(0, 20.0);

    //customPlot->legend->setVisible(true); //图示
    //customPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
    //customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    //customPlot->replot(); //重画图像

    customPlot->resize(500,500);
    customPlot->show();
}

void SubView::paintCurve()
{
    qDebug()<<"Curve"<<endl;

    QCustomPlot *customPlot = new QCustomPlot;

    int dataCount = 20;
    QVector<QCPGraphData> x(dataCount);
    double min = 0, max = 0;
    for (int i=0; i<dataCount; ++i)
    {
      x[i].key = i;
      x[i].value = i*i*i - 7*i*i - i + 10;
      if(x[i].value>max) max = x[i].value;
      if(x[i].value<min) min = x[i].value;
    }

    customPlot->addGraph();
    customPlot->graph(0)->data()->set(x);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0, dataCount - 1);
    customPlot->yAxis->setRange(min, max);

    customPlot->resize(500,500);
    customPlot->show();
}
