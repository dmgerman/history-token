macro_line|#ifndef _ASM_GENERIC_BUG_H
DECL|macro|_ASM_GENERIC_BUG_H
mdefine_line|#define _ASM_GENERIC_BUG_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef HAVE_ARCH_BUG
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;panic(&quot;BUG!&quot;); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#ifndef HAVE_ARCH_PAGE_BUG
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;printk(&quot;page BUG for page at %p&bslash;n&quot;, page); &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#ifndef HAVE_ARCH_BUG_ON
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
macro_line|#endif
macro_line|#ifndef HAVE_ARCH_WARN_ON
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif
eof
