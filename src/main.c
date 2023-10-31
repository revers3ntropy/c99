#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "lexer.h"
#include "ds/list.h"
 
int main() {
//  char *processed = processFile("src/lexer.h");
//  free(processed);

    // test the linked list 
    list_t *list_t = listInitialise();
    int a = 2;
    int b = 2;
    int c = 3;
    appendItem(list, &a);
    appendItem(list, &b);
    appendItem(list, &c);
    printList(list);
    removeTail(list);
    printList(list);
    prependItem(list, &c);
    printList(list);
    freeList(list);

    return 0;
}
