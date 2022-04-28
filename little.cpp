#include "nodeBT.hpp"
#include "little.hpp"

little::little()
{
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    kara = 0;
    h = 0;
    head = new nodeBT(Tab2);
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

void little::stepOne(bool show){
    if(show){
        wypiszKrok1Wegierski();
        if(! next->M->haveZerosRows()){
            *next->limit += metodaWegierskaKrok1(*next);
        }
        wypiszKrok2Wegierski();
        if(!next->M->haveZerosColums()){
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
void little::stepTree(){
    int wiersz = next->edge[0],   kolumna = next->edge[1];
    double leftNodeLimit = *next->limit + kara;
    double rightNodeLimit = *next->limit + h;

    next->left = new nodeBT(wiersz,kolumna,leftNodeLimit,*next->M);
    next->left->name->insert(0,1,'*');

    next->right = new nodeBT(wiersz,kolumna,rightNodeLimit,*next->M);

    stepFour();
}
void little::stepFour(){
    int wiersz = next->edge[0],   kolumna = next->edge[1];

    next->right->M->delRowCol(wiersz,kolumna);
    stepFive();
}
void little::stepFive(){
    h = 0;
    if(!next->right->M->haveZerosRows()){
        h += metodaWegierskaKrok1(*next->right);
    }
    if(next->right->M->haveZerosColums()){
        h += metodaWegierskaKrok2(*next->right);
    }

    //ograniczenia[0] += h;
    *next->right->limit += h;
    h = 0;

    stepSix();
}
void little::stepSix(){

    cout << "==================================" << endl;
    showArray(*next);
    showArray(*next->left);
    showArray(*next->right);
    cout << "==================================" << endl;
    next = next->right;

    if(next->M->N == 2 && next->M->M == 2){
        stepSeven();
    }
    else{
        stepOne(false);
    }
}
void little::stepSeven(){

    if(next->M->N == 2 && next->M->M == 2 && ( (next->M->get(0,0) == 0 && next->M->get(1,1) == 0) || (next->M->get(0,1) == 0 && next->M->get(1,0) == 0)) ){
        for(int i=0; i<next->M->N ; i++){
            for(int j=0; j<next->M->M ; j++){
                if(next->M->get(i,j) == 0 ){

                    next->right = new nodeBT(i,j,*next->limit,*next->M);
                    next = next->right;
                }
            }
        }
    }

       stepEight();
}
void little::stepEight(){
    nodeBT *last = next;
    if(*head->left->limit < *last->limit ){
        stepNine();
    }
    else if( *head->right->limit < *last->limit ){
        //stepTwo();
    }
}
void little::stepNine(){
    int row = head->left->edge[0];
    int col = head->left->edge[1];
    head->left->M->tablica[row][col] = 999;
    next = head->left;

    metodaWegierskaKrok1(*next);
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
void little::wypiszKrok1Wegierski(){
    for(int j = 0; j<next->M->N; j++){
        cout <<"|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(4);
            cout << next->M->get(j,i) << " ";
        }
        if(next->M->get(j,next->M->indexMinRow(j)) <= 0){
            cout << endl;
        }
        else{
            cout <<" |- "<< next->M->get(j,next->M->indexMinRow(j)) << endl;
        }
    }
    cout << endl;
}
void little::wypiszKrok2Wegierski(){
    int space=4;
    for(int j = 0; j<next->M->N; j++){
        cout << "|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(space);
            cout << next->M->get(j,i) << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<next->M->M; i++){
        cout << setw(space) << "------";
    }
    cout << endl;
    for(int i = 0 ; i<next->M->M; i++){
        if(next->M->get(next->M->indexMinCol(i),i) <= 0){
            space+= 5;
        }
        else{
            cout << setw(space) <<"-"<< next->M->get(next->M->indexMinCol(i),i);
        }
    }
    cout << endl;
}

void little::showArray(){
    cout << endl;
    cout << setw(6) << next->M->nameM[0];
    for(int i = 1 ; i<next->M->M; i++){
        cout << setw(5) << next->M->nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i<next->M->M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j<next->M->N; j++){
        cout << next->M->nameN[j] <<"|";
        for(int i = 0 ; i<next->M->M; i++){
            cout << setw(4);
            cout << next->M->get(j,i) << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i<next->M->M; i++){
        cout <<"------";
    }
    cout << endl;
}

void little::showArray(const nodeBT &_node){
    cout << endl;
    cout << setw(6) << _node.M->nameM[0];
    for(int i = 1 ; i< _node.M->M; i++){
        cout << setw(5) << _node.M->nameM[i];
    }
    cout << endl;
    for(int i = 0 ; i< _node.M->M; i++){
        cout <<"------";
    }
    cout << endl;
    for(int j = 0; j< _node.M->N; j++){
        cout << _node.M->nameN[j] <<"|";
        for(int i = 0 ; i< _node.M->M; i++){
            cout << setw(4);
            cout << _node.M->get(j,i) << " ";
        }
        cout <<" |"<< endl;
    }
    for(int i = 0 ; i< _node.M->M; i++){
        cout <<"------";
    }
    cout << endl;
}

void little::showData(){
    cout << "Wiersze: "<< next->M->N << endl;
    cout << "Kolumny: "<< next->M->M << endl;
    cout << "Oszacowanie dolne: " << next->edge[0] << endl;
    cout << "Ograniczenie dolne: " << next->edge[1] << endl;
    cout << "Kara: " << kara << endl;
    cout << "Krawedz: " <<  next->edge[0]+1 <<  next->edge[1]+1 << endl;
}

void little::showGraph(const string& prefix, const nodeBT* node, bool isLeft){
    if( node != nullptr )
        {
            if(prefix != ""){
                cout << prefix << "|" << endl <<prefix;
                cout << (isLeft ? "|---" : "^---" );
            }else{
                cout << "    ";
            }

            // print the value of the node
            cout  << "[" << setw(3) << *node->name  << " " << *node->limit << "]\n";

            // enter the next tree level - left and right branch
            showGraph( prefix + (isLeft ? "|     " : "        "), node->left, true);
            showGraph( prefix + (isLeft ? "|     " : "        "), node->right, false);
        }
}
void little::showGraph(){
    showGraph("", head, false);
}
