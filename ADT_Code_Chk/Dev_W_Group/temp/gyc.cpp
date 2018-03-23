void MergeList_C(LinkList_C La, LinkList_C Lb, LinkList_C Lc, int (*compare)(ElemType, ElemType));
{
    //已知单循环链表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的单循环链表Lc，Lc的元素也按值非递减排列
    LinkList pa, pb, pc;
    pa = La->next; pb = Lb->next; pc = La;   
    Lc = La;                        //用La的头结点作为Lc的头结点

    while(pa!=La && pb!=Lb)
    {
        if(compare(pa->data, pb->data) < 0)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    
    while(pa!=La || pb!=Lb)
    pc->next = (pa=!La) ? pa : pb; 
    
	pc->next = Lc; 
    
    free(Lb);
    return Lc;
}//MergeList_C


Status ListTraverse_C(LinkList_C L, Status (*visit)(ElemType*));
{
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    if (ListEmpty_C(L) == TRUE)	 
        return ERROR;
    while(i <= ListLength_C(L) && visit(L + i) == OK)
        i++;
    if(i > ListLength_C(L)) return OK;
    else return ERROR;
}//ListTraverse_C


Status PrintList_C(LinkList_C L);
{
    //打印单循环链表L
    LinkList p;
    p = L->next;
    while(p!=L)
	{
    	printf("%d ",p->data);
    	p = p->next;
	}
	printf("\n");
}//PrintList_C 
