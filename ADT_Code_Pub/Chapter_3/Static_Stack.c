//STATIC_STACK
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
#define MAX_STACK_SIZE 100     //栈的存储空间大小
typedef int ElemType;          //栈存储的数据类型
struct SqStack{
    ElemType  stack_array[MAX_STACK_SIZE];          //在栈构造之前和销毁之后，base的值为NULL
    int top;                    //栈顶指针
};
//-----------------------------

//---------|FuncList|----------
Status InitStack(struct SqStack*);
    //初始化栈S
Status ClearStack(struct SqStack*);
    //把S重置为空栈
Status StackEmpty(struct SqStack*);
    //若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(struct SqStack*);
    //返回S的元素个数，即栈的长度
Status GetTop(struct SqStack*, ElemType*);
    //若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
Status Push(struct SqStack*, ElemType);
    //插入元素e为新的栈顶元素
Status Pop(struct SqStack*, ElemType*);
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status StackTraverse(struct SqStack*, Status (*visit)(ElemType*));
    //依次对S的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintStack(struct SqStack*);
    //打印栈S
//-----------------------------

int main()
{
    struct SqStack stack;
    InitStack(stack);
    return 0;
}

//-----------------------------
Status InitStack(struct SqStack *S)
{
    //初始化一个空栈S
    S->top = 0;
    return OK;
}//InitStack

Status ClearStack(struct SqStack *S)
{
    //把S重置为空栈
    S->top = 0;
    return OK;
}//ClearStack

Status StackEmpty(struct SqStack *S)
{
    //若栈S为空栈，则返回TRUE，否则返回FALSE
    if(S->top == 0)
        return TRUE;
    else return FALSE;
}//StackEmpty

int StackLength(struct SqStack *S)
{
    //返回S的元素个数，即栈的长度
    return (S->top);
}//ListLength_Sq

Status GetTop(struct SqStack *S, ElemType *e)
{
    //若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
    if(S->top == 0) return ERROR;
    *e = S->stack_array[S->top-1];
    return OK;
}//GetTop

Status Push(struct SqStack *S, ElemType e)
{
    //插入元素e为新的栈顶元素
    if(S->top == MAX_STACK_SIZE)//栈满
        return OVERFLOW;
    S->stack_array[S->top] = e;
    S->top ++;
    return OK;
}//Push

Status Pop(struct SqStack *S, ElemType *e)
{
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if(S->top == 0) return ERROR;
    S->top --;
    *e = S->stack_array[S->top];
    return OK;
}//Pop

Status StackTraverse(struct SqStack *S, Status (*visit)(ElemType*))
{
    //依次对S的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    int p = S->top;
    if(S->top == 0) return ERROR;
    while(p > 0 && visit(&(S->stack_array[p-1])) == OK)
        p--;
    if(p == 0) return OK;
    else return ERROR;
}//StackTraverse

Status PrintStack(struct SqStack *S)
{
    //打印栈S
    int i;
    if(S->top == 0)
    {
        printf("Error : EMPTY STACK\n");
        return ERROR;
    }
    printf("--TOP--\n");
    for(i = S->top; i > 0; i--)
        printf(" %d\n", S->stack_array[i - 1]); //Issue: ElemType?
    printf("--BASE--\n");
    if(S->top == 0) return OK;
    else return ERROR;
}//PrintStack
