macro_line|#ifndef _ASM_IA64_TIMEX_H
DECL|macro|_ASM_IA64_TIMEX_H
mdefine_line|#define _ASM_IA64_TIMEX_H
multiline_comment|/*&n; * Copyright (C) 1998-2001, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * 2001/01/18 davidm&t;Removed CLOCK_TICK_RATE.  It makes no sense on IA-64.&n; *&t;&t;&t;Also removed cacheflush_time as it&squot;s entirely unused.&n; */
macro_line|#include &lt;asm/processor.h&gt;
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
multiline_comment|/*&n; * For performance reasons, we don&squot;t want to define CLOCK_TICK_TRATE as&n; * local_cpu_data-&gt;itc_rate.  Fortunately, we don&squot;t have to, either: according to George&n; * Anzinger, 1/CLOCK_TICK_RATE is taken as the resolution of the timer clock.  The time&n; * calculation assumes that you will use enough of these so that your tick size &lt;= 1/HZ.&n; * If the calculation shows that your CLOCK_TICK_RATE can not supply exactly 1/HZ ticks,&n; * the actual value is calculated and used to update the wall clock each jiffie.  Setting&n; * the CLOCK_TICK_RATE to x*HZ insures that the calculation will find no errors.  Hence we&n; * pick a multiple of HZ which gives us a (totally virtual) CLOCK_TICK_RATE of about&n; * 100MHz.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(HZ * 100000UL)
r_static
r_inline
id|cycles_t
DECL|function|get_cycles
id|get_cycles
(paren
r_void
)paren
(brace
id|cycles_t
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov %0=ar.itc&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_TIMEX_H */
eof
