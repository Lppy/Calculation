#include "CondInfBinding.h"
#include "Model/Model.h"

CondInfBinding::CondInfBinding(Model *m):pm(m)
{

}

void CondInfBinding::exec(string &in){
    string::size_type start;
    if((start = in.find('[')) != in.npos){
        istringstream is(in.substr(start + 1));
        string entry=in.substr(8);
        Matrix m=pm->shell_save_matrix(entry,is);
        cout<<"in Model:before CondInf "<<m.getRow()<<" "<<m.getCol()<<endl;
        pm->getCond_inf(m);
    }
    else
        throw gram_error("grammer error in CondInf: incorrect matrix");
}
