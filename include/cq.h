#pragma once
#include <stdio.h>

#if !defined(__x86_64__) && !defined(__x86__)
#error Only x86 architectures are supported!
#endif

/**
 * From Table 3-17 of Volume 2 of the Intel SDM
 */
enum cq_cache_type {
    CQ_TYPE_NULL = 0,
    CQ_TYPE_DATA = 1,
    CQ_TYPE_INST = 2,
    CQ_TYPE_UNIF = 3,
    CQ_TYPE_MAX = 4,
};

const char* cq_cache_type_str(enum cq_cache_type ty);

struct cq_cache_info {
    int cache_idx;
    unsigned cache_size;
    enum cq_cache_type type;
    unsigned lvl : 3;
    unsigned linesz_ml : 12;
    unsigned parts_ml : 10;
    unsigned ways_ml : 10;
};

void cq_extensions(void);
/**
 * Returns cache_idx = -1 if the cache was not found
 */
struct cq_cache_info cq_cache(int cache_idx);
void cq_print_cache_info(FILE* out, struct cq_cache_info const* info);
void cq_cpuinfo(void);

#ifdef __PIC__
static inline void cq_cpuid(unsigned* restrict const a, unsigned* restrict const b, unsigned* restrict const c, unsigned* restrict const d)
{
    __asm__ __volatile__("xchg %%ebx, %1\n\t"
                         "cpuid\n\t"
                         "xchg %1, %%ebx\n\t"
                         : "+a"(*a),
                         "+b"(*b),
                         "+c"(*c),
                         "+d"(*d));
}
#else
static inline void cq_cpuid(unsigned* restrict const a, unsigned* restrict const b, unsigned* restrict const c, unsigned* restrict const d)
{
    __asm__ __volatile__("cpuid\n\t"
                         : "+a"(*a),
                         "+b"(*b),
                         "+c"(*c),
                         "+d"(*d));
}
#endif
