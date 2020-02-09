//
//  cLinkList.h
//  单链表
//
//  Created by WuTao on 2020/2/1.
//  Copyright © 2020 WuTao. All rights reserved.
//

#ifndef cLinkList_h
#define cLinkList_h
#include <stdio.h>
#include <stdlib.h>

typedef struct CNode
{
    int data;
    struct CNode *next;
}CNode, *cLinkList;

//初始化
void initCLinkList(cLinkList &L)
{
    L = (CNode*)malloc(sizeof(CNode));
    L->next = L;
}

bool isCEmpty(cLinkList L)
{
    if (L->next == L)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void destroyCList(cLinkList &L)
{
    if (L != NULL)
    {
        CNode *p = L->next;
        CNode *u;
        L->next = NULL;
        while (p != NULL)
        {
            u = p;
            p = p->next;
            free(u);
        }
    }
}

//后插
bool insertNextCNode(CNode *p, int e)
{
    if (p == NULL)
    {
        return false;
    }
    CNode *s = (CNode*)malloc(sizeof(CNode));
    if (s == NULL)
    {
        return false;
    }
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}


bool createCList_Tail(cLinkList &L)
{
    initCLinkList(L);
    CNode *p = L;
    int x;
    scanf("%d",&x);
    while (x != 9999)
    {
        if (!insertNextCNode(p,x))
        {
            return false;
        }
        else
        {
            p = p->next;
            scanf("%d",&x);
        }
    }
    return true;
}

//打印
void print(cLinkList L)
{
    if (L != NULL)
    {
        if (isCEmpty(L))
        {
            printf("循环链表为空\n");
        }
        else
        {
            CNode *p = L->next;
            while (p != L)
            {
                printf("%d ",p->data);
                p = p->next;
            }
            printf("\n");
        }
    }
}

//循环输出n个数
void printNTimes(cLinkList L, int n)
{
    if (L!= NULL)
    {
        if (L->next == L)
        {
            printf("循环链表为空\n");
        }
        else
        {
            CNode *p = L->next;
            while (n != 0)
            {
                if (p != L)
                {
                    printf("%d ",p->data);
                    n--;
                }
                p = p->next;
            }
            printf("\n");
        }
    }
}

void printAndDelMin(cLinkList &L)
{
    if (!isCEmpty(L))
    {
        CNode *p, *pre, *minp, *minpre;
        while (!isCEmpty(L))
        {
            p = L->next;
            pre = L;
            minp = p;
            minpre = pre;
            while (p != L)//遍历一遍找到最小值
            {
                if (p->data < minp->data)
                {
                    minp = p;
                    minpre = pre;
                }
                pre = pre->next;
                p = p->next;
            }
            //将最小值结点删除
            printf("%d ",minp->data);
            minpre->next = minp->next;
            free(minp);
        }
        printf("\n");
    }
}
#endif /* cLinkList_h */
