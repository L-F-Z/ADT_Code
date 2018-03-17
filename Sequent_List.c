#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
//----------|Status|-----------
typedef int    Status;
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2
//-----------------------------

//---------|Typedef|-----------
#define LIST_INIT_SIZE 100    //线性表存储空间的初始分配量
#define LISTINCREMENT   10    //线性表存储空间的分配增量
typedef int ElemType;         //线性表存储的数据类型
struct SqList{
    ElemType  *elem;          //储存空间基址
    int       length;         //当前长度
    int       listsize;       //当前分配的储存容量(以sizeof(ElemType)为单位)
};
//-----------------------------

Status InitList_Sq(struct SqList L)
{
    //构造一个空的线性表L
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}//InitList_Sq

Status ListInsert_Sq(struct SqList L, int i, ElemType e)
{
    //在顺序线性表L中第i个位置之前插入新的元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
    ElemType *newbase, *q, *p;
    if(i < 1 || i > L.listsize+1) return ERROR; //i值不合法
    if(L.length >= L.listsize)
    {
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW); //储存分配失败
        L.elem = newbase;            //新基址
        L.listsize += LISTINCREMENT; //增加储存容量
    }
    q = &(L.elem[i-1]);              //q为插入地址
    for(p = &(L.elem[L.length-1]); p >= q; --p)
        *(p + 1) = *p;               //插入位置及之后的元素右移
    *q = e;                          //插入e
    L.length++;                      //表长增1
    return OK;
}//ListInsert_Sq

Status ListDelete_Sq(struct SqList L, int i, ElemType *e)
{
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为1<=i<=ListLength_Sq(L)
    ElemType *p, *q;
    if((i < 1) || (i > L.length)) return ERROR; //i值不合法
    p = &(L.elem[i - 1]);                       //p为被删除元素的位置
    *e = *p;                                    //被删除元素的值赋给e
    q = L.elem + L.length - 1;                  //表尾元素的位置
    for(++p; p <= q; ++p) *(p-1) = *p;          //被删除元素之后的元素左移
    L.length--;                                 //表长减1
    return OK;
}//ListDelete_Sq

int compare(ElemType a, ElemType b)
{
    //元素的比较函数
    return a-b;
}

int LocateElem_Sq(struct SqList L, ElemType e, int (*compare)(ElemType, ElemType))
{
    //在顺序线性表L中查找第1个值与e满足compare()的元素的位序
    //若找到，则返回其在L中的位序，否则返回0
    ElemType *p;
    int i = 1;    //i的初值为第1个元素的位序
    p = L.elem;   //p的初值为第1个元素的储存位置
    while(i <= L.length && !(*compare)(*p++, e)) ++i;
    if(i <= L.length) return i;
    else return 0;
}//LocateElem.Sq

void MergeList_Sq(struct SqList La, struct SqList Lb, struct SqList Lc, int (*compare)(ElemType, ElemType))
{
    //已知顺序线性表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    Lc.listsize = La.length + Lb.length;
    Lc.length = La.length + Lb.length;
    Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
    if(!Lc.elem) exit(OVERFLOW);
    pa = La.elem; pb = Lb.elem; pc = Lc.elem;
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while(pa <= pa_last && pb <= pb_last)//归并
    {
        if((*compare)(*pa, *pb) < 0)
            *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while(pa <= pa_last) *pc++ = *pa++; //插入La剩余元素
    while(pb <= pb_last) *pc++ = *pb++; //插入Lb剩余元素
}//MergeList_Sq

int main()
{
    return 0;
}
//int ListLength_Sq(SqList &L)