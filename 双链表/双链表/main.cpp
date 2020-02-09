#include "dLinkList.h"
#include <iostream>
using namespace std;
int main(int argc, const char * argv[])
{
//    cdLinkList list = NULL;
//    createCDList_Tail(list);
//    printL(list);
//    printR(list);
//    cout << isSymmertry(list) << endl;
    dLinkList list;
    createDList_Tail(list);
    printDList(list);
    Locate(list,2);
    Locate(list,3);
    Locate(list,3);
    Locate(list,2);
    Locate(list,2);
    Locate(list,5);
    printDList(list);
    destroyDList(list);
    return 0;
}
