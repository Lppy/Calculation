#ifndef IBINDING_H
#define IBINDING_H
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

/*base Class of shell to binding function*/
class iBinding{
public:
    virtual void exec(string &in)=0;
};

/*grammer error when binding funcion*/
class gram_error :public logic_error{
public:
    gram_error(const string &s) : logic_error(s) {}
};

#endif // IBINDING_H
