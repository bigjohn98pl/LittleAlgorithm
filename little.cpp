#include "nodeBT.hpp"
#include "little.hpp"

little::little()
{
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    NM = new macierz(Tab2[0].size(),Tab2.size());
    kara = 0;
    head = new nodeBT;
    next = head;
}

little::little(int row, int col)
{
    NM = new macierz(row,col);
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);
    kara = 0;
    head = new nodeBT;
    next = head;
}

little::little(vector<vector<double>> Tab){
    NM = new macierz(Tab);
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);

    kara = 0;
    head = new nodeBT(*NM);
    next = head;
}
little::~little(){
    delete NM;
    delete head;
    delete next;
}

//nodeBT* little::next = new nodeBT;

void little::stepOne(bool show){
    if(show){
        wypiszKrok1Wegierski();
        if(!(*NM).haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        wypiszKrok2Wegierski();
        if(!(*NM).haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }
    else{
        if(!(*NM).haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        if(!(*NM).haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }

    stepTwo();
}
void little::stepTwo(){
    double suma=0,karaMax=0;
    int* iMin;
    for(int i = 0; i < (*NM).N; i++){
        for(int j = 0 ; j < (*NM).M ; j++){
            if((*NM)[i][j] == 0){
                iMin = (*NM).indexMin(i,j);
                suma = (*NM)[iMin[0]][j] + (*NM)[i][iMin[1]];
                if(suma > karaMax){
                    karaMax = suma;
                    iKrawedz[0] = i;
                    iKrawedz[1] = j;
                }
            }
        }
    }
    kara = karaMax;
    *next->limit = ograniczenia[0];//cos z tym
    cout << kara << endl;
    stepTree();
}
void little::stepTree(){
    ograniczenia[1] = ograniczenia[0]+kara;

    stepFour();
}
void little::stepFour(){
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];


    addNode((*NM).nameN[wiersz],(*NM).nameM[kolumna],ograniczenia[1]);

    next = addNode((*NM).nameN[wiersz],(*NM).nameM[kolumna],ograniczenia[0]);//cos z tym?

    (*NM).delRowCol(iKrawedz[0],iKrawedz[1]);
    stepFive();
}
void little::stepFive(){
    int h = 0;
    if(!(*NM).haveZerosRows()){
        h += metodaWegierskaKrok1();
    }
    if((*NM).haveZerosColums()){
        h += metodaWegierskaKrok2();
    }
    ograniczenia[0] += h;
    *next->limit = ograniczenia[0];
    showArray();
    stepSix();
}
void little::stepSix(){

    if((*NM).N == 2 && (*NM).M == 2){
        stepSeven();
    }
    else{
        stepOne(false);
    }
}
void little::stepSeven(){
    if((*NM).N == 2 && (*NM).M == 2 && ( ((*NM)[0][0] == 0 && (*NM)[1][1] == 0) || ((*NM)[0][1] == 0 && (*NM)[1][0] == 0)) ){
        for(int i=0; i<(*NM).N ; i++){
            for(int j=0; j<(*NM).M ; j++){
                if((*NM)[i][j] == 0 ){
                    addNode((*NM).nameN[i],(*NM).nameM[j],ograniczenia[0]);
                }
            }
        }
    }
    else{
        stepEight();
    }
}
void little::stepEight(){
    nodeBT *last = next->top;
    if(last->left->limit < last->right->limit){
        stepNine();
    }
    else{
        stepTwo();
    }
}
void little::stepNine(){
    (*NM)[iKrawedz[0]][iKrawedz[1]] = 999;
    stepOne(false);
}
double little::metodaWegierskaKrok1(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i<(*NM).N; i++){
        Min = (*NM)[i][(*NM).indexMinRow(i)];
        SUM = SUM + Min;
        for(int j=0 ; j<(*NM).M ; j++){
            (*NM)[i][j] = (*NM)[i][j] - Min;
        }
    }

    return SUM;
}

double little::metodaWegierskaKrok2(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i < (*NM).N; i++){
        Min = (*NM)[(*NM).indexMinCol(i)][i];
        SUM = SUM + Min;
        for(int j=0 ; j<(*NM).N ; j++){
            (*NM)[j][i] = (*NM)[j][i] - Min;
        }
    }
    return SUM;
}
void little::wypiszKrok1Wegierski(){
    for(int j = 0; j<(*NM).N; j++){
        cout <<"|";
        for(int i = 0 ; i<(*NM).M; i++){
            cout << setw(4);
            cout << (*NM)[j][i] << " ";
        }
        if((*NM)[j][(*NM).indexMinRow(j)] <= 0){
            cout << endl;
        }
        else{
            cout <<" |- "<< (*NM)[j][(*NM).indexMinRow(j)] << endl;
        }
    }
    cout << endl;
}
void little::wypiszKrok2Wegierski(){
    int space=4;
    for(int j = 0; j<(*NM).N; j++){
        cout << "|";
        for(int i = 0 ; i<(*NM).M; i++){
            cout << setw(space);
            cout << (*NM)[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<(*NM).M; i++){
        cout << setw(space) << "------";
    }
    cout << endl;
    for(int i = 0 ; i<(*NM).M; i++){
        if((*NM)[(*NM).indexMinCol(i)][i] <= 0){
            space+= 5;
        }
        else{
            cout << setw(space) <<"-"<< (*NM)[(*NM).indexMinCol(i)][i];
        }
    }
    cout << endl;
}
nodeBT* little::addNode(char& row, char& col, double& limit){
    //nodeBT* tmp = head;
    static nodeBT* last = next;
    if(*last->limit < limit && last->left == NULL){
        last->left = new nodeBT(row,col,limit,*NM);
        last->left->top = last;
    }
    if(*last->limit == limit && last->right == NULL){
        last->right = new nodeBT(row,col,limit,*NM);
        last->right->top = last;
        last = last->right;
    }
    return last;
}
void little::showArray(){
    cout << endl;
    cout << setw(6) << (*NM).nameM[0];
    for(int i = 1 ; i<(*NM).M; i++){
        cout << setw(5) << (*NM).nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<(*NM).M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<(*NM).N; j++){
        cout << (*NM).nameN[j] <<"|";
        for(int i = 0 ; i<(*NM).M; i++){
            cout << setw(4);
            cout << (*NM)[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<(*NM).M; i++){
        cout <<"------";
    }
    cout << endl;
}

void little::showData(){
    cout << "Wiersze: "<< (*NM).N << endl;
    cout << "Kolumny: "<< (*NM).M << endl;
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
