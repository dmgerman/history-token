macro_line|#ifndef __ASM_BUG_H
DECL|macro|__ASM_BUG_H
mdefine_line|#define __ASM_BUG_H
macro_line|#include &lt;asm/break.h&gt;
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__);&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;break %0&quot; : : &quot;i&quot; (BRK_BUG));&t;&t;&bslash;&n;} while (0)
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do {  BUG(); } while (0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
eof
