macro_line|#ifndef __ASM_SH64_TIMEX_H
DECL|macro|__ASM_SH64_TIMEX_H
mdefine_line|#define __ASM_SH64_TIMEX_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/timex.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * sh-5 architecture timex specifications&n; *&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|function|get_cycles
r_static
id|__inline__
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|vxtime_lock
mdefine_line|#define vxtime_lock()&t;&t;do {} while (0)
DECL|macro|vxtime_unlock
mdefine_line|#define vxtime_unlock()&t;&t;do {} while (0)
macro_line|#endif /* __ASM_SH64_TIMEX_H */
eof
