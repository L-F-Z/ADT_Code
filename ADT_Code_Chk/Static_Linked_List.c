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
#define MAXSIZE   100
typedef int ElemType;
struct component{
    ElemType data;
    int      cur;
};
typedef struct component SLinkList[MAXSIZE];
//-----------------------------

//---------|FuncList|----------
int Malloc_SL(SLinkList space)
{
    //若备用空间链表非空，则返回分配的节点下标，否则返回0
    int i;
    i = space[0].cur;
    if(space[0].cur)
        space[0].cur = space[i].cur;
    return i;
}//Malloc_SL

int Free_SL(SLinkList space, int k)
{
    //将下标为k的空闲节点回收到备用链表
    space[k].cur = space[0].cur;
    space[0].cur = k;
    return OK;
}//Free_SL

Status InitList_SL(SLinkList space)
{
    //构造一个空的静态链表
    //将一维数组space中各分量链成一个备用链表，space[0].cur为头指针
    //"0"表示空指针
    int i;
    for(i = 0; i < MAXSIZE - 1; i++)
        space[i].cur = i + 1;
    space[MAXSIZE - 1].cur = 0;
    return OK;
}

int CreateList(SLinkList space, int n)
{
    //创建一个含有n个结点的静态链表，返回表头在存储数组的位置
    int head, k, s, i;
    k = Malloc_SL(space); //从空闲链表中取得一个空结点
    head = k;
    for(i = 0; i < n; i++)
    {
        s = Malloc_SL(space);
        space[s].data = 5 * i;
        //scanf("%d", &space[s].data);
        space[k].cur = s;
        k = s;
    }
    space[k].cur = 0;
    return head;
}

// Status ClearList_SL(SLinkList space)
//     //重置为空表
// Status ListEmpty_SL(SLinkList space, int head)
//     //静态链表判空
// int ListLength_SL(SLinkList space, int head)
//     //求静态链表长度
// Status Locatepos_SL(SLinkList space, int head, int i, ElemType *e)
//     //用e返回链表第i个节点的元素值，其中head为表头指针
// int Prior_SL(SLinkList space, int head, int i)
//     //改变当前指针指向其前驱，错误则返回0
// int Next_SL(SLinkList space, int i)
//     //改变当前指针指向其后继，错误则返回0
// Status ListTraverse_SL(SLinkList space, int head, Status (*visit)(ElemType*))
//     //对每个元素调用函数visit,一旦visit()失败，则操作失败
// Status LocateElem_SL(SLinkList space, ElemType e, int *head, int(*compare)(ElemType, ElemType))
//     //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
// ElemType GetCurElem_SL(SLinkList space, int i)
//     //返回当前指针所指数据元素
// Status SetCurElem_SL(SLinkList space, int i, ElemType e)
//     //更新当前指针所指数据元素
// Status Append_SL(SLinkList space, int head, int s)
//     //s指向的一串节点连接在最后一个节点之后
// Status InsAfter_SL(SLinkList space, int i)
//     //将元素e插入在当前指针之后
// Status DelAfter_SL(SLinkList space, int i)
//     //删除当前指针之后的节点
// void MergeList_SL(SLinkList space, int a, int b, int c, int (*compare)(ElemType, ElemType))
//     //在La和Lb有序的前提下，合并出Lc
//void Difference_SL(SLinkList space, int a, int b, int c)
//     //在c中建立(a-b)∪(b-a)
// int compare(ElemType a, ElemType b)
//     //元素比较函数， 返回a-b

void PrintList_SL(SLinkList space, int head)
{
    //从头结点开始，依次输出以后所有结点值
    int pos;
    pos = space[head].cur;
    while(pos)
    {
        printf("%d\t", space[pos].data);
        pos = space[pos].cur;
    }
    printf("\n");
}

//-----------------------------------------
/*
Status ClearList_SL(SLinkList space)
{
    //重置为空表
    if(!space[0].cur) return ERROR;//已是空表
    return initList_SL(space);
}//ClearList_SL

Status ListEmpty_SL(SLinkList space, int head)
{
    //静态链表判空
    if(!space[0].cur)
        return TRUE;
    else
        return FALSE;
}//ListEmpty_SL

int ListLength_SL(SLinkList space, int head)
{
    //求静态链表长度
    int i = 0;
    int k = space[head].cur;
    while(!space[k].cur)
    {
        k = space[k].cur;
        i++;
    }
    return i;
}//ListLength_SL

Status Locatepos_SL(SLinkList space, int head, int i, ElemType *e)
{
    //用e返回链表第i个节点的元素值，其中head为表头指针
    //i的合法值为1<=i<=SLinkLength_Sq(SLinkList space)
    int j;
    int k = head;
    if((i < 1) || (i > SLinkLength_Sq(space))) return ERROR; //i值不合法
    for(j = 1; j <= i; k++)
    {
        k = space[k].cur;
    }
    e = space[k].data;
    return OK;
}//Locatepos_SL
int Prior_SL(SLinkList space, int head, int i){
    //改变当前指针指向其前驱，错误则返回0
    if(i < 0 || i > MAXSIZE - 1) return 0; //i不合法
    int pr;
    int k = head;
    for(pr = 0; space[k].cur != i; )
    {
        pr = k;
        k = space[k].cur;
    }
    return k;
}//Prior_SL

int Next_SL(SLinkList space, int i)
{
    //head没必要
    //改变当前指针指向其后继，错误则返回0
    if(i < 0 || i > MAXSIZE - 1) return 0; //i不合法
    return space[i].cur;
}//Next_SL
Status ListTraverse_SL(SLinkList space, int head, Status (*visit)(ElemType*))
{
    //对每个元素调用函数visit,一旦visit()失败，则操作失败
    int i,k = space[head].cur;
    for(i = 0; i < ListLength_SL(space,head) && visit(space[k].data); i++, k = space[k].cur)
        ;
    if(i < ListLength_SL(space,head)) return ERROR;
    else return OK;
}//ListTraverse_SL
Status LocateElem_SL(SLinkList space, int *head, ElemType e, int(*compare)(ElemType, ElemType))
{
    //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
    int k;
    for(k = *head; !compare(e,space[k].data) && k; k = space[k].cur)
        ;
    if(k)
    {
        *head = k;
        return OK;
    }
    else return ERROR;
}//LocateElem_SL
ElemType GetCurElem_SL(SLinkList space, int i)
{
    //返回当前指针所指数据元素
    if(i < 0 || i > MAXSIZE - 1) return ERROR; //i不合法
    return space[i].data;
}//GetCurElem_SL
Status SetCurElem_SL(SLinkList space, int i, ElemType e)
{
    //更新当前指针所指数据元素
    if(i < 0 || i > MAXSIZE - 1) return ERROR; //i不合法
    space[i].data = e;
    return OK;
}//SetCurElem_SL
    pos = space[head].cur;
    while(pos)
    {
        printf("%d\t", space[pos].data);
        pos = space[pos].cur;
    }
    printf("\n");
}
*/
Status Append_SL(SLinkList space, int head, int s)
{
    //应该提供的是int s而非SLinkList s吧
    //s指向的一串节点连接在最后一个节点之后
    if(head < 1 || head > MAXSIZE-1) return ERROR;  //head不合法，上面好像都没有考虑
    if(s < 1 || s > MAXSIZE-1) return ERROR;  //s不合法
    int k = head;
    while(space[k].cur)  //寻找最后一个节点
        k = space[k].cur;
    space[k].cur = s;
    return OK;
}//Append_SL

Status InsAfter_SL(SLinkList space, int i, ElemType e)
{
    //将元素e插入在当前指针之后
    if(i < 1 || i > MAXSIZE-1) return ERROR;  //i不合法
    int k = Malloc_SL(space);
    space[k].data = e;
    space[k].cur = space[i].cur;
    space[i].cur = k;
    return OK;
}//InsAfter_SL

Status DelAfter_SL(SLinkList space, int i)
{
    //删除当前指针之后的节点
    if(i < 1 || i > MAXSIZE-1) return ERROR;  //i不合法
    int k = space[i].cur;
    if(!k) return ERROR;  //当前指针之后没有节点
    space[i].cur = space[k].cur;
    Free_SL(space, k);
    return OK;
}//DelAfter_SL

void MergeList_SL(SLinkList space, int a, int b, int c, int (*compare)(ElemType, ElemType))
{
    //在La和Lb有序的前提下，合并出Lc
    int pa = space[a].cur, pb = space[b].cur, pc = c;
    while(pa && pb)
        if(compare(space[pa].data, space[pb].data) <= 0)
        {
            space[pc].cur = pa;
            pc = pa;
            pa = space[pa].cur;
        }
        else
        {
            space[pc].cur = pb;
            pc = pb;
            pb = space[pb].cur;
        }
    if(pa)
        space[pc].cur = pa;
    if(pb)
        space[pc].cur = pb;
}//MergeList_SL

void Difference_SL(SLinkList space, int a, int b, int c)
{
    //在c中建立(a-b)∪(b-a)
    int pb = space[b].cur, tmp;
    int *pa;
    *pa = a;
    while(pb)
    {
        if(LocateElem_SL(space, pa, spcae[pb].data, compare) == ERROR)  //该元素不在a中，插入
        {
            tmp = space[pb].cur;
            space[pb].cur = space[a].cur;
            space[a].cur = pb;
            pb = tmp;
        }
        else  //该元素在a中，删除
        {
            *pa = Prior_SL(space, a, *pa);
            DelAfter_SL(space, *pa);
        }
        pb = space[pb].cur;
    }
}//Difference_SL

int compare(ElemType a, ElemType b)
{
    //元素比较函数， 返回a-b
    return a-b;
}//compare

//-----------------------------

int main()
{
    int head;
    SLinkList test;
    InitList_SL(test);
    head = CreateList(test, 10);
    PrintList_SL(test, head);
    return 0;
}
