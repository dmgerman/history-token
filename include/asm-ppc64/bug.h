macro_line|#ifndef _PPC64_BUG_H
DECL|macro|_PPC64_BUG_H
mdefine_line|#define _PPC64_BUG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_XMON
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|xmon
c_func
(paren
r_struct
id|pt_regs
op_star
id|excp
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;xmon(0); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;__asm__ __volatile__(&quot;.long &quot; BUG_ILLEGAL_INSTR); &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
macro_line|#endif
eof
