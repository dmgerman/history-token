multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999, 2003 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_TIMEX_H
DECL|macro|_ASM_TIMEX_H
mdefine_line|#define _ASM_TIMEX_H
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * This is the frequency of the timer used for Linux&squot;s timer interrupt.&n; * The value should be defined as accurate as possible or under certain&n; * circumstances Linux timekeeping might become inaccurate or fail.&n; *&n; * For many system the exact clockrate of the timer isn&squot;t known but due to&n; * the way this value is used we can get away with a wrong value as long&n; * as this value is:&n; *&n; *  - a multiple of HZ&n; *  - a divisor of the actual rate&n; *&n; * 500000 is a good such cheat value.&n; *&n; * The obscure number 1193182 is the same as used by the original i8254&n; * time in legacy PC hardware; the chip unfortunately also found in a&n; * bunch of MIPS systems.  The last remaining user of the i8254 for the&n; * timer interrupt is the RM200; it&squot;s a very standard system so there is&n; * no reason to make this a separate architecture.&n; */
macro_line|#include &lt;timex.h&gt;
multiline_comment|/*&n; * Standard way to access the cycle counter.&n; * Currently only used on SMP for scheduling.&n; *&n; * Only the low 32 bits are available as a continuously counting entity.&n; * But this only means we&squot;ll force a reschedule every 8 seconds or so,&n; * which isn&squot;t an evil thing.&n; *&n; * We know that all SMP capable CPUs have cycle counters.&n; */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
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
