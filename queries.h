#pragma once

void query_extensions(void);
void query_caches(void);

#ifdef __PIC__
static inline void cpuid(unsigned* restrict const a, unsigned* restrict const b, unsigned* restrict const c, unsigned* restrict const d)
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
static inline void cpuid(unsigned* restrict const a, unsigned* restrict const b, unsigned* restrict const c, unsigned* restrict const d)
{
    __asm__ __volatile__("cpuid\n\t"
                         : "+a"(*a),
                         "+b"(*b),
                         "+c"(*c),
                         "+d"(*d));
}
#endif

