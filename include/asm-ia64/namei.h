macro_line|#ifndef _ASM_IA64_NAMEI_H
DECL|macro|_ASM_IA64_NAMEI_H
mdefine_line|#define _ASM_IA64_NAMEI_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999, 2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|EMUL_PREFIX_LINUX_IA32
mdefine_line|#define EMUL_PREFIX_LINUX_IA32 &quot;emul/ia32-linux/&quot;
r_static
r_inline
r_char
op_star
DECL|function|__emul_prefix
id|__emul_prefix
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
id|PER_LINUX32
suffix:colon
r_return
id|EMUL_PREFIX_LINUX_IA32
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* _ASM_IA64_NAMEI_H */
eof
