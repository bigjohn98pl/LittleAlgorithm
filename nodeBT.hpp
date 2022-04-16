#ifndef NODEBT_H
#define NODEBT_H

#include "global.hpp"
#include "macierz.hpp"

class nodeBT : public macierz
{
public:

    nodeBT();
    nodeBT( macierz& _M);
    nodeBT(vector<vector<double>> Tab);
    nodeBT(char& row, char& col, double& _limit, macierz _M);
    ~nodeBT();
    void set(char& row, char& col, double& ogr);
    void setLimit(double& ogr);
    void show(int tabs,bool node);
    void tabsInsert(int amount);
private:
    double *limit;
    string *name;
    macierz *M;
    nodeBT* left;
    nodeBT* right;
    nodeBT* top;

    friend class little;
};

#endif // NODEBT_H
