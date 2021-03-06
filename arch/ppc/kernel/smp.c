multiline_comment|/*&n; * Smp support for ppc.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great&n; * deal of code from the sparc and intel versions.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
DECL|variable|smp_commenced
r_volatile
r_int
id|smp_commenced
suffix:semicolon
DECL|variable|smp_tb_synchronized
r_int
id|smp_tb_synchronized
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_PPC
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|klock_info
r_struct
id|klock_info_struct
id|klock_info
op_assign
(brace
id|KLOCK_CLEAR
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|ipi_recv
id|atomic_t
id|ipi_recv
suffix:semicolon
DECL|variable|ipi_sent
id|atomic_t
id|ipi_sent
suffix:semicolon
DECL|variable|cpu_online_map
id|cpumask_t
id|cpu_online_map
suffix:semicolon
DECL|variable|cpu_possible_map
id|cpumask_t
id|cpu_possible_map
suffix:semicolon
DECL|variable|smp_hw_index
r_int
id|smp_hw_index
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|secondary_ti
r_struct
id|thread_info
op_star
id|secondary_ti
suffix:semicolon
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|cpu_possible_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_possible_map
)paren
suffix:semicolon
multiline_comment|/* SMP operations for this machine */
DECL|variable|smp_ops
r_static
r_struct
id|smp_ops_t
op_star
id|smp_ops
suffix:semicolon
multiline_comment|/* all cpu mappings are 1-1 -- Cort */
DECL|variable|cpu_callin_map
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|start_secondary
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|smp_call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|__smp_call_function
c_func
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
id|wait
comma
r_int
id|target
)paren
suffix:semicolon
multiline_comment|/* Low level assembly function used to backup CPU 0 state */
r_extern
r_void
id|__save_cpu_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Since OpenPIC has only 4 IPIs, we use slightly different message numbers.&n; *&n; * Make sure this matches openpic_request_IPIs in open_pic.c, or what shows up&n; * in /proc/interrupts will be wrong!!! --Troy */
DECL|macro|PPC_MSG_CALL_FUNCTION
mdefine_line|#define PPC_MSG_CALL_FUNCTION&t;0
DECL|macro|PPC_MSG_RESCHEDULE
mdefine_line|#define PPC_MSG_RESCHEDULE&t;1
DECL|macro|PPC_MSG_INVALIDATE_TLB
mdefine_line|#define PPC_MSG_INVALIDATE_TLB&t;2
DECL|macro|PPC_MSG_XMON_BREAK
mdefine_line|#define PPC_MSG_XMON_BREAK&t;3
r_static
r_inline
r_void
DECL|function|smp_message_pass
id|smp_message_pass
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
r_if
c_cond
(paren
id|smp_ops
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ipi_sent
)paren
suffix:semicolon
id|smp_ops
op_member_access_from_pointer
id|message_pass
c_func
(paren
id|target
comma
id|msg
comma
id|data
comma
id|wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Common functions&n; */
DECL|function|smp_message_recv
r_void
id|smp_message_recv
c_func
(paren
r_int
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ipi_recv
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|msg
)paren
(brace
r_case
id|PPC_MSG_CALL_FUNCTION
suffix:colon
id|smp_call_function_interrupt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PPC_MSG_RESCHEDULE
suffix:colon
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PPC_MSG_INVALIDATE_TLB
suffix:colon
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
r_case
id|PPC_MSG_XMON_BREAK
suffix:colon
id|xmon
c_func
(paren
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_XMON */
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SMP %d: smp_message_recv(): unknown msg %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * 750&squot;s don&squot;t broadcast tlb invalidates so&n; * we have to emulate that behavior.&n; *   -- Cort&n; */
DECL|function|smp_send_tlb_invalidate
r_void
id|smp_send_tlb_invalidate
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|PVR_VER
c_func
(paren
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
)paren
op_eq
l_int|8
)paren
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
comma
id|PPC_MSG_INVALIDATE_TLB
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/*&n;&t; * This is only used if `cpu&squot; is running an idle task,&n;&t; * so it will reschedule itself anyway...&n;&t; *&n;&t; * This isn&squot;t the case anymore since the other CPU could be&n;&t; * sleeping and won&squot;t reschedule until the next interrupt (such&n;&t; * as the timer).&n;&t; *  -- Cort&n;&t; */
multiline_comment|/* This is only used if `cpu&squot; is running an idle task,&n;&t;   so it will reschedule itself anyway... */
id|smp_message_pass
c_func
(paren
id|cpu
comma
id|PPC_MSG_RESCHEDULE
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_XMON
DECL|function|smp_send_xmon_break
r_void
id|smp_send_xmon_break
c_func
(paren
r_int
id|cpu
)paren
(brace
id|smp_message_pass
c_func
(paren
id|cpu
comma
id|PPC_MSG_XMON_BREAK
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_XMON */
DECL|function|stop_this_cpu
r_static
r_void
id|stop_this_cpu
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|stop_this_cpu
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Structure and data for smp_call_function(). This is designed to minimise&n; * static memory requirements. It also looks cleaner.&n; * Stolen from the i386 version.&n; */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|call_lock
)paren
suffix:semicolon
DECL|struct|call_data_struct
r_static
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
DECL|member|started
id|atomic_t
id|started
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|variable|call_data
)brace
op_star
id|call_data
suffix:semicolon
multiline_comment|/*&n; * this function sends a &squot;generic call function&squot; IPI to all other CPUs&n; * in the system.&n; */
DECL|function|smp_call_function
r_int
id|smp_call_function
c_func
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
multiline_comment|/*&n; * [SUMMARY] Run a function on all other CPUs.&n; * &lt;func&gt; The function to run. This must be fast and non-blocking.&n; * &lt;info&gt; An arbitrary pointer to pass to the function.&n; * &lt;nonatomic&gt; currently unused.&n; * &lt;wait&gt; If true, wait (atomically) until function has completed on other CPUs.&n; * [RETURNS] 0 on success, else a negative status code. Does not return until&n; * remote CPUs are nearly ready to execute &lt;&lt;func&gt;&gt; or are or have executed.&n; *&n; * You must not call this function with disabled interrupts or from a&n; * hardware interrupt handler or from a bottom half handler.&n; */
(brace
multiline_comment|/* FIXME: get cpu lock with hotplug cpus, or change this to&n;           bitmask. --RR */
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
op_le
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Can deadlock when called with interrupts disabled */
id|WARN_ON
c_func
(paren
id|irqs_disabled
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|__smp_call_function
c_func
(paren
id|func
comma
id|info
comma
id|wait
comma
id|MSG_ALL_BUT_SELF
)paren
suffix:semicolon
)brace
DECL|function|__smp_call_function
r_static
r_int
id|__smp_call_function
c_func
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
id|wait
comma
r_int
id|target
)paren
(brace
r_struct
id|call_data_struct
id|data
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|timeout
suffix:semicolon
r_int
id|ncpus
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
)paren
id|ncpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
op_minus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL
)paren
id|ncpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
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
id|spin_lock
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
multiline_comment|/* Send a message to all other CPUs and wait for them to respond */
id|smp_message_pass
c_func
(paren
id|target
comma
id|PPC_MSG_CALL_FUNCTION
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Wait for response */
id|timeout
op_assign
l_int|1000000
suffix:semicolon
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
id|ncpus
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|timeout
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;smp_call_function on cpu %d: other cpus not responding (%d)&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
)paren
(brace
id|timeout
op_assign
l_int|1000000
suffix:semicolon
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
id|ncpus
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|timeout
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;smp_call_function on cpu %d: other cpus not finishing (%d/%d)&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|data.finished
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|smp_call_function_interrupt
r_void
id|smp_call_function_interrupt
c_func
(paren
r_void
)paren
(brace
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
op_assign
id|call_data-&gt;func
suffix:semicolon
r_void
op_star
id|info
op_assign
id|call_data-&gt;info
suffix:semicolon
r_int
id|wait
op_assign
id|call_data-&gt;wait
suffix:semicolon
multiline_comment|/*&n;&t; * Notify initiating CPU that I&squot;ve grabbed the data and am&n;&t; * about to execute the function&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;started
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At this point the info structure may be out of scope unless wait==1&n;&t; */
(paren
op_star
id|func
)paren
(paren
id|info
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
id|call_data-&gt;finished
)paren
suffix:semicolon
)brace
DECL|function|smp_store_cpu_info
r_static
r_void
id|__devinit
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
(brace
r_struct
id|cpuinfo_PPC
op_star
id|c
op_assign
op_amp
id|cpu_data
(braket
id|id
)braket
suffix:semicolon
multiline_comment|/* assume bogomips are same for everything */
id|c-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
id|c-&gt;pvr
op_assign
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
suffix:semicolon
)brace
DECL|function|smp_prepare_cpus
r_void
id|__init
id|smp_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|num_cpus
comma
id|i
suffix:semicolon
multiline_comment|/* Fixup boot cpu */
id|smp_store_cpu_info
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|cpu_callin_map
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
l_int|1
suffix:semicolon
id|smp_ops
op_assign
id|ppc_md.smp_ops
suffix:semicolon
r_if
c_cond
(paren
id|smp_ops
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SMP not supported on this machine.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Probe platform for CPUs: always linear. */
id|num_cpus
op_assign
id|smp_ops
op_member_access_from_pointer
id|probe
c_func
(paren
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
id|num_cpus
suffix:semicolon
op_increment
id|i
)paren
id|cpu_set
c_func
(paren
id|i
comma
id|cpu_possible_map
)paren
suffix:semicolon
multiline_comment|/* Backup CPU 0 state */
id|__save_cpu_setup
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_ops-&gt;space_timers
)paren
id|smp_ops
op_member_access_from_pointer
id|space_timers
c_func
(paren
id|num_cpus
)paren
suffix:semicolon
)brace
DECL|function|smp_prepare_boot_cpu
r_void
id|__devinit
id|smp_prepare_boot_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_online_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_possible_map
)paren
suffix:semicolon
)brace
DECL|function|setup_profiling_timer
r_int
id|__init
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Processor coming up starts here */
DECL|function|start_secondary
r_int
id|__devinit
id|start_secondary
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|cpu
suffix:semicolon
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
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|set_dec
c_func
(paren
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
id|cpu_callin_map
(braket
id|cpu
)braket
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %i done callin...&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|smp_ops
op_member_access_from_pointer
id|setup_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %i done setup...&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|smp_ops
op_member_access_from_pointer
id|take_timebase
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %i done timebase take...&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__cpu_up
r_int
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|c
suffix:semicolon
multiline_comment|/* create a process for the processor */
multiline_comment|/* only regs.msr is actually used, and 0 is OK for it */
id|p
op_assign
id|fork_idle
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;failed fork for CPU %u: %li&quot;
comma
id|cpu
comma
id|PTR_ERR
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|secondary_ti
op_assign
id|p-&gt;thread_info
suffix:semicolon
id|p-&gt;thread_info-&gt;cpu
op_assign
id|cpu
suffix:semicolon
multiline_comment|/*&n;&t; * There was a cache flush loop here to flush the cache&n;&t; * to memory for the first 8MB of RAM.  The cache flush&n;&t; * has been pushed into the kick_cpu function for those&n;&t; * platforms that need it.&n;&t; */
multiline_comment|/* wake up cpu */
id|smp_ops
op_member_access_from_pointer
id|kick_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * wait to see if the cpu made a callin (is actually up).&n;&t; * use this value that I found through experimentation.&n;&t; * -- Cort&n;&t; */
r_for
c_loop
(paren
id|c
op_assign
l_int|1000
suffix:semicolon
id|c
op_logical_and
op_logical_neg
id|cpu_callin_map
(braket
id|cpu
)braket
suffix:semicolon
id|c
op_decrement
)paren
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_callin_map
(braket
id|cpu
)braket
)paren
(brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;didn&squot;t find cpu %u&quot;
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
id|buf
comma
l_int|0x360
op_plus
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processor %u is stuck.&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;found cpu %u&quot;
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
id|buf
comma
l_int|0x350
op_plus
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processor %d found.&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|smp_ops
op_member_access_from_pointer
id|give_timebase
c_func
(paren
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|cpu
comma
id|cpu_online_map
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_cpus_done
r_void
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
id|smp_ops
op_member_access_from_pointer
id|setup_cpu
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
