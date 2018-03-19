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
// int Next_SL(SLinkList space, int head, int i)
//     //改变当前指针指向其后继，错误则返回0
// Status ListTraverse_SL(SLinkList space, int head, Status (*visit)(ElemType*))
//     //对每个元素调用函数visit,一旦visit()失败，则操作失败
// Status LocateElem_SL(SLinkList *space, ElemType e, int(*compare)(ElemType, ElemType))
//     //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
// ElemType GetCurElem_SL(SLinkList space, int i)
//     //返回当前指针所指数据元素
// Status SetCurElem_SL(SLinkList space, int i, ElemType e)
//     //更新当前指针所指数据元素
// Status Append_SL(SLinkList space, int head, SLinkList s)
//     //s指向的一串节点连接在最后一个节点之后
// Status InsAfter_SL(SLinkList space, int i)
//     //将元素e插入在当前指针之后
// Status DelAfter_SL(SLinkList space, int i)
//     //删除当前指针之后的节点
// void MergeList_SL(SLinkList spacea, SLinkList spaceb, SLinkList spacec, int (*compare)(ElemType, ElemType))
//     //在La和Lb有序的前提下，合并出Lc
// void Difference_SL(SLinkList space, int s)
//     //见教材算法2.16
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