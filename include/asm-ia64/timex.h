macro_line|#ifndef _ASM_IA64_TIMEX_H
DECL|macro|_ASM_IA64_TIMEX_H
mdefine_line|#define _ASM_IA64_TIMEX_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193180&t;/* Underlying HZ XXX fix me! */
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
