macro_line|#ifndef _S390_BUG_H
DECL|macro|_S390_BUG_H
mdefine_line|#define _S390_BUG_H
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;        printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;        __asm__ __volatile__(&quot;.long 0&quot;); &bslash;&n;} while (0)
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
