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
void nodeBT::setLimit(double ogr){
    limit = ogr;
}
void nodeBT::show(int tabs,bool node){
    tabsInsert(tabs);
    if(node){
        cout  << "|" << setw(3) << name  << setw(3) << limit << "|";
    }
    else{
        name.push_back('*');
       cout  <<"|" << setw(3) << name << setw(3) << limit << "|";
    }
}
void nodeBT::tabsInsert(int amount){
    for (int i=0;i < amount ; i++ ) {
        cout << "\t";
    }
}
