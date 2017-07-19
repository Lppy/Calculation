#include "MatrixBinding.h"
#include "Model/Model.h"

MatrixBinding::MatrixBinding(Model *m):pm(m)
{

}

void MatrixBinding::exec(string &in){
    size_t equal=in.find("x=");
    string aa(1,in[equal-1]);
    string bb(1,in[equal+2]);
    cout<<"in Model:solve Matrix "<<aa<<" "<<bb<<endl;
    if(matrix_table.find(aa)==matrix_table.end()||matrix_table.find(bb)==matrix_table.end())
        throw logic_error("no such matrix");
    Matrix AA=matrix_table[aa],BB=matrix_table[bb];
    cout<<"in Model::before getMatrixRoot"<<endl;
    pm->getMatrixRoot(AA,BB);
}
