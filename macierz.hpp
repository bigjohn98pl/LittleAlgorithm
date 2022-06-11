/*
 * Klasa macierz ktora znajduje sie wewnatrz klasy nodeBT(węzeł drzewa binarnego) i ktora ma przydatne do obliczen metody takie jak:
 *  indexMinRow() - zwraca indeks wiersza gdzie wystepuje najmniejsza liczba w wierszu
 *  indexMinCol() - to samo dla kolumny
 *  indexMin() - zwraca jednoczesnie 2 wartosci , indeks dla minimalnej wartosci w podanym wierszu, i indeks dla minimum w podanej kolumnie z pominieciem punktu przeciecia sie kolumny z wierszem
 *  delRowCol() - usuwa wskazany wiersz i kolumne
 *  haveZerosRows() - sprawdza czy w we wszystkich kolumnach jest chociaz jedno 0
 *  haveZerosColums() - to samo dla wierszy
 *  przeladowane operatory w wiekszosci nie sa tutaj uzywane
 *
*/

#ifndef MACIERZ_HPP
#define MACIERZ_HPP

#include "global.hpp"

#define ROW 5
#define COL 5

using namespace std;

class macierz {
public:

    macierz();
    macierz(const int _n,const int _m);
    macierz(double **tab, int _n, int _m);
    macierz(macierz& X);
    macierz( vector< vector< double>> Tab);
    ~macierz();

    bool file(string Fname);

    void random(int from = 1, int to = 10);
    void reSize(int n, int m);
    void set(vector<vector<double>> tab);
    void show(bool showCities);
    void fill(bool showCieties);
    int col();
    int row();
    int indexMinRow(int row);
    int indexMinCol(int col);
    int* indexMin(int Row, int Col);
    macierz& operator =(macierz& B);
    void delRowCol(int row, int col,list<char> &result, list<char> &savePath, bool &stepByStep);
    bool haveZerosRows();
    bool haveZerosColums();

    double get(const int &i, const int &j);
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
    friend class nodeBT;
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
