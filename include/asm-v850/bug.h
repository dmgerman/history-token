multiline_comment|/*&n; * include/asm-v850/bug.h -- Bug reporting&n; *&n; *  Copyright (C) 2003  NEC Electronics Corporation&n; *  Copyright (C) 2003  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_BUG_H__
DECL|macro|__V850_BUG_H__
mdefine_line|#define __V850_BUG_H__
r_extern
r_void
id|__bug
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;__bug()
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;__bug()
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif /* __V850_BUG_H__ */
eof
