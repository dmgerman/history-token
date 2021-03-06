macro_line|#ifndef __ASM_SH64_BUG_H
DECL|macro|__ASM_SH64_BUG_H
mdefine_line|#define __ASM_SH64_BUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem, then force a segfault (in process&n; * context) or a panic (interrupt context).&n; */
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;*(volatile int *)0 = 0; &bslash;&n;} while (0)
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) &bslash;&n;&t;&t;BUG(); &bslash;&n;} while(0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif /* __ASM_SH64_BUG_H */
eof
