macro_line|#ifndef _PPC_BUG_H
DECL|macro|_PPC_BUG_H
mdefine_line|#define _PPC_BUG_H
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;__asm__ __volatile__(&quot;.long 0x0&quot;); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
macro_line|#endif
eof
