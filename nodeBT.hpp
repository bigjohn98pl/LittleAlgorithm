#ifndef NODEBT_H
#define NODEBT_H

#include "global.hpp"

class nodeBT
{
public:

    nodeBT();
    nodeBT(char& row, char& col, double& ogr);
    ~nodeBT();
    void set(char& row, char& col, double& ogr);
    void setLimit(double& ogr);
    void show(int tabs,bool node);
    void tabsInsert(int amount);
private:
    double *limit;
    string *name;
    nodeBT* left;
    nodeBT* right;
    nodeBT* top;

    friend class little;
};

#endif // NODEBT_H
