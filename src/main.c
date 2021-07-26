#include "queries.h"

#include <stdio.h>

int main(void)
{
    puts("============================= Cache Information =============================");
    query_caches();
    puts("============================== Processor Info ===============================");
    query_cpuinfo();
    puts("=========================== Extension Information ===========================");
    query_extensions();
}
