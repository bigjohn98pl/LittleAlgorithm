#ifndef LITTLE_HPP
#define LITTLE_HPP

#include "macierz.hpp"
#include "krawedz.hpp"
#include "global.hpp"

using namespace std;

class little{
public:

    little();
    little(int row, int col);
    little(vector<vector<double>> Tab);
    ~little();
    int indexMinRow(int wiersz);
    int indexMinCol(int kolumna);
    int* indexMin(int Row, int Col);
    void delRowCol(int row, int col);
    bool haveZeros();
    double metodaWegierskaKrok1();
    double metodaWegierskaKrok2();
    void krokDrugi();
    void krokTrzeci();
    void krokCzwarty();
    void krokPiaty();
    void krokSzosty();
    void krokSiodmy();
    void wypiszKrok1Wegierski();
    void wypiszKrok2Wegierski();
    void showData();
    void showArray();
    void showGraph();
private:

    macierz NM;
    int iKrawedz[2];
    double ograniczenia[2];
    double kara;
    krawedz *head;
};


#endif // LITTLE_HPP
