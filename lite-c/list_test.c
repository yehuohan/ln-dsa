
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct test {
    int             value;
    char*           text;
    list_node_t     node;
} test_t;

#define to_test(ln) _node_to_struct(ln, test_t, node)

int main(void) {
    test_t test;
    list_init(&test.node);

    for (int k = 0; k < 10; k ++) {
        test_t* pt = (test_t*)malloc(sizeof(test_t));
        pt->value = k;
        pt->text = "text";
        list_add_next(&test.node, &pt->node);
    }

    list_node_t* ln = test.node.next;
    while (ln != &test.node) {
        test_t* t = to_test(ln);
        printf("%d, %s\n", t->value, t->text);
        ln = ln->next;
    }
    
    return 0;
}
