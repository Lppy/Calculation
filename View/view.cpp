#include "View/View.h"
#include "View/subview.h"
#include "ui_View.h"
#include "iqwidget.h"
#include <QTextEdit>
#include <QScrollBar>
#include <QTextBrowser>
#include <QKeyEvent>


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
}
View::~View()
{
    delete ui;
    delete buttonRun;
    delete buttonRedo;
    delete buttonUndo;
    delete text;
}
void View::setWidget()
{
    this->setFixedSize(600,400);
    this->setWindowTitle("Calculator");
    this->setWindowOpacity(0.92);

    QPixmap background(":/Image/background.jpg");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(background));
    this->setPalette(palette);

    QString buttonStyle = "QPushButton{background-color:black;\
            color: white;   border-radius: 15px;  border: 1px groove gray;\
    border-style: outset;}"
    "QPushButton:hover{background-color:#dcdddd; color: black;}"
    "QPushButton:pressed{background-color:white;\
    border-style: inset; }";

    buttonRun = new iQPushButton(this, shared_ptr<View>(this));
    buttonRun->resize(80,35);
    buttonRun->move(450,220);
    buttonRun->setText("RUN");
    buttonRun->show();
    buttonRun->setStyleSheet(buttonStyle);

    buttonUndo = new iQPushButton(this, shared_ptr<View>(this));
    buttonUndo->resize(80,35);
    buttonUndo->move(250,220);
    buttonUndo->setText("UNDO");
    buttonUndo->show();
    buttonUndo->setStyleSheet(buttonStyle);

    buttonRedo = new iQPushButton(this, shared_ptr<View>(this));
    buttonRedo->resize(80,35);
    buttonRedo->move(350,220);
    buttonRedo->setText("REDO");
    buttonRedo->show();
    buttonRedo->setStyleSheet(buttonStyle);


    //iQTextEdit* text = ui->text;
    text = new iQTextEdit(this);
    text->setView(shared_ptr<View>(this));
    text->setFontPointSize(15);
    text->resize(450,160);
    text->move(100,50);
    text->append(QString("Input here"));
    text->show();
    QString textStyle= "QTextEdit {\
            border: 1px solid rgb(111, 156, 207);"
            "color: rgb(70, 71, 73);\
            background: rgb(228, 228, 228);\
    }";
    text->setStyleSheet(textStyle);


    QTextBrowser* textBrowser = ui->textBrowser;
    textBrowser->setFontPointSize(15);
    textBrowser->resize(450,100);
    textBrowser->move(100,250);
    textBrowser->setText(QString(out_ptr->data()));
    textBrowser->setAlignment(Qt::AlignTop);
    textBrowser->show();
    textBrowser->setStyleSheet(textStyle);
}

void View::show()
{
    setWidget();
    QMainWindow::show();
}

void View::setOutputString(shared_ptr<QString> out)
{
    out_ptr = out;
}

void View::refreshDisplay()
{
    QTextBrowser* label = ui->textBrowser;
    label->setText(QString(out_ptr->data()));
}

void View::execRun(){
   // *in_ptr = text->toPlainText();
    string str = text->toPlainText().toStdString();
    shared_ptr<StringParam> sp=shared_ptr<StringParam>(new StringParam);
    sp->setString(str);
    calculateCommand->setParam(static_pointer_cast<Param,StringParam>(sp));
    calculateCommand->exec();
}

void View::execRedo(){
    redoCommand->exec();
}

void View::execUndo(){
    undoCommand->exec();
}

void View::update(const string& type){   
    if(type=="text"){
        refreshDisplay();
    }
    else if(type=="graph"){
        refreshDisplay();
        SubView sw;
        shared_ptr<iDataClass> d(points);
        sw.show(d);
    }
}

void View::setCalculateCommand(shared_ptr<iCommand> command){
    calculateCommand=command;
}

void View::setRedoCommand(shared_ptr<iCommand> command){
    redoCommand=command;
}

void View::setUndoCommand(shared_ptr<iCommand> command){
    undoCommand=command;
}

void View::setPoints(shared_ptr<Data> p){
    points=p;
}



