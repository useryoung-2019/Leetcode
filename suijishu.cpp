#include"data.hpp"
#include<time.h>
#include<cstring>

int main()
{
    srand((unsigned)time(NULL));
    vector<int> arr;
    arr.reserve(20);

    for(int i = 0; i < 20; ++i)
    {
        int temp = rand() % 15;
        arr.push_back(temp);
    }

    for(auto s:arr)
    {
        cout << s << " ";
    }
    cout << endl;

    sort(arr.begin(), arr.end());

    auto begin = reverse_iterator<vector<int>::iterator>(arr.end());
    auto end = reverse_iterator<vector<int>::iterator>(arr.begin());
    reverse(begin, end);
    
    for(auto s:arr)
    {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}