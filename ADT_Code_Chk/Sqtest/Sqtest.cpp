#include<bits/stdc++.h>
using namespace std;

ofstream outfile0;
ofstream outfile1;
ofstream outfile2;
ofstream outfile3;
ofstream outfile4;
ofstream outfile5;
ofstream outfile6;
ofstream outfile7;
ofstream outfile8;

/*
    测试说明：
        测试函数不包括DestoryList_Sq/MergeList_Sq
        ListTraverse_Sq暂只测试*2和/2功能(详见mul2)

    命令格式：
    函数 参数1 参数2 ...
    
    输出文件
    State:表示函数返回的Status，不返回时默认为OK
    Ans:表示函数返回的答案，不返回时默认为0
    version0，version1:交替输出整个队列
    (带std的表示利用C++标准库重写的顺序表)


    函数对应：
    "Init"   InitList_Sq
    "Clear"  ClearList_Sq
    "Empty"  ListEmpty_Sq
    "Length" ListLength_Sq
    "Get"    GetElem_Sq
    "Locate" LocateElem_Sq
    "Prior"  PriorElem_Sq
    "Next"   NextElem_Sq
    "Insert" ListInsert_Sq
    "Delete" ListDelete_Sq
    "Travel" ListTraverse_Sq

*/
//数字与命令对照表
//----------|Test|-------------
#define Init        0
#define Clear       1
#define Empty       2
#define Length      3
#define Get         4
#define Locate      5
#define Prior       6
#define Next        7
#define Insert      8
#define Delete      9
#define Travel      10
//-----------------------------

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
#define LIST_INIT_SIZE 100    //顺序表存储空间的初始分配量
#define LISTINCREMENT   10    //顺序表存储空间的分配增量
typedef int ElemType;         //顺序表存储的数据类型
struct SqList{
    ElemType  *elem;          //储存空间基址
    int       length;         //当前长度
    int       listsize;       //当前分配的储存容量(以sizeof(ElemType)为单位)
};
//-----------------------------

//---------|FuncList|----------
Status InitList_Sq(struct SqList*);
    //构造一个空的顺序表L
Status DestroyList_Sq(struct SqList*);
    //销毁顺序表L
void ClearList_Sq(struct SqList*);
    //将L重置为空表
Status ListEmpty_Sq(struct SqList*);
    //判断L是否为空表
int ListLength_Sq(struct SqList*);
    //返回L中数据元素的个数
Status GetElem_Sq(struct SqList*, int, ElemType*);
    //用e返回L中第i个数据元素的值
int compare(ElemType, ElemType);
    //元素的比较函数
int LocateElem_Sq(struct SqList*, ElemType, int (*compare)(ElemType, ElemType));
    //在顺序顺序表L中查找第1个值与e满足compare()的元素的位序
Status PriorElem_Sq(struct SqList*, ElemType, ElemType*);
    //返回cur_e的前驱节点pre_e
Status NextElem_Sq(struct SqList*, ElemType, ElemType*);
    //返回cur_e的后继节点next_e
Status ListInsert_Sq(struct SqList*, int, ElemType);
    //在顺序表L中第i个位置之前插入新的元素e
Status ListDelete_Sq(struct SqList*, int, ElemType*);
    //在顺序表L中删除第i个元素，并用e返回其值
void MergeList_Sq(struct SqList*, struct SqList*, struct SqList*, int (*compare)(ElemType, ElemType));
    //已知顺序表La和Lb的元素按值非递减排列
Status ListTraverse_Sq(struct SqList*, Status (*visit)(ElemType*));
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status PrintList_Sq(struct SqList*);
    //打印顺序表L
//-----------------------------

SqList List;
list<ElemType> stdList;
int version = 0;
//当前版本
//操作前后的队列数据会分别存在std0,std1和my0,my1中,version为当次操作后将输入的文件序号

int ComCount = 0;
//已执行命令数

int StateNow;
int StateStdNow;
int AnsNow;
int AnsStdNow;

//输出到State文件中
void printState(Status state)
{
    StateNow = state;

    outfile1 << state << endl;

}

//输出到stdState文件中
void printstdState(Status state)
{
    StateStdNow = state;

    outfile2 << state << endl;
}

//输出到ans文件中
void printAns(int x)
{
    AnsNow = x;

    outfile3 << x << endl;

}

//输出到stdans文件中
void printstdAns(int x)
{
    AnsStdNow = x;

    outfile4 << x << endl;
}


//遍历表操作时所用函数
Status mul2(ElemType *a)
{
    if (a == NULL) return ERROR;
    if (*a > 200) (*a)/=2;
        else (*a)*=2;
    return OK;
}

//执行命令
//分别执行顺序表函数和利用C++标准库中的链表list模拟顺序表函数(以后测试可以使用多个线性表互相对照，由于格式统一，方便很多)
bool execute(int x)
{
    int y, wz; ElemType ans = 0,number;
    bool flag;
    switch(x){
        case Init:
            printState(InitList_Sq(&List));
            printstdState(OK);
            printAns(0);
            printstdAns(0);
            break;
        case Clear:
            printState(OK);
            printstdState(OK);
            printAns(0);
            printstdAns(0);
            break;
        case Empty:
            printState(OK);
            printstdState(OK);
            printAns(ListEmpty_Sq(&List));
            printstdAns(stdList.empty());
            break;
        case Length:
            printState(OK);
            printstdState(OK);
            printAns(ListLength_Sq(&List));
            printstdAns(stdList.size());
            break;
        case Get:
            scanf("%d",&y);
            ans = 0;
            printState(GetElem_Sq(&List, y, &ans));
            printstdState((y >= 1 && y <= stdList.size())? OK : ERROR);
            printAns(ans);
            wz = 1;
            if (y >= 1 && y <= stdList.size())
            {
                int wz = 1;
                for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
                {
                    if (wz == y)
                    {
                        printstdAns(*iter);
                        break;
                    }else ++wz;
                }

            }else printstdAns(0);
            break;
        case Locate:
            scanf("%d",&y);
            printState(OK);
            printstdState(OK);
            printAns(LocateElem_Sq(&List, y, compare));
            flag = false;
            wz = 1;
            for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
            {
                if (*iter == y)
                {
                    flag = true;
                    break;
                }
                else
                    ++wz;
            }
            if (!flag) printstdAns(0);
                else printstdAns(wz);
            break;
        case Prior:
            scanf("%d",&y);
            ans = 0;
            printState(PriorElem_Sq(&List, y ,&ans));
            printAns(ans);
            flag = false;
            wz = 1;
            for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
            {
                if (*iter == y)
                {
                    flag = true;
                    break;
                }
                else
                    ++wz;
            }

            if (!flag || wz < 2){
                printstdState(ERROR);
                printstdAns(0);
            }else{
                printstdState(OK);
                {
                    --wz;
                    int wz2 = 1;
                    for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
                    {
                        if (wz2 == wz)
                        {
                            printstdAns(*iter);
                            break;
                        }else ++wz2;
                    }
                }
            }
            break;
        case Next:
            ans = 0;
            scanf("%d",&y);
            printState(NextElem_Sq(&List, y ,&ans));
            printAns(ans);

            wz = 1;
            flag = false;
            for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
            {
                if (*iter == y)
                {
                    flag = true;
                    break;
                }
                else
                    ++wz;
            }

            if (!flag || wz >= stdList.size()){
                printstdState(ERROR);
                printstdAns(0);
            }else{
                printstdState(OK);
                {
                    ++wz;
                    int wz2 = 1;
                    for(list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
                    {
                        if (wz2 == wz)
                        {
                            printstdAns(*iter);
                            break;
                        }else ++wz2;
                    }
                }
            }
            break;
        case Insert:
            scanf("%d%d",&y,&number);
            printState(ListInsert_Sq(&List, y, number));
            printAns(0);
            wz = 1;
            if (y >= 1 && y <= stdList.size() + 1)
            {
                printstdState(OK);
                if (y == stdList.size() + 1)
                {
                    stdList.insert(stdList.end(),number);
                }else
                for (list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
                {
                    if (wz == y)
                    {
                        stdList.insert(iter,number);
                        break;
                    }else ++wz;
                }
            }else printstdState(ERROR);
            printstdAns(0);
            break;
        case Delete:
            ans = 0;
            scanf("%d",&y);
            printState(ListDelete_Sq(&List, y, &ans));
            printAns(ans);
            wz = 1;
            if (y >= 1 && y <= stdList.size())
            {
                for (list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
                {
                    if (wz == y)
                    {
                        printstdAns(*iter);
                        stdList.erase(iter);
                        break;
                    }else ++wz;
                }
                printstdState(OK);
            }else printstdState(ERROR), printstdAns(0);
            break;
        case Travel:
            printState(ListTraverse_Sq(&List, mul2));
            printAns(0);
            for (list<int>::iterator iter = stdList.begin();iter != stdList.end();iter++)
                if (*iter > 200)
                    *iter /= 2;
                else
                    *iter *= 2;
            printstdState(stdList.empty() ? ERROR : OK);
            printstdAns(0);
            break;
    }
    if (version == 0)
    {
        //输出到version0
        outfile5 << List.length << endl;
        for(int i = 0;i < List.length;++i)
            outfile5 << List.elem[i] << " ";
        outfile5 << endl;
    }else{
        //输出到version1
        outfile7 << List.length << endl;
        for(int i = 0;i < List.length;++i)
            outfile7 << List.elem[i] << " ";
        outfile7 << endl;
    }


    if (version == 0)
    {
        //输出到versionstd0
        outfile6 << stdList.size() << endl;
        for (list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
            outfile6 << *iter << " ";
        outfile6 << endl;
    }else{
        //输出到versionstd1 
        outfile8 << stdList.size() << endl;
        for (list<int>::const_iterator iter = stdList.begin();iter != stdList.end();iter++)
            outfile8 << *iter << " ";
        outfile8 << endl;
    }

    if (stdList.size() != List.length)
        return false;
    list<int>::const_iterator iter = stdList.begin();
    for(int i = 0;i < List.length;++iter,++i)
    {
        //对比当前队列，不一样则返回false
        if (*iter != List.elem[i])
            return false;
    }

    //对比当前State和ans，不一样则返回false
    if (StateNow != StateStdNow)
        return false;
    if (AnsNow != AnsStdNow)
        return false;

    return true;
}

int main()
{
    int n;
    //文件流
    freopen("Sqtest.in","r",stdin);
    outfile1.open("State.txt");
    outfile2.open("stdState.txt");
    outfile3.open("ans.txt");
    outfile4.open("stdans.txt");
    outfile5.open("version0.txt");
    outfile6.open("versionStd0.txt");
    outfile7.open("version1.txt");
    outfile8.open("versionStd1.txt");
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if (!execute(x))
        {
            //如果执行返回false,即出现不一致，则输出出现错误的命令数，以及最新的队列在version0还是version1中，并退出程序
            outfile0.open("Log.txt");
            outfile0 << "ERROR IN COM " << ComCount + 1 << "\nNow The Version Is " << version << endl;
            outfile0.close();
            outfile1.close();
            outfile2.close();
            outfile3.close();
            outfile4.close();
            outfile5.close();
            outfile6.close();
            outfile7.close();
            outfile8.close();
            return 0;
        }
        //0->1 1->0
        version^=1;
        //已执行命令数+1
        ++ComCount;
    }
    outfile1.close();
    outfile2.close();
    outfile3.close();
    outfile4.close();
    outfile5.close();
    outfile6.close();
    outfile7.close();
    outfile8.close();

    return 0;
}

//-----------------------------
Status InitList_Sq(struct SqList *L)
{
    //构造一个空的顺序表L
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;

    return OK;
}//InitList_Sq

Status DestroyList_Sq(struct SqList *L)
{
    //销毁顺序表L
    if(!L->listsize) return ERROR; //已是空表
    free(L->elem);
    L->length = 0;
    L->listsize = 0;
    return OK;
}//DestroyList_Sq

void ClearList_Sq(struct SqList *L)
{
    //将L重置为空表
    L->length = 0;
}//ClearList_Sq

Status ListEmpty_Sq(struct SqList *L)
{
    //判断L是否为空表
    if(L->length == 0)
        return TRUE;
    else return FALSE;
}//ListEmpty_Sq

int ListLength_Sq(struct SqList *L)
{
    //返回L中数据元素的个数
    return L->length;
}//ListLength_Sq

Status GetElem_Sq(struct SqList *L, int i, ElemType *e)
{
    //用e返回L中第i个数据元素的值
    //i的合法值为1<=i<=ListLength_Sq(L)
    if((i < 1) || (i > L->length)) return ERROR; //i值不合法
    *e = L->elem[i - 1];
    return OK;
}//GetElem_Sq

int compare(ElemType a, ElemType b)
{
    //元素的比较函数
    return a-b;
}

int LocateElem_Sq(struct SqList *L, ElemType e, int (*compare)(ElemType, ElemType))
{
    //在顺序顺序表L中查找第1个值与e满足compare()的元素的位序
    //若找到，则返回其在L中的位序，否则返回0
    ElemType *p;
    int i = 1;    //i的初值为第1个元素的位序
    p = L->elem;   //p的初值为第1个元素的储存位置
    while(i <= L->length && (*compare)(*p++, e)) ++i;
    if(i <= L->length) return i;
    else return 0;
}//LocateElem_Sq

Status PriorElem_Sq(struct SqList *L, ElemType cur_e, ElemType *pre_e)
{
    //返回cur_e的前驱节点pre_e
    int Location;
    Location = LocateElem_Sq(L, cur_e, compare);
    if(Location < 2) return ERROR;
    else *pre_e = L->elem[Location - 2];
    return OK;
}//PriorElem_Sq

Status NextElem_Sq(struct SqList *L, ElemType cur_e, ElemType *next_e)
{
    //返回cur_e的后继节点next_e
    int Location;
    Location = LocateElem_Sq(L, cur_e, compare);
    if(Location == 0 || Location == L->length) return ERROR;
    else *next_e = L->elem[Location];
    return OK;
}//NextElem_Sq

Status ListInsert_Sq(struct SqList *L, int i, ElemType e)
{
    //在顺序表L中第i个位置之前插入新的元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
    ElemType *newbase, *q, *p;
    if(i < 1 || i > L->length+1) return ERROR; //i值不合法
    if(L->length >= L->listsize)
    {
        newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);           //储存分配失败
        L->elem = newbase;                     //新基址
        L->listsize += LISTINCREMENT;          //增加储存容量
    }
    q = &(L->elem[i-1]);                       //q为插入地址
    for(p = &(L->elem[L->length-1]); p >= q; --p)
        *(p + 1) = *p;                         //插入位置及之后的元素右移
    *q = e;                                    //插入e
    L->length++;                               //表长增1
    return OK;
}//ListInsert_Sq

Status ListDelete_Sq(struct SqList *L, int i, ElemType *e)
{
    //在顺序表L中删除第i个元素，并用e返回其值
    //i的合法值为1<=i<=ListLength_Sq(L)
    ElemType *p, *q;
    if((i < 1) || (i > L->length)) return ERROR; //i值不合法
    p = &(L->elem[i - 1]);                       //p为被删除元素的位置
    *e = *p;                                    //被删除元素的值赋给e
    q = L->elem + L->length - 1;                  //表尾元素的位置
    for(++p; p <= q; ++p) *(p-1) = *p;          //被删除元素之后的元素左移
    L->length--;                                 //表长减1
    return OK;
}//ListDelete_Sq

void MergeList_Sq(struct SqList *La, struct SqList *Lb, struct SqList *Lc, int (*compare)(ElemType, ElemType))
{
    //已知顺序表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的顺序表Lc，Lc的元素也按值非递减排列
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    Lc->listsize = La->length + Lb->length;
    Lc->length = La->length + Lb->length;
    Lc->elem = (ElemType*)malloc(Lc->listsize * sizeof(ElemType));
    if(!Lc->elem) exit(OVERFLOW);
    pa = La->elem; pb = Lb->elem; pc = Lc->elem;
    pa_last = La->elem + La->length - 1;
    pb_last = Lb->elem + Lb->length - 1;
    while(pa <= pa_last && pb <= pb_last)//归并
    {
        if((*compare)(*pa, *pb) < 0)
            *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while(pa <= pa_last) *pc++ = *pa++; //插入La剩余元素
    while(pb <= pb_last) *pc++ = *pb++; //插入Lb剩余元素
}//MergeList_Sq

Status ListTraverse_Sq(struct SqList *L, Status (*visit)(ElemType*))
{
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    int i = 0;
    if (ListEmpty_Sq(L) == TRUE)
        return ERROR;
    while(i < L->length && visit(L->elem + i) == OK)
        i++;
    if(i >= L->length) return OK;
    else return ERROR;
}

Status PrintList_Sq(struct SqList *L)
{
    //打印顺序表L
    int i;
    for(i = 0; i < L->length; i++)
        printf("%d\t", *(L->elem + i));
    printf("\n");
}
