macro_line|#ifndef _H8300_IRQ_H_
DECL|macro|_H8300_IRQ_H_
mdefine_line|#define _H8300_IRQ_H_
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#if defined(CONFIG_CPU_H8300H)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 64
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_H8S)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 128
macro_line|#endif
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Some drivers want these entry points&n; */
DECL|macro|enable_irq_nosync
mdefine_line|#define enable_irq_nosync(x)&t;enable_irq(x)
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync(x)&t;disable_irq(x)
macro_line|#endif /* _H8300_IRQ_H_ */
eof
