macro_line|#ifndef __UM_RWSEM_H__
DECL|macro|__UM_RWSEM_H__
mdefine_line|#define __UM_RWSEM_H__
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96)
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(exp,c) (exp)
macro_line|#endif
macro_line|#include &quot;asm/arch/rwsem.h&quot;
macro_line|#endif
eof
