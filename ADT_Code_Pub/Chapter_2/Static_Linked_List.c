//STATIC_LINKED_LIST
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

//


//！！！！！本代码可能不稳定，请等待更新！！！！！


//

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
int Malloc_SL(SLinkList);
    //若备用空间链表非空，则返回分配的节点下标，否则返回0
int Free_SL(SLinkList, int);
    //将下标为k的空闲节点回收到备用链表
Status InitList_SL(SLinkList);
    //构造一个空的静态链表
int CreateList(SLinkList, int);
    //创建一个含有n个结点的静态链表，返回表头在存储数组的位置
Status ClearList_SL(SLinkList);
    //重置为空表
Status ListEmpty_SL(SLinkList, int);
    //静态链表判空
int ListLength_SL(SLinkList, int);
    //求静态链表长度
Status Locatepos_SL(SLinkList, int, int, ElemType*);
    //用e返回链表第i个节点的元素值，其中head为表头指针
int Prior_SL(SLinkList, int, int, ElemType*);
    //改变当前指针指向其前驱，错误则返回0
int Next_SL(SLinkList, int, int, ElemType*);
    //改变当前指针指向其后继，错误则返回0
Status ListTraverse_SL(SLinkList, int, Status (*visit)(ElemType*));
    //对每个元素调用函数visit,一旦visit()失败，则操作失败
Status LocateElem_SL(SLinkList, int, ElemType, int(*compare)(ElemType, ElemType));
    //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
ElemType GetCurElem_SL(SLinkList, int, int, ElemType*);
    //返回当前指针所指数据元素
Status SetCurElem_SL(SLinkList, int, ElemType);
    //更新当前指针所指数据元素
Status Append_SL(SLinkList, int, int);
    //s指向的一串节点连接在最后一个节点之后
Status InsAfter_SL(SLinkList, int, int, ElemType);
    //将元素e插入在当前指针之后
Status DelAfter_SL(SLinkList, int, int, ElemType*);
    //删除当前指针之后的节点
void MergeList_SL(SLinkList, int, int, int, int (*compare)(ElemType, ElemType));
    //在La和Lb有序的前提下，合并出Lc
void Difference_SL(SLinkList, int*);
    //在c中建立(a-b)∪(b-a)
int compare(ElemType, ElemType);
    //元素比较函数， 返回a-b
void PrintList_SL(SLinkList, int);
    //从头结点开始，依次输出以后所有结点值
Status GetIndex_SL(SLinkList,int,int ,int*);
    //获取第i个元素
//-----------------------------------------

int main()
{
    int head;
    SLinkList test;
    InitList_SL(test);
    head = CreateList(test, 10);
    PrintList_SL(test, head);
    return 0;
}

//------------------------------------------

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
        scanf("%d", &space[s].data);
        space[k].cur = s;
        k = s;
    }
    space[k].cur = 0;
    return head;
}

Status ClearList_SL(SLinkList space)
{
    //重置为空表
    if(!space[0].cur) return ERROR;//已是空表
    return InitList_SL(space);
}//ClearList_SL

Status ListEmpty_SL(SLinkList space, int head)
{
    //静态链表判空
    if(!space[head].cur)
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
    if((i < 1) || (i > ListLength_SL(space,head))) return ERROR; //i值不合法
    int k;
	if(!GetIndex_SL(space,head,i,&k))
	  return ERROR;
    *e = space[k].data;
    return OK;
}//Locatepos_SL

Status Prior_SL(SLinkList space, int head, int i,ElemType* e)
{
    //改变当前指针指向其前驱，错误则返回0
    if(i < 0 || i > MAXSIZE - 1) return 0; //i不合法
    int pr;
    int k = head;
    for(pr = 0; space[k].cur != i; )
    {
        pr = k;
        k = space[k].cur;
    }
	*e = space[k].data;
    return OK;
}//Prior_SL

Status Next_SL(SLinkList space, int head, int i,ElemType* e)
{
    //改变当前指针指向其后继，错误则返回0
	int k;
	if(!GetIndex_SL(space,head,i,&k))
	  return ERROR;
	k = space[k].cur;
	if(!k)
	  return ERROR;
	*e = space[k].data;
	return OK;
}//Next_SL

Status ListTraverse_SL(SLinkList space, int head, Status (*visit)(ElemType*))
{
    //对每个元素调用函数visit,一旦visit()失败，则操作失败
    int i,k = space[head].cur;
    for(i = 0; i < ListLength_SL(space,head) && visit(&space[k].data); i++, k = space[k].cur)
        ;
    if(i < ListLength_SL(space,head)) return ERROR;
    else return OK;
}//ListTraverse_SL

int LocateElem_SL(SLinkList space,int head, ElemType e, int(*compare)(ElemType, ElemType))
{
    //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
    int i,k;
    for(i = 1,k = space[head].cur; !compare(e,space[k].data)||!k; i++,k = space[k].cur)
        ;
    if(k)
        return i;
    else 
	  return 0;
}//LocateElem_SL

Status GetCurElem_SL(SLinkList space,int head, int i,ElemType* e)
{
    //返回当前指针所指数据元素
    if(i < 0 || i > MAXSIZE - 1) return ERROR; //i不合法
	int k;
	if(!GetIndex_SL(space,head,i,&k))return ERROR;
    *e = space[k].data;
	return OK;
}//GetCurElem_SL

Status SetCurElem_SL(SLinkList space, int i, ElemType e)
{
    //更新当前指针所指数据元素
    if(i < 0 || i > MAXSIZE - 1) return ERROR; //i不合法
    space[i].data = e;
    return OK;
}//SetCurElem_SL

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

Status InsAfter_SL(SLinkList space,int head ,int i, ElemType e)
{
    //将元素e插入在当前指针之后
    if(i < 1 || i > MAXSIZE-1) return ERROR;  //i不合法
	int tmp;
	if(!GetIndex_SL(space,head,i,&tmp))
	  return ERROR;
	i = tmp;
    int k = Malloc_SL(space);
    space[k].data = e;
    space[k].cur = space[i].cur;
    space[i].cur = k;
    return OK;
}//InsAfter_SL

Status DelAfter_SL(SLinkList space,int head, int i,ElemType* e)
{
    //删除当前指针之后的节点
    if(i < 1 || i > MAXSIZE-1) return ERROR;  //i不合法
	int k;
	if(!GetIndex_SL(space,head,i,&k))
	  return ERROR;
	i = k;
	k = space[i].cur;
	if(!k)return ERROR;
    space[i].cur = space[k].cur;
	*e = space[k].data;
    Free_SL(space, k);
    return OK;
}//DelAfter_SL

void MergeList_SL(SLinkList space, int a, int b, int c, int (*compare)(ElemType, ElemType))
{
    //在La和Lb有序的前提下，合并出Lc
    int pa = space[a].cur, pb = space[b].cur, pc = c;
    while(pa && pb)
        if(compare(space[pa].data, space[pb].data) < 0)
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

void Difference_SL(SLinkList space, int *s)
{
    //依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A)的静态链表，s为其头指针
    InitList_SL(space);
    *s = Malloc_SL(space);
    int r = *s;
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    //建立集合A的链表
    int i, j;
    for(j = 1; j <= m; ++j)
    {
        i = Malloc_SL(space);
        scanf("%d", &space[i].data);
        space[r].cur = i;
        r = i;
    }
    space[r].cur = 0;
    //依次输入集合B的元素，若在A中则删除，否则插入
    int b, p, k;
    for(j = 1; j <= n; ++j)
    {
        scanf("%d", &b);
        p = *s;
        k = space[*s].cur;
        while(k != space[r].cur && space[k].data != b)
            p = k, k = space[k].cur;
        if(k == space[r].cur)
        {
            i = Malloc_SL(space);
            space[i].data = b;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        }
        else
        {
            space[p].cur = space[k].cur;
            Free_SL(space, k);
            if(r == k) r = p; //删除的是r所指节点，需改变r
        }
    }
}//Difference_SL

int compare(ElemType a, ElemType b)
{
    //元素比较函数， 返回a-b
    return a-b;
}//compare

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
}//PrintList_SL

Status GetIndex_SL(SLinkList space,int head,int i,int* k)
{
    //获取第i个元素
	if(i<1 || i<MAXSIZE)return ERROR;
	int cnt = 0;
	for(*k = head; cnt < i; *k = space[*k].cur)
    {
		cnt++;
		if(space[*k].cur ==0 )
		  return ERROR;
	}
	return OK;
}//GetIndex_SL
