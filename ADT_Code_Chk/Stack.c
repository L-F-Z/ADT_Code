//STACK
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
#define STACK_INIT_SIZE 100    //栈的存储空间的初始分配量
#define STACKINCREMENT   10    //栈的存储空间的分配增量
typedef int SElemType;         //顺序表存储的数据类型
struct SqStack{
    SElemType  *base;          //在栈构造之前和销毁之后，base的值为NULL
    SElemType  *top;           //栈顶指针
    int        stacksize;      //当前已分配的储存容量(以sizeof(SElemType)为单位)
};
//-----------------------------

//---------|FuncList|----------
Status InitStack(struct SqStack*);
    //构造一个空栈S
Status DestroyStack(struct SqStack*);
    //销毁栈S,S不再存在
Status ClearStack(struct SqStack*);
    //把S重置为空栈
Status StackEmpty(struct SqStack*);
    //若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(struct SqStack*);
    //返回S的元素个数，即栈的长度
Status GetTop(struct SqStack*, SElemType*);
    //若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
Status Push(struct SqStack*, SElemType);
    //插入元素e为新的栈顶元素
Status Pop(struct SqStack*, SElemType*);
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status StackTraverse(struct SqStack*, Status (*visit)(SElemType*));
    //依次对S的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintStack(struct SqStack*);
    //打印栈S
//-----------------------------

//-----Private-Func-for-Testing------//
Status _sqr(SElemType *elem)
{
  *elem *= *elem;
  return TRUE;
}
//--End-of-Private-Func-for-Testing--//
int main()
{
//--------------Testing--------------//
    struct SqStack stack;
    SElemType temp_pop_elem;
    printf("****Start simple testing****：\n");
    printf("****************************\n");
    printf("InitStack     %d\n", InitStack(&stack));
    printf("GetTop %d     %d\n", temp_pop_elem, GetTop(&stack, &temp_pop_elem));
    printf("Is empty?     %d\n", StackEmpty(&stack));
    for(int i=-2;i<=2;i++)
      printf("Push %d       %d\n", i, Push(&stack, i));
    printf("PrintStack    %d\n", PrintStack(&stack));
    printf("Is empty?     %d\n", StackEmpty(&stack));
    printf("GetTop %d     %d\n", temp_pop_elem, GetTop(&stack, &temp_pop_elem));

    printf("\nIn-place square operation\n");
    printf("StackTraverse %d\n", StackTraverse(&stack, _sqr));
    printf("PrintStack    %d\n", PrintStack(&stack));

    printf("\nPop all         \n");
    while(Pop(&stack, &temp_pop_elem))
      printf("Pop out %d    \n", temp_pop_elem);

    printf("\nDestroyStack  %d\n", DestroyStack(&stack));
    printf("ClearStack      %d\n", ClearStack(&stack));
    printf("Is empty?     %d\n", StackEmpty(&stack));

    printf("\n\n***Start extreme testing****：\n");
    printf("****************************\n");
    printf("push -100~100 into stack,\n201 numbers in tatal\n");
    for(int i=-100;i<=100;i++)
      Push(&stack, i);
    printf("StackLength = %d\n", StackLength(&stack));
    printf("stacksize =   %d\n", stack.stacksize);


//--------The-End-of-Testing---------//
}


//-----------------------------
Status InitStack(struct SqStack *S)
{
    //构造一个空栈S
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}//InitStack

Status DestroyStack(struct SqStack *S)
{
    //销毁栈S,S不再存在
    if(!S->stacksize) return ERROR; //已经销毁
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stacksize = 0;
    return OK;
}//DestroyStack

Status ClearStack(struct SqStack *S)
{
    //把S重置为空栈
    if(S->top == S->base) return ERROR; //已是空栈
    S->top = S->base;
    return OK;
}//ClearStack

Status StackEmpty(struct SqStack *S)
{
    //若栈S为空栈，则返回TRUE，否则返回FALSE
    if(S->top == S->base)
        return TRUE;
    else return FALSE;
}//StackEmpty

int StackLength(struct SqStack *S)
{
    //返回S的元素个数，即栈的长度
    return (S->top - S->base);
}//ListLength_Sq

Status GetTop(struct SqStack *S, SElemType *e)
{
    //若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
    if(S->top == S->base) return ERROR;
    *e = *(S->top - 1);
    return OK;
}//GetTop

Status Push(struct SqStack *S, SElemType e)
{
    //插入元素e为新的栈顶元素
    if(S->top - S->base >= S->stacksize)//栈满，追加储存空间
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);//储存分配失败
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = e;
    return OK;
}//Push

Status Pop(struct SqStack *S, SElemType *e)
{
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if(S->top == S->base) return ERROR;
    S->top --;
    *e = *(S->top);
    return OK;
}//Pop

Status StackTraverse(struct SqStack *S, Status (*visit)(SElemType*))
{
    //依次对S的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    SElemType *p;
    if(S->top == S->base) return ERROR;
    p = S->top;
    while(p != S->base & visit(p) == OK)
        p--;
    if(p == S->base) return OK;
    else return ERROR;
}//StackTraverse

Status PrintStack(struct SqStack *S)
{
    //打印栈S
    SElemType *p;
    if(S->top == S->base)
    {
        printf("Error : EMPTY STACK\n");
        return ERROR;
    }
    printf("--TOP--\n");
    p = S->top;
    while(p != S->base)
    {
        p--;
        printf(" %d\n", *p); //Issue: SElemType?
    }
    printf("--BASE--\n");
    if(p == S->base) return OK;
    else return ERROR;
}//PrintStack
