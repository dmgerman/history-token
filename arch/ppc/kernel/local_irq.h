multiline_comment|/*&n; * BK Id: SCCS/s.local_irq.h 1.7 05/17/01 18:14:21 cort&n; */
macro_line|#ifndef _PPC_KERNEL_LOCAL_IRQ_H
DECL|macro|_PPC_KERNEL_LOCAL_IRQ_H
mdefine_line|#define _PPC_KERNEL_LOCAL_IRQ_H
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|NR_MASK_WORDS
mdefine_line|#define NR_MASK_WORDS&t;((NR_IRQS + 31) / 32)
r_extern
r_int
id|ppc_spurious_interrupts
suffix:semicolon
r_extern
r_int
id|ppc_second_irq
suffix:semicolon
r_extern
r_struct
id|irqaction
op_star
id|ppc_irq_action
(braket
id|NR_IRQS
)braket
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_LOCAL_IRQ_H */
eof
