multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Idle daemon for PowerPC.  Idle daemon will handle any action&n; * that needs to be taken when the system becomes idle.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
r_static
r_void
id|yield_shared_processor
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|run_light_on
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_extern
r_int
r_int
id|yield_count
suffix:semicolon
macro_line|#else /* CONFIG_PPC_ISERIES */
DECL|macro|run_light_on
mdefine_line|#define run_light_on(x)         do { } while (0)
macro_line|#endif /* CONFIG_PPC_ISERIES */
r_void
id|power_save
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|zero_paged_on
r_int
r_int
id|zero_paged_on
suffix:semicolon
DECL|variable|powersave_nap
r_int
r_int
id|powersave_nap
suffix:semicolon
DECL|function|idled
r_int
id|idled
c_func
(paren
r_void
)paren
(brace
r_int
id|do_power_save
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_CAN_DOZE
)paren
id|do_power_save
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* endless loop with no priority at all */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
macro_line|#ifdef CONFIG_PPC_ISERIES
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
(brace
multiline_comment|/* Turn off the run light */
id|run_light_on
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|yield_shared_processor
c_func
(paren
)paren
suffix:semicolon
)brace
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|do_power_save
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
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
id|test_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
)paren
id|barrier
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
)brace
macro_line|#endif
r_if
c_cond
(paren
id|do_power_save
op_logical_and
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|power_save
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
(brace
id|run_light_on
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_ISERIES
r_else
(brace
id|run_light_on
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|yield_shared_processor
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
macro_line|#endif /* CONFIG_PPC_ISERIES */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP entry into the idle task - calls the same thing as the&n; * non-smp versions. -- Cort&n; */
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
id|idled
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|power_save
r_void
id|power_save
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid0
suffix:semicolon
r_int
id|nap
op_assign
id|powersave_nap
suffix:semicolon
multiline_comment|/* 7450 has no DOZE mode mode, we return if powersave_nap&n;&t; * isn&squot;t enabled&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nap
op_logical_and
id|cur_cpu_spec
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_SPEC7450
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Disable interrupts to prevent a lost wakeup&n;&t; * when going to sleep.  This is necessary even with&n;&t; * RTLinux since we are not guaranteed an interrupt&n;&t; * didn&squot;t come in and is waiting for a __sti() before&n;&t; * emulating one.  This way, we really do hard disable.&n;&t; * &n;&t; * We assume that we&squot;re sti-ed when we come in here.  We&n;&t; * are in the idle loop so if we&squot;re cli-ed then it&squot;s a bug&n;&t; * anyway.&n;&t; *  -- Cort&n;&t; */
id|_nmask_and_or_msr
c_func
(paren
id|MSR_EE
comma
l_int|0
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
(brace
id|asm
c_func
(paren
l_string|&quot;mfspr %0,1008&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|hid0
)paren
suffix:colon
)paren
suffix:semicolon
id|hid0
op_and_assign
op_complement
(paren
id|HID0_NAP
op_or
id|HID0_SLEEP
op_or
id|HID0_DOZE
)paren
suffix:semicolon
id|hid0
op_or_assign
(paren
id|powersave_nap
ques
c_cond
id|HID0_NAP
suffix:colon
id|HID0_DOZE
)paren
op_or
id|HID0_DPM
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mtspr 1008,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|hid0
)paren
)paren
suffix:semicolon
multiline_comment|/* set the POW bit in the MSR, and enable interrupts&n;&t;&t; * so we wake up sometime! */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_POW
op_or
id|MSR_EE
)paren
suffix:semicolon
)brace
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_EE
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_ISERIES
r_extern
r_void
id|fake_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u64
id|get_tb64
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|run_light_on
r_void
id|run_light_on
c_func
(paren
r_int
id|on
)paren
(brace
r_int
r_int
id|CTRL
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
op_assign
id|on
ques
c_cond
(paren
id|CTRL
op_or
id|RUNLATCH
)paren
suffix:colon
(paren
id|CTRL
op_amp
op_complement
id|RUNLATCH
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|CTRLT
comma
id|CTRL
)paren
suffix:semicolon
)brace
DECL|function|yield_shared_processor
r_void
id|yield_shared_processor
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
id|u64
id|tb
suffix:semicolon
multiline_comment|/* Poll for I/O events */
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|paca
op_assign
(paren
r_struct
id|Paca
op_star
)paren
id|mfspr
c_func
(paren
id|SPRG1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|paca-&gt;xLpPaca.xSharedProc
)paren
(brace
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
multiline_comment|/*&n;&t;&t; * Check here for any of the above pending...&n;&t;&t; * IPI and Decrementers are indicated in ItLpPaca&n;&t;&t; * LpEvents are indicated on the LpQueue&n;&t;&t; *&n;&t;&t; * Disabling/enabling will check for LpEvents, IPIs&n;&t;&t; * and decrementers&n;&t;&t; */
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
op_increment
id|yield_count
suffix:semicolon
multiline_comment|/* Get current tb value */
id|tb
op_assign
id|get_tb64
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Compute future tb value when yield will expire */
id|tb
op_add_assign
id|tb_ticks_per_jiffy
suffix:semicolon
id|HvCall_yieldProcessor
c_func
(paren
id|HvCall_YieldTimed
comma
id|tb
)paren
suffix:semicolon
multiline_comment|/* Check here for any of the above pending or timeout expired*/
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The decrementer stops during the yield.  Just force&n;&t;&t; * a fake decrementer now and the timer_interrupt&n;&t;&t; * code will straighten it all out&n;&t;&t; */
id|paca-&gt;xLpPaca.xDecrInt
op_assign
l_int|1
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PPC_ISERIES */
eof
