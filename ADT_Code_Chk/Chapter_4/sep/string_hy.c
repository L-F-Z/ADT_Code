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
//ʹ��char[]��Ϊ�ַ��������ݽṹ, �ַ���Ҫ��ͬC����Ҫ��, ��0��β.
typedef char *String_C;
//-----------------------------
//������µı�����������ĸ��д

//---------|Constdef|----------
#define BUFSIZE 1024
//-----------------------------

//---------|FuncList|----------
//���к���Ҫ�������һ��
//д������ʱ���鷳˳�������ע��Ҳ����(Ц)

//���ƴ�
Status StrAssign(String_C *S, char *src);
Status StrInput(String_C *S);
Status StrCopy(String_C *S, String_C src);
Status StrEmpty(String_C S);
Status StrCompare(String_C S, String_C T);
Status StrLength(String_C S);
Status ClearString(String_C *S);
Status Concat(String_C *dist, String_C S1, String_C S2);
Status SubString(String_C *dist, String_C S, int pos, int len);

//����
Status Index(String_C S, String_C T, int pos);
Status Replace(String_C *S, String_C T, String_C V);
Status StrInsert(String_C *S, int pos, String_C T);
Status StrDelete(String_C *S, int pos, int len);
Status DestoryString(String_C *S);

//����
Status StrPrint(String_C S);
Status Index_KMP(String_C S, String_C C, int pos);
//���Դ���

void get_next(String_C T, int next[]);
int char_string_length(char *C);
//-----------------------------

int char_string_length(char *C) //����һ��char�ַ����ĳ���
{
    int cnt = 0;
    while (*C)
    {
        ++cnt;
        ++C;
    }
    return cnt;
}

Status StrAssign(String_C *S, char *src) //��char*�ַ�����ʼ��char*�ַ���
{
    int len = char_string_length(src);
    if (*S = (String_C)malloc(sizeof(char) * (len + 1)))
    {
        memcpy(*S, src, len + 1);
        return OK;
    }
    return ERROR;
}

Status StrInput(String_C *S)//ʹ��scanf�����ַ���
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

Status StrPrint(String_C S)//��ӡ�ַ���
{
    printf("%s", S);
    return OK;
}

int next[BUFSIZE];

void get_next(String_C T, int next[]){
    //��ģʽ��T��next����ֵ����������next
    int i, j = 0, l = char_string_length(T);
    next[0] = 0;
    for(i = 1; i < l;++i)
    {
        while (j > 0 && T[i] != T[j]) j = next[j - 1];
        if (T[i] == T[j]) ++j;
        next[i] = j;
    }
}//get_next

int Index_KMP(String_C S, String_C T,int pos){
    //����ģʽ��T��next������T������S��pos���ַ�֮���λ�õ�
    //  KMP�㷨�����У�T�ǿգ�0<=pos<=StrLength(S) - 1
    int i = pos,  j = 0, ls = char_string_length(S), lt = char_string_length(T);
    get_next(T, next);
    for(i = 0;i < ls;++i)
    {
        while(j > 0 && T[j] != S[i]) j = next[j - 1];
        if (T[j] == S[i]) ++j;
        if (j == lt) return i - lt + 1;
    }
    return -1;
}//Index_KMP

//for debug
int main()
{
    /*
    String_C a;
    StrInput(&a);
    StrPrint(a);
    StrAssign(&a, "2333333");
    StrPrint(a);*/

    String_C a ,b;
    StrInput(&a);
    StrInput(&b);
    printf("%d",Index_KMP(a, b, 0));
}

#endif
