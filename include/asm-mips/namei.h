multiline_comment|/*&n; * linux/include/asm-mips/namei.h&n; *&n; * Included from linux/fs/namei.c&n; *&n; * $Id: namei.h,v 1.6 1999/01/04 16:09:23 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_NAMEI_H
DECL|macro|__ASM_MIPS_NAMEI_H
mdefine_line|#define __ASM_MIPS_NAMEI_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Only one at this time. */
DECL|macro|IRIX32_EMUL
mdefine_line|#define IRIX32_EMUL &quot;usr/gnemul/irix/&quot;
macro_line|#ifdef CONFIG_BINFMT_IRIX
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
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_IRIX32
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|IRIX32_EMUL
suffix:semicolon
)brace
macro_line|#else /* !defined(CONFIG_BINFMT_IRIX) */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif /* !defined(CONFIG_BINFMT_IRIX) */
macro_line|#endif /* __ASM_MIPS_NAMEI_H */
eof
