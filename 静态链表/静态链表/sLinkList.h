#ifndef sLinkList_h
#define sLinkList_h
#define MAXSIZE 20

typedef struct SNode
{
    int data;
    int next;
}sLinkList[MAXSIZE];

typedef int ptr;

void initSLinkList(sLinkList L)
{
    L[0].next = -1;//-1表示后继为空
    for (int i = 1; i < MAXSIZE; i++)
    {
        L[i].next = -2;//-2表示当前位置未分配
    }
}

//按位序插入
bool insertSLinkList(sLinkList L, int i, int e)
{
    if (i > MAXSIZE)
    {
        return false;
    }
    int j = 0;
    ptr p = 0;
    while (p != -1 && j < i - 1)
    {
        p = L[p].next;
    }
    if (p == -1)
    {
        return false;//位序不合法
    }
    
    return true;
}
#endif /* sLinkList_h */
