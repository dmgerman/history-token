multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Idle task for iSeries.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;asm/machdep.h&gt;
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
DECL|function|iSeries_idle
r_void
id|iSeries_idle
c_func
(paren
r_void
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
id|HMT_low
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
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
macro_line|#endif
)brace
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
r_return
suffix:semicolon
)brace
)brace
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
r_static
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
r_static
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The decrementer stops during the yield.  Just force&n;&t;&t; * a fake decrementer now and the timer_interrupt&n;&t;&t; * code will straighten it all out&n;&t;&t; */
id|paca-&gt;xLpPaca.xDecrInt
op_assign
l_int|1
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
eof
