multiline_comment|/*&n; * cpufeature.h&n; *&n; * Defines x86 CPU feature bits&n; */
macro_line|#ifndef __ASM_I386_CPUFEATURE_H
DECL|macro|__ASM_I386_CPUFEATURE_H
mdefine_line|#define __ASM_I386_CPUFEATURE_H
multiline_comment|/* Sample usage: CPU_FEATURE_P(cpu.x86_capability, FPU) */
DECL|macro|CPU_FEATURE_P
mdefine_line|#define CPU_FEATURE_P(CAP, FEATURE) test_bit(CAP, X86_FEATURE_##FEATURE ##_BIT)
DECL|macro|NCAPINTS
mdefine_line|#define NCAPINTS&t;4&t;/* Currently we have 4 32-bit words worth of info */
multiline_comment|/* Intel-defined CPU features, CPUID level 0x00000001, word 0 */
DECL|macro|X86_FEATURE_FPU
mdefine_line|#define X86_FEATURE_FPU&t;&t;(0*32+ 0) /* Onboard FPU */
DECL|macro|X86_FEATURE_VME
mdefine_line|#define X86_FEATURE_VME&t;&t;(0*32+ 1) /* Virtual Mode Extensions */
DECL|macro|X86_FEATURE_DE
mdefine_line|#define X86_FEATURE_DE&t;&t;(0*32+ 2) /* Debugging Extensions */
DECL|macro|X86_FEATURE_PSE
mdefine_line|#define X86_FEATURE_PSE &t;(0*32+ 3) /* Page Size Extensions */
DECL|macro|X86_FEATURE_TSC
mdefine_line|#define X86_FEATURE_TSC&t;&t;(0*32+ 4) /* Time Stamp Counter */
DECL|macro|X86_FEATURE_MSR
mdefine_line|#define X86_FEATURE_MSR&t;&t;(0*32+ 5) /* Model-Specific Registers, RDMSR, WRMSR */
DECL|macro|X86_FEATURE_PAE
mdefine_line|#define X86_FEATURE_PAE&t;&t;(0*32+ 6) /* Physical Address Extensions */
DECL|macro|X86_FEATURE_MCE
mdefine_line|#define X86_FEATURE_MCE&t;&t;(0*32+ 7) /* Machine Check Architecture */
DECL|macro|X86_FEATURE_CX8
mdefine_line|#define X86_FEATURE_CX8&t;&t;(0*32+ 8) /* CMPXCHG8 instruction */
DECL|macro|X86_FEATURE_APIC
mdefine_line|#define X86_FEATURE_APIC&t;(0*32+ 9) /* Onboard APIC */
DECL|macro|X86_FEATURE_SEP
mdefine_line|#define X86_FEATURE_SEP&t;&t;(0*32+11) /* SYSENTER/SYSEXIT */
DECL|macro|X86_FEATURE_MTRR
mdefine_line|#define X86_FEATURE_MTRR&t;(0*32+12) /* Memory Type Range Registers */
DECL|macro|X86_FEATURE_PGE
mdefine_line|#define X86_FEATURE_PGE&t;&t;(0*32+13) /* Page Global Enable */
DECL|macro|X86_FEATURE_MCA
mdefine_line|#define X86_FEATURE_MCA&t;&t;(0*32+14) /* Machine Check Architecture */
DECL|macro|X86_FEATURE_CMOV
mdefine_line|#define X86_FEATURE_CMOV&t;(0*32+15) /* CMOV instruction (FCMOVCC and FCOMI too if FPU present) */
DECL|macro|X86_FEATURE_PAT
mdefine_line|#define X86_FEATURE_PAT&t;&t;(0*32+16) /* Page Attribute Table */
DECL|macro|X86_FEATURE_PSE36
mdefine_line|#define X86_FEATURE_PSE36&t;(0*32+17) /* 36-bit PSEs */
DECL|macro|X86_FEATURE_PN
mdefine_line|#define X86_FEATURE_PN&t;&t;(0*32+18) /* Processor serial number */
DECL|macro|X86_FEATURE_CLFLSH
mdefine_line|#define X86_FEATURE_CLFLSH&t;(0*32+19) /* Supports the CLFLUSH instruction */
DECL|macro|X86_FEATURE_DTES
mdefine_line|#define X86_FEATURE_DTES&t;(0*32+21) /* Debug Trace Store */
DECL|macro|X86_FEATURE_ACPI
mdefine_line|#define X86_FEATURE_ACPI&t;(0*32+22) /* ACPI via MSR */
DECL|macro|X86_FEATURE_MMX
mdefine_line|#define X86_FEATURE_MMX&t;&t;(0*32+23) /* Multimedia Extensions */
DECL|macro|X86_FEATURE_FXSR
mdefine_line|#define X86_FEATURE_FXSR&t;(0*32+24) /* FXSAVE and FXRSTOR instructions (fast save and restore */
multiline_comment|/* of FPU context), and CR4.OSFXSR available */
DECL|macro|X86_FEATURE_XMM
mdefine_line|#define X86_FEATURE_XMM&t;&t;(0*32+25) /* Streaming SIMD Extensions */
DECL|macro|X86_FEATURE_XMM2
mdefine_line|#define X86_FEATURE_XMM2&t;(0*32+26) /* Streaming SIMD Extensions-2 */
DECL|macro|X86_FEATURE_SELFSNOOP
mdefine_line|#define X86_FEATURE_SELFSNOOP&t;(0*32+27) /* CPU self snoop */
DECL|macro|X86_FEATURE_HT
mdefine_line|#define X86_FEATURE_HT&t;&t;(0*32+28) /* Hyper-Threading */
DECL|macro|X86_FEATURE_ACC
mdefine_line|#define X86_FEATURE_ACC&t;&t;(0*32+29) /* Automatic clock control */
DECL|macro|X86_FEATURE_IA64
mdefine_line|#define X86_FEATURE_IA64&t;(0*32+30) /* IA-64 processor */
multiline_comment|/* AMD-defined CPU features, CPUID level 0x80000001, word 1 */
multiline_comment|/* Don&squot;t duplicate feature flags which are redundant with Intel! */
DECL|macro|X86_FEATURE_SYSCALL
mdefine_line|#define X86_FEATURE_SYSCALL&t;(1*32+11) /* SYSCALL/SYSRET */
DECL|macro|X86_FEATURE_MP
mdefine_line|#define X86_FEATURE_MP&t;&t;(1*32+19) /* MP Capable. */
DECL|macro|X86_FEATURE_MMXEXT
mdefine_line|#define X86_FEATURE_MMXEXT&t;(1*32+22) /* AMD MMX extensions */
DECL|macro|X86_FEATURE_LM
mdefine_line|#define X86_FEATURE_LM&t;&t;(1*32+29) /* Long Mode (x86-64) */
DECL|macro|X86_FEATURE_3DNOWEXT
mdefine_line|#define X86_FEATURE_3DNOWEXT&t;(1*32+30) /* AMD 3DNow! extensions */
DECL|macro|X86_FEATURE_3DNOW
mdefine_line|#define X86_FEATURE_3DNOW&t;(1*32+31) /* 3DNow! */
multiline_comment|/* Transmeta-defined CPU features, CPUID level 0x80860001, word 2 */
DECL|macro|X86_FEATURE_RECOVERY
mdefine_line|#define X86_FEATURE_RECOVERY&t;(2*32+ 0) /* CPU in recovery mode */
DECL|macro|X86_FEATURE_LONGRUN
mdefine_line|#define X86_FEATURE_LONGRUN&t;(2*32+ 1) /* Longrun power control */
DECL|macro|X86_FEATURE_LRTI
mdefine_line|#define X86_FEATURE_LRTI&t;(2*32+ 3) /* LongRun table interface */
multiline_comment|/* Other features, Linux-defined mapping, word 3 */
multiline_comment|/* This range is used for feature bits which conflict or are synthesized */
DECL|macro|X86_FEATURE_CXMMX
mdefine_line|#define X86_FEATURE_CXMMX&t;(3*32+ 0) /* Cyrix MMX extensions */
DECL|macro|X86_FEATURE_K6_MTRR
mdefine_line|#define X86_FEATURE_K6_MTRR&t;(3*32+ 1) /* AMD K6 nonstandard MTRRs */
DECL|macro|X86_FEATURE_CYRIX_ARR
mdefine_line|#define X86_FEATURE_CYRIX_ARR&t;(3*32+ 2) /* Cyrix ARRs (= MTRRs) */
DECL|macro|X86_FEATURE_CENTAUR_MCR
mdefine_line|#define X86_FEATURE_CENTAUR_MCR&t;(3*32+ 3) /* Centaur MCRs (= MTRRs) */
macro_line|#endif /* __ASM_I386_CPUFEATURE_H */
multiline_comment|/* &n; * Local Variables:&n; * mode:c&n; * comment-column:42&n; * End:&n; */
eof
