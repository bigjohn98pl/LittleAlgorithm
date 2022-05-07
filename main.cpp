#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

macierz fill(macierz &tmp){
    unsigned width,hight,option=0;

    while (!option) {
        cout << "Podaj wymiary macierzy odleglosci:" << endl <<
                "Szerokosc:";
        cin >> width;
        cout << "Wysokosc:";
        cin >> hight;

        tmp.reSize(width,hight);

        for (unsigned int i = 0; i < hight; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                if(i == j){
                    tmp[i][j] = INF;
                    cout << "Pozycja " << "[" << i+1 << " " << j+1 << "]" << " -> Inf" << endl;
                }
                else{
                    cout << "Pozycja " << "[" << i+1 << " " << j+1 << "]" << " -> :";
                    cin >> tmp[i][j];
                    while (tmp[i][j] < 0) {
                        cout << "Blad przy wprowadzaniu danych. Wartosci nie moga byc ujemne. Wprowadz dane jeszcze raz." << endl <<
                                "Pozycja " << "[" << i+1 << " " << j+1 << "]" << " -> :";
                        cin >> tmp[i][j];
                    }
                }
            }
        }
        cout << endl << "Czy wprowadzone dane sa poprawne?" << endl;
        tmp.show();
        cout << "1.Tak" << endl <<
                "0.Nie" << endl <<
                ":";
        cin >> option;
    }
    return tmp;
}

int main()
{
    int option = -1;

    macierz data;
    static vector<vector<double>> Tab1 = {{INF,1,1,2,3},{3,INF,2,5,6},{5,4,INF,3,7},{8,4,3,INF,2},{7,7,5,6,INF}};
    static vector<vector<double>> Tab2 = {{INF,8,7,5},{2,INF,6,4},{3,10,INF,4},{7,5,4,INF}};
    static vector<vector<double>> Tab3 = {{INF,10,15,20},{10,INF,35,25},{15,35,INF,30},{20,25,30,INF}};
    little problem;

    while (option != 0) {
        cout << "==========================================================" << endl
             << "|                  Problem komiwojazera                   |"<< endl
             << "==========================================================" << endl << endl
             << "Opcje:" << endl <<
                "1.Wprowadz dane i oblicz" << endl <<
                "2.Testowe zestawy danych "<< endl <<
                "0.Zakoncz"<< endl <<
                ":" ;
        cin >> option;

        switch (option) {
        case 1:
            fill(data);
            problem.set(data);
            problem.stepOne(false);
            problem.showGraph();
            break;
        case 2:

            cout << "Wybierz ktory problem chcesz obliczyc:" << endl <<
                    "1.Macierz 4x4 - zajecia" << endl <<
                    "2.Macierz 5x5 - z ksiazki "<< endl <<
                    ":" ;
            cin >> option;
            switch (option) {
            case 1:
                problem.set(Tab1);
                cout << "Dane wejściowe:" << endl;
                problem.showGraph();
                problem.stepOne(false);
                problem.showGraph();
                break;
            case 2:
                problem.set(Tab2);
                cout << "Dane wejściowe:" << endl;
                problem.showArray();
                problem.stepOne(false);
                problem.showGraph();
                break;
            default:
                break;
            }
            break;
        case 0:

            break;
        default:
            break;
        }
    }

    return 0;
}
