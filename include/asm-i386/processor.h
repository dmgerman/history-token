multiline_comment|/*&n; * include/asm-i386/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_I386_PROCESSOR_H
DECL|macro|__ASM_I386_PROCESSOR_H
mdefine_line|#define __ASM_I386_PROCESSOR_H
macro_line|#include &lt;asm/vm86.h&gt;
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/cpufeature.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;movl $1f,%0&bslash;n1:&quot;:&quot;=g&quot; (pc)); pc; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; *  Members of this structure are referenced in head.S, so think twice&n; *  before touching them. [mj]&n; */
DECL|struct|cpuinfo_x86
r_struct
id|cpuinfo_x86
(brace
DECL|member|x86
id|__u8
id|x86
suffix:semicolon
multiline_comment|/* CPU family */
DECL|member|x86_vendor
id|__u8
id|x86_vendor
suffix:semicolon
multiline_comment|/* CPU vendor */
DECL|member|x86_model
id|__u8
id|x86_model
suffix:semicolon
DECL|member|x86_mask
id|__u8
id|x86_mask
suffix:semicolon
DECL|member|wp_works_ok
r_char
id|wp_works_ok
suffix:semicolon
multiline_comment|/* It doesn&squot;t on 386&squot;s */
DECL|member|hlt_works_ok
r_char
id|hlt_works_ok
suffix:semicolon
multiline_comment|/* Problems on some 486Dx4&squot;s and old 386&squot;s */
DECL|member|hard_math
r_char
id|hard_math
suffix:semicolon
DECL|member|rfu
r_char
id|rfu
suffix:semicolon
DECL|member|cpuid_level
r_int
id|cpuid_level
suffix:semicolon
multiline_comment|/* Maximum supported CPUID level, -1=no CPUID */
DECL|member|x86_capability
id|__u32
id|x86_capability
(braket
id|NCAPINTS
)braket
suffix:semicolon
DECL|member|x86_vendor_id
r_char
id|x86_vendor_id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|x86_model_id
r_char
id|x86_model_id
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|x86_cache_size
r_int
id|x86_cache_size
suffix:semicolon
multiline_comment|/* in KB - valid for CPUS which support this&n;&t;&t;&t;&t;    call  */
DECL|member|fdiv_bug
r_int
id|fdiv_bug
suffix:semicolon
DECL|member|f00f_bug
r_int
id|f00f_bug
suffix:semicolon
DECL|member|coma_bug
r_int
id|coma_bug
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pmd_quick
r_int
r_int
op_star
id|pmd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|macro|X86_VENDOR_INTEL
mdefine_line|#define X86_VENDOR_INTEL 0
DECL|macro|X86_VENDOR_CYRIX
mdefine_line|#define X86_VENDOR_CYRIX 1
DECL|macro|X86_VENDOR_AMD
mdefine_line|#define X86_VENDOR_AMD 2
DECL|macro|X86_VENDOR_UMC
mdefine_line|#define X86_VENDOR_UMC 3
DECL|macro|X86_VENDOR_NEXGEN
mdefine_line|#define X86_VENDOR_NEXGEN 4
DECL|macro|X86_VENDOR_CENTAUR
mdefine_line|#define X86_VENDOR_CENTAUR 5
DECL|macro|X86_VENDOR_RISE
mdefine_line|#define X86_VENDOR_RISE 6
DECL|macro|X86_VENDOR_TRANSMETA
mdefine_line|#define X86_VENDOR_TRANSMETA 7
DECL|macro|X86_VENDOR_UNKNOWN
mdefine_line|#define X86_VENDOR_UNKNOWN 0xff
multiline_comment|/*&n; * capabilities of CPUs&n; */
r_extern
r_struct
id|cpuinfo_x86
id|boot_cpu_data
suffix:semicolon
r_extern
r_struct
id|tss_struct
id|init_tss
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|cpuinfo_x86
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
macro_line|#else
DECL|macro|cpu_data
mdefine_line|#define cpu_data (&amp;boot_cpu_data)
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
DECL|macro|cpu_has_pge
mdefine_line|#define cpu_has_pge&t;(test_bit(X86_FEATURE_PGE,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_pse
mdefine_line|#define cpu_has_pse&t;(test_bit(X86_FEATURE_PSE,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_pae
mdefine_line|#define cpu_has_pae&t;(test_bit(X86_FEATURE_PAE,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_tsc
mdefine_line|#define cpu_has_tsc&t;(test_bit(X86_FEATURE_TSC,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_de
mdefine_line|#define cpu_has_de&t;(test_bit(X86_FEATURE_DE,   boot_cpu_data.x86_capability))
DECL|macro|cpu_has_vme
mdefine_line|#define cpu_has_vme&t;(test_bit(X86_FEATURE_VME,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_fxsr
mdefine_line|#define cpu_has_fxsr&t;(test_bit(X86_FEATURE_FXSR, boot_cpu_data.x86_capability))
DECL|macro|cpu_has_xmm
mdefine_line|#define cpu_has_xmm&t;(test_bit(X86_FEATURE_XMM,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;(test_bit(X86_FEATURE_FPU,  boot_cpu_data.x86_capability))
DECL|macro|cpu_has_apic
mdefine_line|#define cpu_has_apic&t;(test_bit(X86_FEATURE_APIC, boot_cpu_data.x86_capability))
r_extern
r_char
id|ignore_irq13
suffix:semicolon
r_extern
r_void
id|identify_cpu
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_cpu_info
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dodgy_tsc
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * EFLAGS bits&n; */
DECL|macro|X86_EFLAGS_CF
mdefine_line|#define X86_EFLAGS_CF&t;0x00000001 /* Carry Flag */
DECL|macro|X86_EFLAGS_PF
mdefine_line|#define X86_EFLAGS_PF&t;0x00000004 /* Parity Flag */
DECL|macro|X86_EFLAGS_AF
mdefine_line|#define X86_EFLAGS_AF&t;0x00000010 /* Auxillary carry Flag */
DECL|macro|X86_EFLAGS_ZF
mdefine_line|#define X86_EFLAGS_ZF&t;0x00000040 /* Zero Flag */
DECL|macro|X86_EFLAGS_SF
mdefine_line|#define X86_EFLAGS_SF&t;0x00000080 /* Sign Flag */
DECL|macro|X86_EFLAGS_TF
mdefine_line|#define X86_EFLAGS_TF&t;0x00000100 /* Trap Flag */
DECL|macro|X86_EFLAGS_IF
mdefine_line|#define X86_EFLAGS_IF&t;0x00000200 /* Interrupt Flag */
DECL|macro|X86_EFLAGS_DF
mdefine_line|#define X86_EFLAGS_DF&t;0x00000400 /* Direction Flag */
DECL|macro|X86_EFLAGS_OF
mdefine_line|#define X86_EFLAGS_OF&t;0x00000800 /* Overflow Flag */
DECL|macro|X86_EFLAGS_IOPL
mdefine_line|#define X86_EFLAGS_IOPL&t;0x00003000 /* IOPL mask */
DECL|macro|X86_EFLAGS_NT
mdefine_line|#define X86_EFLAGS_NT&t;0x00004000 /* Nested Task */
DECL|macro|X86_EFLAGS_RF
mdefine_line|#define X86_EFLAGS_RF&t;0x00010000 /* Resume Flag */
DECL|macro|X86_EFLAGS_VM
mdefine_line|#define X86_EFLAGS_VM&t;0x00020000 /* Virtual Mode */
DECL|macro|X86_EFLAGS_AC
mdefine_line|#define X86_EFLAGS_AC&t;0x00040000 /* Alignment Check */
DECL|macro|X86_EFLAGS_VIF
mdefine_line|#define X86_EFLAGS_VIF&t;0x00080000 /* Virtual Interrupt Flag */
DECL|macro|X86_EFLAGS_VIP
mdefine_line|#define X86_EFLAGS_VIP&t;0x00100000 /* Virtual Interrupt Pending */
DECL|macro|X86_EFLAGS_ID
mdefine_line|#define X86_EFLAGS_ID&t;0x00200000 /* CPUID detection flag */
multiline_comment|/*&n; * Generic CPUID function&n; */
DECL|function|cpuid
r_static
r_inline
r_void
id|cpuid
c_func
(paren
r_int
id|op
comma
r_int
op_star
id|eax
comma
r_int
op_star
id|ebx
comma
r_int
op_star
id|ecx
comma
r_int
op_star
id|edx
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
op_star
id|ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
op_star
id|ecx
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * CPUID functions returning a single datum&n; */
DECL|function|cpuid_eax
r_static
r_inline
r_int
r_int
id|cpuid_eax
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|eax
suffix:semicolon
)brace
DECL|function|cpuid_ebx
r_static
r_inline
r_int
r_int
id|cpuid_ebx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|ebx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
id|ebx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|ebx
suffix:semicolon
)brace
DECL|function|cpuid_ecx
r_static
r_inline
r_int
r_int
id|cpuid_ecx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|ecx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=c&quot;
(paren
id|ecx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|ecx
suffix:semicolon
)brace
DECL|function|cpuid_edx
r_static
r_inline
r_int
r_int
id|cpuid_edx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|edx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|edx
suffix:semicolon
)brace
multiline_comment|/*&n; * Intel CPU features in CR4&n; */
DECL|macro|X86_CR4_VME
mdefine_line|#define X86_CR4_VME&t;&t;0x0001&t;/* enable vm86 extensions */
DECL|macro|X86_CR4_PVI
mdefine_line|#define X86_CR4_PVI&t;&t;0x0002&t;/* virtual interrupts flag enable */
DECL|macro|X86_CR4_TSD
mdefine_line|#define X86_CR4_TSD&t;&t;0x0004&t;/* disable time stamp at ipl 3 */
DECL|macro|X86_CR4_DE
mdefine_line|#define X86_CR4_DE&t;&t;0x0008&t;/* enable debugging extensions */
DECL|macro|X86_CR4_PSE
mdefine_line|#define X86_CR4_PSE&t;&t;0x0010&t;/* enable page size extensions */
DECL|macro|X86_CR4_PAE
mdefine_line|#define X86_CR4_PAE&t;&t;0x0020&t;/* enable physical address extensions */
DECL|macro|X86_CR4_MCE
mdefine_line|#define X86_CR4_MCE&t;&t;0x0040&t;/* Machine check enable */
DECL|macro|X86_CR4_PGE
mdefine_line|#define X86_CR4_PGE&t;&t;0x0080&t;/* enable global pages */
DECL|macro|X86_CR4_PCE
mdefine_line|#define X86_CR4_PCE&t;&t;0x0100&t;/* enable performance counters at ipl 3 */
DECL|macro|X86_CR4_OSFXSR
mdefine_line|#define X86_CR4_OSFXSR&t;&t;0x0200&t;/* enable fast FPU save and restore */
DECL|macro|X86_CR4_OSXMMEXCPT
mdefine_line|#define X86_CR4_OSXMMEXCPT&t;0x0400&t;/* enable unmasked SSE exceptions */
multiline_comment|/*&n; * Save the cr4 feature set we&squot;re using (ie&n; * Pentium 4MB enable and PPro Global page&n; * enable), so that any CPU&squot;s that boot up&n; * after us can get the correct flags.&n; */
r_extern
r_int
r_int
id|mmu_cr4_features
suffix:semicolon
DECL|function|set_in_cr4
r_static
r_inline
r_void
id|set_in_cr4
(paren
r_int
r_int
id|mask
)paren
(brace
id|mmu_cr4_features
op_or_assign
id|mask
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr4,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orl %0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%eax,%%cr4&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;irg&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
DECL|function|clear_in_cr4
r_static
r_inline
r_void
id|clear_in_cr4
(paren
r_int
r_int
id|mask
)paren
(brace
id|mmu_cr4_features
op_and_assign
op_complement
id|mask
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr4,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;andl %0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%eax,%%cr4&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;irg&quot;
(paren
op_complement
id|mask
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *      Cyrix CPU configuration register indexes&n; */
DECL|macro|CX86_CCR0
mdefine_line|#define CX86_CCR0 0xc0
DECL|macro|CX86_CCR1
mdefine_line|#define CX86_CCR1 0xc1
DECL|macro|CX86_CCR2
mdefine_line|#define CX86_CCR2 0xc2
DECL|macro|CX86_CCR3
mdefine_line|#define CX86_CCR3 0xc3
DECL|macro|CX86_CCR4
mdefine_line|#define CX86_CCR4 0xe8
DECL|macro|CX86_CCR5
mdefine_line|#define CX86_CCR5 0xe9
DECL|macro|CX86_CCR6
mdefine_line|#define CX86_CCR6 0xea
DECL|macro|CX86_CCR7
mdefine_line|#define CX86_CCR7 0xeb
DECL|macro|CX86_DIR0
mdefine_line|#define CX86_DIR0 0xfe
DECL|macro|CX86_DIR1
mdefine_line|#define CX86_DIR1 0xff
DECL|macro|CX86_ARR_BASE
mdefine_line|#define CX86_ARR_BASE 0xc4
DECL|macro|CX86_RCR_BASE
mdefine_line|#define CX86_RCR_BASE 0xdc
multiline_comment|/*&n; *      Cyrix CPU indexed register access macros&n; */
DECL|macro|getCx86
mdefine_line|#define getCx86(reg) ({ outb((reg), 0x22); inb(0x23); })
DECL|macro|setCx86
mdefine_line|#define setCx86(reg, data) do { &bslash;&n;&t;outb((reg), 0x22); &bslash;&n;&t;outb((data), 0x23); &bslash;&n;} while (0)
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; */
macro_line|#ifdef CONFIG_EISA
r_extern
r_int
id|EISA_bus
suffix:semicolon
macro_line|#else
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus (0)
macro_line|#endif
r_extern
r_int
id|MCA_bus
suffix:semicolon
multiline_comment|/* from system description table in BIOS.  Mostly for MCA use, but&n;others may find it useful. */
r_extern
r_int
r_int
id|machine_id
suffix:semicolon
r_extern
r_int
r_int
id|machine_submodel_id
suffix:semicolon
r_extern
r_int
r_int
id|BIOS_revision
suffix:semicolon
r_extern
r_int
r_int
id|mca_pentium_flag
suffix:semicolon
multiline_comment|/*&n; * User space process size: 3GB (default).&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(PAGE_OFFSET)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
DECL|macro|IO_BITMAP_OFFSET
mdefine_line|#define IO_BITMAP_OFFSET offsetof(struct tss_struct,io_bitmap)
DECL|macro|INVALID_IO_BITMAP_OFFSET
mdefine_line|#define INVALID_IO_BITMAP_OFFSET 0x8000
DECL|struct|i387_fsave_struct
r_struct
id|i387_fsave_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* software status information */
)brace
suffix:semicolon
DECL|struct|i387_fxsave_struct
r_struct
id|i387_fxsave_struct
(brace
DECL|member|cwd
r_int
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
r_int
id|twd
suffix:semicolon
DECL|member|fop
r_int
r_int
id|fop
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|mxcsr
r_int
id|mxcsr
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|xmm_space
r_int
id|xmm_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each XMM-reg = 128 bytes */
DECL|member|padding
r_int
id|padding
(braket
l_int|56
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|struct|i387_soft_struct
r_struct
id|i387_soft_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
DECL|member|ftop
DECL|member|changed
DECL|member|lookahead
DECL|member|no_update
DECL|member|rm
DECL|member|alimit
r_int
r_char
id|ftop
comma
id|changed
comma
id|lookahead
comma
id|no_update
comma
id|rm
comma
id|alimit
suffix:semicolon
DECL|member|info
r_struct
id|info
op_star
id|info
suffix:semicolon
DECL|member|entry_eip
r_int
r_int
id|entry_eip
suffix:semicolon
)brace
suffix:semicolon
DECL|union|i387_union
r_union
id|i387_union
(brace
DECL|member|fsave
r_struct
id|i387_fsave_struct
id|fsave
suffix:semicolon
DECL|member|fxsave
r_struct
id|i387_fxsave_struct
id|fxsave
suffix:semicolon
DECL|member|soft
r_struct
id|i387_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|struct|tss_struct
r_struct
id|tss_struct
(brace
DECL|member|back_link
DECL|member|__blh
r_int
r_int
id|back_link
comma
id|__blh
suffix:semicolon
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
DECL|member|ss0
DECL|member|__ss0h
r_int
r_int
id|ss0
comma
id|__ss0h
suffix:semicolon
DECL|member|esp1
r_int
r_int
id|esp1
suffix:semicolon
DECL|member|ss1
DECL|member|__ss1h
r_int
r_int
id|ss1
comma
id|__ss1h
suffix:semicolon
DECL|member|esp2
r_int
r_int
id|esp2
suffix:semicolon
DECL|member|ss2
DECL|member|__ss2h
r_int
r_int
id|ss2
comma
id|__ss2h
suffix:semicolon
DECL|member|__cr3
r_int
r_int
id|__cr3
suffix:semicolon
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|eax
DECL|member|ecx
DECL|member|edx
DECL|member|ebx
r_int
r_int
id|eax
comma
id|ecx
comma
id|edx
comma
id|ebx
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|ebp
r_int
r_int
id|ebp
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
DECL|member|ldt
DECL|member|__ldth
r_int
r_int
id|ldt
comma
id|__ldth
suffix:semicolon
DECL|member|trace
DECL|member|bitmap
r_int
r_int
id|trace
comma
id|bitmap
suffix:semicolon
DECL|member|io_bitmap
r_int
r_int
id|io_bitmap
(braket
id|IO_BITMAP_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * pads the TSS to be cacheline-aligned (size is 0x100)&n;&t; */
DECL|member|__cacheline_filler
r_int
r_int
id|__cacheline_filler
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|fs
r_int
r_int
id|fs
suffix:semicolon
DECL|member|gs
r_int
r_int
id|gs
suffix:semicolon
multiline_comment|/* Hardware debugging registers */
DECL|member|debugreg
r_int
r_int
id|debugreg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* %%db0-7 debug registers */
multiline_comment|/* fault info */
DECL|member|cr2
DECL|member|trap_no
DECL|member|error_code
r_int
r_int
id|cr2
comma
id|trap_no
comma
id|error_code
suffix:semicolon
multiline_comment|/* floating point info */
DECL|member|i387
r_union
id|i387_union
id|i387
suffix:semicolon
multiline_comment|/* virtual 86 mode info */
DECL|member|vm86_info
r_struct
id|vm86_struct
op_star
id|vm86_info
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|v86flags
DECL|member|v86mask
DECL|member|v86mode
DECL|member|saved_esp0
r_int
r_int
id|v86flags
comma
id|v86mask
comma
id|v86mode
comma
id|saved_esp0
suffix:semicolon
multiline_comment|/* IO permissions */
DECL|member|ioperm
r_int
id|ioperm
suffix:semicolon
DECL|member|io_bitmap
r_int
r_int
id|io_bitmap
(braket
id|IO_BITMAP_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0, 0, 0, 0, &t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ [0 ... 7] = 0 },&t;/* debugging registers */&t;&bslash;&n;&t;0, 0, 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ { 0, }, },&t;&t;/* 387 state */&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,{~0,}&t;&t;&t;/* io permissions */&t;&t;&bslash;&n;}
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,0, /* back_link, __blh */&t;&t;&t;&t;&bslash;&n;&t;sizeof(init_stack) + (long) &amp;init_stack, /* esp0 */&t;&bslash;&n;&t;__KERNEL_DS, 0, /* ss0 */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* stack1, stack2 */&t;&t;&t;&bslash;&n;&t;0, /* cr3 */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,0, /* eip,eflags */&t;&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0, /* eax,ecx,edx,ebx */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0, /* esp,ebp,esi,edi */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* es,cs,ss */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* ds,fs,gs */&t;&t;&t;&t;&bslash;&n;&t;__LDT(0),0, /* ldt */&t;&t;&t;&t;&t;&bslash;&n;&t;0, INVALID_IO_BITMAP_OFFSET, /* tace, bitmap */&t;&t;&bslash;&n;&t;{~0, } /* ioperm */&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_eip, new_esp) do {&t;&t;&bslash;&n;&t;__asm__(&quot;movl %0,%%fs ; movl %0,%%gs&quot;: :&quot;r&quot; (0));&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xds = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xes = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xss = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xcs = __USER_CS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;eip = new_eip;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;esp = new_esp;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
r_extern
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * create a kernel thread without removing it from tasklists&n; */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Copy and release all segment info associated with a VM */
r_extern
r_void
id|copy_segments
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_static
r_inline
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;esp
)paren
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1019])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1022])
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() ((struct task_struct *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p) free_pages((unsigned long) (p), 1)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
DECL|struct|microcode
r_struct
id|microcode
(brace
DECL|member|hdrver
r_int
r_int
id|hdrver
suffix:semicolon
DECL|member|rev
r_int
r_int
id|rev
suffix:semicolon
DECL|member|date
r_int
r_int
id|date
suffix:semicolon
DECL|member|sig
r_int
r_int
id|sig
suffix:semicolon
DECL|member|cksum
r_int
r_int
id|cksum
suffix:semicolon
DECL|member|ldrver
r_int
r_int
id|ldrver
suffix:semicolon
DECL|member|pf
r_int
r_int
id|pf
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|bits
r_int
r_int
id|bits
(braket
l_int|500
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &squot;6&squot; because it used to be for P6 only (but now covers Pentium 4 as well) */
DECL|macro|MICROCODE_IOCFREE
mdefine_line|#define MICROCODE_IOCFREE&t;_IO(&squot;6&squot;,0)
multiline_comment|/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
DECL|function|rep_nop
r_static
r_inline
r_void
id|rep_nop
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rep;nop&quot;
)paren
suffix:semicolon
)brace
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;rep_nop()
multiline_comment|/* Prefetch instructions for Pentium III and AMD Athlon */
macro_line|#ifdef &t;CONFIG_MPENTIUMIII
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;prefetchnta (%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
macro_line|#elif CONFIG_X86_USE_3DNOW
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;prefetch (%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;prefetchw (%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)&t;prefetchw(x)
macro_line|#endif
macro_line|#endif /* __ASM_I386_PROCESSOR_H */
eof
