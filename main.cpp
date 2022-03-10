#include <iostream>
#include <iomanip>

#define N 2
#define M 2

using namespace std;

class little{
public:
    void set( int wier, int kol);
    double MinimumWiersza(int wiersz);
    int indexMinimumWiersza(int wiersz);
    double metodaWegierskaKrok1();
    void wypisz();
private:
    int wiersze,kolumny;
    double **Tab;
};


void little::set(int wier,int kol){

    wiersze = wier;
    kolumny = kol;

    Tab = new double*[wiersze];
    for(int i = 0; i < wiersze; ++i)
        Tab[i] = new double[kolumny];

    for(int j = 0; j<wiersze; j++){
        for(int i=0 ; i<kolumny ; i++){
            cout << "podaj wartosc ["<< i+1 << " " << j+1 <<"] :"; cin >> Tab[j][i];
        }
    }
}

int little::indexMinimumWiersza(int wiersz){
    int minIndex = 0;
    for(int i = 1 ; i<kolumny; i++){
        if(Tab[wiersz][i] < Tab[wiersz][i-1]){
            minIndex = i;
        }
    }
    return minIndex;
}

double little::MinimumWiersza(int wiersz){
    double min = Tab[wiersz][0];
    for(int i = 1 ; i<kolumny; i++){
        if(Tab[wiersz][i] < Tab[wiersz][i-1]){
            min = Tab[wiersz][i];
        }
    }
    return min;
}

double little::metodaWegierskaKrok1(){
    double Min =0 ;
    for(int j = 0; j<wiersze; j++){
        Min = Tab[j][indexMinimumWiersza(j)];
        for(int i=0 ; i<kolumny ; i++){
            Tab[j][i] = Tab[j][i] - abs(Min);
        }
    }

    return Min;
}
void little::wypisz(){
    for(int j = 0; j<wiersze; j++){
        cout <<"|";
        for(int i = 0 ; i<kolumny; i++){
            cout << setw(4);
            cout << Tab[j][i] << " ";
        }
        cout <<" |- "<< MinimumWiersza(j) << endl;
    }
    cout << endl;
}
int main()
{

    little problem1;
    problem1.set(3,3);
    problem1.wypisz();
    problem1.metodaWegierskaKrok1();
    problem1.wypisz();
    return 0;
}
