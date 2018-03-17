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
    e = *p;                                     //被删除元素的值赋给e
    q = L.elem + L.length - 1;                  //表尾元素的位置
    for(++p; p <= q; ++p) *(p-1) = *p           //被删除元素之后的元素左移
    --L.length                                  //表长减1
    return OK;
}//ListDelete_Sq

int main()
{
    return 0;
}
//int ListLength_Sq(SqList &L)