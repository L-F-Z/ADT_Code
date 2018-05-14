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
#define STACK_INIT_SIZE 100; //存储空间初始分配量
#define STACKINCREMENT 10; //存储空间分配增量
typedef int ElemType;
typedef struct{
    SElemType *base; //在栈构造之前和销毁之后，base的值为NULL
    SElemType *top; //栈顶指针
    int stacksize; //当前已分配的存储空间，以元素为单位
}SqStack;
//-----------------------------

//---------|FuncList|----------
//Status InitStack (SqStack &S);
    //构造一个空栈S
//Status DestroyStack (SqStack &S);
    //销毁栈S,S不再存在
//Status ClearStack (SqStack &S);
    //把S置为空栈
//Status StackEmpty (SqStack S);
    //若栈S为空栈，则返回 TRUE，否则返回 FALSE
//int StackLength (SqStack S);
    //返回S的元素个数，即栈的长度
//Status GetTop (SqStack S, SElemType &e);
    //若栈不空，则用 e 返回 S 的栈顶元素，并返回 OK; 否则返回 ERROR
//Status Push (SqStack &S, SElemType e);
    //插入元素 e 为新的栈顶元素
//Status Pop (SqStack &S, SElemType &e);
    //若栈不空，则删除 S 的栈顶元素，用 e 返回其值，并返回 OK; 否则返回 ERROR
//Status StackTraverse(SqStack S, Status (*visit)());
    //从栈底到栈顶依次对栈中每个元素调用函数 visit ()。一旦visit ()失败，则操作失败

Status InitStack (SqStack &S) 
{
    //构造一个空栈S
    S.base = (SElemType *)malloc(STACK_INIT_SISE * sizeof(SElemType));
    if (!S.base) exit(OVERFLOW);    //存储分配失败
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}// InitStack

Status GetTop(SqStack S, SElemType &e)
{
    //若栈不空，则用 e 返回 S 的栈顶元素，并返回 OK；否则返回　ERROR
    if (S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}// GetTop

Status Push (SqStack S, SElemType &e)
{
    //插入元素 e 为新的栈顶元素
    if (S.top - S.base >= S.stacksize)
    {
        //栈满，追加存储空间
        S.base = (SElemType *) realloc (s.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (! S.base) exit(OVERFLOW); //存储分配失败

        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }

    * S.top ++ = e;
    return OK;
} //Push

Status Pop (SqStack &S, SElemType &e)
{
    //若栈不空，则删除S的栈顶元素，用 e 返回其值，并返回 OK;否则返回 ERROR
    if (S.top == S.base) return ERROR;
    e = * --S.top;
    return OK;
}//Pop


//-----------------------------------------
