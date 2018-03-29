//LINKED_LIST
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LINKED_LIST_C

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
typedef int ElemType; //链栈存储的数据类型
typedef struct Node 
{
	ElemType data;
	struct Node *next;
} LinkedStack;


//-----------------------------
//定义的新的变量类型首字母大写

//---------|FuncList|----------
//这里实现的是带头结点的链栈, 这是基本的函数列表

LinkedStack *InitLStack(void);
//创建一个带头结点的空栈
Status DestroyLStack(LinkedStack *);
//销毁链栈
Status ClearLStack(LinkedStack *);
//清空链栈（保留空栈)
int GetLen(LinkedStack *);
//获取链栈中元素个数并返回其值
Status GetTop(LinkedStack *, ElemType *);
//获取栈顶元素，但不改变链栈
Status Push(LinkedStack *, ElemType );
//将e写入栈顶
Status Pop(LinkedStack *, ElemType *);
//将栈顶元素推出至e,并从链栈中删除该元素
int IsLStackEmpty(LinkedStack *);
//判断链栈是否为空
Status TravalseLStack(LinkedStack *s ，Status(*visit)(ElemType *));
//遍历链栈中每一个元素，若访问失败，则返回ERROR

//-----------------------------


//-----------------------------

//函数示例
LinkedStack *InitLStack(void)
{
	//创建一个带头结点的空栈
	LinkedStack *s;
	s = (LinkedStack *)malloc(sizeof(LinkedStack));
	s->next = NULL;
	return s;
} //InitLStack

Status DestroyLStack(LinkedStack *s)
{
	//销毁链栈
	LinkedStack *t;
	if (!s) return ERROR;
	while (t = s->next)
	{
		free(s);
		s = t;
	}
	free(s); 
	return OK;
} //DestroyLStack

Status ClearLStack(LinkedStack *s)
{
	//清空链栈（保留空栈)
	LinkedStack *t;
	if (!s) return ERROR;
	while (t = s->next)
	{
		free(s);
		s = t;
	}
	return OK;
} //ClearLStack

int GetLen(LinkedStack *s)
{
	//获取链栈中元素个数并返回其值
	int i = 0;
	LinkedStack *t;
	while (t = s->next)
	{
		i++;
		s = t;
	}
	return i;
} //GetLen

Status GetTop(LinkedStack *s, ElemType *e)
{
	//获取栈顶元素，但不改变链栈
	LinkedStack *t;
	if (!s) return ERROR;
	
	t = s->next;
	e = t->data;
	return OK;
} //GetTop

Status Push(LinkedStack *s, ElemType e)
{
	//将e写入栈顶
	LinkedStack *t;
	t = alloca(sizeof(LinkedStack));
	if (!s) return ERROR;
	
	t->next = s->next;
	t->data = e;
	s->next = t;
	return OK;
} //Push

Status Pop(LinkedStack *s, ElemType *e)
{
	//将栈顶元素推出至e,并从链栈中删除该元素
	LinkedStack *t;
	if (!s) return ERROR;
	
	t = s->next;
	e = t->data;
	s->next = t->next;
	free(t);
	return OK;
} //Pop

Status IsLStackEmpty(LinkedStack *s)
{
	//判断链栈是否为空
	if (!s) return ERROR;
	
	if (s->next) return TRUE;
	else return FALSE;
} //IsLStackEmpty

Status TravalseLStack(LinkedStack *s，Status (*visit)(ElemType *))
{
	//遍历链栈中每一个元素，若访问失败，则返回ERROR
	/*LinkedStack *t;
	t = alloca(sizeof(LinkedStack));
	if (!s) return ERROR;
	
	while (t = s->next && visit(t->data))
	{
		s = t;
	}
	
	if (t) return OK;
	else return ERROR;*/
	if (s == NULL) return ERROR;

	if (IsLStackEmpty(s) == TRUE)
		return ERROR;
	s = s->next;
	while (s && visit(&s->data) == OK)
		s = s->next;
	if (!s)
		return OK;
	else
		return ERROR;
} //TravalseLStack*/

int main()
{

	return 0;

}
