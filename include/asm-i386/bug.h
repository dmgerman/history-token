macro_line|#ifndef _I386_BUG_H
DECL|macro|_I386_BUG_H
mdefine_line|#define _I386_BUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem.&n; * The offending file and line are encoded after the &quot;officially&n; * undefined&quot; opcode for parsing in the trap handler.&n; */
macro_line|#if 1&t;/* Set to zero for a slightly smaller kernel */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&bslash;&n; __asm__ __volatile__(&t;&quot;ud2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.word %c0&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.long %c1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t; : : &quot;i&quot; (__LINE__), &quot;i&quot; (__FILE__))
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() __asm__ __volatile__(&quot;ud2&bslash;n&quot;)
macro_line|#endif
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
eof
