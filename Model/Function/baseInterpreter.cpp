//
// Created by Kira on 2017/7/12.
//

#include <cmath>
#include "baseInterpreter.h"

map<string, double> symbol_table;

void baseInterpreter::output(ostream &os) {
     while (*input) {
        // cout << ">>> ";
        get_token();
        if (curr_tok == END) break;
        if (curr_tok == PRINT) continue;
        os << expr(false) << endl;
    }
}

// + -
double baseInterpreter::expr(bool get) {
    double left = term(get);
    while (true)
        switch (curr_tok) {
            case PLUS:
                left += term(true);
                break;
            case MINUS:
                left -= term(true);
                break;
            default:
                return left;
        }
}

// * /
double baseInterpreter::term(bool get) {
    double left = power(get);
    while (true)
        switch (curr_tok) {
            case MUL:
                left *= power(true);
                break;
            case DIV:
                if (double d = power(true)) {
                    left /= d;
                    break;
                }
                throw calc_error("divide by 0");
            default:
                return left;
        }
}

// ^
double baseInterpreter::power(bool get) {
    double left = prim(get);
    while (true)
        switch (curr_tok) {
            case POWER:
                left = pow(left, prim(true));
                break;
            default:
                return left;
        }

}

// base
double baseInterpreter::prim(bool get) {
    if (get) get_token();

    switch (curr_tok) {
        case NUMBER: {
            double v = number_value;
            get_token();
            return v;
        }
        case NAME: {
            double &v = symbol_table[string_value];
            if (get_token() == ASSIGN)
                v = expr(true);
            return v;
        }
        case MINUS:
            return -prim(true);
        case LP: {
            double e = expr(true);
            if (curr_tok != RP)
                throw calc_error(") expected");
            get_token();
            return e;
        }
        case FUNC: {
            if (get_token() == LP) {
                double e = 0;
                if (curr_func == "sin")
                    e = sin(expr(true));
                else if (curr_func == "cos")
                    e = cos(expr(true));
                else if (curr_func == "tan")
                    e = tan(expr(true));
                get_token();
                return e;
            } else {
                throw calc_error("function usage: func()");
            }
        }
        default:
            throw calc_error("primary expected");
    }
}

baseInterpreter::Token_value baseInterpreter::get_token() {
    char ch;
    do {
        if (!input->get(ch)) return curr_tok = END;
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';':
        case '\n':
            return curr_tok = PRINT;
        case '^':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = Token_value(ch);
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
        case '.':
            input->putback(ch);
            input->operator>>(number_value);
            return curr_tok = NUMBER;
        default:
            if (isalpha(ch)) {
                string_value = ch;
                while (input->get(ch) && isalnum(ch))
                    string_value.push_back(ch);
                input->putback(ch);
                if (string_value == "sin" || string_value == "cos" || string_value == "tan") {
                    curr_func = string_value;
                    return curr_tok = FUNC;
                }
                return curr_tok = NAME;
            }
            curr_tok = PRINT;
            throw calc_error("bad token");
    }
}

