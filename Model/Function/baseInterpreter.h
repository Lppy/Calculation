//
// Created by Kira on 2017/7/12.
//

#ifndef CALC_SHELL_CALCULATOR_H
#define CALC_SHELL_CALCULATOR_H


#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <stdexcept>

using namespace std;
extern map<string, double> symbol_table;

class calc_error : public logic_error {
public:
    calc_error(const string &s) : logic_error(s) {}
};

class gram_error :public logic_error{
public:
    gram_error(const string &s) : logic_error(s) {}
};


class baseInterpreter {
public:
    enum Token_value {
        NUMBER,
        NAME,
        END,
        FUNC,
        PLUS = '+',
        MINUS = '-',
        MUL = '*',
        DIV = '/',
        PRINT = ';',
        ASSIGN = '=',
        LP = '(',
        RP = ')',
        POWER = '^'
    };

    baseInterpreter(const string &s) : input(new istringstream(s)), curr_tok(PRINT) {
        symbol_table["pi"] = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
        symbol_table["e"] = 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274;
    }

    baseInterpreter(istream &is) : input(&is), curr_tok(PRINT) {
        symbol_table["pi"] = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
        symbol_table["e"] = 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274;
    }

    double output(ostream &);
    void main();

private:
    double expr(bool);

    double power(bool);

    double term(bool);

    double prim(bool);

    Token_value get_token();

    istream *input;
    Token_value curr_tok;
    double number_value;
    string string_value;
    string curr_func;
};


#endif //CALC_SHELL_CALCULATOR_H
