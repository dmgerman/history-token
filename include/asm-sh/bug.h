macro_line|#ifndef __ASM_SH_BUG_H
DECL|macro|__ASM_SH_BUG_H
mdefine_line|#define __ASM_SH_BUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem.&n; */
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;*(volatile int *)0 = 0; &bslash;&n;} while (0)
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
