//TRIPLET
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
typedef int ElemType;         //三元组存储的数据类型
typedef ElemType *Triplet;    //由InitTriplet分配3个元素储存空间
//-----------------------------

//---------|FuncList|----------
Status InitTriplet(Triplet*, ElemType, ElemType, ElemType);
    //构造三元组，依次置T的3个元素的初值为v1,v2和v3;
Status DestroyTriplet(Triplet*);
    //销毁三元组T
Status Get(Triplet, int, ElemType*);
    //用e返回T的第i元的值
Status Put(Triplet*, int, ElemType);
    //置T的第i元的值为e
Status IsAscending(Triplet);
    //如果T的三个元素按升序排序，则返回1，否则返回0
Status IsDescending(Triplet);
    //如果T的三个元素按降序排序，则返回1，否则返回0
Status Max(Triplet, ElemType*);
    //用e返回指向T的最大元素的值
Status Min(Triplet, ElemType*);
    //用e返回指向T的最小元素的值
Status PrintTriplet(Triplet);
    //打印三元组T
//-----------------------------

int main()
{
    return 0;
}

//-----------------------------
Status InitTriplet(Triplet *T, ElemType v1, ElemType v2, ElemType v3)
{
    //构造三元组，依次置T的3个元素的初值为v1,v2和v3;
    *T = (ElemType *)malloc(3 * sizeof(ElemType)); //分配3个元素的储存空间
    if(!*T) exit(OVERFLOW);                        //分配储存空间失败
    (*T)[0] = v1; (*T)[1] = v2; (*T)[2] = v3;
    return OK;
}//InitTriplet

Status DestroyTriplet(Triplet *T)
{
    //销毁三元组T
    free(*T);
    *T = NULL;
    return OK;
}//DestroyTriplet

Status Get(Triplet T, int i, ElemType *e)
{
    //用e返回T的第i元的值
    //i的合法值为1<=i<=3
    if(i < 1 || i > 3) return ERROR;
    *e = T[i - 1];
    return OK;
}//Get

Status Put(Triplet *T, int i, ElemType e)
{
    //置T的第i元的值为e
    //i的合法值为1<=i<=3
    if(i < 1 || i > 3) return ERROR;
    (*T)[i - 1] = e;
    return OK;
}//Put

Status IsAscending(Triplet T)
{
    //如果T的三个元素按升序排序，则返回1，否则返回0
    return (T[0] <= T[1]) && (T[1] <= T[2]);
}//IsAscending

Status IsDescending(Triplet T)
{
    //如果T的三个元素按降序排序，则返回1，否则返回0
    return (T[0] >= T[1]) && (T[1] >= T[2]);
}//IsDescending

Status Max(Triplet T, ElemType *e)
{
    //用e返回指向T的最大元素的值
    *e = (T[0] >= T[1]) ?
            ((T[0] >= T[2]) ? T[0] :T[2]):
            ((T[1] >= T[2]) ? T[1] :T[2]);
    return OK;
}//Max

Status Min(Triplet T, ElemType *e)
{
    //用e返回指向T的最小元素的值
    *e = (T[0] <= T[1]) ?
            ((T[0] <= T[2]) ? T[0] :T[2]):
            ((T[1] <= T[2]) ? T[1] :T[2]);
    return OK;
}//Min

Status PrintTriplet(Triplet T)
{
    //打印三元组T
    int i;
    for(i = 0; i < 3; i++)
        printf("%d\t", T[i]); //issue: Should Depend on the ElemType
    printf("\n");
}