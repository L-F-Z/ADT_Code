//CHAR_STRING
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

#ifndef CHAR_STRING
#define CHAR_STRING

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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
//使用char[]作为字符串的数据结构, 字符串要求同C语言要求, 以0结尾.
typedef char *String_C;
//-----------------------------
//定义的新的变量类型首字母大写

//---------|Constdef|----------
#define BUFSIZE 1024
//-----------------------------

//---------|FuncList|----------
//所有函数要求和书上一样
//写函数的时候麻烦顺便把书上注释也抄了(笑)

//高云聪
Status StrAssign(String_C *S, char *src);
Status StrInput(String_C *S);
Status StrCopy(String_C *S, String_C src);
Status StrEmpty(String_C S);
Status StrCompare(String_C S, String_C T);
Status StrLength(String_C S);
Status ClearString(String_C *S);
Status Concat(String_C *dist, String_C S1, String_C S2);
Status SubString(String_C *dist, String_C S, int pos, int len);

//邱林
int Index(String_C S, String_C T, int pos);
Status Replace(String_C *S, String_C T, String_C V);
Status StrInsert(String_C *S, int pos, String_C T);
Status StrDelete(String_C *S, int pos, int len);
Status DestoryString(String_C *S);

//韩雨
Status StrPrint(String_C S);
Status Index_KMP(String_C S, String_C C, int pos);
//测试代码

void get_next(String_C T, int next[]);
int char_string_length(char *C);
//-----------------------------

Status StrCopy(String_C *S, String_C src)
//由串S复制得串T
{
    int len = StrLength(src);
    int i = 0;

    free(*S);
    *S = malloc(sizeof(char) * (len + 1));
    for (i = 0; i <= len; i++)
    {
        (*S)[i] = src[i];
    }
}

int StrEmpty(String_C S)
//若S为空串，则返回TRUE，否则返回FALSE
{
    return (!(*S));
}

int StrCompare(String_C S, String_C T)
//若S>T，则返回值>0；若S=T，则返回值=0;若S<T，则返回值<0
{
    int len_S = StrLength(S);
    int len_T = StrLength(T);
    int i = 0;

    for (i = 0; i < len_S && i < len_T; ++i)
    {
        if (S[i] != T[i])
            return S[i] - T[i];
    }
    return len_S - len_T;
}

int StrLength(String_C S)
//返回S的元素个数，称为串的长度
{
    int len = char_string_length(S);
    return len;
}

Status ClearString(String_C *S)
//将S清为空串
{
    S[0] = 0;
}

Status Concat(String_C *dist, String_C S1, String_C S2)
//用dist返回由S1和S2联接而成的新串
{
    int len_S1 = StrLength(S1);
    int len_S2 = StrLength(S2);

    free(*dist);
    if (!(*dist = (char *)malloc((len_S1 + len_S2 + 1) * sizeof(char))))
        exit(OVERFLOW);

    int i = 0;
    int j = 0;
    while (i < len_S1)
    {
        (*dist)[j++] = S1[i++];
    }
    i = 0;
    while (i <= len_S2)
    {
        (*dist)[j++] = S2[i++];
    }
    return OK;
}

Status SubString(String_C *dist, String_C S, int pos, int len)
//用dist返回串S的第pos个字符起长度为len的子串
{
    if (len < 0)
        return ERROR;
    (*dist) = (String_C)malloc(sizeof(char) * (len + 1));
    int len_S = StrLength(S);
    int i = pos;

    if (len_S < 0 || pos < 0 || len < 0 || (pos + len) > len_S)
        return ERROR;
    else
    {
        for (i == pos; i < pos + len; i++)
        {
            (*dist)[i - pos] = S[i];
        }
    }
    return OK;
}

int Index(String_C S, String_C T, int pos)
{
    int i, j = 0;
    i = pos;
    j = 0;
    int len_S = char_string_length(S);
    int len_T = char_string_length(T);
    if (pos < 0 || pos >= len_S)
        return ERROR;
    while (i <= (len_S - 1) && j <= (len_T - 1))
    {
        if (*(S + i) == *(T + j))
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= len_T)
        return i - j;
    else
        return -1;
} //返回S中第pos个后与T相同的第一个子串的在S的地址，否则为0

Status Replace(String_C *S, String_C T, String_C V)
{
    int p = 0;
    int k;
    int len_T = char_string_length(T);
    int len_S = char_string_length(*S);
    int len_V = char_string_length(V);

    while ((k = Index(*S, T, p)) > -1)
    {
        StrDelete(S, k + 1, len_T);
        StrInsert(S, k + 1, V);
        p = k + len_V;
    }
    return OK;
} //用V替换主串S中出现的所有与T相等的不重叠的子串

Status StrInsert(String_C *S, int pos, String_C T)
{
    int len_S = char_string_length(*S);
    int len_T = char_string_length(T);
    if (pos > len_S) //允许在'\0'之前插入
        return ERROR;
    String_C temp = (String_C)malloc(sizeof(char) * (len_S + len_T + 1));
    if (pos > 0)
        memcpy(temp, (*S), pos - 1);
    memcpy(temp + pos - 1, T, len_T);
    memcpy(temp + pos + len_T - 1, *S + pos - 1, len_S - pos + 2);
    free(*S);
    *S = temp;
    return OK;

} //在串S的第pos个字符之前插入串T

Status StrDelete(String_C *S, int pos, int len)
{
    int len_S = char_string_length(*S);
    if (pos + len > len_S || len < 0 || pos < 0 || pos >= len_S)
        return ERROR;
    int before = pos;
    int after = pos + len;
    while ((*S)[after])
    {
        (*S)[before++] = (*S)[after++];
    }
    (*S)[before] = 0;
    return OK;
} //从串S中删除第pos个字符起长度为len的子串

Status DestoryString(String_C *S)
{
    if (*S)
    {
        free(*S);
        S = NULL;
        return OK;
    }
    else
        return ERROR;
} //串S被销毁

int char_string_length(char *C) //返回一个char字符串的长度
{
    int cnt = 0;
    while (*C)
    {
        ++cnt;
        ++C;
    }
    return cnt;
}

Status StrAssign(String_C *S, char *src) //用char*字符串初始化char*字符串
{
    int len = char_string_length(src);
    if (*S = (String_C)malloc(sizeof(char) * (len + 1)))
    {
        memcpy(*S, src, len + 1);
        return OK;
    }
    return ERROR;
}

Status StrInput(String_C *S) //使用scanf创建字符串
{
    char buf[BUFSIZE];
    scanf("%s", buf);
    int len = char_string_length(buf);
    if (len < (BUFSIZE))
    {
        if ((*S) = (String_C)malloc(sizeof(char) * (len + 1)))
        {
            memcpy(*S, buf, len + 1);
            return OK;
        }
        else
        {
            return ERROR;
        }
    }
    return ERROR;
}

Status StrPrint(String_C S) //打印字符串
{
    printf("%s", S);
    return OK;
}

int next[BUFSIZE];

void get_next(String_C T, int next[])
{
    //求模式串T的next函数值并存入数组next
    int i, j = 0, l = char_string_length(T);
    next[0] = 0;
    for (i = 1; i < l; ++i)
    {
        while (j > 0 && T[i] != T[j])
            j = next[j - 1];
        if (T[i] == T[j])
            ++j;
        next[i] = j;
    }
} //get_next

int Index_KMP(String_C S, String_C T, int pos)
{
    //利用模式串T的next函数求T在主串S第pos个字符之后的位置的
    //  KMP算法。其中，T非空，0<=pos<=StrLength(S) - 1
    int i = pos, j = 0, ls = char_string_length(S), lt = char_string_length(T);
    get_next(T, next);
    for (i = 0; i < ls; ++i)
    {
        while (j > 0 && T[j] != S[i])
            j = next[j - 1];
        if (T[j] == S[i])
            ++j;
        if (j == lt)
            return i - lt + 1;
    }
    return -1;
} //Index_KMP

    //for debug

// #include "lazy.h"
// int test_gyc()
// {
//     String_C a, b, c, d, e, f;

//     StrInput(&a);
//     StrPrint(a);

//     StrAssign(&b, "2333333");
//     StrAssign(&c, "111111");
//     StrAssign(&d, "222222222");
//     StrAssign(&e, "33333");
//     StrPrint(b);
//     StrPrint(c);
//     StrPrint(d);
//     StrPrint(e);
//     puts("-------------------");
//     StrCopy(&a, c);
//     puts("-------------------");

//     StrPrint(c);
//     puts("-------------------");

//     StrPrint(a);

//     //printf("%d\n",StrEmpty(a));
//     //ClearString(&a);

//     SubString(&e, b, 0, 3);
//     StrPrint(e);
// }
// int main()
// {
//     /*
//     String_C a;
//     StrInput(&a);
//     StrPrint(a);
//     StrAssign(&a, "2333333");
//     StrPrint(a);*/

//     test_gyc();

//     String_C a, b, d, e;
//     // StrInput(&a);
//     // StrInput(&b);
//     // StrInput(&d);
//     StrAssign(&a, "02330000000023333000000");
//     StrAssign(&b, "233");
//     StrAssign(&d, "4");
//     StrAssign(&e, "3");
//     String_C *c;
//     c = &a;
//     printf("%s\n", a);
//     printf("%s\n", b);
//     printf("%s\n", d);
//     printf("%s\n", *c);
//     StrDelete(c, 2, 3);
//     printf("%s\n", *c);
//     StrInsert(c, 2, b);
//     printf("%s\n", *c);
//     Replace(c, e, d);
//     printf("%s\n", *c);
// }

#endif