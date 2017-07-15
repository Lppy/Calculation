#include "Model.h"
#include <sstream>
#include <cstdio>
map<string, Matrix> matrix_table;
double coefficient[10];
double coefficient2[10];

Model::Model()
{
    this->res=shared_ptr<QString>(new QString("Output here"));
    this->points=shared_ptr<Data>(new Data);
    pos=-1;
}

Model::~Model()
{
}

//for test
double Model::f(double x){
    return poly(x,coefficient);
}

//for test
double Model::ff(double t,double w){
    return poly(w,coefficient)+poly(t,coefficient2);
}

double Model::poly(double x,double coe[]){
    double pow=1,res=0;
    for(int i=0;i<10;i++){
        res+=coe[i]*pow;
        pow*=x;
    }
    return res;
}

void Model::Calculate(string &in){

   // main();

    //解释器处理字符串in，并调用model中的计算函数
    cout<<"in Model:Calculate "<<in<<endl;
    //data for test
    memset(coefficient,0,10*sizeof(double));  //clear coefficient
    memset(coefficient2,0,10*sizeof(double));
    if(in.substr(0,10)=="solve Poly"){
        string polys=in.substr(6);
        resolve_polynomial(polys);
        for(int i=9;i>=0;i--)
            cout<<coefficient[i]<<" ";
        cout<<endl;
        getPolynomialRoot(MAXD,coefficient,(double)0.01);
    }
    else if(in.substr(0,12)=="solve Matrix"){
        size_t equal=in.find("x=");
        string aa(1,in[equal-1]);
        string bb(1,in[equal+2]);
        cout<<"in Model:solve Matrix "<<aa<<" "<<bb<<endl;
        if(matrix_table.find(aa)==matrix_table.end()||matrix_table.find(bb)==matrix_table.end())
            throw logic_error("no such matrix");
        Matrix AA=matrix_table[aa],BB=matrix_table[bb];
        cout<<"in Model::before getMatrixRoot"<<endl;
        getMatrixRoot(AA,BB);
        cout<<res->toStdString()<<endl;
    }
    else if(in.substr(0,3)=="Int"){
        double lower,upper;
        shell_integrate(in,lower,upper);
        getIntegral(f,lower,upper,(double)0.01);
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
    }
    //dy/dt=y^2-t^4+y^3-t+100 (0,1) y(0)=0
    else if(in.substr(0,5)=="dy/dt"){
        double lower,upper,ya;
        shell_ode(in,lower,upper,ya);
        int step=(upper-lower)/0.2;
        getODE(ff,lower,upper,step,ya);
    }
    else if(in.substr(0,3)=="Fit"){
        string str=in.substr(4);
        vector<Point> p=shell_point(str);
        getCubicSpline(p,2);
    }
    else if(in.substr(0,5)=="Curve"){
        string str=in.substr(6);
        vector<Point> p=shell_point(str);
        getCurve(p);
    }
    else if(in.substr(0,10)=="BrokenLine"){
        string str=in.substr(11);
        vector<Point> p=shell_point(str);
        getBrokenLine(p);
    }
    else if(in.find("[") != in.npos){
        size_t start = in.find("[");
        istringstream is(in.substr(start + 1));
        cout<<"in model::before shell_save_matrix"<<endl;
        shell_save_matrix(in,is);
    }
    else {
        baseInterpreter calc(in);
        double res=calc.output(cout);
        getCalcNumeric(res);
    }

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

void Model::getCalcNumeric(double dres){
    *(this->res)=QString::fromStdString(double2string(dres));
    DoneList.push_back(Action(*res));
    pos++;
    string s="text";
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
    points->setBroken(false);
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
    cout<<"in Mode::getMatrixRootl"<<endl;
    a.print();
    b.print();
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


void Model::getCubicSpline(vector<Point> p,int Type){
    Cubic_Spline cs;
    vector<Point> pp = cs.cubic_Spline(p,Type);
    points->setPoint(pp);
    points->setBroken(false);
    DoneList.push_back(Action(pp));
    pos++;
    string s="graph";
    cout<<s<<endl;
    vector<Point> pdata=points->getPoint();
    for(auto it=pdata.begin();it!=pdata.end();it++)
        cout<<"p "<<it->first<<" "<<it->second<<endl;
    this->notify(s);
}

void Model::getBrokenLine(vector<Point> p){
    points->setPoint(p);
    points->setBroken(true);
    DoneList.push_back(Action(p));
    pos++;
    vector<Point> pdata=points->getPoint();
    for(auto it=pdata.begin();it!=pdata.end();it++)
        cout<<"p "<<it->first<<" "<<it->second<<endl;
    string s="graph";
    this->notify(s);
}

void Model::getCurve(vector<Point> p){
    points->setPoint(p);
    points->setBroken(false);
    DoneList.push_back(Action(p));
    pos++;
    vector<Point> pdata=points->getPoint();
    for(auto it=pdata.begin();it!=pdata.end();it++)
        cout<<"p "<<it->first<<" "<<it->second<<endl;
    string s="graph";
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
    cout<<"~1~"<<endl;
    string param_name;
    int row_num = 1, i;
    char ch;
    double tmp_num;

    cout<<"~2~";
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
    cout<<"in Matrix "<<param_name<<endl;
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
        if (isdigit(ch) || ch == '-') {
            is.putback(ch);
            is >> co;
            if (is.get(ch) && ch != 'x' && ch != '*') {
                coefficient[0] = co;
                break;
            }
            while (is.get(ch) || ch == '-')
                if (isdigit(ch)) {
                    is.putback(ch);
                    is >> exp;
                    coefficient[exp] = co;
                    break;
                }
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

void Model::shell_ode(string& in,double& lower,double& upper,double& ya){
    size_t lbrack=in.find_first_of("(");  //(a,b)
    size_t comma=in.find_first_of(",");
    size_t rbrack=in.find_first_of(")");
    size_t equal=in.find_last_of("=");
    if(lbrack==string::npos||comma==string::npos||rbrack==string::npos)
        throw gram_error("need boundary limit in integration");
    string ode=in.substr(0,lbrack);
    string lowstr=in.substr(lbrack+1,comma-lbrack-1);
    string upstr=in.substr(comma+1,rbrack-comma-1);
    string yastr=in.substr(equal+1);

    lower=string2double(lowstr);
    upper=string2double(upstr);
    ya=string2double(yastr);
    shell_equation(ode);
}

vector<Point> Model::shell_point(string &in) {
    // (1,23) (0.123,-222) (-1.2,33)
    istringstream is(in);
    Point p;
    vector<Point> points;
    char ch;
    bool left;
    int point_count = 0;

    while (is.get(ch) && point_count <= 30) {
        switch (ch) {
            case '(':
                left = true;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '-':
                is.putback(ch);
                if (left)
                    is >> p.first;
                else
                    is >> p.second;
                break;
            case ',':
                left = false;
                break;
            case ')':
                point_count++;
                points.push_back(p);
                break;
            default:
                continue;
        }
    }
    return points;
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


