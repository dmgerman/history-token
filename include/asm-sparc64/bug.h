multiline_comment|/* $Id$ */
macro_line|#ifndef _SPARC64_BUG_H
DECL|macro|_SPARC64_BUG_H
mdefine_line|#define _SPARC64_BUG_H
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
r_extern
r_void
id|do_BUG
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() do {&t;&t;&t;&t;&t;&bslash;&n;&t;do_BUG(__FILE__, __LINE__);&t;&t;&t;&bslash;&n;&t;__builtin_trap();&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;__builtin_trap()
macro_line|#endif
macro_line|#endif
eof
