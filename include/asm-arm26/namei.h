multiline_comment|/* &n; * linux/include/asm-arm/namei.h&n; *&n; * Routines to handle famous /usr/gnemul&n; * Derived from the Sparc version of this file&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __ASMARM_NAMEI_H
DECL|macro|__ASMARM_NAMEI_H
mdefine_line|#define __ASMARM_NAMEI_H
DECL|macro|ARM_BSD_EMUL
mdefine_line|#define ARM_BSD_EMUL &quot;usr/gnemul/bsd/&quot;
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
id|PER_BSD
suffix:colon
r_return
id|ARM_BSD_EMUL
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* __ASMARM_NAMEI_H */
eof
