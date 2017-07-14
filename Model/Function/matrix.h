#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

class matrix_error:public logic_error {
public:
    matrix_error(const string &s) : logic_error(s) {}
};

class Matrix {
protected:
    int row;
    int col;
    static const int MAXM = 30;
    vector<vector<double>> entry;

    bool checkInputEntry(vector<vector<double>> element) {
        int col = element[0].size();
        for (auto it = element.begin(); it != element.end(); it++) {
            if (it->size() != col)
                return false;
        }
        return true;
    }

public:
    explicit Matrix(){}
    Matrix(const Matrix& m){
        const vector<vector<double>> mm=m.getEntry();
        resize(mm.size(),mm[0].size());
        assign(mm);
    }
    Matrix(const vector<vector<double>>& mm){
        resize(mm.size(),mm[0].size());
        assign(mm);
    }
    Matrix(const int row, const int col) :row(row),col(col),entry(row) {
    //    entry.resize(row);
        for (int i = 0;i < row;i++)
            entry[i].resize(col);
    }
    void print() {
        for (int i = 0; i < entry.size(); i++) {
            for (int j = 0; j < entry[i].size(); j++) {
                cout << entry[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void resize(int row, int col) {
        this->row = row;
        this->col = col;
        entry.resize(row);
        for (int i = 0; i < row; i++)
            entry[i].resize(col);
    }

    bool isSquare() {
        return col == row;
    }

    int getCol() {
        return col;
    }

    int getRow() {
        return row;
    }

    bool assign(vector<vector<double>> element) {
        if (checkInputEntry(element)) {
            entry = element;
            return true;
        }
        return false;
    }

    bool to2DArray(double res[][MAXM]) {
        if (col >= MAXM || row >= MAXM) return false;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
                res[i][j] = entry[i][j];
        }
        return true;
    }
    bool to1DArray(double b[]){
        for(int i=0;i<row;i++)
            b[i]=entry[i][0];
        return true;
    }
    vector<vector<double>> getEntry() const{
        return entry;
    }
    ~Matrix(){}

};


#endif // MATRIX_H
