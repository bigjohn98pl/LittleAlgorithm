#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

#include "little.cpp"
#include "nodeBT.cpp"
#include "macierz.cpp"

int main()
{
    string fileName = "arkusz.txt";
    int option = -1;
    bool showCieties = true;
    macierz data;

    static vector<vector<double>> Tab1 = {{INF, 1, 1, 2, 3}, {3, INF, 2, 5, 6}, {5, 4, INF, 3, 7}, {8, 4, 3, INF, 2}, {7, 7, 5, 6, INF}};
    static vector<vector<double>> Tab2 = {{INF,8,7,5},{2,INF,6,4},{3,10,INF,4},{7,5,4,INF}};
    static vector<vector<double>> Tab3 = {{INF,10,15,20},{10,INF,35,25},{15,35,INF,30},{20,25,30,INF}};
    static vector<vector<double>> Tab4 = {{INF,130,180,300},{130,INF,320,350},{180,320,INF,360},{300,350,360,INF}};

    little problem;

    while (option != 0) {
        system("cls");
        cout << "==============================================================" << endl
             << "|                    Problem komiwojazera                     |"<< endl
             << "==============================================================" << endl << endl
             << "   Opcje:" << endl <<
                "1. Reczne wprowadzanie danych" << endl <<
                "2. Przykladowe zestawy danych "<< endl <<
                "3. Dane z pliku    >>  "<< fileName << endl <<
                "4. Ustawienia programu"<< endl <<
                endl<<
                "0. Zakoncz"<< endl;
        cin >> option;
        system("cls");
        switch (option) {
        default:
            option = -1;
            break;
        case 0:
            break;
        case 1:
            data.fill(showCieties);
            problem.set(data);
            problem.showArray(showCieties);
            problem.stepOne(false);
            problem.showGraph(showCieties);
            problem.result(showCieties);
            system("PAUSE");
            break;
        case 2:
            cout << "   Wybierz ktory problem chcesz obliczyc:" << endl <<
                    "1. Macierz 4x4 - z ksiazki" << endl <<
                    "2. Macierz 5x5 - z zajec"<< endl <<
                    "3. Macierz 4x4 - z wikipedi (blad,zapetla sie)"<< endl <<
                    endl <<
                    "0. Cofnij" << endl <<
                    ">> " ;
            cin >> option;
            system("cls");
            cout << "   Macierz wejsciowa:" << endl;
            switch (option) {
            case 0:
                option = -1;
                break;
            case 1:
                problem.set(Tab2);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(false);
                problem.showGraph(showCieties);
                problem.result(showCieties);
                system("PAUSE");
                break;
            case 2:
                problem.set(Tab1);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(false);
                problem.showGraph(showCieties);
                problem.result(showCieties);
                system("PAUSE");
                break;
            case 3:
                problem.set(Tab4);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(false);
                problem.showGraph(showCieties);
                problem.result(showCieties);
                system("PAUSE");
                break;
            default:
                break;
            }
            break;
        case 4:
            while(option != 0){
                system("cls");
                cout << "   Ustawienia programu:" << endl;
                cout << "1. Wyswietlaj nazwy z pliku city.txt   >> " << (showCieties ? "Tak":"Nie") << endl <<
                        "2. Zmien nazwe pliku z danymi  >>  " << fileName << endl <<
                         endl <<
                        "0. Cofnij" << endl <<
                         ">>    ";
                cin >> option;
                switch (option) {
                case 1:
                    showCieties = not showCieties;
                    break;
                case 2:
                    system("cls");
                    cout << "Podaj nazwe pliku z danymi >>  ";
                    cin >> fileName;
                    break;
                default:
                    break;
                }
            }
            option = -1;
            break;
        case 3:
            macierz data2(fileName);
            problem.set(data2);
            cout << "   Macierz wejsciowa:" << endl;
            problem.showArray(showCieties);
            system("PAUSE");
            problem.stepOne(false);
            problem.showGraph(showCieties);
            problem.result(showCieties);
            system("PAUSE");
            break;
        }
    }
    return 0;
}
