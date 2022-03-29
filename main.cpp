#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

//static double Tab2[ROW][COL] = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
int main()
{
    static vector<vector<double>> Tab2 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    little problem1(Tab2);

    problem1.showArray();
    problem1.stepOne(true);
//    problem1.stepTwo();
//    problem1.stepTree();
//    problem1.stepFour();
//    problem1.showArray();
//    problem1.stepFive();

//    problem1.stepSix();
    problem1.showArray();
    problem1.showData();
    problem1.showGraph();
    return 0;
}
