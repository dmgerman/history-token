multiline_comment|/* timex.h: FR-V architecture timex specifications&n; */
macro_line|#ifndef _ASM_TIMEX_H
DECL|macro|_ASM_TIMEX_H
mdefine_line|#define _ASM_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) *&t;&t;&t;&bslash;&n;   (1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR))&t;&bslash;&n;  &lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
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
c_func
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
macro_line|#endif
eof
