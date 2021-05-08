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
        for(int i = 1; i < arr.size(); ++i)
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
        for(int i = 2; i < arr.size(); ++i)
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

        if ((len1 + len2) & 1 == 1)
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
        for (int i = 0; i < arr.size() -1; ++i)
        {
            for (int j = i; j < arr.size(); ++j)
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
        for(int i = 0; i < arr.size(); ++i)
        {
            elem[arr[i]] = i+1;
        }

        for (int i = 0; i < arr.size(); ++i)
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
        for(int i = 0; i < arr.size(); ++i)
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

        for (int i = 0; i < arr.size(); ++i)
        {
            fill(used, used + 9, false);//检查行
            for (int j = 0; j < arr[i].size(); ++j)
            {
                if (!check(arr[i][j], used))
                    return false;
            }

            fill(used, used+9, false);//检查列
            for (int j = 0; j < arr.size(); ++j)
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

        for (int i = 1; i < arr.size() - 2; ++i)
        {
            int max_left = 0;
            int max_right = 0;
            for (int j = i - 1; j >= 0; --j)
            {
                max_left = max_left > arr[j] ? max_left : arr[j];
            }

            for (int j = i + 1; j < arr.size(); ++j)
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

        for(int i = 1; i < arr.size(); ++i)
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

        for (int i = 1; i < arr.size() - 1; ++i)
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
        for (int i = 0; i < arr.size(); ++i)
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
    vector<vector<int>> matix = {{1,2},{3,4}};
    
    RotateImage().solution(matix);
    for(int i = 0; i < 6; ++i)
    {
        for(auto s : matix[i])
            cout << s << " ";
        cout << endl;
    }

    return 0;
}





