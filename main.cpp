#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"


int main()
{
    string fileName = "arkusz.txt";
    int option = -1;
    bool showCieties = true;
    macierz data;

    static vector<vector<double>> Tab1 = {{INF, 1, 1, 2, 3}, {3, INF, 2, 5, 6}, {5, 4, INF, 3, 7}, {8, 4, 3, INF, 2}, {7, 7, 5, 6, INF}};
    static vector<vector<double>> Tab2 = {{INF,8,7,5},{2,INF,6,4},{3,10,INF,4},{7,5,4,INF}};
    static vector<vector<double>> Tab3 = {{INF, 7, 3, 6, 5, 2}, {4, INF, 8, 13, 5, 4}, {2, 1, INF, 16, 17, 19}, {18, 3, 25, INF, 2, 8}, {6, 10, 31, 23, INF, 7}, {3, 7, 4, 5, 6, INF}};

    little problem;

    while (option != 0) {
        macierz dataFile(fileName);
        system("cls");
        cout << "==============================================================" << endl
             << "|                    Problem komiwojazera                     |" << endl
             << "==============================================================" << endl
             << endl
             << "   Opcje:" << endl
             << "1. Reczne wprowadzanie danych" << endl
             << "2. Przykladowe zestawy danych " << endl
             << "3. Dane z pliku    ->  " << fileName << endl
             << "4. Ustawienia programu" << endl
             << endl
             << "0. Zakoncz" << endl
             << ">> ";

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
            problem.result2(showCieties);
            system("PAUSE");
            break;
        case 2:
            cout << "   Wybierz ktory problem chcesz obliczyc:" << endl <<
                    "1. Macierz 4x4 - z ksiazki" << endl <<
                    "2. Macierz 5x5 - z zajec 1"<< endl <<
                    "3. Macierz 6x6 - z zajec 2"<< endl <<
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
                problem.set(Tab1);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(false);
                problem.showGraph(showCieties);
                problem.result2(showCieties);
                system("PAUSE");
                break;
            case 2:
                problem.set(Tab2);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(false);
                problem.showGraph(showCieties);
                problem.result2(showCieties);
                system("PAUSE");
                break;
            case 3:
                problem.set(Tab3);
                problem.showArray(showCieties);
                system("PAUSE");
                problem.stepOne(true);
                problem.showGraph(showCieties);
                problem.result2(showCieties);
                system("PAUSE");
                break;
            default:
                break;
            }
            break;
        case 3:
            problem.set(dataFile);
            cout << "   Macierz wejsciowa:" << endl;
            problem.showArray(showCieties);
            system("PAUSE");
            problem.stepOne(true);
            problem.showGraph(showCieties);
            problem.result2(showCieties);
            system("PAUSE");
            break;
        case 4:
            while(option != 0)
            {
                system("cls");
                cout << "   Ustawienia programu:" << endl;
                cout << "1. Wyswietlaj nazwy z pliku city.txt   -> " << (showCieties ? "Tak":"Nie") << endl <<
                        "2. Zmien nazwe pliku z danymi  ->  " << fileName << endl <<
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
        }
    }
    return 0;
}
