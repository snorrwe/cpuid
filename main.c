#include "queries.h"

#include <stdio.h>

int main(void)
{
    puts("============================= Cache Information =============================");
    query_caches();
    puts("=========================== Extension Information ===========================");
    query_extensions();
}
