#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define CIRCULAR_LINKED_LIST_C

//----------|Status|-----------
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//-----------------------------
//---------|Typedef|-----------
typedef int ElemType; //单链表存储的数据类型
struct LNode_C
{
    ElemType data;        //数据域
    struct LNode_C *next; //指针域，指向下一个节点
};
typedef struct LNode_C *Position; //单链表节点存储的位置
typedef struct LNode_C *LinkList_C;
//-----------------------------
//定义的新的变量类型首字母大写----------------------

//---------|FuncList|----------
Status InitList_C(LinkList_C *L);
//构造一个空的循环链表L
Status DestroyList_C(LinkList_C L);
//销毁循环链表L
void ClearList_C(LinkList_C L);
//将L重置为空表
Status ListEmpty_C(LinkList_C L);
//判断L是否为空表
int ListLength_C(LinkList_C L);
//返回L中数据元素的个数
Status GetElem_C(LinkList_C L, int, ElemType *);
//用e返回L中第i个数据元素的值
int compare(ElemType, ElemType);
//元素的比较函数
int LocateElem_C(LinkList_C L, ElemType, int (*compare)(ElemType, ElemType));
//在循环链表L中查找第1个值与e满足compare()的元素的位序
Status PriorElem_C(LinkList_C L, ElemType, ElemType *);
//返回cur_e的前驱节点pre_e
Status NextElem_C(LinkList_C L, ElemType, ElemType *);
//返回cur_e的后继节点next_e
Status ListInsert_C(LinkList_C L, int, ElemType);
//在循环链表L中第i个位置之前插入新的元素e
Status ListDelete_C(LinkList_C L, int, ElemType *);
//在循环链表L中删除第i个元素，并用e返回其值
void MergeList_C(LinkList_C L, LinkList_C Y, LinkList_C B, int (*compare)(ElemType, ElemType));
//已知循环链表La和Lb的元素按值非递减排列
Status ListTraverse_C(LinkList_C L, Status (*visit)(ElemType *));
//依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintList_C(LinkList_C L);
//打印循环链表L
//-----------------------------

//循环链表定义: 若首节点.next==0则为空节点, 否则此节点中有元素存在.

//-----------------------------
Status InitList_C(LinkList_C *L) //2.3
{
    //输入参数是一个LinkList_C类型的变量L
    //函数把L初始化成一个循环链表
    *L = (LinkList_C)malloc(sizeof(struct LNode_C));
    if (!*L)
        exit(OVERFLOW);
    (*L)->next = 0;
    return OK;
} //构造一个空的循环链表L

Status DestroyList_C(LinkList_C L)
{
    //输入参数是一个LinkList类型的变量L
    //函数将整个循环链表都free掉
    LinkList_C temp, temp1, initial;
    if (!L)
        exit(OVERFLOW);
    initial = L;
    if (L->next == 0)
        free(L);
    for (temp = L->next; temp != initial;)
    {
        if (!temp)
            exit(OVERFLOW);
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    free(L);
    L = NULL;
    return OK;
} //销毁循环链表L

void ClearList_C(LinkList_C L)
{
    //删除所有元素, 保留循环链表的空表头
    LinkList_C temp, temp1, initial;
    if (!L)
        exit(OVERFLOW);
    initial = L;
    for (temp = L->next; temp != initial;)
    {
        if (!temp)
            exit(OVERFLOW);
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    L->next = 0;
    return;
} //将L重置为空表

Status ListEmpty_C(LinkList_C L)
{
    //输入一个LinkList类型的L，判断其是否是空串（NULL）
    if (!L || L->next == 0)
        return TRUE;
    else
        return FALSE;
} //判断L是否为空表

int ListLength_C(LinkList_C L)
{
    //输入是一个LinkList类型的变量L
    //输出是一个int整数，为链表的元素个数
    int i;
    LinkList_C temp = L->next;
    if (!L)
        exit(OVERFLOW);
    if (!L->next)
        return 0;
    for (i = 1; temp != L; i++)
        temp = temp->next;
    return i;
} //返回L中数据元素的个数

Status GetElem_C(LinkList_C L, int i, ElemType *e)
{
    //有三个参数，第一个参数是链表L，第二个参数是元素序数，记得是从1开始数的，如果i大于链表长度就会报错
    //第三个参数e是用来放第i个元素的值的
    int j;
    int n;
    LinkList_C p = L;
    if (!L)
        exit(OVERFLOW);
    if (ListEmpty_C(L))
        return ERROR;
    n = ListLength_C(L);
    for (j = 1; j != i && j != n; j++)
        p = p->next;
    if (i = !j)
        return ERROR;
    else
    {
        *e = p->data;
        return OK;
    }

} //用e返回L中第i个数据元素的值

int compare(ElemType a, ElemType b)
{
    //两个参数都是元素类型，如果a大于b就输出1，等于输出0，小于输出-1
    if (a == b)
        return 0;
    else if (a > b)
        return 1;
    else
        return -1;
} //元素的比较函数

int LocateElem_C(LinkList_C L, ElemType e, int (*compare)(ElemType, ElemType))
{
    //输入参数是一个循环链表L，一个用来比较的元素e，和用来比较的函数指针
    //返回值是一个int型的整数，是第一个满足和compare满足关系的元素序号
    int i;
    int n;
    LinkList_C p = L;
    if (ListEmpty_C(L))
        return ERROR;
    n = ListLength_C(L);
    for (i = 1; compare(L->data, e) && i != n; i++, p = p->next)
        ;
    if (i == n)
        return ERROR;
    else
        return i;
} //在循环链循环链表L中查找第1个值与e满足compare()的元素的位序

Status PriorElem_C(LinkList_C L, ElemType cur_e, ElemType *pre_e)
{
    //三个参数第一个是循环链表L，第二个是用来比较的cur_e，第三个用来返回值
    //返回前驱结点
    int i, n;
    LinkList_C temp, p;
    n = ListLength_C(L);
    p = L;
    if (ListEmpty_C(L))
        return ERROR;
    for (i = 0, temp = L; p->data != cur_e && i != n; i++, p = p->next)
        temp = p;
    if (i == n && p->data != cur_e)
        return ERROR;
    else
    {
        *pre_e = temp->data;
        return OK;
    }
}
//返回cur_e的前驱节点pre_e

Status NextElem_C(LinkList_C L, ElemType cur_e, ElemType *next_e)
{
    //三个参数第一个是循环链表L，第二个是用来比较的cur_e，第三个用来返回值
    //返回后继结点
    int i, n;
    LinkList_C temp, p;
    if (ListEmpty_C(L))
        return ERROR;
    n = ListLength_C(L);
    p = L;
    for (i = 0, temp = L; p->data != cur_e && i != n; i++, p = p->next)
        temp = p;
    if (i == n && p->data != cur_e)
        return ERROR;
    else
    {
        *next_e = temp->data;
        return OK;
    }
}
//返回cur_e的后继节点next_e

Status ListInsert_C(LinkList_C L, int i, ElemType e)
{
    //在循环链表L中第i个位置之前插入新的元素e
    int j, n;
    LinkList_C p, temp, temp1;
    if (ListEmpty_C(L))
        return ERROR;
    n = ListLength_C(L);
    p = L;
    if (i > n)
        return ERROR;
    else if (i = 1)
    {
        for (j = 1; j != n; j++)
            p = p->next;
        temp = (LinkList_C)malloc(sizeof(struct LNode_C));
        p->next = temp;
        temp->data = e;
        temp->next = L;
        return OK;
    }
    else
    {
        for (j = 1; j != i; j++, p = p->next)
            temp = p;
        temp1 = (LinkList_C)malloc(sizeof(struct LNode_C));
        temp->next = temp1;
        temp1->data = e;
        temp1->next = p;
        return OK;
    }
}
//在循环链表L中第i个位置之前插入新的元素e

Status ListDelete_C(LinkList_C L, int i, ElemType *e)
{
    //在循环表L中删除第i个元素，并用e返回其值
    int j, n;
    LinkList_C p, temp;
    if (ListEmpty_C(L))
        return ERROR;
    n = ListLength_C(L);
    if(n==1)
        L->next = 0;
    p = L;
    if (i > n)
        return ERROR;
    else if (i = 1)
    {
        for (j = 1; j != n; i++)
            p = p->next;
        p->next = L->next;
        *e = L->data;
        free(L);
        L = p->next;
        return OK;
    }
    else
    {
        for (j = 1; j != i; i++, p = p->next)
            temp = p;
        temp->next = p->next;
        *e = p->data;
        free(p);
        return OK;
    }
}
//在循环表L中删除第i个元素，并用e返回其值

Status CreatList_C(LinkList_C *L, int n) //函数返回Status类型
{
    //逆位序输入n个元素的值，建立带表头节点的单链线性表L
    //函数体首行写函数功能
    //注释对齐, 见下方注释
    //建议考虑一下复杂度和函数用时, 比如malloc操作就很费时间
    InitList_C(L);
    int i = 0;
    while (i++ < n)
    {
        ElemType a;
        scanf("%d", &a);
        ListInsert_C(*L, 1, a);
    }
} //ClearList_C

void MergeList_C(LinkList_C La, LinkList_C Lb, LinkList_C Lc, int (*compare)(ElemType, ElemType))
{
    //已知单循环链表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的单循环链表Lc，Lc的元素也按值非递减排列

    if (ListEmpty_C(La))
    {
        Lc = La;
        return;
    }

    if (ListEmpty_C(Lb))
    {
        Lc = Lb;
        return;
    }
    LinkList_C pa, pb, pc;
    pa = La->next;
    pb = Lb->next;
    pc = La;
    Lc = La; //用La的头结点作为Lc的头结点

    while (pa != La && pb != Lb)
    {
        if (compare(pa->data, pb->data) < 0)
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
    }

    while (pa != La || pb != Lb)
        pc->next = (pa != La) ? pa : pb;

    pc->next = Lc;

    free(Lb);
    // return Lc;
} //MergeList_C

Status ListTraverse_C(LinkList_C L, Status (*visit)(ElemType *))
{
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    LinkList_C p;
    p = L->next;
    if (ListEmpty_C(L))
        return ERROR;
    while (p != L && visit(&p->data) == OK)
        p = p->next;
    if (p == L)
        return OK;
    else
        return ERROR;
} //ListTraverse_C

Status PrintList_C(LinkList_C L)
{
    //打印单循环链表L
    LinkList_C p;
    p = L->next;
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
} //PrintList_C

#include "lazy.h"
int main()
{

    LinkList_C L;
    CreatList_C(&L, 3);
    int a;
    ListInsert_C(L, 2, 33);
    GetElem_C(L, 2, &a);
    CK(a);
    ListDelete_C(L, 1, &a);
    CK(a);
    LinkList_C LL;
    CreatList_C(&LL, 2);
    LinkList_C LLL;
    MergeList_C(L, LL, LLL, compare);
    LinkList_C Q;
    InitList_C(&Q);
    PrintList_C(Q);
    DestroyList_C(L);
    ClearList_C(Q);

    a = ListEmpty_C(Q);
    CK(a);
    ListLength_C(LL);
    CK(LocateElem_C(LL, 1, compare));

    PriorElem_C(LL, 1, &a);
    NextElem_C(LL, 1, &a);
    Status mprint(int *t)
    {
        printf("%d ", *t);
    }
    ListTraverse_C(LL, mprint);
    return 0;
}

//完整版函数

// //---------|FuncList|----------
// //这里实现的是带头结点的线性链表, 这是完整的函数列表
// Status CreatList_C(LinkList_C L, int n);
// //逆位序输入n个元素的值，建立带表头节点的单链线性表L
// Status InitList_C(LinkList_C L);
// //构造一个空的线性链表
// Status DestroyList_C(LinkList_C L);
// //销毁线性链表L, L不再存在
// Status ClearList_C(LinkList_C L);
// //将线性链表置为空表并释放原链表的节点空间
// Status InsFirst_C(LinkList_C h,LinkList_C s);
// //已知h指向线性链表的头节点, 将s所指的节点插入到第一个节点之前
// Status DelFirst_C(LinkList_C h,LinkList_C q);
// //已知h指向线性链表的头节点, 删除链表中的第一个节点并以q返回
// Status Append_C(LinkList_C L,LinkList_C s);
// //将指针s所指的(彼此以指针相连的)一串节点连接在线性链表后的最后一个节点, 并改变链表L的尾指针指向新的尾节点.
// Status Remove_C(LinkList_C L, LinkList_C q);
// //删除线性链表L的尾节点并以q返回, 改变链表L的尾指针指向新的尾节点
// Status InsBefore_C(LinkList_C L, LinkList_C p, LinkList_C s);
// //已知p指向线性链表L中的一个节点, 将s插入到p所指的节点之前, 并修改指针p指向新插入的节点
// Status InsAfter_C(LinkList_C L, LinkList_C p, LinkList_C s);
// //已知p指向线性链表L中的一个节点, 将s插入到p所指的节点之后, 并修改指针p指向新插入的节点
// Status SetCurElem_C(LinkList_C p, ElemType e);
// //p指向线性链表中的一个节点, 用e更新其中数据元素的值
// ElemType GetCurElem_C(LinkList_C p);
// //p指向线性链表中的一个节点, 返回其中数据元素的值
// Status ListEmpty_C(LinkList_C L);
// //若线性链表L为空表返回TRUE, FALSE
// int ListLength_C(LinkList_C L);
// //返回线性链表L中元素个数
// Position GetHead_C(LinkList_C L);
// //返回线性链表L中头结点的位置
// Position GetLast_C(LinkList_C L);
// //返回线性链表L中最后一个结点的位置
// Position PriorPos_C(LinkList_C L, LinkList_C p);
// //已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，
// //若无前驱，则返回NULL
// Position NextPos_C(LinkList_C L, LinkList_C p);
// //已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，
// //若无后继，则返回NULL
// Status LocatePos_C(LinkList_C L, int i, LinkList_C p);
// //返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法时返回ERROR
// Position LocateElem_C(LinkList_C L, ElemType e, Status(*compare)(ElemType, ElemType));
// //返回线性链表L中第一个与e满足函数compare（）判定关系的元素的位置，
// //若不存在这样的元素，则返回NULL
// Status ListTraverse_C(LinkList_C L, Status (*visit)());
// //依次对L的每个元素调用函数visit（）。一旦visit（）失败，则操作失败。
// Status MergeList_C(LinkList_C La, LinkList_C Lb, LinkList_C Lc, int (*compare)(ElemType, ElemType));
// //已知单链线性表La和Lb的元素按值非递减排列
// //归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列

//-----------------------------
