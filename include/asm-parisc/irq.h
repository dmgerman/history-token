multiline_comment|/*&n; * include/asm-parisc/irq.h&n; *&n; * Copyright 2005 Matthew Wilcox &lt;matthew@wil.cx&gt;&n; */
macro_line|#ifndef _ASM_PARISC_IRQ_H
DECL|macro|_ASM_PARISC_IRQ_H
mdefine_line|#define _ASM_PARISC_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;&t;(-1)
macro_line|#ifdef CONFIG_GSC
DECL|macro|GSC_IRQ_BASE
mdefine_line|#define GSC_IRQ_BASE&t;16
DECL|macro|GSC_IRQ_MAX
mdefine_line|#define GSC_IRQ_MAX&t;63
DECL|macro|CPU_IRQ_BASE
mdefine_line|#define CPU_IRQ_BASE&t;64
macro_line|#else
DECL|macro|CPU_IRQ_BASE
mdefine_line|#define CPU_IRQ_BASE&t;16
macro_line|#endif
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;(CPU_IRQ_BASE + 0)
DECL|macro|IPI_IRQ
mdefine_line|#define&t;IPI_IRQ&t;&t;(CPU_IRQ_BASE + 1)
DECL|macro|CPU_IRQ_MAX
mdefine_line|#define CPU_IRQ_MAX&t;(CPU_IRQ_BASE + (BITS_PER_LONG - 1))
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(CPU_IRQ_MAX + 1)
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
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
suffix:semicolon
)brace
r_struct
id|hw_interrupt_type
suffix:semicolon
multiline_comment|/*&n; * Some useful &quot;we don&squot;t have to do anything here&quot; handlers.  Should&n; * probably be provided by the generic code.&n; */
r_void
id|no_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_void
id|no_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|txn_alloc_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|txn_claim_irq
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|txn_alloc_data
c_func
(paren
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|txn_alloc_addr
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cpu_claim_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|hw_interrupt_type
op_star
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* soft power switch support (power.c) */
r_extern
r_struct
id|tasklet_struct
id|power_tasklet
suffix:semicolon
macro_line|#endif&t;/* _ASM_PARISC_IRQ_H */
eof
