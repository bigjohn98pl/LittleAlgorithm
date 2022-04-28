#include "global.hpp"
#include "little.hpp"
#include "nodeBT.hpp"

int main()
{
    static vector<vector<double>> Tab1 = {{INF,1,1,2,3},{3,INF,2,5,6},{5,4,INF,3,7},{8,4,3,INF,2},{7,7,5,6,INF}};
    static vector<vector<double>> Tab2 = {{INF,8,7,5},{2,INF,6,4},{3,10,INF,4},{7,5,4,INF}};
    static vector<vector<double>> Tab3 = {{INF,10,15,20},{10,INF,35,25},{15,35,INF,30},{20,25,30,INF}};

    little problem1(Tab2);
    little problem2(Tab3);

    problem1.showArray();
    problem1.stepOne(false);
    problem1.showGraph();

    return 0;
}
