macro_line|#ifndef _H8300_IRQ_H_
DECL|macro|_H8300_IRQ_H_
mdefine_line|#define _H8300_IRQ_H_
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#if defined(__H8300H__)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 64
DECL|macro|EXT_IRQ0
mdefine_line|#define EXT_IRQ0 12
DECL|macro|EXT_IRQ1
mdefine_line|#define EXT_IRQ1 13
DECL|macro|EXT_IRQ2
mdefine_line|#define EXT_IRQ2 14
DECL|macro|EXT_IRQ3
mdefine_line|#define EXT_IRQ3 15
DECL|macro|EXT_IRQ4
mdefine_line|#define EXT_IRQ4 16
DECL|macro|EXT_IRQ5
mdefine_line|#define EXT_IRQ5 17
DECL|macro|EXT_IRQ6
mdefine_line|#define EXT_IRQ6 18
DECL|macro|EXT_IRQ7
mdefine_line|#define EXT_IRQ7 19
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_H8S)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 128
DECL|macro|EXT_IRQ0
mdefine_line|#define EXT_IRQ0 16
DECL|macro|EXT_IRQ1
mdefine_line|#define EXT_IRQ1 17
DECL|macro|EXT_IRQ2
mdefine_line|#define EXT_IRQ2 18
DECL|macro|EXT_IRQ3
mdefine_line|#define EXT_IRQ3 19
DECL|macro|EXT_IRQ4
mdefine_line|#define EXT_IRQ4 20
DECL|macro|EXT_IRQ5
mdefine_line|#define EXT_IRQ5 21
DECL|macro|EXT_IRQ6
mdefine_line|#define EXT_IRQ6 22
DECL|macro|EXT_IRQ7
mdefine_line|#define EXT_IRQ7 23
DECL|macro|EXT_IRQ8
mdefine_line|#define EXT_IRQ8 24
DECL|macro|EXT_IRQ9
mdefine_line|#define EXT_IRQ9 25
DECL|macro|EXT_IRQ10
mdefine_line|#define EXT_IRQ10 26
DECL|macro|EXT_IRQ11
mdefine_line|#define EXT_IRQ11 27
DECL|macro|EXT_IRQ12
mdefine_line|#define EXT_IRQ12 28
DECL|macro|EXT_IRQ13
mdefine_line|#define EXT_IRQ13 29
DECL|macro|EXT_IRQ14
mdefine_line|#define EXT_IRQ14 30
DECL|macro|EXT_IRQ15
mdefine_line|#define EXT_IRQ15 31
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
