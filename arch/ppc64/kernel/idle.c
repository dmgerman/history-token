multiline_comment|/*&n; * Idle daemon for PowerPC.  Idle daemon will handle any action&n; * that needs to be taken when the system becomes idle.&n; *&n; * Originally Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * iSeries supported added by Mike Corrigan &lt;mikejc@us.ibm.com&gt;&n; *&n; * Additional shared processor, SMT, and firmware support&n; *    Copyright (c) 2003 Dave Engebretsen &lt;engebret@us.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/plpar_wrappers.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
r_extern
r_void
id|power4_idle
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|idle_loop
r_static
r_int
(paren
op_star
id|idle_loop
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|maxYieldTime
r_static
r_int
r_int
id|maxYieldTime
op_assign
l_int|0
suffix:semicolon
DECL|variable|minYieldTime
r_static
r_int
r_int
id|minYieldTime
op_assign
l_int|0xffffffffffffffffUL
suffix:semicolon
DECL|function|yield_shared_processor
r_static
r_void
id|yield_shared_processor
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tb
suffix:semicolon
r_int
r_int
id|yieldTime
suffix:semicolon
id|HvCall_setEnabledInterrupts
c_func
(paren
id|HvCall_MaskIPI
op_or
id|HvCall_MaskLpEvent
op_or
id|HvCall_MaskLpProd
op_or
id|HvCall_MaskTimeout
)paren
suffix:semicolon
id|tb
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Compute future tb value when yield should expire */
id|HvCall_yieldProcessor
c_func
(paren
id|HvCall_YieldTimed
comma
id|tb
op_plus
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
id|yieldTime
op_assign
id|get_tb
c_func
(paren
)paren
op_minus
id|tb
suffix:semicolon
r_if
c_cond
(paren
id|yieldTime
OG
id|maxYieldTime
)paren
id|maxYieldTime
op_assign
id|yieldTime
suffix:semicolon
r_if
c_cond
(paren
id|yieldTime
OL
id|minYieldTime
)paren
id|minYieldTime
op_assign
id|yieldTime
suffix:semicolon
multiline_comment|/*&n;&t; * The decrementer stops during the yield.  Force a fake decrementer&n;&t; * here and let the timer_interrupt code sort out the actual time.&n;&t; */
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|lppaca.int_dword.fields.decr_int
op_assign
l_int|1
suffix:semicolon
id|process_iSeries_events
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|iSeries_idle
r_static
r_int
id|iSeries_idle
c_func
(paren
r_void
)paren
(brace
r_struct
id|paca_struct
op_star
id|lpaca
suffix:semicolon
r_int
id|oldval
suffix:semicolon
r_int
r_int
id|CTRL
suffix:semicolon
multiline_comment|/* ensure iSeries run light will be out when idle */
id|clear_thread_flag
c_func
(paren
id|TIF_RUN_LIGHT
)paren
suffix:semicolon
id|CTRL
op_assign
id|mfspr
c_func
(paren
id|CTRLF
)paren
suffix:semicolon
id|CTRL
op_and_assign
op_complement
id|RUNLATCH
suffix:semicolon
id|mtspr
c_func
(paren
id|CTRLT
comma
id|CTRL
)paren
suffix:semicolon
id|lpaca
op_assign
id|get_paca
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
r_if
c_cond
(paren
id|lpaca-&gt;lppaca.shared_proc
)paren
(brace
r_if
c_cond
(paren
id|ItLpQueue_isLpIntPending
c_func
(paren
id|lpaca-&gt;lpqueue_ptr
)paren
)paren
id|process_iSeries_events
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|yield_shared_processor
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ItLpQueue_isLpIntPending
c_func
(paren
id|lpaca-&gt;lpqueue_ptr
)paren
)paren
id|process_iSeries_events
c_func
(paren
)paren
suffix:semicolon
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
)brace
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|default_idle
r_static
r_int
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_int
id|oldval
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
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
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Go into low thread priority and possibly&n;&t;&t;&t;&t; * low power mode.&n;&t;&t;&t;&t; */
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
id|HMT_very_low
c_func
(paren
)paren
suffix:semicolon
)brace
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
op_logical_and
id|system_state
op_eq
id|SYSTEM_RUNNING
)paren
id|cpu_die
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
id|DECLARE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|smt_snooze_delay
)paren
suffix:semicolon
DECL|function|dedicated_idle
r_int
id|dedicated_idle
c_func
(paren
r_void
)paren
(brace
r_int
id|oldval
suffix:semicolon
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
comma
op_star
id|ppaca
suffix:semicolon
r_int
r_int
id|start_snooze
suffix:semicolon
r_int
r_int
op_star
id|smt_snooze_delay
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|smt_snooze_delay
)paren
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|ppaca
op_assign
op_amp
id|paca
(braket
id|cpu
op_xor
l_int|1
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Indicate to the HV that we are idle. Now would be&n;&t;&t; * a good time to find other work to dispatch.&n;&t;&t; */
id|lpaca-&gt;lppaca.idle
op_assign
l_int|1
suffix:semicolon
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
id|start_snooze
op_assign
id|__get_tb
c_func
(paren
)paren
op_plus
op_star
id|smt_snooze_delay
op_star
id|tb_ticks_per_usec
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Go into low thread priority and possibly&n;&t;&t;&t;&t; * low power mode.&n;&t;&t;&t;&t; */
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
id|HMT_very_low
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|smt_snooze_delay
op_eq
l_int|0
op_logical_or
id|__get_tb
c_func
(paren
)paren
OL
id|start_snooze
)paren
r_continue
suffix:semicolon
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ppaca-&gt;lppaca.idle
)paren
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * We are about to sleep the thread&n;&t;&t;&t;&t;&t; * and so wont be polling any&n;&t;&t;&t;&t;&t; * more.&n;&t;&t;&t;&t;&t; */
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * SMT dynamic mode. Cede will result&n;&t;&t;&t;&t;&t; * in this thread going dormant, if the&n;&t;&t;&t;&t;&t; * partner thread is still doing work.&n;&t;&t;&t;&t;&t; * Thread wakes up if partner goes idle,&n;&t;&t;&t;&t;&t; * an interrupt is presented, or a prod&n;&t;&t;&t;&t;&t; * occurs.  Returning from the cede&n;&t;&t;&t;&t;&t; * enables external interrupts.&n;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|cede_processor
c_func
(paren
)paren
suffix:semicolon
r_else
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Give the HV an opportunity at the&n;&t;&t;&t;&t;&t; * processor, since we are not doing&n;&t;&t;&t;&t;&t; * any work.&n;&t;&t;&t;&t;&t; */
id|poll_pending
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|lpaca-&gt;lppaca.idle
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
op_logical_and
id|system_state
op_eq
id|SYSTEM_RUNNING
)paren
id|cpu_die
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shared_idle
r_static
r_int
id|shared_idle
c_func
(paren
r_void
)paren
(brace
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
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
multiline_comment|/*&n;&t;&t; * Indicate to the HV that we are idle. Now would be&n;&t;&t; * a good time to find other work to dispatch.&n;&t;&t; */
id|lpaca-&gt;lppaca.idle
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Yield the processor to the hypervisor.  We return if&n;&t;&t;&t; * an external interrupt occurs (which are driven prior&n;&t;&t;&t; * to returning here) or if a prod occurs from another &n;&t;&t;&t; * processor. When returning here, external interrupts&n;&t;&t;&t; * are enabled.&n;&t;&t;&t; *&n;&t;&t;&t; * Check need_resched() again with interrupts disabled&n;&t;&t;&t; * to avoid a race.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|cede_processor
c_func
(paren
)paren
suffix:semicolon
r_else
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
id|HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|lpaca-&gt;lppaca.idle
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_logical_and
id|system_state
op_eq
id|SYSTEM_RUNNING
)paren
id|cpu_die
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PSERIES */
DECL|function|native_idle
r_static
r_int
id|native_idle
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* check CPU type here */
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|power4_idle
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_logical_and
id|system_state
op_eq
id|SYSTEM_RUNNING
)paren
id|cpu_die
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_ISERIES */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
id|idle_loop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|powersave_nap
r_int
id|powersave_nap
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
multiline_comment|/*&n; * Register the sysctl to set/clear powersave_nap.&n; */
DECL|variable|powersave_nap_ctl_table
r_static
id|ctl_table
id|powersave_nap_ctl_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|powersave_nap_sysctl_root
r_static
id|ctl_table
id|powersave_nap_sysctl_root
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
l_string|&quot;kernel&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0755
comma
id|powersave_nap_ctl_table
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|register_powersave_nap_sysctl
id|register_powersave_nap_sysctl
c_func
(paren
r_void
)paren
(brace
id|register_sysctl_table
c_func
(paren
id|powersave_nap_sysctl_root
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|register_powersave_nap_sysctl
id|__initcall
c_func
(paren
id|register_powersave_nap_sysctl
)paren
suffix:semicolon
macro_line|#endif
DECL|function|idle_setup
r_int
id|idle_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Move that junk to each platform specific file, eventually define&n;&t; * a pSeries_idle for shared processor stuff&n;&t; */
macro_line|#ifdef CONFIG_PPC_ISERIES
id|idle_loop
op_assign
id|iSeries_idle
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#else
id|idle_loop
op_assign
id|default_idle
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_PSERIES
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_PSERIES
)paren
(brace
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
r_if
c_cond
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|lppaca.shared_proc
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using shared processor idle loop&bslash;n&quot;
)paren
suffix:semicolon
id|idle_loop
op_assign
id|shared_idle
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using dedicated idle loop&bslash;n&quot;
)paren
suffix:semicolon
id|idle_loop
op_assign
id|dedicated_idle
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using default idle loop&bslash;n&quot;
)paren
suffix:semicolon
id|idle_loop
op_assign
id|default_idle
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PPC_PSERIES */
macro_line|#ifndef CONFIG_PPC_ISERIES
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_POWERMAC
op_logical_or
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_MAPLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using native/NAP idle loop&bslash;n&quot;
)paren
suffix:semicolon
id|idle_loop
op_assign
id|native_idle
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_ISERIES */
r_return
l_int|1
suffix:semicolon
)brace
eof
