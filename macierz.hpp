#ifndef MACIERZ_HPP
#define MACIERZ_HPP


#include "global.hpp"

#define ROW 5
#define COL 5

using namespace std;

class macierz {
public:

    macierz();
    macierz(int n, int m);
    macierz(double tab[ROW][COL]);
    macierz(macierz& X);
    ~macierz();

    void random(int from = 1, int to = 10);
    void reSize(int n, int m);
    void set(vector<vector<double>> tab);
    void show();
    int col();
    int row();
    int indexMinRow(int row);
    int indexMinCol(int col);
    int* indexMin(int Row, int Col);
    macierz& operator =(macierz& B);
    void delRowCol(int row, int col);
    bool haveZeros();
    bool haveZerosRows();


    double operator ()(int i, int j);
    vector<double>& operator [](int i);

    friend macierz& operator +(macierz& A, double x);
    friend macierz& operator -(macierz& A, double x);
    friend macierz& operator +(macierz& A);
    friend macierz& operator -(macierz& A);
    friend macierz& operator *(macierz& A, double x);
    friend macierz& operator /(macierz& A, double x);
    friend macierz& operator +(macierz& A, macierz& B);
    friend macierz& operator -(macierz& A, macierz& B);
    friend macierz& operator *(macierz& A, macierz& B);
    friend macierz& operator +=(macierz& A, macierz& B);
    friend macierz& operator -=(macierz& A, macierz& B);
    friend macierz& operator *=(macierz& A, macierz& B);
    friend macierz& operator *=(macierz& A, double x);
    friend macierz& operator +=(macierz& A, double x);
    friend macierz& operator -=(macierz& A, double x);
    friend bool& operator ==(macierz& A, macierz& B);
    friend bool& operator !=(macierz& A, macierz& B);
    friend ostream& operator <<(ostream& str, macierz& A);
    friend istream& operator >>(istream& is, macierz& A);

private:

    int N, M;
    vector<char> nameN;
    vector<char> nameM;
    vector<vector<double>> tablica;
    friend class little;
};

void showRowCol(macierz X);
macierz& operator +(macierz& A);
macierz& operator -(macierz& A);
macierz& operator +(macierz& A, double x);
macierz& operator -(macierz& A, double x);
macierz& operator *(macierz& A, double x);
macierz& operator /(macierz& A, double x);
macierz& operator +=(macierz& A, double x);
macierz& operator -=(macierz& A, double x);
macierz& operator *=(macierz& A, double x);
macierz& operator +(macierz& A, macierz& B);
macierz& operator -(macierz& A, macierz& B);
macierz& operator *(macierz& A, macierz& B);
macierz& operator +=(macierz& A, macierz& B);
macierz& operator -=(macierz& A, macierz& B);
macierz& operator *=(macierz& A, macierz& B);
macierz& operator *=(macierz& A, double x);
bool& operator ==(macierz& A, macierz& B);
bool& operator !=(macierz& A, macierz& B);
ostream& operator <<(ostream& str, macierz& A);
istream& operator >>(istream& is, macierz& A);

#endif // MACIERZ_HPP
