multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999, 2003 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_TIMEX_H
DECL|macro|_ASM_TIMEX_H
mdefine_line|#define _ASM_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * This is the frequency of the timer used for Linux&squot;s timer interrupt.&n; * The value should be defined as accurate as possible or under certain&n; * circumstances Linux timekeeping might become inaccurate or fail.&n; *&n; * For IP22 we cheat and pretend to have a 1MHz timer whic isn&squot;t strictly&n; * true - we only use the 8259 timer to calibrate the actual interrupt&n; * timer, so after all it&squot;s the master clock source of the system.&n; *&n; * The obscure number 1193182 is the same as used by the original i8254&n; * time in legacy PC hardware; the chip unfortunately also found in a&n; * bunch of MIPS systems.&n; */
macro_line|#ifdef CONFIG_ACER_PICA_61
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193182
macro_line|#elif defined(CONFIG_MIPS_MAGNUM_4000)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193182
macro_line|#elif defined(CONFIG_OLIVETTI_M700)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193182
macro_line|#elif defined(CONFIG_SGI_IP22)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1000000
macro_line|#elif defined(CONFIG_SNI_RM200_PCI)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193182
macro_line|#endif
multiline_comment|/*&n; * Standard way to access the cycle counter.&n; * Currently only used on SMP for scheduling.&n; *&n; * Only the low 32 bits are available as a continuously counting entity.&n; * But this only means we&squot;ll force a reschedule every 8 seconds or so,&n; * which isn&squot;t an evil thing.&n; *&n; * We know that all SMP capable CPUs have cycle counters.&n; */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /*  _ASM_TIMEX_H */
eof
