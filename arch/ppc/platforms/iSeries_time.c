multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Time routes for iSeries LPAR.&n; *&n; * Copyright (C) 2001 IBM Corp.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/iSeries/Paca.h&gt;
DECL|variable|next_jiffy_update_tb
id|u64
id|next_jiffy_update_tb
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|u64
id|get_tb64
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
r_extern
r_char
id|_stext
suffix:semicolon
r_extern
r_int
id|is_soft_enabled
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ppc_do_profile
r_static
r_inline
r_void
id|ppc_do_profile
(paren
r_int
r_int
id|nip
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Only measure the CPUs specified by /proc/irq/prof_cpu_mask.&n;&t; * (default is all CPUs.)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
op_amp
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|nip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|nip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds EIP values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|nip
OG
id|prof_len
op_minus
l_int|1
)paren
id|nip
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|nip
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  * For iSeries shared processors, we have to let the hypervisor&n;  * set the hardware decrementer.  We set a virtual decrementer&n;  * in the ItLpPaca and call the hypervisor if the virtual&n;  * decrementer is less than the current value in the hardware&n;  * decrementer. (almost always the new decrementer value will&n;  * be greater than the current hardware decementer so the hypervisor&n;  * call will not be needed)&n;  *&n;  * When we yield the processor in idle.c (needed for shared processors)&n;  * we cannot yield for too long or the 32-bit tbl may wrap and then&n;  * we would lose jiffies.  In addition, if we yield for too long,&n;  * we might be pretty far off on timing for device drivers and such.&n;  * When the hypervisor returns to us after a yield we need to&n;  * determine whether decrementers might have been missed.  If so&n;  * we need to drive the timer_interrupt code to catch up (using&n;  * the tb)&n;  *&n;  * For processors other than processor 0, there is no correction&n;  * (in the code below) to next_dec so they&squot;re last_jiffy_stamp&n;  * values are going to be way off.&n;  *&n;  */
DECL|variable|timerRetEnabled
r_int
id|timerRetEnabled
op_assign
l_int|0
suffix:semicolon
DECL|variable|timerRetDisabled
r_int
id|timerRetDisabled
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_dec_value
suffix:semicolon
DECL|function|timer_interrupt
r_int
id|timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|next_dec
suffix:semicolon
r_struct
id|Paca
op_star
id|paca
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
id|is_soft_enabled
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;softEnable
)paren
id|timerRetEnabled
op_increment
suffix:semicolon
r_else
id|timerRetDisabled
op_increment
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|ppc_do_profile
c_func
(paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|next_jiffy_update_tb
(braket
id|cpu
)braket
OL
id|get_tb64
c_func
(paren
)paren
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_eq
l_int|0
op_logical_and
id|xtime.tv_sec
op_minus
id|last_rtc_update
op_ge
l_int|659
op_logical_and
id|abs
c_func
(paren
id|xtime.tv_usec
op_minus
(paren
l_int|1000000
op_minus
l_int|1000000
op_div
id|HZ
)paren
)paren
OL
l_int|500000
op_div
id|HZ
op_logical_and
id|jiffies
op_minus
id|wall_jiffies
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|ppc_md
dot
id|set_rtc_time
c_func
(paren
id|xtime.tv_sec
op_plus
l_int|1
op_plus
id|time_offset
)paren
op_eq
l_int|0
)paren
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|1
suffix:semicolon
r_else
multiline_comment|/* Try again one minute later */
id|last_rtc_update
op_add_assign
l_int|60
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
id|next_jiffy_update_tb
(braket
id|cpu
)braket
op_add_assign
id|tb_ticks_per_jiffy
suffix:semicolon
)brace
id|next_dec
op_assign
id|next_jiffy_update_tb
(braket
id|cpu
)braket
op_minus
id|get_tb64
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next_dec
OG
id|paca-&gt;default_decr
)paren
id|next_dec
op_assign
id|paca-&gt;default_decr
suffix:semicolon
id|paca-&gt;xLpPacaPtr-&gt;xDecrInt
op_assign
l_int|0
suffix:semicolon
id|set_dec
c_func
(paren
(paren
r_int
)paren
id|next_dec
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
