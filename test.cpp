#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct node
{
    node* next;
    int val;
    node(int x):val(x), next(nullptr) {}
};

class inst
{
public:
    node* head;

    inst():head(nullptr){}

    void create()
    {
        head = new node(1);
        node* ptr = head;
        for(int i = 0; i < 9; ++i)
        {
            ptr->next = new node(i+4);
            ptr = ptr->next;
        }
    }

};


int main()
{
    vector<pair<int, int>> ret;
    pair<int, int> p1(35, 68);
    ret.push_back(p1);

    pair<int, int> re = ret.front();
    cout << ret[0].first << " " << ret[0].second << endl;

    int temp = 7 & 7;
    cout << temp << endl;

    inst test;
    test.create();
    node* res = test.head;
    while(res != nullptr)
    {
        cout << res->val << " ";
        res =res->next;
    }
    cout << endl;

    return 0;
}