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
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;__bug(__FILE__, __LINE__, page)
macro_line|#else
multiline_comment|/* these just cause an oops */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;(*(int *)0 = 0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;(*(int *)0 = 0)
macro_line|#endif
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
eof
