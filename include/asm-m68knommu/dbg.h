DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
macro_line|#ifdef CONFIG_COLDFIRE
DECL|macro|BREAK
mdefine_line|#define&t;BREAK asm volatile (&quot;halt&quot;)
macro_line|#else
DECL|macro|BREAK
mdefine_line|#define BREAK *(volatile unsigned char *)0xdeadbee0 = 0
macro_line|#endif
eof
