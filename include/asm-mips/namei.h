macro_line|#ifndef _ASM_NAMEI_H
DECL|macro|_ASM_NAMEI_H
mdefine_line|#define _ASM_NAMEI_H
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
DECL|macro|IRIX_EMUL
mdefine_line|#define IRIX_EMUL&t;&quot;/usr/gnemul/irix/&quot;
DECL|macro|RISCOS_EMUL
mdefine_line|#define RISCOS_EMUL&t;&quot;/usr/gnemul/riscos/&quot;
DECL|function|__emul_prefix
r_static
r_inline
r_char
op_star
id|__emul_prefix
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|current-&gt;personality
)paren
(brace
r_case
id|PER_IRIX32
suffix:colon
r_case
id|PER_IRIXN32
suffix:colon
r_case
id|PER_IRIX64
suffix:colon
r_return
id|IRIX_EMUL
suffix:semicolon
r_case
id|PER_RISCOS
suffix:colon
r_return
id|RISCOS_EMUL
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* _ASM_NAMEI_H */
eof
