/*
 * cpuinfo_x86
 * Displays information about a "modern" x86 processor.
 * Amit Singh <http://osxbook.com>
 *
 * Reuses code from the Mac OS X kernel.
 *
 * ***********
 * Originally from http://www.osxbook.com/blog/2009/03/02/retrieving-x86-processor-information/ 
 * Resurrected via http://www.osxbook.com/blog/2009/03/02/retrieving-x86-processor-information/ 
 * Modified by Xeno Kovah for ost2.fyi Arch2001 class 2021
 * ***********
 * Compilation: gcc -o cpuinfo cpuid.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <stdint.h>

typedef enum { eax, ebx, ecx, edx } cpuid_register_t;

static inline void cpuid(uint32_t* data)
{
    asm(
        "pushq %%rbx       \n"
        "cpuid             \n"
        "movl  %%ebx, %%esi\n"
        "popq  %%rbx       \n"
      : "=a"   (data[eax]),
        "=S"   (data[ebx]),
        "=c"   (data[ecx]),
        "=d"   (data[edx])
      : "a"    (data[eax]),
        "S"    (data[ebx]),
        "c"    (data[ecx]),
        "d"    (data[edx]));
}

static inline void do_cpuid(uint32_t selector, uint32_t* data)
{
    asm(
        "pushq %%rbx       \n"
        "cpuid             \n"
        "movl  %%ebx, %%esi\n"
        "popq  %%rbx       \n"
      : "=a"   (data[0]),
        "=S"   (data[1]),
        "=c"   (data[2]),
        "=d"   (data[3])
      : "a"    (selector)
    );
}

typedef uint32_t cpu_type_t;
typedef uint32_t cpu_subtype_t;
typedef uint32_t cpu_threadtype_t;

#if defined(__x86_64__)
typedef uint32_t boolean_t;
#else
typedef int32_t  boolean_t;
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define CPUID_VID_INTEL      "GenuineIntel"
#define CPUID_VID_AMD        "AuthenticAMD"
#define CPUID_STRING_UNKNOWN "Unknown CPU Type"

#define CPUID_MODEL_YONAH     14
#define CPUID_MODEL_MEROM     15
#define CPUID_MODEL_PENRYN    23
#define CPUID_MODEL_NEHALEM   26

struct {
    int model_number;
    const char* model_name;
} some_model_names[] = {
    { CPUID_MODEL_YONAH,   "Yonah"   },
    { CPUID_MODEL_MEROM,   "Merom"   },
    { CPUID_MODEL_PENRYN,  "Penryn"  },
    { CPUID_MODEL_NEHALEM, "Nehalem" },
    { -1, NULL },
};

#define _Bit(n)         (1ULL << n)
#define _HBit(n)        (1ULL << ((n) + 32))

#define min(a,b)        ((a) < (b) ? (a) : (b))
#define quad(hi,lo)     (((uint64_t)(hi)) << 32 | (lo))
#define bit(n)          (1UL << (n))
#define bitmask(h,l)    ((bit(h) | (bit(h) - 1)) & ~(bit(l) - 1))
#define bitfield(x,h,l) (((x) & bitmask(h, l)) >> l)

/*
 * When the EAX register contains a value of 1, the CPUID instruction (in
 * addition to loading the processor signature in the EAX register) loads
 * the EDX and ECX registers with the feature flags.
 */

/*
 * Feature Flag Values Reported in the EDX Register
 */
#define CPUID_FEATURE_FPU     _Bit(0)   /* Floating point unit on-chip */
#define CPUID_FEATURE_VME     _Bit(1)   /* Virtual Mode Extension */
#define CPUID_FEATURE_DE      _Bit(2)   /* Debugging Extension */
#define CPUID_FEATURE_PSE     _Bit(3)   /* Page Size Extension */
#define CPUID_FEATURE_TSC     _Bit(4)   /* Time Stamp Counter */
#define CPUID_FEATURE_MSR     _Bit(5)   /* Model Specific Registers */
#define CPUID_FEATURE_PAE     _Bit(6)   /* Physical Address Extension */
#define CPUID_FEATURE_MCE     _Bit(7)   /* Machine Check Exception */
#define CPUID_FEATURE_CX8     _Bit(8)   /* CMPXCHG8B */
#define CPUID_FEATURE_APIC    _Bit(9)   /* On-chip APIC */
#define CPUID_FEATURE_SEP     _Bit(11)  /* Fast System Call */
#define CPUID_FEATURE_MTRR    _Bit(12)  /* Memory Type Range Register */
#define CPUID_FEATURE_PGE     _Bit(13)  /* Page Global Enable */
#define CPUID_FEATURE_MCA     _Bit(14)  /* Machine Check Architecture */
#define CPUID_FEATURE_CMOV    _Bit(15)  /* Conditional Move Instruction */
#define CPUID_FEATURE_PAT     _Bit(16)  /* Page Attribute Table */
#define CPUID_FEATURE_PSE36   _Bit(17)  /* 36-bit Page Size Extension */
#define CPUID_FEATURE_PSN     _Bit(18)  /* Processor Serial Number */
#define CPUID_FEATURE_CLFSH   _Bit(19)  /* CLFLUSH Instruction Supported */
#define CPUID_FEATURE_RESV20  _Bit(20)  /* Reserved */
#define CPUID_FEATURE_DS      _Bit(21)  /* Debug Store */
#define CPUID_FEATURE_ACPI    _Bit(22)  /* Thermal Monitor and Clock Control */
#define CPUID_FEATURE_MMX     _Bit(23)  /* MMX Supported */
#define CPUID_FEATURE_FXSR    _Bit(24)  /* Fast Floating Point Save/Restore */
#define CPUID_FEATURE_SSE     _Bit(25)  /* Streaming SIMD Extensions */
#define CPUID_FEATURE_SSE2    _Bit(26)  /* Streaming SIMD Extensions 2 */
#define CPUID_FEATURE_SS      _Bit(27)  /* Self-Snoop */
#define CPUID_FEATURE_HTT     _Bit(28)  /* Hyper-Threading Technology */
#define CPUID_FEATURE_TM      _Bit(29)  /* Thermal Monitor (TM1) */
#define CPUID_FEATURE_IA64    _Bit(30)  /* Itanium Family Emulating IA-32 */
#define CPUID_FEATURE_PBE     _Bit(31)  /* Pending Break Enable */

/*
 * Feature Flag Values Reported in the ECX Register
 */
#define CPUID_FEATURE_SSE3    _HBit(0)  /* Streaming SIMD extensions 3 */
#define CPUID_FEATURE_RESVH1  _HBit(1)  /* Reserved */
#define CPUID_FEATURE_DTES64  _HBit(2)  /* 64-Bit Debug Store */
#define CPUID_FEATURE_MONITOR _HBit(3)  /* MONITOR/MWAIT */
#define CPUID_FEATURE_DSCPL   _HBit(4)  /* CPL Qualified Debug Store */
#define CPUID_FEATURE_VMX     _HBit(5)  /* Virtual Machine Extensions (VMX) */
#define CPUID_FEATURE_SMX     _HBit(6)  /* Safer Mode Extensions (SMX) */
#define CPUID_FEATURE_EST     _HBit(7)  /* Enhanced Intel SpeedStep (GV3) */
#define CPUID_FEATURE_TM2     _HBit(8)  /* Thermal Monitor 2 */
#define CPUID_FEATURE_SSSE3   _HBit(9)  /* Supplemental SSE3 Instructions */
#define CPUID_FEATURE_CID     _HBit(10) /* L1 Context ID */
#define CPUID_FEATURE_RESVH11 _HBit(11) /* Reserved */
#define CPUID_FEATURE_RESVH12 _HBit(12) /* Reserved */
#define CPUID_FEATURE_CX16    _HBit(13) /* CMPXCHG16B Instruction */
#define CPUID_FEATURE_xTPR    _HBit(14) /* Task Priority Update Control */
#define CPUID_FEATURE_PDCM    _HBit(15) /* Perfmon/Debug Capability MSR */
#define CPUID_FEATURE_RESVH16 _HBit(16) /* Reserved */
#define CPUID_FEATURE_RESVH17 _HBit(17) /* Reserved */
#define CPUID_FEATURE_DCA     _HBit(18) /* Direct Cache Access */
#define CPUID_FEATURE_SSE4_1  _HBit(19) /* Streaming SIMD Extensions 4.1 */
#define CPUID_FEATURE_SSE4_2  _HBit(20) /* Streaming SIMD Extensions 4.1 */
#define CPUID_FEATURE_xAPIC   _HBit(21) /* Extended xAPIC Support */
#define CPUID_FEATURE_MOVBE   _HBit(22) /* MOVBE Instruction */
#define CPUID_FEATURE_POPCNT  _HBit(23) /* POPCNT Instruction */
#define CPUID_FEATURE_RESVH24 _HBit(24) /* Reserved */
#define CPUID_FEATURE_RESVH25 _HBit(25) /* Reserved */
#define CPUID_FEATURE_XSAVE   _HBit(26) /* XSAVE/XSTOR States */
#define CPUID_FEATURE_OSXSAVE _HBit(27) /* OS Has Enabled XSETBV/XGETBV */
#define CPUID_FEATURE_RESVH28 _HBit(28) /* Reserved */
#define CPUID_FEATURE_RESVH29 _HBit(29) /* Reserved */
#define CPUID_FEATURE_RESVH30 _HBit(30) /* Reserved */
#define CPUID_FEATURE_RESVH31 _HBit(31) /* Reserved */

/*
 * When the EAX register contains a value of 0x80000001, the CPUID instruction
 * loads the EDX and ECX registers with extended feature flags.
 */

/*
 * Extended Feature Flag Values Reported in the EDX Register
 */
#define CPUID_EXTFEATURE_SEP   _Bit(11)  /* SYSENTER/SYSEXIT */
#define CPUID_EXTFEATURE_XD    _Bit(20)  /* eXecute Disable */
#define CPUID_EXTFEATURE_EM64T _Bit(29)  /* Extended Mem 64 Technology */

/*
 * Extended Feature Flag Values Reported in the ECX Register
 */
#define CPUID_EXTFEATURE_LAHF  _HBit(20) /* LAFH/SAHF instructions */

/*
 * When the EAX register contains a value of 2, the CPUID instruction loads
 * the EAX, EBX, ECX, and EDX registers with descriptors that indicate the
 * processor's cache and TLB characteristics.
 */

#define CPUID_CACHE_SIZE           16   /* Number of 8-bit descriptor vales */

#define CPUID_CACHE_NULL           0x00 /* NULL */
#define CPUID_CACHE_ITLB_4K_32_4   0x01 /* Inst TLB: 4K pages, 32 ents, 4-way */
#define CPUID_CACHE_ITLB_4M_2      0x02 /* Inst TLB: 4M pages, 2 ents */
#define CPUID_CACHE_DTLB_4K_64_4   0x03 /* Data TLB: 4K pages, 64 ents, 4-way */
#define CPUID_CACHE_DTLB_4M_8_4    0x04 /* Data TLB: 4M pages, 8 ents, 4-way */
#define CPUID_CACHE_DTLB_4M_32_4   0x05 /* Data TLB: 4M pages, 32 ents, 4-way */
#define CPUID_CACHE_L1I_8K         0x06 /* Icache: 8K */
#define CPUID_CACHE_L1I_16K        0x08 /* Icache: 16K */
#define CPUID_CACHE_L1I_32K        0x09 /* Icache: 32K, 4-way, 64 bytes */
#define CPUID_CACHE_L1D_8K         0x0A /* Dcache: 8K */
#define CPUID_CACHE_L1D_16K        0x0C /* Dcache: 16K */
#define CPUID_CACHE_L1D_16K_4_32   0x0D /* Dcache: 16K, 4-way, 64 byte, ECC */
#define CPUID_CACHE_L2_256K_8_64   0x21 /* L2: 256K, 8-way, 64 bytes */
#define CPUID_CACHE_L3_512K        0x22 /* L3: 512K */
#define CPUID_CACHE_L3_1M          0x23 /* L3: 1M */
#define CPUID_CACHE_L3_2M          0x25 /* L3: 2M */
#define CPUID_CACHE_L3_4M          0x29 /* L3: 4M */
#define CPUID_CACHE_L1D_32K_8      0x2C /* Dcache: 32K, 8-way, 64 byte */
#define CPUID_CACHE_L1I_32K_8      0x30 /* Icache: 32K, 8-way */
#define CPUID_CACHE_L2_128K_S4     0x39 /* L2: 128K, 4-way, sectored, 64B */
#define CPUID_CACHE_L2_192K_S6     0x3A /* L2: 192K, 6-way, sectored, 64B */
#define CPUID_CACHE_L2_128K_S2     0x3B /* L2: 128K, 2-way, sectored, 64B */
#define CPUID_CACHE_L2_256K_S4     0x3C /* L2: 256K, 4-way, sectored, 64B */
#define CPUID_CACHE_L2_384K_S6     0x3D /* L2: 384K, 6-way, sectored, 64B */
#define CPUID_CACHE_L2_512K_S4     0x3E /* L2: 512K, 4-way, sectored, 64B */
#define CPUID_CACHE_NOCACHE        0x40 /* No 2nd level or 3rd-level cache */
#define CPUID_CACHE_L2_128K        0x41 /* L2: 128K */
#define CPUID_CACHE_L2_256K        0x42 /* L2: 256K */
#define CPUID_CACHE_L2_512K        0x43 /* L2: 512K */
#define CPUID_CACHE_L2_1M_4        0x44 /* L2: 1M, 4-way */
#define CPUID_CACHE_L2_2M_4        0x45 /* L2: 2M, 4-way */
#define CPUID_CACHE_L3_4M_4_64     0x46 /* L3:  4M,  4-way, 64 bytes */
#define CPUID_CACHE_L3_8M_8_64     0x47 /* L3:  8M,  8-way, 64 bytes*/
#define CPUID_CACHE_L2_3M_12_64    0x48 /* L3:  3M,  8-way, 64 bytes*/
#define CPUID_CACHE_L2_4M_16_64    0x49 /* L2:  4M, 16-way, 64 bytes */
#define CPUID_CACHE_L2_6M_12_64    0x4A /* L2:  6M, 12-way, 64 bytes */
#define CPUID_CACHE_L2_8M_16_64    0x4B /* L2:  8M, 16-way, 64 bytes */
#define CPUID_CACHE_L2_12M_12_64   0x4C /* L2: 12M, 12-way, 64 bytes */
#define CPUID_CACHE_L2_16M_16_64   0x4D /* L2: 16M, 16-way, 64 bytes */
#define CPUID_CACHE_L2_6M_24_64    0x4E /* L2:  6M, 24-way, 64 bytes */
#define CPUID_CACHE_ITLB_32        0x4F /* Inst TLB: 32 entries */
#define CPUID_CACHE_ITLB_64        0x50 /* Inst TLB: 64 entries */
#define CPUID_CACHE_ITLB_128       0x51 /* Inst TLB: 128 entries */
#define CPUID_CACHE_ITLB_256       0x52 /* Inst TLB: 256 entries */
#define CPUID_CACHE_ITLB_4M2M_7    0x55 /* Inst TLB: 4M/2M, 7 entries */
#define CPUID_CACHE_DTLB_4M_16_4   0x56 /* Data TLB: 4M, 16 entries, 4-way */
#define CPUID_CACHE_DTLB_4K_16_4   0x57 /* Data TLB: 4K, 16 entries, 4-way */
#define CPUID_CACHE_DTLB_4K_16     0x59 /* Data TLB: 4K, 16 entries, fully */
#define CPUID_CACHE_DTLB_4M2M_32_4 0x5A /* Data TLB: 4M/2M, 32 entries */
#define CPUID_CACHE_DTLB_64        0x5B /* Data TLB: 64 entries */
#define CPUID_CACHE_DTLB_128       0x5C /* Data TLB: 128 entries */
#define CPUID_CACHE_DTLB_256       0x5D /* Data TLB: 256 entries */
#define CPUID_CACHE_L1D_16K_8_64   0x60 /* Data cache: 16K, 8-way, 64 bytes */
#define CPUID_CACHE_DTLB_4M_32_4_1GB   0x63 /* Data TLB: 4M/2M, 32 entries, 4-way + 1GB, 4 entries, 4-way */
#define CPUID_CACHE_L1D_8K_4_64    0x66 /* Data cache:  8K, 4-way, 64 bytes */
#define CPUID_CACHE_L1D_16K_4_64   0x67 /* Data cache: 16K, 4-way, 64 bytes */
#define CPUID_CACHE_L1D_32K_4_64   0x68 /* Data cache: 32K, 4-way, 64 bytes */
#define CPUID_CACHE_TRACE_12K_8    0x70 /* Trace cache 12K-uop, 8-way */
#define CPUID_CACHE_TRACE_16K_8    0x71 /* Trace cache 16K-uop, 8-way */
#define CPUID_CACHE_TRACE_32K_8    0x72 /* Trace cache 32K-uop, 8-way */
#define CPUID_CACHE_TRACE_64K_8    0x73 /* Trace cache 64K-uop, 8-way */
#define CPUID_CACHE_L2_1M_4_64     0x78 /* L2:   1M, 4-way, 64 bytes */
#define CPUID_CACHE_L2_128K_8_64_2 0x79 /* L2: 128K, 8-way, 64b, 2 lines/sec */
#define CPUID_CACHE_L2_256K_8_64_2 0x7A /* L2: 256K, 8-way, 64b, 2 lines/sec */
#define CPUID_CACHE_L2_512K_8_64_2 0x7B /* L2: 512K, 8-way, 64b, 2 lines/sec */
#define CPUID_CACHE_L2_1M_8_64_2   0x7C /* L2:   1M, 8-way, 64b, 2 lines/sec */
#define CPUID_CACHE_L2_2M_8_64     0x7D /* L2:   2M, 8-way, 64 bytes */
#define CPUID_CACHE_L2_512K_2_64   0x7F /* L2: 512K, 2-way, 64 bytes */
#define CPUID_CACHE_L2_256K_8_32   0x82 /* L2: 256K, 8-way, 32 bytes */
#define CPUID_CACHE_L2_512K_8_32   0x83 /* L2: 512K, 8-way, 32 bytes */
#define CPUID_CACHE_L2_1M_8_32     0x84 /* L2:   1M, 8-way, 32 bytes */
#define CPUID_CACHE_L2_2M_8_32     0x85 /* L2:   2M, 8-way, 32 bytes */
#define CPUID_CACHE_L2_512K_4_64   0x86 /* L2: 512K, 4-way, 64 bytes */
#define CPUID_CACHE_L2_1M_8_64     0x87 /* L2:   1M, 8-way, 64 bytes */
#define CPUID_CACHE_ITLB_4K_128_4  0xB0 /* ITLB: 4KB, 128 entries, 4-way */
#define CPUID_CACHE_ITLB_4M_4_4    0xB1 /* ITLB: 4MB, 4 entries, 4-way, or */
#define CPUID_CACHE_ITLB_2M_8_4    0xB1 /* ITLB: 2MB, 8 entries, 4-way, or */
#define CPUID_CACHE_ITLB_4M_8      0xB1 /* ITLB: 4MB, 8 entries */
#define CPUID_CACHE_ITLB_4K_64_4   0xB2 /* ITLB: 4KB, 64 entries, 4-way */
#define CPUID_CACHE_DTLB_4K_128_4  0xB3 /* DTLB: 4KB, 128 entries, 4-way */
#define CPUID_CACHE_DTLB_4K_256_4  0xB4 /* DTLB: 4KB, 256 entries, 4-way */
#define CPUID_CACHE_2TLB_4K_512_4  0xCA /* 2nd-level TLB: 4KB, 512, 4-way */
#define CPUID_CACHE_L3_512K_4_64   0xD0 /* L3: 512KB, 4-way, 64 bytes */
#define CPUID_CACHE_L3_1M_4_64     0xD1 /* L3:    1M, 4-way, 64 bytes */
#define CPUID_CACHE_L3_2M_4_64     0xD2 /* L3:    2M, 4-way, 64 bytes */
#define CPUID_CACHE_L3_1M_8_64     0xD6 /* L3:    1M, 8-way, 64 bytes */
#define CPUID_CACHE_L3_2M_8_64     0xD7 /* L3:    2M, 8-way, 64 bytes */
#define CPUID_CACHE_L3_4M_8_64     0xD8 /* L3:    4M, 8-way, 64 bytes */
#define CPUID_CACHE_L3_1M5_12_64   0xDC /* L3:  1.5M, 12-way, 64 bytes */
#define CPUID_CACHE_L3_3M_12_64    0xDD /* L3:    3M, 12-way, 64 bytes */
#define CPUID_CACHE_L3_6M_12_64    0xDE /* L3:    6M, 12-way, 64 bytes */
#define CPUID_CACHE_L3_2M_16_64    0xE2 /* L3:    2M, 16-way, 64 bytes */
#define CPUID_CACHE_L3_4M_16_64    0xE3 /* L3:    4M, 16-way, 64 bytes */
#define CPUID_CACHE_L3_8M_16_64    0xE4 /* L3:    8M, 16-way, 64 bytes */
#define CPUID_CACHE_PREFETCH_64    0xF0 /* 64-Byte Prefetching */
#define CPUID_CACHE_PREFETCH_128   0xF1 /* 128-Byte Prefetching */

#define CPUID_MWAIT_EXTENSION      _Bit(0) /* Enumeration of MWAIT Extensions */
#define CPUID_MWAIT_BREAK          _Bit(1) /* Interrupts are Break Events */

static struct {
    uint64_t    mask;
    const char* name;
} feature_map[] = {
    { CPUID_FEATURE_ACPI,    "ACPI"    },
    { CPUID_FEATURE_APIC,    "APIC"    },
    { CPUID_FEATURE_CLFSH,   "CLFSH"   },
    { CPUID_FEATURE_CMOV,    "CMOV"    },
    { CPUID_FEATURE_CID,     "CNXT-ID" },
    { CPUID_FEATURE_CX16,    "CX16"    },
    { CPUID_FEATURE_CX8,     "CX8"     },
    { CPUID_FEATURE_DCA,     "DCA"     },
    { CPUID_FEATURE_DE,      "DE"      },
    { CPUID_FEATURE_DS,      "DS"      },
    { CPUID_FEATURE_DSCPL,   "DS-CPL"  },
    { CPUID_FEATURE_DTES64,  "DTES64"  },
    { CPUID_FEATURE_EST,     "EST"     },
    { CPUID_FEATURE_FPU,     "FPU"     },
    { CPUID_FEATURE_FXSR,    "FXSR"    },
    { CPUID_FEATURE_HTT,     "HTT"     },
    { CPUID_FEATURE_IA64,    "IA64"    },
    { CPUID_FEATURE_MCA,     "MCA"     },
    { CPUID_FEATURE_MCE,     "MCE"     },
    { CPUID_FEATURE_MMX,     "MMX"     },
    { CPUID_FEATURE_MONITOR, "MONITOR" },
    { CPUID_FEATURE_MOVBE,   "MOVBE"   },
    { CPUID_FEATURE_MSR,     "MSR"     },
    { CPUID_FEATURE_MTRR,    "MTRR"    },
    { CPUID_FEATURE_OSXSAVE, "OSXSAVE" },
    { CPUID_FEATURE_PAE,     "PAE"     },
    { CPUID_FEATURE_PAT,     "PAT"     },
    { CPUID_FEATURE_PBE,     "PBE"     },
    { CPUID_FEATURE_PDCM,    "PDCM"    },
    { CPUID_FEATURE_PGE,     "PGE"     },
    { CPUID_FEATURE_POPCNT,  "POPCNT"  },
    { CPUID_FEATURE_PSE,     "PSE"     },
    { CPUID_FEATURE_PSE36,   "PSE-36"  },
    { CPUID_FEATURE_PSN,     "PSN"     },
    { CPUID_FEATURE_SEP,     "SEP"     },
    { CPUID_FEATURE_SMX,     "SMX"     },
    { CPUID_FEATURE_SS,      "SS"      },
    { CPUID_FEATURE_SSE,     "SSE"     },
    { CPUID_FEATURE_SSE2,    "SSE2"    },
    { CPUID_FEATURE_SSE3,    "SSE3"    },
    { CPUID_FEATURE_SSSE3,   "SSSE3"   },
    { CPUID_FEATURE_SSE4_1,  "SSE4.1"  },
    { CPUID_FEATURE_SSE4_2,  "SSE4.2"  },
    { CPUID_FEATURE_TM,      "TM"      },
    { CPUID_FEATURE_TM2,     "TM2"     },
    { CPUID_FEATURE_TSC,     "TSC"     },
    { CPUID_FEATURE_VME,     "VME"     },
    { CPUID_FEATURE_VMX,     "VMX"     },
    { CPUID_FEATURE_XSAVE,   "XSAVE"   },
    { CPUID_FEATURE_xAPIC,   "x2APIC"  },
    { CPUID_FEATURE_xTPR,    "xTPR"    },
    { 0, 0 }
},

extfeature_map[] = {
    { CPUID_EXTFEATURE_EM64T, "EM64T"   },
    { CPUID_EXTFEATURE_LAHF,  "LAHF"    },
    { CPUID_EXTFEATURE_SEP,   "SYSCALL" },
    { CPUID_EXTFEATURE_XD,    "XD"      },
    { 0, 0 }
},

feature_map_detailed[] = {
    { CPUID_FEATURE_ACPI,    "Thermal Monitor and Software Controlled Clock" },
    { CPUID_FEATURE_APIC,    "On-Chip APIC Hardware"                         },
    { CPUID_FEATURE_CLFSH,   "CLFLUSH Instruction"                           },
    { CPUID_FEATURE_CMOV,    "Conditional Move Instruction"                  },
    { CPUID_FEATURE_CID,     "L1 Context ID"                                 },
    { CPUID_FEATURE_CX16,    "CMPXCHG16B Instruction"                        },
    { CPUID_FEATURE_CX8,     "CMPXCHG8 Instruction"                          },
    { CPUID_FEATURE_DCA,     "Direct Cache Access"                           },
    { CPUID_FEATURE_DE,      "Debugging Extension"                           },
    { CPUID_FEATURE_DS,      "Debug Store"                                   },
    { CPUID_FEATURE_DSCPL,   "CPL Qualified Debug Store"                     },
    { CPUID_FEATURE_DTES64,  "64-Bit Debug Store"                            },
    { CPUID_FEATURE_EST,     "Enhanced Intel SpeedStep Technology"           },
    { CPUID_FEATURE_FPU,     "Floating-Point Unit On-Chip"                   },
    { CPUID_FEATURE_FXSR,    "FXSAVE and FXSTOR Instructions"                },
    { CPUID_FEATURE_HTT,     "HyperThreading"                                },
    { CPUID_FEATURE_IA64,    "IA64 Capabilities"                             },
    { CPUID_FEATURE_MCA,     "Machine-Check Architecture"                    },
    { CPUID_FEATURE_MCE,     "Machine-Check Exception"                       },
    { CPUID_FEATURE_MMX,     "MMX Technology"                                },
    { CPUID_FEATURE_MONITOR, "MONITOR/MWAIT Instructions"                    },
    { CPUID_FEATURE_MOVBE,   "MOVBE Instruction"                             },
    { CPUID_FEATURE_MSR,     "Model Specific Registers"                      },
    { CPUID_FEATURE_MTRR,    "Memory Type Range Registers"                   },
    { CPUID_FEATURE_OSXSAVE, "XSETBV/XGETBV Instructions Enabled"            },
    { CPUID_FEATURE_PAE,     "Physical Address Extension"                    },
    { CPUID_FEATURE_PAT,     "Page Attribute Table"                          },
    { CPUID_FEATURE_PBE,     "Pending Break Enable"                          },
    { CPUID_FEATURE_PDCM,    "Perfmon and Debug Capability"                  },
    { CPUID_FEATURE_PGE,     "Page Global Enable"                            },
    { CPUID_FEATURE_POPCNT,  "POPCNT Instruction"                            },
    { CPUID_FEATURE_PSE,     "Page Size Extension"                           },
    { CPUID_FEATURE_PSE36,   "36-Bit Page Size Extension"                    },
    { CPUID_FEATURE_PSN,     "Processor Serial Number"                       },
    { CPUID_FEATURE_SEP,     "Fast System Call"                              },
    { CPUID_FEATURE_SMX,     "Safer Mode Extensions"                         },
    { CPUID_FEATURE_SS,      "Self-Snoop"                                    },
    { CPUID_FEATURE_SSE,     "Streaming SIMD Extensions"                     },
    { CPUID_FEATURE_SSE2,    "Streaming SIMD Extensions 2"                   },
    { CPUID_FEATURE_SSE3,    "Streaming SIMD Extensions 3"                   },
    { CPUID_FEATURE_SSSE3,   "Supplemental Streaming SIMD Extensions 3"      },
    { CPUID_FEATURE_SSE4_1,  "Streaming SIMD Extensions 4.1"                 },
    { CPUID_FEATURE_SSE4_2,  "Streaming SIMD Extensions 4.2"                 },
    { CPUID_FEATURE_TM,      "Thermal Monitor"                               },
    { CPUID_FEATURE_TM2,     "Thermal Monitor 2"                             },
    { CPUID_FEATURE_TSC,     "Time Stamp Counter"                            },
    { CPUID_FEATURE_VME,     "Virtual Mode Extension"                        },
    { CPUID_FEATURE_VMX,     "Virtual Machine Extensions"                    },
    { CPUID_FEATURE_XSAVE,   "XSAVE/XSTOR States"                            },
    { CPUID_FEATURE_xAPIC,   "Extended xAPIC Support"                        },
    { CPUID_FEATURE_xTPR,    "xTPR Update Control"                           },
    { 0, 0 }
},

extfeature_map_detailed[] = {
    { CPUID_EXTFEATURE_EM64T, "Intel Extended Memory 64 Technology"          },
    { CPUID_EXTFEATURE_LAHF,  "LAHF/SAHF Instructions"                       },
    { CPUID_EXTFEATURE_SEP,   "Fast System Call"                             },
    { CPUID_EXTFEATURE_XD,    "Execution Disable"                            },
    { 0, 0 }
};

typedef enum { Lnone, L1I, L1D, L2U, L3U, LCACHE_MAX } cache_type_t; 

static const char* cache_names[LCACHE_MAX] = {
    "Invalid Cache",
    "L1 Instruction Cache",
    "L1 Data Cache",
    "L2 Unified Cache",
    "L3 Unified Cache",
};

typedef struct {
    unsigned char value;
    cache_type_t  type;          
    uint32_t      level;
    uint32_t      sharing;
    uint32_t      linesize;
    uint32_t      sets;
    uint32_t      associativity;
    uint32_t      size;
    uint32_t      partitions;
} cpuid_cache_desc_t;

typedef struct {

    cpu_type_t    cpuid_type;

    char          cpuid_vendor[16];
    char          cpuid_brand_string[48];

    /* Identification */
    uint8_t       cpuid_family;
    uint8_t       cpuid_model;
    uint8_t       cpuid_extmodel;
    uint8_t       cpuid_extfamily;
    uint8_t       cpuid_stepping;
    uint64_t      cpuid_features;
    uint64_t      cpuid_extfeatures;
    uint32_t      cpuid_signature;
    uint8_t       cpuid_brand; 

    /* Address Bits */
    uint32_t      cpuid_address_bits_physical;
    uint32_t      cpuid_address_bits_virtual;
    
    /* Cache */
    uint8_t            cache_info[64];
    cpuid_cache_desc_t cache_descriptors[LCACHE_MAX];
    uint32_t           cache_linesize;
    uint32_t           cpuid_cache_linesize;
    uint32_t           cpuid_cache_L2_associativity;
    uint32_t           cpuid_cache_size;

    /* Numbers of TLBs Per Processor */
    uint32_t      cpuid_itlb_4k;
    uint32_t      cpuid_dtlb_4k;
    uint32_t      cpuid_itlb_4mb;
    uint32_t      cpuid_dtlb_4mb;
    uint32_t      cpuid_itlb_2mb_or_4mb;
    uint32_t      cpuid_dtlb_2mb_or_4mb;
    uint32_t      cpuid_itlb_1gb;
    uint32_t      cpuid_dtlb_1gb;

    /* Cores and Threads */
    uint32_t      cpuid_cores_per_package;
    uint32_t      cpuid_logical_per_package;
    uint32_t      core_count;
    uint32_t      thread_count;

    /* MONITOR/MWAIT Leaf */
    uint32_t      cpuid_mwait_linesize_min;
    uint32_t      cpuid_mwait_linesize_max;
    uint32_t      cpuid_mwait_extensions;
    uint32_t      cpuid_mwait_sub_Cstates;

    /* Thermal/Power Management Leaf */
    boolean_t     cpuid_thermal_sensor;
    boolean_t     cpuid_thermal_dynamic_acceleration;
    uint32_t      cpuid_thermal_thresholds;
    boolean_t     cpuid_thermal_ACNT_MCNT;

    /* Architectural Performance Monitoring Leaf */
    uint8_t       cpuid_arch_perf_version;
    uint8_t       cpuid_arch_perf_number;
    uint8_t       cpuid_arch_perf_width;
    uint8_t       cpuid_arch_perf_events_number;
    uint32_t      cpuid_arch_perf_events;
    uint8_t       cpuid_arch_perf_fixed_number;
    uint8_t       cpuid_arch_perf_fixed_width;

} i386_cpu_info_t;

static i386_cpu_info_t cpuid_cpu_info;

static void
cpuid_set_generic_info(i386_cpu_info_t* info_p)
{
    uint32_t cpuid_reg[4];
    uint32_t max_extid;
    char     str[128];
    char*    p;

    /* Get vendor */
    do_cpuid(0, cpuid_reg);
    bcopy((char *)&cpuid_reg[ebx], &info_p->cpuid_vendor[0], 4); /* ug */
    bcopy((char *)&cpuid_reg[ecx], &info_p->cpuid_vendor[8], 4);
    bcopy((char *)&cpuid_reg[edx], &info_p->cpuid_vendor[4], 4);
    info_p->cpuid_vendor[12] = 0;

    /* Get extended CPUID results */
    do_cpuid(0x80000000, cpuid_reg);
    max_extid = cpuid_reg[eax];

    /* Check to see if we can get the brand string */
    if (max_extid >= 0x80000004) {
        /*
         * The brand string is up to 48 bytes and is guaranteed to be
         * NUL terminated.
         */
        do_cpuid(0x80000002, cpuid_reg);
        bcopy((char *)cpuid_reg, &str[0], 16);
        do_cpuid(0x80000003, cpuid_reg);
        bcopy((char *)cpuid_reg, &str[16], 16);
        do_cpuid(0x80000004, cpuid_reg);
        bcopy((char *)cpuid_reg, &str[32], 16);
        for (p = str; *p != '\0'; p++) {
            if (*p != ' ') break;
        }
        strncpy(info_p->cpuid_brand_string, p,
                sizeof(info_p->cpuid_brand_string));

        if (!strncmp(info_p->cpuid_brand_string, CPUID_STRING_UNKNOWN,
            min(sizeof(info_p->cpuid_brand_string),
            strlen(CPUID_STRING_UNKNOWN) + 1))) {
            /*
             * This string means we have a firmware-programmable brand string,
             * and the firmware couldn't figure out what sort of CPU we have.
             */
            info_p->cpuid_brand_string[0] = '\0';
        }
    }
    
    /* Get cache and addressing info */
    if (max_extid >= 0x80000006) {
        do_cpuid(0x80000006, cpuid_reg);
        info_p->cpuid_cache_linesize = bitfield(cpuid_reg[ecx], 7, 0);
        info_p->cpuid_cache_L2_associativity = bitfield(cpuid_reg[ecx], 15, 12);
        info_p->cpuid_cache_size = bitfield(cpuid_reg[ecx], 31, 16);
        do_cpuid(0x80000008, cpuid_reg);
        info_p->cpuid_address_bits_physical = bitfield(cpuid_reg[eax], 7, 0);
        info_p->cpuid_address_bits_virtual = bitfield(cpuid_reg[eax], 15, 8);
    }

    /* Get processor signature and decode */
    do_cpuid(1, cpuid_reg);
    info_p->cpuid_signature = cpuid_reg[eax];
    info_p->cpuid_stepping  = bitfield(cpuid_reg[eax],  3,  0);
    info_p->cpuid_model     = bitfield(cpuid_reg[eax],  7,  4);
    info_p->cpuid_family    = bitfield(cpuid_reg[eax], 11,  8);
    info_p->cpuid_type      = bitfield(cpuid_reg[eax], 13, 12);
    info_p->cpuid_extmodel  = bitfield(cpuid_reg[eax], 19, 16);
    info_p->cpuid_extfamily = bitfield(cpuid_reg[eax], 27, 20);
    info_p->cpuid_brand     = bitfield(cpuid_reg[ebx],  7,  0);
    info_p->cpuid_features  = quad(cpuid_reg[ecx], cpuid_reg[edx]);

    /* Fold extensions into family/model */
    if (info_p->cpuid_family == 0x0f) {
        info_p->cpuid_family += info_p->cpuid_extfamily;
    }
    if (info_p->cpuid_family == 0x0f || info_p->cpuid_family== 0x06) {
        info_p->cpuid_model += (info_p->cpuid_extmodel << 4);
    }

    if (info_p->cpuid_features & CPUID_FEATURE_HTT) {
        info_p->cpuid_logical_per_package = bitfield(cpuid_reg[ebx], 23, 16);
    } else {
        info_p->cpuid_logical_per_package = 1;
    }

    if (max_extid >= 0x80000001) {
        do_cpuid(0x80000001, cpuid_reg);
        info_p->cpuid_extfeatures = quad(cpuid_reg[ecx], cpuid_reg[edx]);
    }

    if (info_p->cpuid_extfeatures & CPUID_FEATURE_MONITOR) {

        do_cpuid(5, cpuid_reg);
        info_p->cpuid_mwait_linesize_min = cpuid_reg[eax];
        info_p->cpuid_mwait_linesize_max = cpuid_reg[ebx];
        info_p->cpuid_mwait_extensions   = cpuid_reg[ecx];
        info_p->cpuid_mwait_sub_Cstates  = cpuid_reg[edx];

        do_cpuid(6, cpuid_reg);
        info_p->cpuid_thermal_sensor = bitfield(cpuid_reg[eax], 0, 0);
        info_p->cpuid_thermal_dynamic_acceleration =
                    bitfield(cpuid_reg[eax], 1, 1);
        info_p->cpuid_thermal_thresholds = bitfield(cpuid_reg[ebx], 3, 0);
        info_p->cpuid_thermal_ACNT_MCNT = bitfield(cpuid_reg[ecx], 0, 0);

        do_cpuid(0xa, cpuid_reg);
        info_p->cpuid_arch_perf_version = bitfield(cpuid_reg[eax], 7, 0);
        info_p->cpuid_arch_perf_number = bitfield(cpuid_reg[eax],15, 8);
        info_p->cpuid_arch_perf_width = bitfield(cpuid_reg[eax],23,16);
        info_p->cpuid_arch_perf_events_number = bitfield(cpuid_reg[eax],31,24);
        info_p->cpuid_arch_perf_events = cpuid_reg[ebx];
        info_p->cpuid_arch_perf_fixed_number = bitfield(cpuid_reg[edx], 4, 0);
        info_p->cpuid_arch_perf_fixed_width = bitfield(cpuid_reg[edx],12, 5);

    }
}

static void
cpuid_set_cache_info(i386_cpu_info_t* info_p)
{
    uint32_t  cpuid_result[4];
    uint32_t  reg[4];
    uint32_t  index;
    uint32_t  linesizes[LCACHE_MAX];
    unsigned  int i, j;
    boolean_t cpuid_deterministic_supported = FALSE;

    bzero(linesizes, sizeof(linesizes));

    do_cpuid(2, cpuid_result); /* Cache descriptor info */
    for (j = 0; j < 4; j++) {
        if ((cpuid_result[j] >> 31) == 1) { /* bit31 is validity */
            continue;
        }
        ((uint32_t *)info_p->cache_info)[j] = cpuid_result[j];
    }

    /* First byte gives the number of CPUID calls to get all descriptors */
    for (i = 1; i < info_p->cache_info[0]; i++) {
        if (i * 16 > sizeof(info_p->cache_info)) {
            break;
        }
        do_cpuid(2, cpuid_result);
        for (j = 0; j < 4; j++) {
            if ((cpuid_result[j] >> 31) == 1)  {
                continue;
            }
            ((uint32_t *)info_p->cache_info)[4 * i + j] = cpuid_result[j];
        }
    }

    do_cpuid(0, cpuid_result);
    if (cpuid_result[eax] >= 4) {
        cpuid_deterministic_supported = TRUE;
    }

    for (index = 0; cpuid_deterministic_supported; index++) {

        cache_type_t type = Lnone;

        reg[eax] = 4;     /* CPUID request 4 */
        reg[ecx] = index; /* index starting at 0 */
        cpuid(reg);

        uint32_t cache_type = bitfield(reg[eax], 4, 0);
        if (cache_type == 0) {
            break;        /* no more caches */
        }

        uint32_t cache_level = bitfield(reg[eax],  7,  5);

        /* Map type/levels returned by CPUID into cache_type_t */
        switch (cache_level) {
        case 1:
            type = cache_type == 1 ? L1D : cache_type == 2 ? L1I : Lnone;
            break;
        case 2:
            type = cache_type == 3 ? L2U : Lnone;
            break;
        case 3:
            type = cache_type == 3 ? L3U : Lnone;
            break;
        default:
            type = Lnone;
        }

        cpuid_cache_desc_t* cd = &(info_p->cache_descriptors[type]);

        cd->type          = type;
        cd->level         = cache_level;
        cd->sharing       = bitfield(reg[eax], 25, 14) + 1;
        cd->linesize      = bitfield(reg[ebx], 11,  0) + 1;
        cd->sets          = bitfield(reg[ecx], 31,  0) + 1;
        cd->partitions    = bitfield(reg[ebx], 21, 12) + 1;
        cd->associativity = bitfield(reg[ebx], 31, 22) + 1;

        info_p->cpuid_cores_per_package = bitfield(reg[eax], 31, 26) + 1;
                
        /*
         * The total size of a cache is (linesize * sets * associativity )
         */
        if (type != Lnone) {
            cd->size = cd->linesize * cd->sets * cd->associativity;
            linesizes[type] = cd->linesize;
        }
    } 
    
    /*
     * If deterministic cache parameters are not available...
     */
    if (info_p->cpuid_cores_per_package == 0) {

        info_p->cpuid_cores_per_package = 1;

        /* CPUID define in 1024 quantities */
        info_p->cache_descriptors[L2U].size = info_p->cpuid_cache_size * 1024;
        info_p->cache_descriptors[L2U].sharing = 1;
        info_p->cache_descriptors[L2U].partitions = 1;
        info_p->cache_descriptors[L2U].linesize = info_p->cpuid_cache_linesize;
        linesizes[L2U] = info_p->cpuid_cache_linesize;
    }
    
    /*
     * What linesize to publish? We use the L2 linesize if any, else the L1D.
     */
    if (linesizes[L2U]) {
        info_p->cache_linesize = linesizes[L2U];
    } else if (linesizes[L1D]) {
        info_p->cache_linesize = linesizes[L1D];
    } else {
        fprintf(stderr, "*** No cache line size!\n");
        exit(1);
    }

    /*
     * Extract and publish the TLB information.
     */
    for (i = 1; i < sizeof(info_p->cache_info); i++) {

        uint8_t desc = info_p->cache_info[i];

	printf("desc = 0x%02x\n", desc);
        switch (desc) {
        case CPUID_CACHE_ITLB_4K_32_4:
            info_p->cpuid_itlb_4k = 32;
            break;
        case CPUID_CACHE_ITLB_4M_2:
            info_p->cpuid_itlb_4mb = 2;
            break;
        case CPUID_CACHE_DTLB_4K_64_4:
            info_p->cpuid_dtlb_4k = 64;
            break;
        case CPUID_CACHE_DTLB_4M_8_4:
            info_p->cpuid_dtlb_4mb = 8;
            break;
        case CPUID_CACHE_DTLB_4M_32_4:
            info_p->cpuid_dtlb_4mb = 32;
            break;
        case CPUID_CACHE_ITLB_32:
            info_p->cpuid_itlb_4k = 32;
            break;
        case CPUID_CACHE_ITLB_64:
            info_p->cpuid_itlb_4k = 64;
            info_p->cpuid_itlb_2mb_or_4mb = 64;
            break;
        case CPUID_CACHE_ITLB_128:
            info_p->cpuid_itlb_4k = 128;
            info_p->cpuid_itlb_2mb_or_4mb = 128;
            break;
        case CPUID_CACHE_ITLB_256:
            info_p->cpuid_itlb_4k = 256;
            info_p->cpuid_itlb_2mb_or_4mb = 256;
            break;
        case CPUID_CACHE_DTLB_64:
            info_p->cpuid_dtlb_4k = 64;
            info_p->cpuid_dtlb_4mb = 64;
            break;
        case CPUID_CACHE_DTLB_128:
            info_p->cpuid_dtlb_4k = 128;
            info_p->cpuid_dtlb_4mb = 128;
            break;
        case CPUID_CACHE_DTLB_256:
            info_p->cpuid_dtlb_4k = 256;
            info_p->cpuid_dtlb_4mb = 256;
            break;
        case CPUID_CACHE_ITLB_4M2M_7:
            info_p->cpuid_itlb_2mb_or_4mb = 7;
            break;
        case CPUID_CACHE_DTLB_4M_16_4:
            info_p->cpuid_dtlb_4mb = 16;
            break;
        case CPUID_CACHE_DTLB_4K_16_4:
            info_p->cpuid_dtlb_4k = 16;
            break;
        case CPUID_CACHE_DTLB_4K_16:
            info_p->cpuid_dtlb_4k = 16;
            break;
        case CPUID_CACHE_DTLB_4M2M_32_4:
            info_p->cpuid_dtlb_4mb = 32;
            break;
        case CPUID_CACHE_ITLB_4K_128_4:
            info_p->cpuid_itlb_4k = 128;
            break;
        case CPUID_CACHE_ITLB_4M_8:
            info_p->cpuid_itlb_4mb = 8;
            break;
        case CPUID_CACHE_DTLB_4K_128_4:
            info_p->cpuid_dtlb_4k = 128;
            break;
        case CPUID_CACHE_DTLB_4K_256_4:
            info_p->cpuid_dtlb_4k = 256;
            break;
	case CPUID_CACHE_DTLB_4M_32_4_1GB:
	    info_p->cpuid_dtlb_2mb_or_4mb = 32;
	    info_p->cpuid_dtlb_1gb = 4;
	    break;
        }
    }
}

void
cpuid_set_info(void)
{
    bzero((void *)&cpuid_cpu_info, sizeof(cpuid_cpu_info));

    cpuid_set_generic_info(&cpuid_cpu_info);

    if ((strncmp(CPUID_VID_INTEL, cpuid_cpu_info.cpuid_vendor,
                 min(strlen(CPUID_STRING_UNKNOWN) + 1,
                 sizeof(cpuid_cpu_info.cpuid_vendor))))) {
        fprintf(stderr, "*** Unsupported CPU\n");
        exit(1);
    }

    cpuid_set_cache_info(&cpuid_cpu_info);

    if (cpuid_cpu_info.core_count == 0) {
        cpuid_cpu_info.core_count = cpuid_cpu_info.cpuid_cores_per_package;
        cpuid_cpu_info.thread_count = cpuid_cpu_info.cpuid_logical_per_package;
    }
}

/*
 * Copyright (c) 1997, 1998, 1999, 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center, by Luke Mewburn and by Tomas Svensson.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the NetBSD
 *      Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define HN_DECIMAL      0x01
#define HN_NOSPACE      0x02
#define HN_B            0x04
#define HN_DIVISOR_1000 0x08
#define HN_GETSCALE     0x10
#define HN_AUTOSCALE    0x20

#include <locale.h>

int
humanize_number(char* buf, size_t len, int64_t bytes,
                const char* suffix, int scale, int flags)
{
	const char *prefixes, *sep;
	int	b, i, r, maxscale, s1, s2, sign;
	int64_t	divisor, max;
	size_t	baselen;

	if (flags & HN_DIVISOR_1000) {
		/* SI for decimal multiplies */
		divisor = 1000;
		if (flags & HN_B)
			prefixes = "B\0k\0M\0G\0T\0P\0E";
		else
			prefixes = "\0\0k\0M\0G\0T\0P\0E";
	} else {
		/*
		 * binary multiplies
		 * XXX IEC 60027-2 recommends Ki, Mi, Gi...
		 */
		divisor = 1024;
		if (flags & HN_B)
			prefixes = "B\0K\0M\0G\0T\0P\0E";
		else
			prefixes = "\0\0K\0M\0G\0T\0P\0E";
	}

#define	SCALE2PREFIX(scale)	(&prefixes[(scale) << 1])
	maxscale = 7;

	if (scale >= maxscale &&
	    (scale & (HN_AUTOSCALE | HN_GETSCALE)) == 0)
		return (-1);

	if (buf == NULL || suffix == NULL)
		return (-1);

	if (len > 0)
		buf[0] = '\0';
	if (bytes < 0) {
		sign = -1;
		bytes *= -100;
		baselen = 3;		/* sign, digit, prefix */
	} else {
		sign = 1;
		bytes *= 100;
		baselen = 2;		/* digit, prefix */
	}
	if (flags & HN_NOSPACE)
		sep = "";
	else {
		sep = " ";
		baselen++;
	}
	baselen += strlen(suffix);

	/* Check if enough room for `x y' + suffix + `\0' */
	if (len < baselen + 1)
		return (-1);

	if (scale & (HN_AUTOSCALE | HN_GETSCALE)) {
		/* See if there is additional columns can be used. */
		for (max = 100, i = len - baselen; i-- > 0;)
			max *= 10;

		for (i = 0; bytes >= max && i < maxscale; i++)
			bytes /= divisor;

		if (scale & HN_GETSCALE)
			return (i);
	} else
		for (i = 0; i < scale && i < maxscale; i++)
			bytes /= divisor;

	/* If a value <= 9.9 after rounding and ... */
	if (bytes < 995 && i > 0 && flags & HN_DECIMAL) {
		/* baselen + \0 + .N */
		if (len < baselen + 1 + 2)
			return (-1);
		b = ((int)bytes + 5) / 10;
		s1 = b / 10;
		s2 = b % 10;
		r = snprintf(buf, len, "%d%s%d%s%s%s",
		    sign * s1, localeconv()->decimal_point, s2,
		    sep, SCALE2PREFIX(i), suffix);
	} else
		r = snprintf(buf, len, "%lld%s%s%s",
		    /* LONGLONG */
		    (long long)(sign * ((bytes + 50) / 100)),
		    sep, SCALE2PREFIX(i), suffix);

	return (r);
}

int
main(void)
{
    /* Gather */

    cpuid_set_info();

    i386_cpu_info_t* I = &cpuid_cpu_info;
    
    /* Display */

    printf("# Identification\n");
    printf("%-22s: %s\n", "Vendor", I->cpuid_vendor);
    printf("%-22s: %s\n", "Brand String", I->cpuid_brand_string);

    printf("%-22s: %hhd", "Model Number", I->cpuid_model);
    int i = 0;
    for (; some_model_names[i].model_name; i++) {
        if (some_model_names[i].model_number == I->cpuid_model) {
            printf(" (%s)", some_model_names[i].model_name);
        }
    }
    printf("\n");

    printf("%-22s: %hhd\n", "Family Code", I->cpuid_family);
    printf("%-22s: %hhd\n", "Extended Model", I->cpuid_extmodel);
    printf("%-22s: %hhd\n", "Extended Family", I->cpuid_extfamily);
    printf("%-22s: %hhd\n", "Stepping ID", I->cpuid_stepping);
    printf("%-22s: %d\n", "Signature", I->cpuid_signature);
    printf("\n");

    printf("# Address Bits\n");
    printf("%-22s: %d\n", "Physical Addressing",
           I->cpuid_address_bits_physical);
    printf("%-22s: %d\n", "Virtual Addressing",
           I->cpuid_address_bits_virtual);
    printf("\n");

    printf("# Multi-Core Information\n");
    printf("%-52s: %d\n", "Logical Processors (Threads) per Physical Processor",
           I->cpuid_logical_per_package);
    printf("%-52s: %d\n", "Cores per Physical Package",
           I->cpuid_cores_per_package);
    printf("\n");

    printf("# Caches\n");

    i = L1I;
    for (; i < LCACHE_MAX; i++) {
        cpuid_cache_desc_t* cd = &(I->cache_descriptors[i]);
        if (cd->size == 0) {
            continue;
        }

        printf("## %s\n", cache_names[i]);

        char human_buf[5];
        humanize_number(human_buf, sizeof(human_buf), cd->size, "",
                        HN_AUTOSCALE, HN_B | HN_NOSPACE);
        printf("%-22s: %s\n", "Size", human_buf);

        if (cd->linesize) {
            humanize_number(human_buf, sizeof(human_buf), cd->linesize, "",
                            HN_AUTOSCALE, HN_B | HN_NOSPACE | HN_DECIMAL);
            printf("%-22s: %s\n", "Line Size", human_buf);
        } else {
            printf("%-22s: %s\n", "Line Size", "default");
        }

        char shared_buf[64];
        if (cd->sharing == 1) {
            snprintf(shared_buf, sizeof(shared_buf), "%s",
                     "dedicated per processor thread");
        } else {
            snprintf(shared_buf, sizeof(shared_buf),
                 "shared between %d processor threads", cd->sharing);
        }
        printf("%-22s: %s\n", "Sharing", shared_buf);

        printf("%-22s: %d\n", "Sets", cd->sets);
        printf("%-22s: %d\n", "Partitions", cd->partitions);
        printf("%-22s: %d\n", "Associativity", cd->associativity);
        printf("\n");
    }
       
    printf("# Translation Lookaside Buffers\n");
    printf("%-22s: %d 1GB, %d 2MB or 4MB, %d 4MB, %d 4KB\n",
           "Instruction TLBs", I->cpuid_itlb_1gb, I->cpuid_itlb_2mb_or_4mb, I->cpuid_itlb_4mb, I->cpuid_itlb_4k);
    printf("%-22s:  %d 1GB, %d 2MB or 4MB, %d 4MB, %d 4KB\n",
           "Data TLBs", I->cpuid_dtlb_1gb, I->cpuid_dtlb_2mb_or_4mb, I->cpuid_dtlb_4mb, I->cpuid_dtlb_4k);
    printf("\n");

    printf("# Features\n");
    for (i = 0; feature_map[i].mask != 0; i++) {
        if ((I->cpuid_features & feature_map[i].mask) == 0) {
            continue;
        }
        printf("%-22s: %s\n", feature_map[i].name,
               feature_map_detailed[i].name);
    }
    printf("\n");

    printf("# Extended Features\n");
    for (i = 0; extfeature_map[i].mask != 0; i++) {
        if ((I->cpuid_extfeatures & extfeature_map[i].mask) == 0) {
            continue;
        }
        printf("%-22s: %s\n", extfeature_map[i].name,
               extfeature_map_detailed[i].name);
    }
    printf("\n");

    exit(0);
}
