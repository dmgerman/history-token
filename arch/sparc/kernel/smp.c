multiline_comment|/* smp.c: Sparc SMP support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
DECL|macro|IRQ_RESCHEDULE
mdefine_line|#define IRQ_RESCHEDULE&t;&t;13
DECL|macro|IRQ_STOP_CPU
mdefine_line|#define IRQ_STOP_CPU&t;&t;14
DECL|macro|IRQ_CROSS_CALL
mdefine_line|#define IRQ_CROSS_CALL&t;&t;15
DECL|variable|smp_processors_ready
r_volatile
r_int
id|smp_processors_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpu_present_map
r_int
r_int
id|cpu_present_map
op_assign
l_int|0
suffix:semicolon
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|mid_xlate
r_int
r_char
id|mid_xlate
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
macro_line|#ifdef NOTUSED
DECL|variable|smp_spinning
r_volatile
r_int
r_int
id|smp_spinning
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|smp_proc_in_lock
r_int
r_int
id|smp_proc_in_lock
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_sparc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cpu_offset
r_int
r_int
id|cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|boot_cpu_id
r_int
r_char
id|boot_cpu_id
op_assign
l_int|0
suffix:semicolon
DECL|variable|boot_cpu_id4
r_int
r_char
id|boot_cpu_id4
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* boot_cpu_id &lt;&lt; 2 */
DECL|variable|smp_activated
r_int
id|smp_activated
op_assign
l_int|0
suffix:semicolon
DECL|variable|__cpu_number_map
r_volatile
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__cpu_logical_map
r_volatile
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cacheflush_time
id|cycles_t
id|cacheflush_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX */
multiline_comment|/* The only guaranteed locking primitive available on all Sparc&n; * processors is &squot;ldstub [%reg + immediate], %dest_reg&squot; which atomically&n; * places the current byte at the effective address into dest_reg and&n; * places 0xff there afterwards.  Pretty lame locking primitive&n; * compared to the Alpha and the Intel no?  Most Sparcs have &squot;swap&squot;&n; * instruction which is much better...&n; */
multiline_comment|/* Kernel spinlock */
DECL|variable|__cacheline_aligned_in_smp
id|spinlock_t
id|kernel_flag
id|__cacheline_aligned_in_smp
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Used to make bitops atomic */
DECL|variable|bitops_spinlock
r_int
r_char
id|bitops_spinlock
op_assign
l_int|0
suffix:semicolon
DECL|variable|ipi_count
r_volatile
r_int
r_int
id|ipi_count
suffix:semicolon
DECL|variable|smp_process_available
r_volatile
r_int
id|smp_process_available
op_assign
l_int|0
suffix:semicolon
DECL|variable|smp_commenced
r_volatile
r_int
id|smp_commenced
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not supported on Sparc yet. */
DECL|function|smp_setup
r_void
id|__init
id|smp_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
)brace
multiline_comment|/*&n; *&t;The bootstrap kernel entry code has set these up. Save them for&n; *&t;a given CPU&n; */
DECL|function|smp_store_cpu_info
r_void
id|__init
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
(brace
id|cpu_data
(braket
id|id
)braket
dot
id|udelay_val
op_assign
id|loops_per_jiffy
suffix:semicolon
multiline_comment|/* this is it on sparc. */
)brace
DECL|function|smp_commence
r_void
id|__init
id|smp_commence
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Lets the callin&squot;s below out of their loop.&n;&t; */
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|smp_commenced
op_assign
l_int|1
suffix:semicolon
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Only broken Intel needs this, thus it should not even be referenced&n; * globally...&n; */
DECL|function|initialize_secondary
r_void
id|__init
id|initialize_secondary
c_func
(paren
r_void
)paren
(brace
)brace
r_extern
r_int
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Activate a secondary processor. */
DECL|function|start_secondary
r_int
id|start_secondary
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Start secondary called. Should not happen&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cpu_panic
r_void
id|cpu_panic
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU[%d]: Returns from cpu_idle!&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;SMP bolixed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Cycle through the processors asking the PROM to start each one.&n; */
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__initdata
r_struct
id|linux_prom_registers
id|smp_penguin_ctable
id|__initdata
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|function|smp_boot_cpus
r_void
id|__init
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|smp4m_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp4d_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4m
)paren
id|smp4m_boot_cpus
c_func
(paren
)paren
suffix:semicolon
r_else
id|smp4d_boot_cpus
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_flush_cache_all
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|xc0
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_cache_all
)paren
)paren
suffix:semicolon
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_flush_tlb_all
r_void
id|smp_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|xc0
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_tlb_all
)paren
)paren
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_flush_cache_mm
r_void
id|smp_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc1
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_cache_mm
)paren
comma
(paren
r_int
r_int
)paren
id|mm
)paren
suffix:semicolon
)brace
id|local_flush_cache_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_tlb_mm
r_void
id|smp_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc1
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_tlb_mm
)paren
comma
(paren
r_int
r_int
)paren
id|mm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_eq
l_int|1
op_logical_and
id|current-&gt;active_mm
op_eq
id|mm
)paren
(brace
id|mm-&gt;cpu_vm_mask
op_assign
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
id|local_flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_cache_range
r_void
id|smp_flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc3
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_cache_range
)paren
comma
(paren
r_int
r_int
)paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
id|local_flush_cache_range
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_tlb_range
r_void
id|smp_flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc3
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_tlb_range
)paren
comma
(paren
r_int
r_int
)paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
id|local_flush_tlb_range
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_cache_page
r_void
id|smp_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc2
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_cache_page
)paren
comma
(paren
r_int
r_int
)paren
id|vma
comma
id|page
)paren
suffix:semicolon
)brace
id|local_flush_cache_page
c_func
(paren
id|vma
comma
id|page
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_tlb_page
r_void
id|smp_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc2
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_tlb_page
)paren
comma
(paren
r_int
r_int
)paren
id|vma
comma
id|page
)paren
suffix:semicolon
)brace
id|local_flush_tlb_page
c_func
(paren
id|vma
comma
id|page
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_flush_page_to_ram
r_void
id|smp_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* Current theory is that those who call this are the one&squot;s&n;&t; * who have just dirtied their cache with the pages contents&n;&t; * in kernel space, therefore we only run this on local cpu.&n;&t; *&n;&t; * XXX This experiment failed, research further... -DaveM&n;&t; */
macro_line|#if 1
id|xc1
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_page_to_ram
)paren
comma
id|page
)paren
suffix:semicolon
macro_line|#endif
id|local_flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|smp_flush_sig_insns
r_void
id|smp_flush_sig_insns
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|insn_addr
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|xc2
c_func
(paren
(paren
id|smpfunc_t
)paren
id|BTFIXUP_CALL
c_func
(paren
id|local_flush_sig_insns
)paren
comma
(paren
r_int
r_int
)paren
id|mm
comma
id|insn_addr
)paren
suffix:semicolon
)brace
id|local_flush_sig_insns
c_func
(paren
id|mm
comma
id|insn_addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Reschedule call back. */
DECL|function|smp_reschedule_irq
r_void
id|smp_reschedule_irq
c_func
(paren
r_void
)paren
(brace
id|current-&gt;work.need_resched
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Stopping processors. */
DECL|function|smp_stop_cpu_irq
r_void
id|smp_stop_cpu_irq
c_func
(paren
r_void
)paren
(brace
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|prof_multiplier
r_int
r_int
id|prof_multiplier
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|prof_counter
r_int
r_int
id|prof_counter
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|lvl14_resolution
suffix:semicolon
DECL|function|setup_profiling_timer
r_int
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Prevent level14 ticker IRQ flooding. */
r_if
c_cond
(paren
(paren
op_logical_neg
id|multiplier
)paren
op_logical_or
(paren
id|lvl14_resolution
op_div
id|multiplier
)paren
OL
l_int|500
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
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
)paren
(brace
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|load_profile_irq
c_func
(paren
id|mid_xlate
(braket
id|i
)braket
comma
id|lvl14_resolution
op_div
id|multiplier
)paren
suffix:semicolon
id|prof_multiplier
(braket
id|i
)braket
op_assign
id|multiplier
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_bogo_info
r_void
id|smp_bogo_info
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
id|i
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
)paren
(brace
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Cpu%dBogo&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|i
comma
id|cpu_data
(braket
id|i
)braket
dot
id|udelay_val
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|udelay_val
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_info
r_void
id|smp_info
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
id|i
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
)paren
(brace
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;CPU%d&bslash;t&bslash;t: online&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
eof
