multiline_comment|/*&n; * SMP support for pSeries machines.&n; *&n; * Dave Engebretsen, Peter Bergner, and&n; * Mike Corrigan {engebret|bergner|mikec}@us.ibm.com&n; *&n; * Plus various changes from other IBM teams...&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/plpar_wrappers.h&gt;
macro_line|#include &quot;mpic.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) udbg_printf(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
r_extern
r_void
id|pSeries_secondary_smp_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Get state of physical CPU.&n; * Return codes:&n; *&t;0&t;- The processor is in the RTAS stopped state&n; *&t;1&t;- stop-self is in progress&n; *&t;2&t;- The processor is not in the RTAS stopped state&n; *&t;-1&t;- Hardware Error&n; *&t;-2&t;- Hardware Busy, Try again later.&n; */
DECL|function|query_cpu_stopped
r_static
r_int
id|query_cpu_stopped
c_func
(paren
r_int
r_int
id|pcpu
)paren
(brace
r_int
id|cpu_status
suffix:semicolon
r_int
id|status
comma
id|qcss_tok
suffix:semicolon
id|qcss_tok
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;query-cpu-stopped-state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcss_tok
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|qcss_tok
comma
l_int|1
comma
l_int|2
comma
op_amp
id|cpu_status
comma
id|pcpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RTAS query-cpu-stopped-state failed: %i&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_return
id|cpu_status
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
DECL|function|pSeries_cpu_disable
r_int
id|pSeries_cpu_disable
c_func
(paren
r_void
)paren
(brace
id|systemcfg-&gt;processorCount
op_decrement
suffix:semicolon
multiline_comment|/*fix boot_cpuid here*/
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|boot_cpuid
)paren
id|boot_cpuid
op_assign
id|any_online_cpu
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
multiline_comment|/* FIXME: abstract this to not be platform specific later on */
id|xics_migrate_irqs_away
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pSeries_cpu_die
r_void
id|pSeries_cpu_die
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_int
id|tries
suffix:semicolon
r_int
id|cpu_status
suffix:semicolon
r_int
r_int
id|pcpu
op_assign
id|get_hard_smp_processor_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tries
op_assign
l_int|0
suffix:semicolon
id|tries
OL
l_int|25
suffix:semicolon
id|tries
op_increment
)paren
(brace
id|cpu_status
op_assign
id|query_cpu_stopped
c_func
(paren
id|pcpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_status
op_eq
l_int|0
op_logical_or
id|cpu_status
op_eq
op_minus
l_int|1
)paren
r_break
suffix:semicolon
id|msleep
c_func
(paren
l_int|200
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Querying DEAD? cpu %i (%i) shows %i&bslash;n&quot;
comma
id|cpu
comma
id|pcpu
comma
id|cpu_status
)paren
suffix:semicolon
)brace
multiline_comment|/* Isolation and deallocation are definatly done by&n;&t; * drslot_chrp_cpu.  If they were not they would be&n;&t; * done here.  Change isolate state to Isolate and&n;&t; * change allocation-state to Unusable.&n;&t; */
id|paca
(braket
id|cpu
)braket
dot
id|cpu_start
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Search all cpu device nodes for an offline logical cpu.  If a&n; * device node has a &quot;ibm,my-drc-index&quot; property (meaning this is an&n; * LPAR), paranoid-check whether we own the cpu.  For each &quot;thread&quot;&n; * of a cpu, if it is offline and has the same hw index as before,&n; * grab that in preference.&n; */
DECL|function|find_physical_cpu_to_start
r_static
r_int
r_int
id|find_physical_cpu_to_start
c_func
(paren
r_int
r_int
id|old_hwindex
)paren
(brace
r_struct
id|device_node
op_star
id|np
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|best
op_assign
op_minus
l_int|1U
suffix:semicolon
r_while
c_loop
(paren
(paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;cpu&quot;
)paren
)paren
)paren
(brace
r_int
id|nr_threads
comma
id|len
suffix:semicolon
id|u32
op_star
id|index
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ibm,my-drc-index&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|u32
op_star
id|tid
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ibm,ppc-interrupt-server#s&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tid
)paren
id|tid
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tid
)paren
r_continue
suffix:semicolon
multiline_comment|/* If there is a drc-index, make sure that we own&n;&t;&t; * the cpu.&n;&t;&t; */
r_if
c_cond
(paren
id|index
)paren
(brace
r_int
id|state
suffix:semicolon
r_int
id|rc
op_assign
id|rtas_get_sensor
c_func
(paren
l_int|9003
comma
op_star
id|index
comma
op_amp
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
op_logical_or
id|state
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
)brace
id|nr_threads
op_assign
id|len
op_div
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr_threads
op_decrement
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|query_cpu_stopped
c_func
(paren
id|tid
(braket
id|nr_threads
)braket
)paren
)paren
(brace
id|best
op_assign
id|tid
(braket
id|nr_threads
)braket
suffix:semicolon
r_if
c_cond
(paren
id|best
op_eq
id|old_hwindex
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
r_return
id|best
suffix:semicolon
)brace
multiline_comment|/**&n; * smp_startup_cpu() - start the given cpu&n; *&n; * At boot time, there is nothing to do.  At run-time, call RTAS with&n; * the appropriate start location, if the cpu is in the RTAS stopped&n; * state.&n; *&n; * Returns:&n; *&t;0&t;- failure&n; *&t;1&t;- success&n; */
DECL|function|smp_startup_cpu
r_static
r_inline
r_int
id|__devinit
id|smp_startup_cpu
c_func
(paren
r_int
r_int
id|lcpu
)paren
(brace
r_int
id|status
suffix:semicolon
r_int
r_int
id|start_here
op_assign
id|__pa
c_func
(paren
(paren
id|u32
)paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|pSeries_secondary_smp_init
)paren
)paren
suffix:semicolon
r_int
r_int
id|pcpu
suffix:semicolon
multiline_comment|/* At boot time the cpus are already spinning in hold&n;&t; * loops, so nothing to do. */
r_if
c_cond
(paren
id|system_state
OL
id|SYSTEM_RUNNING
)paren
r_return
l_int|1
suffix:semicolon
id|pcpu
op_assign
id|find_physical_cpu_to_start
c_func
(paren
id|get_hard_smp_processor_id
c_func
(paren
id|lcpu
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcpu
op_eq
op_minus
l_int|1U
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;No more cpus available, failing&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fixup atomic count: it exited inside IRQ handler. */
id|paca
(braket
id|lcpu
)braket
dot
id|__current-&gt;thread_info-&gt;preempt_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* At boot this is done in prom.c. */
id|paca
(braket
id|lcpu
)braket
dot
id|hw_cpu_id
op_assign
id|pcpu
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;start-cpu&quot;
)paren
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|pcpu
comma
id|start_here
comma
id|lcpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;start-cpu failed: %i&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else /* ... CONFIG_HOTPLUG_CPU */
DECL|function|smp_startup_cpu
r_static
r_inline
r_int
id|__devinit
id|smp_startup_cpu
c_func
(paren
r_int
r_int
id|lcpu
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
DECL|function|smp_xics_do_message
r_static
r_inline
r_void
id|smp_xics_do_message
c_func
(paren
r_int
id|cpu
comma
r_int
id|msg
)paren
(brace
id|set_bit
c_func
(paren
id|msg
comma
op_amp
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|xics_cause_IPI
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|smp_xics_message_pass
r_static
r_void
id|smp_xics_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|target
OL
id|NR_CPUS
)paren
(brace
id|smp_xics_do_message
c_func
(paren
id|target
comma
id|msg
)paren
suffix:semicolon
)brace
r_else
(brace
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
op_logical_and
id|i
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
id|smp_xics_do_message
c_func
(paren
id|i
comma
id|msg
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|smp_xics_probe
r_static
r_int
id|__init
id|smp_xics_probe
c_func
(paren
r_void
)paren
(brace
id|xics_request_IPIs
c_func
(paren
)paren
suffix:semicolon
r_return
id|cpus_weight
c_func
(paren
id|cpu_possible_map
)paren
suffix:semicolon
)brace
DECL|function|smp_xics_setup_cpu
r_static
r_void
id|__devinit
id|smp_xics_setup_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|cpu
op_ne
id|boot_cpuid
)paren
id|xics_setup_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
id|vpa_init
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Put the calling processor into the GIQ.  This is really only&n;&t; * necessary from a secondary thread as the OF start-cpu interface&n;&t; * performs this function for us on primary threads.&n;&t; */
id|rtas_set_indicator
c_func
(paren
id|GLOBAL_INTERRUPT_QUEUE
comma
(paren
l_int|1UL
op_lshift
id|interrupt_server_size
)paren
op_minus
l_int|1
op_minus
id|default_distrib_server
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|timebase_lock
)paren
suffix:semicolon
DECL|variable|timebase
r_static
r_int
r_int
id|timebase
op_assign
l_int|0
suffix:semicolon
DECL|function|pSeries_give_timebase
r_static
r_void
id|__devinit
id|pSeries_give_timebase
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|timebase_lock
)paren
suffix:semicolon
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;freeze-time-base&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|timebase
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|timebase_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timebase
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;thaw-time-base&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pSeries_take_timebase
r_static
r_void
id|__devinit
id|pSeries_take_timebase
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|timebase
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|timebase_lock
)paren
suffix:semicolon
id|set_tb
c_func
(paren
id|timebase
op_rshift
l_int|32
comma
id|timebase
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|timebase
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|timebase_lock
)paren
suffix:semicolon
)brace
DECL|function|smp_pSeries_kick_cpu
r_static
r_void
id|__devinit
id|smp_pSeries_kick_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
id|BUG_ON
c_func
(paren
id|nr
OL
l_int|0
op_logical_or
id|nr
op_ge
id|NR_CPUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smp_startup_cpu
c_func
(paren
id|nr
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * The processor is currently spinning, waiting for the&n;&t; * cpu_start field to become non-zero After we set cpu_start,&n;&t; * the processor will continue on to secondary_start&n;&t; */
id|paca
(braket
id|nr
)braket
dot
id|cpu_start
op_assign
l_int|1
suffix:semicolon
)brace
DECL|variable|pSeries_mpic_smp_ops
r_static
r_struct
id|smp_ops_t
id|pSeries_mpic_smp_ops
op_assign
(brace
dot
id|message_pass
op_assign
id|smp_mpic_message_pass
comma
dot
id|probe
op_assign
id|smp_mpic_probe
comma
dot
id|kick_cpu
op_assign
id|smp_pSeries_kick_cpu
comma
dot
id|setup_cpu
op_assign
id|smp_mpic_setup_cpu
comma
)brace
suffix:semicolon
DECL|variable|pSeries_xics_smp_ops
r_static
r_struct
id|smp_ops_t
id|pSeries_xics_smp_ops
op_assign
(brace
dot
id|message_pass
op_assign
id|smp_xics_message_pass
comma
dot
id|probe
op_assign
id|smp_xics_probe
comma
dot
id|kick_cpu
op_assign
id|smp_pSeries_kick_cpu
comma
dot
id|setup_cpu
op_assign
id|smp_xics_setup_cpu
comma
)brace
suffix:semicolon
multiline_comment|/* This is called very early */
DECL|function|smp_init_pSeries
r_void
id|__init
id|smp_init_pSeries
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
comma
id|i
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; -&gt; smp_init_pSeries()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc64_interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
id|smp_ops
op_assign
op_amp
id|pSeries_mpic_smp_ops
suffix:semicolon
r_else
id|smp_ops
op_assign
op_amp
id|pSeries_xics_smp_ops
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_CPU
id|smp_ops-&gt;cpu_disable
op_assign
id|pSeries_cpu_disable
suffix:semicolon
id|smp_ops-&gt;cpu_die
op_assign
id|pSeries_cpu_die
suffix:semicolon
macro_line|#endif
multiline_comment|/* Start secondary threads on SMT systems; primary threads&n;&t; * are already in the running state.&n;&t; */
id|for_each_present_cpu
c_func
(paren
id|i
)paren
(brace
r_if
c_cond
(paren
id|query_cpu_stopped
c_func
(paren
id|get_hard_smp_processor_id
c_func
(paren
id|i
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%16.16x : starting thread&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%16.16x : starting thread&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;start-cpu&quot;
)paren
comma
l_int|3
comma
l_int|1
comma
op_amp
id|ret
comma
id|get_hard_smp_processor_id
c_func
(paren
id|i
)paren
comma
id|__pa
c_func
(paren
(paren
id|u32
)paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|pSeries_secondary_smp_init
)paren
)paren
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Non-lpar has additional take/give timebase */
r_if
c_cond
(paren
id|rtas_token
c_func
(paren
l_string|&quot;freeze-time-base&quot;
)paren
op_ne
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
id|smp_ops-&gt;give_timebase
op_assign
id|pSeries_give_timebase
suffix:semicolon
id|smp_ops-&gt;take_timebase
op_assign
id|pSeries_take_timebase
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot; &lt;- smp_init_pSeries()&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
