multiline_comment|/* &n; * X86-64 specific setup part.&n; * Copyright (C) 1995  Linus Torvalds&n; * Copyright 2001 2002 SuSE Labs / Andi Kleen.&n; * See setup.c for older changelog.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
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
r_static
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
DECL|variable|gdt_descr
r_struct
id|desc_ptr
id|gdt_descr
op_assign
(brace
l_int|0
multiline_comment|/* filled in */
comma
(paren
r_int
r_int
)paren
id|gdt_table
)brace
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
DECL|function|pda_init
r_void
id|pda_init
c_func
(paren
r_int
id|cpu
)paren
(brace
id|cpu_pda
(braket
id|cpu
)braket
dot
id|me
op_assign
op_amp
id|cpu_pda
(braket
id|cpu
)braket
suffix:semicolon
id|cpu_pda
(braket
id|cpu
)braket
dot
id|cpunumber
op_assign
id|cpu
suffix:semicolon
id|cpu_pda
(braket
id|cpu
)braket
dot
id|irqcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|cpu_pda
(braket
id|cpu
)braket
dot
id|irqstackptr
op_assign
id|cpu_pda
(braket
id|cpu
)braket
dot
id|irqstack
op_plus
r_sizeof
(paren
id|cpu_pda
(braket
l_int|0
)braket
dot
id|irqstack
)paren
suffix:semicolon
multiline_comment|/* others are initialized in smpboot.c */
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|cpu_pda
(braket
id|cpu
)braket
dot
id|pcurrent
op_assign
op_amp
id|init_task
suffix:semicolon
id|cpu_pda
(braket
id|cpu
)braket
dot
id|kernelstack
op_assign
(paren
r_int
r_int
)paren
op_amp
id|init_thread_union
op_plus
id|THREAD_SIZE
op_minus
id|PDA_STACKOFFSET
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%gs ; movl %0,%%fs&quot;
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
)brace
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU. Some data is already&n; * initialized (naturally) in the bootstrap process, such as the GDT&n; * and IDT. We reload them nevertheless, this function acts as a&n; * &squot;CPU state barrier&squot;, nothing should get across.&n; */
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
id|nr
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|cpu
suffix:semicolon
macro_line|#else
r_int
id|nr
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
id|nr
)braket
suffix:semicolon
r_int
r_int
id|v
suffix:semicolon
multiline_comment|/* CPU 0 is initialised in head64.c */
r_if
c_cond
(paren
id|nr
op_ne
l_int|0
)paren
id|pda_init
c_func
(paren
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|nr
comma
op_amp
id|cpu_initialized
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU#%d already initialized!&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Initializing CPU#%d&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_vme
op_logical_or
id|cpu_has_tsc
op_logical_or
id|cpu_has_de
)paren
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
id|gdt_descr.size
op_assign
(paren
id|__u8
op_star
)paren
id|gdt_end
op_minus
(paren
id|__u8
op_star
)paren
id|gdt_table
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lgdt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|gdt_descr
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
multiline_comment|/*&n;&t; * Delete NT&n;&t; */
id|__asm__
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
id|rdmsrl
c_func
(paren
id|MSR_EFER
comma
id|v
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_EFER
comma
id|v
op_or
l_int|1
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t; * set up and load the per-CPU TSS and LDT&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|enter_lazy_tlb
c_func
(paren
op_amp
id|init_mm
comma
id|current
comma
id|nr
)paren
suffix:semicolon
id|set_tssldt_descriptor
c_func
(paren
(paren
id|__u8
op_star
)paren
id|tss_start
op_plus
(paren
id|nr
op_star
l_int|16
)paren
comma
(paren
r_int
r_int
)paren
id|t
comma
id|DESC_TSS
comma
m_offsetof
(paren
r_struct
id|tss_struct
comma
id|io_bitmap
)paren
)paren
suffix:semicolon
id|load_TR
c_func
(paren
id|nr
)paren
suffix:semicolon
id|load_LDT
c_func
(paren
op_amp
id|init_mm
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
multiline_comment|/*&n;&t; * Force FPU initialization:&n;&t; */
id|clear_thread_flag
c_func
(paren
id|TIF_USEDFPU
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
eof
