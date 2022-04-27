#include "nodeBT.hpp"

nodeBT::nodeBT()
{
    limit = new double;
    name = new string;
    M = new macierz(2,2);
    *limit = 0;
    *name->insert(name->begin(),2,'X');
    left = nullptr;
    right = nullptr;
}
nodeBT::nodeBT(macierz& _M)
{
    limit = new double;
    name = new string;
    M = new macierz(_M);
    *limit = 0;
    *name->insert(name->begin(),2,'X');
    left = nullptr;
    right = nullptr;
}
nodeBT::nodeBT(nodeBT & coppy){
    limit = new double;
    name = new string;

    M = new macierz(*coppy.M);

    *limit = *coppy.limit;
    *name = *coppy.name;
    left = coppy.left;
    right = coppy.right;
}
nodeBT::nodeBT(vector<vector<double>> Tab)
{
    limit = new double;
    name = new string;
    M = new macierz(Tab);
    *limit = 0;
    *name->insert(name->begin(),2,'X');
    left = nullptr;
    right = nullptr;
}
nodeBT::~nodeBT()
{
    delete limit;
    delete name;
    left = nullptr;
    right = nullptr;
    delete left;
    delete right;

}
nodeBT::nodeBT(char& row, char& col, double& _limit,macierz _M){

    limit = new double;
    name = new string;
    M = new macierz(_M);
    *limit = _limit;
    name->push_back(row);
    name->push_back(col);
    left = nullptr;
    right = nullptr;
}


void nodeBT::set(int& row, int& col, double& ogr){

    *limit = ogr;
    name->clear();
    name->push_back(M->nameN[row]);
    name->push_back(M->nameM[col]);
    left = nullptr;
    right = nullptr;

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
