macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar,&n; *&t;&t;Copyright 1999 SuSE GmbH&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
DECL|macro|CPU_IRQ_REGION
mdefine_line|#define CPU_IRQ_REGION&t; 1
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t; (IRQ_FROM_REGION(CPU_IRQ_REGION) | 0)
DECL|macro|IPI_IRQ
mdefine_line|#define&t;IPI_IRQ&t;&t; (IRQ_FROM_REGION(CPU_IRQ_REGION) | 1)
multiline_comment|/* This should be 31 for PA1.1 binaries and 63 for PA-2.0 wide mode) */
DECL|macro|MAX_CPU_IRQ
mdefine_line|#define MAX_CPU_IRQ&t;(BITS_PER_LONG - 1)
macro_line|#if 1    /* set to 1 to get the new irq offsets, or ...   */
macro_line|# if BITS_PER_LONG == 32
DECL|macro|IRQ_REGION_SHIFT
macro_line|#  define IRQ_REGION_SHIFT 5
macro_line|# else
DECL|macro|IRQ_REGION_SHIFT
macro_line|#  define IRQ_REGION_SHIFT 6
macro_line|# endif
macro_line|#else   /* 256 irq-entries per region (wastes memory, maybe gains speed? :-))*/
DECL|macro|IRQ_REGION_SHIFT
macro_line|# define IRQ_REGION_SHIFT 8
macro_line|#endif 
DECL|macro|IRQ_PER_REGION
mdefine_line|#define IRQ_PER_REGION  (1 &lt;&lt; IRQ_REGION_SHIFT)
DECL|macro|NR_IRQ_REGS
mdefine_line|#define NR_IRQ_REGS&t;8
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(NR_IRQ_REGS * IRQ_PER_REGION)
DECL|macro|IRQ_REGION
mdefine_line|#define IRQ_REGION(irq) &t;((irq) &gt;&gt; IRQ_REGION_SHIFT)
DECL|macro|IRQ_OFFSET
mdefine_line|#define IRQ_OFFSET(irq)&t;&t;((irq) &amp; ((1&lt;&lt;IRQ_REGION_SHIFT)-1))
DECL|macro|IRQ_FROM_REGION
mdefine_line|#define&t;IRQ_FROM_REGION(reg)&t;((reg) &lt;&lt; IRQ_REGION_SHIFT)
DECL|macro|IRQ_REG_DIS
mdefine_line|#define IRQ_REG_DIS&t;   1&t;/* support disable_irq / enable_irq */
DECL|macro|IRQ_REG_MASK
mdefine_line|#define IRQ_REG_MASK&t;   2&t;/* require IRQs to be masked */
DECL|struct|irq_region_ops
r_struct
id|irq_region_ops
(brace
DECL|member|disable_irq
r_void
(paren
op_star
id|disable_irq
)paren
(paren
r_void
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|member|enable_irq
r_void
(paren
op_star
id|enable_irq
)paren
(paren
r_void
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|member|mask_irq
r_void
(paren
op_star
id|mask_irq
)paren
(paren
r_void
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|member|unmask_irq
r_void
(paren
op_star
id|unmask_irq
)paren
(paren
r_void
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irq_region_data
r_struct
id|irq_region_data
(brace
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|irqbase
r_int
id|irqbase
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irq_region
r_struct
id|irq_region
(brace
DECL|member|ops
r_struct
id|irq_region_ops
id|ops
suffix:semicolon
DECL|member|data
r_struct
id|irq_region_data
id|data
suffix:semicolon
DECL|member|action
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|irq_region
op_star
id|irq_region
(braket
id|NR_IRQ_REGS
)braket
suffix:semicolon
DECL|function|irq_cannonicalize
r_static
id|__inline__
r_int
id|irq_cannonicalize
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
id|disable_irq
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|do_irq_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_struct
id|irq_region
op_star
id|region
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_struct
id|irq_region
op_star
id|alloc_irq_region
c_func
(paren
r_int
id|count
comma
r_struct
id|irq_region_ops
op_star
id|ops
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|dev
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
macro_line|#endif /* _ASM_IRQ_H */
eof
