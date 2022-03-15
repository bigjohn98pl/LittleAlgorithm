#include <iostream>
#include <iomanip>

#define N 2
#define M 2

using namespace std;

class little{
public:
    little(){};
    ~little(){};
    void set( int wier, int kol);
    int indexMinimumWiersza(int wiersz, int wyklucz = -1);
    int indexMinimumKolumny(int kolumna, int wyklucz = -1);
    double metodaWegierskaKrok1();
    double metodaWegierskaKrok2();
    double bilansZer();
    void wypiszKrok1();
    void wypiszKrok2();
    void wypiszTablice();
    void wypiszDane();
private:
    int wiersze,kolumny;
    double **Tab;
    double oszacowanieDolne;
};


void little::set(int wier,int kol){

    wiersze = wier;
    kolumny = kol;

    Tab = new double*[wiersze];
    for(int i = 0; i < wiersze; ++i)
        Tab[i] = new double[kolumny];

    double Tab2[5][5] = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};

    for(int j = 0; j<wiersze; j++){
        for(int i=0 ; i<kolumny ; i++){
            //cout << "podaj wartosc ["<< i+1 << " " << j+1 <<"] :"; cin >> Tab[j][i];
            Tab[i][j] = Tab2[i][j];
        }
    }

}

int little::indexMinimumWiersza(int wiersz, int wyklucz){

    int minIndex;
    if(wyklucz != -1){
        minIndex = 1;
    }
    else{
        minIndex = 0;
    }

    int lastMinIndex = minIndex;
    for(int i = 1 ; i<kolumny; i++){
        if(Tab[wiersz][i] < Tab[wiersz][minIndex]){
            minIndex = i;
        }
    }

    if(minIndex == wyklucz){
        return lastMinIndex;
    }
    else{
        return minIndex;
    }
}

int little::indexMinimumKolumny(int kolumna , int wyklucz){

    int minIndex;
    if(wyklucz != -1){
        minIndex = 1;
    }
    else{
        minIndex = 0;
    }

    int lastMinIndex = minIndex;

    for(int j = 1 ; j<wiersze; j++){
        lastMinIndex = minIndex;
        if(Tab[j][kolumna] < Tab[minIndex][kolumna]){
            minIndex = j;
        }
    }

    if(minIndex == wyklucz){
        return lastMinIndex;
    }
    else{
        return minIndex;
    }
}


double little::metodaWegierskaKrok1(){
    double Min =0 ;
    oszacowanieDolne = 0;
    for(int j = 0; j<wiersze; j++){
        Min = Tab[j][indexMinimumWiersza(j)];
        oszacowanieDolne = oszacowanieDolne + Min;
        for(int i=0 ; i<kolumny ; i++){
            Tab[j][i] = Tab[j][i] - Min;
        }
    }

    return Min;
}

double little::metodaWegierskaKrok2(){
    double Min =0 ;
    int count = 0;
    for(int i = 0; i < wiersze; i++){

        for(int j = 0 ; j < kolumny ; j++){
            if(Tab[j][i] > 0){
                count++;
            }
        }
        if(count >= kolumny){
            Min = Tab[indexMinimumKolumny(i)][i];
            oszacowanieDolne = oszacowanieDolne + Min;
            for(int j=0 ; j<wiersze ; j++){
                Tab[j][i] = Tab[j][i] - Min;
            }
        }
        count = 0;
    }
    return Min;
}
double little::bilansZer(){
    double suma=0;

    for(int j = 0; j < wiersze; j++){
        for(int i = 0 ; i < kolumny ; i++){
            if(Tab[j][i] == 0){
                suma = Tab[indexMinimumKolumny(i)][i] + Tab[indexMinimumWiersza(j)][j];
                cout << "Suma wiersza i kolumny ["<< j+1 << " " << i+1 <<"] to : "<< Tab[indexMinimumKolumny(i,i)][j] << "[" << indexMinimumKolumny(i)+1 << " " << j+1 << "] "
                                                                                  << Tab[i][indexMinimumWiersza(j,j)] << "[" << indexMinimumWiersza(j)+1 << " " << i+1 << "]" << endl;
            }
        }
    }
    return suma;
}
void little::wypiszKrok1(){
    for(int j = 0; j<wiersze; j++){
        cout <<"|";
        for(int i = 0 ; i<kolumny; i++){
            cout << setw(4);
            cout << Tab[j][i] << " ";
        }
        cout <<" |- "<< Tab[j][indexMinimumWiersza(j)] << endl;
    }
    cout << endl;
}
void little::wypiszKrok2(){
    for(int j = 0; j<wiersze; j++){
        cout <<"|";
        for(int i = 0 ; i<kolumny; i++){
            cout << setw(4);
            cout << Tab[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<kolumny; i++){
        cout <<"------";
    }
    cout << endl;
    for(int i = 0 ; i<kolumny; i++){
        cout <<"   -"<< Tab[indexMinimumKolumny(i)][i];
    }
    cout << endl;
}

void little::wypiszTablice(){
    cout << endl;
    for(int i = 0 ; i<kolumny; i++){
        cout <<"_____";
    }
    cout << endl;
    for(int j = 0; j<wiersze; j++){
        cout <<"|";
        for(int i = 0 ; i<kolumny; i++){
            cout << setw(4);
            cout << Tab[j][i] << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<kolumny; i++){
        cout <<"_____";
    }
    cout << endl;
}

void little::wypiszDane(){
    cout << "wiersze: "<< wiersze << endl;
    cout << "kolumny: "<< kolumny << endl;
    cout << "Oszacowanie dolne: " << oszacowanieDolne << endl;
}
int main()
{

    little problem1;
    problem1.set(5,5);
    problem1.wypiszTablice();
    problem1.wypiszKrok1();
    problem1.metodaWegierskaKrok1();
    problem1.wypiszKrok2();
    problem1.metodaWegierskaKrok2();
    problem1.wypiszTablice();
    problem1.wypiszDane();
    problem1.bilansZer();
    return 0;
}
