#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

int main()
{
    static vector<vector<double>> Tab1 = {{999,1,1,2,3},{3,999,2,5,6},{5,4,999,3,7},{8,4,3,999,2},{7,7,5,6,999}};
    static vector<vector<double>> Tab2 = {{999,8,7,5},{2,999,6,4},{3,10,999,4},{7,5,4,999}};
    static vector<vector<double>> Tab3 = {{999,10,15,20},{10,999,35,25},{15,35,999,30},{20,25,30,999}};

    little problem1(Tab2);
    little problem2(Tab3);

    problem1.showArray();
    problem1.stepOne(false);
    problem1.showGraph();

    return 0;
}
