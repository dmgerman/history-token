macro_line|#ifndef _ASMARM_BUG_H
DECL|macro|_ASMARM_BUG_H
mdefine_line|#define _ASMARM_BUG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
r_extern
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
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;__bug(__FILE__, __LINE__, page)
macro_line|#else
multiline_comment|/* these just cause an oops */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;(*(int *)0 = 0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;(*(int *)0 = 0)
macro_line|#endif
macro_line|#endif
eof
