#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SEQUENT_LIST_C

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
typedef struct LNode *Position;         //单链表节点存储的位置
typedef struct LNode *LinkList;
//-----------------------------
//定义的新的变量类型首字母大写


//---------|FuncList|----------
//这里实现的是带头结点的线性链表, 这是基本的函数列表

Status InitList_L(LinkList L);
    //构造一个空的顺序表L
Status DestroyList_L(LinkList L);
    //销毁顺序表L
void ClearList_L(LinkList L);
    //将L重置为空表
Status ListEmpty_L(LinkList L);
    //判断L是否为空表
int ListLength_L(LinkList L);
    //返回L中数据元素的个数
Status GetElem_L(LinkList L, int, ElemType*);
    //用e返回L中第i个数据元素的值
int compare(ElemType, ElemType);
    //元素的比较函数
int LocateElem_L(LinkList L, ElemType, int (*compare)(ElemType, ElemType));
    //在顺序顺序表L中查找第1个值与e满足compare()的元素的位序
Status PriorElem_L(LinkList L, ElemType, ElemType*);
    //返回cur_e的前驱节点pre_e
Status NextElem_L(LinkList L, ElemType, ElemType*);
    //返回cur_e的后继节点next_e
Status ListInsert_L(LinkList L, int, ElemType);
    //在顺序表L中第i个位置之前插入新的元素e
Status ListDelete_L(LinkList L, int, ElemType*);
    //在顺序表L中删除第i个元素，并用e返回其值
void MergeList_L(LinkList L, LinkList Y, LinkList B, int (*compare)(ElemType, ElemType));
    //已知顺序表La和Lb的元素按值非递减排列
Status ListTraverse_L(LinkList L, Status (*visit)(ElemType*));
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintList_L(LinkList L);
    //打印顺序表L
//-----------------------------

//有多余时间可以实现完整版函数

// //---------|FuncList|----------
// //这里实现的是带头结点的线性链表, 这是完整的函数列表
// Status CreatList_L(LinkList L, int n);
// //逆位序输入n个元素的值，建立带表头节点的单链线性表L
// Status InitList_L(LinkList L);
// //构造一个空的线性链表
// Status DestroyList_L(LinkList L);
// //销毁线性链表L, L不再存在
// Status ClearList_L(LinkList L);
// //将线性链表置为空表并释放原链表的节点空间
// Status InsFirst_L(LinkList h,LinkList s);
// //已知h指向线性链表的头节点, 将s所指的节点插入到第一个节点之前
// Status DelFirst_L(LinkList h,LinkList q);
// //已知h指向线性链表的头节点, 删除链表中的第一个节点并以q返回
// Status Append_L(LinkList L,LinkList s);
// //将指针s所指的(彼此以指针相连的)一串节点连接在线性链表后的最后一个节点, 并改变链表L的尾指针指向新的尾节点.
// Status Remove_L(LinkList L, LinkList q);
// //删除线性链表L的尾节点并以q返回, 改变链表L的尾指针指向新的尾节点
// Status InsBefore_L(LinkList L, LinkList p, LinkList s);
// //已知p指向线性链表L中的一个节点, 将s插入到p所指的节点之前, 并修改指针p指向新插入的节点
// Status InsAfter_L(LinkList L, LinkList p, LinkList s);
// //已知p指向线性链表L中的一个节点, 将s插入到p所指的节点之后, 并修改指针p指向新插入的节点
// Status SetCurElem_L(LinkList p, ElemType e);
// //p指向线性链表中的一个节点, 用e更新其中数据元素的值
// ElemType GetCurElem_L(LinkList p);
// //p指向线性链表中的一个节点, 返回其中数据元素的值
// Status ListEmpty_L(LinkList L);
// //若线性链表L为空表返回TRUE, FALSE
// int ListLength_L(LinkList L);
// //返回线性链表L中元素个数
// Position GetHead_L(LinkList L);
// //返回线性链表L中头结点的位置
// Position GetLast_L(LinkList L);
// //返回线性链表L中最后一个结点的位置
// Position PriorPos_L(LinkList L, LinkList p);
// //已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，
// //若无前驱，则返回NULL
// Position NextPos_L(LinkList L, LinkList p);
// //已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，
// //若无后继，则返回NULL
// Status LocatePos_L(LinkList L, int i, LinkList p);
// //返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法时返回ERROR
// Position LocateElem_L(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
// //返回线性链表L中第一个与e满足函数compare（）判定关系的元素的位置，
// //若不存在这样的元素，则返回NULL
// Status ListTraverse_L(LinkList L, Status (*visit)());
// //依次对L的每个元素调用函数visit（）。一旦visit（）失败，则操作失败。
// Status MergeList_L(LinkList La, LinkList Lb, LinkList Lc, int (*compare)(ElemType, ElemType));
// //已知单链线性表La和Lb的元素按值非递减排列
// //归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列

//-----------------------------

//函数示例
Status CreatList_L(LinkList L, int n) //函数返回Status类型
{
    //逆位序输入n个元素的值，建立带表头节点的单链线性表L
    //函数体首行写函数功能
    //注释对齐, 见下方注释
    //建议考虑一下复杂度和函数用时, 比如malloc操作就很费时间
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


int main()
{
    return 0;
}
