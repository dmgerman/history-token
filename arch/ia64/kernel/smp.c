multiline_comment|/*&n; * SMP Support&n; *&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 1999, 2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Lots of stuff stolen from arch/alpha/kernel/smp.c&n; *&n; * 01/05/16 Rohit Seth &lt;rohit.seth@intel.com&gt;  IA64-SMP functions. Reorganized&n; * the existing code (on the lines of x86 port).&n; * 00/09/11 David Mosberger &lt;davidm@hpl.hp.com&gt; Do loops_per_jiffy&n; * calibration on each CPU.&n; * 00/08/23 Asit Mallick &lt;asit.k.mallick@intel.com&gt; fixed logical processor id&n; * 00/03/31 Rohit Seth &lt;rohit.seth@intel.com&gt;&t;Fixes for Bootstrap Processor&n; * &amp; cpu_online_map now gets done here (instead of setup.c)&n; * 99/10/05 davidm&t;Update to bring it in sync with new command-line processing&n; *  scheme.&n; * 10/13/00 Goutham Rao &lt;goutham.rao@intel.com&gt; Updated smp_call_function and&n; *&t;&t;smp_call_function_single to resend IPI on timeouts&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
multiline_comment|/*&n; * The Big Kernel Lock.  It&squot;s not supposed to be used for performance critical stuff&n; * anymore.  But we still need to align it because certain workloads are still affected by&n; * it.  For example, llseek() and various other filesystem related routines still use the&n; * BKL.&n; */
DECL|variable|__cacheline_aligned
id|spinlock_t
id|kernel_flag
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Structure and data for smp_call_function(). This is designed to minimise static memory&n; * requirements. It also looks cleaner.&n; */
DECL|variable|__cacheline_aligned
r_static
id|spinlock_t
id|call_lock
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|call_data_struct
r_struct
id|call_data_struct
(brace
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|member|started
id|atomic_t
id|started
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|call_data
r_static
r_volatile
r_struct
id|call_data_struct
op_star
id|call_data
suffix:semicolon
DECL|macro|IPI_CALL_FUNC
mdefine_line|#define IPI_CALL_FUNC&t;&t;0
DECL|macro|IPI_CPU_STOP
mdefine_line|#define IPI_CPU_STOP&t;&t;1
multiline_comment|/* This needs to be cacheline aligned because it is written to by *other* CPUs.  */
DECL|variable|____cacheline_aligned
r_static
id|__u64
id|ipi_operation
id|__per_cpu_data
id|____cacheline_aligned
suffix:semicolon
r_static
r_void
DECL|function|stop_this_cpu
id|stop_this_cpu
(paren
r_void
)paren
(brace
r_extern
r_void
id|cpu_halt
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Remove this CPU:&n;&t; */
id|clear_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
id|max_xtp
c_func
(paren
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|cpu_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|handle_IPI
id|handle_IPI
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|this_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
op_star
id|pending_ipis
op_assign
op_amp
id|this_cpu
c_func
(paren
id|ipi_operation
)paren
suffix:semicolon
r_int
r_int
id|ops
suffix:semicolon
multiline_comment|/* Count this now; we may make a call that never returns. */
id|local_cpu_data-&gt;ipi_count
op_increment
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Order interrupt and bit testing. */
r_while
c_loop
(paren
(paren
id|ops
op_assign
id|xchg
c_func
(paren
id|pending_ipis
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Order bit clearing and data access. */
r_do
(brace
r_int
r_int
id|which
suffix:semicolon
id|which
op_assign
id|ffz
c_func
(paren
op_complement
id|ops
)paren
suffix:semicolon
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|which
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|IPI_CALL_FUNC
suffix:colon
(brace
r_struct
id|call_data_struct
op_star
id|data
suffix:semicolon
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
r_void
op_star
id|info
suffix:semicolon
r_int
id|wait
suffix:semicolon
multiline_comment|/* release the &squot;pointer lock&squot; */
id|data
op_assign
(paren
r_struct
id|call_data_struct
op_star
)paren
id|call_data
suffix:semicolon
id|func
op_assign
id|data-&gt;func
suffix:semicolon
id|info
op_assign
id|data-&gt;info
suffix:semicolon
id|wait
op_assign
id|data-&gt;wait
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|data-&gt;started
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;       * At this point the structure may be gone unless&n;&t;&t;&t;&t;       * wait is true.&n;&t;&t;&t;&t;       */
(paren
op_star
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* Notify the sending CPU that the task is done.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_inc
c_func
(paren
op_amp
id|data-&gt;finished
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPI_CPU_STOP
suffix:colon
id|stop_this_cpu
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unknown IPI on CPU %d: %lu&bslash;n&quot;
comma
id|this_cpu
comma
id|which
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|ops
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Order data access and bit testing. */
)brace
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_single
id|send_IPI_single
(paren
r_int
id|dest_cpu
comma
r_int
id|op
)paren
(brace
id|set_bit
c_func
(paren
id|op
comma
op_amp
id|per_cpu
c_func
(paren
id|ipi_operation
comma
id|dest_cpu
)paren
)paren
suffix:semicolon
id|platform_send_ipi
c_func
(paren
id|dest_cpu
comma
id|IA64_IPI_VECTOR
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_allbutself
id|send_IPI_allbutself
(paren
r_int
id|op
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
id|send_IPI_single
c_func
(paren
id|i
comma
id|op
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_all
id|send_IPI_all
(paren
r_int
id|op
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|send_IPI_single
c_func
(paren
id|i
comma
id|op
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_self
id|send_IPI_self
(paren
r_int
id|op
)paren
(brace
id|send_IPI_single
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|op
)paren
suffix:semicolon
)brace
r_void
DECL|function|smp_send_reschedule
id|smp_send_reschedule
(paren
r_int
id|cpu
)paren
(brace
id|platform_send_ipi
c_func
(paren
id|cpu
comma
id|IA64_IPI_RESCHEDULE
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function sends a reschedule IPI to all (other) CPUs.  This should only be used if&n; * some &squot;global&squot; task became runnable, such as a RT task, that must be handled now. The&n; * first CPU that manages to grab the task will run it.&n; */
r_void
DECL|function|smp_send_reschedule_all
id|smp_send_reschedule_all
(paren
r_void
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
id|smp_send_reschedule
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_void
DECL|function|smp_flush_tlb_all
id|smp_flush_tlb_all
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|__flush_tlb_all
comma
l_int|0
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Run a function on another CPU&n; *  &lt;func&gt;&t;The function to run. This must be fast and non-blocking.&n; *  &lt;info&gt;&t;An arbitrary pointer to pass to the function.&n; *  &lt;nonatomic&gt;&t;Currently unused.&n; *  &lt;wait&gt;&t;If true, wait until function has completed on other CPUs.&n; *  [RETURNS]   0 on success, else a negative status code.&n; *&n; * Does not return until the remote CPU is nearly ready to execute &lt;func&gt;&n; * or is or has executed.&n; */
r_int
DECL|function|smp_call_function_single
id|smp_call_function_single
(paren
r_int
id|cpuid
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|nonatomic
comma
r_int
id|wait
)paren
(brace
r_struct
id|call_data_struct
id|data
suffix:semicolon
r_int
id|cpus
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cpuid
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot; trying to call self&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.started
comma
l_int|0
)paren
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_set
c_func
(paren
op_amp
id|data.finished
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
id|call_data
op_assign
op_amp
id|data
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ensure store to call_data precedes setting of IPI_CALL_FUNC */
id|send_IPI_single
c_func
(paren
id|cpuid
comma
id|IPI_CALL_FUNC
)paren
suffix:semicolon
multiline_comment|/* Wait for response */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.finished
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|call_data
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * this function sends a &squot;generic call function&squot; IPI to all other CPUs&n; * in the system.&n; */
multiline_comment|/*&n; *  [SUMMARY]&t;Run a function on all other CPUs.&n; *  &lt;func&gt;&t;The function to run. This must be fast and non-blocking.&n; *  &lt;info&gt;&t;An arbitrary pointer to pass to the function.&n; *  &lt;nonatomic&gt;&t;currently unused.&n; *  &lt;wait&gt;&t;If true, wait (atomically) until function has completed on other CPUs.&n; *  [RETURNS]   0 on success, else a negative status code.&n; *&n; * Does not return until remote CPUs are nearly ready to execute &lt;func&gt; or are or have&n; * executed.&n; *&n; * You must not call this function with disabled interrupts or from a hardware interrupt&n; * handler, you may call it from a bottom half handler.&n; */
r_int
DECL|function|smp_call_function
id|smp_call_function
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|nonatomic
comma
r_int
id|wait
)paren
(brace
r_struct
id|call_data_struct
id|data
suffix:semicolon
r_int
id|cpus
op_assign
id|smp_num_cpus
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus
)paren
r_return
l_int|0
suffix:semicolon
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.started
comma
l_int|0
)paren
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_set
c_func
(paren
op_amp
id|data.finished
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
id|call_data
op_assign
op_amp
id|data
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ensure store to call_data precedes setting of IPI_CALL_FUNC */
id|send_IPI_allbutself
c_func
(paren
id|IPI_CALL_FUNC
)paren
suffix:semicolon
multiline_comment|/* Wait for response */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.finished
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|call_data
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|smp_do_timer
id|smp_do_timer
(paren
r_struct
id|pt_regs
op_star
id|regs
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
r_if
c_cond
(paren
op_decrement
id|local_cpu_data-&gt;prof_counter
op_le
l_int|0
)paren
(brace
id|local_cpu_data-&gt;prof_counter
op_assign
id|local_cpu_data-&gt;prof_multiplier
suffix:semicolon
id|update_process_times
c_func
(paren
id|user
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * this function calls the &squot;stop&squot; function on all other CPUs in the system.&n; */
r_void
DECL|function|smp_send_stop
id|smp_send_stop
(paren
r_void
)paren
(brace
id|send_IPI_allbutself
c_func
(paren
id|IPI_CPU_STOP
)paren
suffix:semicolon
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
)brace
r_int
id|__init
DECL|function|setup_profiling_timer
id|setup_profiling_timer
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
