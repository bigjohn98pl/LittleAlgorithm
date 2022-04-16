#ifndef LITTLE_HPP
#define LITTLE_HPP

#include "macierz.hpp"
#include "nodeBT.hpp"
#include "global.hpp"

using namespace std;

class little{
public:

    little();
    little(int row, int col);
    little(vector<vector<double>> Tab);
    ~little();
    void stepOne(bool show);
    void stepTwo();
    void stepTree();
    void stepFour();
    void stepFive();
    void stepSix();
    void stepSeven();
    void stepEight();
    void stepNine();

    double metodaWegierskaKrok1();
    double metodaWegierskaKrok2();
    void wypiszKrok1Wegierski();
    void wypiszKrok2Wegierski();
    nodeBT* addNode(char& row, char& col, double& limit);
    void showData();
    void showArray();
    void showGraph();
private:

    macierz *NM;
    int iKrawedz[2];
    double ograniczenia[2];
    double kara;
    nodeBT *head;
    nodeBT *next;
};


#endif // LITTLE_HPP
