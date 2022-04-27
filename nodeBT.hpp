#ifndef NODEBT_H
#define NODEBT_H

#include "global.hpp"
#include "macierz.hpp"

class nodeBT
{
public:

    nodeBT();
    nodeBT( macierz& _M);
    nodeBT( nodeBT& coppy);
    nodeBT(vector<vector<double>> Tab);
    nodeBT(char& row, char& col, double& _limit, macierz _M);
    ~nodeBT();
    void set(int& row, int& col, double& ogr);
    void setLimit(double& ogr);
    void show(int tabs,bool node);
    void tabsInsert(int amount);
    void add(nodeBT &_node, char side);
private:
    double *limit;
    string *name;
    macierz *M;
    nodeBT* left;
    nodeBT* right;

    friend class little;
};

#endif // NODEBT_H
