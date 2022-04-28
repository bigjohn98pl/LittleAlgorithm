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

    double metodaWegierskaKrok1(nodeBT &_node);
    double metodaWegierskaKrok2(nodeBT &_node);
    void wypiszKrok1Wegierski();
    void wypiszKrok2Wegierski();
    nodeBT* addNode(char& row, char& col, double& limit);
    void showData();
    void showArray();
    void showArray(const nodeBT &_node);
    void showGraph(const string& prefix, const nodeBT* node, bool isLeft);
    void showGraph();
private:

    double kara,h;
    nodeBT *head;
    nodeBT *next;
};


#endif // LITTLE_HPP
