macro_line|#ifndef _ASM_IA64_TIMEX_H
DECL|macro|_ASM_IA64_TIMEX_H
mdefine_line|#define _ASM_IA64_TIMEX_H
multiline_comment|/*&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; * Copyright (C) 1998-2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * 2001/01/18 davidm&t;Removed CLOCK_TICK_RATE.  It makes no sense on IA-64.&n; *&t;&t;&t;Also removed cacheflush_time as it&squot;s entirely unused.&n; */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
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
