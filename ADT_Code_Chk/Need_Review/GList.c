#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//广义表的头尾链表存储表示
typedef enum {ATOM, LIST} ElemTag; //ATOM == 0：原子，LIST == 1：子表
typedef char AtomType; //原子的数据类型
typedef struct GLNode{
    ElemTag tag; //公共部分，用于区分原子结点和表结点
    union { //原子结点和表结点的联合部分
        AtomType atom; //原子结点的值域
        struct {struct GLNode *hp, *tp;} ptr; //ptr是表结点的指针域，ptr.hp和ptr.tp分别指向表头和表尾
    };
} GLNode, *GList; //广义表类型
//-----------------------------

//---------|FuncList|----------
Status InitGList(GList *L);
    //创建空的广义表L
Status CreateGList(GList *L, char *S);
    //由S创建广义表L
Status DestroyGList(GList *L);
    //销毁广义表L
Status CopyGList(GList *T, GList L);
    //由广义表L复制得到广义表T
int GListLength(GList L);
    //求广义表L的长度
int GListDepth(GList L);
    //求广义表L的深度
int GListEmpty(GList L);
    //判定广义表L是否为空
Status GetHead(GList L, GList *T);
    //取广义表L的头，存入T
Status GetTail(GList L, GList *T);
    //取广义表L的尾，存入T
Status InsertFirst_GL(GList *L, AtomType e);
    //插入元素e作为广义表L的第一元素
Status DeleteFirst_GL(GList L, AtomType *e);
    //删除广义表L的第一元素，并用e返回其值
Status Traverse_GL(GList L, Status Visit(GList L));
    //遍历广义表L，用函数Visit处理每个元素
//-----------------------------

//------------Func-------------

Status InitGList(GList *L)
{
    //创建空的广义表L
    *L = NULL;
    return OK;
}

Status serve(char **str, char **hstr)
{
    //将非空串str分割成两部分，hstr是第一个','前的字串，str是之后的字串
    //要求*str是可写的
    int n = strlen(*str);
    int i = 0, k = 0; //k为未配对的左括号的个数
    char ch;
    do //搜索最外层的第一个逗号
    {
        ch = (*str)[i++];
        if(ch == '(') ++k;
        if(ch == ')') --k;
    }while(i < n && (k != 0 || ch != ','));
    if(i < n)
    {
        *hstr = *str; (*str)[i - 1] = '\0'; //令hstr为第一个','前的字串
        *str = *str + i; //令str是之后的字串
    }
    else //最外层没有逗号
    {
        *hstr = *str; //将hstr置为str
        *str = *str + n; //将str置为空串
    }
    return OK;
}

Status CreateGList(GList *L, char *S)
{
    //由S创建广义表L，假定输入S是正确的
    //为了不引入串的内容，尽量用<string.h>中的函数代替串中的函数，SubString用等效的操作代替
    //要求S是可写的
    const char *emp = "";
    int Sl = strlen(S);
    char *sub, *hsub;
    GList p, q;
    if(strcmp(S, emp) == 0) *L = NULL; //创建空表
    else
    {
        *L = (GList)malloc((sizeof(GLNode)));
        if(!(*L)) exit(OVERFLOW);
        if(Sl == 1) //创建原子结点
        {
            (*L)->tag = ATOM;
            (*L)->atom = S[0];
        }
        else
        {
            (*L)->tag = LIST;
            p = *L;
            sub = S + 1; sub[Sl - 2] = '\0'; //脱外层括号
            do
            {
                serve(&sub, &hsub); //从sub中分离出表头串hsub
                CreateGList(&((p->ptr).hp), hsub); //用表头串创建子表
                q = p;
                if(strcmp(sub, emp) != 0) //表尾不空
                {
                    p = (GList)malloc(sizeof(GLNode));
                    if(!p) exit(OVERFLOW);
                    (q->ptr).tp = p;
                    p->tag = LIST;
                }
            }while(strcmp(sub, emp) != 0);
            (q->ptr).tp = NULL;
        }
    }
    return OK;
}

Status DestroyGList(GList *L)
{
    //销毁广义表L
    GList p, q;
    p = *L;
    if(!p) return OK; //已经是空表
    if(p->tag == ATOM) //销毁原子结点
    {
        free(p);
        return OK;
    }
    while(p)
    {
        DestroyGList(&(p->ptr).hp);
        q = p;
        p = (p->ptr).tp;
        free(q);
    }
    *L = NULL;
    return OK;
}

Status CopyGList(GList *T, GList L)
{
    //由广义表L复制得到广义表T
    if(!L) *T = NULL; //复制空表
    else
    {
        *T = (GList)malloc(sizeof(GLNode)); //建立表结点
        if(!(*T)) exit(OVERFLOW);
        (*T)->tag = L->tag;
        if((*T)->tag == ATOM) //复制原子结点
            (*T)->atom = L->atom;
        else //复制两个子表
        {
            CopyGList(&(( (*T)->ptr ).hp), (L->ptr).hp);
            CopyGList(&(( (*T)->ptr ).tp), (L->ptr).tp);
        }
    }
    return OK;
}

int GListLength(GList L)
{
    //求广义表L的长度
    int length = 1;
    if(!L) return 0;
    while((L->ptr).tp)
    {
        ++length;
        L = (L->ptr).tp;
    }
    return length;
}

int GListDepth(GList L)
{
    //求广义表L的深度
    int max = 0;
    int td;
    if(!L) return 1; //空表深度为1
    if(L->tag == ATOM) return 0; //原子结点深度为0
    for(; L; L = (L->ptr).tp)
    {
        td = GListDepth((L->ptr).hp); //求子表深度
        if(td >= max) max = td;
    }
    return max + 1;
}

int GListEmpty(GList L)
{
    //判定广义表L是否为空
    return (!L);
}

Status GetHead(GList L, GList *T)
{
    //取广义表L的头，存入T
    if(!L) return ERROR; //L是空表
    if(L->tag == ATOM) return ERROR; //L是原子结点
    *T = (L->ptr).hp;
    return OK;
}

Status GetTail(GList L, GList *T)
{
    //取广义表L的尾，存入T
    if(!L) return ERROR; //L是空表
    if(L->tag == ATOM) return ERROR; //L是原子结点
    *T = (L->ptr).tp;
    return OK;
}

Status InsertFirst_GL(GList *L, AtomType e)
{
    //插入元素e作为广义表L的第一元素
    GList p = (GList)malloc(sizeof(GLNode));
    if(!p) exit(OVERFLOW);
    GList pe = (GList)malloc(sizeof(GLNode));
    if(!pe) exit(OVERFLOW);
    pe->tag = ATOM;
    pe->atom = e;
    if(!(*L)) //空表时无法访问(*L)->tag
    {
        p->tag = LIST;
        (p->ptr).hp = pe;
        (p->ptr).tp = *L;
        *L = p;
    }
    else
    {
        if((*L)->tag == ATOM) //单个原子结点不是广义表
        {
            free(pe);
            pe = NULL;
            return ERROR;
        }
        p->tag = LIST;
        (p->ptr).hp = pe;
        (p->ptr).tp = *L;
        *L = p;
    }
    return OK;
}

Status DeleteFirst_GL(GList L, AtomType *e)
{
    //删除广义表L的第一个元素，并用e返回其值
    if(!L) return ERROR; //空表没有元素
    GList p = (L->ptr).hp, q = L;
    while(p->tag == LIST) //寻找第一个元素
    {
        q = p;
        p = (p->ptr).hp;
    }
    *e = p->atom;
    (q->ptr).hp = NULL;
    return OK;
}

Status Traverse_GL(GList L, Status Visit(GList L))
{
    //遍历广义表L，用函数Visit处理每个元素
    if(!L) return OK;
    if(L->tag == ATOM)
        return Visit(L);
    while(L)
    {
        if(Visit(L) == ERROR) return ERROR;
        Traverse_GL((L->ptr).hp, Visit);
        L = (L->ptr).tp;
    }
    return OK;
}

Status Delete_GL(GList L, AtomType x)
{
    //删除广义表L中所有值为x的原子结点
    GList p = L, q;
    if(!L) return OK;
    for(; p; p = (p->ptr).tp)
    {
        q = (p->ptr).hp;
        if(!q) continue;
        if(q->tag == ATOM)
        {
            if(q->atom == x)
            {
                free(q);
                (p->ptr).hp = NULL;
            }
            continue;
        }
        Delete_GL((p->ptr).hp, x);
    }
    return OK;
}

//-----------------------------

//------------Test-------------
Status printGLNode(GList L)
{
    if(L->tag == ATOM)
        printf("%p, %d, %c\n", L, L->tag, L->atom);
    else
        printf("%p, %d, %p, %p\n", L, L->tag, (L->ptr).hp, (L->ptr).tp);
    return OK;
}

void printGList(GList L)
{
    if(!L) printf("NULL\n");
    else Traverse_GL(L, printGLNode);
    printf("-------------------------------\n");
}

int main()
{
    /*
    char S[1000] = "((),(b,c,d),(c))";
    GList L, T;
    char c;
    InitGList(&L);
    InitGList(&T);
    CreateGList(&L, S);
    printGList(L);
    CopyGList(&T, L);
    DestroyGList(&L);
    printGList(L);
    printGList(T);
    printf("empty: %d %d\n", GListEmpty(L), GListEmpty(T));
    printf("l: %d  d: %d\n", GListLength(T), GListDepth(T));
    GetHead(T, &L);
    printGList(L);
    GetTail(T, &L);
    printGList(L);
    InsertFirst_GL(&T, 'x');
    printGList(T);
    DeleteFirst_GL(T, &c);
    printGList(T);
    printf("c: %c\n", c);
    Delete_GL(T, 'c');
    printGList(T);
    */
    return 0;
}
//-----------------------------