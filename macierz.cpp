#include "macierz.hpp"
#include "little.hpp"
#include <algorithm>

macierz::macierz() {
    N = 1;
    M = 1;
    for (int i = 0; i < N; i++)
    {
        nameN.push_back('A'+i);
    }
    for (int i = 0; i < M; i++)
    {
        nameM.push_back('A'+i);
    }
}
macierz::macierz(const int _n,const int _m) : N(_n), M(_m)
{
    tablica.reserve(N);
    for (int i = 0; i < N; i++)
    {
        tablica[i].reserve(M);
        nameN.push_back('A'+i);
    }
    for (int i = 0; i < M; i++)
    {
        nameM.push_back('A'+i);
    }

}

vector<double> &macierz::operator [](int i) {
    return (tablica.at(i));
}

macierz::macierz( vector< vector< double>> Tab){
    N = Tab.size();
    M = Tab[0].size();
    tablica.swap(Tab);
    for (int i = 0; i < N; i++)
    {
        nameN.push_back('A'+i);
    }
    for (int i = 0; i < M; i++)
    {
        nameM.push_back('A'+i);
    }
}

macierz::macierz(string Fname)
{
    vector<vector<double>> temp;
    fstream arkusz(Fname);
    string record;
    vector<double> row;

    if (arkusz.good())
    {
        arkusz >> N;
        M = N;
        for (int i = 0; i < N; i++)
        {
            nameN.push_back('A' + i);
            nameM.push_back('A' + i);
            for (int c = 0; c < N; c++)
            {
                arkusz >> record;

                if(record == "0" || record == "INF"){
                    row.push_back(INF);
                }
                else{
                    row.push_back(stod(record));
                }


            }
            temp.push_back(row);
            row.clear();
        }
        tablica.swap(temp);
    }
    else
    {
        cout << "Blad odczytu pliku: " << Fname << endl
             << "    Nastapi zakonczenie dzialania programu!";
    }
    arkusz.close();
}

macierz::macierz(double **tab, int _n, int _m) {
    N = _n;
    M = _m;
    tablica.reserve(N);
    for (int i = 0; i < N; i++)
    {
        tablica[i].reserve(M);
    }

    for (int i = 0; i < N; i++)
    {
        nameN.push_back('A'+i);
    }
    for (int i = 0; i < M; i++)
    {
        nameM.push_back('A'+i);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            tablica[i][j] = tab[i][j];
        }
    }
}
macierz::macierz(macierz& X) {
    N = X.N;
    M = X.M;

    tablica = X.tablica;
    nameN = X.nameN;
    nameM = X.nameM;

};
macierz::~macierz() {
    N = 0;
    M = 0;
}

void macierz::random(int from, int to) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(from, to);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            tablica[i][j] = dist(gen);
        }
    }
}
void macierz::reSize(int n, int m) {
    macierz temp(*this);

    tablica.resize(n);
    for (int i = 0; i < n; i++)
    {
        tablica[i].resize(m);
    }

    nameN.resize(n);
    nameM.resize(m);

    for (int i = 0; i < n; i++)
    {
        nameN[i] = 'A'+i;
        for (int j = 0; j < m; j++)
        {
            nameM[j] = 'A'+j;
            if (i < temp.N && j < temp.M && !temp.tablica.empty())
            {
                tablica[i][j] = temp.tablica[i][j];
            }
            else
            {
                tablica[i][j] = 0;
            }
        }
    }
    N = n;
    M = m;
}
void macierz::set(vector<vector<double>> tab){
    tablica.insert(tablica.begin(),tab.begin(),tab.end());
}
void macierz::show(bool showCities)
{
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        if (showCities)
        {
            cout << setw(6) << little::city(nameM[i]) << "|";
        }
        else
        {
            cout << setw(6) << nameM[i] << "|";
        }
    }
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "----------";
    }
    cout << endl;
    for (int j = 0; j < N; j++)
    {

        for (int i = 0; i < M; i++)
        {
            cout << setw(6);
            if (get(j, i) >= (INF - 20000))
            {
                cout << "Inf"
                     << " ";
            }
            else
            {
                cout << get(j, i) << " ";
            }
        }
        if (showCities)
        {
            cout << "|" << left << setw(6) << little::city(nameN[j]) << right;
        }
        else
        {
            cout << "|" << setw(6) << nameN[j];
        }
        cout << endl;
    }
    for (int i = 0; i < M; i++)
    {
        cout << "----------";
    }
    cout << endl;
}

void macierz::fill(bool showCieties)
{
    unsigned int N, option = 0;
    while (!option)
    {
        cout << "Podaj wymiar macierzy odleglosci:" << endl
             << ">>  ";
        cin >> N;

        this -> reSize(N, N);

        for (unsigned int i = 0; i < N; ++i)
        {
            for (unsigned int j = 0; j < N; ++j)
            {
                if (i == j)
                {
                    tablica[i][j] = INF;
                    cout << "Pozycja "
                         << "[" << i + 1 << " " << j + 1 << "]"
                         << " -> Inf" << endl;
                }
                else
                {
                    cout << "Pozycja "
                         << "[" << i + 1 << " " << j + 1 << "]"
                         << " -> :";
                    cin >> tablica[i][j];
                    while (tablica[i][j] < 0)
                    {
                        cout << "Blad przy wprowadzaniu danych. Wartosci nie moga byc ujemne. Wprowadz dane jeszcze raz." << endl
                             << "Pozycja "
                             << "[" << i + 1 << " " << j + 1 << "]"
                             << " -> :";
                        cin >> tablica[i][j];
                    }
                }
            }
        }
        cout << endl
             << "   Czy wprowadzone dane sa poprawne?" << endl;
        this -> show(showCieties);
        cout << "1. Tak" << endl
             << "0. Nie" << endl
             << ">> ";
        cin >> option;
    }
}

int macierz::col() {
    return this->M;
}

int macierz::row() {
    return this->N;
}

void showRowCol(macierz X) {
    cout << "Macierz: " << X.row() << " na " << X.col() << endl;
}

int macierz::indexMinRow(int row){

    int minIndex=0,i=1;
    int lastMin = minIndex;

    while(i<M){
        lastMin = minIndex;

        if(tablica[row][i] <= tablica[row][minIndex]){
            minIndex = i;
        }
        i++;
    }

    if(tablica[row][lastMin] < tablica[row][minIndex]){
        return lastMin;
    }
    else{
        return minIndex;
    }
}
int macierz::indexMinCol(int col){

    int minIndex=0,j=1;
    int lastMin = minIndex;

    while(j< N ){
        lastMin = minIndex;

        if(tablica[j][col] <= tablica[minIndex][col]){
            minIndex = j;
        }
        j++;
    }

    if(tablica[lastMin][col] < tablica[minIndex][col]){
        return lastMin;
    }
    else{
        return minIndex;
    }
}
int* macierz::indexMin(int Row, int Col){
    int minRow = -1,minCol = -1;
    static int indexMin[2];
    int value=0;


    for(int rows = 0; rows < N ; rows++){
        if(rows != Row){
            value = tablica[rows][Col];
            if((value <= minRow || minRow == -1) && minRow != Row){
                minRow = value;
                indexMin[0] = rows;
            }
        }
    }

    for(int colums = 0; colums < M ; colums++){
        if(colums != Col){
            value = tablica[Row][colums];
            if((value <= minCol || minCol == -1) && colums != Col){
                minCol = value;
                indexMin[1] = colums;
            }
        }
    }
    return indexMin;
}
void macierz::delRowCol(int row, int col, list<char> &result,list<char> &savePath, bool &stepByStep){

    int j=0;
    bool change = false;
    char delRow = nameN[row], delCol = nameM[col];
    int indexParasiteRow = -1,indexParasiteCol = -1;
    if(stepByStep){cout << "Redukcja macierzy, usuwanie wiersza i kolumny : ["<< delRow <<"] i [" << delCol << "]" << endl;}
    if(N > 1 && M > 1 && row <= N-1 && col <= M-1 ){

        for(int i=0 ; i< (int)nameN.size(); i++){
            if(nameN[i] == delCol){
                indexParasiteRow = i;
            }
            if(nameM[i] == delRow){
                indexParasiteCol = i;
            }
        }

        if( (indexParasiteRow >= 0) && (indexParasiteCol >=0) ){
            if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[indexParasiteRow] <<"] i [" << nameM[indexParasiteCol] << "]" << endl;}
            tablica[indexParasiteRow][indexParasiteCol] = INF;
        }
        else{
            while (!change) {
                for (int i=0; i<N ;i++ ) {
                    if(nameN[i] == delCol && nameM[j] == delRow){
                        if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[i] <<"] i [" << nameM[j] << "]" << endl;}
                        tablica[i][j] = INF;
                        change = true;
                        break;
                    }
                    if(result.back() == nameN[i] && result.front() == nameM[j]){
                        if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[i] <<"] i [" << nameM[j] << "]" << endl;}
                        tablica[i][j] = INF;
                        change = true;
                        break;
                    }
                    else if(result.front() == nameN[i] && result.back() == nameM[j]){
                        if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[i] <<"] i [" << nameM[j] << "]" << endl;}
                        tablica[i][j] = INF;
                        change = true;
                        break;
                    }
                    else{
                        if(savePath.back() == nameN[i] && savePath.front() == nameM[j]){
                            if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[i] <<"] i [" << nameM[j] << "]" << endl;}
                            tablica[i][j] = INF;
                            change = true;
                            break;
                        }
                        else if(savePath.front() == nameN[i] && savePath.back() == nameM[j]){
                            if(stepByStep){cout << "Usuwanie cyklu pasozytniczego, wstawienie Inf w: ["<< nameN[i] <<"] i [" << nameM[j] << "]" << endl;}
                            tablica[i][j] = INF;
                            change = true;
                            break;
                        }
                    }
                }
                j++;
            }
        }

        for (int j=0; j<N ;j++ ) {
            tablica[j].erase(tablica[j].begin()+col);
        }
        tablica.erase(tablica.begin()+row);
        nameN.erase(nameN.begin()+row);
        nameM.erase(nameM.begin()+col);
        N--;
        M--;
    }
}
bool macierz::haveZerosRows(){
    int countRowZeros=0;
    int countRowZerosLastRow = 0;

    for(int i = 0; i < N; i++){

        countRowZerosLastRow = countRowZeros;

        for(int j = 0 ; j < M ; j++){

            if(tablica[i][j] == 0){
                countRowZeros++;
            }
        }
        if(countRowZeros == countRowZerosLastRow){
            return false;
        }
    }

    return true;
}
bool macierz::haveZerosColums(){
    int countColZeros=0;
    int countColZerosLastCol = 0;

    for(int i = 0; i < N; i++){

        countColZerosLastCol = countColZeros;

        for(int j = 0 ; j < M ; j++){

            if(tablica[j][i] == 0){
                countColZeros++;
            }
        }

        if(countColZeros == countColZerosLastCol){
            return false;
        }
    }

    return true;
}

double macierz::get(const int &i,const int &j){
    return tablica[i][j];
}
//=========================================================================================

macierz& macierz::operator =(macierz& B) {
    this->~macierz();
    this->M = B.M;
    this->N = B.N;
    tablica.reserve(N);
    for (int i = 0; i < N; i++)
    {
        tablica[i].reserve(M);
    }
    for (int i = 0; i < B.N; i++)
    {
        for (int j = 0; j < B.M; j++)
        {
            tablica[i][j] = B.tablica[i][j];
        }
    }
    return *this;
}

macierz& operator +(macierz& A) {
    return A;
}
macierz& operator -(macierz& A) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] * (-1);
        }
    }
    return A;
}
macierz& operator +(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] + x;
        }
    }
    return A;
}

macierz& operator -(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] - x;
        }
    }
    return A;
}

macierz& operator *(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] * x;
        }
    }
    return A;
}

macierz& operator /(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] / x;
        }
    }
    return A;
}

macierz& operator +(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] + B.tablica[i][j];
        }
    }
    return A;
}

macierz& operator -(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] - B.tablica[i][j];
        }
    }
    return A;
}

macierz& operator *(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] * B.tablica[j][i];
        }
    }
    return A;
}

macierz& operator +=(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] + B.tablica[i][j];
        }
    }
    return A;
}
macierz& operator -=(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] - B.tablica[i][j];
        }
    }
    return A;
}
macierz& operator *=(macierz& A, macierz& B) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] * B.tablica[j][i];
        }
    }
    return A;
}
macierz& operator *=(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] * x;
        }
    }
    return A;
}

macierz& operator +=(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] + x;
        }
    }
    return A;
}
macierz& operator -=(macierz& A, double x) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            A.tablica[i][j] = A.tablica[i][j] - x;
        }
    }
    return A;
}

ostream& operator <<(ostream& so, macierz& A) {

    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            so << setw(3) << A.tablica[i][j] << " ";
        }
        so << endl;
    }
    so << endl;
    return so;
}

istream& operator >>(istream& is, macierz& A) {
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            cout << "[" << i << "," << j << "] ->";
            is >> A.tablica[i][j];
        }
    }
    return is;
}
double macierz::operator ()(int i, int j) {
    if (i < 0) {
        i = i * (-1);
    }
    if (j < 0) {
        j = j * (-1);
    }
    if (i == 0) {
        i = 1;
    }
    if (j == 0) {
        j = 1;
    }
    if (i >= N) {
        i = N;
        cout << "indeks wiersza poza zakresem" << endl;
    }
    if (j >= M) {
        j = M;
        cout << "indeks kolumny poza zakresem" << endl;
    }
    return tablica[i - 1][j - 1];
}

bool& operator ==(macierz& A, macierz& B) {

    bool** tab = new bool* [A.N];
    for (int i = 0; i < A.N; i++) {
        tab[i] = new bool[A.M];
    }

    for (int i = 0; i < A.N; i++) {
        for (int j = 0; j < A.M; j++) {
            if (A.tablica[i][j] == B.tablica[i][j]) {
                tab[i][j] = true;
            }
            else
            {
                tab[i][j] = false;
            }
        }
    }
    return **tab;
}

bool& operator !=(macierz& A, macierz& B) {

    bool** tab = new bool* [A.N];
    for (int i = 0; i < A.N; i++) {
        tab[i] = new bool[A.M];
    }

    for (int i = 0; i < A.N; i++) {
        for (int j = 0; j < A.M; j++) {
            if (A.tablica[i][j] != B.tablica[i][j]) {
                tab[i][j] = true;
            }
            else
            {
                tab[i][j] = false;
            }
        }
    }
    return **tab;
}

