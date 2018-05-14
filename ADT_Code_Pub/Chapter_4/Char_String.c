//CHAR_STRING
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group
//Checked by LFZ

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
Status StrAssign(String_C *T, char *S);
Status StrInput(String_C *S);
Status StrCopy(String_C *S, String_C src);
Status StrEmpty(String_C S);
Status StrCompare(String_C S, String_C T);
Status StrLength(String_C S);
Status ClearString(String_C *S);
Status Concat(String_C *dist, String_C S1, String_C S2);
Status SubString(String_C *dist, String_C S, int pos, int len);
int Index(String_C S, String_C T, int pos);
Status Replace(String_C *S, String_C T, String_C V);
Status StrInsert(String_C *S, int pos, String_C T);
Status StrDelete(String_C *S, int pos, int len);
Status DestoryString(String_C *S);
Status StrPrint(String_C S);
Status Index_KMP(String_C S, String_C C, int pos);
void get_next(String_C T, int next[]);
//-----------------------------

Status StrCopy(String_C *T, String_C S)
//由串S复制得串T
{
    int len = StrLength(S), i = 0;
    *T = malloc(sizeof(char) * (len + 1));
    for (i = 0; i <= len; i++)
        (*T)[i] = S[i];
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
    int cnt = 0;
    while (*S)
    {
        ++cnt;
        ++S;
    }
    return cnt;
}

Status ClearString(String_C *S)
//将S清为空串
{
    S[0] = 0;
}

Status Concat(String_C *dist, String_C S1, String_C S2)
//用dist返回由S1和S2联接而成的新串
{
    int len_S1 = StrLength(S1), len_S2 = StrLength(S2);
    int i = 0, j = 0;
    if (!(*dist = (char *)malloc((len_S1 + len_S2 + 1) * sizeof(char))))
        exit(OVERFLOW);
    while (i < len_S1)
        (*dist)[j++] = S1[i++];
    i = 0;
    while (i <= len_S2)
        (*dist)[j++] = S2[i++];
    return OK;
}

Status SubString(String_C *dist, String_C S, int pos, int len)
//用dist返回串S的第pos个字符起长度为len的子串
{
    int len_S = StrLength(S), i = pos;
    (*dist) = (String_C)malloc(sizeof(char) * (len + 1));
    if (!(*dist) || len_S < 0 || pos < 0 || len < 0 || (pos + len) > len_S)
        return ERROR;
    for (i == pos; i < pos + len; i++)
        (*dist)[i - pos] = S[i];
    (*dist)[len] = 0;
    return OK;
}

int Index(String_C S, String_C T, int pos)
{
    int i, j = 0;
    i = pos;
    j = 0;
    int len_S = StrLength(S);
    int len_T = StrLength(T);
    if (pos < 0 || pos >= len_S)
        return ERROR;
    while (i <= (len_S - 1) && j <= (len_T - 1))
        if (*(S + i) == *(T + j))
            i++, j++;
        else
            i = i - j + 1, j = 0;
    if (j >= len_T)
        return i - j;
    else
        return -1;
} //返回S中第pos个后与T相同的第一个子串的在S的地址，否则为0

Status Replace(String_C *S, String_C T, String_C V)
{
    int k, p = 0;
    int len_S = StrLength(*S);
    int len_T = StrLength(T);
    int len_V = StrLength(V);
    while ((k = Index_KMP(*S, T, p)) > -1)
    {
        StrDelete(S, k, len_T);
        StrInsert(S, k, V);
        p = k + len_V;
    }
    return OK;
} //用V替换主串S中出现的所有与T相等的不重叠的子串

Status StrInsert(String_C *S, int pos, String_C T)
{
    int len_S = StrLength(*S);
    int len_T = StrLength(T);
    if (pos > len_S || pos < 0) //允许在'\0'之前插入
        return ERROR;
    String_C temp = (String_C)malloc(sizeof(char) * (len_S + len_T + 1));
    memcpy(temp, (*S), pos);
    memcpy(temp + pos, T, len_T);
    memcpy(temp + pos + len_T, *S + pos, len_S - pos + 1);
    free(*S);
    *S = temp;
    return OK;
} //在串S的第pos个字符之前插入串T

Status StrDelete(String_C *S, int pos, int len)
{
    int len_S = StrLength(*S);
    int before = pos;
    int after = pos + len;
    if (pos + len > len_S || len < 0 || pos < 0 || pos >= len_S)
        return ERROR;
    while ((*S)[after])
        (*S)[before++] = (*S)[after++];
    (*S)[before] = 0;
    return OK;
} //从串S中删除第pos个字符起长度为len的子串

Status DestoryString(String_C *S)//销毁串S
{
    if (*S)
    {
        free(*S);
        S = NULL;
        return OK;
    }
    else
        return ERROR;
}

Status StrAssign(String_C *S, char *src) //用char*字符串初始化char*字符串
{
    int len = StrLength(src);
    if (*S = (String_C)malloc(sizeof(char) * (len + 1)))
    {
        memcpy(*S, src, len + 1); //TODO: Try not to use <string.h>
        return OK;
    }
    return ERROR;
}

Status StrInput(String_C *S) //使用scanf创建字符串
{
    char buf[BUFSIZE];
    scanf("%s", buf);
    int len = StrLength(buf);
    if (len < (BUFSIZE))
        if ((*S) = (String_C)malloc(sizeof(char) * (len + 1)))
        {
            memcpy(*S, buf, len + 1); //TODO: Try not to use <string.h>
            return OK;
        }
    return ERROR;
}

Status StrPrint(String_C S) //打印字符串
{
    printf("%s\n", S);
    return OK;
}

int next[BUFSIZE];
void get_next(String_C T, int next[])
{
    //求模式串T的next函数值并存入数组next
    int i, j = 0, l = StrLength(T);
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
    int i, j = 0, ls = StrLength(S), lt = StrLength(T);
    get_next(T, next);
    for (i = pos; i < ls; ++i)
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

int main()
{
    // String_C a;
    // StrInput(&a);
    // StrPrint(a);
}
