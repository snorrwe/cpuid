#include "queries.h"

#include <stdio.h>

int main(void)
{
    puts("\n============================= Cache Information =============================\n");
    query_caches();
    puts("\n============================== Processor Info ===============================\n");
    query_cpuinfo();
    puts("\n=========================== Extension Information ===========================\n");
    query_extensions();
}
