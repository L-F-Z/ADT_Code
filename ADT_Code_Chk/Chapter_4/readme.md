# 字符串分工

此部分使用分支`dev-wgroup`

## 分工及日程
Member/DDl|Mon|Tue|Wen|Thu|Fri|Sat|Sun
-|-|-|-|-|-|-|-
-|-|-|-|-|-|-|-
-|-|-|-|-|-|-|-
-|-|-|-|-|-|-|-


## 关键要求

1. ADT代码尽量使用C语言完成, 测试代码部分允许使用C++.
1. 在上传/提交代码前, 开发者应确保: 代码中没有语法检查工具可以直接检测出的错误, 代码中无依赖的部分可以正常被编译.
1. 开发者在上传代码前, 应自行构建单元测试(可以使用assert宏), 在提交时同时提交测试代码. 
1. 统一使用标准C库, 尽量避免使用VS等的第三方C库(比如, 使用`scanf_s`)
1. 提交的代码尽量使用`utf-8`进行编码, 项目提交时有条件者直接向小组分支dev-xgroup提交更改, 特殊情况可以将源代码直接提交小组负责人.


## 示例代码
```c
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

```