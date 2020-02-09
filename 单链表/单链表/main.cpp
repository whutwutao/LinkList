#include "linkList.h"
#include "cLinkList.h"
#include <iostream>
using namespace std;
int main()
{
    linkList list;
    createList_Tail(list);
//    func(list,4);
//    delDuplicateUp(list);
    printList(list);
    printf("%d\n",dc(list,length(list)));
    destroyList(list);
    return 0;
}
