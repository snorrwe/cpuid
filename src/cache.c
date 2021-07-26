#include "queries.h"

#include <stdio.h>

/**
     * From Table 3-17 of Volume 2 of the Intel SDM
     */
enum cache_type {
    TYPE_NULL = 0,
    TYPE_DATA = 1,
    TYPE_INST = 2,
    TYPE_UNIF = 3,
    TYPE_MAX = 4,
};

static const char* const type_str[TYPE_MAX] = {
    [TYPE_NULL] = "NULL",
    [TYPE_DATA] = "DATA",
    [TYPE_INST] = "INST",
    [TYPE_UNIF] = "UNIF",
};

union ax {
    unsigned e;
    /**
     * From table 3-17
     */
    struct cache {
        unsigned type : 5;
        unsigned lvl : 3;
    } b;
};

union bx {
    unsigned e;
    /**
     * From table 3-17
     */
    struct cache_sz {
        unsigned linesz_ml : 12;
        unsigned parts_ml : 10;
        unsigned ways_ml : 10;
    } b;
};

void query_caches(void)
{
    unsigned cache_idx = 0;

    while (1) {
        const char* const units[] = { "  B", "KiB", "MiB", "GiB", NULL };

        union ax ax;
        union bx bx;
        unsigned cx, dx, cache_sz;
        const char* const* unit_str;

        ax.e = 0x4;
        cx = cache_idx;
        cpuid(&ax.e, &bx.e, &cx, &dx);

        if (ax.b.type == TYPE_NULL) {
            break;
        }

        cache_sz = (bx.b.ways_ml + 1) * (bx.b.parts_ml + 1) * (bx.b.linesz_ml + 1) * (cx + 1);

        unit_str = &units[0];
        while (cache_sz >= 1024) {
            if (*(unit_str + 1) == NULL) {
                break;
            }
            cache_sz /= 1024;
            ++unit_str;
        }

        printf("(index %d) %3d%s L%d %s [Line Size: %dB]\n", cache_idx, cache_sz, *unit_str, ax.b.lvl, type_str[ax.b.type], bx.b.linesz_ml + 1);
        ++cache_idx;
    }
}
