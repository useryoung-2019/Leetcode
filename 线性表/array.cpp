#include"../data.hpp"

class removeDuplicatesfromSortedArray
{
public:
/*数组的解法之一：哨兵
题目的要求是除去重复的元素，返回不重复元素的个数，前提是arr是有序的，无序哨兵无法使用
哨兵机制可以解决，哨兵的目的在于不动，一旦发现有数据不相同时，哨兵就会下移一个，
并且改变下个位置的值，因此可以得到如下解法。[这是时间复杂度O(n),空间复杂度O(1)]
*/
    int soluation1(vector<int> arr)
    {
        if (arr.empty())
            return 0;
        
        int index = 0;
        for(int i = 1; i < (int)arr.size(); ++i)
        {
            if (arr[index] != arr[i])
            {
                arr[++index] = arr[i];
            }
        }

        return index + 1;
    }
/*
要是arr是无序的话该如何？重复度为1的话那就建议使用set容器[key==value,并且不允许重复的元素]，此时时间复杂度O(n)，
空间复杂度O(n)*/
    int soluation2(vector<int> arr)
    {
        set<int> ar;
        for(auto s:arr)
        {
            ar.insert(s);
        }

        return ar.size();
    }

};

class  removeDuplicatesfromSortedArrayII
{
public:
/*
这是上一个哨兵的延伸，上一个是重复度为1，这个题目改为重复度为2或者n，
实质上原理不会变，我们只需要改变哨兵的位置即可，但是比较的位置还是要从头开始,
实现的细节也要改变，因为需要一定的重复度，所以哨兵位置地方的值不同时需要更改
所以就能得到如下解法：[这是时间复杂度O(n),空间复杂度O(1)]
*/
    int soluation(vector<int> arr)
    {
        if(arr.size() <= 2)
            return arr.size();
        
        int index = 2;
        for(int i = 2; i < (int)arr.size(); ++i)
        {
            if (arr[i] != arr[index - 2])
            {
                arr[index++] = arr[i];
            }
        }

        return index;
    }
};

class SearchinRotatedSortedArray
{
public:
/*
有序的数组查找方法能想到的是：二分法，能够极度减少时间复杂度，理想情况下为O(logN),空间复杂度为O(1)
但是题干给出的要求是一个有序数组，被拆分成两段，然后组合在一起，就是说两段有序，但整体无序，因此二分
的首要需求是找出二分的数列。
但同时也会出现一种 123111111这种数列情况，因此此时的二分需要细致,这种情况只能将begin++重新二分
所以就有如下的解法
*/
    int souluation(vector<int>& arr, int target)
    {
        if (arr.empty())
            return -1;
        int begin = 0;
        int end = arr.size() - 1;

        while(begin != end)
        {
            int mid = begin + (end - begin)/2;
            if (arr[mid] == target)
                return mid;
            if (arr[begin] < arr[mid])
            {
                if (target >= arr[begin] && target < arr[mid])
                {
                    end = mid;
                }
                else
                {
                    begin = mid + 1;
                }
            }
            else if (arr[begin] > arr[mid])
            {
                if (target > arr[mid] && target <= arr[end])
                {
                    begin = mid + 1;
                }
                else
                {
                    end = mid;
                }
            }
            else
            {
                begin++;
            }
        }

        return -1;
    }
};

class MedianofTwoSortedArrays
{
public:
/*
方法一：做一个类似于合并两个有序链表的操作，只不过只合并到一半的位置
此种方法的时间复杂度为O(N), 空间复杂度为O(1)
*/
    double soluation1(vector<int>& arr1, vector<int>& arr2)
    {
        if (arr1.size() == 0 && arr2.size() == 0)
            return 0;

        int len1 = arr1.size();
        int len2 = arr2.size();
        int mid = (len1 + len2)/2 + 1;

        int index1 = 0;
        int index2 = 0;
        int midtemp = 0;
        int median = 0;
        int median_prev = 0;
        int temp = 0;

        while((index1 < len1) && (index2 < len2))
        {   
            if (midtemp < mid)
            {
                if (arr1[index1] < arr2[index2])
                {
                    temp = arr1[index1];
                    ++index1;
                }
                else
                {
                    temp = arr2[index2];
                    ++index2;
                }
                ++midtemp;
                
                if (midtemp == mid)
                    median = temp;
                
                if (midtemp == mid - 1)
                    median_prev = temp;
            }
            else
                break;
        }

        while(midtemp < mid && (index1 >= len1 || index2 >= len2))
        {
            if (index1 >= len1)
            {
                temp = arr2[index2];
                ++index2;
            }
            else
            {
                temp = arr1[index1];
                ++index1;
            }
            ++midtemp;

            if (midtemp == mid)
                median = temp;
            if (midtemp == mid - 1)
                median_prev = temp;
        }

        if (((len1 + len2) & 1 )== 1)
        {
            return (double)median;
        }
        else
        {
            return (median + median_prev)/2.0;
        }
    }

/*TODO：

解法二：将两个序列分别取半(k/2)，如果A[k/2 - 1] < B[k/2-1] 那就说明A的前半部分就在整体k中，只可以跑去前半部分去考虑后半部分
反之就说明B的前半部分在整体k中，如果刚好等于那就说明刚好取到，思路很清晰，但是代码需要使用递归，略显困难
*/
    double soluation2(vector<int>& arr1, vector<int>& arr2)
    {
        return 0.0;
    }
};

class LongestConsecutiveSequence
{//无需数列中最长的连续数列，100， 4， 220， 3，1，2  最长的长度是4： 1，2，3，4
public:
/*
1.首先想到的是我们可以先排序再查看连续的最大长度，这样排序所花时间为O(NlogN)，然后暴力检查O(N)，还不一定能找出来，比如1，2，2，2，2，3，还需要去重
2.使用哈希表就能规避掉重复的元素，并且耗时O(N),使用空间O(N)
*/
    int solution1(vector<int>& arr)
    {
        unordered_map<int, bool> seq;
        for (auto i : arr)
            seq[i] = false;
        
        int length = 0;
        int longest = 0;

        for (auto i : arr)
        {
            if (seq[i])
                continue;
            
            longest = 1;
            seq[i] = true;

            for (int j = i+1; seq.find(j) != seq.end(); ++j)
            {
                seq[j] = true;
                ++longest;
            }

            for (int j = i-1; seq.find(j) != seq.end(); --j)
            {
                seq[j] = true;
                ++longest;
            }

            length = length > longest ? length : longest;
        }

        return length;
    }
};

class TwoSum
{
//题目：找出无序数组中两数字之和为target，返回其下标,但不是以0为起始部位，要求index1<index2
public:
/*
方案一：暴力法,时间复杂度O(N²),空间复杂度O(1)
*/
    vector<int> solution1(vector<int>& arr, int target)
    {
        vector<int> answer = {0, 0};
        if (arr.size() < 2)
            return answer;

        bool isFind = false;
        for (int i = 0; i < (int)arr.size() -1; ++i)
        {
            for (int j = i; j < (int)arr.size(); ++j)
            {
                if (arr[i] + arr[j] == target)
                {
                    answer[0] = i+1;
                    answer[1] = j+1;
                    isFind = true;
                    break;
                }
            }
            if(isFind)
                break;
        }

        return answer;
    }

/*
方案二：利用哈希表查找效率为O(1),空间复杂度为O(N),将数组元素所谓key，其下标+1作为value
这样只需要一个循环即可得到对应的值，综合来看时间复杂度为O(N), 空间复杂度为O(N)
*/

    vector<int> solution2(vector<int>& arr, int target)
    {
        vector<int> answer = {0, 0};
        if (arr.size() < 2)
            return answer;
        
        unordered_map<int, int> elem;
        for(int i = 0; i < (int)arr.size(); ++i)
        {
            elem[arr[i]] = i+1;
        }

        for (int i = 0; i < (int)arr.size(); ++i)
        {
            int temp = target - arr[i];
            auto it = elem.find(temp);
            if (it != elem.end())
            {
                answer[0] = it->second < (i+1) ? it->second : (i+1);
                answer[1] = it->second > (i+1) ? it->second : (i+1);
                break;
            }
        }

        return answer;
    }
};

class ThreeSum
{
public:
//题目是要求一个无序的数组中3个元素之和等于0(k),并且返回的数组顺序为升序，并且不得返回重复的数组顺序
//无序的数组不好操作，一般都需要排序，然后a+b+c=k->b+c=k-a这样的TwoSUM问题，前面的TwoSUM要求返回的是下标
//所以不能排序，但这个题目要求的是元素，因此排序后的TwoSum问题该如何解决？答案是左右夹逼
//时间复杂度O(N²),空间复杂度为O(1)

    vector<vector<int>> solution(vector<int> arr, int target)
    {
        vector<vector<int>> result;
        sort(arr.begin(), arr.end());

        auto start = arr.begin();
        auto end = arr.end();
        auto a = start;
        auto b = start;
        auto c = start;

        for(; a < end - 2; ++a)
        {
            if (a > start && (*a) == *(a-1))
                continue;
            int temp = target - *a;
            b = a + 1;
            c = end -1;

            while (b < c)
            {
                int elem = temp - *b;

                if (elem == *c)
                {
                    result.push_back({*a,*b,*c});
                    ++b;
                    --c;
                    while (b < c && *b == *(b-1))
                    {
                        ++b;
                    }
                }
                else if (elem > *c)
                {
                    ++b;
                }
                else
                {
                    --c;
                }
            }
        }

        return result;        
    }
};

class  RemoveElement
{
//题目是移除数组中指定对象，对象在数组中可能出现0次或者多次,返回值为修改后的长度
public:
/*
这是很简单的一个题目，解法也不麻烦,还是要利用哨兵，在等于值的时候不变
*/
    int solution(vector<int>& arr, int target)
    {
        if (arr.size() == 0)
            return 0;
        
        int index = 0;
        for(int i = 0; i < (int)arr.size(); ++i)
        {
            if (arr[i] != target)
            {
                arr[index++] = arr[i];
            }
        }
        return index;
    }
};

class NextPermutation
{
//题目很绕：大致意思是给一个数组，需要处理为下一个比它大一点的数组，并且如果该数组的排列本身是最大的，那么就翻转为最小的【排列组合】
public:
/*
解法：数组的升序是最小的，降序是最大的，那么局部来看也是一样的，因此我们需要将改变降序的元素换到发生改变的地方，这样数组局部变成降序【最大】，
再逆序一下，这样就能得到题目要求；
    8 10 12 5 13 2 1 0 ---> 13打破了逆序，所以和前面一个互换  8 10 12 13 5 2 1 0  -->  再逆序  8 10 12 13 0 1 2 5
    时间复杂度O(N),空间复杂度O(1)
*/
    void solution(vector<int>& arr)
    {
        if (arr.size() <= 1)
            return;
        
        auto rbegin = reverse_iterator<vector<int>::iterator>(arr.end());
        auto rend = reverse_iterator<vector<int>::iterator>(arr.begin());
        auto index = rbegin + 1;

        for(; index != rend; ++index)
        {
            if (*index < *prev(index))
                break;
        }

        if (index == rend)
        {
            reverse(rbegin, rend);
            return;
        }

        auto temp = find_if(rbegin, index, bind1st(less<int>(), *index));
        swap(*index, *temp);
        reverse(rbegin, index);//前闭后开

        return;
    }
};

class PermutationSequence
{
//题目：{1,2,3....n}这样的无重复的数列，求取第K个由小到大的数组组合
//解法一：可以用上面的NextPermutation,循环k-1次，因为最小的就是题目的数组
//      这样的时间复杂度为O(N²)
/*
解法二：利用康托展开，何为康托展开？
      一个数列中，当前在以数列中数字自由组合下，有小到大的顺序数的计算式为 An(N-1)! + An-1(N-2)!+...+A2*1!+A1*0!
      其中自然递增数列是最小的一位，第0位，举例：34521
      3开头，比3小的还有两个，因此为2*4!
      34开头，比4小还有2个，因此还有2*3!
      345开头，比5小的还有2个，因此还有2*2！
      3452开头，比2小的还有1个，因此还有1*1！
      34521开头，还有0*0！，因此加起来为2*24+2*6+2*2+1=65，排名第66位

      那么已知K如何求数列？K首先要减1位，因为康托展开是对于0开始的
      K对(N-1)!做除法，就能得到An，An代表的是该比该数字还小的个数，可以认为An是第(An+1)大的数，
      是不是很熟悉，要是自然数列的话【1开始的】其实An就是下标，这就是第K个数的第一个数字，然后需要对
      (N-1)!取余，并且除去原始数据中的An位的数字，取余之后就变成了An-1(N-2)!+...+A2*1!+A1*0! 
      这样第二次再找，迭代只不过这次除的是(N-2)!

      这样做的时间复杂度极低O(N)
*/
public:
    vector<int> solution(int n, int k)
    {
        vector<int> arr;
        arr.reserve(n);

        for(int i = 0; i < n; ++i)
        {
            arr.push_back(i+1);
        }

        int kangtuo = 1;
        for(int i = 1; i < n; ++i)
        {
            kangtuo *= i;
        }
        --k;
        vector<int> result;
        result.reserve(n);

        for(int i = n-1; i > 0; k %= kangtuo, kangtuo /= i, --i)
        {
            auto res = next(arr.begin(), k / kangtuo);
            result.push_back(*res);
            arr.erase(res);
        }

        result.push_back(arr[0]);
        return result;
    }
};

class ValidSudoku
{
/*题目：给一个9*9的格子，里面有一定的数字，空缺部位用.代替，用一个算法来看看这个数独能否成立
        要求是行，列各自不能重复，并且9*9里面有9个3*3的框，里面的数值也不能重复
*/
public:
/*
如何解决？这个方法在以后的BFS以及DFS也会用到，包括动态规划：判断是否重复，或者已经查看，我们需要标志位去存储
    很简单的方式就是使用布尔变量，使用到了就改为true，没有使用到就用false，当访问同一个位置时发现为true，就说明已经读过了
    时间复杂度O(N²)，空间复杂度O(1)
*/

    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
    };

    bool solution(vector<vector<char>>& arr)
    {
        bool used[9];

        for (int i = 0; i < (int)arr.size(); ++i)
        {
            fill(used, used + 9, false);//检查行
            for (int j = 0; j < (int)arr[i].size(); ++j)
            {
                if (!check(arr[i][j], used))
                    return false;
            }

            fill(used, used+9, false);//检查列
            for (int j = 0; j < (int)arr.size(); ++j)
            {
                if(!check(arr[j][i], used))
                    return false;
            }
        }

        for(int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                fill(used, used+9, false);
                for (int i = 3*row; i < 3*row+3; ++i)
                {
                    for(int j = 3*col; j < 3*col+3; ++j)
                    {
                        if (!check(arr[i][j], used))
                            return false;
                    }
                }
            }
        }

        return true;
    }

    bool check(char ch, bool* used)
    {
        if (ch == '.')//这个还必须在最上面，不然就会出错，优先=='.'返回
            return true;
        
        if (used[ch - '1'])//有数字才要判断这个，没数字就在第一个if就返回了
            return false;

        used[ch - '1'] = true;
        return true;
    }

};

class TrappingRainWater
{
/*题目：由一组无序的非负整数构成的条形图，求各个条形之间能接收多少单位的水
    思路：实质上就是元素左边与右边的最大值中的最小值与元素的差值（>0）
*/
public:
/*
解法一：对每个节点求其左右两边的最大值，然后比较大小，最后求值【暴力解法O(N²),空间O(1)】
*/

    int solution1(vector<int>& arr)
    {
        if (arr.size() < 2)
            return 0;
        
        
        int sum = 0;

        for (int i = 1; i < (int)arr.size() - 2; ++i)
        {
            int max_left = 0;
            int max_right = 0;
            for (int j = i - 1; j >= 0; --j)
            {
                max_left = max_left > arr[j] ? max_left : arr[j];
            }

            for (int j = i + 1; j < (int)arr.size(); ++j)
            {
                max_right = max_right > arr[j] ? max_right : arr[j];
            }

            int temp = max_left < max_right ? max_left : max_right;

            if (temp > arr[i])
            {
                sum += (temp - arr[i]);
            }
        }

        return sum;
    }

/*解法二：与解法一一样，但是不用暴力算，我们使用两个数组装每个元素对应位上的左边最大值与右边最大值
        这样能降低时间复杂度O(N)，空间复杂度为O(N)
*/

    int solution2(vector<int>& arr)
    {
        if (arr.size() < 2)
            return 0;
        
        vector<int> max_left(arr.size(), 0);
        vector<int> max_right(arr.size(), 0);
        int sum = 0;

        for(int i = 1; i < (int)arr.size(); ++i)
        {
            max_left[0] = arr[0];
            //不是跟自身比较，而是跟自身的前一个比较，因为自身不包含在左边，这里可以和下面合并为一个迭代,
            //只是两个迭代看着很明了
            max_left[i] = max_left[i-1] > arr[i-1] ? max_left[i-1] : arr[i-1];

            /*
            max_left[0] = arr[0];
            max_right[arr.size()-1] = arr[arr.size()-1];
            
            max_left[i] = max(max_lefi[i-1], arr[i-1]);
            max_right[arr.size()-1-i] = max(max_right[arr.size() - i], arr[arr.size()-i]);
            */
        }

        for (int i = arr.size() - 2; i >= 0; --i)
        {
            max_right[arr.size() - 1] = arr[arr.size()-1];
            //这个也是一样的，是跟右边比较，不跟自身比较
            max_right[i] = max_right[i+1] > arr[i+1] ? max_right[i+1] : arr[i+1];
        }

        for (int i = 1; i < (int)arr.size() - 1; ++i)
        {
            int temp = min(max_right[i], max_left[i]);
            if (temp > arr[i])
            {
                sum += (temp - arr[i]);
            }
        }

        return sum;
    }

/*
解法三：将最高的柱子分为两半，左边的max_right为柱子，右边的max_left为柱子，因此我们已经知道了最大值，
        左边只需要知道max_left，右边只需要知道max_right;
        这样的时间复杂度为O(N), 空间复杂度为O(1)
*/
    int solution3(vector<int>& arr)
    {
        if (arr.size() < 2)
            return 0;
        int max = 0;
        for (int i = 0; i < (int)arr.size(); ++i)
        {
            if (arr[i] > arr[max])
                max = i;
        }

        int temp = 0;
        int sum = 0;
        for (int i = 1; i < max; ++i)
        {
            if (arr[i] > temp)
                temp = arr[i];
            else
                sum += (temp - arr[i]);
        }

        temp = 0;
        for (int i = arr.size() -1; i > max; --i)
        {
            if (arr[i] > temp)
                temp = arr[i];
            else
                sum += (temp - arr[i]);
        }

        return sum;
    }
};

class RotateImage
{
/*题目：旋转一个n*n的矩阵，顺时针旋转90度*/
public:
/*解法：要观察矩阵的变化，先按照水平翻转，然后斜对角翻转
        翻转的顺序不同也能得到一样的结果，我的顺序是先水平翻转，然后左下->右上式的翻转，剩下的就是观察对应下标的变化了
        时间复杂度O(N²)，空间复杂度O(1)*/

    void solution(vector<vector<int>>& arr)
    {
        if (arr.empty())
            return;
        
        int size = arr.size();

        //水平翻转
        for (int row = 0; row < size/2; ++row)
        {
            for(int col = 0; col < size; ++col)
            {
                swap(arr[row][col], arr[size - 1- row][col]);
            }
        }
        //左下->右上对折
        for (int row = 0; row < size; ++row)
        {
            for (int col = 0; col < size; ++col)
            {
                if (col == row)
                {
                    swap(arr[row][col], arr[size - 1 - row][size - 1 - col]);
                    break;
                }
                else
                {
                    swap(arr[row][col], arr[col][row]);
                }
            }
        }
    }
};

class PlusOne
{
/*题目：以一个数组代替一个数字，对其进行加1操作，返回得到的数组，【我觉得题目有缺陷，arr[0]该为何值也没说,正负两种情况*/
public:
    /*
解法一:首先看首位是负数还是非负数,[0后面再接一个负数就很奇怪,一般要么直接是0,要么是02111这种],正数+1,负数则-1;
        其次正数看最后是9还是非9,9的话变为0并前移一个,再看是不是9,一直到头或者一个不为9的数为止,对其+1;
        负数的话处理的不是9,而是0,类似于9的处理效果,0变成9
*/
    void solution1(vector<int>& arr)
    {
        if (arr.empty())
            return;

        int size = arr.size();
        if (arr[0] >= 0)
        {
            for (int i = size - 1; i >= 0; --i)
            {
                if (arr[i] == 9 && i != 0)
                {
                    arr[i] = 0;
                }
                else
                {
                    ++arr[i];
                    return;
                }
            }
        }
        else
        {
            for (int i = size - 1; i >= 0; --i)
            {
                if (arr[i] == 0 && i != 0)
                {
                    arr[i] = 9;
                }
                else if (i == 0)
                {
                    ++arr[i];
                    return;
                }
                else
                {
                    --arr[i];
                    return;
                }
            }
        }
    }

    /*
解法二[也是标准解法]:首先标准解法认为数组里面的元素是 0 <= elem <= 9,也就是说当出现999这样的情况发生时
    第一位必须是个位数,而不能是10,所以只能用到vector.insert了;[英文中digit就是0-9的数,还是中文博大精深]
    解法也很简洁,也是标准的加法运算,直接相加,然后取余10就是当前位应该有的数,对10取除,则是需要进位的数,
    当进位的数为0时就说明不需要再迭代了
    两种解法的时间复杂度都是O(N),空间复杂度O(1)
*/

    void solution2(vector<int>& arr)
    {
        if (arr.empty())
            return;

        plusX(arr, 1);
    }

    void plusX(vector<int>& arr, int digit)
    {
        int temp = 0;

        for (auto i = arr.rbegin(); i != arr.rend(); ++i)
        {
            temp = *i + digit;
            *i = temp % 10;
            temp /= 10;
            if (temp == 0)
                break;
        }

        if (temp > 0) //还大于0就说明还有需要进位,但是已经到头了,所以我们需要插入一个temp进去
            arr.insert(arr.begin(), temp);
    }
};

class ClimbStair
{
//题目:爬楼梯,你只能一次跨一步或者两步,那么到有n个楼梯的上面时,你有多少种方案?
/*
这是个典型的斐波那契额数列,如何分析得出的呢?假设到顶点一共有f(n)种,那么如何到N去呢,此时有两种一种是N-1跨一步,
一种是N-2跨两步,也就是说不过过程如何,你最后一定到达N-1或者N-2这两个楼梯的一个,因此就有f(N) = f(N-1) + f(N-2);
这样的函数关系不难得出.到达N-1有f(N-1)个方案,到达N-2有f(N-2)个方案.

既然已知这样的函数关系,那么又该如何解决?要么递归,要么迭代
*/
public:
/*方法一:递归,递归的程序很简单,给出边界条件即可,但是当N特别大时就会导致崩溃,所以要慎重使用递归
        时间复杂度O(2^N) --->每展开一个fn就需要两个fn-1与fn-2,呈指数级别增长, 空间复杂度O(N)*/
    int solution1(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)//上一个台阶只有一种
            return 1;
        if (n == 2)//上两个台阶可以一下跨2步,也可以跨两个1步,到f(3)就符合规律了,1+1+1,1+2,2+1,满足f(1)+f(2)
            return 2;

        return solution1(n - 1) + solution1(n - 2);
    }

/*方法二:迭代,递归与迭代基本上是可以互相转化的,迭代实现起来可能不是很让人看懂
        时间复杂度O(N),空间复杂度O(1)*/
    int solution2(int n)
    {
        int fn = 0;
        int fn_1 = 1;
        int fn_2 = 0;

        for (int i = 1; i <= n; ++i)
        {
            fn = fn_1 + fn_2;
            fn_2 = fn_1;
            fn_1 = fn;
        }

        return fn;
    }
};

class SetMatrixZeroes
{
/*将一个矩阵中含有0的行与列重置为0
    2 5 6 9         0 0 6 9
    4 0 7 1  --->   0 0 0 0
    0 6 9 3         0 0 0 0
*/
public:
/*
这个题目还是很简单的，就是要使用利用布尔变量设置的标志位【我总是容易忘记这个特性】，难点在于如何降低空间复杂度
解法一：也是空间复杂度最高的一个O(m*n),设置一个bool[m][n],嵌套迭代查询为0的项,将bool置为true,完后,重新迭代一次,将为true的
        的行与列全部归0,实现很简单很易懂,空间复杂度最高
解法二: 不申请这么大的bool矩阵,我们改进为存储为0项的行列二元数组,vector<pair<int,int>>形式,嵌套迭代并插入其中
        而后,逐一访问并重置矩阵,在0项较少时空间复杂度很低,但是假设全部为0时,其空间复杂度还是为O(m*n),写法也是很简单
解法三: 还是要使用bool变量，但是不适用m*n的大型矩阵，对所有的列用一个bool数组，对所有的行用一个bool数组
        这样空间复杂度就降为O(m+n)
*/

    vector<vector<int>> solution1(vector<vector<int>> arr)
    {
        int row_size = arr.size();
        int col_size = arr[0].size();

        vector<bool> row_bool(row_size, false);
        vector<bool> col_bool(col_size, false);

        for (int row = 0; row < row_size; ++row)
        {
            for (int col = 0; col < col_size; ++col)
            {
                if (arr[row][col] == 0)
                {
                    row_bool[row] = true;
                    col_bool[col] = true;
                }
            }
        }

        for (int row = 0; row < row_size; ++row)
        {
            for (int col = 0; col < col_size; ++col)
            {
                if (row_bool[row] || col_bool[col])
                {
                    arr[row][col] = 0;
                }
            }
        }

        return arr;
    }
/*
解法四：那么还有没有一种耗用空间复杂度更低的手段呢？答案是有的，从上面就能知道，把所有等于0的项投影到row_bool与col_bool
        上，根据这两个的真值去重置0，我们可以将这两个数组安排在第一行与第一列上，只要arr[i][j]为0，那么就将
        第arr[i][0],arr[0][j]置为0，也就是说只需要这时候只需要遍历第一列，第一行的数字就知道要重置哪些列哪些行了。
        但是在实际处理时会发现，假设原本没有0的第一行此时该如何处理？我们已经修改了第一行的数据，将其某个位置置为0，所以
        在嵌套迭代重置0的时候，需要对第一行以及第一列分类讨论，1，如果第一行或者第一列原本没有0值，就不要对其重置 2，如果
        本来就有0，才要对其重置。那么如何判断这个分类？答案就是需要对原来的未修改的第一行第一列都轮询一次，如果有0就要set
        一个标志位
*/
    vector<vector<int>> solution2(vector<vector<int>> arr)
    {
        int row_size = arr.size();
        int col_size = arr[0].size();
        bool row_has_zero = false;
        bool col_has_zero = false;

        for (int col = 0; col < col_size; ++col)
        {
            if (arr[0][col] == 0)
            {
                row_has_zero = true;
                break;
            }
        }

        for (int row = 0; row < row_size; ++row)
        {
            if (arr[row][0] == 0)
            {
                col_has_zero = true;
                break;
            }
        }

        for (int row = 1; row < row_size; ++row)
        {
            for (int col = 1; col < col_size; ++col)
            {
                if (arr[row][col] == 0)
                {
                    arr[row][0] = 0;
                    arr[0][col] = 0;
                }
            }
        }

        for (int row = 1; row < row_size; ++row)
        {
            for (int col = 1; col < col_size; ++col)
            {
                if (arr[0][col] == 0 || arr[row][0] == 0)
                {
                    arr[row][col] = 0;
                }
            }
        }

        if (row_has_zero)
        {
            for (int col = 0; col < col_size; ++col)
            {
                arr[0][col] = 0;
            }
        }

        if (col_has_zero)
        {
            for (int row = 0; row < row_size; ++row)
            {
                arr[row][0] = 0;
            }
        }

        return arr;
    }
};

int main(int argc, char** argv)
{
    //vector<int> arr = {0,1,2,2,3,4,5,6,6,7,7,7,8,8,8,9,10,10,10,10};
    //cout << removeDuplicatesfromSortedArray().soluation2(arr) << endl;
    //cout << removeDuplicatesfromSortedArrayII().soluation(arr) << endl;
    //vector<int> arr1 = {26,31,36,36,37,40,46,1,1,2,3,6,12,12,17,17,18,19,20,23};
    //cout << SearchinRotatedSortedArray().souluation(arr1, 6) << endl;
    //cout << SearchinRotatedSortedArray().souluation(arr1, 37) << endl;

    //vector<int> arr1 = {1,3,5,7,9};
    //vector<int> arr2 = {2,4,6,8};
    //cout << MedianofTwoSortedArrays().soluation1(arr1, arr2) << endl;

    //vector<int> arr1 = {9,7,8,14,10,1,14,3,5,8,9,3,10,7,4,9,4,12,1,10};
    //cout << LongestConsecutiveSequence().solution1(arr1) << endl;

    /*vector<int> arr1 = {11, 7, 15, 40, 2};
    vector<int> ans = TwoSum().solution2(arr1, 9);
    for(auto i:ans)
        cout << i << " ";
    cout << endl;*/

    //vector<int> arr = {0,-1,2,1,5,-1};
    /*vector<vector<int>> result = ThreeSum().solution(arr, 0);
    for(int i = 0; i < result.size(); ++i)
    {
        for(auto s:result[i])
            cout << s << " ";
        cout << endl;
    }*/
    //cout << RemoveElement().solution(arr, -1) << endl;
    /*vector<int> arr = {0,1,2,5,8,10,12,13};
    NextPermutation().solution(arr);*/
    /*vector<int> arr = {1,2,3};

    for(int i = 0; i < 6; ++i)
    {
        NextPermutation().solution(arr);
        for (auto s:arr)
            cout << s << " ";
        cout << endl;
    }*/
    
    /*vector<int> res = PermutationSequence().solution(5, 107);
    for(auto s:res)
        cout << s << " ";
    cout << endl;*/

    /*ValidSudoku ins;
    cout << ins.solution(ins.board) << endl;*/

    /*vector<int> arr = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << TrappingRainWater().solution3(arr) << endl;*/

    /*vector<vector<int>> matix = {
        {0,1,2,3,4,5},
        {6,7,8,9,10,11},
        {12,13,14,15,16,17},
        {18,19,20,21,22,23},
        {24,25,26,27,28,29},
        {30,31,32,33,34,35},
    };*/
    /*vector<vector<int>> matix = {{1,2},{3,4}};
    
    RotateImage().solution(matix);
    for(int i = 0; i < 6; ++i)
    {
        for(auto s : matix[i])
            cout << s << " ";
        cout << endl;
    }*/

    /*vector<int> arr = {5,8,5,9,5,9};
    PlusOne().solution2(arr);
    for (auto s:arr)
        cout << s;
    cout << endl;*/

    /*cout << ClimbStair().solution2(10) << endl;
    cout << ClimbStair().solution1(10) << endl;*/

    vector<vector<int>> arr = {
        {2, 5, 6, 0},
        {4, 0, 7, 1},
        {6, 5, 9, 7}
    };

    vector<vector<int>> ret = SetMatrixZeroes().solution2(arr);
    for (int i = 0; i < (int)ret.size(); ++i)
    {
        for (auto s:ret[i])
        {
            cout << s << " ";
        }
        cout << endl;
    }

        return 0;
}





