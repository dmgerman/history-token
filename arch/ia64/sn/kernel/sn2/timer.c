multiline_comment|/*&n; * linux/arch/ia64/sn/kernel/sn2/timer.c&n; *&n; * Copyright (C) 2003 Silicon Graphics, Inc.&n; * Copyright (C) 2003 Hewlett-Packard Co&n; *&t;David Mosberger &lt;davidm@hpl.hp.com&gt;: updated for new timer-interpolation infrastructure&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;shub.h&quot;
macro_line|#include &lt;asm/sn/leds.h&gt;
macro_line|#include &lt;asm/sn/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/clksupport.h&gt;
r_extern
r_int
r_int
id|sn_rtc_cycles_per_second
suffix:semicolon
DECL|variable|sn2_interpolator
r_static
r_struct
id|time_interpolator
id|sn2_interpolator
op_assign
(brace
dot
id|drift
op_assign
op_minus
l_int|1
comma
dot
id|shift
op_assign
l_int|10
comma
dot
id|mask
op_assign
(paren
l_int|1LL
op_lshift
l_int|55
)paren
op_minus
l_int|1
comma
dot
id|source
op_assign
id|TIME_SOURCE_MMIO64
)brace
suffix:semicolon
DECL|function|sn_timer_init
r_void
id|__init
id|sn_timer_init
c_func
(paren
r_void
)paren
(brace
id|sn2_interpolator.frequency
op_assign
id|sn_rtc_cycles_per_second
suffix:semicolon
id|sn2_interpolator.addr
op_assign
id|RTC_COUNTER_ADDR
suffix:semicolon
id|register_time_interpolator
c_func
(paren
op_amp
id|sn2_interpolator
)paren
suffix:semicolon
)brace
eof
