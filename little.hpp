/*
 * glowna klasa, posiada:
 * zmienne:
 *  kara - wyliczane z bilansu zer w kroku 2
 *  h - wyliczane w kroku 5
 *  *head - wskaznik na poczatek grafu
 *  *next - wskaznik pomocniczy na kolejne elementy grafu
 *
 * ta klasa posiada 9 metod które robią to co kroki algorytmu opisane w ksiazce
 * sa tutaj metody do wyswietlania elementow na ekranie, takie jak:
 *  wypiszKrok1Wegierski() - wyswietla macierz z elementami ktore sie odejmuje, nic nie oblicza
 *  wypiszKrok2Wegierski() - dokladnie to samo co wyzej
 *  showData() - aktualnie nie uzywane, mozna napisac na nowo zeby wyswietlac co sie dzieje na kazdym etapie programu
 *  showArray() - wyswietla aktualna macierz, nic nie oblicza
 *  showGraph() - pokazuje drzewko grafu
 *
 *   metodaWegierskaKrok1() - oblicza nowa macierz i zwraca sume odjetych liczb
 *   metodaWegierskaKrok2() - identycznie co wyzej
 *
*/
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
    void stepOne();
    void stepTwo();
    void stepTree();
    void stepFour();
    void stepFive();
    void stepSix();
    void stepSeven();
    void stepEight();
    void stepNine();
    void result2(bool showCities);

    double metodaWegierskaKrok1(nodeBT &_node);
    double metodaWegierskaKrok2(nodeBT &_node);
    void wypiszKrok1Wegierski(nodeBT &_node);
    void wypiszKrok2Wegierski(nodeBT &_node);
    nodeBT* addNode(char& row, char& col, double& limit);
    void showData();
    void showArray(bool showCities);
    void showArray(const nodeBT &_node,bool showCities);
    void showGraph(const string &prefix, const nodeBT *node, bool isLeft, bool showCities);
    void showGraph(bool showCities);
    static string city(char key);
    string city(string key);

    void set(vector<vector<double>> &_set);
    void set(macierz &_set);
    void setStepByStep(const bool &_set){stepByStep = _set;}
    bool& getStepByStep(){return stepByStep;};

private:

    double kara, h;
    nodeBT *head;
    nodeBT *next;
    list<char> result,savePath;
    bool stepByStep;
};


#endif // LITTLE_HPP
