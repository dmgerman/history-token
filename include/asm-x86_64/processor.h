multiline_comment|/*&n; * include/asm-x86_64/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_X86_64_PROCESSOR_H
DECL|macro|__ASM_X86_64_PROCESSOR_H
mdefine_line|#define __ASM_X86_64_PROCESSOR_H
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/cpufeature.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|TF_MASK
mdefine_line|#define TF_MASK&t;&t;0x00000100
DECL|macro|IF_MASK
mdefine_line|#define IF_MASK&t;&t;0x00000200
DECL|macro|IOPL_MASK
mdefine_line|#define IOPL_MASK&t;0x00003000
DECL|macro|NT_MASK
mdefine_line|#define NT_MASK&t;&t;0x00004000
DECL|macro|VM_MASK
mdefine_line|#define VM_MASK&t;&t;0x00020000
DECL|macro|AC_MASK
mdefine_line|#define AC_MASK&t;&t;0x00040000
DECL|macro|VIF_MASK
mdefine_line|#define VIF_MASK&t;0x00080000&t;/* virtual interrupt flag */
DECL|macro|VIP_MASK
mdefine_line|#define VIP_MASK&t;0x00100000&t;/* virtual interrupt pending */
DECL|macro|ID_MASK
mdefine_line|#define ID_MASK&t;&t;0x00200000
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; asm volatile(&quot;leaq 1f(%%rip),%0&bslash;n1:&quot;:&quot;=r&quot;(pc)); pc; })
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
multiline_comment|/* We know that wp_works_ok = 1, hlt_works_ok = 1, hard_math = 1,&n;     etc... */
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
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
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
mdefine_line|#define cpu_data &amp;boot_cpu_data
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
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
multiline_comment|/*&n; *&t;Generic CPUID function&n; * &t;FIXME: This really belongs to msr.h&n; */
DECL|function|cpuid
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
l_string|&quot;movq %%cr4,%%rax&bslash;n&bslash;t&quot;
l_string|&quot;orq %0,%%rax&bslash;n&bslash;t&quot;
l_string|&quot;movq %%rax,%%cr4&bslash;n&quot;
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
l_string|&quot;movq %%cr4,%%rax&bslash;n&bslash;t&quot;
l_string|&quot;andq %0,%%rax&bslash;n&bslash;t&quot;
l_string|&quot;movq %%rax,%%cr4&bslash;n&quot;
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
macro_line|#if 0
multiline_comment|/*&n; *      Cyrix CPU configuration register indexes&n; */
mdefine_line|#define CX86_CCR0 0xc0
mdefine_line|#define CX86_CCR1 0xc1
mdefine_line|#define CX86_CCR2 0xc2
mdefine_line|#define CX86_CCR3 0xc3
mdefine_line|#define CX86_CCR4 0xe8
mdefine_line|#define CX86_CCR5 0xe9
mdefine_line|#define CX86_CCR6 0xea
mdefine_line|#define CX86_CCR7 0xeb
mdefine_line|#define CX86_DIR0 0xfe
mdefine_line|#define CX86_DIR1 0xff
mdefine_line|#define CX86_ARR_BASE 0xc4
mdefine_line|#define CX86_RCR_BASE 0xdc
multiline_comment|/*&n; *      Cyrix CPU indexed register access macros&n; */
mdefine_line|#define getCx86(reg) ({ outb((reg), 0x22); inb(0x23); })
mdefine_line|#define setCx86(reg, data) do { &bslash;&n;&t;outb((reg), 0x22); &bslash;&n;&t;outb((data), 0x23); &bslash;&n;} while (0)
macro_line|#endif
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro
multiline_comment|/*&n; * User space process size: 512GB - 1GB (default).&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x0000007fc0000000)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_32
mdefine_line|#define TASK_UNMAPPED_32 0x40000000
DECL|macro|TASK_UNMAPPED_64
mdefine_line|#define TASK_UNMAPPED_64 (TASK_SIZE/3) 
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;&bslash;&n;&t;(test_thread_flags(TIF_IA32) ? TASK_UNMAPPED_32 : TASK_UNMAPPED_64)  
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
DECL|macro|IO_BITMAP_OFFSET
mdefine_line|#define IO_BITMAP_OFFSET offsetof(struct tss_struct,io_bitmap)
DECL|macro|INVALID_IO_BITMAP_OFFSET
mdefine_line|#define INVALID_IO_BITMAP_OFFSET 0x8000
DECL|struct|i387_fxsave_struct
r_struct
id|i387_fxsave_struct
(brace
DECL|member|cwd
id|u16
id|cwd
suffix:semicolon
DECL|member|swd
id|u16
id|swd
suffix:semicolon
DECL|member|twd
id|u16
id|twd
suffix:semicolon
DECL|member|fop
id|u16
id|fop
suffix:semicolon
DECL|member|rip
id|u64
id|rip
suffix:semicolon
DECL|member|rdp
id|u64
id|rdp
suffix:semicolon
DECL|member|mxcsr
id|u32
id|mxcsr
suffix:semicolon
DECL|member|mxcsr_mask
id|u32
id|mxcsr_mask
suffix:semicolon
DECL|member|st_space
id|u32
id|st_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|xmm_space
id|u32
id|xmm_space
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 16*16 bytes for each XMM-reg = 128 bytes */
DECL|member|padding
id|u32
id|padding
(braket
l_int|24
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
DECL|union|i387_union
r_union
id|i387_union
(brace
DECL|member|fxsave
r_struct
id|i387_fxsave_struct
id|fxsave
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
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|rsp0
id|u64
id|rsp0
suffix:semicolon
DECL|member|rsp1
id|u64
id|rsp1
suffix:semicolon
DECL|member|rsp2
id|u64
id|rsp2
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
DECL|member|ist
id|u64
id|ist
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|member|reserved5
id|u16
id|reserved5
suffix:semicolon
DECL|member|io_map_base
id|u16
id|io_map_base
suffix:semicolon
DECL|member|io_bitmap
id|u32
id|io_bitmap
(braket
id|IO_BITMAP_SIZE
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|rsp0
r_int
r_int
id|rsp0
suffix:semicolon
DECL|member|rip
r_int
r_int
id|rip
suffix:semicolon
DECL|member|rsp
r_int
r_int
id|rsp
suffix:semicolon
DECL|member|userrsp
r_int
r_int
id|userrsp
suffix:semicolon
multiline_comment|/* Copy from PDA */
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
DECL|member|es
DECL|member|ds
DECL|member|fsindex
DECL|member|gsindex
r_int
r_int
id|es
comma
id|ds
comma
id|fsindex
comma
id|gsindex
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
multiline_comment|/* IO permissions. the bitmap could be moved into the GDT, that would make&n;   switch faster for a limited number of ioperm using tasks. -AK */
DECL|member|ioperm
r_int
id|ioperm
suffix:semicolon
DECL|member|io_bitmap
id|u32
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
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&bslash;&n;}
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|STACKFAULT_STACK
mdefine_line|#define STACKFAULT_STACK 1
DECL|macro|DOUBLEFAULT_STACK
mdefine_line|#define DOUBLEFAULT_STACK 2 
DECL|macro|NMI_STACK
mdefine_line|#define NMI_STACK 3 
DECL|macro|N_EXCEPTION_STACKS
mdefine_line|#define N_EXCEPTION_STACKS 3  /* hw limit: 7 */
DECL|macro|EXCEPTION_STKSZ
mdefine_line|#define EXCEPTION_STKSZ 1024
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_rip,new_rsp) do { &bslash;&n;&t;__asm__(&quot;movl %0,%%fs; movl %0,%%es; movl %0,%%ds&quot;: :&quot;r&quot; (0));&t;&t; &bslash;&n;&t;wrmsrl(MSR_KERNEL_GS_BASE, 0);&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;rip = (new_rip);&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;rsp = (new_rsp);&t;&t;&t;&t;&t;&t; &bslash;&n;&t;write_pda(oldrsp, (new_rsp));&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;cs = __USER_CS;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;ss = __USER_DS;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;eflags = 0x200;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t; &bslash;&n;} while(0) 
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
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; * What is this good for? it will be always the scheduler or ret_from_fork.&n; */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(t) (*(unsigned long *)((t)-&gt;thread.rsp - 8))
r_extern
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
mdefine_line|#define KSTK_EIP(tsk) &bslash;&n;&t;(((struct pt_regs *)(tsk-&gt;thread.rsp0 - sizeof(struct pt_regs)))-&gt;rip)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) -1 /* sorry. doesn&squot;t work for syscall. */
multiline_comment|/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
DECL|function|rep_nop
r_extern
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
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu 1
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|macro|prefetch
mdefine_line|#define prefetch(x) __builtin_prefetch((x),0)
DECL|macro|prefetchw
mdefine_line|#define prefetchw(x) __builtin_prefetch((x),1)
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)  prefetchw(x)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()   rep_nop()
macro_line|#endif /* __ASM_X86_64_PROCESSOR_H */
eof
