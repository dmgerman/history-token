multiline_comment|/*&n; * SMP support for iSeries machines.&n; *&n; * Dave Engebretsen, Peter Bergner, and&n; * Mike Corrigan {engebret|bergner|mikec}@us.ibm.com&n; *&n; * Plus various changes from other IBM teams...&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
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
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallCfg.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|iSeries_smp_message
r_static
r_int
r_int
id|iSeries_smp_message
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|iSeries_smp_message_recv
r_void
id|iSeries_smp_message_recv
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
r_int
id|msg
suffix:semicolon
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
OL
l_int|2
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|msg
op_assign
l_int|0
suffix:semicolon
id|msg
OL
l_int|4
suffix:semicolon
op_increment
id|msg
)paren
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|msg
comma
op_amp
id|iSeries_smp_message
(braket
id|cpu
)braket
)paren
)paren
id|smp_message_recv
c_func
(paren
id|msg
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|smp_iSeries_do_message
r_static
r_inline
r_void
id|smp_iSeries_do_message
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
id|iSeries_smp_message
(braket
id|cpu
)braket
)paren
suffix:semicolon
id|HvCall_sendIPI
c_func
(paren
op_amp
(paren
id|paca
(braket
id|cpu
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|smp_iSeries_message_pass
r_static
r_void
id|smp_iSeries_message_pass
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
id|i
suffix:semicolon
r_if
c_cond
(paren
id|target
OL
id|NR_CPUS
)paren
id|smp_iSeries_do_message
c_func
(paren
id|target
comma
id|msg
)paren
suffix:semicolon
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
id|smp_iSeries_do_message
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
DECL|function|smp_iSeries_numProcs
r_static
r_int
id|smp_iSeries_numProcs
c_func
(paren
r_void
)paren
(brace
r_int
id|np
comma
id|i
suffix:semicolon
id|np
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|paca
(braket
id|i
)braket
dot
id|lppaca.dyn_proc_status
OL
l_int|2
)paren
(brace
id|cpu_set
c_func
(paren
id|i
comma
id|cpu_possible_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|i
comma
id|cpu_present_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|i
comma
id|cpu_sibling_map
(braket
id|i
)braket
)paren
suffix:semicolon
op_increment
id|np
suffix:semicolon
)brace
)brace
r_return
id|np
suffix:semicolon
)brace
DECL|function|smp_iSeries_probe
r_static
r_int
id|smp_iSeries_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|np
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|paca
(braket
id|i
)braket
dot
id|lppaca.dyn_proc_status
OL
l_int|2
)paren
(brace
multiline_comment|/*paca[i].active = 1;*/
op_increment
id|np
suffix:semicolon
)brace
)brace
r_return
id|np
suffix:semicolon
)brace
DECL|function|smp_iSeries_kick_cpu
r_static
r_void
id|smp_iSeries_kick_cpu
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
multiline_comment|/* Verify that our partition has a processor nr */
r_if
c_cond
(paren
id|paca
(braket
id|nr
)braket
dot
id|lppaca.dyn_proc_status
op_ge
l_int|2
)paren
r_return
suffix:semicolon
multiline_comment|/* The processor is currently spinning, waiting&n;&t; * for the cpu_start field to become non-zero&n;&t; * After we set cpu_start, the processor will&n;&t; * continue on to secondary_start in iSeries_head.S&n;&t; */
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
DECL|function|smp_iSeries_setup_cpu
r_static
r_void
id|__devinit
id|smp_iSeries_setup_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
)brace
DECL|variable|iSeries_smp_ops
r_static
r_struct
id|smp_ops_t
id|iSeries_smp_ops
op_assign
(brace
dot
id|message_pass
op_assign
id|smp_iSeries_message_pass
comma
dot
id|probe
op_assign
id|smp_iSeries_probe
comma
dot
id|kick_cpu
op_assign
id|smp_iSeries_kick_cpu
comma
dot
id|setup_cpu
op_assign
id|smp_iSeries_setup_cpu
comma
)brace
suffix:semicolon
multiline_comment|/* This is called very early. */
DECL|function|smp_init_iSeries
r_void
id|__init
id|smp_init_iSeries
c_func
(paren
r_void
)paren
(brace
id|smp_ops
op_assign
op_amp
id|iSeries_smp_ops
suffix:semicolon
id|systemcfg-&gt;processorCount
op_assign
id|smp_iSeries_numProcs
c_func
(paren
)paren
suffix:semicolon
)brace
eof
