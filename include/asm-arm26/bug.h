macro_line|#ifndef _ASMARM_BUG_H
DECL|macro|_ASMARM_BUG_H
mdefine_line|#define _ASMARM_BUG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
r_extern
r_volatile
r_void
id|__bug
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* give file/line information */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;__bug(__FILE__, __LINE__, NULL)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;(*(int *)0 = 0)
macro_line|#endif
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
