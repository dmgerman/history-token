macro_line|#ifndef _M68K_BUG_H
DECL|macro|_M68K_BUG_H
mdefine_line|#define _M68K_BUG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
macro_line|#ifndef CONFIG_SUN3
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;asm volatile(&quot;illegal&quot;); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;panic(&quot;BUG!&quot;); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;asm volatile(&quot;illegal&quot;); &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif
eof
