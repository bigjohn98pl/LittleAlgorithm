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

void krawedz::show(int tabs,bool node){
    for (int i=0;i < tabs ; i++ ) {
        cout << "\t";
    }
    if(node){
        cout << setw(3) << "|" << oznaczenie  << setw(3) << ograniczenieDolne << "|";
    }
    else{
       cout << setw(3) <<"|" << oznaczenie << "*" << setw(3) << ograniczenieDolne << "|";
    }
//    for (int i=0;i < tabs ; i++ ) {
//        cout << "\t";
//    }
//    cout << setw(8) <<"ogr. : "     << setw(4)  << ograniczenieDolne    << endl << endl;
}
