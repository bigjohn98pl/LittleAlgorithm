#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

int main()
{
    static vector<vector<double>> Tab1 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    static vector<vector<double>> Tab2 = {{999,8,7,5},{2,999,6,4},{3,10,999,4},{7,5,4,999}};

    little problem1(Tab1);
    little problem2(Tab2);

    problem1.showArray();
    problem1.stepOne(true);
    problem1.showGraph();

    problem1.~little();

    problem2.showArray();
    problem2.stepOne(true);
    problem2.showGraph();

    {
    little problem3(Tab1);
    problem3.showArray();
    problem3.stepOne(true);
    problem3.showGraph();
    }
    return 0;
}
