macro_line|#ifndef _ASM_IA64_BUG_H
DECL|macro|_ASM_IA64_BUG_H
mdefine_line|#define _ASM_IA64_BUG_H
macro_line|#if (__GNUC__ &gt; 3) || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 1)
DECL|macro|ia64_abort
macro_line|# define ia64_abort()&t;__builtin_trap()
macro_line|#else
DECL|macro|ia64_abort
macro_line|# define ia64_abort()&t;(*(volatile int *) 0 = 0)
macro_line|#endif
DECL|macro|BUG
mdefine_line|#define BUG() do { printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); ia64_abort(); } while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
macro_line|#endif
eof
