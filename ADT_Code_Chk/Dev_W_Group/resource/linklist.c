// MCSTL: My C Standard Template Libray, created for data structure class

// Author: Huaqiang Wang
// Created: 2018.3.5

// linklist.c

//TODO: 用raw string ## 实现模板? /滑稽
// #define _UNITTEST_LINKLIST_C

#ifndef _LINKLIST_C
#define _LINKLIST_C

#define ERROR -1
#define OVERFLOW -2

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lazy.h"

// typedef int DatatypeLinklist;
#define DatatypeLinklist int

//simple linklist func prototype

typedef struct Lnode
{
    DatatypeLinklist data;
    struct Lnode *next;
} Lnode, *pLnode;

pLnode LinklistInit();
int LinklistFree(pLnode plinklist);
int LinklistClear(pLnode plinklist);
int LinklistAdd(pLnode plinklist, DatatypeLinklist data);
// int LinklistInsFirst(pLnode plinklist, DatatypeLinklist data);
int LinklistAppend(pLnode plinklist, DatatypeLinklist data);
int LinklistAppendLinklist(pLnode ll1, pLnode ll2);
int LinklistMap(pLnode plinklist, void func());
int LinklistFind(pLnode plinklist, DatatypeLinklist data);
int LinklistGet(pLnode plinklist, int position, DatatypeLinklist *pdata);
int LinklistDel(pLnode plinklist, int position);
int LinklistInsert(pLnode plinklist, int position, DatatypeLinklist data);
int LinklistInsertAfter(pLnode plinklist, int position, DatatypeLinklist data);
int LinklistInsertStrict(pLnode plinklist, int position, DatatypeLinklist data);
int LinklistPop(pLnode plinklist, int position, DatatypeLinklist *pdata);
pLnode LinklistMerge(pLnode ll1, pLnode ll2, int compfunc());
pLnode LinklistCpyNode(pLnode src);
pLnode LinklistCounterpart(pLnode src);
int LinklistCpyAll(pLnode dist, pLnode src);
int LinklistLength(pLnode plinklist);
int LinklistPosition(pLnode plinklist, pLnode pnode);
pLnode LinklistBefore(pLnode plinklist, pLnode pnode);
pLnode LinklistNext(pLnode pnode);
int LinklistTranspose(pLnode plinklist);

//array linklist func prototype

typedef struct ALnode
{
    DatatypeLinklist data;
    int next;
} ALnode, *pALnode;

// pALnode ALinklistInit();
// int ALinklistAppend(pALnode plinklist, DatatypeLinklist data);
// int ALinklistAdd(pALnode plinklist, DatatypeLinklist data);
// int ALinklistMap(pALnode plinklist, void func());
// int ALinklistFind(pALnode plinklist, DatatypeLinklist data);
// int ALinklistGet(pALnode plinklist, int position, DatatypeLinklist *pdata);
// int ALinklistInsert(pALnode plinklist, int position, DatatypeLinklist data);
// int ALinklistInsertStrict(pALnode plinklist, int position, DatatypeLinklist data);
// int ALinklistDel(pALnode plinklist, int position);
// int ALinklistPop(pALnode plinklist, int position, DatatypeLinklist *pdata);
// int ALinklistFree(pALnode plinklist);
// pLnode ALinklistMerge(pALnode ll1, pALnode ll2, int compfunc());

//double linklist func prototype

typedef struct DLnode
{
    DatatypeLinklist data;
    struct Lnode *next;
} DLnode, *pDLnode;

// pDLnode DLinklistInit();
// int DLinklistAppend(pDLnode plinklist, DatatypeLinklist data);
// int DLinklistAdd(pDLnode plinklist, DatatypeLinklist data);
// int DLinklistMap(pDLnode plinklist, void func());
// int DLinklistFind(pDLnode plinklist, DatatypeLinklist data);
// int DLinklistGet(pDLnode plinklist, int position, DatatypeLinklist *pdata);
// int DLinklistInsert(pDLnode plinklist, int position, DatatypeLinklist data);
// int DLinklistInsertStrict(pDLnode plinklist, int position, DatatypeLinklist data);
// int DLinklistDel(pDLnode plinklist, int position);
// int DLinklistPop(pDLnode plinklist, int position, DatatypeLinklist *pdata);
// int DLinklistFree(pDLnode plinklist);
// pDLnode DLinklistMerge(pDLnode ll1, pDLnode ll2, int compfunc());

//circular linklist is omitted

pLnode LinklistInit()
{
    pLnode p = (pLnode)malloc(sizeof(Lnode));
    p->next = 0;
    return p;
}

int LinklistAppend(pLnode plinklist, DatatypeLinklist data)
{
    pLnode p = plinklist;
    while (p->next != 0)
    {
        p = p->next;
    }
    pLnode n = (pLnode)malloc(sizeof(Lnode));
    if (n)
    {
        n->data = data;
        n->next = 0;
        p->next = n;
        return 0;
    }
    return ERROR;
}

int LinklistAdd(pLnode plinklist, DatatypeLinklist data)
{
    pLnode p = plinklist;
    pLnode n = (pLnode)malloc(sizeof(Lnode));
    if (n)
    {
        n->data = data;
        n->next = p->next;
        p->next = n;
        return 0;
    }
    return ERROR;
}

int LinklistMap(pLnode plinklist, void func())
{
    if (plinklist == 0)
        return ERROR;
    pLnode p = plinklist;
    if (p = p->next)
    {
        while (p->next != 0)
        {
            func(p->data);
            p = p->next;
        }
        func(p->data);
        return 0;
    }
    return ERROR;
}

int LinklistFind(pLnode plinklist, DatatypeLinklist data)
{
    int cnt = 0;
    while (plinklist = plinklist->next)
    {
        cnt++;
        if (plinklist->data == data)
        {
            return cnt;
        }
    }
    return 0;
}

int LinklistGet(pLnode plinklist, int position, DatatypeLinklist *pdata)
{
    if (position < 1)
        return 0;
    int cnt = 0;
    while (plinklist = plinklist->next)
    {
        cnt++;
        if (cnt == position)
        {
            *pdata = plinklist->data;
            return 0;
        }
    }
    return ERROR;
}

int LinklistInsert(pLnode plinklist, int position, DatatypeLinklist data)
{
    if (position < 1)
        return ERROR;
    int cnt = 1;
    do
    {
        if (position == cnt)
        {
            pLnode n = (pLnode)malloc(sizeof(Lnode));
            if (n)
            {
                n->data = data;
                n->next = plinklist->next;
                plinklist->next = n;
                return 0;
            }
            return ERROR;
        }
        cnt++;
    } while (plinklist = plinklist->next);
    return ERROR;
}

int LinklistInsertAfter(pLnode plinklist, int position, DatatypeLinklist data)
{
    if (position < 1)
        return ERROR;
    int cnt = 0;
    do
    {
        if (position == cnt)
        {
            pLnode n = (pLnode)malloc(sizeof(Lnode));
            if (n)
            {
                n->data = data;
                n->next = plinklist->next;
                plinklist->next = n;
                return 0;
            }
            return ERROR;
        }
        cnt++;
    } while (plinklist = plinklist->next);
    return ERROR;
}

int LinklistInsertStrict(pLnode plinklist, int position, DatatypeLinklist data)
{
    int cnt = 0;
    while (plinklist && cnt < (position - 1))
    {
        plinklist = plinklist->next;
        cnt++;
    }                                       //Find the position-1 node
    if (!plinklist || cnt > (position - 1)) //position-1 node not exist
    {
        return ERROR;
    }
    pLnode n = (pLnode)malloc(sizeof(Lnode));
    if (n)
    {
        n->data = data;
        n->next = plinklist->next;
        plinklist->next = n;
        return 0;
    }
    return ERROR;
}

int LinklistDel(pLnode plinklist, int position)
{
    int cnt = 0;
    while (plinklist && cnt < (position - 1))
    {
        plinklist = plinklist->next;
        cnt++;
    }
    if (!plinklist || cnt > (position - 1))
        return ERROR;
    if (!plinklist->next)
        return ERROR;
    pLnode p = plinklist->next;
    plinklist->next = plinklist->next->next;
    free(p);
    return 0;
}

int LinklistPop(pLnode plinklist, int position, DatatypeLinklist *pdata)
{
    int cnt = 0;
    while (plinklist && cnt < (position - 1))
    {
        plinklist = plinklist->next;
        cnt++;
    }
    if (!plinklist || cnt > (position - 1))
        return ERROR;
    if (!plinklist->next)
        return ERROR;
    pLnode p = plinklist->next;
    *pdata = p->data;
    plinklist->next = plinklist->next->next;
    free(p);
    return 0;
}

int LinklistFree(pLnode plinklist)
{
    if (plinklist == 0)
        return ERROR;
    pLnode p;
    while (p = plinklist->next)
    {
        free(plinklist);
        plinklist = p;
    }
    return 0;
}

int LinklistAppendLinklist(pLnode ll1, pLnode ll2)
{
    if ((!ll1) || (!ll2))
        return ERROR;
    pLnode p = ll1->next;
    while (p->next)
        p = p->next;
    p->next = ll2->next;
    free(ll2);
    return 0;
}

pLnode LinklistMerge(pLnode ll1, pLnode ll2, int compfunc())
{
    if (ll1 == 0 || ll2 == 0 || ll1 == ll2)
        return 0;
    pLnode p = (pLnode)malloc(sizeof(Lnode));
    pLnode t;
    p->next = 0;
    ll1 = ll1->next;
    ll2 = ll2->next;
    while ((ll1 != 0) && (ll2 != 0)) //both 2 linklist not empty
    {
        switch (compfunc(ll1->data, ll2->data))
        {
        case 1:
            p = p->next = ll1;
            ll1 = ll1->next;
            break;
        case -1:
            p = p->next = ll2;
            ll2 = ll2->next;
            break;
        case 0:
            p = p->next = ll1;
            ll1 = ll1->next;
            break;
        default:
            return 0; // return null point
        }
    }
    if (ll1) //ll1 not empty
    {
        p->next = ll1;
    }
    else
    {
        p->next = ll2;
    }
    return p;
}

int LinklistClear(pLnode plinklist)
{
    if (plinklist)
    {
        LinklistFree(plinklist->next);
        plinklist->next = 0;
        return 0;
    }
    return ERROR;
}

int LinklistInsFirst(pLnode plinklist, DatatypeLinklist data)
{
    LinklistAdd(plinklist, data);
}

pLnode LinklistCpyNode(pLnode src)
{
    pLnode p = (pLnode)malloc(sizeof(Lnode));
    if (src)
    {
        p->data = src->data;
        p->next = src->next;
        return p;
    }
    return 0;
}

pLnode LinklistCounterpart(pLnode src)
{
    pLnode p = 0;
    pLnode s = 0;
    if (src)
    {
        s = p = LinklistCpyNode(src);
    }
    while (src = src->next) //not finished
    {
        p = p->next = LinklistCpyNode(src);
    }
    return s;
}

int LinklistCpyAll(pLnode dist, pLnode src)
{
    if (dist == 0)
        return ERROR;
    LinklistFree(dist->next);
    pLnode p = LinklistCounterpart(src);
    dist->next = p->next;
    free(p);
    return 0;
}

int LinklistLength(pLnode plinklist)
{
    if (plinklist)
    {
        int cnt = 0;
        while (plinklist = plinklist->next)
        {
            cnt++;
        }
        return cnt;
    }
    return ERROR;
}

int LinklistPosition(pLnode plinklist, pLnode pnode)
{
    if (plinklist)
    {
        int cnt = 0;
        while (plinklist->next && plinklist != pnode)
        {
            plinklist = plinklist->next;
            cnt++;
        }
        if (plinklist == pnode)
            return cnt;
        return OVERFLOW;
    }
    return ERROR;
}

pLnode LinklistBefore(pLnode plinklist, pLnode pnode)
{
    if (plinklist)
    {
        while (plinklist->next && plinklist->next != pnode)
        {
            plinklist = plinklist->next;
        }
        if (plinklist->next == pnode)
            return plinklist;
        return NULL;
    }
    return NULL;
}

pLnode LinklistNext(pLnode pnode)
{
    if (pnode)
    {
        return pnode->next;
    }
    return NULL;
}

int LinklistTranspose(pLnode plinklist)
{
    if (plinklist && plinklist->next)
    {
        pLnode newhead=plinklist->next;//temp
        pLnode cur = plinklist->next;//1st one
        pLnode nxt = cur->next;
        while (nxt) //nxt exists, not end
        {
            cur = nxt;
            nxt = cur->next;
            cur->next = newhead;
            newhead = cur;
        }
        plinklist->next->next = 0;
        plinklist->next = newhead;
        return 0;
    }
    return ERROR;
}

    //for debug

#ifdef _UNITTEST_LINKLIST_C

void Showint(int i)
{
    printf("%d\t", i);
}

int Intcmp(int a, int b)
{
    if (a > b)
        return 1;
    if (a = b)
        return 0;
    if (a < b)
        return -1;
}

int _debug_Linklist()
{
    pLnode ll;
    ll = LinklistInit();
    LinklistAppend(ll, 1);
    LinklistAppend(ll, 2);
    LinklistAppend(ll, 3);
    LinklistMap(ll, Showint);
    int a = LinklistFind(ll, 4);
    CK(a);
    a = LinklistFind(ll, 2);
    CK(a);
    LinklistGet(ll, 3, &a);
    CK(a);
    LinklistInsertStrict(ll, 4, 9);
    LinklistInsertStrict(ll, 1, 9);
    LinklistMap(ll, Showint);

    LinklistInsert(ll, 4, 0);
    LinklistMap(ll, Showint);
    LinklistInsert(ll, 1, 0);
    LinklistMap(ll, Showint);

    LinklistFree(ll);
    ll = LinklistInit();
    LinklistAdd(ll, 3);
    LinklistAdd(ll, 2);
    LinklistAdd(ll, 1);
    LinklistMap(ll, Showint);
    LinklistDel(ll, 1);
    LinklistPop(ll, 1, &a);
    CK(a);
    LinklistMap(ll, Showint);
    pLnode lll = LinklistInit();
    LinklistAdd(lll, 233);
    LinklistAdd(lll, 233);
    LinklistAdd(lll, 233);
    pLnode result = LinklistMerge(ll, lll, Intcmp);
    LinklistMap(result, Showint);
    LinklistClear(result);
    LinklistMap(result, Showint);
    LinklistAdd(result, 1);
    pLnode l = LinklistInit();
    LinklistAppend(l, 8);
    LinklistAppend(l, 7);
    LinklistAppend(l, 6);
    LinklistAppend(l, 5);
    LinklistAppendLinklist(result, l);
    LinklistMap(result, Showint);
    pLnode r = LinklistInit();
    puts("---------");
    LinklistCpyAll(r, result);
    LinklistMap(r, Showint);
    puts("---------");    
    LinklistTranspose(r);
    LinklistMap(r, Showint);
    pLnode o=LinklistInit();
    LinklistMap(o, Showint);
    LinklistAdd(o, 1);
    LinklistMap(o, Showint);
    LinklistTranspose(o);
    LinklistMap(o, Showint);
    
    
}

int main()
{
    _debug_Linklist();
}

#endif

#endif