//LINKED_QUEUE
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
typedef int ElemType; //存储的数据类型
struct QNode //链式队列节点
{
    ElemType data;      //数据域
    struct QNode *next; //指针域，指向下一个节点
};
struct LinkQueue //链式队列头
{
    struct QNode *front;
    struct QNode *rear;
};//链式队列头节点指针
//-----------------------------

//---------|FuncList|----------
Status InitQueue(struct LinkQueue*);
//生成一个新的链式队列
Status QueueEmpty(struct LinkQueue*);
//返回队列是否为空, 若为空返回TRUE
int QueueLength(struct LinkQueue*);
//返回链式队列长度
Status GetHead(struct LinkQueue*, ElemType*);
//返回队列头元素值
Status EnQueue(struct LinkQueue*, ElemType);
//将新元素进入队列尾
Status DeQueue(struct LinkQueue*, ElemType*);
//将首元素离开队列
//-----------------------------
int main()
{
    struct LinkQueue Q;
    int a;
    
    InitQueue(&Q);
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);   
    GetHead(&Q,&a);
    printf("%d\n", a);
    DeQueue(&Q,  &a);
    printf("%d\n", a);
    DeQueue(&Q,  &a);
    printf("%d\n", a);
    return 0;
}

Status InitQueue(struct LinkQueue *Q)
//生成一个新的链式队列
{
    Q->front = Q->rear = (struct QNode*)malloc(sizeof(struct QNode));
    if (!Q->front)
        exit(OVERFLOW);
    Q->front->next = NULL;
    Q->rear->data = 1;
    return OK;
}

Status QueueEmpty(struct LinkQueue *Q)
//返回队列是否为空, 若为空返回TRUE
{
    return Q->rear == Q->front;
}

int QueueLength(struct LinkQueue *Q)
//返回链式队列长度
{
    int cnt = 0;
    if (!Q)
        return -1;
    struct QNode *t = Q->front;
    while (t != Q->rear)
    {
        t = t->next;
        cnt++;
    }
    return cnt;
}

Status GetHead(struct LinkQueue *Q, ElemType *E)
//返回队列头元素值
{
    if (!Q || Q->rear == Q->front)
        return OVERFLOW;
    *E = Q->front->next->data;
    return OK;
}

Status EnQueue(struct LinkQueue *Q, ElemType E)
//将新元素进入队列尾
{
    struct QNode* p;
    p = (struct QNode*)malloc(sizeof(struct QNode));
    if (!p)
        exit(OVERFLOW);
    p->data = E;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

Status DeQueue(struct LinkQueue *Q, ElemType *E)
//将首元素离开队列
{
    if (Q->front == Q->rear)
        return ERROR;
    struct QNode* p = Q->front->next;
    *E = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}