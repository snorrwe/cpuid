#include "cq.h"

#include <stdio.h>

int main(void)
{
    puts("\n============================= Cache Information =============================\n");
    unsigned cache_idx = 0;
    while (1) {
        struct cq_cache_info info = cq_cache(cache_idx);
        if (info.cache_idx < 0) {
            break;
        }
        cq_print_cache_info(stdout, &info);
        ++cache_idx;
    }
    puts("\n============================== Processor Info ===============================\n");
    cq_cpuinfo();
    puts("\n=========================== Extension Information ===========================\n");
    cq_extensions();
}
