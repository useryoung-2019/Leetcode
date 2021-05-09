#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<pair<int, int>> ret;
    pair<int, int> p1(35, 68);
    ret.push_back(p1);

    pair<int, int> re = ret.front();
    cout << ret[0].first << " " << ret[0].second << endl;
    return 0;
}