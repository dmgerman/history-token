multiline_comment|/*&n; * SMP support for ppc.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great&n; * deal of code from the sparc and intel versions.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; * PowerPC-64 Support added by Dave Engebretsen, Peter Bergner, and&n; * Mike Corrigan {engebret|bergner|mikec}@us.ibm.com&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
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
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallCfg.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &quot;open_pic.h&quot;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
suffix:semicolon
DECL|variable|cache_decay_ticks
r_int
r_int
id|cache_decay_ticks
suffix:semicolon
multiline_comment|/* initialised so it doesn&squot;t end up in bss */
DECL|variable|cpu_online_map
id|cpumask_t
id|cpu_online_map
op_assign
id|CPU_MASK_NONE
suffix:semicolon
DECL|variable|smp_ops
r_static
r_struct
id|smp_ops_t
op_star
id|smp_ops
suffix:semicolon
DECL|variable|cpu_callin_map
r_static
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
id|stab_array
(braket
)braket
suffix:semicolon
r_extern
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
suffix:semicolon
r_void
id|smp_call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
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
suffix:semicolon
DECL|macro|smp_message_pass
mdefine_line|#define smp_message_pass(t,m,d,w) smp_ops-&gt;message_pass((t),(m),(d),(w))
DECL|function|set_tb
r_static
r_inline
r_void
id|set_tb
c_func
(paren
r_int
r_int
id|upper
comma
r_int
r_int
id|lower
)paren
(brace
id|mttbl
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|mttbu
c_func
(paren
id|upper
)paren
suffix:semicolon
id|mttbl
c_func
(paren
id|lower
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_ISERIES
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
comma
r_int
r_int
id|data
comma
r_int
id|wait
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|target
op_eq
id|MSG_ALL
)paren
op_logical_or
(paren
id|target
op_eq
id|i
)paren
op_logical_or
(paren
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
)paren
op_logical_and
(paren
id|i
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
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
id|i
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
id|i
)braket
)paren
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
r_struct
id|ItLpPaca
op_star
id|lpPaca
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
id|lpPaca
op_assign
id|paca
(braket
id|i
)braket
dot
id|xLpPacaPtr
suffix:semicolon
r_if
c_cond
(paren
id|lpPaca-&gt;xDynProcStatus
OL
l_int|2
)paren
(brace
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
r_struct
id|ItLpPaca
op_star
id|lpPaca
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
id|lpPaca
op_assign
id|paca
(braket
id|i
)braket
dot
id|xLpPacaPtr
suffix:semicolon
r_if
c_cond
(paren
id|lpPaca-&gt;xDynProcStatus
OL
l_int|2
)paren
(brace
id|paca
(braket
id|i
)braket
dot
id|active
op_assign
l_int|1
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
r_struct
id|ItLpPaca
op_star
id|lpPaca
suffix:semicolon
multiline_comment|/* Verify we have a Paca for processor nr */
r_if
c_cond
(paren
(paren
id|nr
op_le
l_int|0
)paren
op_logical_or
(paren
id|nr
op_ge
id|NR_CPUS
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Verify that our partition has a processor nr */
id|lpPaca
op_assign
id|paca
(braket
id|nr
)braket
dot
id|xLpPacaPtr
suffix:semicolon
r_if
c_cond
(paren
id|lpPaca-&gt;xDynProcStatus
op_ge
l_int|2
)paren
r_return
suffix:semicolon
multiline_comment|/* The information for processor bringup must&n;&t; * be written out to main store before we release&n;&t; * the processor.&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The processor is currently spinning, waiting&n;&t; * for the xProcStart field to become non-zero&n;&t; * After we set xProcStart, the processor will&n;&t; * continue on to secondary_start in iSeries_head.S&n;&t; */
id|paca
(braket
id|nr
)braket
dot
id|xProcStart
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
id|ppc_md.smp_ops
suffix:semicolon
id|smp_ops-&gt;message_pass
op_assign
id|smp_iSeries_message_pass
suffix:semicolon
id|smp_ops-&gt;probe
op_assign
id|smp_iSeries_probe
suffix:semicolon
id|smp_ops-&gt;kick_cpu
op_assign
id|smp_iSeries_kick_cpu
suffix:semicolon
id|smp_ops-&gt;setup_cpu
op_assign
id|smp_iSeries_setup_cpu
suffix:semicolon
macro_line|#warning fix for iseries
id|systemcfg-&gt;processorCount
op_assign
id|smp_iSeries_numProcs
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_PSERIES
r_static
r_void
DECL|function|smp_openpic_message_pass
id|smp_openpic_message_pass
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
multiline_comment|/* make sure we&squot;re sending something that translates to an IPI */
r_if
c_cond
(paren
id|msg
OG
l_int|0x3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SMP %d: smp_message_pass: unknown msg %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|target
)paren
(brace
r_case
id|MSG_ALL
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|msg
comma
l_int|0xffffffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MSG_ALL_BUT_SELF
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|msg
comma
l_int|0xffffffff
op_amp
op_complement
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|msg
comma
l_int|1
op_lshift
id|target
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|smp_openpic_probe
r_static
r_int
id|__init
id|smp_openpic_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|nr_cpus
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
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|nr_cpus
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_cpus
OG
l_int|1
)paren
id|openpic_request_IPIs
c_func
(paren
)paren
suffix:semicolon
r_return
id|nr_cpus
suffix:semicolon
)brace
r_static
r_void
DECL|function|smp_kick_cpu
id|smp_kick_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
multiline_comment|/* Verify we have a Paca for processor nr */
r_if
c_cond
(paren
(paren
id|nr
op_le
l_int|0
)paren
op_logical_or
(paren
id|nr
op_ge
id|NR_CPUS
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* The information for processor bringup must&n;&t; * be written out to main store before we release&n;&t; * the processor.&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The processor is currently spinning, waiting&n;&t; * for the xProcStart field to become non-zero&n;&t; * After we set xProcStart, the processor will&n;&t; * continue on to secondary_start&n;&t; */
id|paca
(braket
id|nr
)braket
dot
id|xProcStart
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|smp_space_timers
r_static
r_void
id|__init
id|smp_space_timers
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|tb_ticks_per_jiffy
op_div
id|max_cpus
suffix:semicolon
r_int
r_int
id|previous_tb
op_assign
id|paca
(braket
id|boot_cpuid
)braket
dot
id|next_jiffy_update_tb
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
id|cpu_possible
c_func
(paren
id|i
)paren
op_logical_and
id|i
op_ne
id|boot_cpuid
)paren
(brace
id|paca
(braket
id|i
)braket
dot
id|next_jiffy_update_tb
op_assign
id|previous_tb
op_plus
id|offset
suffix:semicolon
id|previous_tb
op_assign
id|paca
(braket
id|i
)braket
dot
id|next_jiffy_update_tb
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
DECL|function|pSeries_setup_cpu
r_static
r_void
id|__devinit
id|pSeries_setup_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
(brace
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
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
)brace
)brace
r_static
r_void
DECL|function|smp_xics_message_pass
id|smp_xics_message_pass
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL
op_logical_or
id|target
op_eq
id|i
op_logical_or
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
op_logical_and
id|i
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
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
id|i
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
id|i
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
r_int
id|i
suffix:semicolon
r_int
id|nr_cpus
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
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|nr_cpus
op_increment
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|xics_request_IPIs
c_func
(paren
r_void
)paren
suffix:semicolon
id|xics_request_IPIs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nr_cpus
suffix:semicolon
)brace
DECL|variable|timebase_lock
r_static
id|spinlock_t
id|timebase_lock
op_assign
id|SPIN_LOCK_UNLOCKED
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
id|smp_ops
op_assign
op_amp
id|ppc_md.smp_ops
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
(brace
id|smp_ops-&gt;message_pass
op_assign
id|smp_openpic_message_pass
suffix:semicolon
id|smp_ops-&gt;probe
op_assign
id|smp_openpic_probe
suffix:semicolon
)brace
r_else
(brace
id|smp_ops-&gt;message_pass
op_assign
id|smp_xics_message_pass
suffix:semicolon
id|smp_ops-&gt;probe
op_assign
id|smp_xics_probe
suffix:semicolon
)brace
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES
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
id|smp_ops-&gt;kick_cpu
op_assign
id|smp_kick_cpu
suffix:semicolon
id|smp_ops-&gt;setup_cpu
op_assign
id|pSeries_setup_cpu
suffix:semicolon
)brace
macro_line|#endif
DECL|function|smp_local_timer_interrupt
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|prof_counter
)paren
)paren
(brace
id|update_process_times
c_func
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|prof_counter
)paren
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|prof_multiplier
suffix:semicolon
)brace
)brace
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
multiline_comment|/* XXX Do we have to do this? */
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|PPC_MSG_MIGRATE_TASK
suffix:colon
multiline_comment|/* spare */
r_break
suffix:semicolon
macro_line|#endif
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
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
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
DECL|variable|__cacheline_aligned_in_smp
r_static
id|spinlock_t
id|call_lock
id|__cacheline_aligned_in_smp
op_assign
id|SPIN_LOCK_UNLOCKED
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
multiline_comment|/* delay of at least 8 seconds on 1GHz cpu */
DECL|macro|SMP_CALL_TIMEOUT
mdefine_line|#define SMP_CALL_TIMEOUT (1UL &lt;&lt; (30 + 3))
multiline_comment|/*&n; * This function sends a &squot;generic call function&squot; IPI to all other CPUs&n; * in the system.&n; *&n; * [SUMMARY] Run a function on all other CPUs.&n; * &lt;func&gt; The function to run. This must be fast and non-blocking.&n; * &lt;info&gt; An arbitrary pointer to pass to the function.&n; * &lt;nonatomic&gt; currently unused.&n; * &lt;wait&gt; If true, wait (atomically) until function has completed on other CPUs.&n; * [RETURNS] 0 on success, else a negative status code. Does not return until&n; * remote CPUs are nearly ready to execute &lt;&lt;func&gt;&gt; or are or have executed.&n; *&n; * You must not call this function with disabled interrupts or from a&n; * hardware interrupt handler or from a bottom half handler.&n; */
DECL|function|smp_call_function
r_int
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
id|ret
op_assign
op_minus
l_int|1
comma
id|cpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|timeout
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
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Send a message to all other CPUs and wait for them to respond */
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
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
id|SMP_CALL_TIMEOUT
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
id|cpus
)paren
(brace
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|timeout
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger
)paren
id|debugger
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;smp_call_function on cpu %d: other cpus not &quot;
l_string|&quot;responding (%d)&bslash;n&quot;
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
)brace
r_if
c_cond
(paren
id|wait
)paren
(brace
id|timeout
op_assign
id|SMP_CALL_TIMEOUT
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
id|cpus
)paren
(brace
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|timeout
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger
)paren
id|debugger
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;smp_call_function on cpu %d: other &quot;
l_string|&quot;cpus not finishing (%d/%d)&bslash;n&quot;
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
)brace
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
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
r_extern
r_int
r_int
id|decr_overclock
suffix:semicolon
r_extern
r_struct
id|gettimeofday_struct
id|do_gtod
suffix:semicolon
DECL|variable|current_set
r_struct
id|thread_info
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
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
id|paca
(braket
id|id
)braket
dot
id|pvr
op_assign
id|_get_PVR
c_func
(paren
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
id|paca
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|prof_counter
op_assign
l_int|1
suffix:semicolon
id|paca
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|prof_multiplier
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * XXX very rough. &n;&t; */
id|cache_decay_ticks
op_assign
id|HZ
op_div
l_int|100
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
id|paca
(braket
id|boot_cpuid
)braket
dot
id|next_jiffy_update_tb
op_assign
id|tb_last_stamp
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Should update do_gtod.stamp_xsec.&n;&t; * For now we leave it which means the time can be some&n;&t; * number of msecs off until someone does a settimeofday()&n;&t; */
id|do_gtod.tb_orig_stamp
op_assign
id|tb_last_stamp
suffix:semicolon
macro_line|#endif
id|max_cpus
op_assign
id|smp_ops
op_member_access_from_pointer
id|probe
c_func
(paren
)paren
suffix:semicolon
id|smp_space_timers
c_func
(paren
id|max_cpus
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
multiline_comment|/* FIXME: what about cpu_possible()? */
)brace
DECL|function|__cpu_up
r_int
id|__devinit
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|c
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|prof_counter
op_assign
l_int|1
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|prof_multiplier
op_assign
l_int|1
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|default_decr
op_assign
id|tb_ticks_per_jiffy
op_div
id|decr_overclock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SLB
)paren
)paren
(brace
r_void
op_star
id|tmp
suffix:semicolon
multiline_comment|/* maximum of 48 CPUs on machines with a segment table */
r_if
c_cond
(paren
id|cpu
op_ge
l_int|48
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|tmp
op_assign
op_amp
id|stab_array
(braket
id|PAGE_SIZE
op_star
id|cpu
)braket
suffix:semicolon
id|memset
c_func
(paren
id|tmp
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|xStab_data.virt
op_assign
(paren
r_int
r_int
)paren
id|tmp
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|xStab_data.real
op_assign
(paren
r_int
r_int
)paren
id|__v2a
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/* create a process for the processor */
multiline_comment|/* only regs.msr is actually used, and 0 is OK for it */
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|p
op_assign
id|copy_process
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_IDLETASK
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
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
id|wake_up_forked_process
c_func
(paren
id|p
)paren
suffix:semicolon
id|init_idle
c_func
(paren
id|p
comma
id|cpu
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|p
)paren
suffix:semicolon
id|paca
(braket
id|cpu
)braket
dot
id|xCurrent
op_assign
(paren
id|u64
)paren
id|p
suffix:semicolon
id|current_set
(braket
id|cpu
)braket
op_assign
id|p-&gt;thread_info
suffix:semicolon
multiline_comment|/* wake up cpus */
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
l_int|5000
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
id|printk
c_func
(paren
l_string|&quot;Processor %u found.&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_ops-&gt;give_timebase
)paren
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
multiline_comment|/* Activate a secondary processor. */
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
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
id|smp_store_cpu_info
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|set_dec
c_func
(paren
id|paca
(braket
id|cpu
)braket
dot
id|default_decr
)paren
suffix:semicolon
id|cpu_callin_map
(braket
id|cpu
)braket
op_assign
l_int|1
suffix:semicolon
id|smp_ops
op_member_access_from_pointer
id|setup_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_ops-&gt;take_timebase
)paren
id|smp_ops
op_member_access_from_pointer
id|take_timebase
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|cpu_idle
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_cpus_done
r_void
id|__init
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
id|boot_cpuid
)paren
suffix:semicolon
multiline_comment|/* XXX fix this, xics currently relies on it - Anton */
id|smp_threads_ready
op_assign
l_int|1
suffix:semicolon
)brace
eof
