multiline_comment|/* &n; * X86-64 specific CPU setup.&n; * Copyright (C) 1995  Linus Torvalds&n; * Copyright 2001, 2002, 2003 SuSE Labs / Andi Kleen.&n; * See setup.c for older changelog.&n; * $Id: setup64.c,v 1.12 2002/03/21 10:09:17 ak Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
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
id|cpumask_t
id|cpu_initialized
id|__initdata
op_assign
id|CPU_MASK_NONE
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
DECL|variable|boot_cpu_stack
r_char
id|boot_cpu_stack
(braket
id|IRQSTACKSIZE
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.bss.page_aligned&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|__supported_pte_mask
r_int
r_int
id|__supported_pte_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|do_not_nx
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* noexec=on|off&n;Control non executable mappings for 64bit processes.&n;&n;on&t;Enable(default)&n;off&t;Disable&n;*/
DECL|function|nonx_setup
r_void
id|__init
id|nonx_setup
c_func
(paren
r_const
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
l_string|&quot;on&quot;
comma
l_int|2
)paren
)paren
(brace
id|__supported_pte_mask
op_or_assign
id|_PAGE_NX
suffix:semicolon
id|do_not_nx
op_assign
l_int|0
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
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
(brace
id|do_not_nx
op_assign
l_int|1
suffix:semicolon
id|__supported_pte_mask
op_and_assign
op_complement
id|_PAGE_NX
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Great future plan:&n; * Declare PDA itself and support (irqstack,tss,pgd) as per cpu data.&n; * Always point %gs to its beginning&n; */
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
id|i
suffix:semicolon
r_int
r_int
id|size
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
macro_line|#ifdef CONFIG_MODULES
r_if
c_cond
(paren
id|size
OL
id|PERCPU_ENOUGH_ROOM
)paren
id|size
op_assign
id|PERCPU_ENOUGH_ROOM
suffix:semicolon
macro_line|#endif
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
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NODE_DATA
c_func
(paren
id|cpu_to_node
c_func
(paren
id|i
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpu with no node %d, num_online_nodes %d&bslash;n&quot;
comma
id|i
comma
id|num_online_nodes
c_func
(paren
)paren
)paren
suffix:semicolon
id|ptr
op_assign
id|alloc_bootmem
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
id|alloc_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|cpu_to_node
c_func
(paren
id|i
)paren
)paren
comma
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot allocate cpu data for CPU %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|cpu_pda
(braket
id|i
)braket
dot
id|data_offset
op_assign
id|ptr
op_minus
id|__per_cpu_start
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|__per_cpu_start
comma
id|__per_cpu_end
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
)brace
)brace
DECL|function|pda_init
r_void
id|pda_init
c_func
(paren
r_int
id|cpu
)paren
(brace
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
id|pda-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|pda-&gt;mmu_state
op_assign
l_int|0
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
l_string|&quot;cannot allocate irqstack for cpu %d&quot;
comma
id|cpu
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%cr3&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__pa_symbol
c_func
(paren
op_amp
id|init_level4_pgt
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
)brace
DECL|variable|boot_exception_stacks
r_char
id|boot_exception_stacks
(braket
id|N_EXCEPTION_STACKS
op_star
id|EXCEPTION_STKSZ
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.bss.page_aligned&quot;
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* May not be marked __init: used by software suspend */
DECL|function|syscall_init
r_void
id|syscall_init
c_func
(paren
r_void
)paren
(brace
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
id|syscall32_cpu_init
(paren
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
)brace
DECL|function|check_efer
r_void
id|__init
id|check_efer
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|efer
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
)brace
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
id|per_cpu
c_func
(paren
id|init_tss
comma
id|cpu
)paren
suffix:semicolon
r_int
r_int
id|v
suffix:semicolon
r_char
op_star
id|estacks
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
suffix:semicolon
r_int
id|i
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
id|cpu_test_and_set
c_func
(paren
id|cpu
comma
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
id|asm
r_volatile
(paren
l_string|&quot;lgdt %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|cpu_gdt_descr
(braket
id|cpu
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lidt %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
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
id|syscall_init
c_func
(paren
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
id|check_efer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set up and load the per-CPU TSS&n;&t; */
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
r_if
c_cond
(paren
id|cpu
)paren
(brace
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
id|EXCEPTION_STACK_ORDER
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
l_string|&quot;Cannot allocate exception stack %ld %d&bslash;n&quot;
comma
id|v
comma
id|cpu
)paren
suffix:semicolon
)brace
id|estacks
op_add_assign
id|EXCEPTION_STKSZ
suffix:semicolon
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
)brace
id|t-&gt;io_bitmap_base
op_assign
m_offsetof
(paren
r_struct
id|tss_struct
comma
id|io_bitmap
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * &lt;= is required because the CPU will access up to&n;&t; * 8 bits beyond the end of the IO permission bitmap.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|IO_BITMAP_LONGS
suffix:semicolon
id|i
op_increment
)paren
id|t-&gt;io_bitmap
(braket
id|i
)braket
op_assign
op_complement
l_int|0UL
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
