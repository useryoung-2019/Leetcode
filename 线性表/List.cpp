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
/*思路：
先遍历一遍找出size，然后再遍历一次找到需要旋转的size-k位置，记录下节点位置以及后一个位置，后一个位置为最终链表的起始节点，size-k节点为最终节点  时间复杂度O(N)，空间复杂度O(1)

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

class RemoveNthNodeFromEndofList
{
/*给一个链表，除去倒数第k个元素，并且返回链表的头节点，给出的k值保证是有效的并且要求一次完成*/
public:
    Listnode* l1;
    RemoveNthNodeFromEndofList():l1(nullptr){}
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
/*
解法思路：关于链表的解法无非就几种：
        1. 遍历找节点，最简单的暴力解法，对于链表尤其好用
        2. 经典双指针解法，这种一般就应用在这类题目中，除去倒数第K个节点
        3. 经典快慢指针，判断循环链表，找循环节点等等都可以用快慢指针

        这个题目的要求就是尽量在一次遍历中完成，本来两次暴力遍历也能完成，题目要求的话，那就要考虑使用双指针的方法，找倒数第K个指针，那就让一个指针先走到顺数第K个节点，然后一个节点指向头结点，让两个节点同时走，先到链表末尾时，指向头结点的指针就指向倒数第K个节点，现在要删除这个节点，那就只需要直到倒数第K个节点的前一个即可。所以先让第一个指针走到顺数第K+1个节点就可以了，或者计数从第0个开始也行。具体实现都差不多,时间复杂度O(N) 空间复杂度O(1)
*/
    Listnode* solution(Listnode* head, int k)
    {
        if (head == nullptr)
            return head;
        
        Listnode* quickptr = head;
        Listnode* slowptr = head;
        int count = 1;
        while(count < k + 1)
        {
            quickptr = quickptr->next;
            ++count;
        }

        while(quickptr->next != nullptr)
        {
            quickptr = quickptr->next;
            slowptr = slowptr->next;
        }

        Listnode* temp = slowptr->next;
        slowptr->next = temp->next;
        temp->next = nullptr;

        return head;
    }

    void test()
    {
        create();
        Listnode* res = solution(l1, 5);
        cout << __LINE__ << ":  ";
        while(res != nullptr)
        {
            cout << res->val << " ";
            res = res->next;
        }
        cout << endl;
    }
};

class SwapNodesinPairs
{
/*交换链表中相邻的两个节点，不能只交换其值： 1->2->3->4->5    2->1->4->3->5*/
public:
    Listnode* l1;
    SwapNodesinPairs():l1(nullptr){}
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

/*思路：还是要用三个指针代表左右中间三个节点，其中右边与中间表示成对的两个，左边只是起到对换后上一个数对的尾节点，方便与新数对连接
        时间复杂度O(N) 空间复杂度O(1)*/
    Listnode* solution(Listnode* head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        Listnode result(0);
        result.next = head;

        Listnode* prev = &result;
        Listnode* cur = prev->next;
        Listnode* next = cur->next;

        while (next != nullptr)
        {
            prev->next = next;
            cur->next = next->next;
            next->next = cur;

            prev = cur;
            cur = cur->next;
            next = cur == nullptr ? cur : cur->next; // 有两种情况，第一种刚好偶数对，那么cur就为nullptr此时next无法赋值，会出现段错误，第二种奇数对，cur不为nullptr，此时next就可以赋值为cut->next
        }
        
        return result.next;
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

class ReverseNodesinkGroup
{
/*反转局部连续的K个节点，如果最后剩下的节点不够K个，那就不要对其排序，不允许交换节点的值，只允许对节点进行操作
    1->2->3->4->5   k=2  2->1->4->3->5
    1->2->3->4->5   k=3  3->2->1->4->5
*/
public:
    Listnode* l1;
    ReverseNodesinkGroup():l1(nullptr){}
    void create()
    {
        l1 = new Listnode(1);
        vector<int> arr = {2,3,4,5,6,7,8};
        Listnode* ptr = l1;
        for (auto s:arr)
        {
            ptr->next = new Listnode(s);
            ptr = ptr->next;
        }
    }

    Listnode* solution(Listnode* l, int k)
    {
        if (l == nullptr || l->next == nullptr || k < 1)
            return l;
        
        Listnode head(0);
        head.next = l;

        Listnode* end = l;
        Listnode* prev = &head;
        while(end != nullptr)
        {
            for (int i = 1; i < k && end != nullptr; ++i) // k个或者到尾都要退出
            {
                end = end->next;
            }

            if (end == nullptr)
                break;//不足K个，不进行局部倒序

            prev = reverseLocalList(prev, prev->next, end);
            
            end = prev->next;
        }

        return head.next;
    }
//函数返回的是局部排序后的倒数第一个节点位置
    Listnode* reverseLocalList(Listnode* mark, Listnode* begin, Listnode* end)
    {
        Listnode* end_next = end->next;

        for(Listnode* ptr = begin, *cur = begin->next, *next = cur->next; cur != end_next;
            ptr = cur, cur = next, next = cur == nullptr ? cur : cur->next)
            {
                cur->next = ptr;
            }

        begin->next = end_next;
        mark->next = end;//这里主要是为了将头结点连接到第一次未排序的尾节点上

        return begin;
    }

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
};

class LinkedListCycle
{
/*判断是否循环，快慢指针就可以解决，当快慢指针相遇则说明一定循环*/
};

class LinkedListCycleII
{
/*找出循环点，快慢指针相遇时，另起一个从头结点出发的慢指针，让两个慢指针相遇即为循环点*/
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
    RemoveNthNodeFromEndofList().test();
    SwapNodesinPairs().test();
    ReverseNodesinkGroup().test();
    return 0;
}

