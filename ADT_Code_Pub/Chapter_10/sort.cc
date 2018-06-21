//OO_ADT_Code Project
//https://github.com/L-F-Z/ADT_Code
//https://github.com/AugustusWillisWang/Notes/tree/master/DataStructure/ooadt
//Developed by AugustusWillisWang

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

#include <string.h>
#include <stdio.h>

#include "adt.h"
#include "dbg.h"

int test[] = {3, 6, 2, 5, 4, 8, 4, 123, 54};//9

template<class T>
int printit(T* src, int size)
{
    int a=0;
    while(a<size)
    {
        std::cout << src[a] << " ";
        a++;
    }
    std::cout << std::endl;
    return 0;
}

template<class T>
int insert_sort2(T* src, int size)
{
    int i = 1;
    while(i<size)
    {
        for (int j = 0;j<i;j++)
        {
            if(src[i]>src[j])
            {
                T tmp = src[i]; //i is current insert index;
                for (int p = i;p>j;p--)
                {
                    src[p] = src[p - 1];
                }
                src[j] = tmp;
                break;
            }
        }
        i++;
    }
}

template<class T>
int insert_sort(T* src, int size)
{
    int i = 1;
    while(i<size)
    {
        T tmp = src[i];
        int p = i-1;
        for (; (p >= 0)&&(src[p] < tmp); p--)
        {
            src[p+1] = src[p];
        }
        src[p + 1] = tmp;
        i++;
    }
}

// inline shell_gap()

template <class T>
int shell_sort(T *src, int size, int* shell_gap, int shell_gap_size)
{
    int a = 0;
    while(a<shell_gap_size)
    {
        int b=0;
        while(b<shell_gap[a])
        {
            // int insert_sort2(T * src, int size)
            {
                int i = 1*shell_gap[a]+b;
                while (i < size)
                {
                    T tmp = src[i];
                    int p = i - 1*shell_gap[a];
                    for (; (p >= 0) && (src[p] < tmp); p--)
                    {
                        src[p + 1*shell_gap[a]] = src[p];
                    }
                    src[p + 1* shell_gap[a]] = tmp;
                    i += shell_gap[a];
                }
            }

            b++;
        }
        a++;
    }
}

template<class T>
int bubble_sort(T* src, int size)
{

    for (int top = size - 1; top > 0;top--)
    {
        for (int i = 1;i<=top;i++)
        {
            if(src[i]>src[i-1])
            {
                auto temp=src[i];
                src[i]=src[i-1];
                src[i - 1] = temp;
            }
        }
    }
}

template<class T>
inline void mswap(T &a, T&b)
{
    auto t = a;
    a=b;
    b = t;
}

template <class T>
mqsort(T *src, int begin, int end)
{
    if(begin>=end)
        return 0;
    int medium = (begin + end) / 2;
    T midval = src[medium];
    mswap<T>(src[begin], src[medium]);
    int head = begin;
    int foot = end;
    while(head<foot)
    {
        for (; (head < foot)&&(src[foot]<=midval);foot--);
            mswap<T>(src[foot],src[head]);
        for (; (head < foot)&&(src[head]>=midval);head++);
            mswap<T>(src[head],src[foot]);
    }
    src[head]=midval;
    mqsort(src, begin, head - 1);
    mqsort(src, head+1, end);
}

template<class T>
int quick_sort(T* src, int size)
{
    mqsort<T>(src, 0, size-1);
}

template<class T>
select_sort(T* src, int size)
{
    while(size-->0)
    {
        //size is the palce o be filled in
        //find min
        T min=src[0];
        int index = 0;
        for (int i = 1; i <= size; i++)
        {
            if(src[i]<min)
            {
                min = src[i];
                index = i;
            }
        }
        mswap<T>(src[index], src[size]);
    }
}

template<class T>
heap_adjust(T* src, int size, int root)
{
    //little top heap heap_adjust
    int l = (root+1) * 2-1;
    int r = l+1;
    if (l< size)
    {
        if(src[l]<src[root])
        {
            mswap(src[root], src[l]);
            heap_adjust(src, size, l);
        }
    }
    if (r< size)
    {
        if(src[r]<src[root])
        {
            mswap(src[root], src[r]);
            heap_adjust(src, size, r);
        }
    }
}

template <class T>
heap_build(T *src, int size)
{
    if(size<2)
        return 1;
    int noleaf = (size+1) >> 1-1;
    while(noleaf-->0)
    {
        heap_adjust(src, size, noleaf);
    }
}

template <class T>
heap_sort(T* src, int size)
{
    heap_build(src,size);
    // printit<int>(test, 9);

    int step = size;
    while (step-->1)
    {
        mswap<T>(src[0], src[step]);
        // printit<int>(test, 9);   
        heap_adjust(src, --size, 0);
    }
    mswap<T>(src[0], src[step]);
}

#include<cstring>

template<class T>
int merge_atom(T* src, int begin1, int end1, int begin2, int end2, T* temp)
{

    memcpy(temp+begin1,src+begin1,(end2-begin1)*sizeof(T));
    int point1=begin1;
    int point2=begin2;
    int now = begin1;
    while((point1!=(end1+1))&&(point2!=(end2+1)))
    {
        if(temp[point1]>temp[point2])
        {
            src[now] = temp[point1];
            point1++;
            now++;
        }
        else
        {
            src[now]=temp[point2];
            point2++;
            now++;
        }
    }
    while(point1<(end1+1))
    {
        src[now++] = temp[point1++];
    }
    while(point2<(end2+1))
    {
        src[now++] = temp[point2++];
    }
}

template<class T>
int merge_sort_atom(T* src, int begin, int end, T* temp)
{
    int size = (end - begin + 1);
    if(size<=1)
        return 1;
    int m = (begin+end)>>1;
    merge_sort_atom<T>(src,begin,m,temp);
    merge_sort_atom<T>(src,m+1,end,temp);
    memcpy(temp+begin, src+begin, size * sizeof(T));
    merge_atom<T>(src, begin, m, m + 1, end, temp);
    printit<int>(test, 9);
}

template<class T>
int merge_sort(T* src, int size)
{
    T *temp = new T[size];
    merge_sort_atom<T>(src, 0, size - 1,temp);
}

template<class T>
int radix_sort(T* src, int size)
{
    // link table radix sort.
    // use link table to save the data.
    // use LSD: least significant digit first.
    // for each possible value of key, set up a link head;
    // do traverse, add element to according link head
    // link each link head`
}



//test-------------------

// int main()
// {
//     merge_sort<int>(test, 9);
//     printit<int>(test, 9);

//     heap_sort<int>(test, 9);
//     printit<int>(test, 9);

//     select_sort<int>(test, 9);
//     printit<int>(test, 9);

//     quick_sort<int>(test, 9);
//     printit<int>(test, 9);

//     bubble_sort<int>(test, 9);
//     printit<int>(test, 9);

//     insert_sort2<int>(test, 9);
//     printit<int>(test, 9);
// }