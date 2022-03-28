#ifndef NODEBT_H
#define NODEBT_H

#include "global.hpp"

class nodeBT
{
public:

    nodeBT();
    nodeBT(char row, char col, double ogr);
    ~nodeBT();
    void set(char row, char col, double ogr);
    void show(int tabs,bool node);

private:
    double limit;
    string name;
    nodeBT* top;
    nodeBT* left;
    nodeBT* right;

    friend class little;
};

#endif // NODEBT_H
