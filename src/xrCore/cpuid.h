#pragma once
#ifndef _INC_CPUID
#define _INC_CPUID

#ifdef WINDOWS
#include <intrin.h>
#else // POSIX
#include <unistd.h>
#endif // WINDOWS
#include <thread>

// Features
#define _CPU_FEATURE_MMX 1<<23
#define _CPU_FEATURE_SSE 1<<25
#define _CPU_FEATURE_SSE2 1<<26
#define _CPU_FEATURE_HTT 1<<28

// Extended Features
#define _CPU_FEATURE_SSE3 1<<0
#define _CPU_FEATURE_MWAIT 1<<3
#define _CPU_FEATURE_SSSE3 1<<9
#define _CPU_FEATURE_SSE4_1 1<<19
#define _CPU_FEATURE_SSE4_2 1<<20

IC void nativeCpuId( unsigned int i, unsigned int regs[4] )
{
#ifdef WINDOWS
  __cpuid( (int *)regs, (int)i );
#elif defined(LINUX)
  asm volatile("cpuid" :
              "=eax" (regs[0]),
              "=ebx" (regs[1]),
              "=ecx" (regs[2]),
              "=edx" (regs[3])
              : "eax" (i));
#else
#error Cpuid is not implemented
#endif
}

struct _processor_info
{
    char v_name[13]; // vendor name
    char model_name[49]; // Name of model eg. Intel_Pentium_Pro

    unsigned char family; // family of the processor, eg. Intel_Pentium_Pro is family 6 processor
    unsigned char model; // model of processor, eg. Intel_Pentium_Pro is model 1 of family 6 processor
    unsigned char stepping; // Processor revision number

    unsigned int feature; // processor Feature ( same as return value).

    unsigned int n_cores; // number of available physical cores
    unsigned int n_threads; // number of available logical threads

    unsigned int affinity_mask; // recommended affinity mask
    // all processors available to process
    // except 2nd (and upper) logical threads
    // of the same physical core
};

int _cpuid(_processor_info*);

#endif
