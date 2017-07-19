#include "Cond2Binding.h"
#include "Model/Model.h"
#include <stdexcept>

Cond2Binding::Cond2Binding(Model *m):pm(m)
{

}

void Cond2Binding::exec(string &in){
    string::size_type start;
    if((start = in.find('[')) != in.npos){
        istringstream is(in.substr(start + 1));
        string entry=in.substr(6);
        Matrix m=pm->shell_save_matrix(entry,is);
        pm->getCond_2(m);
    }
    else
        throw logic_error("need matrix in cond2");
}

