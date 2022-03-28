#include "nodeBT.hpp"
#include "little.hpp"

little::little()
{
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    NM.set(Tab2);
    NM.N = ROW;
    NM.M = COL;
    kara = 0;
    head = new nodeBT;
}
little::little(int row, int col)
{
    NM.N = row;
    NM.M = col;
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);

    NM.reSize(row,col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            NM[i][j] = i*j+i;
        }
    }
    NM.N = row;
    NM.M = col;
    kara = 0;
    head = new nodeBT;

}
little::little(vector<vector<double>> Tab){
    NM.N = Tab.size();
    NM.M = Tab[0].size();
    fill(ograniczenia, ograniczenia+2, 0);
    fill(iKrawedz, iKrawedz+2, 0);

    NM.reSize(ROW,COL);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            NM[i][j] = Tab[i][j];
        }
    }
    NM.N = ROW;
    NM.M = COL;
    kara = 0;
    head = new nodeBT;
}
little::~little(){

}
void little::stepOne(bool show){
    if(show){
        wypiszKrok1Wegierski();
        if(!NM.haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        wypiszKrok2Wegierski();
        if(!NM.haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }
    else{
        if(!NM.haveZerosRows()){
            ograniczenia[0] += metodaWegierskaKrok1();
        }
        if(!NM.haveZerosColums()){
            ograniczenia[0] += metodaWegierskaKrok2();
        }
    }
}
void little::stepTwo(){
    double suma=0,karaMax=0;
    next = head;
    int* iMin;
    for(int i = 0; i < NM.N; i++){
        for(int j = 0 ; j < NM.M ; j++){
            if(NM[i][j] == 0){
                iMin = NM.indexMin(i,j);
                suma = NM[iMin[0]][j] + NM[i][iMin[1]];
                if(suma > karaMax){
                    karaMax = suma;
                    iKrawedz[0] = i;
                    iKrawedz[1] = j;
                }
            }
        }
    }
    kara = karaMax;
    next->limit = ograniczenia[0];
}
void little::stepTree(){
    ograniczenia[1] += ograniczenia[0]+kara;
}
void little::stepFour(){
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];

    head->left = new nodeBT(NM.nameN[wiersz],NM.nameN[kolumna],ograniczenia[1]);

    //next= head->right;
    NM.delRowCol(iKrawedz[0],iKrawedz[1]);
    head->right = new nodeBT(NM.nameN[wiersz],NM.nameN[kolumna],ograniczenia[0]);

}
void little::stepFive(){
    int h = 0;
    if(!NM.haveZerosRows()){
        h += metodaWegierskaKrok1();
    }
    if(NM.haveZerosColums()){
        h += metodaWegierskaKrok2();
    }
    ograniczenia[0] += h;

}
void little::stepSix(){
    head->right->limit = ograniczenia[0];
}
void little::stepSeven(){
    nodeBT *next = head->right;
    if(NM.N == 2 && NM.M == 2){
        for(int i=0; i<NM.N ; i++){
            for(int j=0; j< NM.M; j++){
                if( (i == j) && ( NM[i][j] == 0 ) ){
                    next->right = new nodeBT();
                    next = next->right;
                }
            }
        }
    }
}
void little::stepEight(){

}
void little::stepNine(){
    NM[iKrawedz[0]][iKrawedz[1]] = 999;
    stepOne(false);
}
double little::metodaWegierskaKrok1(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i<NM.N; i++){
        Min = NM[i][NM.indexMinRow(i)];
        SUM = SUM + Min;
        for(int j=0 ; j<NM.M ; j++){
            NM[i][j] = NM[i][j] - Min;
        }
    }

    return SUM;
}

double little::metodaWegierskaKrok2(){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i < NM.N; i++){
        Min = NM[NM.indexMinCol(i)][i];
        SUM = SUM + Min;
        for(int j=0 ; j<NM.N ; j++){
            NM[j][i] = NM[j][i] - Min;
        }
    }
    return SUM;
}
void little::wypiszKrok1Wegierski(){
    for(int j = 0; j<NM.N; j++){
        cout <<"|";
        for(int i = 0 ; i<NM.M; i++){
            cout << setw(4);
            cout << NM[j][i] << " ";
        }
        if(NM[j][NM.indexMinRow(j)] <= 0){
            cout << endl;
        }
        else{
            cout <<" |- "<< NM[j][NM.indexMinRow(j)] << endl;
        }
    }
    cout << endl;
}
void little::wypiszKrok2Wegierski(){

    for(int j = 0; j<NM.N; j++){
        cout << "|";
        for(int i = 0 ; i<NM.M; i++){
            cout << setw(4);
            cout << NM[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<NM.M; i++){
        cout << setw(4) << "------";
    }
    cout << endl;
    for(int i = 0 ; i<NM.M; i++){
        if(NM[NM.indexMinCol(i)][i] <= 0){
            cout << setw(4);
        }
        else{
            cout << setw(4) <<"-"<< NM[NM.indexMinCol(i)][i];
        }
    }
    cout << endl;
}

void little::showArray(){
    cout << endl;
    cout << setw(6) << NM.nameM[0];
    for(int i = 1 ; i<NM.M; i++){
        cout << setw(5) << NM.nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<NM.M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<NM.N; j++){
        cout << NM.nameN[j] <<"|";
        for(int i = 0 ; i<NM.M; i++){
            cout << setw(4);
            cout << NM[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<NM.M; i++){
        cout <<"------";
    }
    cout << endl;
}

void little::showData(){
    cout << "Wiersze: "<< NM.N << endl;
    cout << "Kolumny: "<< NM.M << endl;
    cout << "Oszacowanie dolne: " << ograniczenia[0] << endl;
    cout << "Ograniczenie dolne: " << ograniczenia[1] << endl;
    cout << "Kara: " << kara << endl;
    cout << "Krawedz: " << iKrawedz[0]+1 << iKrawedz[1]+1 << endl;
}

void little::showGraph(){
    int tabs =2;
    while(head->left != NULL && head->right != NULL){
        head->show(tabs,true);
        cout << endl;
        for(int i =0 ; i<tabs;i++){
            cout << "\t";
        }
        cout << setw(4)<< "/" << setw(4) << "\\";
        cout << endl;
        tabs--;
        if(head->left){
            head->left->show(tabs,false);
        }
        if(head->right){
            head->right->show(tabs,true);
        }
        cout << endl;
        head = head->right;
    }
}
