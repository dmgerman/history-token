macro_line|#ifndef _PARISC_BUG_H
DECL|macro|_PARISC_BUG_H
mdefine_line|#define _PARISC_BUG_H
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;dump_stack(); &bslash;&n;&t;panic(&quot;BUG!&quot;); &bslash;&n;} while (0)
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
