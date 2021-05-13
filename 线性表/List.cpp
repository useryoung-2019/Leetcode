#include"../data.hpp"

class Listnode
{
public:
    int val;
    Listnode* next;

    Listnode(int x = 0): val(x), next(nullptr){}
};

class AddTwoNumber
{
public: 
/*题目： 两个非负整数以相反的顺序存储在两个链表上，对这个数相加，得到的数以链表的形式表示
        比如387和2984在链表上表示为 7->8->3 + 4->8->9->2 == 1->7>3->3*/
    Listnode* l1;
    Listnode* l2;

    AddTwoNumber():l1(nullptr), l2(nullptr) {}

    void create()
    {   
        l1 = new Listnode(7);
        l1->next = new Listnode(8);
        l1->next->next = new Listnode(3);

        l2 = new Listnode(4);
        l2->next = new Listnode(8);
        l2->next->next = new Listnode(9);
        l2->next->next->next = new Listnode(2);
    }

/*与将整数放进数组逐位相加一个道理,PlusOne的链表形式*/

    Listnode* solution(Listnode* l1, Listnode* l2)
    {
        Listnode* result;
        Listnode* tail = result;
        int sum = 0;

        while (l1 != nullptr || l2 != nullptr)
        {
            if (l1 == nullptr)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            else if (l2 == nullptr)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            else
            {
                sum += (l1->val + l2->val);
                l1 = l1->next;
                l2 = l2->next;
            }

            Listnode* temp = new Listnode(sum % 10);
            sum /= 10;
            tail->next = temp;
            tail = temp;
        }

        if (sum > 0)
        {
            tail->next = new Listnode(sum);
        }

        return result->next;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1, l2);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << "->";
            res = res->next;
        }
        cout << endl;
    }
};

class ReverseLinkedList
{//题目：翻转一个链表
public:
    Listnode* l1;
    ReverseLinkedList():l1(nullptr) {}

private:
    void create()
    {
        l1 = new Listnode(1);
        Listnode* tail = l1;
        for (int i = 0; i < 1; ++i)
        {
            Listnode* temp = new Listnode(i+2);
            tail->next = temp;
            tail = temp;
        }
    }
public:
/*解法： 翻转操作是非常简单但总是忘,要重复训练. 
        需要两个指针，一个prev，一个next，每次搭桥完成后prev指向next，next再指向next->next
        直到next为空就说明prev为最后的末尾指针,即为翻转后的头结点,返回prev即可
        时间复杂度O(N), 空间复杂度O(1)*/
    Listnode* solution(Listnode* head)
    {
        if (head == nullptr)
            return nullptr;
        
        Listnode* prev = head;
        Listnode* next = head->next;
        head->next = nullptr;//更改头结点的next为null

        while (next != nullptr)
        {
            head = next->next;
            next->next = prev;
            prev = next;
            next = head;
        }
        head = prev;

        return head;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1);
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
    }
};

class ReverseLinkedListII
{/*题目: 给定一个链表,指定某个位置到某个位置翻转,而其他位置不变
        1->2->3->4->5->6->7, m = 2  n = 4, 翻转后的结果为 1->4->3->2->5->6->7
        其中 1 <= m <= n <= length
        时间复杂度O(N),空间复杂度O(1)*/
public:
    Listnode* l1;
    ReverseLinkedListII():l1(nullptr) {}
private:
    void create()
    {
        l1 = new Listnode(1);
        Listnode* tail = l1;
        for (int i = 0; i < 5; ++i)
        {
            Listnode* temp = new Listnode(i+2);
            tail->next = temp;
            tail = temp;
        }
    }
public:
/*得到翻转的链表,然后考虑头尾的连接,与整体翻转差不多的操作,只是要更改头部与尾部的连接部位
*/
    Listnode* solution(Listnode* head, int m, int n)
    {
        if (head == nullptr || m == n)
            return head;
        
        Listnode* temp = head;
        Listnode* start_prev, *start, *end;
        if (m == 1)
            start_prev = nullptr;
        
        int count = 1;
        while(temp != nullptr)
        {
            if (count == m - 1)
                start_prev = temp;
            if (count == m)
                start = temp;            
            if (count == n)
            {
                end = temp;
                break;
            }
            temp = temp->next;
            ++count;
        }

        temp = start;
        Listnode* prev = temp;
        Listnode* next = temp->next;
        start->next = end->next;

        while(prev != end)
        {
            temp = next->next;
            next->next = prev;
            prev = next;
            next = temp;
        }

        if (start_prev != nullptr)
        {
            start_prev->next = prev;
            return head; 
        }
        
        return end;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1, 1, 6);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }
};

class PartitionList
{
/*一个链表以及给定一个元素val， 将小于val放在左边，大于等于val放在右边
    1->4->3->2->5->2  val=3  1->2->2->4->3->5*/
public:
/*解决思路:需要两个头指针,一个指针指向小于,一个指向大于的,最终小于的链表末尾指向大于的头部,连接起来
        所以分别需要头指针与尾指针,写下去可能很复杂,但是看上去很简洁易懂,最后需要注意的是最大的
        尾指针的指向要更改为nullptr
        时间复杂度O(N),空间复杂度O(1)*/
    Listnode* solution(Listnode* l1, int x)
    {
        Listnode big(0);
        Listnode small(0);
        Listnode* big_index = &big;
        Listnode* small_index = &small;

        Listnode* temp = l1;
        while (temp != nullptr)
        {
            if (temp->val < x)
            {
                small_index->next = temp;
                small_index = temp;
            }
            else
            {
                big_index->next = temp;
                big_index = temp;
            }

            temp = temp->next;
        }
        small_index->next = big.next;
        big_index->next = nullptr;//这个很重要,不然可能会指向其他地方导致出现循环链表
        return small.next;
    }

    PartitionList():l1(nullptr){}

    void test()
    {
        create();
        Listnode* res = solution(l1, 3);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }

private:
    Listnode* l1;

    void create()
    {
        l1 = new Listnode(1);
        vector<int> arr = {4,3,2,5,2};
        Listnode* ptr = l1;
        for (auto s:arr)
        {
            ptr->next = new Listnode(s);
            ptr = ptr->next;
        }
    }
};

class RemoveDuplicatesfromSortedList
{
/*数组版的除去重复数字,链表的数字已经排好序,返回一个链表每个数字只出现一次*/
public:
    Listnode* l1;
    RemoveDuplicatesfromSortedList():l1(nullptr){}
    void create()
    {
        l1 = new Listnode(1);
        vector<int> arr = {1,2,2,2,3,3,5,7};
        Listnode* ptr = l1;
        for (auto s:arr)
        {
            ptr->next = new Listnode(s);
            ptr = ptr->next;
        }
    }
/*
思路:与数组版的差不多,数组版的是arr[1]与arr[0]比较,相同就不改变哨兵[1]的位置,不同就将哨兵
    移到下一位[2],并更新[1]的值,然后再来一轮比较.
    链表版也一样类似,只是没有快速访问那么简单,需要指针的迭代,第一个肯定不会重复所以先记录好第一个,
    比较第二个与第一个,要是不同就重新接上,要是相同就往下找,直至找到不同的,接上不同的节点,最后的最后,
    最后一个节点需要将其next指向nullptr
    时间复杂度O(N) ,空间复杂度O(1)
*/
    Listnode* solution(Listnode* l1)
    {
        if(l1 == nullptr || l1->next == nullptr)
            return l1;

        Listnode head(0);
        Listnode* tail = &head;
        tail->next = l1;
        tail = tail->next;
        Listnode* temp = l1->next;

        while(temp != nullptr)
        {
            if (tail->val != temp->val)
            {
                tail->next = temp;
                tail = temp;
            }
            temp = temp->next;
        }
        tail->next = nullptr;

        return head.next;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }
};

class RemoveDuplicatesfromSortedListII
{
//排序链表中删除所有重复的节点,返回一个原本只有一个值的链表
public:
    Listnode* l1;
    RemoveDuplicatesfromSortedListII():l1(nullptr){}
    void create()
    {
        l1 = new Listnode(1);
        vector<int> arr = {1,2,2,2,3,3,5,7,9,9};
        Listnode* ptr = l1;
        for (auto s:arr)
        {
            ptr->next = new Listnode(s);
            ptr = ptr->next;
        }
    }
/*
解法思路:相当于前后三个节点的比较,然后需要注意的是第一个节点的重要性,需要拿出来单独讨论
        时间复杂度O(N),空间复杂度O(1)
*/
    Listnode* solution(Listnode* head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        Listnode start(0);
        Listnode* tail = &start;

        Listnode* prev = head;
        Listnode* cur = head->next;

        if (prev->val != cur->val)//首先确定第一个是不是单身数
        {
            tail->next = prev;
            tail = prev;
        }

        while(cur != nullptr)
        {
            if (cur->val != prev->val)//当与前面不同时为触发条件
            {
                if (cur->next != nullptr)//第一检查next指针的合法性
                {
                    if (cur->val == cur->next->val)//当前值与后面值相同,那就直接跳过,更新prev
                    {
                        prev = cur;
                        cur = cur->next;
                    }
                    else//否则就说明找到了一个单身节点,那就接上去
                    {
                        tail->next = cur;
                        tail = cur;
                        prev = cur;
                    }
                }
                else//遇到nullptr就说明到了头,此时还不相等就说明最后一个也是单身节点,接上
                {
                    tail->next = cur;
                    tail = cur;
                    break;
                }
            }
            cur = cur->next;//406行与这个并不冲突,已知122,所以第二个2没必要比较,那么再next一下也合理
        }

        tail->next = nullptr;//最后节点的next指向nullptr防止出现重复的值
        return start.next;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }
};

class RotateList
{
/*给一个链表,指定一个k,将后k个节点旋转到链表首端, k为非负数
    1->2->3->4->5->nullptr  k = 2   res:4->5->1->2->3->nullptr*/
public:
    Listnode* l1;
    RotateList():l1(nullptr){}
    void create()
    {
        l1 = new Listnode(1);
        vector<int> arr = {2,3,4,5,6,7,8,9};
        Listnode* ptr = l1;
        for (auto s:arr)
        {
            ptr->next = new Listnode(s);
            ptr = ptr->next;
        }
    }
/*思路：先遍历一遍找出size，然后再遍历一次找到需要旋转的size-k位置，记录下节点位置以及后一个位置
        后一个位置为最终链表的起始节点，size-k节点为最终节点
        时间复杂度O(N)，空间复杂度O(1)

还有一种思路： 也是先遍历求size，然后将首尾相连，形成一个环，接着找到size-k位置，直接断掉也可以*/
    Listnode* solution(Listnode* head, int k)
    {
        if (head == nullptr || k == 0)
            return head;
        
        int size = 0;
        for (Listnode* index = head; index != nullptr; index = index->next)
        {
            ++size;
        }

        if (k == size)
            return head;

        int count  = 0;
        Listnode* start = nullptr;
        Listnode* end = nullptr;
        for (Listnode* index = head; index != nullptr; index = index->next)
        {
            ++count;
            if (count == (size - k))
            {
                end = index;
                start = index->next;
                end->next = nullptr;
                break;
            }
        }

        Listnode* ptr = start;
        while(ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = head;

        return start;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1, 8);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }
};



int main(int argc, char** argv)
{
    AddTwoNumber().test();
    //ReverseLinkedList().test();
    ReverseLinkedListII().test();
    PartitionList().test();
    RemoveDuplicatesfromSortedList().test();
    RemoveDuplicatesfromSortedListII().test();
    RotateList().test();
    return 0;
}

