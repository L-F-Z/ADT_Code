    pc->next = (pa=!La) ? pa : pb; 

    Status ListTraverse_C(LinkList_C L, Status (*visit)(ElemType*))
{
    //依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
    if (ListEmpty_C(L) == TRUE)	 
        return ERROR;
    int i = 0;
    while (i <= ListLength_C(L) && visit(L + i) == OK)
        i++;
    if(i > ListLength_C(L)) return OK;
    else return ERROR;
}//ListTraverse_C
//todo: 复杂度太高 by AW

