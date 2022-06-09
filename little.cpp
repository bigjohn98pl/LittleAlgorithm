#include "nodeBT.hpp"
#include "little.hpp"

//Konstruktory destruktory
//==============================================================================================//
little::little()
{
    kara = 0;
    h = 0;
    head = nullptr;
    next = head;
}

little::little(int row, int col)
{
    kara = 0;
    h = 0;

    head = new nodeBT(*new macierz(row,col));
    next = head;
}

little::little(vector<vector<double>> Tab){

    kara = 0;
    h = 0;
    head = new nodeBT(Tab);
    next = head;
}
little::~little(){
    delete head;
    delete next;

    head = nullptr;
    next = nullptr;
}
//==============================================================================================//

//Krok 1 - metoda wegierska 1 i 2
void little::stepOne(bool show){
    if(show){
        if(! next->M->haveZerosRows()){
            wypiszKrok1Wegierski(*next);
            *next->limit += metodaWegierskaKrok1(*next);
        }
        if(!next->M->haveZerosColums()){
            wypiszKrok2Wegierski(*next);
            *next->limit += metodaWegierskaKrok2(*next);
        }
    }
    else{
        if(! next->M->haveZerosRows()){
            *next->limit += metodaWegierskaKrok1(*next);
        }
        if(!next->M->haveZerosColums()){
            *next->limit += metodaWegierskaKrok2(*next);
        }
    }
    stepTwo();
}
//Krok2 - obliczanie bilansu zer
void little::stepTwo(){
    double suma=0,karaMax=0;
    int* iMin;
    for(int i = 0; i < next->M->N   ; i++){
        for(int j = 0 ; j < next->M->M ; j++){
            if(next->M->get(i,j) == 0.00){
                iMin = next->M->indexMin(i,j);
                suma = next->M->get(iMin[0],j) + next->M->get(i,iMin[1]);
                if(suma > karaMax){

                    karaMax = suma;

                    next->edge[0] = i;
                    next->edge[1] = j;
                }
            }
        }
    }
    kara = karaMax;

    stepTree();
}
//Krok 3 - przypisanie wartosci do kolejnego elementu grafu
void little::stepTree(){
    int wiersz = next->edge[0],   kolumna = next->edge[1];
    double leftNodeLimit = *next->limit + kara;
    double rightNodeLimit = *next->limit + h;

    next->left = new nodeBT(wiersz,kolumna,leftNodeLimit,*next->M);
    next->left->name->insert(0,1,'*'); //Gwiazdka Beee

    next->right = new nodeBT(wiersz,kolumna,rightNodeLimit,*next->M);

    if(result.empty()){
        result.push_back(next->right->name->front());
        result.push_back(next->right->name->back());
    }
    else{
        if(result.back() == next->right->name->front()){
            result.push_back(next->right->name->back());
        }
        else if(result.front() == next->right->name->back()){
            result.push_front(next->right->name->front());
        }
        else if(result.back() == next->right->name->back()){
            result.pop_back();
            result.push_back(next->right->name->front());
            result.push_back(next->right->name->back());
        }
        else{
            if(savePath.empty()){
                savePath.push_back(next->right->name->front());
                savePath.push_back(next->right->name->back());
            }
            else{
                if(savePath.back() == next->right->name->front()){
                    savePath.push_back(next->right->name->back());
                }
                else if(savePath.front() == next->right->name->back()){
                    savePath.push_front(next->right->name->front());
                }
                else if(savePath.back() == next->right->name->back()){
                    savePath.pop_back();
                    savePath.push_back(next->right->name->front());
                    savePath.push_back(next->right->name->back());
                }
            }
        }
    }

    stepFour();
}
//Krok4 - zredukowanie macierzy
void little::stepFour(){
    int wiersz = next->edge[0],   kolumna = next->edge[1];

    next->right->M->delRowCol(wiersz,kolumna,result,savePath);
    stepFive();
}
//Krok5 - sprawdzanie czy mamy zera a nastepnie obliczenie h
void little::stepFive(){
    h = 0;
    if(!next->right->M->haveZerosRows()){
        wypiszKrok1Wegierski(*next->right);
        h += metodaWegierskaKrok1(*next->right);
    }
    if(!next->right->M->haveZerosColums()){
        wypiszKrok2Wegierski(*next->right);
        h += metodaWegierskaKrok2(*next->right);
    }
    *next->right->limit += h; // dodanie h do ograniczenia
    h = 0;

    stepSix();
}
//Krok6 - przyporzadkowanie wartosci do wierzcholka(zrealizowane w kroku 5)
void little::stepSix(){

    next = next->right; //zredukowana macierz staje sie nowa macierza
    showArray(*next,false);
    if(next->M->N == 2 && next->M->M == 2){
        stepSeven();
    }
    else{
        stepOne(true);
    }
}
//Krok7 - sprawdzanie czy macierz jest 2x2 i czy zblizamy sie do konca
void little::stepSeven(){

    if(next->M->N == 2 && next->M->M == 2 && ( (next->M->get(0,0) == 0 && next->M->get(1,1) == 0) || (next->M->get(0,1) == 0 && next->M->get(1,0) == 0) ) ){
        for(int i=0; i<next->M->N ; i++){
            for(int j=0; j<next->M->M ; j++){
                if(next->M->get(i,j) == 0 ){
                    //Dodanie 2 ostatnicj krawedzi do grafu
                    next->right = new nodeBT(i,j,*next->limit,*next->M);
                    next = next->right;
                }
            }
        }
    }

    stepEight();
}
//Krok8 - to PRAWDZIWE kryterium stopu, w ksiazce jest blad
//sprawdzamy czy limit ostatniej krawedzi jest wiekszy od limitu dziecka po lewej stronie z poczatku grafu, jesli tak to KONIEC
void little::stepEight(){
    nodeBT *last = next;
    result.clear();
    savePath.clear();
    if(*head->left->limit < *last->limit ){
        result.push_back(head->right->name->front());
        result.push_back(head->right->name->back());
        stepNine();
    }
}
//Krok9 - Wstawienie nieskonczonosci w dane miejsce i zapetlenie programu
void little::stepNine(){
    int row = head->left->edge[0];
    int col = head->left->edge[1];
    head->left->M->tablica[row][col] = INF;
    next = head->left;
    showArray(*next,false);
    wypiszKrok1Wegierski(*next);
    metodaWegierskaKrok1(*next);
    wypiszKrok2Wegierski(*next);
    metodaWegierskaKrok2(*next);

    stepTwo();
}

double little::metodaWegierskaKrok1(nodeBT &_node){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i<_node.M->N; i++){
        Min = _node.M->get(i,_node.M->indexMinRow(i));
        SUM = SUM + Min;
        for(int j=0 ; j<_node.M->M ; j++){
            _node.M->tablica[i][j] = _node.M->tablica[i][j] - Min;
        }
    }

    return SUM;
}

double little::metodaWegierskaKrok2(nodeBT &_node){
    double Min = 0 ;
    double SUM = 0;
    for(int i = 0; i < _node.M->N; i++){
        Min = _node.M->get(_node.M->indexMinCol(i),i);
        SUM = SUM + Min;
        for(int j=0 ; j<_node.M->N ; j++){
            _node.M->tablica[j][i] = _node.M->tablica[j][i] - Min;
        }
    }
    return SUM;
}
void little::wypiszKrok1Wegierski(nodeBT &_node){

    cout << "Metoda wegierska krok 1"<< endl;
    cout << setw(6) << _node.M->nameM[0];
    for(int i = 1 ; i<_node.M->M; i++){
        cout << setw(5) << _node.M->nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<_node.M->M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<_node.M->N; j++){
        cout << _node.M->nameN[j] <<"|";
        for(int i = 0 ; i<_node.M->M; i++){
            cout << setw(4);
            if(_node.M->get(j,i) >= (INF - 20000)){
                cout << "Inf" << " ";
            }
            else{
                cout << _node.M->get(j,i) << " ";
            }
        }
        if(_node.M->get(j,_node.M->indexMinRow(j)) <= 0){
            cout << endl;
        }
        else{
            cout <<" |- "<< _node.M->get(j,_node.M->indexMinRow(j)) << endl;
        }
    }
    for(int i = 0 ; i<_node.M->M; i++){
        cout <<"------";
    }
    cout << endl;

}
void little::wypiszKrok2Wegierski(nodeBT &_node){

    string space = "    ";

    cout << "Metoda wegierska krok 2"<< endl;
    cout << setw(6) << _node.M->nameM[0];
    for(int i = 1 ; i<_node.M->M; i++){
        cout << setw(5) << _node.M->nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<_node.M->M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<_node.M->N; j++){
        cout << _node.M->nameN[j] <<"|";
        for(int i = 0 ; i<_node.M->M; i++){
            cout << setw(4);
            if(_node.M->get(j,i) >= (INF - 20000)){
                cout << "Inf" << " ";
            }
            else{
                cout << _node.M->get(j,i) << " ";
            }
        }
        if(_node.M->get(j,_node.M->indexMinRow(j)) <= 0){
            cout << endl;
        }
        else{
            cout <<" | "<< endl;
        }
    }
    for(int i = 0 ; i<_node.M->M; i++){
        cout <<"------";
    }
    cout << endl;

    cout  << " -" ;
    for(int i = 0 ; i<_node.M->M; i++){
        if(_node.M->get(_node.M->indexMinCol(i),i) <= 0){
            cout  << space << " ";
        }
        else{
            cout << setw(4) << _node.M->get(_node.M->indexMinCol(i),i) << " " ;
        }
    }
    cout << endl;
}

string little::city(string key)
{
    vector<string> nazwyMiast;
    fstream arkusz1("city.txt");
    string a,b;

     if (arkusz1.is_open())
    {
        for (int i = 0; i < head->M->M; i++)
        {
            arkusz1 >> a;
            nazwyMiast.push_back(a);
        }
    }

    string result ="";
    size_t index = 0;

    if(key[0] == '*')
    {
        result += '*';
        index += 1;
    }
    if(key[index] == 'X')
    {
        result += "X-";
        index += 1;
        if(key[index] == 'X')
            result += 'X';
        
        else
        {
            size_t x = static_cast<size_t>(key[index]);
            x -= 65;
            result +=  nazwyMiast[x];
        }
    }
    else
    {
        size_t x = static_cast<size_t>(key[index]);
        x -= 65;
        if (key[index+1] == 'X')
            result += "-X";
        else
        {
            size_t y = static_cast<size_t>(key[index + 1]);
            y -= 65;
            result += nazwyMiast[x] + '-' + nazwyMiast[y];
        }
    }
    arkusz1.close();
    result += " =";
    return result;
}


string little::city(char key)
{
    vector<string> nazwyMiast;
    fstream arkusz("city.txt");
    if (arkusz.good())
    {
        string a;
        for (int i = 0; i < 15 ; i++)
        {
            arkusz >> a;
            nazwyMiast.push_back(a);
            if(arkusz.eof())
                break;
        }
    }
    else
    {
        cout << "Blad pliku city.txt" << endl;
    }
    string b = nazwyMiast[key - 'A'];
    arkusz.close();
    return b;
}


void little::showArray(bool showCities)
{

    cout << endl;
    for (int i = 0; i < next->M->M; i++)
    {
        if(showCities){
            cout << setw(6) << city(next->M->nameM[i]) << "|";
        }
        else{
            cout << setw(6) << next->M->nameM[i] << "|";
        }

    }
    cout << endl;
    for (int i = 0; i < next->M->M; i++)
    {
        cout << "--------";
    }
    cout << endl;
    for (int j = 0; j < next->M->N; j++)
    {

        for (int i = 0; i < next->M->M; i++)
        {
            cout << setw(6);
            if (next->M->get(j, i) >= (INF - 20000))
            {
                cout << "Inf"
                     << " ";
            }
            else
            {
                cout << next->M->get(j, i) << " ";
            }
        }
        if(showCities){
            cout << "|" << left << setw(6) << city(next->M->nameN[j]) << right;
        }
        else{
            cout << "|" << setw(6) << next->M->nameN[j];
        }
        cout << endl;
    }
    for (int i = 0; i < next->M->M; i++)
    {
        cout << "--------";
    }
    cout << endl;
}

void little::showArray(const nodeBT &_node,bool showCities)
{
    cout << " +++ Macierz [" << *_node.name << "] +++" << endl;
    for (int i = 0; i < _node.M->M; i++)
    {
        if(showCities){
            cout << setw(6) << city(_node.M->nameM[i]) << "|";
        }
        else{
            cout << setw(6) << _node.M->nameM[i] << "|";
        }

    }
    cout << endl;
    for (int i = 0; i < _node.M->M; i++)
    {
        cout << "--------";
    }
    cout << endl;
    for (int j = 0; j < _node.M->N; j++)
    {

        for (int i = 0; i < _node.M->M; i++)
        {
            cout << setw(6);
            if (_node.M->get(j, i) >= (INF - 20000))
            {
                cout << "Inf"
                     << " ";
            }
            else
            {
                cout << _node.M->get(j, i) << " ";
            }
        }
        if(showCities){
            cout << "|" << left << setw(6) << city(_node.M->nameN[j]) << right;
        }
        else{
            cout << "|" << setw(6) << _node.M->nameN[j];
        }
        cout << endl;
    }
    for (int i = 0; i < _node.M->M; i++)
    {
        cout << "--------";
    }
    cout << endl;
}

void little::showData()
{
    cout << "Wiersze: " << next->M->N << endl;
    cout << "Kolumny: " << next->M->M << endl;
    cout << "Oszacowanie dolne: " << next->edge[0] << endl;
    cout << "Ograniczenie dolne: " << next->edge[1] << endl;
    cout << "Kara: " << kara << endl;
    cout << "Krawedz: " << next->edge[0] + 1 << next->edge[1] + 1 << endl;
}

void little::showGraph(const string &prefix, const nodeBT *node, bool isLeft,bool showCities)
{
    if (node != nullptr)
    {
        if (prefix != "")
        {
            cout << prefix << "|" << endl
                 << prefix;
            cout << (isLeft ? "|----" : "^----");
        }
        else
        {
            cout << "    ";
        }

        // print the value of the node
        if (*node->limit > INF - 20000)
        {
            if(showCities){
                cout << "[" << setw(3) << city(*node->name) << " ";
            }
            else{
                cout << "[" << setw(3) << *node->name << " ";
            }
            cout << "Inf";
            cout << "]\n";
        }
        else
        {
            if(showCities){
                cout << "[" << setw(3) << city(*node->name) << " " << *node->limit << "]\n";
            }
            else{
                cout << "[" << setw(3) << *node->name << " " << *node->limit << "]\n";
            }
        }

        // enter the next tree level - left and right branch
        showGraph(prefix + (isLeft ? "|       " : "        "), node->left, true,showCities);
        showGraph(prefix + (isLeft ? "|       " : "        "), node->right, false,showCities);
    }
}
void little::showGraph(bool showCieties)
{
    cout << "   Graf:" << endl;
    showGraph("", head, false,showCieties);
    cout << endl;
}
void little::set(vector<vector<double>> &_set)
{
    kara = 0;
    h = 0;
    head = new nodeBT(_set);
    next = head;
}
void little::set(macierz &_set)
{
    kara = 0;
    h = 0;
    head = new nodeBT(_set);
    next = head;
}

void little::result2(bool showCities)
{

    nodeBT *tmp = head, *next;
    list<char> path,savePath;
    bool flag = true;

    path.push_back(tmp->right->name->front());
    path.push_back(tmp->right->name->back());
    next = tmp->right;
    while(next->right != nullptr){
        if(path.back() == next->right->name->front()){
            path.push_back(next->right->name->back());
        }
        else if(path.front() == next->right->name->back()){
            path.push_front(next->right->name->front());
        }
        else if(path.back() == next->right->name->back()){
            path.pop_back();
            path.push_back(next->right->name->front());
            path.push_back(next->right->name->back());
        }
        else{
            savePath.push_back(next->right->name->front());
            savePath.push_back(next->right->name->back());
        }

        next = next->right;

        if(next->right == nullptr)
        {
            cout << "   Optymalna droga :" << endl;

            for (size_t i = path.size(); i > 0 ; i--)  // wypisuje z listy od począku i usuwa 
            {
                if (showCities)
                    cout << city(path.front()) ;
                else
                    cout << path.front() ;
                if(i > 1)
                   cout << " -> ";
                path.pop_front();
            }
            cout << endl 
                 << "   Strumien minimalny  ->  " << *next->limit << endl;

            path.push_back(tmp->right->name->front());
            path.push_back(tmp->right->name->back());
            next = tmp->left;

            if(!flag)
                break;

            flag = false;
        }
    }
}
