//HEAP STRING
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status;

typedef struct
{
    char* ch;
    int length;//the length of string
} HString;

void StrInit ( HString* T )
{
    T->ch = NULL;
    T->length = 0;
}

Status StrAssign ( HString* T, char* chars )
{
    if ( T->ch )
    {
        free ( T->ch );    //free the origin space
    }
    T->length = 0;
    for ( char* c = chars; *c; c++, T->length++ );
    if ( !T->length )
    {
        T->ch = NULL;
    }
    else
    {
        if ( ! ( T->ch = ( char* ) malloc ( T->length * sizeof ( char ) ) ) )
        {
            return OVERFLOW;
        }
        for ( int i = 0; i < T->length; i++ )
        {
            T->ch[i] = chars[i];
        }
    }
    return OK;
}

Status StrCopy ( HString* T, HString S )
{
    if ( T->ch )
    {
        free ( T->ch );
        T->ch = NULL;
    }
    T->length = S.length;
    if ( ! ( T->ch = ( char* ) malloc ( T->length * sizeof ( char ) ) ) )
    {
        return OVERFLOW;
    }
    for ( int i = 0; i < T->length; i++ )
    {
        T->ch[i] = S.ch[i];
    }
    return OK;
}

int StrCompare ( HString S, HString T )
{
    for ( int i = 0; i < S.length && i < T.length; i++ )
    {
        if ( S.ch[i] != T.ch[i] )
        {
            return S.ch[i] - T.ch[i];
        }
    }
    return S.length - T.length;
}

Status ClearString ( HString* S )
{
    if ( S->ch )
    {
        free ( S->ch );
        S->ch = NULL;
    }
    S->length = 0;
    return OK;
}

int StrLength ( HString S )
{
    return S.length;
}

Status Concat ( HString* T, HString S1, HString S2 )
{
    if ( T->ch )
    {
        free ( T->ch );
    }
    T->length = S1.length + S2.length;
    if ( ! ( T->ch = ( char* ) malloc ( T->length * sizeof ( char ) ) ) )
    {
        return OVERFLOW;
    }
    for ( int i = 0; i < S1.length; i++ )
    {
        T->ch[i] = S1.ch[i];
    }
    for ( int i = 0; i < S2.length; i++ )
    {
        T->ch[S1.length + i] = S2.ch[i];
    }
    return OK;
}

Status SubString ( HString* Sub, HString S, int pos, int len )
{
    if ( pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1 )
    {
        return ERROR;
    }
    if ( Sub->ch )
    {
        free ( Sub->ch );
    }
    if ( !len )
    {
        Sub->ch = NULL;
        Sub->length = 0;
    }
    else
    {
        Sub->length = len;
        if ( ! ( Sub->ch = ( char* ) malloc ( Sub->length * sizeof ( char ) ) ) )
        {
            return OVERFLOW;
        }
        for ( int i = 0; i < Sub->length; i++ )
        {
            Sub->ch[i] = S.ch[pos + i - 1];
        }
    }
    return OK;
}


int Index ( HString S, HString T, int pos )
{
    int ret = 0;
    pos--;
    if ( pos < 0 || pos >= S.length )
    {
        return 0;
    }
    int flag = 0;
    for ( ret = pos; ret < S.length; ret++ )
    {
        if ( S.length - ret < T.length )
        {
            break;
        }
        flag = 1;
        for ( int i = 0; i < T.length; i++ )
        {
            if ( S.ch[ret + i] != T.ch[i] )
            {
                flag = 0;
                break;
            }
        }
        if ( flag )
        {
            break;
        }
    }
    ret++;
    if ( !flag )
    {
        ret = 0;
    }
    return ret;
}

Status StrInsert ( HString* S, int pos, HString T )
{
    pos--;
    if ( pos < 0 || pos > S->length )
    {
        return ERROR;
    }
    HString tmp;
    StrInit ( &tmp );
    tmp.length = S->length + T.length;
    if ( ! ( tmp.ch = ( char* ) malloc ( tmp.length * sizeof ( char ) ) ) )
    {
        return OVERFLOW;
    }
    for ( int i = 0; i < pos; i ++ )
    {
        tmp.ch[i] = S->ch[i];
    }
    for ( int i = 0; i < T.length; i++ )
    {
        tmp.ch[pos + i] = T.ch[i];
    }
    for ( int i = pos; i < S->length; i++ )
    {
        tmp.ch[i + T.length] = S->ch[i];
    }
    return StrCopy ( S, tmp );
}

Status StrDelete ( HString* S, int pos, int len )
{
    pos--;
    if ( pos < 0 || pos + len - 1 >= S->length )
    {
        return ERROR;
    }
    HString tmp;
    StrInit ( &tmp );
    tmp.length = S->length - len;
    if ( ! ( tmp.ch = ( char* ) malloc ( tmp.length * sizeof ( char ) ) ) )
    {
        return OVERFLOW;
    }
    for ( int i = 0; i < pos; i++ )
    {
        tmp.ch[i] = S->ch[i];
    }
    for ( int i = pos + len; i < S->length; i++ )
    {
        tmp.ch[i - len] = S->ch[i];
    }
    return StrCopy ( S, tmp );
}


Status Replace ( HString* S, HString T, HString V )
{
    if ( !T.length )
    {
        return ERROR;
    }
    int pos = 1;
    while ( ( pos = Index ( *S, T, pos ) ) )
    {
        int tmp;
        tmp = StrDelete ( S, pos, T.length );
        if ( tmp != OK )
        {
            return tmp;
        }
        tmp = StrInsert ( S, pos, V );
        if ( tmp != OK )
        {
            return tmp;
        }
        pos += V.length;
    }
    return OK;
}


Status DestroryString ( HString* S )
{
    S->length = 0;
    if ( S->ch )
    {
        free ( S->ch );
        S->ch = NULL;
    }
    return OK;
}

//--------------Test--------------//

Status _print(HString *S)
{
  for(int i=0; i<S->length; i++)
    printf("%c ", S->ch[i]);
  printf("%c", '\n');
}

int main()
{
    HString s, t, v;
    StrInit(&s);
    printf("StrAssign(s):       %d\n", StrAssign(&s, "Tse\0Beny"));
    _print(&s);
    printf("StrLength(s):       %d\n", StrLength(s));
    StrInit(&t);
    printf("StrCopy(&t, s):     %d\n", StrCopy(&t, s));
    _print(&t);
    printf("DestroryString(&t): %d\n", DestroryString(&t));
    StrInit(&t);
    printf("StrCopy(&s, t):     %d\n", StrCopy(&s, t));
    _print(&t);
    printf("StrLength(s):       %d\n", StrLength(s));
    printf("StrLength(t):       %d\n", StrLength(t));
    printf("%s", "-------------------------------------\n");
    printf("StrAssign(s):       %d\n", StrAssign(&s, "Tse\0Beny"));
    printf("StrAssign(t):       %d\n", StrAssign(&t, "Tse"));
    printf("StrCompare(s, t):   %d\n", StrCompare(s, t));
    printf("Concat(&s, t, t):   %d\n", Concat(&s, t, t));
    _print(&s);
    printf("ClearString(&s):    %d\n", ClearString(&s));
    printf("StrLength(s):       %d\n", StrLength(s));
    printf("Concat(&s, t, t):   %d\n", Concat(&s, t, t));
    printf("SubString(&t,s,2,4):%d\n", SubString(&t,s,2,5));
    _print(&t);
    printf("Index(s, t, 1):     %d\n", Index(s, t, 3));
    printf("Index(s, t, 1):     %d\n", Index(s, t, 2));
    printf("%s", "-------------------------------------\n");
    StrInit(&v);
    printf("StrAssign(s):       %d\n", StrAssign(&s, "TseTseTseTseTseTseTse"));
    printf("StrAssign(v):       %d\n", StrAssign(&v, "19"));
    _print(&s);
    _print(&t);
    _print(&v);
    printf("Replace(&s,t,v):    %d\n", Replace(&s,t,v));
    _print(&s);
    printf("%s", "-------------------------------------\n");
    printf("StrInsert(&s, 1, t):%d\n", StrInsert(&s, 1, t));
    _print(&s);
    printf("StrInsert(&s, 1, t):%d\n", StrInsert(&v, 3, t));
    _print(&v);
    printf("StrDelete(&s,1,all):%d\n", StrDelete(&s,1,StrLength(s)));
    printf("StrLength(s):       %d\n", StrLength(s));

    return 0;
}
//--------The-End-of-Test---------//
//------------Logs----------------//
//问题以及改动:
//    1.  SubString的位置从1开始,而不是从0开始
//        143行改为pos + i - 1
//疑惑:
//    1.  需不需要实现Concat(&s, s, s)?
//--------The-End-of-Logs---------//
