multiline_comment|/* $Id: timex.h,v 1.1 1998/08/25 09:22:03 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999 by Ralf Baechle&n; *&n; * FIXME: For some of the supported machines this is dead wrong.&n; */
macro_line|#ifndef __ASM_MIPS_TIMEX_H
DECL|macro|__ASM_MIPS_TIMEX_H
mdefine_line|#define __ASM_MIPS_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Standard way to access the cycle counter.&n; * Currently only used on SMP for scheduling.&n; *&n; * Only the low 32 bits are available as a continuously counting entity. &n; * But this only means we&squot;ll force a reschedule every 8 seconds or so,&n; * which isn&squot;t an evil thing.&n; *&n; * We know that all SMP capable CPUs have cycle counters.&n; */
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
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /*  __ASM_MIPS_TIMEX_H */
eof
