macro_line|#ifndef _I386_BUG_H
DECL|macro|_I386_BUG_H
mdefine_line|#define _I386_BUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem.&n; * The offending file and line are encoded after the &quot;officially&n; * undefined&quot; opcode for parsing in the trap handler.&n; */
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&bslash;&n; __asm__ __volatile__(&t;&quot;ud2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.word %c0&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.long %c1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t; : : &quot;i&quot; (__LINE__), &quot;i&quot; (__FILE__))
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() __asm__ __volatile__(&quot;ud2&bslash;n&quot;)
macro_line|#endif
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
