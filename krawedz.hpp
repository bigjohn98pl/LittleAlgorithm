#ifndef KRAWEDZ_HPP
#define KRAWEDZ_HPP

#include "global.hpp"

class krawedz
{
public:

    krawedz();
    krawedz(char row, char col, double ogr);
    ~krawedz();
    void set(char row, char col, double ogr);
    void show(int tabs,bool node);

private:
    int h;
    double ograniczenieDolne;
    string oznaczenie;
    krawedz* lewa;
    krawedz* prawa;

    friend class little;
};

#endif // KRAWEDZ_HPP
