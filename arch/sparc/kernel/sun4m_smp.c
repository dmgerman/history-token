multiline_comment|/* sun4m_smp.c: Sparc SUN4M SMP support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
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
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/cpudata.h&gt;
DECL|macro|IRQ_RESCHEDULE
mdefine_line|#define IRQ_RESCHEDULE&t;&t;13
DECL|macro|IRQ_STOP_CPU
mdefine_line|#define IRQ_STOP_CPU&t;&t;14
DECL|macro|IRQ_CROSS_CALL
mdefine_line|#define IRQ_CROSS_CALL&t;&t;15
r_extern
id|ctxd_t
op_star
id|srmmu_ctx_table_phys
suffix:semicolon
r_extern
r_void
id|calibrate_delay
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_processors_ready
suffix:semicolon
r_extern
r_int
id|smp_num_cpus
suffix:semicolon
r_extern
r_int
id|smp_threads_ready
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
r_int
id|smp_activated
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|ipi_count
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_process_available
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_commenced
suffix:semicolon
r_extern
r_int
id|__smp4m_processor_id
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*#define SMP_DEBUG*/
macro_line|#ifdef SMP_DEBUG
DECL|macro|SMP_PRINTK
mdefine_line|#define SMP_PRINTK(x)&t;printk x
macro_line|#else
DECL|macro|SMP_PRINTK
mdefine_line|#define SMP_PRINTK(x)
macro_line|#endif
DECL|function|swap
r_static
r_inline
r_int
r_int
id|swap
c_func
(paren
r_volatile
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;swap [%1], %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;1&quot;
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_void
id|smp_setup_percpu_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|smp4m_callin
r_void
id|__init
id|smp4m_callin
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
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
id|set_irq_udt
c_func
(paren
id|boot_cpu_id
)paren
suffix:semicolon
multiline_comment|/* Get our local ticker going. */
id|smp_setup_percpu_timer
c_func
(paren
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
id|cpuid
)paren
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
multiline_comment|/*&n;&t; * Unblock the master CPU _only_ when the scheduler state&n;&t; * of all secondary CPUs will be up-to-date, so after&n;&t; * the SMP initialization the master will be just allowed&n;&t; * to call the scheduler code.&n;&t; */
multiline_comment|/* Allow master to continue. */
id|swap
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|cpu_callin_map
(braket
id|cpuid
)braket
comma
l_int|1
)paren
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
id|cpu_probe
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fix idle thread fields. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%0], %%g6&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|current_set
(braket
id|cpuid
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
multiline_comment|/* paranoid */
)paren
suffix:semicolon
multiline_comment|/* Attach to the address space of init_task. */
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
r_while
c_loop
(paren
op_logical_neg
id|smp_commenced
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_panic
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Cycle through the processors asking the PROM to start each one.&n; */
r_extern
r_struct
id|linux_prom_registers
id|smp_penguin_ctable
suffix:semicolon
r_extern
r_int
r_int
id|trapbase_cpu1
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|trapbase_cpu2
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|trapbase_cpu3
(braket
)braket
suffix:semicolon
DECL|function|smp4m_boot_cpus
r_void
id|__init
id|smp4m_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_int
id|cpucount
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|mid
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Entering SMP Mode...&bslash;n&quot;
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|cpus_clear
c_func
(paren
id|cpu_present_map
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|cpu_find_by_instance
c_func
(paren
id|i
comma
l_int|NULL
comma
op_amp
id|mid
)paren
suffix:semicolon
id|i
op_increment
)paren
id|cpu_set
c_func
(paren
id|mid
comma
id|cpu_present_map
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
id|__cpu_number_map
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|__cpu_logical_map
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|__cpu_number_map
(braket
id|boot_cpu_id
)braket
op_assign
l_int|0
suffix:semicolon
id|__cpu_logical_map
(braket
l_int|0
)braket
op_assign
id|boot_cpu_id
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|cpu
op_assign
id|boot_cpu_id
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
id|boot_cpu_id
)paren
suffix:semicolon
id|set_irq_udt
c_func
(paren
id|boot_cpu_id
)paren
suffix:semicolon
id|smp_setup_percpu_timer
c_func
(paren
)paren
suffix:semicolon
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_find_by_instance
c_func
(paren
l_int|1
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Not an MP box. */
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
id|i
op_eq
id|boot_cpu_id
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|i
comma
id|cpu_present_map
)paren
)paren
(brace
r_extern
r_int
r_int
id|sun4m_cpu_startup
suffix:semicolon
r_int
r_int
op_star
id|entry
op_assign
op_amp
id|sun4m_cpu_startup
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|timeout
suffix:semicolon
multiline_comment|/* Cook up an idler for this guy. */
id|p
op_assign
id|fork_idle
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpucount
op_increment
suffix:semicolon
id|current_set
(braket
id|i
)braket
op_assign
id|p-&gt;thread_info
suffix:semicolon
multiline_comment|/* See trampoline.S for details... */
id|entry
op_add_assign
(paren
(paren
id|i
op_minus
l_int|1
)paren
op_star
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Initialize the contexts table&n;&t;&t;&t; * Since the call to prom_startcpu() trashes the structure,&n;&t;&t;&t; * we need to re-initialize it for each cpu&n;&t;&t;&t; */
id|smp_penguin_ctable.which_io
op_assign
l_int|0
suffix:semicolon
id|smp_penguin_ctable.phys_addr
op_assign
(paren
r_int
r_int
)paren
id|srmmu_ctx_table_phys
suffix:semicolon
id|smp_penguin_ctable.reg_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* whirrr, whirrr, whirrrrrrrrr... */
id|printk
c_func
(paren
l_string|&quot;Starting CPU %d at %p&bslash;n&quot;
comma
id|i
comma
id|entry
)paren
suffix:semicolon
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|prom_startcpu
c_func
(paren
id|cpu_data
c_func
(paren
id|i
)paren
dot
id|prom_node
comma
op_amp
id|smp_penguin_ctable
comma
l_int|0
comma
(paren
r_char
op_star
)paren
id|entry
)paren
suffix:semicolon
multiline_comment|/* wheee... it&squot;s going... */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|10000
suffix:semicolon
id|timeout
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_callin_map
(braket
id|i
)braket
)paren
(brace
r_break
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_callin_map
(braket
id|i
)braket
)paren
(brace
multiline_comment|/* Another &quot;Red Snapper&quot;. */
id|__cpu_number_map
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
id|__cpu_logical_map
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
r_else
(brace
id|cpucount
op_decrement
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processor %d is stuck.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_callin_map
(braket
id|i
)braket
)paren
)paren
(brace
id|cpu_clear
c_func
(paren
id|i
comma
id|cpu_present_map
)paren
suffix:semicolon
id|__cpu_number_map
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpucount
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error: only one Processor found.&bslash;n&quot;
)paren
suffix:semicolon
id|cpu_present_map
op_assign
id|cpumask_of_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|bogosum
op_assign
l_int|0
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
id|cpu_isset
c_func
(paren
id|i
comma
id|cpu_present_map
)paren
)paren
id|bogosum
op_add_assign
id|cpu_data
c_func
(paren
id|i
)paren
dot
id|udelay_val
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Total of %d Processors activated (%lu.%02lu BogoMIPS).&bslash;n&quot;
comma
id|cpucount
op_plus
l_int|1
comma
id|bogosum
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|bogosum
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
id|smp_activated
op_assign
l_int|1
suffix:semicolon
id|smp_num_cpus
op_assign
id|cpucount
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Free unneeded trap tables */
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|i
comma
id|cpu_present_map
)paren
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu1
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu1
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|trapbase_cpu1
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|num_physpages
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|2
comma
id|cpu_present_map
)paren
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu2
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu2
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|trapbase_cpu2
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|num_physpages
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|3
comma
id|cpu_present_map
)paren
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu3
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|trapbase_cpu3
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|trapbase_cpu3
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|num_physpages
op_increment
suffix:semicolon
)brace
multiline_comment|/* Ok, they are spinning and ready to go. */
id|smp_processors_ready
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* At each hardware IRQ, we get this called to forward IRQ reception&n; * to the next processor.  The caller must disable the IRQ level being&n; * serviced globally so that there are no double interrupts received.&n; *&n; * XXX See sparc64 irq.c.&n; */
DECL|function|smp4m_irq_rotate
r_void
id|smp4m_irq_rotate
c_func
(paren
r_int
id|cpu
)paren
(brace
)brace
multiline_comment|/* Cross calls, in order to work efficiently and atomically do all&n; * the message passing work themselves, only stopcpu and reschedule&n; * messages come through here.&n; */
DECL|function|smp4m_message_pass
r_void
id|smp4m_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
(brace
r_static
r_int
r_int
id|smp_cpu_in_msg
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|cpumask_t
id|mask
suffix:semicolon
r_int
id|me
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|irq
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_eq
id|MSG_RESCHEDULE
)paren
(brace
id|irq
op_assign
id|IRQ_RESCHEDULE
suffix:semicolon
r_if
c_cond
(paren
id|smp_cpu_in_msg
(braket
id|me
)braket
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|msg
op_eq
id|MSG_STOP_CPU
)paren
(brace
id|irq
op_assign
id|IRQ_STOP_CPU
suffix:semicolon
)brace
r_else
(brace
r_goto
id|barf
suffix:semicolon
)brace
id|smp_cpu_in_msg
(braket
id|me
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
op_logical_or
id|target
op_eq
id|MSG_ALL
)paren
(brace
id|mask
op_assign
id|cpu_present_map
suffix:semicolon
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
)paren
(brace
id|cpu_clear
c_func
(paren
id|me
comma
id|mask
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|i
comma
id|mask
)paren
)paren
id|set_cpu_int
c_func
(paren
id|i
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|set_cpu_int
c_func
(paren
id|target
comma
id|irq
)paren
suffix:semicolon
)brace
id|smp_cpu_in_msg
(braket
id|me
)braket
op_decrement
suffix:semicolon
r_return
suffix:semicolon
id|barf
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Yeeee, trying to send SMP msg(%d) on cpu %d&bslash;n&quot;
comma
id|msg
comma
id|me
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Bogon SMP message pass.&quot;
)paren
suffix:semicolon
)brace
DECL|struct|smp_funcall
r_static
r_struct
id|smp_funcall
(brace
DECL|member|func
id|smpfunc_t
id|func
suffix:semicolon
DECL|member|arg1
r_int
r_int
id|arg1
suffix:semicolon
DECL|member|arg2
r_int
r_int
id|arg2
suffix:semicolon
DECL|member|arg3
r_int
r_int
id|arg3
suffix:semicolon
DECL|member|arg4
r_int
r_int
id|arg4
suffix:semicolon
DECL|member|arg5
r_int
r_int
id|arg5
suffix:semicolon
DECL|member|processors_in
r_int
r_int
id|processors_in
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Set when ipi entered. */
DECL|member|processors_out
r_int
r_int
id|processors_out
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Set when ipi exited. */
DECL|variable|ccall_info
)brace
id|ccall_info
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|cross_call_lock
)paren
suffix:semicolon
multiline_comment|/* Cross calls must be serialized, at least currently. */
DECL|function|smp4m_cross_call
r_void
id|smp4m_cross_call
c_func
(paren
id|smpfunc_t
id|func
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
id|arg5
)paren
(brace
r_if
c_cond
(paren
id|smp_processors_ready
)paren
(brace
r_register
r_int
id|ncpus
op_assign
id|smp_num_cpus
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cross_call_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Init function glue. */
id|ccall_info.func
op_assign
id|func
suffix:semicolon
id|ccall_info.arg1
op_assign
id|arg1
suffix:semicolon
id|ccall_info.arg2
op_assign
id|arg2
suffix:semicolon
id|ccall_info.arg3
op_assign
id|arg3
suffix:semicolon
id|ccall_info.arg4
op_assign
id|arg4
suffix:semicolon
id|ccall_info.arg5
op_assign
id|arg5
suffix:semicolon
multiline_comment|/* Init receive/complete mapping, plus fire the IPI&squot;s off. */
(brace
id|cpumask_t
id|mask
op_assign
id|cpu_present_map
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mask
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
id|ncpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|i
comma
id|mask
)paren
)paren
(brace
id|ccall_info.processors_in
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|ccall_info.processors_out
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|set_cpu_int
c_func
(paren
id|i
comma
id|IRQ_CROSS_CALL
)paren
suffix:semicolon
)brace
r_else
(brace
id|ccall_info.processors_in
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|ccall_info.processors_out
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
(brace
r_register
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_while
c_loop
(paren
op_logical_neg
id|ccall_info.processors_in
(braket
id|i
)braket
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_increment
id|i
OL
id|ncpus
)paren
(brace
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_while
c_loop
(paren
op_logical_neg
id|ccall_info.processors_out
(braket
id|i
)braket
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_increment
id|i
OL
id|ncpus
)paren
(brace
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cross_call_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Running cross calls. */
DECL|function|smp4m_cross_call_irq
r_void
id|smp4m_cross_call_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|ccall_info.processors_in
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|ccall_info
dot
id|func
c_func
(paren
id|ccall_info.arg1
comma
id|ccall_info.arg2
comma
id|ccall_info.arg3
comma
id|ccall_info.arg4
comma
id|ccall_info.arg5
)paren
suffix:semicolon
id|ccall_info.processors_out
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|smp4m_percpu_timer_interrupt
r_void
id|smp4m_percpu_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|clear_profile_irq
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|profile_tick
c_func
(paren
id|CPU_PROFILING
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|prof_counter
c_func
(paren
id|cpu
)paren
)paren
(brace
r_int
id|user
op_assign
id|user_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|update_process_times
c_func
(paren
id|user
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
id|prof_counter
c_func
(paren
id|cpu
)paren
op_assign
id|prof_multiplier
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
)brace
r_extern
r_int
r_int
id|lvl14_resolution
suffix:semicolon
DECL|function|smp_setup_percpu_timer
r_static
r_void
id|__init
id|smp_setup_percpu_timer
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|prof_counter
c_func
(paren
id|cpu
)paren
op_assign
id|prof_multiplier
c_func
(paren
id|cpu
)paren
op_assign
l_int|1
suffix:semicolon
id|load_profile_irq
c_func
(paren
id|cpu
comma
id|lvl14_resolution
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|boot_cpu_id
)paren
(brace
id|enable_pil_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp4m_blackbox_id
r_void
id|__init
id|smp4m_blackbox_id
c_func
(paren
r_int
op_star
id|addr
)paren
(brace
r_int
id|rd
op_assign
op_star
id|addr
op_amp
l_int|0x3e000000
suffix:semicolon
r_int
id|rs1
op_assign
id|rd
op_rshift
l_int|11
suffix:semicolon
id|addr
(braket
l_int|0
)braket
op_assign
l_int|0x81580000
op_or
id|rd
suffix:semicolon
multiline_comment|/* rd %tbr, reg */
id|addr
(braket
l_int|1
)braket
op_assign
l_int|0x8130200c
op_or
id|rd
op_or
id|rs1
suffix:semicolon
multiline_comment|/* srl reg, 0xc, reg */
id|addr
(braket
l_int|2
)braket
op_assign
l_int|0x80082003
op_or
id|rd
op_or
id|rs1
suffix:semicolon
multiline_comment|/* and reg, 3, reg */
)brace
DECL|function|smp4m_blackbox_current
r_void
id|__init
id|smp4m_blackbox_current
c_func
(paren
r_int
op_star
id|addr
)paren
(brace
r_int
id|rd
op_assign
op_star
id|addr
op_amp
l_int|0x3e000000
suffix:semicolon
r_int
id|rs1
op_assign
id|rd
op_rshift
l_int|11
suffix:semicolon
id|addr
(braket
l_int|0
)braket
op_assign
l_int|0x81580000
op_or
id|rd
suffix:semicolon
multiline_comment|/* rd %tbr, reg */
id|addr
(braket
l_int|2
)braket
op_assign
l_int|0x8130200a
op_or
id|rd
op_or
id|rs1
suffix:semicolon
multiline_comment|/* srl reg, 0xa, reg */
id|addr
(braket
l_int|4
)braket
op_assign
l_int|0x8008200c
op_or
id|rd
op_or
id|rs1
suffix:semicolon
multiline_comment|/* and reg, 3, reg */
)brace
DECL|function|sun4m_init_smp
r_void
id|__init
id|sun4m_init_smp
c_func
(paren
r_void
)paren
(brace
id|BTFIXUPSET_BLACKBOX
c_func
(paren
id|hard_smp_processor_id
comma
id|smp4m_blackbox_id
)paren
suffix:semicolon
id|BTFIXUPSET_BLACKBOX
c_func
(paren
id|load_current
comma
id|smp4m_blackbox_current
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|smp_cross_call
comma
id|smp4m_cross_call
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|smp_message_pass
comma
id|smp4m_message_pass
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|__hard_smp_processor_id
comma
id|__smp4m_processor_id
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
)brace
eof
