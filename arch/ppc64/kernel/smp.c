multiline_comment|/*&n; * &n; *&n; * SMP support for ppc.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great&n; * deal of code from the sparc and intel versions.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; * PowerPC-64 Support added by Dave Engebretsen, Peter Bergner, and&n; * Mike Corrigan {engebret|bergner|mikec}@us.ibm.com&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* #include &lt;linux/openpic.h&gt; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/Naca.h&gt;
macro_line|#include &lt;asm/Paca.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallCfg.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &quot;open_pic.h&quot;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
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
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
DECL|variable|smp_tb_synchronized
r_int
id|smp_tb_synchronized
op_assign
l_int|0
suffix:semicolon
DECL|variable|__cacheline_aligned
id|spinlock_t
id|kernel_flag
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|cacheflush_time
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|variable|cache_decay_ticks
r_int
r_int
id|cache_decay_ticks
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|max_cpus
id|__initdata
op_assign
id|NR_CPUS
suffix:semicolon
DECL|variable|cpu_online_map
r_int
r_int
id|cpu_online_map
suffix:semicolon
DECL|variable|cpu_callin_map
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|macro|TB_SYNC_PASSES
mdefine_line|#define TB_SYNC_PASSES 4
DECL|variable|tb_sync_flag
r_volatile
r_int
r_int
id|__initdata
id|tb_sync_flag
op_assign
l_int|0
suffix:semicolon
DECL|variable|tb_offset
r_volatile
r_int
r_int
id|__initdata
id|tb_offset
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_char
id|stab_array
(braket
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
DECL|variable|iSeries_smp_message
r_static
r_int
r_int
id|iSeries_smp_message
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_struct
id|Naca
op_star
id|naca
suffix:semicolon
r_extern
r_struct
id|Paca
id|xPaca
(braket
)braket
suffix:semicolon
r_void
id|xics_setup_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|xics_cause_IPI
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n; * XICS only has a single IPI, so encode the messages per CPU&n; */
DECL|variable|xics_ipi_message
r_volatile
r_int
r_int
id|xics_ipi_message
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|macro|smp_message_pass
mdefine_line|#define smp_message_pass(t,m,d,w) ppc_md.smp_message_pass((t),(m),(d),(w))
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
id|mtspr
c_func
(paren
id|SPRN_TBWL
comma
l_int|0
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_TBWU
comma
id|upper
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_TBWL
comma
id|lower
)paren
suffix:semicolon
)brace
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
id|smp_num_cpus
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
id|smp_num_cpus
suffix:semicolon
op_increment
id|i
)paren
(brace
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
id|xPaca
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
id|maxPacas
suffix:semicolon
op_increment
id|i
)paren
(brace
id|lpPaca
op_assign
id|xPaca
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
id|maxPacas
suffix:semicolon
op_increment
id|i
)paren
(brace
id|lpPaca
op_assign
id|xPaca
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
id|xPaca
(braket
id|i
)braket
dot
id|next_jiffy_update_tb
op_assign
id|xPaca
(braket
l_int|0
)braket
dot
id|next_jiffy_update_tb
suffix:semicolon
)brace
)brace
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
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
id|maxPacas
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Verify that our partition has a processor nr */
id|lpPaca
op_assign
id|xPaca
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
multiline_comment|/* The processor is currently spinning, waiting&n;&t; * for the xProcStart field to become non-zero&n;&t; * After we set xProcStart, the processor will&n;&t; * continue on to secondary_start in iSeries_head.S&n;&t; */
id|xPaca
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
id|smp_init_iSeries
c_func
(paren
r_void
)paren
(brace
id|ppc_md.smp_message_pass
op_assign
id|smp_iSeries_message_pass
suffix:semicolon
id|ppc_md.smp_probe
op_assign
id|smp_iSeries_probe
suffix:semicolon
id|ppc_md.smp_kick_cpu
op_assign
id|smp_iSeries_kick_cpu
suffix:semicolon
id|ppc_md.smp_setup_cpu
op_assign
id|smp_iSeries_setup_cpu
suffix:semicolon
id|naca-&gt;processorCount
op_assign
id|smp_iSeries_numProcs
c_func
(paren
)paren
suffix:semicolon
)brace
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
r_static
r_int
DECL|function|smp_chrp_probe
id|smp_chrp_probe
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|naca-&gt;processorCount
OG
l_int|1
)paren
id|openpic_request_IPIs
c_func
(paren
)paren
suffix:semicolon
r_return
id|naca-&gt;processorCount
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
id|maxPacas
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* The processor is currently spinning, waiting&n;&t; * for the xProcStart field to become non-zero&n;&t; * After we set xProcStart, the processor will&n;&t; * continue on to secondary_start in iSeries_head.S&n;&t; */
id|xPaca
(braket
id|nr
)braket
dot
id|xProcStart
op_assign
l_int|1
suffix:semicolon
)brace
r_extern
r_struct
id|gettimeofday_struct
id|do_gtod
suffix:semicolon
DECL|function|smp_space_timers
r_static
r_void
id|smp_space_timers
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
r_int
id|offset
comma
id|i
suffix:semicolon
id|offset
op_assign
id|tb_ticks_per_jiffy
op_div
id|nr
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
op_increment
id|i
)paren
(brace
id|xPaca
(braket
id|i
)braket
dot
id|next_jiffy_update_tb
op_assign
id|xPaca
(braket
id|i
op_minus
l_int|1
)braket
dot
id|next_jiffy_update_tb
op_plus
id|offset
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|smp_chrp_setup_cpu
id|smp_chrp_setup_cpu
c_func
(paren
r_int
id|cpu_nr
)paren
(brace
r_static
id|atomic_t
id|ready
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_static
r_volatile
r_int
id|frozen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_pSeriesLP
)paren
(brace
multiline_comment|/* timebases already synced under the hypervisor. */
id|xPaca
(braket
id|cpu_nr
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
r_if
c_cond
(paren
id|cpu_nr
op_eq
l_int|0
)paren
(brace
id|do_gtod.tb_orig_stamp
op_assign
id|tb_last_stamp
suffix:semicolon
multiline_comment|/* Should update do_gtod.stamp_xsec.&n;&t;&t;&t; * For now we leave it which means the time can be some&n;&t;&t;&t; * number of msecs off until someone does a settimeofday()&n;&t;&t;&t; */
)brace
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cpu_nr
op_eq
l_int|0
)paren
(brace
multiline_comment|/* wait for all the others */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ready
)paren
OL
id|smp_num_cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ready
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* freeze the timebase */
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
id|mb
c_func
(paren
)paren
suffix:semicolon
id|frozen
op_assign
l_int|1
suffix:semicolon
id|set_tb
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|xPaca
(braket
l_int|0
)braket
dot
id|next_jiffy_update_tb
op_assign
l_int|0
suffix:semicolon
id|smp_space_timers
c_func
(paren
id|smp_num_cpus
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ready
)paren
OL
id|smp_num_cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* thaw the timebase again */
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
id|mb
c_func
(paren
)paren
suffix:semicolon
id|frozen
op_assign
l_int|0
suffix:semicolon
id|tb_last_stamp
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
id|do_gtod.tb_orig_stamp
op_assign
id|tb_last_stamp
suffix:semicolon
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ready
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|frozen
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|set_tb
c_func
(paren
l_int|0
comma
l_int|0
)paren
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
id|ready
)paren
suffix:semicolon
r_while
c_loop
(paren
id|frozen
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
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
id|cpu_nr
OG
l_int|0
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
id|smp_num_cpus
suffix:semicolon
op_increment
id|i
)paren
(brace
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
r_static
r_int
DECL|function|smp_xics_probe
id|smp_xics_probe
c_func
(paren
r_void
)paren
(brace
r_return
id|naca-&gt;processorCount
suffix:semicolon
)brace
multiline_comment|/* This is called very early */
DECL|function|smp_init_pSeries
r_void
id|smp_init_pSeries
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
(brace
id|ppc_md.smp_message_pass
op_assign
id|smp_openpic_message_pass
suffix:semicolon
id|ppc_md.smp_probe
op_assign
id|smp_chrp_probe
suffix:semicolon
id|ppc_md.smp_kick_cpu
op_assign
id|smp_kick_cpu
suffix:semicolon
id|ppc_md.smp_setup_cpu
op_assign
id|smp_chrp_setup_cpu
suffix:semicolon
)brace
r_else
(brace
id|ppc_md.smp_message_pass
op_assign
id|smp_xics_message_pass
suffix:semicolon
id|ppc_md.smp_probe
op_assign
id|smp_xics_probe
suffix:semicolon
id|ppc_md.smp_kick_cpu
op_assign
id|smp_kick_cpu
suffix:semicolon
id|ppc_md.smp_setup_cpu
op_assign
id|smp_chrp_setup_cpu
suffix:semicolon
)brace
)brace
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
DECL|variable|migration_lock
r_static
id|spinlock_t
id|migration_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|new_task
r_static
id|task_t
op_star
id|new_task
suffix:semicolon
multiline_comment|/*&n; * This function sends a &squot;task migration&squot; IPI to another CPU.&n; * Must be called from syscall contexts, with interrupts *enabled*.&n; */
DECL|function|smp_migrate_task
r_void
id|smp_migrate_task
c_func
(paren
r_int
id|cpu
comma
id|task_t
op_star
id|p
)paren
(brace
multiline_comment|/*&n;&t; * The target CPU will unlock the migration spinlock:&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|migration_lock
)paren
suffix:semicolon
id|new_task
op_assign
id|p
suffix:semicolon
id|smp_message_pass
c_func
(paren
id|cpu
comma
id|PPC_MSG_MIGRATE_TASK
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Task migration callback.&n; */
DECL|function|smp_task_migration_interrupt
r_static
r_void
id|smp_task_migration_interrupt
c_func
(paren
r_void
)paren
(brace
id|task_t
op_star
id|p
suffix:semicolon
multiline_comment|/* Should we ACK the IPI interrupt early? */
id|p
op_assign
id|new_task
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|migration_lock
)paren
suffix:semicolon
id|sched_task_migrated
c_func
(paren
id|p
)paren
suffix:semicolon
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
r_case
id|PPC_MSG_MIGRATE_TASK
suffix:colon
id|smp_task_migration_interrupt
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
multiline_comment|/*&n; * this function sends a reschedule IPI to all (other) CPUs.&n; * This should only be used if some &squot;global&squot; task became runnable,&n; * such as a RT task, that must be handled now. The first CPU&n; * that manages to grab the task will run it.&n; */
DECL|function|smp_send_reschedule_all
r_void
id|smp_send_reschedule_all
c_func
(paren
r_void
)paren
(brace
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
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
id|__cli
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
id|smp_num_cpus
op_assign
l_int|1
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
multiline_comment|/*&n; * This function sends a &squot;generic call function&squot; IPI to all other CPUs&n; * in the system.&n; *&n; * [SUMMARY] Run a function on all other CPUs.&n; * &lt;func&gt; The function to run. This must be fast and non-blocking.&n; * &lt;info&gt; An arbitrary pointer to pass to the function.&n; * &lt;nonatomic&gt; currently unused.&n; * &lt;wait&gt; If true, wait (atomically) until function has completed on other CPUs.&n; * [RETURNS] 0 on success, else a negative status code. Does not return until&n; * remote CPUs are nearly ready to execute &lt;&lt;func&gt;&gt; or are or have executed.&n; *&n; * You must not call this function with disabled interrupts or from a&n; * hardware interrupt handler, you may call it from a bottom half handler.&n; */
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
id|smp_num_cpus
op_minus
l_int|1
suffix:semicolon
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
l_int|8000000
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
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_ISERIES
id|HvCall_terminateMachineSrc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_PPC_ISERIES
id|HvCall_terminateMachineSrc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_bh
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
DECL|variable|current_set
r_struct
id|thread_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
op_assign
(brace
op_amp
id|init_thread_union
comma
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
r_struct
id|Paca
op_star
id|paca
suffix:semicolon
r_int
id|i
comma
id|cpu_nr
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Entering SMP Mode...&bslash;n&quot;
)paren
suffix:semicolon
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|cpu_online_map
op_assign
l_int|1UL
suffix:semicolon
multiline_comment|/*&n;&t; * assume for now that the first cpu booted is&n;&t; * cpu 0, the master -- Cort&n;&t; */
id|cpu_callin_map
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* XXX buggy - Anton */
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|cpu
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
id|paca
op_assign
op_amp
id|xPaca
(braket
id|i
)braket
suffix:semicolon
id|paca-&gt;prof_counter
op_assign
l_int|1
suffix:semicolon
id|paca-&gt;prof_multiplier
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Processor 0&squot;s segment table is statically &n;&t;&t;&t; * initialized to real address 0x5000.  The&n;&t;&t;&t; * Other processor&squot;s tables are created and&n;&t;&t;&t; * initialized here.&n;&t;&t;&t; */
id|paca-&gt;xStab_data.virt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|stab_array
(braket
id|PAGE_SIZE
op_star
(paren
id|i
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|paca-&gt;xStab_data.virt
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|paca-&gt;xStab_data.real
op_assign
id|__v2a
c_func
(paren
id|paca-&gt;xStab_data.virt
)paren
suffix:semicolon
id|paca-&gt;default_decr
op_assign
id|tb_ticks_per_jiffy
op_div
id|decr_overclock
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * XXX very rough, assumes 20 bus cycles to read a cache line,&n;&t; * timebase increments every 4 bus cycles, 32kB L1 data cache.&n;&t; */
id|cacheflush_time
op_assign
l_int|5
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* XXX - Fix - Anton */
id|cache_decay_ticks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Probe arch for CPUs */
id|cpu_nr
op_assign
id|ppc_md
dot
id|smp_probe
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Probe found %d CPUs&bslash;n&quot;
comma
id|cpu_nr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * only check for cpus we know exist.  We keep the callin map&n;&t; * with cpus at the bottom -- Cort&n;&t; */
r_if
c_cond
(paren
id|cpu_nr
OG
id|max_cpus
)paren
id|cpu_nr
op_assign
id|max_cpus
suffix:semicolon
macro_line|#ifdef CONFIG_ISERIES
id|smp_space_timers
c_func
(paren
id|cpu_nr
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Waiting for %d CPUs&bslash;n&quot;
comma
id|cpu_nr
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|cpu_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|c
suffix:semicolon
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* create a process for the processor */
multiline_comment|/* we don&squot;t care about the values in regs since we&squot;ll&n;&t;&t;   never reschedule the forked task. */
multiline_comment|/* We DO care about one bit in the pt_regs we&n;&t;&t;   pass to do_fork.  That is the MSR_FP bit in&n;&t;&t;   regs.msr.  If that bit is on, then do_fork&n;&t;&t;   (via copy_thread) will call giveup_fpu.&n;&t;&t;   giveup_fpu will get a pointer to our (current&squot;s)&n;&t;&t;   last register savearea via current-&gt;thread.regs&n;&t;&t;   and using that pointer will turn off the MSR_FP,&n;&t;&t;   MSR_FE0 and MSR_FE1 bits.  At this point, this&n;&t;&t;   pointer is pointing to some arbitrary point within&n;&t;&t;   our stack */
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
r_if
c_cond
(paren
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_PID
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;failed fork for CPU %d&quot;
comma
id|i
)paren
suffix:semicolon
id|p
op_assign
id|prev_task
c_func
(paren
op_amp
id|init_task
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|panic
c_func
(paren
l_string|&quot;No idle task for CPU %d&quot;
comma
id|i
)paren
suffix:semicolon
id|init_idle
c_func
(paren
id|p
comma
id|i
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|p
)paren
suffix:semicolon
id|xPaca
(braket
id|i
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
id|i
)braket
op_assign
id|p-&gt;thread_info
suffix:semicolon
multiline_comment|/* wake up cpus */
id|ppc_md
dot
id|smp_kick_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait to see if the cpu made a callin (is actually up).&n;&t;&t; * use this value that I found through experimentation.&n;&t;&t; * -- Cort&n;&t;&t; */
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
id|i
)braket
suffix:semicolon
id|c
op_decrement
)paren
(brace
id|udelay
c_func
(paren
l_int|100
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
id|printk
c_func
(paren
l_string|&quot;Processor %d found.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* this sync&squot;s the decr&squot;s -- Cort */
id|smp_num_cpus
op_increment
suffix:semicolon
)brace
r_else
(brace
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
multiline_comment|/* Setup CPU 0 last (important) */
id|ppc_md
dot
id|smp_setup_cpu
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_num_cpus
OL
l_int|2
)paren
(brace
id|tb_last_stamp
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
)brace
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
id|PPCDBG
c_func
(paren
id|PPCDBG_SMP
comma
l_string|&quot;smp_commence: start&bslash;n&quot;
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|smp_commenced
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|smp_callin
r_void
id|__init
id|smp_callin
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
id|smp_store_cpu_info
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|set_dec
c_func
(paren
id|xPaca
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
id|set_bit
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
id|ppc_md
dot
id|smp_setup_cpu
c_func
(paren
id|cpu
)paren
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
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* intel needs this */
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
id|smp_callin
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
multiline_comment|/* this function is called for each processor&n; */
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
id|xPaca
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
DECL|function|maxcpus
r_static
r_int
id|__init
id|maxcpus
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|max_cpus
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;maxcpus=&quot;
comma
id|maxcpus
)paren
suffix:semicolon
eof
