multiline_comment|/*&n; * include/asm-v850/gbus_int.h -- Midas labs GBUS interrupt support&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_GBUS_INT_H__
DECL|macro|__V850_GBUS_INT_H__
mdefine_line|#define __V850_GBUS_INT_H__
multiline_comment|/* The GBUS interrupt interface has 32 interrupts shared among 4&n;   processor interrupts.  The 32 GBUS interrupts are divided into two&n;   sets of 16 each, for allocating among control registers, etc (there&n;   are two of each control register, with bits 0-15 controlling an&n;   interrupt each).  */
multiline_comment|/* The GBUS interrupts themselves.  */
DECL|macro|IRQ_GBUS_INT
mdefine_line|#define IRQ_GBUS_INT(n)&t;&t;(GBUS_INT_BASE_IRQ + (n))
DECL|macro|IRQ_GBUS_INT_NUM
mdefine_line|#define IRQ_GBUS_INT_NUM&t;32
multiline_comment|/* Control registers.  */
DECL|macro|GBUS_INT_STATUS_ADDR
mdefine_line|#define GBUS_INT_STATUS_ADDR(w)&t;(GBUS_INT_BASE_ADDR + (w)*0x40)
DECL|macro|GBUS_INT_STATUS
mdefine_line|#define GBUS_INT_STATUS(w)&t;(*(volatile u16 *)GBUS_INT_STATUS_ADDR(w))
DECL|macro|GBUS_INT_CLEAR_ADDR
mdefine_line|#define GBUS_INT_CLEAR_ADDR(w)&t;(GBUS_INT_BASE_ADDR + 0x10 + (w)*0x40)
DECL|macro|GBUS_INT_CLEAR
mdefine_line|#define GBUS_INT_CLEAR(w)&t;(*(volatile u16 *)GBUS_INT_CLEAR_ADDR(w))
DECL|macro|GBUS_INT_EDGE_ADDR
mdefine_line|#define GBUS_INT_EDGE_ADDR(w)&t;(GBUS_INT_BASE_ADDR + 0x20 + (w)*0x40)
DECL|macro|GBUS_INT_EDGE
mdefine_line|#define GBUS_INT_EDGE(w)&t;(*(volatile u16 *)GBUS_INT_EDGE_ADDR(w))
DECL|macro|GBUS_INT_POLARITY_ADDR
mdefine_line|#define GBUS_INT_POLARITY_ADDR(w)&t;(GBUS_INT_BASE_ADDR + 0x30 + (w)*0x40)
DECL|macro|GBUS_INT_POLARITY
mdefine_line|#define GBUS_INT_POLARITY(w)&t;(*(volatile u16 *)GBUS_INT_POLARITY_ADDR(w))
multiline_comment|/* This allows enabling interrupt bits in word W for interrupt GINTn.  */
DECL|macro|GBUS_INT_ENABLE_ADDR
mdefine_line|#define GBUS_INT_ENABLE_ADDR(w, n) &bslash;&n;   (GBUS_INT_BASE_ADDR + 0x100 + (w)*0x10 + (n)*0x20)
DECL|macro|GBUS_INT_ENABLE
mdefine_line|#define GBUS_INT_ENABLE(w, n)&t;(*(volatile u16 *)GBUS_INT_ENABLE_ADDR(w, n))
multiline_comment|/* Mapping between kernel interrupt numbers and hardware control regs/bits.  */
DECL|macro|GBUS_INT_BITS_PER_WORD
mdefine_line|#define GBUS_INT_BITS_PER_WORD&t;16
DECL|macro|GBUS_INT_NUM_WORDS
mdefine_line|#define GBUS_INT_NUM_WORDS&t;(IRQ_GBUS_INT_NUM / GBUS_INT_BITS_PER_WORD)
DECL|macro|GBUS_INT_IRQ_WORD
mdefine_line|#define GBUS_INT_IRQ_WORD(irq)&t;(((irq) - GBUS_INT_BASE_IRQ) &gt;&gt; 4)
DECL|macro|GBUS_INT_IRQ_BIT
mdefine_line|#define GBUS_INT_IRQ_BIT(irq)&t;(((irq) - GBUS_INT_BASE_IRQ) &amp; 0xF)
DECL|macro|GBUS_INT_IRQ_MASK
mdefine_line|#define GBUS_INT_IRQ_MASK(irq)&t;(1 &lt;&lt; GBUS_INT_IRQ_BIT(irq))
multiline_comment|/* Possible priorities for GBUS interrupts.  */
DECL|macro|GBUS_INT_PRIORITY_HIGH
mdefine_line|#define GBUS_INT_PRIORITY_HIGH&t;&t;2
DECL|macro|GBUS_INT_PRIORITY_MEDIUM
mdefine_line|#define GBUS_INT_PRIORITY_MEDIUM&t;4
DECL|macro|GBUS_INT_PRIORITY_LOW
mdefine_line|#define GBUS_INT_PRIORITY_LOW&t;&t;6
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Enable interrupt handling for interrupt IRQ.  */
r_extern
r_void
id|gbus_int_enable_irq
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Disable interrupt handling for interrupt IRQ.  Note that any&n;   interrupts received while disabled will be delivered once the&n;   interrupt is enabled again, unless they are explicitly cleared using&n;   `gbus_int_clear_pending_irq&squot;.  */
r_extern
r_void
id|gbus_int_disable_irq
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Return true if interrupt handling for interrupt IRQ is enabled.  */
r_extern
r_int
id|gbus_int_irq_enabled
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Disable all GBUS irqs.  */
r_extern
r_int
id|gbus_int_disable_irqs
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Clear any pending interrupts for IRQ.  */
r_extern
r_void
id|gbus_int_clear_pending_irq
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Return true if interrupt IRQ is pending (but disabled).  */
r_extern
r_int
id|gbus_int_irq_pending
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|struct|gbus_int_irq_init
r_struct
id|gbus_int_irq_init
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of interrupt type */
multiline_comment|/* Range of kernel irq numbers for this type:&n;&t;   BASE, BASE+INTERVAL, ..., BASE+INTERVAL*NUM  */
DECL|member|base
DECL|member|num
DECL|member|interval
r_int
id|base
comma
id|num
comma
id|interval
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
multiline_comment|/* interrupt priority to assign */
)brace
suffix:semicolon
r_struct
id|hw_interrupt_type
suffix:semicolon
multiline_comment|/* fwd decl */
multiline_comment|/* Initialize HW_IRQ_TYPES for GBUS irqs described in array&n;   INITS (which is terminated by an entry with the name field == 0).  */
r_extern
r_void
id|gbus_int_init_irq_types
(paren
r_struct
id|gbus_int_irq_init
op_star
id|inits
comma
r_struct
id|hw_interrupt_type
op_star
id|hw_irq_types
)paren
suffix:semicolon
multiline_comment|/* Initialize GBUS interrupts.  */
r_extern
r_void
id|gbus_int_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_GBUS_INT_H__ */
eof
