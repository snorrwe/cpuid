//! SEE: https://en.wikipedia.org/wiki/CPUID

#include "queries.h"

#include <assert.h>
#include <stdio.h>

union bx {
    unsigned e;
    struct {
        unsigned fsgsbase : 1;
        unsigned ia32_tsc_adjust : 1;
        unsigned sgx : 1;
        unsigned bmi1 : 1;
        unsigned hle : 1;
        unsigned avx2 : 1;
        unsigned fdp_excptn_only : 1;
        unsigned smep : 1;
        unsigned bmi2 : 1;
        unsigned erms : 1;
        unsigned invpcid : 1;
        unsigned rtm : 1;
        unsigned pqm : 1;
        unsigned fpu_cs_deprecated_ : 1;
        unsigned mpx : 1;
        unsigned pqe : 1;
        unsigned avx512_f : 1;
        unsigned avx512_dq : 1;
        unsigned rdseed : 1;
        unsigned adx : 1;
        unsigned smap : 1;
        unsigned avx512_ifma : 1;
        unsigned pcommit : 1;
        unsigned clflushopt : 1;
        unsigned clwb : 1;
        unsigned intel_pt : 1;
        unsigned avx512_pf : 1;
        unsigned avx512_er : 1;
        unsigned avx512_cd : 1;
        unsigned sha : 1;
        unsigned avx512_bw : 1;
        unsigned avx512_vl : 1;
    } b;
};

union cx {
    unsigned e;
    struct {
        unsigned prefetchwt1 : 1;
        unsigned avx512_vbmi : 1;
        unsigned umip : 1;
        unsigned pku : 1;
        unsigned ospke : 1;
        unsigned waitpkg : 1;
        unsigned avx512_vbmi2 : 1;
        unsigned cet_ss : 1;
        unsigned gfni : 1;
        unsigned vaes : 1;
        unsigned vpclmulqdq : 1;
        unsigned avx512_vnni : 1;
        unsigned avx512_bitalg : 1;
        // reserved bit
        unsigned res1_ : 1;
        unsigned avx512_vpopcntdq : 1;
        // reserved bit
        unsigned res2_ : 1;
        unsigned five_l_paging : 1;
        unsigned mawau : 5;
        unsigned rdpid : 1;
        // reserved bit
        unsigned res3_ : 1;
        // reserved bit
        unsigned res4_ : 1;
        unsigned cldemote : 1;
        // reserved bit
        unsigned res5_ : 1;
        unsigned MOVDIRI : 1;
        unsigned MOVDIR64B : 1;
        unsigned ENQCMD : 1;
        unsigned sgx_lc : 1;
        unsigned pks : 1;
    } b;
};

static inline void bx_print(union bx bx)
{
    printf("Access to base of %%fs and %%gs: %d\n", bx.b.fsgsbase);
    printf("IA32_TSC_ADJUST: %d\n", bx.b.ia32_tsc_adjust);
    printf("Software Guard Extensions: %d\n", bx.b.sgx);
    printf("Bit Manipulation Instruction Sets#BMI: %d\n", bx.b.bmi1);
    printf("Transactional Synchronization Extension: %d\n", bx.b.hle);
    printf("Advanced Vector Extensions 2: %d\n", bx.b.avx2);
    printf("FDP_EXCPTN_ONLY: %d\n", bx.b.fdp_excptn_only);
    printf("Supervisor Mode Execution Prevention: %d\n", bx.b.smep);
    printf("Bit Manipulation Instruction Sets: %d\n", bx.b.bmi2);
    printf("Enhanced REP MOVSB/STOSB: %d\n", bx.b.erms);
    printf("INVPCID instruction: %d\n", bx.b.invpcid);
    printf("Transactional Synchronization Extension: %d\n", bx.b.rtm);
    printf("Platform Quality of Service Monitoring: %d\n", bx.b.pqm);
    printf("FPU CS and FPU DS deprecated: %d\n", bx.b.fpu_cs_deprecated_);
    printf("Intel MPX (Memory Protection Extensions): %d\n", bx.b.mpx);
    printf("Platform Quality of Service Enforcement: %d\n", bx.b.pqe);
    printf("AVX-512 Foundation: %d\n", bx.b.avx512_f);
    printf("AVX-512 Doubleword and Quadword Instructions: %d\n", bx.b.avx512_dq);
    printf("RDSEED instruction: %d\n", bx.b.rdseed);
    printf("Intel ADX (Multi-Precision Add-Carry Instruction Extensions): %d\n", bx.b.adx);
    printf("Supervisor Mode Access Prevention: %d\n", bx.b.smap);
    printf("AVX-512 Integer Fused Multiply-Add Instructions: %d\n", bx.b.avx512_ifma);
    printf("PCOMMIT instruction: %d\n", bx.b.pcommit);
    printf("CLFLUSHOPT instruction: %d\n", bx.b.clflushopt);
    printf("CLWB instruction: %d\n", bx.b.clwb);
    printf("Intel Processor Trace: %d\n", bx.b.intel_pt);
    printf("AVX-512 Prefetch Instructions: %d\n", bx.b.avx512_pf);
    printf("AVX-512 Exponential and Reciprocal Instructions: %d\n", bx.b.avx512_er);
    printf("AVX-512 Conflict Detection Instructions: %d\n", bx.b.avx512_cd);
    printf("Intel SHA extensions: %d\n", bx.b.sha);
    printf("AVX-512 Byte and Word Instructions: %d\n", bx.b.avx512_bw);
    printf("AVX-512 Vector Length Extensions: %d\n", bx.b.avx512_vl);
}

static inline void cx_print(union cx cx)
{
    printf("PREFETCHWT1 instruction: %d\n", cx.b.prefetchwt1);
    printf("AVX-512 Vector Bit Manipulation Instructions: %d\n", cx.b.avx512_vbmi);
    printf("User-mode Instruction Prevention: %d\n", cx.b.umip);
    printf("Memory Protection Keys for User-mode pages: %d\n", cx.b.pku);
    printf("PKU enabled by OS: %d\n", cx.b.ospke);
    printf("Timed pause and user-level monitor/wait: %d\n", cx.b.waitpkg);
    printf("AVX-512 Vector Bit Manipulation Instructions 2: %d\n", cx.b.avx512_vbmi2);
    printf("Control flow enforcement (CET) shadow stack: %d\n", cx.b.cet_ss);
    printf("Galois Field instructions: %d\n", cx.b.gfni);
    printf("Vector AES instruction set (VEX-256/EVEX): %d\n", cx.b.vaes);
    printf("CLMUL instruction set (VEX-256/EVEX): %d\n", cx.b.vpclmulqdq);
    printf("AVX-512 Vector Neural Network Instructions: %d\n", cx.b.avx512_vnni);
    printf("AVX-512 BITALG instructions: %d\n", cx.b.avx512_bitalg);
    printf("AVX-512 Vector Population Count Double and Quad-word: %d\n", cx.b.avx512_vpopcntdq);
    printf("Intel 5-level paging: %d\n", cx.b.five_l_paging);
    printf("Read Processor ID and IA32_TSC_AUX: %d\n", cx.b.rdpid);
    printf("Cache line demote: %d\n", cx.b.cldemote);
    printf("MOVDIRI: %d\n", cx.b.MOVDIRI);
    printf("MOVDIR64B: %d\n", cx.b.MOVDIR64B);
    printf("Enqueue Stores: %d\n", cx.b.ENQCMD);
    printf("SGX Launch Configuration: %d\n", cx.b.sgx_lc);
    printf("Protection keys for supervisor-mode pages: %d\n", cx.b.pks);
}

void query_extensions(void)
{
    unsigned ax, dx;
    union bx bx;
    union cx cx;

    ax = 0x7;
    cx.e = 0;
    cpuid(&ax, &bx.e, &cx.e, &dx);

    bx_print(bx);
    cx_print(cx);
}
