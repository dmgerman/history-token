macro_line|#ifndef __ASM_BUG_H
DECL|macro|__ASM_BUG_H
mdefine_line|#define __ASM_BUG_H
macro_line|#include &lt;asm/break.h&gt;
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;break %0&quot; : : &quot;i&quot; (BRK_BUG));&t;&t;&bslash;&n;} while (0)
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
