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
typedef int ElemType;         //单链表存储的数据类型
struct LNode{
    ElemType     data;        //数据域
    struct LNode *next;       //指针域，指向下一个节点
};
typedef struct LNode *LinkList;
//-----------------------------

Status CreatList_L(LinkList L, int n)
{
    //逆位序输入n个元素的值，建立带表头节点的单链线性表L
    int i; LinkList p;
    L = (LinkList)malloc(sizeof(struct LNode));
    if(!L) exit(OVERFLOW);
    L->next = NULL;                                 //先建立一个带头结点的单链表
    for(i = n; i > 0; i--)
    {
        p = (LinkList)malloc(sizeof(struct LNode)); //生成新结点
        if(!p) exit(OVERFLOW);
        scanf("%d", &p->data);                      //输入元素值 issue:未考虑ElemType
        p->next = L->next;                          //插入到表头
        L->next = p;
    }
    return OK;
}//ClearList_L

Status InitList_L(LinkList L)
{
    //构造一个空的线性表L
    L = (LinkList)malloc(sizeof(struct LNode));
    if(!L) exit(OVERFLOW);
    L->next = NULL;
    return OK;
}//InitList_L

// Status DestroyList_L(struct SqList L)
// {
//     //销毁线性表L
// }//DestroyList_L

// void ClearList_L(LinkList L)
// {
//     //将L重置为空表
// }//ClearList_Sq

Status ListEmpty_L(LinkList L)
{
    //判断L是否为空表
    if(!L)
        return TRUE;
    else FALSE;
}//ListEmpty_L

int ListLength_L(LinkList L)
{
    //返回L中数据元素的个数
    LinkList p; int i;
    p = L; i = 0;
    while(p)
    {
        p = p->next;
        i++;
    }
    return i;
}//ListLength_L

Status GetElem_L(LinkList L, int i, ElemType *e)
{
    //用e返回L中第i个数据元素的值
    //L为带头结点的单链表的头指针
    //当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    int j; LinkList p;
    p = L->next; j = 1;         //初始化，p指向第一个节点，j为计数器
    while(p && j < i)           //顺指针向后查找，直到p指向第i个元素或p为空
    {
        p = p->next;
        j++;
    }
    if(!p || j>i) return ERROR; //第i个元素不存在
    *e = p->data;                //取第i个元素
    return OK;
}//GetElem_L

int compare(ElemType a, ElemType b)
{
    //元素的比较函数
    return a-b;
}

// int LocateElem_L(struct SqList L, ElemType e, int (*compare)(ElemType, ElemType))
// {
//     //在顺序线性表L中查找第1个值与e满足compare()的元素的位序
//     //若找到，则返回其在L中的位序，否则返回0
// }//LocateElem.L

// Status PriorElem_L(struct SqList L, ElemType cur_e, ElemType *pre_e)
// {
//     //返回cur_e的前驱节点pre_e
// }//PriorElem_L

// Status NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e)
// {
//     //返回cur_e的后继节点next_e
// }//NextElem_L

Status ListInsert_L(LinkList L, int i, ElemType e)
{
    //在带头结点的单链线性表L中第i个位置之前插入元素e
    int j; LinkList p, s;
    p = L; j = 0;
    while(p && j < i-1)                  //寻找第i-1个节点
    {
        p = p->next;
        j++;
    }
    if(!p || j > i-1) return ERROR;      //i小于1或者大于表长+1
    s = (LinkList)malloc(sizeof(struct LNode)); //生成新节点
    s->data = e;
    s->next = p->next;                   //插入L中
    p->next = s;
    return OK;
}//ListInsert_L

Status ListDelete_L(LinkList L, int i, ElemType *e)
{
    //在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
    //i的合法值为1<=i<=ListLength_Sq(L)
    int j; LinkList p, q;
    p = L; j = 0;
    while(p->next && j < i-1)               //寻找第i个节点，并令p指向其前趋
    {
        p = p->next;
        j++;
    }
    if(!(p->next) || j > i-1) return ERROR; //删除位置不合理
    q = p->next;                            //删除并释放节点
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}//ListDelete_L

void MergeList_L(LinkList La, LinkList Lb, LinkList Lc, int (*compare)(ElemType, ElemType))
{
    //已知单链线性表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
    LinkList pa, pb, pc;
    pa = La->next; pb = Lb->next; pc = La;
    Lc = La;                        //用La的头结点作为Lc的头结点
    while(pa && pb)
    {
        if(compare(pa->data, pb->data) < 0)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        pc->next = pa ? pa : pb;
        free(Lb);
    }
}//MergeList_L

// Status ListTraverse_L(struct SqList L, Status (*visit)(ElemType*))
// {
// }//ListTraverse_L

int main()
{
    return 0;
}