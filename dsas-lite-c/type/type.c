
#include "type.h"

void t_set (Type* a, Type* b) {*a = *b;}

int t_cmp(Type* a, Type* b)
{
    if (*a > *b)
        return 1;
    if (*a < *b)
        return -1;
    return 0;
}
