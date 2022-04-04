#include "nodeBT.hpp"

nodeBT::nodeBT()
{
    limit = new double;
    name = new string;

    *limit = 0;
    *name->insert(name->begin(),2,'X');
    left = NULL;
    right = NULL;
    top = NULL;
}
nodeBT::~nodeBT()
{
    delete limit;
    delete name;
    left = NULL;
    right = NULL;
    top = NULL;
    delete left;
    delete right;
    delete top;

}
nodeBT::nodeBT(char& row, char& col, double& ogr){

    limit = new double;
    name = new string;

    *limit = ogr;
    name->push_back(row);
    name->push_back(col);
    left = NULL;
    right = NULL;
    top = NULL;
}


void nodeBT::set(char& row, char& col, double& ogr){

    *limit = ogr;
    name->push_back(row);
    name->push_back(col);
    left = NULL;
    right = NULL;

}
void nodeBT::setLimit(double& ogr){
    *limit = ogr;
}
void nodeBT::show(int tabs,bool node){
    tabsInsert(tabs);
    if(node){
        cout  << "|" << setw(3) << *name  << setw(3) << *limit << "|";
    }
    else{
        name->push_back('*');
       cout  <<"|" << setw(3) << *name << setw(3) << *limit << "|";
    }
}
void nodeBT::tabsInsert(int amount){
    for (int i=0;i < amount ; i++ ) {
        cout << "\t";
    }
}
