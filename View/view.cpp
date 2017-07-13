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

    QPixmap background(":/Image/background.jpg");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(background));
    this->setPalette(palette);

    QString buttonStyle = "QPushButton{background-color:black;\
            color: white;   border-radius: 5px;  border: 1px groove gray;\
            border-style: outset;}"
            "QPushButton:hover{background-color:#dcdddd; color: black;}"
            "QPushButton:pressed{background-color:white;\
            border-style: inset; }";
    button->setStyleSheet(buttonStyle);

    QTextEdit* text = ui->text;
    text->setFontPointSize(10);
    text->resize(750,550);
    text->move(200,50);
    text->append(QString(in_ptr->data()));
    text->show();

    QTextBrowser* textBrowser = ui->textBrowser;
    textBrowser->setFontPointSize(10);
    textBrowser->resize(750,100);
    textBrowser->move(200,650);
    textBrowser->setText(QString(out_ptr->data()));
    textBrowser->setAlignment(Qt::AlignTop);
    textBrowser->show();
}
void View::show()
{
    button = new iQPushButton(this, shared_ptr<View>(this));
    button->resize(80,35);
    button->move(850,620);
    button->setText("RUN");
    button->show();
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

/*
void View::setButtonRun(shared_ptr<iEventClass> iE)
{
    button = new iQPushButton(this, shared_ptr<iEventClass>(this), iE);
    button->resize(80,35);
    button->move(850,620);
    button->setText("RUN");
    button->show();
}*/

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
        shared_ptr<iDataClass> d(points);
        sw.show(d);
    }
}

void View::setCalculateCommand(shared_ptr<iCommand> command){
    calculateCommand=command;
}

void View::setPoints(shared_ptr<Data> p){
    points=p;
}


