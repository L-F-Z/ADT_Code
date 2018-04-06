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

Status StrAssign(String_C *S, char *src);
Status StrInput(String_C *S);
Status StrCopy(String_C *S, String_C *T);
Status StrEmpty(String_C S);
Status StrCompare(String_C S, String_C T); 
Status StrLength(String_C S);
Status ClearString(String_C *S);
Status Concat(String_C *dist, String_C S1, String_C S2);
Status SubString(String_C *dist, String_C S, int pos, int len);



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


Status StrAssign(String_C *S, char *src)
//生成一个其值等于串常量scr的串S 
{
    int len = char_string_length(src);
    if (*S = (String_C)malloc(sizeof(char) * (len + 1)))
    {
        memcpy(*S, src, len + 1);
        return OK;
    }
    return ERROR;
}

Status StrInput(String_C *S)
//使用scanf创建字符串
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

Status StrCopy(String_C *S, String_C *T)
//由串S复制得串T 
{
	int len = StrLength(*S);
	int i = 0;
	
    for(i=0;i<len;i++) 
	{
		T[i] = S[i];
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
	
	for(i=0;i<len_S&&i<len_T;++i)
	{
		if (S[i]!=T[i])
		return S[i]-T[i];
	}
	return len_S-len_T;
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


Status Concat(String_C dist, String_C S1, String_C S2)
//用dist返回由S1和S2联接而成的新串
{
	int len_S1 = StrLength(S1);
	int len_S2 = StrLength(S2);
		
	free(dist);  
    if(!(dist = (char*)malloc((len_S1+len_S2)*sizeof(char))))  
        exit(OVERFLOW);  
        
	int i = 0;
	int j = 0;
	while(i<=len_S1)
	{
		dist[j++] = S1[i++];
	}
	i = 0;
	while(i<=len_S2)
	{
		dist[j++] = S2[i++];
	}
	return OK;

} 




Status SubString(String_C dist, String_C S, int pos, int len)
//用dist返回串S的第pos个字符起长度为len的子串 
{
	int len_S = StrLength(S);
	int i=pos;
		
	if(len_S<=0||pos<=0||len<=0)
	return ERROR;
	else
	{
		for(i==pos;i<pos+len;i++)
		{
			dist[i-pos] = S[i];
		}
	}
	return OK;
} 

Status StrPrint(String_C S)//打印字符串
{
    printf("%s\n", S);
    return OK;
}


//Debug
int main()
{
	String_C a,b,c,d,e,f;
	
    StrInput(&a);
    StrPrint(a);
    
    StrAssign(&b, "2333333");
    StrAssign(&c, "111111");
    StrAssign(&d, "222222222");
    StrAssign(&e, "33333");
    StrPrint(b);
    
    StrCopy(&a,&c);
    StrPrint(c);

    
    //printf("%d\n",StrEmpty(a));   
    //ClearString(&a);
    
	Concat(d, a, b);
    StrPrint(d);
    
    //StrCompare(a, b);
    
    SubString(e, a, 2, 3);
    StrPrint(e);
} 

#endif