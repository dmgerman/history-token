multiline_comment|/* $Id$ */
macro_line|#ifndef _SPARC_BUG_H
DECL|macro|_SPARC_BUG_H
mdefine_line|#define _SPARC_BUG_H
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
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) &bslash;&n;&t;&t;BUG(); &bslash;&n;} while(0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
eof
