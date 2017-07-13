#ifndef PARAMS_H
#define PARAMS_H
#include "./Model/Function/matrix.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <QString>

using namespace std;
typedef pair<double,double> Point;

class iDataClass //data's abstract class
{
public:
    virtual ~iDataClass() = 0;

    enum { Brokenline, Curve } dataType;
};

class Data : public iDataClass{
private:
    vector<Point> point;
public:
    Data(){}
    Data(vector<Point>& point):point(point)
    {
       dataType=Curve;
    }
    void setPoint(vector<Point>& p){
        point=p;
    }
    vector<Point>& getPoint(){
        return point;
    }
    ~Data(){}
};

class Action{
private:
    Data data;
    QString str;
public:
    enum ActionType {POINT,STRING} type;
    Action(){}
    Action(const Data& d):data(d),type(POINT){}
    Action(const QString& s):str(s),type(STRING){}
    ~Action(){}
    void setData(const Data& d){data=d;}
    void setStr(const QString& s){str=s;}
    Data getData() const{return data;}
    QString getStr() const{return str;}
    void setActionType(ActionType t){type=t;}
    ActionType& getType(){return type;}
};

class Param{

};

class StringParam:public Param{
private:
    string input;
public:
    void setString(const string& in){
        input=in;
    }
    string& getString(){
        return input;
    }
};




#endif // PARAMS_H
