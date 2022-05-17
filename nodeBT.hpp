/*
 * Klasa reprezentujaca jedna krawedz w grafie z tej klasy jest zbudowany graf
 *  *limit - ograniczenie dolne
 *  *name - nazwa krawedzi skaladajaca sie z 2 liter
 *  *edge - posiada indeks dla wiersza i kolumny tej krawedzi,
 *  *M - dynamiczna macierz
 *  *left - lewe dziecko/lewa krawedz tej krawedzi, jest to wskażnik na krawedz ij* gdzie ograniczenie = ograniczenie + kara
 *  *right - prawa krawedz/ dziecko, jest tu przechowywana macierz po usunięciu z niej wskazanego wiersza i kolumny
 *
*/
#ifndef NODEBT_H
#define NODEBT_H

#include "global.hpp"
#include "macierz.hpp"

class nodeBT
{
public:

    nodeBT();
    nodeBT( macierz &_M);
    nodeBT( nodeBT &coppy);
    nodeBT(vector<vector<double>> &Tab);
    nodeBT(int &row, int &col, double &_limit, macierz &_M);
    ~nodeBT();
    void set(int &row, int &col, double &ogr);
    void setLimit(double &ogr);
    void show(int tabs,bool node);
    void tabsInsert(int amount);

private:

    double *limit;
    string *name;
    vector<int> edge;
    macierz *M;
    nodeBT* left;
    nodeBT* right;

    friend class little;
};

#endif // NODEBT_H
