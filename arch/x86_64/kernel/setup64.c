multiline_comment|/* &n; * X86-64 specific CPU setup.&n; * Copyright (C) 1995  Linus Torvalds&n; * Copyright 2001, 2002, 2003 SuSE Labs / Andi Kleen.&n; * See setup.c for older changelog.&n; * $Id: setup64.c,v 1.12 2002/03/21 10:09:17 ak Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
DECL|variable|__initdata
r_char
id|x86_boot_params
(braket
l_int|2048
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_int
id|cpu_initialized
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__cacheline_aligned
r_struct
id|x8664_pda
id|cpu_pda
(braket
id|NR_CPUS
)braket
id|__cacheline_aligned
suffix:semicolon
r_extern
r_void
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_cstar_target
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|task_struct
id|init_task
suffix:semicolon
r_extern
r_int
r_char
id|__per_cpu_start
(braket
)braket
comma
id|__per_cpu_end
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|desc_ptr
id|cpu_gdt_descr
(braket
)braket
suffix:semicolon
DECL|variable|idt_descr
r_struct
id|desc_ptr
id|idt_descr
op_assign
(brace
l_int|256
op_star
l_int|16
comma
(paren
r_int
r_int
)paren
id|idt_table
)brace
suffix:semicolon
DECL|variable|__cacheline_aligned
r_char
id|boot_cpu_stack
(braket
id|IRQSTACKSIZE
)braket
id|__cacheline_aligned
suffix:semicolon
DECL|variable|__supported_pte_mask
r_int
r_int
id|__supported_pte_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
DECL|variable|do_not_nx
r_static
r_int
id|do_not_nx
op_assign
l_int|0
suffix:semicolon
DECL|function|nonx_setup
r_static
r_int
id|__init
id|nonx_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
(brace
id|__supported_pte_mask
op_and_assign
op_complement
id|_PAGE_NX
suffix:semicolon
id|do_not_nx
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;on&quot;
comma
l_int|3
)paren
)paren
(brace
id|do_not_nx
op_assign
l_int|0
suffix:semicolon
id|__supported_pte_mask
op_or_assign
id|_PAGE_NX
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;noexec=&quot;
comma
id|nonx_setup
)paren
suffix:semicolon
macro_line|#ifndef  __GENERIC_PER_CPU
DECL|variable|__per_cpu_offset
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|setup_per_cpu_areas
r_void
id|__init
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|size
comma
id|i
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* Copy section for each CPU (we discard the original) */
id|size
op_assign
id|ALIGN
c_func
(paren
id|__per_cpu_end
op_minus
id|__per_cpu_start
comma
id|SMP_CACHE_BYTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
id|ptr
op_assign
id|alloc_bootmem
c_func
(paren
id|size
op_star
id|NR_CPUS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
comma
id|ptr
op_add_assign
id|size
)paren
(brace
multiline_comment|/* hide this from the compiler to avoid problems */
r_int
r_int
id|offset
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;subq %[b],%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|offset
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ptr
)paren
comma
(braket
id|b
)braket
l_string|&quot;r&quot;
(paren
op_amp
id|__per_cpu_start
)paren
)paren
suffix:semicolon
id|__per_cpu_offset
(braket
id|i
)braket
op_assign
id|offset
suffix:semicolon
id|cpu_pda
(braket
id|i
)braket
dot
id|cpudata_offset
op_assign
id|offset
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|__per_cpu_start
comma
id|size
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|pda_init
r_void
id|pda_init
c_func
(paren
r_int
id|cpu
)paren
(brace
id|pml4_t
op_star
id|level4
suffix:semicolon
r_struct
id|x8664_pda
op_star
id|pda
op_assign
op_amp
id|cpu_pda
(braket
id|cpu
)braket
suffix:semicolon
multiline_comment|/* Setup up data that may be needed in __get_free_pages early */
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%fs ; movl %0,%%gs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_GS_BASE
comma
id|cpu_pda
op_plus
id|cpu
)paren
suffix:semicolon
id|pda-&gt;me
op_assign
id|pda
suffix:semicolon
id|pda-&gt;cpunumber
op_assign
id|cpu
suffix:semicolon
id|pda-&gt;irqcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|pda-&gt;cpudata_offset
op_assign
l_int|0
suffix:semicolon
id|pda-&gt;kernelstack
op_assign
(paren
r_int
r_int
)paren
id|stack_thread_info
c_func
(paren
)paren
op_minus
id|PDA_STACKOFFSET
op_plus
id|THREAD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
multiline_comment|/* others are initialized in smpboot.c */
id|pda-&gt;pcurrent
op_assign
op_amp
id|init_task
suffix:semicolon
id|pda-&gt;irqstackptr
op_assign
id|boot_cpu_stack
suffix:semicolon
id|level4
op_assign
id|init_level4_pgt
suffix:semicolon
)brace
r_else
(brace
id|pda-&gt;irqstackptr
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|IRQSTACK_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pda-&gt;irqstackptr
)paren
id|panic
c_func
(paren
l_string|&quot;cannot allocate irqstack for cpu %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|level4
op_assign
(paren
id|pml4_t
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|level4
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot allocate top level page for cpu %d&quot;
comma
id|cpu
)paren
suffix:semicolon
id|pda-&gt;level4_pgt
op_assign
(paren
r_int
r_int
op_star
)paren
id|level4
suffix:semicolon
r_if
c_cond
(paren
id|level4
op_ne
id|init_level4_pgt
)paren
id|memcpy
c_func
(paren
id|level4
comma
op_amp
id|init_level4_pgt
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pml4
c_func
(paren
id|level4
op_plus
l_int|510
comma
id|mk_kernel_pml4
c_func
(paren
id|__pa_symbol
c_func
(paren
id|boot_vmalloc_pgt
)paren
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%cr3&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__pa
c_func
(paren
id|level4
)paren
)paren
)paren
suffix:semicolon
id|pda-&gt;irqstackptr
op_add_assign
id|IRQSTACKSIZE
op_minus
l_int|64
suffix:semicolon
id|pda-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|pda-&gt;mmu_state
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|EXCEPTION_STK_ORDER
mdefine_line|#define EXCEPTION_STK_ORDER 0 /* &gt;= N_EXCEPTION_STACKS*EXCEPTION_STKSZ */
DECL|variable|boot_exception_stacks
r_char
id|boot_exception_stacks
(braket
id|N_EXCEPTION_STACKS
op_star
id|EXCEPTION_STKSZ
)braket
suffix:semicolon
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU. Some data is already&n; * initialized (naturally) in the bootstrap process, such as the GDT&n; * and IDT. We reload them nevertheless, this function acts as a&n; * &squot;CPU state barrier&squot;, nothing should get across.&n; * A lot of state is already set up in PDA init.&n; */
DECL|function|cpu_init
r_void
id|__init
id|cpu_init
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
id|cpu
op_assign
id|stack_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_struct
id|tss_struct
op_star
id|t
op_assign
op_amp
id|init_tss
(braket
id|cpu
)braket
suffix:semicolon
r_int
r_int
id|v
comma
id|efer
suffix:semicolon
r_char
op_star
id|estacks
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
suffix:semicolon
multiline_comment|/* CPU 0 is initialised in head64.c */
r_if
c_cond
(paren
id|cpu
op_ne
l_int|0
)paren
(brace
id|pda_init
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|estacks
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|estacks
)paren
id|panic
c_func
(paren
l_string|&quot;Can&squot;t allocate exception stacks for CPU %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
)brace
r_else
id|estacks
op_assign
id|boot_exception_stacks
suffix:semicolon
id|me
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|cpu
comma
op_amp
id|cpu_initialized
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;CPU#%d already initialized!&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initializing CPU#%d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|clear_in_cr4
c_func
(paren
id|X86_CR4_VME
op_or
id|X86_CR4_PVI
op_or
id|X86_CR4_TSD
op_or
id|X86_CR4_DE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the per-CPU GDT with the boot GDT,&n;&t; * and set up the GDT descriptor:&n;&t; */
r_if
c_cond
(paren
id|cpu
)paren
(brace
id|memcpy
c_func
(paren
id|cpu_gdt_table
(braket
id|cpu
)braket
comma
id|cpu_gdt_table
(braket
l_int|0
)braket
comma
id|GDT_SIZE
)paren
suffix:semicolon
)brace
id|cpu_gdt_descr
(braket
id|cpu
)braket
dot
id|size
op_assign
id|GDT_SIZE
suffix:semicolon
id|cpu_gdt_descr
(braket
id|cpu
)braket
dot
id|address
op_assign
(paren
r_int
r_int
)paren
id|cpu_gdt_table
(braket
id|cpu
)braket
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lgdt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|cpu_gdt_descr
(braket
id|cpu
)braket
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|idt_descr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|me-&gt;thread.tls_array
comma
id|cpu_gdt_table
(braket
id|cpu
)braket
comma
id|GDT_ENTRY_TLS_ENTRIES
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Delete NT&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;pushfq ; popq %%rax ; btr $14,%%rax ; pushq %%rax ; popfq&quot;
op_scope_resolution
suffix:colon
l_string|&quot;eax&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * LSTAR and STAR live in a bit strange symbiosis.&n;&t; * They both write to the same internal register. STAR allows to set CS/DS&n;&t; * but only a 32bit target. LSTAR sets the 64bit rip. &t; &n;&t; */
id|wrmsrl
c_func
(paren
id|MSR_STAR
comma
(paren
(paren
id|u64
)paren
id|__USER32_CS
)paren
op_lshift
l_int|48
op_or
(paren
(paren
id|u64
)paren
id|__KERNEL_CS
)paren
op_lshift
l_int|32
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_LSTAR
comma
id|system_call
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_EMULATION   &t;&t;
id|wrmsrl
c_func
(paren
id|MSR_CSTAR
comma
id|ia32_cstar_target
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Flags to clear on syscall */
id|wrmsrl
c_func
(paren
id|MSR_SYSCALL_MASK
comma
id|EF_TF
op_or
id|EF_DF
op_or
id|EF_IE
op_or
l_int|0x3000
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_FS_BASE
comma
l_int|0
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
l_int|0
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_EFER
comma
id|efer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|efer
op_amp
id|EFER_NX
)paren
op_logical_or
id|do_not_nx
)paren
(brace
id|__supported_pte_mask
op_and_assign
op_complement
id|_PAGE_NX
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * set up and load the per-CPU TSS&n;&t; */
id|estacks
op_add_assign
id|EXCEPTION_STKSZ
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
l_int|0
suffix:semicolon
id|v
OL
id|N_EXCEPTION_STACKS
suffix:semicolon
id|v
op_increment
)paren
(brace
id|t-&gt;ist
(braket
id|v
)braket
op_assign
(paren
r_int
r_int
)paren
id|estacks
suffix:semicolon
id|estacks
op_add_assign
id|EXCEPTION_STKSZ
suffix:semicolon
)brace
id|t-&gt;io_map_base
op_assign
id|INVALID_IO_BITMAP_OFFSET
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|me-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|enter_lazy_tlb
c_func
(paren
op_amp
id|init_mm
comma
id|me
comma
id|cpu
)paren
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|cpu
comma
id|t
)paren
suffix:semicolon
id|load_TR_desc
c_func
(paren
)paren
suffix:semicolon
id|load_LDT
c_func
(paren
op_amp
id|init_mm.context
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear all 6 debug registers:&n;&t; */
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|0
)paren
suffix:semicolon
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|1
)paren
suffix:semicolon
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|2
)paren
suffix:semicolon
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|3
)paren
suffix:semicolon
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|6
)paren
suffix:semicolon
id|set_debug
c_func
(paren
l_int|0UL
comma
l_int|7
)paren
suffix:semicolon
id|fpu_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
