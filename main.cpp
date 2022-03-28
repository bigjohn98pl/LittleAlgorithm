#include "global.hpp"
#include "little.hpp"
#include "krawedz.hpp"

//static double Tab2[ROW][COL] = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
int main()
{
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    little problem1(Tab2);

    problem1.showArray();
    problem1.wypiszKrok1Wegierski();
    problem1.metodaWegierskaKrok1();
    problem1.wypiszKrok2Wegierski();
    problem1.metodaWegierskaKrok2();
    problem1.showArray();
    problem1.krokDrugi();
    problem1.showArray();
    problem1.krokTrzeci();
    problem1.showArray();
    problem1.krokCzwarty();
    problem1.showArray();
    problem1.krokPiaty();
    problem1.showArray();
    problem1.showData();
    return 0;
}
