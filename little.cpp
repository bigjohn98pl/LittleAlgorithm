#include "nodeBT.hpp"
#include "little.hpp"

little::little()
{
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    kara = 0;
    head = new nodeBT(Tab2);
    next = head;
}

little::little(int row, int col)
{
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);
    kara = 0;


    head = new nodeBT(*new macierz(row,col));
    next = head;
}

little::little(vector<vector<double>> Tab){
    //NM = new macierz(Tab);
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);

    kara = 0;
    head = new nodeBT(Tab);
    next = head;
}
little::~little(){
    delete head;
    delete next;

    head = nullptr;
    next = nullptr;
}

//nodeBT* little::next = new nodeBT;

void little::stepOne(bool show){
    if(show){
        wypiszKrok1Wegierski();
        if(! next->M->haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        wypiszKrok2Wegierski();
        if(!next->M->haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }
    else{
        if(! next->M->haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        if(!next->M->haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }

    stepTwo();
}
void little::stepTwo(){
    double suma=0,karaMax=0;
    int* iMin;
    for(int i = 0; i < next->M->N   ; i++){
        for(int j = 0 ; j < next->M->M ; j++){
            if(next->M->get(i,j) == 0.00){
                iMin = next->M->indexMin(i,j);
                suma = next->M->get(iMin[0],j) + next->M->get(i,iMin[1]);
                if(suma > karaMax){
                    karaMax = suma;
                    iKrawedz[0] = i;
                    iKrawedz[1] = j;
                }
            }
        }
    }

    kara = karaMax;
    *next->limit = ograniczenia[0];

    stepTree();
}
void little::stepTree(){
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];

    ograniczenia[1] = ograniczenia[0]+kara;

    next->left = new nodeBT(next->M->nameN[wiersz],next->M->nameM[kolumna],ograniczenia[1],*next->M);
    cout << *next->left->name << endl;

    stepFour();
}
void little::stepFour(){
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];

    next->M->delRowCol(wiersz,kolumna);

    stepFive();
}
void little::stepFive(){
    int h = 0;

    if(!next->M->haveZerosRows()){
        h += metodaWegierskaKrok1();
    }
    if(next->M->haveZerosColums()){
        h += metodaWegierskaKrok2();
    }
    ograniczenia[0] += h;

    stepSix();
}
void little::stepSix(){
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];

    next->right = new nodeBT(next->left->M->nameN[wiersz],next->left->M->nameM[kolumna],ograniczenia[0],*next->M);
    cout << *next->right->name << endl;
    next = next->right;

    if(next->M->N == 2 && next->M->M == 2){
        stepSeven();
    }
    else{
        stepOne(false);
    }
}
void little::stepSeven(){
    if(next->M->N == 2 && next->M->M == 2 && ( (next->M->get(0,0) == 0 && next->M->get(1,1) == 0) || (next->M->get(0,1) == 0 && next->M->get(1,0) == 0)) ){
        for(int i=0; i<next->M->N ; i++){
            for(int j=0; j<next->M->M ; j++){
                if(next->M->get(i,j) == 0 ){

                    next->right = new nodeBT(next->M->nameN[i],next->M->nameM[j],ograniczenia[0],*next->M);
                    next = next->right;
                }
            }
        }
    }
    else{
        stepEight();
    }
}
void little::stepEight(){
    nodeBT *last = next;
    if(last->left->limit < last->right->limit){
        stepNine();
    }
    else{
        stepTwo();
    }
}
void little::stepNine(){
    next->M->tablica[iKrawedz[0]][iKrawedz[1]] = 999;
    stepOne(false);
}
double little::metodaWegierskaKrok1(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i<next->M->N; i++){
        Min = next->M->get(i,next->M->indexMinRow(i));
        SUM = SUM + Min;
        for(int j=0 ; j<next->M->M ; j++){
             next->M->tablica[i][j] = next->M->tablica[i][j] - Min;
        }
    }

    return SUM;
}

double little::metodaWegierskaKrok2(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i < next->M->N; i++){
        Min = next->M->get(next->M->indexMinCol(i),i);
        SUM = SUM + Min;
        for(int j=0 ; j<next->M->N ; j++){
            next->M->tablica[j][i] = next->M->tablica[j][i] - Min;
        }
    }
    return SUM;
}
void little::wypiszKrok1Wegierski(){
    for(int j = 0; j<next->M->N; j++){
        cout <<"|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(4);
            cout << next->M->get(j,i) << " ";
        }
        if(next->M->get(j,next->M->indexMinRow(j)) <= 0){
            cout << endl;
        }
        else{
            cout <<" |- "<< next->M->get(j,next->M->indexMinRow(j)) << endl;
        }
    }
    cout << endl;
}
void little::wypiszKrok2Wegierski(){
    int space=4;
    for(int j = 0; j<next->M->N; j++){
        cout << "|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(space);
            cout << next->M->get(j,i) << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<next->M->M; i++){
        cout << setw(space) << "------";
    }
    cout << endl;
    for(int i = 0 ; i<next->M->M; i++){
        if(next->M->get(next->M->indexMinCol(i),i) <= 0){
            space+= 5;
        }
        else{
            cout << setw(space) <<"-"<< next->M->get(next->M->indexMinCol(i),i);
        }
    }
    cout << endl;
}

void little::showArray(){
    cout << endl;
    cout << setw(6) << next->M->nameM[0];
    for(int i = 1 ; i<next->M->M; i++){
        cout << setw(5) << next->M->nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<next->M->M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<next->M->N; j++){
        cout << next->M->nameN[j] <<"|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(4);
            cout << next->M->get(j,i) << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<next->M->M; i++){
        cout <<"------";
    }
    cout << endl;
}

void little::showData(){
    cout << "Wiersze: "<< next->M->N << endl;
    cout << "Kolumny: "<< next->M->M << endl;
    cout << "Oszacowanie dolne: " << ograniczenia[0] << endl;
    cout << "Ograniczenie dolne: " << ograniczenia[1] << endl;
    cout << "Kara: " << kara << endl;
    cout << "Krawedz: " << iKrawedz[0]+1 << iKrawedz[1]+1 << endl;
}

void little::showGraph(){

    int tabs =2;
    nodeBT *tmp = head;
    tmp->show(tabs,true);

    cout << endl;

    while( tmp->right != NULL){

        tmp->tabsInsert(tabs);

        cout << "/" << setw(7) << "\\";
        cout << endl;

        if(tmp->left){

            tmp->left->show(tabs-1,false);
        }
        else{

            tmp->tabsInsert(tabs-1);
            cout << setw(8) << "| NULL |";

        }

        if(tmp->right){

            tmp->right->show(1,true);

        }
        else{

            tmp->tabsInsert(tabs);
            cout << setw(8) << "| NULL |";

        }
        cout << endl;

        tmp = tmp->right;
        tabs++;
    }

}
