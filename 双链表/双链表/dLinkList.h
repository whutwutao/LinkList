//
//  dLinkList.h
//  双链表
//
//  Created by WuTao on 2020/1/29.
//  Copyright © 2020 WuTao. All rights reserved.
//

#ifndef dLinkList_h
#define dLinkList_h
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode
{
    int data;
    int freq;
    struct DNode* prior;//前驱
    struct DNode* next;//后继
}DNode, *dLinkList, *cdLinkList;

bool initDList(dLinkList &L)
{
    L = (DNode*)malloc(sizeof(DNode));
    if (L == NULL)
    {
        return false;
    }
    L->next = NULL;
    L->prior = NULL;
    return true;
}

bool initCDList(cdLinkList &L)
{
    L = (DNode*)malloc(sizeof(DNode));
    if (L == NULL)
    {
        return false;
    }
    L->next = L;
    L->prior = L;
    return true;
}
bool isEmpty(dLinkList L)
{
    if (L->next == NULL)
    {
        return true;
    }
    return false;
}

//释放非循环双链表
void destroyDList(dLinkList &L)
{
    if (L != NULL)
    {
        DNode *p = L;
        while (p != NULL)
        {
            p = p->next;
            free(L);
            L = p;
        }
    }
}

//释放循环双链表
void destroyCDList(dLinkList &L)
{
    if (L != NULL)
    {
        DNode *p = L;
        //将尾结点的后继指针置为空，否则循环没有终点
        L->prior->next = NULL;
        while (p != NULL)
        {
            p = p->next;
            free(L);
            L = p;
        }
    }
}
//后插，用于非循环双链表
bool insertNextNode(DNode *p, int e)
{
    DNode *q = (DNode*)malloc(sizeof(DNode));
    q->data = e;
    q->freq = 0;
    q->next = p->next;
    q->prior = p;
    p->next = q;
    if (q->next != NULL)
    {
        q->next->prior = q;
    }
    return true;
}

//后插，用于循环双链表
bool insertCNextNode(DNode *p, int e)
{
    DNode *q = (DNode*)malloc(sizeof(DNode));
    q->data = e;
    q->next = p->next;
    q->prior = p;
    p->next = q;
    q->next->prior = q;
    return true;

}

//删除p结点的后继结点
bool deleteNextNode(DNode *p)
{
    if (p == NULL || p->next == NULL)
    {
        return false;
    }
    else
    {
        DNode *q = p->next;//q指向p的后继结点
        p->next = q->next;
        if (q->next != NULL)//p的后继结点不为最后一个结点
        {
            q->next->prior = p;
        }
        free(q);
        return true;
    }
}

//尾插法建立双链表
bool createDList_Tail(dLinkList &L)
{
    initDList(L);
    DNode *p = L;
    int x;
    scanf("%d",&x);
    while (x != 9999)
    {
        if (!insertNextNode(p,x))
        {
            return false;
        }
        else
        {
            p = p->next;
        }
        scanf("%d",&x);
    }
    return true;
}

void printDList(dLinkList L)
{
    DNode *p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
//尾插法建立循环双链表
bool createCDList_Tail(cdLinkList &L)
{
    initCDList(L);
    DNode *p = L;
    int x;
    scanf("%d",&x);
    while (x != 9999)
    {
        if (!insertCNextNode(p,x))
        {
            return false;
        }
        else
        {
            p = p->next;
        }
        scanf("%d",&x);
    }
    return true;
}

//从头结点的后继结点开始依次输出
void printR(cdLinkList L)
{
    DNode *p = L->next;
    while (p != L)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

//从头结点的前驱结点开始依次输出
void printL(cdLinkList L)
{
    DNode *p = L->prior;
    while (p != L)
    {
        printf("%d ",p->data);
        p = p->prior;
    }
    printf("\n");
}

//判断循环双链表是否对称
bool isSymmertry(cdLinkList L)
{
    DNode *pl = L->prior;
    DNode *pr = L->next;
    while (pl != pr && pr->next != pl)
    {
        if (pl->data == pr->data)
        {
            pl = pl->prior;
            pr = pr->next;
        }
        else
        {
            return false;
        }
    }
    return true;
}

//王道书2020版40页第20题
DNode* Locate(dLinkList &L, int x)
{
    DNode *p = L->next;
    while (p->data != x && p != NULL)
    {
        p = p->next;
    }
    if (p == NULL)//找不到值为x的结点，返回NULL
    {
        return NULL;
    }
    p->freq ++;
    DNode *q = p;
    while (q->freq <= p->freq && q != L)
    {
        q = q->prior;
    }
    p->prior->next = p->next;
    if (p->next != NULL)
    {
        p->next->prior = p->prior;
    }
    p->next = q->next;
    if (p->next != NULL)
    {
        p->next->prior = p;
    }
    p->prior = q;
    q->next = p;
    return p;
}

#endif /* dLinkList_h */
