multiline_comment|/*&n; * cpufeature.h&n; *&n; * Defines x86 CPU feature bits&n; */
macro_line|#ifndef __ASM_I386_CPUFEATURE_H
DECL|macro|__ASM_I386_CPUFEATURE_H
mdefine_line|#define __ASM_I386_CPUFEATURE_H
macro_line|#include &lt;linux/bitops.h&gt;
DECL|macro|NCAPINTS
mdefine_line|#define NCAPINTS&t;7&t;/* N 32-bit words worth of info */
multiline_comment|/* Intel-defined CPU features, CPUID level 0x00000001 (edx), word 0 */
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
DECL|macro|X86_FEATURE_NX
mdefine_line|#define X86_FEATURE_NX&t;&t;(1*32+20) /* Execute Disable */
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
multiline_comment|/* cpu types for specific tunings: */
DECL|macro|X86_FEATURE_K8
mdefine_line|#define X86_FEATURE_K8&t;&t;(3*32+ 4) /* Opteron, Athlon64 */
DECL|macro|X86_FEATURE_K7
mdefine_line|#define X86_FEATURE_K7&t;&t;(3*32+ 5) /* Athlon */
DECL|macro|X86_FEATURE_P3
mdefine_line|#define X86_FEATURE_P3&t;&t;(3*32+ 6) /* P3 */
DECL|macro|X86_FEATURE_P4
mdefine_line|#define X86_FEATURE_P4&t;&t;(3*32+ 7) /* P4 */
multiline_comment|/* Intel-defined CPU features, CPUID level 0x00000001 (ecx), word 4 */
DECL|macro|X86_FEATURE_XMM3
mdefine_line|#define X86_FEATURE_XMM3&t;(4*32+ 0) /* Streaming SIMD Extensions-3 */
DECL|macro|X86_FEATURE_MWAIT
mdefine_line|#define X86_FEATURE_MWAIT&t;(4*32+ 3) /* Monitor/Mwait support */
DECL|macro|X86_FEATURE_DSCPL
mdefine_line|#define X86_FEATURE_DSCPL&t;(4*32+ 4) /* CPL Qualified Debug Store */
DECL|macro|X86_FEATURE_EST
mdefine_line|#define X86_FEATURE_EST&t;&t;(4*32+ 7) /* Enhanced SpeedStep */
DECL|macro|X86_FEATURE_TM2
mdefine_line|#define X86_FEATURE_TM2&t;&t;(4*32+ 8) /* Thermal Monitor 2 */
DECL|macro|X86_FEATURE_CID
mdefine_line|#define X86_FEATURE_CID&t;&t;(4*32+10) /* Context ID */
DECL|macro|X86_FEATURE_CX16
mdefine_line|#define X86_FEATURE_CX16        (4*32+13) /* CMPXCHG16B */
DECL|macro|X86_FEATURE_XTPR
mdefine_line|#define X86_FEATURE_XTPR&t;(4*32+14) /* Send Task Priority Messages */
multiline_comment|/* VIA/Cyrix/Centaur-defined CPU features, CPUID level 0xC0000001, word 5 */
DECL|macro|X86_FEATURE_XSTORE
mdefine_line|#define X86_FEATURE_XSTORE&t;(5*32+ 2) /* on-CPU RNG present (xstore insn) */
DECL|macro|X86_FEATURE_XSTORE_EN
mdefine_line|#define X86_FEATURE_XSTORE_EN&t;(5*32+ 3) /* on-CPU RNG enabled */
DECL|macro|X86_FEATURE_XCRYPT
mdefine_line|#define X86_FEATURE_XCRYPT&t;(5*32+ 6) /* on-CPU crypto (xcrypt insn) */
DECL|macro|X86_FEATURE_XCRYPT_EN
mdefine_line|#define X86_FEATURE_XCRYPT_EN&t;(5*32+ 7) /* on-CPU crypto enabled */
multiline_comment|/* More extended AMD flags: CPUID level 0x80000001, ecx, word 6 */
DECL|macro|X86_FEATURE_LAHF_LM
mdefine_line|#define X86_FEATURE_LAHF_LM&t;(5*32+ 0) /* LAHF/SAHF in long mode */
DECL|macro|X86_FEATURE_CMP_LEGACY
mdefine_line|#define X86_FEATURE_CMP_LEGACY&t;(5*32+ 1) /* If yes HyperThreading not valid */
DECL|macro|cpu_has
mdefine_line|#define cpu_has(c, bit)&t;&t;test_bit(bit, (c)-&gt;x86_capability)
DECL|macro|boot_cpu_has
mdefine_line|#define boot_cpu_has(bit)&t;test_bit(bit, boot_cpu_data.x86_capability)
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;&t;boot_cpu_has(X86_FEATURE_FPU)
DECL|macro|cpu_has_vme
mdefine_line|#define cpu_has_vme&t;&t;boot_cpu_has(X86_FEATURE_VME)
DECL|macro|cpu_has_de
mdefine_line|#define cpu_has_de&t;&t;boot_cpu_has(X86_FEATURE_DE)
DECL|macro|cpu_has_pse
mdefine_line|#define cpu_has_pse&t;&t;boot_cpu_has(X86_FEATURE_PSE)
DECL|macro|cpu_has_tsc
mdefine_line|#define cpu_has_tsc&t;&t;boot_cpu_has(X86_FEATURE_TSC)
DECL|macro|cpu_has_pae
mdefine_line|#define cpu_has_pae&t;&t;boot_cpu_has(X86_FEATURE_PAE)
DECL|macro|cpu_has_pge
mdefine_line|#define cpu_has_pge&t;&t;boot_cpu_has(X86_FEATURE_PGE)
DECL|macro|cpu_has_apic
mdefine_line|#define cpu_has_apic&t;&t;boot_cpu_has(X86_FEATURE_APIC)
DECL|macro|cpu_has_sep
mdefine_line|#define cpu_has_sep&t;&t;boot_cpu_has(X86_FEATURE_SEP)
DECL|macro|cpu_has_mtrr
mdefine_line|#define cpu_has_mtrr&t;&t;boot_cpu_has(X86_FEATURE_MTRR)
DECL|macro|cpu_has_mmx
mdefine_line|#define cpu_has_mmx&t;&t;boot_cpu_has(X86_FEATURE_MMX)
DECL|macro|cpu_has_fxsr
mdefine_line|#define cpu_has_fxsr&t;&t;boot_cpu_has(X86_FEATURE_FXSR)
DECL|macro|cpu_has_xmm
mdefine_line|#define cpu_has_xmm&t;&t;boot_cpu_has(X86_FEATURE_XMM)
DECL|macro|cpu_has_xmm2
mdefine_line|#define cpu_has_xmm2&t;&t;boot_cpu_has(X86_FEATURE_XMM2)
DECL|macro|cpu_has_xmm3
mdefine_line|#define cpu_has_xmm3&t;&t;boot_cpu_has(X86_FEATURE_XMM3)
DECL|macro|cpu_has_ht
mdefine_line|#define cpu_has_ht&t;&t;boot_cpu_has(X86_FEATURE_HT)
DECL|macro|cpu_has_mp
mdefine_line|#define cpu_has_mp&t;&t;boot_cpu_has(X86_FEATURE_MP)
DECL|macro|cpu_has_nx
mdefine_line|#define cpu_has_nx&t;&t;boot_cpu_has(X86_FEATURE_NX)
DECL|macro|cpu_has_k6_mtrr
mdefine_line|#define cpu_has_k6_mtrr&t;&t;boot_cpu_has(X86_FEATURE_K6_MTRR)
DECL|macro|cpu_has_cyrix_arr
mdefine_line|#define cpu_has_cyrix_arr&t;boot_cpu_has(X86_FEATURE_CYRIX_ARR)
DECL|macro|cpu_has_centaur_mcr
mdefine_line|#define cpu_has_centaur_mcr&t;boot_cpu_has(X86_FEATURE_CENTAUR_MCR)
DECL|macro|cpu_has_xstore
mdefine_line|#define cpu_has_xstore&t;&t;boot_cpu_has(X86_FEATURE_XSTORE)
DECL|macro|cpu_has_xstore_enabled
mdefine_line|#define cpu_has_xstore_enabled&t;boot_cpu_has(X86_FEATURE_XSTORE_EN)
DECL|macro|cpu_has_xcrypt
mdefine_line|#define cpu_has_xcrypt&t;&t;boot_cpu_has(X86_FEATURE_XCRYPT)
DECL|macro|cpu_has_xcrypt_enabled
mdefine_line|#define cpu_has_xcrypt_enabled&t;boot_cpu_has(X86_FEATURE_XCRYPT_EN)
macro_line|#endif /* __ASM_I386_CPUFEATURE_H */
multiline_comment|/* &n; * Local Variables:&n; * mode:c&n; * comment-column:42&n; * End:&n; */
eof
