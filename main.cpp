#include <iostream>
#include <iomanip>

#define N 2
#define M 2

using namespace std;

class little{
public:
    double metodaWegierskaKrok1(double T[N][M]);
    int indexMinimumWiersza(double T[M]);

private:

};

int little::indexMinimumWiersza(double T[M]){
    int minIndex = 0;
    for(int i = 1 ; i<M; i++){
        if(T[i] < T[i-1]){
            minIndex = i;
        }
    }
    return minIndex;
}


double little::metodaWegierskaKrok1(double T[N][M]){
    double Min;
    for(int j = 0; j<N; j++){
        Min = T[j][indexMinimumWiersza(T[j])];
        for(int i=0 ; i<M ; i++){
            T[j][i] = T[j][i] - abs(Min);
        }
    }

    return Min;
}

int main()
{
    double tab[N][M] = {{1.4,2.2},{21.6,3.5}};

    little problem1;

    return 0;
}
