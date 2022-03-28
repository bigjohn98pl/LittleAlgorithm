#include "nodeBT.hpp"

nodeBT::nodeBT()
{
    limit = 0;
    name = "XX";
    top = this;
    left = NULL;
    right = NULL;
}

nodeBT::nodeBT(char row, char col, double ogr){

    limit = ogr;
    name.push_back(row);
    name.push_back(col);
    top = NULL;
    left = NULL;
    right = NULL;
}

void nodeBT::set(char row, char col, double ogr){

    limit = ogr;
    name.push_back(row);
    name.push_back(col);
    top = NULL;
    left = NULL;
    right = NULL;

}

void nodeBT::show(int tabs,bool node){
    for (int i=0;i < tabs ; i++ ) {
        cout << "\t";
    }
    if(node){
        cout << setw(3) << "|" << name  << setw(3) << limit << "|";
    }
    else{
       cout << setw(3) <<"|" << name << "*" << setw(3) << limit << "|";
    }
//    for (int i=0;i < tabs ; i++ ) {
//        cout << "\t";
//    }
//    cout << setw(8) <<"ogr. : "     << setw(4)  << limit    << endl << endl;
}
