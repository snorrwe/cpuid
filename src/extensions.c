//! SEE: https://en.wikipedia.org/wiki/CPUID

#include "queries.h"

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
        unsigned res1_ : 1; // reserved bit
        unsigned avx512_vpopcntdq : 1;
        unsigned res2_ : 1; // reserved bit
        unsigned five_l_paging : 1;
        unsigned mawau : 5;
        unsigned rdpid : 1;
        unsigned res3_ : 1; // reserved bit
        unsigned res4_ : 1; // reserved bit
        unsigned cldemote : 1;
        unsigned res5_ : 1; // reserved bit
        unsigned MOVDIRI : 1;
        unsigned MOVDIR64B : 1;
        unsigned ENQCMD : 1;
        unsigned sgx_lc : 1;
        unsigned pks : 1;
    } b;
};

union dx {
    unsigned e;
    struct {
        unsigned res0_ : 2;                  //reserved
        unsigned avx512_4vnniw : 1;          // AVX-512 4-register Neural Network Instructions
        unsigned avx512_4fmaps : 1;          // AVX-512 4-register Multiply Accumulation Single precision
        unsigned fsrm : 1;                   // Fast Short REP MOVSB
        unsigned res1_ : 3;                  //reserved
        unsigned avx512_vp2intersect : 1;    // AVX-512#New instructions in AVX-512 VP2INTERSECT|AVX-512 VP2INTERSECT Doubleword and Quadword Instructions
        unsigned SRBDS_CTRL : 1;             // Special Register Buffer Data Sampling Mitigations
        unsigned md_clear : 1;               // VERW instruction clears CPU buffers
        unsigned res2_ : 2;                  //reserved
        unsigned tsx_force_abort : 1;        //
        unsigned SERIALIZE : 1;              // Serialize instruction execution
        unsigned Hybrid : 1;                 //
        unsigned TSXLDTRK : 1;               // TSX suspend load address tracking
        unsigned pconfig : 1;                // Platform configuration (Memory Encryption Technologies Instructions)
        unsigned lbr : 1;                    // Architectural Last Branch Records
        unsigned cet_ibt : 1;                // Control flow enforcement (CET) indirect branch tracking
        unsigned res3_ : 1;                  // reserved
        unsigned amx_bf16 : 1;               // Tile computation on bfloat16 numbers
        unsigned amx_tile : 1;               // Tile architecture
        unsigned amx_int8 : 1;               // Tile computation on 8-bit integers
        unsigned spec_ctrl : 1;              // Speculation Control
        unsigned stibp : 1;                  // Single Thread Indirect Branch Predictor
        unsigned l1d_flush : 1;              // IA32_FLUSH_CMD MSR
        unsigned ia32_arch_capabilities : 1; // Speculative Side Channel Mitigations<ref name="Intel_2018_SESEM"/>
        unsigned ia32_core_capabilities : 1; // Support for a MSR listing model-specific core capabilities
        unsigned ssbd : 1;                   // Speculative Store Bypass Disable,<ref name="Intel_2018_SESEM"/> as mitigation for Speculative Store Bypass  (IA32_SPEC_CTRL)

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

static inline void dx_print(union dx dx)
{
    printf("reserved: %d\n", dx.b.res0_);
    printf("AVX-512 4-register Neural Network Instructions: %d\n", dx.b.avx512_4vnniw);
    printf("AVX-512 4-register Multiply Accumulation Single precision: %d\n", dx.b.avx512_4fmaps);
    printf("Fast Short REP MOVSB: %d\n", dx.b.fsrm);
    printf("reserved: %d\n", dx.b.res1_);
    printf("AVX-512#New instructions in AVX-512 VP2INTERSECT|AVX-512 VP2INTERSECT Doubleword and Quadword Instructions: %d\n", dx.b.avx512_vp2intersect);
    printf("Special Register Buffer Data Sampling Mitigations: %d\n", dx.b.SRBDS_CTRL);
    printf("VERW instruction clears CPU buffers: %d\n", dx.b.md_clear);
    printf("reserved: %d\n", dx.b.res2_);
    printf("tsx_force_abort : %d\n", dx.b.tsx_force_abort);
    printf(" Serialize instruction execution: %d\n", dx.b.SERIALIZE);
    printf("Hybrid : %d\n", dx.b.Hybrid);
    printf("TSX suspend load address tracking: %d\n", dx.b.TSXLDTRK);
    printf("Platform configuration (Memory Encryption Technologies Instructions): %d\n", dx.b.pconfig);
    printf("Architectural Last Branch Records: %d\n", dx.b.lbr);
    printf("Control flow enforcement (CET) indirect branch tracking: %d\n", dx.b.cet_ibt);
    printf("reserved: %d\n", dx.b.res3_);
    printf("Tile computation on bfloat16 numbers: %d\n", dx.b.amx_bf16);
    printf("Tile architecture: %d\n", dx.b.amx_tile);
    printf("Tile computation on 8-bit integers: %d\n", dx.b.amx_int8);
    printf("Speculation Control: %d\n", dx.b.spec_ctrl);
    printf("Single Thread Indirect Branch Predictor: %d\n", dx.b.stibp);
    printf("IA32_FLUSH_CMD MSR: %d\n", dx.b.l1d_flush);
    printf("Speculative Side Channel Mitigations: %d\n", dx.b.ia32_arch_capabilities);
    printf("Support for a MSR listing model-specific core capabilities: %d\n", dx.b.ia32_core_capabilities);
    printf("Speculative Store Bypass Disable as mitigation for Speculative Store Bypass  (IA32_SPEC_CTRL): %d\n", dx.b.ssbd);
}

void query_extensions(void)
{
    unsigned ax;
    union bx bx;
    union cx cx;
    union dx dx;

    ax = 0x7;
    cx.e = 0;
    cpuid(&ax, &bx.e, &cx.e, &dx.e);

    bx_print(bx);
    cx_print(cx);
    dx_print(dx);
}
