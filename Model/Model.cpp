#include "Model.h"
#include <sstream>


Model::Model()
{
    this->res=shared_ptr<QString>(new QString("res"));
    this->points=shared_ptr<Data>(new Data);
}

Model::~Model()
{
}

//for test
double Model::f(double x){
    return x;
}

//for test
double Model::ff(double t,double w){
    return w-t*t+1;
}

void Model::Calculate(string &in){
    //解释器处理字符串in，并调用model中的计算函数
    cout<<"in Model:Calculate "<<in<<endl;
    int n=2;
    double c[3]={1,2,1};
    double eps=0.1;
  //  getPolynomialRoot(n,c,eps);
  //getIntegral(f,(double)1,(double)2,(double)0.0001);
    getODE(ff,(double)0,(double)2,(double)20,(double)0.5);
}


void Model::getPolynomialRoot(const int n, const double c[], const double EPS)
{
    Root_of_Polynomial rp;
    double dres = rp.Polynomial_Root(n, c, EPS);
    *(this->res)=QString::fromStdString(double2string(dres));
    cout<<"getPolyRoot "<<(*(this->res)).toStdString()<<endl;
    string s="text";
    this->notify(s);
}

void Model::getCond_2(Matrix a)
{
    if (a.isSquare()) {
        double aa[MAXM][MAXM];
        a.to2DArray(aa);
        Cond cond;
        double dres = cond.cond_2(aa, a.getCol());
        *(this->res)=QString::fromStdString(double2string(dres));
    }
    else {
        QString err = "not square matrix";
        *(this->res)=err;
    }
    string s="text";
    this->notify(s);
}

void Model::getCond_inf(Matrix a)
{
    if (a.isSquare()) {
        double aa[MAXM][MAXM];
        a.to2DArray(aa);
        Cond cond;
        double dres = cond.cond_inf(aa, a.getCol());
        *(this->res)=QString::fromStdString(double2string(dres));
    }
    else {
        QString err = "not square matrix";
        *(this->res)=err;
    }
    string s="text";
    this->notify(s);
}

void Model::getODE(double(*f)(double t0, double w0), double a, double b, const int step, double ya)
{
    ODE ode;
    vector<Point> p = ode.ode45(f, a, b, step, ya);
    points->setPoint(p);
    string s="graph";
    cout<<s<<endl;
    vector<Point> pdata=points->getPoint();
    for(auto it=pdata.begin();it!=pdata.end();it++)
        cout<<"p "<<it->first<<" "<<it->second<<endl;
    this->notify(s);
}

void Model::getIntegral(double(*f)(double x), const double a, const double b, const double eps)
{
    Integral inte;
    double dres = inte.Romberg(f, a, b, eps);
    *(this->res)=QString::fromStdString(double2string(dres));
    string s="text";
    this->notify(s);
}

void Model::getIntegral(double(*f)(double x), const double a, const double b)
{
    Integral inte;
    double dres = inte.quad(f, a, b);
    *(this->res)=QString::fromStdString(double2string(dres));
    string s="text";
    this->notify(s);
}

void Model::getEigenvalue(Matrix a)
{

}

void Model::getMatrixRoot(Matrix a)
{
    string dres;
    if (a.isSquare()) {
        double aa[MAXM][MAXM],b[MAXM];
        a.to2DArray(aa);
        LU lu;
        lu.LU_decom(a.getCol(), aa, b);
        dres = "[";
        for (int i = 0;i < a.getCol();i++)
            dres += double2string(b[i]) + ",";
        dres.back() = ']';
    }
    else {
        dres = "not square matrix";
    }
    *(this->res)=QString::fromStdString(dres);
    string s="MatrixRoot";
    this->notify(s);

}

string Model::double2string(double res)
{
    ostringstream os;
    if (os << res)
        return os.str();
    return "invalid conversion";
}

shared_ptr<Data>& Model::getPoints(){
    return points;
}

shared_ptr<QString>& Model::getRes(){
    return res;
}
