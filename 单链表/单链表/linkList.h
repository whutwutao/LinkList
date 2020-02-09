#ifndef linkList_h
#define linkList_h
#include <stdlib.h>
#include <stdio.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *linkList;


bool initList(linkList &L)
{
    L = (LNode*)malloc(sizeof(LNode));//C语言
//    L = new LNode;//C++
    if (L == NULL)
    {
        return false;
    }
    L->next = NULL;
    return true;
}

//释放链表所占内存空间
void destroyList(linkList &L)
{
    if (L != NULL)
    {
        LNode *p = L;
        while(p != NULL)
        {
            p = p->next;
            free(L);
            L = p;
        }
    }
}

//判空
bool isEmpty(linkList L)
{
    if (L->next == NULL)
    {
        return true;
    }
    return false;
}

//按位序插入
bool insertList(linkList &L, int i, int e)
{
    if (i < 1)
    {
        return false;
    }
    LNode *p = L;
    int j = 0;
    while(j < i - 1 && p != NULL)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
    {
        return false;
    }
    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//指定结点的后插操作
bool insertNextNode(LNode *p, int e)
{
    if (p == NULL)
    {
        return false;
    }
    LNode *s = (LNode*)malloc(sizeof(LNode));
    if (s == NULL)
    {
        return false;
    }
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//指定结点的前插操作
bool insertPriorNode(LNode *p, int e)
{
    if (p == NULL)
    {
        return false;
    }
    LNode *s = (LNode*)malloc(sizeof(LNode));
    if (s == NULL)
    {
        return false;
    }
    s->data = p->data;
    s->next = p->next;
    p->data = e;
    p->next = s;
    return true;
}

//按位序删除结点
bool deleteIndex(linkList &L, int i, int &e)
{
    if (i < 1)
    {
        return false;
    }
    LNode *p = L;
    int j = 0;
    while (p != NULL && j < i - 1)//找到第i-1个结点
    {
        p = p->next;
        j++;
    }
    if (p == NULL)//位序i不合法
    {
        return false;
    }
    LNode *s = p->next;//s指向第i个结点
    p->next = s->next;//第i-1个结点的next指向第i+1个结点
    e = s->data;
    free(s);//释放第i个结点的空间
    return true;
}

//删除指定结点，此方法有bug，当指定的结点p为链表最后一个结点时会出错
bool deleteNode(LNode *p)
{
    if (p == NULL)
    {
        return false;
    }
    LNode *q = p->next;//s指向p的后继结点
    p->data = q->data;//将p的后继结点的数据与p的交换
    p->next = q->next;
    free(q);//将p的后继结点释放
    return true;
}

//按位查找
LNode* getElem(linkList L, int i)
{
    if (i < 0)
    {
        return NULL;
    }
    int j = 0;
    LNode *p = L;
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

//按值查找
LNode* locateElem(linkList L, int e)
{
    if (L == NULL)
    {
        return NULL;
    }
    LNode *p = L->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;
}

//求长度
int length(linkList L)
{
    int len = 0;
    LNode *p = L;
    while (p->next != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

//尾插法建立单链表
linkList createList_Tail(linkList &L)
{
    initList(L);//初始化单链表
    int x;
    LNode *p;
    p = L;
    scanf("%d",&x);
    while (x != 9999)
    {
        insertNextNode(p,x);//在尾结点的后面插入一个结点
        p = p->next;//将p移到插入的结点，作为新的尾结点
        scanf("%d",&x);
    }
    return L;
}

//头插法建立单链表
linkList createList_Head(linkList &L)
{
    initList(L);
    int x;
    scanf("%d",&x);
    while (x != 9999)
    {
        insertNextNode(L,x);
        scanf("%d",&x);
    }
    return L;
}

//单链表的就地逆置，辅助空间复杂度为O(1)
linkList reverse(linkList &L)
{
    if (length(L) < 2)
    {
        return L;
    }
    LNode *p = L->next, *r = NULL;//p指向第一个结点
    L->next = NULL;//将头结点从链表中取下
    //用头插法，将不带头结点的链表的各结点依次插入
    while (p!= NULL)
    {
        r = p->next;//将p->next保存
        p->next = L->next;
        L->next = p;
        p = r;
    }
    return L;
}

//打印单链表
void printList(linkList L)
{
    if (isEmpty(L))
    {
        printf("链表为空\n");
    }
    else
    {
        LNode *p = L->next;
        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
    return;
}


//按从小到大输出
void printInOrder(linkList L)
{
    if (!isEmpty(L))
    {
        while (!isEmpty(L))
        {
            LNode *p = L->next;//遍历链表的指针
            LNode *pre = L;//遍历链表指针的前驱指针
            LNode *minp = p;//最小值结点指针
            LNode *minpre = pre;//最小值结点前驱指针
            while (p != NULL)//找到最小值结点以及其前驱结点
            {
                //如果当前结点的值小于当前最小值结点的值，则将最小值指针
                //指向当前指针，最小值前驱指针指向当前的前驱指针
                if (minp->data > p->data)
                {
                    minpre = pre;
                    minp = p;
                }
                //当前指针及其前驱指针向后移，以遍历链表
                pre = pre->next;
                p = p->next;
            }
            printf("%d ",minp->data);
            //将最小值结点删除
            minpre->next = minp->next;
            free(minp);
        }
        printf("\n");
    }
}

//反向输出链表中的元素
void printR(linkList L)
{
    if (!isEmpty(L))
    {
        int a[length(L)];
        int i = 0;
        for (LNode *p = L->next; p != NULL; p = p->next)
        {
            a[i++] = p->data;
        }
        i--;
        for (; i >= 0; i--)
        {
            printf("%d ",a[i]);
        }
    }
}


//用递归方法删除链表中值为x的结点，用于不带头结点的单链表
void delX(linkList &L, int x)
{
    if (L == NULL)
    {
        return;
    }
    if (L->data == x)
    {
        LNode *p = L;
        L = L->next;
        free(p);
        delX(L, x);
    }
    else
    {
        delX(L->next, x);
    }
}

//非递归方法删除值为x的结点
void del(linkList &L, int x)
{
    if (!isEmpty(L))
    {
        LNode *p = L;//指向要删除结点的前驱结点
        LNode *q = L->next;//指向要删除的结点
        while (q != NULL)
        {
            if (q->data == x)
            {
                p->next = q->next;
                free(q);
                q = p->next;
            }
            else
            {
                q = q->next;
                p = p->next;
            }
        }
    }
}

//删除链表中值最小的结点
void delMin(linkList &L)
{
    if (!isEmpty(L))
    {
        LNode *p = L->next;//遍历链表的指针
        LNode *pre = L;//遍历链表指针的前驱指针
        LNode *minp = p;//最小值结点指针
        LNode *minpre = pre;//最小值结点前驱指针
        while (p != NULL)//找到最小值结点以及其前驱结点
        {
            //如果当前结点的值小于当前最小值结点的值，则将最小值指针
            //指向当前指针，最小值前驱指针指向当前的前驱指针
            if (minp->data > p->data)
            {
                minpre = pre;
                minp = p;
            }
            //当前指针及其前驱指针向后移，以遍历链表
            pre = pre->next;
            p = p->next;
        }
        //将最小值结点删除
        minpre->next = minp->next;
        free(minp);
    }
}

//将链表中元素按大小递增顺序排序
linkList sort(linkList &L)
{
    if (length(L) < 2)
    {
        return L;
    }
    LNode *q = L->next->next;//q指向原链表的第2个结点
    LNode *r = NULL;
    L->next->next = NULL;//将链表的头结点和第1个结点从链表中取下
    while (q != NULL)
    {
        LNode *p = L->next;//p指向结果链表的第一个结点
        LNode *pre = L;//pre指向p的前驱结点
        //找到第一个值比q->data大的结点
        while (p->data <= q->data && p != NULL)
        {
            p = p->next;
            pre = pre->next;
        }
        r = q->next;//r记录q的后继结点
        //将q结点插到pre后面
        q->next = pre->next;
        pre->next = q;
        q = r;
    }
    return L;
}

//寻找两个链表的所有公共结点
linkList commonNode(linkList L1, linkList L2)
{
    int len1 = length(L1);//表L1的长度
    int len2 = length(L2);//表L2的长度
    int diff;//表长之差
    linkList longList = NULL,shortList = NULL;
    if (len1 > len2)
    {
        longList = L1;
        shortList = L2;
        diff = len1 - len2;
    }
    else
    {
        longList = L2;
        shortList = L1;
        diff = len2 - len1;
    }
    while (diff--)//较长表先遍历diff个结点
    {
        longList = longList->next;
    }
    while (longList != NULL && shortList != NULL)//两表同时遍历
    {
        if (longList == shortList)
        {
            return longList;
        }
        else
        {
            longList = longList->next;
            shortList = shortList->next;
        }
    }
    return NULL;
}

//将链表拆分成两个带头结点的链表，分别存放位序为奇数和偶数的元素，且相对顺序不变
linkList split(linkList &L1)
{
    linkList L2 = (linkList)malloc(sizeof(LNode));
    L2->next = NULL;
    LNode *p = L1->next;//p指向L1的第一个结点
    LNode *tail1, *tail2, *r;
    tail1 = L1;//L1的尾结点
    tail2 = L2;//L2的尾结点
    L1->next = NULL;//将L1的头结点从链表中取下
    int i = 1;
    while (p != NULL)
    {
        if (i % 2 != 0)
        {
            r = p->next;
            tail1->next = p;
            p->next = NULL;
            tail1 = tail1->next;
            p = r;
        }
        else
        {
            r = p->next;
            tail2->next = p;
            p->next = NULL;
            tail2 = tail2->next;
            p = r;
        }
        i++;
    }
    return L2;
}

//将链表分解成两个带头结点的单链表L1,L2，分别保存位序为奇数和偶数的元素，且L2中元素顺序与原来的相反
linkList split1(linkList &L1)
{
    linkList L2 = (linkList)malloc(sizeof(LNode));
    L2->next = NULL;
    LNode *p = L1->next;
    L1->next = NULL;
    LNode *tail = L1, *r = NULL;
    int i = 1;
    while (p != NULL)
    {
        if (i % 2 != 0)
        {
            r = p->next;
            tail->next = p;
            p->next = NULL;
            tail = tail->next;
            p = r;
        }
        else//用头插法建立L2
        {
            r = p->next;
            p->next = L2->next;
            L2->next = p;
            p = r;
        }
        i++;
    }
    return L2;
}

//删去链表中多余的重复元素，链表为一般链表
void delDuplicate(linkList &L)
{
    if (length(L) > 1)
    {
        LNode *p = L->next;
        LNode *pdel, *predel;
        while (p->next != NULL)
        {
            pdel = p->next;
            predel = p;
            while (pdel != NULL)
            {
                if (pdel->data == p->data)
                {
                    predel->next = pdel->next;
                    free(pdel);
                    pdel = predel->next;
                }
                else
                {
                    pdel = pdel->next;
                    predel = predel->next;
                }
            }
            p = p->next;
            if (p == NULL)//因为在一次循环中删除结点之后可能导致p == NULL
            {
                break;
            }
        }
    }
}

//删除链表中多余的重复元素，链表为升序排列
//链表为升序排列，故重复的元素一定两两相邻，故只需遍历链表考察相邻结点，若有重复则删除后面一个结点
void delDuplicateUp(linkList L)
{
    if (L != NULL && length(L) > 1)
    {
        LNode *p = L->next;
        LNode *q;
        while (p->next != NULL)
        {
            q = p->next;
            if (p->data == q->data)
            {
                p->next = q->next;
                free(q);
            }
            else
            {
                p = p->next;
            }
        }
    }
}

//将两个按递增次序排列的单链表归并成一个按递减次序排列的单链表
void merge(linkList &L1, linkList &L2)
{
    LNode *p1 = L1->next;
    LNode *p2 = L2->next;
    LNode *r = NULL;
    L1->next = NULL;
    L2->next = NULL;
    free(L2);//将L2的头结点释放掉
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data < p2->data)
        {
            r = p1->next;
            p1->next = L1->next;
            L1->next = p1;
            p1 = r;
        }
        else
        {
            r = p2->next;
            p2->next = L1->next;
            L1->next = p2;
            p2 = r;
        }
    }
    while (p1 != NULL)
    {
        r = p1->next;
        p1->next = L1->next;
        L1->next = p1;
        p1 = r;
    }
    while (p2 != NULL)
    {
        r = p2->next;
        p2->next = L1->next;
        L1->next = p2;
        p2 = r;
    }
}


//将两个递增有序链表L1,L2的交集放在L1中,采用归并的思想,设两个指针指向两表的第一个结点,比较两结点元
//素大小，若相等则将p1所指结点插入到结果表的尾部，将p2所指结点释放，若不等则将值小的结点释放
void common(linkList &L1, linkList &L2)
{
    LNode *p1 = L1->next;
    LNode *p2 = L2->next;
    L1->next = NULL;
    L2->next = NULL;
    free(L2);//释放L2的头结点
    LNode *tail = L1;
    LNode *r = NULL, *u = NULL;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data == p2->data)
        {
            //将p1所指结点插到结果链表的尾部
            r = p1->next;
            tail->next = p1;
            tail = p1;
            p1->next = NULL;
            p1 = r;
            //释放p2所指结点
            u = p2;
            p2 = p2->next;
            free(u);
        }
        else if (p1->data < p2->data)
        {
            //释放p1结点
            //p1向后移
            u = p1;
            p1 = p1->next;
            free(u);
        }
        else
        {
            //释放p2结点
            //p2向后移
            u = p2;
            p2 = p2->next;
            free(u);
        }
    }
    while (p1 != NULL)
    {
        //释放空间
        u = p1;
        p1 = p1->next;
        free(u);
    }
    while (p2 != NULL)
    {
        //释放空间
        u = p2;
        p2 = p2->next;
        free(u);
    }
}


//两个整数序列A = a1,a2,a3 ... am 和 B = b1,b2,b3,b4 ... bn
//已经存入单链表中，设计一个算法，判断序列B是否是序列A的连续子序列
bool isSub(linkList A, linkList B)
{
    LNode *pa = A->next;
    LNode *pb = B->next;
    while (pa != NULL && pb != NULL)
    {
        LNode *r = pa->next;//保存开始扫描处的后继，本次匹配失败时，作为下一次识别的起点
        if (pa->data == pb->data)//相等则两个指针同时后移，匹配下一个结点
        {
            pa = pa->next;
            pb = pb->next;
        }
        else//不等则pa指向刚刚开始点的后继结点，pb回到B的首元素，重新匹配
        {
            pa = r;
            pb = B->next;
        }
    }
    if (pb == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//输出倒数第n个元素
int getBackN(linkList L, int n)
{
    LNode *p,*q;
    p = L->next;
    q = L->next;
    int k = 1;
    while (k < n && q != NULL)//先将q指向链表的第n个元素
    {
        q = q->next;
        k ++;
    }
    if (q == NULL)//n的大小比表长大
    {
        return 0;
    }
    else
    {
        while (q->next != NULL)
        {
            q = q->next;
            p = p->next;
        }
        printf("倒数第%d个元素的值为：%d\n",n,p->data);
        return 1;
    }
}

int search_k(linkList list, int k)
{
    LNode *p = list->next, *q = list->next;
    int count = 0;
    while (p != NULL)
    {
        if (count < k)
        {
            count ++;
        }
        else
        {
            q = q->next;
        }
        p = p->next;
    }
    if (count < k)
    {
        return 0;
    }
    else
    {
        printf("%d\n",q->data);
        return 1;
    }
}

//王道书2020版第40页第23题
void func(linkList L, int n)
{
    int a[n+1];
    for (int i = 1; i < n + 1; i++)
    {
        a[i] = 0;
    }
    LNode *p = L->next;
    LNode *pre = L;
    while (p != NULL)
    {
        int m = p->data > 0 ? p->data : -p->data;
        if (a[m] == 0)
        {
            a[m] = 1;
            p = p->next;
            pre = pre->next;
        }
        else
        {
            LNode *r = p->next;
            pre->next = r;
            free(p);
            p = r;
        }
    }
}

//王道书2020版第66页第4题
bool dc(linkList L, int n)
{
    char s[n/2];//符号栈，保存链表的前一半结点的值
    LNode *p = L->next;
    for (int i = 0; i < n/2; i ++)
    {
        s[i] = p->data;
        p = p->next;
    }
    if (n % 2 != 0)
    {
        p = p->next;
    }
    int i = n/2 - 1;
    while (i >= 0 && p != NULL)
    {
        if (s[i] == p->data)
        {
            i--;
            p = p->next;
        }
        else
        {
            break;
        }
    }
    if (i == -1)
        return true;
    else
        return false;
}
#endif /* linkList_h */
