macro_line|#ifndef _CRIS_ARCH_DELAY_H
DECL|macro|_CRIS_ARCH_DELAY_H
mdefine_line|#define _CRIS_ARCH_DELAY_H
DECL|function|__delay
r_extern
id|__inline__
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;move.d %0,$r9&bslash;n&bslash;t&quot;
l_string|&quot;beq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subq 1,$r9&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;subq 1,$r9&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;r9&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(_CRIS_ARCH_DELAY_H) */
eof
