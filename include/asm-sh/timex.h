multiline_comment|/*&n; * linux/include/asm-sh/timex.h&n; *&n; * sh architecture timex specifications&n; */
macro_line|#ifndef __ASM_SH_TIMEX_H
DECL|macro|__ASM_SH_TIMEX_H
mdefine_line|#define __ASM_SH_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(CONFIG_SH_PCLK_FREQ / 4) /* Underlying HZ */
DECL|typedef|cycles_t
r_typedef
r_int
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
macro_line|#endif /* __ASM_SH_TIMEX_H */
eof
