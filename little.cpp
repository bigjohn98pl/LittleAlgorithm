#include "krawedz.hpp"
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
    head = new krawedz;
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
    head = new krawedz;

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
    head = new krawedz;
}
little::~little(){

}
double little::metodaWegierskaKrok1(){
    double Min =0 ;
    for(int j = 0; j<NM.N; j++){
        Min = NM[j][NM.indexMinRow(j)];
        ograniczenia[0] = ograniczenia[0] + Min;
        for(int i=0 ; i<NM.M ; i++){
            NM[j][i] = NM[j][i] - Min;
        }
    }

    return Min;
}

double little::metodaWegierskaKrok2(){
    double Min =0 ;
    int count = 0;
    for(int i = 0; i < NM.N; i++){

        for(int j = 0 ; j < NM.M ; j++){
            if(NM[j][i] > 0){
                count++;
            }
        }
        if(count >= NM.M){
            Min = NM[NM.indexMinCol(i)][i];
            ograniczenia[0] = ograniczenia[0] + Min;
            for(int j=0 ; j<NM.N ; j++){
                NM[j][i] = NM[j][i] - Min;
            }
        }
        count = 0;
    }
    return Min;
}
void little::krokDrugi(){
    double suma=0,sumaMax=0;
    int* iMin;
    for(int i = 0; i < NM.N; i++){
        for(int j = 0 ; j < NM.M ; j++){
            if(NM[i][j] == 0){
                iMin = NM.indexMin(i,j);
                suma = NM[iMin[0]][j] + NM[i][iMin[1]];
                if(suma > sumaMax){
                    sumaMax = suma;
                    iKrawedz[0] = i;
                    iKrawedz[1] = j;
                }
            }
        }
    }
    kara = sumaMax;
    head->ograniczenieDolne = ograniczenia[0];
}
void little::krokTrzeci(){
    ograniczenia[1] += ograniczenia[0]+kara;
    int wiersz = iKrawedz[0],   kolumna = iKrawedz[1];
    head->lewa = new krawedz(NM.nameN[wiersz],NM.nameN[kolumna],ograniczenia[1]);
    head->prawa = new krawedz(NM.nameN[wiersz],NM.nameN[kolumna],ograniczenia[0]);
}
void little::krokCzwarty(){
    NM.delRowCol(iKrawedz[0],iKrawedz[1]);

}
void little::krokPiaty(){
    int h = 0;
    while(!NM.haveZeros()){
        metodaWegierskaKrok1();
        metodaWegierskaKrok2();
        h++;
    }
    ograniczenia[0] += h;

}
void little::krokSzosty(){
    head->prawa->ograniczenieDolne = ograniczenia[0];
}
void little::krokSiodmy(){
    krawedz *next = head->prawa;
    if(NM.N == 2 && NM.M == 2){
        for(int i=0; i<NM.N ; i++){
            for(int j=0; j< NM.M; j++){
                if( (i == j) && ( NM[i][j] == 0 ) ){
                    next->prawa = new krawedz();
                    next = next->prawa;
                }
            }
        }
    }
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
