//DOUBLE_LINKED_LIST
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
typedef int ElemType;        //双向链表存储的数据类型
struct DuLNode{
    ElemType        data;    //数据域
    struct DuLNode  *prior;  //指针域，指向上一个节点
    struct DuLNode  *next;   //指针域，指向下一个节点
};
typedef struct DuLNode DuLNode;
typedef struct DuLNode *DuLList;
//-----------------------------

//---------|FuncList|----------
    Status InitList_DuL(DuLList *L);
    //构造一个空的双向链表
    Status DstroyList_DuL(DuLList *L);
    //销毁双向链表L
    Status ClearList_DuL(DuLList L);
    //重置为空表
    Status ListEmpty_DuL(DuLList L);
    //双向链表判空
    int ListLength_DuL(DuLList L);
    //求双向链表长度，复杂度取决于链表长度
    Status Locatepos_DuL(DuLList L, int i, ElemType *e);
    //用e返回链表第i个节点的元素值，其中L为表头指针
    Status Prior_DuL(DuLList *L);
    //改变当前指针指向其前驱
    Status Next_DuL(DuLList *L);
    //改变当前指针指向其后继
    Status ListTraverse_DuL(DuLList L, Status (*visit)(ElemType*));
    //对L中每个元素调用函数visit,一旦visit()失败，则操作失败
    Status LocateElem_DuL(DuLList *L, ElemType e, Status(*compare)(ElemType, ElemType));
    //若存在与e满足函数compare()判定关系的元素，则移动当前指针指向第一个满足条件的元素，并返回OK，否则返回ERROR
    ElemType GetCurElem_DuL(DuLList L);
    //返回当前指针所指数据元素
    Status SetCurElem_DuL(DuLList L, ElemType e);
    //更新当前指针所指数据元素
    Status Append_DuL(DuLList L, DuLList s);
    //s指向的一串节点连接在最后一个节点之后
    Status InsAfter_DuL(DuLList L, ElemType e);
    //将元素e插入在当前指针之后
    Status DelAfter_DuL(DuLList L, ElemType *e);
    //删除当前指针之后的节点
    Status MergeList_DuL(DuLList La, DuLList Lb, DuLList *Lc, int (*compare)(ElemType, ElemType));
    //在La和Lb有序的前提下，合并出Lc

    int compare(ElemType a, ElemType b);
    //测试用函数，元素比较函数， a<=b返回1 a>b返回0
    Status CreatList_DuL(DuLList *L, int n);
    //测试用函数，建立n个元素的双向链表(顺序输入)
    void PrintList_DuL(DuLList L);
    //测试用函数，从头结点开始，依次输出以后所有结点值，再反序输出一次

//-----------------------------

Status InitList_DuL(DuLList *L){
    *L = (DuLList)malloc(sizeof(DuLNode));
    if (!*L) return OVERFLOW;
    (*L)->prior = (*L)->next = NULL;
    return OK;
}//InitList_DuL

Status DstroyList_DuL(DuLList *L)//todo
{
    //销毁双向链表L
    DuLList p = *L;

    if (p == NULL)
        return ERROR;    //已是空表

    while(p)
    {
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }
    return OK;
}//DstroyList_DuL

Status ClearList_DuL(DuLList L)
{
    //重置为空表

    if (L == NULL)
        return ERROR;

    DuLList pre, p;

    pre = L->next;
    while(pre)
    {
        p = pre->next;
        free(pre);
        pre = p;
    }
    L->next = NULL;
    L->data = 0;
    return OK;
}//ClearList_DuL

Status ListEmpty_DuL(DuLList L)
{
    //双向链表判空
    if (L == NULL)
        return ERROR;

    if( (L->next) == NULL && (L->prior) == NULL )
        return TRUE;
    else
        return FALSE;
}//ListEmpty_DuL

int ListLength_DuL(DuLList L)
{
    //求双向链表长度，复杂度取决于链表长度
    if (L == NULL)
        return -1;

    int n = 0;
    DuLList p;
    p = L->next;
    while(p)
    {
        ++n;
        p = p->next;
    }
    return n;
}//ListLength_DuL


ElemType GetCurElem_DuL(DuLList L)
{
    //返回当前指针所指数据元素
    return L->data;
}//GetCurElem_DuL

Status SetCurElem_DuL(DuLList L, ElemType e)
{
    //更新当前指针所指数据元素
    if(L == NULL || L->prior == NULL) return ERROR; //L是头结点
    L->data = e;
    return OK;
}//SetCurElem_DuL

Status Append_DuL(DuLList L, DuLList s)
{
    if (L == NULL || s == NULL) return ERROR;
    //s指向的一串节点连接在最后一个节点之后
    while(L->next) //让L指向尾节点
        L = L->next;
    L->next = s->next;
    if (L->next)
        L->next->prior = L;
    return OK;
}//Append_DuL




Status Prior_DuL(DuLList *L){
    if ((*L) == NULL)
        return ERROR;

    if((*L)->prior)
    {
        (*L)=(*L)->prior;
        return OK;
    }
    else
        return ERROR;
}//Prior_DuL

Status Next_DuL(DuLList *L){
    if ((*L) == NULL)
        return ERROR;

    if((*L)->next)
    {
        (*L)=(*L)->next;
        return OK;
    }
    else
        return ERROR;
}//Next_DuL

Status ListTraverse_DuL(DuLList L, Status (*visit)(ElemType*)){
    //L为头指针

    if (L == NULL)
        return ERROR;

    DuLList p=L->next;
    while(p)
    {
        if(visit(&p->data) == ERROR)
            return ERROR;
        p = p->next;
    }
    return OK;
}//ListTraverse_DuL

Status visit(ElemType *a){
    if(a)
    {
        *a = 50;
        return OK;
    }
    else
        return ERROR;
}//visit

Status LocateElem_DuL(DuLList *L, ElemType e, Status(*compare)(ElemType, ElemType)){
    if ((*L) == NULL)
        return ERROR;


    DuLList p = (*L)->next;
    while(p)
    {
        if(!compare(p->data,e))
        {
            (*L)=p;
            return OK;
        }
        p=p->next;
    }
    return ERROR;
}//LocateElem_DuL;

Status InsAfter_DuL(DuLList L, ElemType e){
    if (L == NULL)
        return ERROR;

    DuLList p;
    if(((p = (DuLList)malloc(sizeof(DuLNode)))==NULL)) return OVERFLOW;
    p->data = e;
    p->prior = L;
    p->next = L->next;
    L->next = p;
    if(p->next)
        p->next->prior = p;
    return OK;
}//InsAfter_DuL

Status DelAfter_DuL(DuLList L, ElemType *e){
    if(L == NULL || L->next == NULL) return ERROR;
    *e = L->next->data;
    if(L->next->next == NULL){
        free(L->next);
        L->next = NULL;
        return OK;
    }
    L->next = L->next->next;
    free(L->next->prior);
    L->next->prior = L;
    return OK;
}//DelAfter_DuL

Status MergeList_DuL(DuLList La, DuLList Lb, DuLList *Lc, int(*compare)(ElemType, ElemType)){

    if (La == NULL || Lb == NULL) return ERROR;

    if (InitList_DuL(Lc) == OVERFLOW) return OVERFLOW;

    DuLList pa,pb,pc;
    ElemType a,b;
    pa = La->next, pb = Lb->next, pc = *Lc;
    while((pa != NULL)&&(pb != NULL)){
        a = pa->data, b = pb->data;
        if(compare(a,b)<=0){
            InsAfter_DuL(pc, a);
            pa = pa->next;
            pc = pc->next;
        }
        else{
            InsAfter_DuL(pc, b);
            pb = pb->next;
            pc = pc->next;
        }
    }
    if(pb){
        pc->next = pb;
        pb->prior = pc;
    }
    if(pa){
        pc->next = pa;
        pa->prior = pc;
    }
    return OK;
}


//测试用函数
Status CreatList_DuL(DuLList *L, int n){
    DuLList p;
    if (InitList_DuL(L) == OVERFLOW)
        return OVERFLOW;
    DuLList tempL = *L;
    tempL -> prior = tempL -> next = NULL;

    int i;
    for (i = 0; i < n; i++){
        p = (DuLList)malloc(sizeof(DuLNode));
        if (!p) return(OVERFLOW);
        scanf("%d", &p->data);
        tempL->next = p;
        p->prior = tempL;
        tempL = p;
    }
    return OK;
}//CreatList_DuL

int compare(ElemType a, ElemType b){
    return a-b;
}//compare

void PrintList_DuL(DuLList L){
    if (L == NULL)
    {
        printf("NULL\n");
        return;
    }
    while(L->next != NULL){
        L = L->next;
        printf("%10d",L->data);
    }
    printf("\n");
    while(L->prior != NULL){
        printf("%10d",L->data);
        L = L->prior;
    }
}//PrintList_DuL

int main()
{
    DuLList L;
    //CreatList_DuL(&L, 5);
    //PrintList_DuL(L);
    return 0;
}
