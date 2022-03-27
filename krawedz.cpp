#include "krawedz.hpp"

krawedz::krawedz()
{
    h = 0;
    ograniczenieDolne = 0;
    oznaczenie = "XX";
    lewa = NULL;
    prawa = NULL;
}

krawedz::krawedz(char row, char col, double ogr){

    h = 0;
    ograniczenieDolne = ogr;
    oznaczenie.push_back(row);
    oznaczenie.push_back(col);
    lewa = NULL;
    prawa = NULL;
}

void krawedz::set(char row, char col, double ogr){

    ograniczenieDolne = ogr;
    oznaczenie.push_back(row);
    oznaczenie.push_back(col);
    lewa = NULL;
    prawa = NULL;
}

void krawedz::show(){
    cout << "Wezel: " << oznaczenie << endl;
    cout << "wiersz: " << 4 << endl;
    cout << "kolumna: " << 4 << endl;
    cout << "ograniczenie: " << ograniczenieDolne << endl;
}
