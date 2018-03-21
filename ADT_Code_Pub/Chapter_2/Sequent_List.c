//SEQUENT_LIST
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

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
#define LIST_INIT_SIZE 100    //顺序表存储空间的初始分配量
#define LISTINCREMENT   10    //顺序表存储空间的分配增量
typedef int ElemType;         //顺序表存储的数据类型
struct SqList{
    ElemType  *elem;          //储存空间基址
    int       length;         //当前长度
    int       listsize;       //当前分配的储存容量(以sizeof(ElemType)为单位)
};
//-----------------------------

//---------|FuncList|----------
Status InitList_Sq(struct SqList*);
    //构造一个空的顺序表L
Status DestroyList_Sq(struct SqList*);
    //销毁顺序表L
void ClearList_Sq(struct SqList*);
    //将L重置为空表
Status ListEmpty_Sq(struct SqList*);
    //判断L是否为空表
int ListLength_Sq(struct SqList*);
    //返回L中数据元素的个数
Status GetElem_Sq(struct SqList*, int, ElemType*);
    //用e返回L中第i个数据元素的值
int compare(ElemType, ElemType);
    //元素的比较函数
int LocateElem_Sq(struct SqList*, ElemType, int (*compare)(ElemType, ElemType));
    //在顺序顺序表L中查找第1个值与e满足compare()的元素的位序
Status PriorElem_Sq(struct SqList*, ElemType, ElemType*);
    //返回cur_e的前驱节点pre_e
Status NextElem_Sq(struct SqList*, ElemType, ElemType*);
    //返回cur_e的后继节点next_e
Status ListInsert_Sq(struct SqList*, int, ElemType);
    //在顺序表L中第i个位置之前插入新的元素e
Status ListDelete_Sq(struct SqList*, int, ElemType*);
    //在顺序表L中删除第i个元素，并用e返回其值
void MergeList_Sq(struct SqList*, struct SqList*, struct SqList*, int (*compare)(ElemType, ElemType));
    //已知顺序表La和Lb的元素按值非递减排列
Status ListTraverse_Sq(struct SqList*, Status (*visit)(ElemType*));
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintList_Sq(struct SqList*);
    //打印顺序表L
//-----------------------------

int main()
{
    return 0;
}

//-----------------------------
Status InitList_Sq(struct SqList *L)
{
    //构造一个空的顺序表L
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}//InitList_Sq

Status DestroyList_Sq(struct SqList *L)
{
    //销毁顺序表L
    if(!L->listsize) return ERROR; //已是空表
    free(L->elem);
    L->length = 0;
    L->listsize = 0;
    return OK;
}//DestroyList_Sq

void ClearList_Sq(struct SqList *L)
{
    //将L重置为空表
    L->length = 0;
}//ClearList_Sq

Status ListEmpty_Sq(struct SqList *L)
{
    //判断L是否为空表
    if(L->length == 0)
        return TRUE;
    else return FALSE;
}//ListEmpty_Sq

int ListLength_Sq(struct SqList *L)
{
    //返回L中数据元素的个数
    return L->length;
}//ListLength_Sq

Status GetElem_Sq(struct SqList *L, int i, ElemType *e)
{
    //用e返回L中第i个数据元素的值
    //i的合法值为1<=i<=ListLength_Sq(L)
    if((i < 1) || (i > L->length)) return ERROR; //i值不合法
    *e = L->elem[i - 1];
    return OK;
}//GetElem_Sq

int compare(ElemType a, ElemType b)
{
    //元素的比较函数
    return a-b;
}

int LocateElem_Sq(struct SqList *L, ElemType e, int (*compare)(ElemType, ElemType))
{
    //在顺序顺序表L中查找第1个值与e满足compare()的元素的位序
    //若找到，则返回其在L中的位序，否则返回0
    ElemType *p;
    int i = 1;    //i的初值为第1个元素的位序
    p = L->elem;   //p的初值为第1个元素的储存位置
    while(i <= L->length && (*compare)(*p++, e)) ++i;
    if(i <= L->length) return i;
    else return 0;
}//LocateElem_Sq

Status PriorElem_Sq(struct SqList *L, ElemType cur_e, ElemType *pre_e)
{
    //返回cur_e的前驱节点pre_e
    int Location;
    Location = LocateElem_Sq(L, cur_e, compare);
    if(Location < 2) return ERROR;
    else *pre_e = L->elem[Location - 2];
    return OK;
}//PriorElem_Sq

Status NextElem_Sq(struct SqList *L, ElemType cur_e, ElemType *next_e)
{
    //返回cur_e的后继节点next_e
    int Location;
    Location = LocateElem_Sq(L, cur_e, compare);
    if(Location == 0 || Location == L->length) return ERROR;
    else *next_e = L->elem[Location];
    return OK;
}//NextElem_Sq

Status ListInsert_Sq(struct SqList *L, int i, ElemType e)
{
    //在顺序表L中第i个位置之前插入新的元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
    ElemType *newbase, *q, *p;
    if(i < 1 || i > L->length+1) return ERROR; //i值不合法
    if(L->length >= L->listsize)
    {
        newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);           //储存分配失败
        L->elem = newbase;                     //新基址
        L->listsize += LISTINCREMENT;          //增加储存容量
    }
    q = &(L->elem[i-1]);                       //q为插入地址
    for(p = &(L->elem[L->length-1]); p >= q; --p)
        *(p + 1) = *p;                         //插入位置及之后的元素右移
    *q = e;                                    //插入e
    L->length++;                               //表长增1
    return OK;
}//ListInsert_Sq

Status ListDelete_Sq(struct SqList *L, int i, ElemType *e)
{
    //在顺序表L中删除第i个元素，并用e返回其值
    //i的合法值为1<=i<=ListLength_Sq(L)
    ElemType *p, *q;
    if((i < 1) || (i > L->length)) return ERROR; //i值不合法
    p = &(L->elem[i - 1]);                       //p为被删除元素的位置
    *e = *p;                                    //被删除元素的值赋给e
    q = L->elem + L->length - 1;                  //表尾元素的位置
    for(++p; p <= q; ++p) *(p-1) = *p;          //被删除元素之后的元素左移
    L->length--;                                 //表长减1
    return OK;
}//ListDelete_Sq

void MergeList_Sq(struct SqList *La, struct SqList *Lb, struct SqList *Lc, int (*compare)(ElemType, ElemType))
{
    //已知顺序表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的顺序表Lc，Lc的元素也按值非递减排列
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    Lc->listsize = La->length + Lb->length;
    Lc->length = La->length + Lb->length;
    Lc->elem = (ElemType*)malloc(Lc->listsize * sizeof(ElemType));
    if(!Lc->elem) exit(OVERFLOW);
    pa = La->elem; pb = Lb->elem; pc = Lc->elem;
    pa_last = La->elem + La->length - 1;
    pb_last = Lb->elem + Lb->length - 1;
    while(pa <= pa_last && pb <= pb_last)//归并
    {
        if((*compare)(*pa, *pb) < 0)
            *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while(pa <= pa_last) *pc++ = *pa++; //插入La剩余元素
    while(pb <= pb_last) *pc++ = *pb++; //插入Lb剩余元素
}//MergeList_Sq

Status ListTraverse_Sq(struct SqList *L, Status (*visit)(ElemType*))
{
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    int i = 0;
    if (ListEmpty_Sq(L) == TRUE)
        return ERROR;
    while(i < L->length && visit(L->elem + i) == OK)
        i++;
    if(i >= L->length) return OK;
    else return ERROR;
}

Status PrintList_Sq(struct SqList *L)
{
    //打印顺序表L
    int i;
    for(i = 0; i < L->length; i++)
        printf("%d\t", *(L->elem + i));
    printf("\n");
}
