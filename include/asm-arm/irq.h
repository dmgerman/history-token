macro_line|#ifndef __ASM_ARM_IRQ_H
DECL|macro|__ASM_ARM_IRQ_H
mdefine_line|#define __ASM_ARM_IRQ_H
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#ifndef irq_cannonicalize
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
macro_line|#endif
macro_line|#ifndef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;128
macro_line|#endif
multiline_comment|/*&n; * Use this value to indicate lack of interrupt&n; * capability&n; */
macro_line|#ifndef NO_IRQ
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;((unsigned int)(-1))
macro_line|#endif
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync(i) disable_irq(i)
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
