#include "Model.h"
#include <sstream>
#include <cstdio>
map<string, Matrix> matrix_table;
double coefficient[10];

Model::Model()
{
    this->res=shared_ptr<QString>(new QString("res"));
    this->points=shared_ptr<Data>(new Data);
    pos=-1;
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

double Model::poly(double x){
    double pow=1,res=0;
    for(int i=0;i<10;i++){
        res+=coefficient[i]*pow;
        pow*=x;
    }
    return res;
}

void Model::Calculate(string &in){

   // main();

    //解释器处理字符串in，并调用model中的计算函数
    cout<<"in Model:Calculate "<<in<<endl;
    int n=2;
    double c[3]={1,2,1};
    double eps=0.1;
    vector<vector<double>> AA,bb;
    AA.resize(2);AA[0].resize(2);AA[1].resize(2);bb.resize(2);
    bb[0].resize(1);bb[1].resize(1);
    AA[0][0]=1;AA[0][1]=1;AA[1][0]=2;AA[1][1]=3;
    bb[0][0]=2;bb[1][0]=5;
    Matrix A(AA),b(bb);
    //data for test
    memset(coefficient,0,10*sizeof(double));  //clear coefficient
    if(in.substr(0,12)=="solve Poly"){
        string polys=in.substr(6);
        resolve_polynomial(polys);
        getPolynomialRoot(MAXD,coefficient,(double)0.01);
    } else if (in.substr(0, 4) == "d/dx") {
        // 求导
        shell_derivative(in);
    }
    else if(in.substr(0,12)=="solve Matrix"){
        getMatrixRoot(A,b);
        cout<<res->toStdString()<<endl;
    }
    else if(in.substr(0,3)=="int"){
        double lower,upper;
        shell_integrate(in,lower,upper);
        getIntegral(poly,lower,upper,(double)0.01);
    }
    else if(in.substr(0,5)=="Cond2"){
        string::size_type start;
        if((start = in.find('[')) != in.npos){
            istringstream is(in.substr(start + 1));
            string entry=in.substr(6);
            Matrix m=shell_save_matrix(entry,is);
            getCond_2(m);
        }
    }
    else if(in.substr(0,7)=="CondInf"){
        string::size_type start;
        if((start = in.find('[')) != in.npos){
            istringstream is(in.substr(start + 1));
            string entry=in.substr(8);
            Matrix m=shell_save_matrix(entry,is);
            cout<<"in Model:before CondInf "<<m.getRow()<<" "<<m.getCol()<<endl;
            getCond_inf(m);
        }
    } else {
        baseInterpreter calc(in);
        calc.output(cout);
    }
   // else if(in.substr()=="dy")
//        getODE(ff,(double)0,(double)5,(double)20,(double)0.5);
}

void Model::Redo(){
    if(pos==DoneList.size()-1)
        cout<<"pos==size-1"<<endl;
    else{
        pos++;
        auto a=DoneList[pos];
        DisplayAction(a);
    }
}

void Model::Undo(){
    if(pos==-1)
        cout<<"pos=-1"<<endl;
    else if (pos==0){
        pos--;
        *res="";
        string s="text";
        this->notify(s);
    }
    else{
        pos--;
        auto a=DoneList[pos];
        DisplayAction(a);
    }
}

void Model::DisplayAction(const Action& a){
    string s;
    switch(a.type){
    case Action::ActionType::STRING:
        *res=a.getStr();
        s="text";
        break;
    case Action::ActionType::POINT:
        *points=a.getData();
        *res="";
        s="graph";
        break;
    }
    this->notify(s);
}

void Model::getPolynomialRoot(const int n, const double c[], const double EPS)
{
    Root_of_Polynomial rp;
    double dres = rp.Polynomial_Root(n, c, EPS);
    *(this->res)=QString::fromStdString(double2string(dres));
    DoneList.push_back(Action(*res));
    pos++;
    cout<<"getPolyRoot "<<(*(this->res)).toStdString()<<endl;
    for(const auto it:DoneList){
        cout<<"~~"<<DoneList.size()<<endl;
        if(it.type==Action::ActionType::STRING){
            cout<<"@@"<<endl;
            cout<<it.getStr().toStdString()<<endl;
        }
        else cout<<"!!"<<endl;
    }
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
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);
}

void Model::getCond_inf(Matrix a)
{
    cout<<"in Model::getCond_inf"<<endl;
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
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);
}

void Model::getODE(double(*f)(double t0, double w0), double a, double b, const int step, double ya)
{
    ODE ode;
    vector<Point> p = ode.ode45(f, a, b, step, ya);
    points->setPoint(p);
    DoneList.push_back(Action(p));
    pos++;
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
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);
}

void Model::getIntegral(double(*f)(double x), const double a, const double b)
{
    Integral inte;
    double dres = inte.quad(f, a, b);
    *(this->res)=QString::fromStdString(double2string(dres));
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);
}

/*
void Model::getEigenvalue(Matrix a)
{
    Eigenvalue eigen;
	double* tempresult;
	int n;
	bool t;
	n = a.getCol();
	double* dres;
	t = eigen.MatrixEigenValue(a, n, 1000, dres);
	if (t) {
        *(this->res) = QString::fromStdString(double2string(&dres));
        DoneList.push_back(Action(*res));
        pos++;
		string s = "text";
		this->notify(s);
     }
    else
        cout<<"no such eigenvalue"<<endl;
}
*/
    
void Model::getMatrixRoot(Matrix a, Matrix b)
{
    string dres;
    if (a.isSquare()) {
        double aa[MAXM][MAXM],bb[MAXM];
        a.to2DArray(aa);
        b.to1DArray(bb);
        LU lu;
        lu.LU_decom(a.getCol(), aa, bb);
        dres = "[";
        for (int i = 0;i < a.getCol();i++)
            dres += double2string(bb[i]) + ",";
        dres.back() = ']';
    }
    else {
        dres = "not square matrix";
    }
    *(this->res)=QString::fromStdString(dres);
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);

}

/*
void Model::CurveFitting(double* x, double* y, size_t length, int PolyN)
{
    Fit fit;
    fit.polyfit(x, y, length,PolyN, true);
    double* dres;
    fit.getFactor(dres);
    *(this->res)=QString::fromStdString(double2string(&dres));
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
    this->notify(s);
}
*/

string Model::double2string(double res)
{
    ostringstream os;
    if (os << res)
        return os.str();
    return "invalid conversion";
}

double Model::string2double(string str){
    istringstream iss(str);
    double  x;
    if(iss >> x) return x;
    else return 0.0;
}

shared_ptr<Data>& Model::getPoints(){
    return points;
}

shared_ptr<QString>& Model::getRes(){
    return res;
}


bool Model::is_legal_param(const string &param_name) {
    int end, i;
    for (i = param_name.length() - 1; i >= 0; i--)
        if(!isspace(param_name[i]))
            break;
    end = i;
    for (i = 0; i < end; i++)
        if(!isalnum(param_name[i]))
            return false;
    return true;
}

Matrix Model::shell_save_matrix(string &in, istringstream &is) {
    // 有矩阵定义标志
    cout<<"1";
    string param_name;
    int row_num = 1, i;
    char ch;
    double tmp_num;

    param_name = in.substr(0, in.find('='));
    if (!is_legal_param(param_name))
        throw calc_error("illegal param name");
    // 解析矩阵
    // a = [ 1 2 3 4 5; 2 3 4 5 6; 3 4 5 6 7; 4 5 6 7 8]
    // fda921fs=[1,2,3;2,4,5]
    vector<vector<double>> data;
    vector<double> row;
    for (i = 0; i < in.length(); i++)
        if (in[i] == ';')
            row_num++;
    for (i = 0; i < row_num; i++) {
        row.clear();
        while (true) {
            if (is.get(ch)) {
                if(ch == ',' || isspace(ch))
                    continue;
                if (ch == ';' || ch == ']')
                    break;
                is.putback(ch);
            }
            is >> tmp_num;
            row.push_back(tmp_num);
        }
        data.push_back(row);
    }
    // 存储矩阵
    cout<<"in Matrix "<<data.size()<<" "<<data[0].size()<<endl;
    Matrix m(data);
    cout<<"in Matrix "<<m.getRow()<<" "<<m.getCol()<<endl;
    m.print();
    matrix_table[param_name] = m;
    return m;
}

void Model::shell_derivative(string &in) {
    // d/dx (3x^4-123) at x=-123.255
    string::size_type end;
    if ((end = in.find("at x=")) == in.npos)
        throw calc_error("must assign x");
    string func_str = in.substr(5, end - 5);

    resolve_polynomial(func_str);
    double where = atof(in.substr(end + 5).c_str());
    // to be done
    // 调用求导的函数:where就是所要求导的地方，f函数的系数已经解析完
}

//int 1x^3+2x^1+2 (1,2)
void Model::shell_integrate(string &in,double &lower,double &upper) {
    size_t lbrack=in.find("(");
    size_t comma=in.find(",");
    size_t rbrack=in.find(")");
    if(lbrack==string::npos||comma==string::npos||rbrack==string::npos)
        throw gram_error("need boundary limit in integration");
    string polys=in.substr(4,lbrack-4);
    string lowstr=in.substr(lbrack+1,comma-lbrack-1);
    string upstr=in.substr(comma+1,rbrack-comma-1);
    cout<<"in model:int "<<polys<<" * "<<lowstr<<" * "<<upstr<<endl;
    lower=string2double(lowstr);
    upper=string2double(upstr);
    resolve_polynomial(polys);
}

void Model::resolve_polynomial(string &func_str) {
    istringstream is(func_str);
    double co;
    int exp;
    char ch;

    while (is.get(ch)) {
        if (isspace(ch))
            continue;
        if (isdigit(ch) || ch == '-') {
            is.putback(ch);
            is >> co;
        } else if (ch == 'x') {
            co = 1;
        } else {
            throw calc_error("illegal char");
        }
        is.get(ch);
        switch (ch) {
            case 'x':
                is.get(ch);
                if (ch == '^')
                    is >> exp;
                else {
                    exp = 1;
                    is.putback(ch);
                }
                coefficient[exp] = co;
                break;
            default:
                coefficient[0] = co;
                break;
        }
    }
}

void Model::shell_eig(string &in) {
    string::size_type start;
    size_t len;
    start = in.find('(');
    len = in.find(')') - start - 1;
    string param_name = in.substr(start + 1, len);
    if(matrix_table.find(param_name) != matrix_table.end()) {
        // to be done
        // 调用求eig的函数
    } else
        throw calc_error("matrix not found");
}

void Model::shell_cond2(string &in){

}

void Model::shell_condInf(string &in){

}


void Model::main() {
    char buff[256];
    while (true) {
        try {
            cout << ">>> ";
            cin.getline(buff, 256);
            string in(buff);
            string::size_type start;
            if ((start = in.find('[')) != in.npos) {
                // 矩阵赋值
                istringstream is(in.substr(start + 1));
                shell_save_matrix(in, is);
            } else if (in.substr(0, 4) == "d/dx") {
                // 求导
                shell_derivative(in);
            } else if (in.substr(0, 3) == "int") {
                // 积分
                double lower,upper;
                shell_integrate(in,lower,upper);
            } else if(in.substr(0, 3) == "eig") {
                // 特征值
                shell_eig(in);
            } else if (in.substr(0, 4) == "cond") {
                // 条件数

            } else {
                // 普通计算器及变量赋值
                baseInterpreter calc(in);
                calc.output(cout);
            }
        } catch (calc_error e) {
            cout << e.what() << endl;
            return;
        }
    }
}

void Model::shell_equation(string &in) {
    // dy/dt=y^2-t^4+y^3-t+100
    string func_str = in.substr(6, in.length() - 6);
    istringstream is(func_str);
    double co;
    int exp;
    char ch;

    while (is.get(ch)) {
        if (isspace(ch) || ch == '+')
            continue;
        if (isdigit(ch)) {
            is.putback(ch);
            is >> co;
        } else if (ch == '-') {
            is.get(ch);
            if (ch == 'y' || ch == 't') {
                is.putback(ch);
                co = -1;
            } else {
                is.putback(ch);
                is >> co;
                co = -co;
            }
        } else if (ch == 'y' || ch == 't') {
            is.putback(ch);
            co = 1;
        } else {
            throw calc_error("illegal char");
        }
        is.get(ch);
        switch (ch) {
            case 'y':
                is.get(ch);
                if (ch == '^')
                    is >> exp;
                else {
                    exp = 1;
                    is.putback(ch);
                }
                coefficient[exp] = co;
                break;
            case 't':
                is.get(ch);
                if (ch == '^')
                    is >> exp;
                else {
                    exp = 1;
                    is.putback(ch);
                }
                coefficient2[exp] = co;
                break;
            default:
                coefficient[0] = co;
                break;
        }
    }
    // to be done
    // 参数已解析完
}