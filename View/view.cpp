#include "View/View.h"
#include "View/subview.h"
#include "ui_View.h"
#include "iqwidget.h"
#include <QTextEdit>
#include <QScrollBar>
#include <QTextBrowser>

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
}
View::~View()
{
    delete ui;
    delete button;
}
void View::setWidget()
{
    this->setFixedSize(1000,800);
    this->setWindowTitle("Calculator");

    QPalette bg = palette();
    bg.setColor(QPalette::Background, QColor(255,255,255,255));
    bg.setColor(QPalette::Foreground, QColor(0,0,0,255));

    QTextEdit* text = ui->text;
    text->setFontPointSize(10);
    text->resize(750,550);
    text->move(200,50);
    text->append(QString(in_ptr->data()));
    text->show();

    QTextBrowser* label = ui->textBrowser;
    label->setFontPointSize(10);
    label->resize(750,100);
    label->move(200,650);
    label->setText(QString(out_ptr->data()));
    label->setAlignment(Qt::AlignTop);

    label->show();
}
void View::show()
{
    setWidget();
    QMainWindow::show();
}

void View::setInputString(shared_ptr<QString> in)
{
    in_ptr = in;
}
void View::setOutputString(shared_ptr<QString> out)
{
    out_ptr = out;
}

void View::setButtonRun(shared_ptr<iEventClass> iE)
{
    button = new iQPushButton(this, shared_ptr<iEventClass>(this), iE);
    button->resize(80,35);
    button->move(850,620);
    button->setText("RUN");
    button->show();
}

void View::refreshDisplay()
{
    QTextBrowser* label = ui->textBrowser;
    label->setText(QString(out_ptr->data()));
}

void View::execEvent(){
    *in_ptr = ui->text->toPlainText();
    string str=ui->text->toPlainText().toStdString();
    shared_ptr<StringParam> sp=shared_ptr<StringParam>(new StringParam);
    sp->setString(str);
    calculateCommand->setParam(static_pointer_cast<Param,StringParam>(sp));
    calculateCommand->exec();
}

void View::update(const string& type){
    if(type=="text"){
        refreshDisplay();
    }
    else if(type=="graph"){
        SubView sw;
        shared_ptr<iDataClass> d(new Data(*points));
        sw.show(d);
    }
}

void View::setCalculateCommand(shared_ptr<iCommand> command){
    calculateCommand=command;
}

void View::setPoints(shared_ptr<vector<Point>> p){
    points=p;
}


