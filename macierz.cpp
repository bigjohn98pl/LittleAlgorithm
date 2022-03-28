#include "macierz.hpp"

macierz::macierz() {
    N = 5;
    M = 5;
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
macierz::macierz(int n, int m) {
    N = n;
    M = m;
    tablica.reserve(N);
    for (int i = 0; i < N; i++)
    {
        tablica[i].reserve(M);
        nameN.push_back('A'+i);
    }
    for (int i = 0; i < M; i++)
    {
        nameN.push_back('A'+i);
    }

}
vector<double> &macierz::operator [](int i) {
    return (tablica.at(i));
}
macierz::macierz(double tab[ROW][COL]) {
    N = ROW;
    M = COL;
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
    tablica.reserve(N);
    nameN.reserve(N);
    nameM.reserve(M);
    for (int i = 0; i < X.N; i++)
    {
        tablica[i].reserve(M);
    }
    for (int i = 0; i < N; i++)
    {
        nameN[i] = X.nameN[i];
        for (int j = 0; j < M; j++)
        {
            tablica[i][j] = X.tablica[i][j];
            nameM[j] = X.nameM[j];
        }
    }
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
    nameN.resize(n);
    nameM.resize(m);

    for (int i = 0; i < n; i++)
    {
        tablica[i].resize(m);
    }
    for (int i = 0; i < n; i++)
    {
        //nameN[i] = 'A'+i;
        for (int j = 0; j < m; j++)
        {
            //nameM[j] = 'A'+j;
            if (i < temp.N && j < temp.M)
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
void macierz::show() {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << setw(3);
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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
        if(colums != Row){
            value = tablica[Row][colums];
            if((value <= minCol || minCol == -1) && colums != Col){
                minCol = value;
                indexMin[1] = colums;
            }
        }
    }
    return indexMin;
}
void macierz::delRowCol(int row, int col){

    if(N > 1 && M > 1 && row <= N-1 && col <= M-1 ){
        tablica[col][row] = 999;
        for (int i=0; i<N ;i++ ) {
            tablica[i].erase(tablica[i].begin()+col);
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
    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < M ; j++){
            if(tablica[i][j] == 0){
                countRowZeros++;
            }
        }
    }

    if(countRowZeros > 0 && countRowZeros == N){
        return true;
    }
    else{
        return false;
    }
}
bool macierz::haveZerosColums(){
    int countColZeros=0;
    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < M ; j++){
            if(tablica[j][i] == 0){
                countColZeros++;
            }
        }
    }

    if(countColZeros > 0 && countColZeros == N){
        return true;
    }
    else{
        return false;
    }
}
bool macierz::haveZeros(){
    int countRowZeros=0,countColZeros=0;
    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < M ; j++){
            if(tablica[i][j] == 0){
                countRowZeros++;
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < M ; j++){
            if(tablica[j][i] == 0){
                countColZeros++;
            }
        }
    }
    if(countRowZeros > 0 && countColZeros >0){
        return true;
    }
    else{
        return false;
    }
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
