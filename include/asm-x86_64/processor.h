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
macro_line|#include &lt;asm/mmsegment.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
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
DECL|macro|desc_empty
mdefine_line|#define desc_empty(desc) &bslash;&n;               (!((desc)-&gt;a + (desc)-&gt;b))
DECL|macro|desc_equal
mdefine_line|#define desc_equal(desc1, desc2) &bslash;&n;               (((desc1)-&gt;a == (desc2)-&gt;a) &amp;&amp; ((desc1)-&gt;b == (desc2)-&gt;b))
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; asm volatile(&quot;leaq 1f(%%rip),%0&bslash;n1:&quot;:&quot;=r&quot;(pc)); pc; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; */
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
multiline_comment|/* in KB */
DECL|member|x86_clflush_size
r_int
id|x86_clflush_size
suffix:semicolon
DECL|member|x86_cache_alignment
r_int
id|x86_cache_alignment
suffix:semicolon
DECL|member|x86_tlbsize
r_int
id|x86_tlbsize
suffix:semicolon
multiline_comment|/* number of 4K pages in DTLB/ITLB combined(in pages)*/
DECL|member|x86_virt_bits
DECL|member|x86_phys_bits
id|__u8
id|x86_virt_bits
comma
id|x86_phys_bits
suffix:semicolon
DECL|member|x86_num_cores
id|__u8
id|x86_num_cores
suffix:semicolon
DECL|member|x86_apicid
id|__u8
id|x86_apicid
suffix:semicolon
DECL|member|x86_power
id|__u32
id|x86_power
suffix:semicolon
DECL|member|x86_cpuid_level
id|__u32
id|x86_cpuid_level
suffix:semicolon
multiline_comment|/* Max CPUID function supported */
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
DECL|macro|X86_VENDOR_NUM
mdefine_line|#define X86_VENDOR_NUM 8
DECL|macro|X86_VENDOR_UNKNOWN
mdefine_line|#define X86_VENDOR_UNKNOWN 0xff
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
r_int
r_int
id|init_intel_cacheinfo
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
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
multiline_comment|/*&n; * User space process size. 47bits.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x800000000000)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|IA32_PAGE_OFFSET
mdefine_line|#define IA32_PAGE_OFFSET ((current-&gt;personality &amp; ADDR_LIMIT_3GB) ? 0xc0000000 : 0xFFFFe000)
DECL|macro|TASK_UNMAPPED_32
mdefine_line|#define TASK_UNMAPPED_32 PAGE_ALIGN(IA32_PAGE_OFFSET/3)
DECL|macro|TASK_UNMAPPED_64
mdefine_line|#define TASK_UNMAPPED_64 PAGE_ALIGN(TASK_SIZE/3) 
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;&bslash;&n;&t;(test_thread_flag(TIF_IA32) ? TASK_UNMAPPED_32 : TASK_UNMAPPED_64)  
multiline_comment|/*&n; * Size of io_bitmap.&n; */
DECL|macro|IO_BITMAP_BITS
mdefine_line|#define IO_BITMAP_BITS  65536
DECL|macro|IO_BITMAP_BYTES
mdefine_line|#define IO_BITMAP_BYTES (IO_BITMAP_BITS/8)
DECL|macro|IO_BITMAP_LONGS
mdefine_line|#define IO_BITMAP_LONGS (IO_BITMAP_BYTES/sizeof(long))
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
DECL|member|io_bitmap_base
id|u16
id|io_bitmap_base
suffix:semicolon
multiline_comment|/*&n;&t; * The extra 1 is there because the CPU will access an&n;&t; * additional byte beyond the end of the IO permission&n;&t; * bitmap. The extra byte must be all 1 bits, and must&n;&t; * be within the limit. Thus we have:&n;&t; *&n;&t; * 128 bytes, the bitmap itself, for ports 0..0x3ff&n;&t; * 8 bytes, for an extra &quot;long&quot; of ~0UL&n;&t; */
DECL|member|io_bitmap
r_int
r_int
id|io_bitmap
(braket
id|IO_BITMAP_LONGS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|____cacheline_aligned
suffix:semicolon
r_extern
r_struct
id|cpuinfo_x86
id|boot_cpu_data
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|tss_struct
comma
id|init_tss
)paren
suffix:semicolon
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN&t;16
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|rsp0
r_int
r_int
id|rsp0
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
DECL|member|debugreg0
r_int
r_int
id|debugreg0
suffix:semicolon
DECL|member|debugreg1
r_int
r_int
id|debugreg1
suffix:semicolon
DECL|member|debugreg2
r_int
r_int
id|debugreg2
suffix:semicolon
DECL|member|debugreg3
r_int
r_int
id|debugreg3
suffix:semicolon
DECL|member|debugreg6
r_int
r_int
id|debugreg6
suffix:semicolon
DECL|member|debugreg7
r_int
r_int
id|debugreg7
suffix:semicolon
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
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* IO permissions. the bitmap could be moved into the GDT, that would make&n;   switch faster for a limited number of ioperm using tasks. -AK */
DECL|member|ioperm
r_int
id|ioperm
suffix:semicolon
DECL|member|io_bitmap_ptr
r_int
r_int
op_star
id|io_bitmap_ptr
suffix:semicolon
DECL|member|io_bitmap_max
r_int
id|io_bitmap_max
suffix:semicolon
multiline_comment|/* cached TLS descriptors. */
DECL|member|tls_array
id|u64
id|tls_array
(braket
id|GDT_ENTRY_TLS_ENTRIES
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {}
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|STACKFAULT_STACK
mdefine_line|#define STACKFAULT_STACK 1
DECL|macro|DOUBLEFAULT_STACK
mdefine_line|#define DOUBLEFAULT_STACK 2 
DECL|macro|NMI_STACK
mdefine_line|#define NMI_STACK 3 
DECL|macro|DEBUG_STACK
mdefine_line|#define DEBUG_STACK 4 
DECL|macro|MCE_STACK
mdefine_line|#define MCE_STACK 5
DECL|macro|N_EXCEPTION_STACKS
mdefine_line|#define N_EXCEPTION_STACKS 5  /* hw limit: 7 */
DECL|macro|EXCEPTION_STKSZ
mdefine_line|#define EXCEPTION_STKSZ (PAGE_SIZE &lt;&lt; EXCEPTION_STACK_ORDER)
DECL|macro|EXCEPTION_STACK_ORDER
mdefine_line|#define EXCEPTION_STACK_ORDER 0 
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_rip,new_rsp) do { &bslash;&n;&t;asm volatile(&quot;movl %0,%%fs; movl %0,%%es; movl %0,%%ds&quot;: :&quot;r&quot; (0));&t; &bslash;&n;&t;load_gs_index(0);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(regs)-&gt;rip = (new_rip);&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;rsp = (new_rsp);&t;&t;&t;&t;&t;&t; &bslash;&n;&t;write_pda(oldrsp, (new_rsp));&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;cs = __USER_CS;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;ss = __USER_DS;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(regs)-&gt;eflags = 0x200;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t; &bslash;&n;} while(0) 
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
r_extern
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
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
DECL|struct|microcode_header
r_struct
id|microcode_header
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
DECL|member|datasize
r_int
r_int
id|datasize
suffix:semicolon
DECL|member|totalsize
r_int
r_int
id|totalsize
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|microcode
r_struct
id|microcode
(brace
DECL|member|hdr
r_struct
id|microcode_header
id|hdr
suffix:semicolon
DECL|member|bits
r_int
r_int
id|bits
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|microcode_t
r_typedef
r_struct
id|microcode
id|microcode_t
suffix:semicolon
DECL|typedef|microcode_header_t
r_typedef
r_struct
id|microcode_header
id|microcode_header_t
suffix:semicolon
multiline_comment|/* microcode format is extended from prescott processors */
DECL|struct|extended_signature
r_struct
id|extended_signature
(brace
DECL|member|sig
r_int
r_int
id|sig
suffix:semicolon
DECL|member|pf
r_int
r_int
id|pf
suffix:semicolon
DECL|member|cksum
r_int
r_int
id|cksum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|extended_sigtable
r_struct
id|extended_sigtable
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|cksum
r_int
r_int
id|cksum
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|sigs
r_struct
id|extended_signature
id|sigs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &squot;6&squot; because it used to be for P6 only (but now covers Pentium 4 as well) */
DECL|macro|MICROCODE_IOCFREE
mdefine_line|#define MICROCODE_IOCFREE&t;_IO(&squot;6&squot;,0)
DECL|macro|ASM_NOP1
mdefine_line|#define ASM_NOP1 K8_NOP1
DECL|macro|ASM_NOP2
mdefine_line|#define ASM_NOP2 K8_NOP2
DECL|macro|ASM_NOP3
mdefine_line|#define ASM_NOP3 K8_NOP3
DECL|macro|ASM_NOP4
mdefine_line|#define ASM_NOP4 K8_NOP4
DECL|macro|ASM_NOP5
mdefine_line|#define ASM_NOP5 K8_NOP5
DECL|macro|ASM_NOP6
mdefine_line|#define ASM_NOP6 K8_NOP6
DECL|macro|ASM_NOP7
mdefine_line|#define ASM_NOP7 K8_NOP7
DECL|macro|ASM_NOP8
mdefine_line|#define ASM_NOP8 K8_NOP8
multiline_comment|/* Opteron nops */
DECL|macro|K8_NOP1
mdefine_line|#define K8_NOP1 &quot;.byte 0x90&bslash;n&quot;
DECL|macro|K8_NOP2
mdefine_line|#define K8_NOP2&t;&quot;.byte 0x66,0x90&bslash;n&quot; 
DECL|macro|K8_NOP3
mdefine_line|#define K8_NOP3&t;&quot;.byte 0x66,0x66,0x90&bslash;n&quot; 
DECL|macro|K8_NOP4
mdefine_line|#define K8_NOP4&t;&quot;.byte 0x66,0x66,0x66,0x90&bslash;n&quot; 
DECL|macro|K8_NOP5
mdefine_line|#define K8_NOP5&t;K8_NOP3 K8_NOP2 
DECL|macro|K8_NOP6
mdefine_line|#define K8_NOP6&t;K8_NOP3 K8_NOP3
DECL|macro|K8_NOP7
mdefine_line|#define K8_NOP7&t;K8_NOP4 K8_NOP3
DECL|macro|K8_NOP8
mdefine_line|#define K8_NOP8&t;K8_NOP4 K8_NOP4
DECL|macro|ASM_NOP_MAX
mdefine_line|#define ASM_NOP_MAX 8
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
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Stop speculative execution */
DECL|function|sync_core
r_extern
r_inline
r_void
id|sync_core
c_func
(paren
r_void
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;ebx&quot;
comma
l_string|&quot;ecx&quot;
comma
l_string|&quot;edx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu 1
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|function|prefetch
r_static
r_inline
r_void
id|prefetch
c_func
(paren
r_void
op_star
id|x
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;prefetcht0 %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW 1
DECL|function|prefetchw
r_static
r_inline
r_void
id|prefetchw
c_func
(paren
r_void
op_star
id|x
)paren
(brace
id|alternative_input
c_func
(paren
id|ASM_NOP5
comma
l_string|&quot;prefetchw (%1)&quot;
comma
id|X86_FEATURE_3DNOW
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH 1
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)  prefetchw(x)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()   rep_nop()
multiline_comment|/*&n; *      NSC/Cyrix CPU configuration register indexes&n; */
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
multiline_comment|/*&n; *      NSC/Cyrix CPU indexed register access macros&n; */
DECL|macro|getCx86
mdefine_line|#define getCx86(reg) ({ outb((reg), 0x22); inb(0x23); })
DECL|macro|setCx86
mdefine_line|#define setCx86(reg, data) do { &bslash;&n;&t;outb((reg), 0x22); &bslash;&n;&t;outb((data), 0x23); &bslash;&n;} while (0)
DECL|function|__monitor
r_static
r_inline
r_void
id|__monitor
c_func
(paren
r_const
r_void
op_star
id|eax
comma
r_int
r_int
id|ecx
comma
r_int
r_int
id|edx
)paren
(brace
multiline_comment|/* &quot;monitor %eax,%ecx,%edx;&quot; */
id|asm
r_volatile
(paren
l_string|&quot;.byte 0x0f,0x01,0xc8;&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;c&quot;
(paren
id|ecx
)paren
comma
l_string|&quot;d&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
)brace
DECL|function|__mwait
r_static
r_inline
r_void
id|__mwait
c_func
(paren
r_int
r_int
id|eax
comma
r_int
r_int
id|ecx
)paren
(brace
multiline_comment|/* &quot;mwait %eax,%ecx;&quot; */
id|asm
r_volatile
(paren
l_string|&quot;.byte 0x0f,0x01,0xc9;&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;c&quot;
(paren
id|ecx
)paren
)paren
suffix:semicolon
)brace
DECL|macro|stack_current
mdefine_line|#define stack_current() &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct thread_info *ti;&t;&t;&t;&t;&t;&bslash;&n;&t;asm(&quot;andq %%rsp,%0; &quot;:&quot;=r&quot; (ti) : &quot;0&quot; (CURRENT_MASK));&t;&bslash;&n;&t;ti-&gt;task;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|cache_line_size
mdefine_line|#define cache_line_size() (boot_cpu_data.x86_cache_alignment)
r_extern
r_int
r_int
id|boot_option_idle_override
suffix:semicolon
multiline_comment|/* Boot loader type from the setup header */
r_extern
r_int
id|bootloader_type
suffix:semicolon
macro_line|#endif /* __ASM_X86_64_PROCESSOR_H */
eof
