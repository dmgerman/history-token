macro_line|#ifndef _ASM_BUG_H
DECL|macro|_ASM_BUG_H
mdefine_line|#define _ASM_BUG_H
DECL|macro|BUG
mdefine_line|#define BUG() do { printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); *(int *)0=0; } while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do {  BUG(); } while (0)
macro_line|#endif
eof
