multiline_comment|/*&n; * include/asm-v850/v850e_intc.h -- V850E CPU interrupt controller (INTC)&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_V850E_INTC_H__
DECL|macro|__V850_V850E_INTC_H__
mdefine_line|#define __V850_V850E_INTC_H__
multiline_comment|/* There are 4 16-bit `Interrupt Mask Registers&squot; located contiguously&n;   starting from this base.  Each interrupt uses a single bit to&n;   indicated enabled/disabled status.  */
DECL|macro|V850E_INTC_IMR_BASE_ADDR
mdefine_line|#define V850E_INTC_IMR_BASE_ADDR  0xFFFFF100
DECL|macro|V850E_INTC_IMR_ADDR
mdefine_line|#define V850E_INTC_IMR_ADDR(irq)  (V850E_INTC_IMR_BASE_ADDR + ((irq) &gt;&gt; 3))
DECL|macro|V850E_INTC_IMR_BIT
mdefine_line|#define V850E_INTC_IMR_BIT(irq)&t;  ((irq) &amp; 0x7)
multiline_comment|/* Each maskable interrupt has a single-byte control register at this&n;   address.  */
DECL|macro|V850E_INTC_IC_BASE_ADDR
mdefine_line|#define V850E_INTC_IC_BASE_ADDR&t;  0xFFFFF110
DECL|macro|V850E_INTC_IC_ADDR
mdefine_line|#define V850E_INTC_IC_ADDR(irq)&t;  (V850E_INTC_IC_BASE_ADDR + ((irq) &lt;&lt; 1))
DECL|macro|V850E_INTC_IC
mdefine_line|#define V850E_INTC_IC(irq)&t;  (*(volatile u8 *)V850E_INTC_IC_ADDR(irq))
multiline_comment|/* Encode priority PR for storing in an interrupt control register.  */
DECL|macro|V850E_INTC_IC_PR
mdefine_line|#define V850E_INTC_IC_PR(pr)&t;  (pr)
multiline_comment|/* Interrupt disable bit in an interrupt control register.  */
DECL|macro|V850E_INTC_IC_MK_BIT
mdefine_line|#define V850E_INTC_IC_MK_BIT&t;  6
DECL|macro|V850E_INTC_IC_MK
mdefine_line|#define V850E_INTC_IC_MK&t;  (1 &lt;&lt; V850E_INTC_IC_MK_BIT)
multiline_comment|/* Interrupt pending flag in an interrupt control register.  */
DECL|macro|V850E_INTC_IC_IF_BIT
mdefine_line|#define V850E_INTC_IC_IF_BIT&t;  7
DECL|macro|V850E_INTC_IC_IF
mdefine_line|#define V850E_INTC_IC_IF&t;  (1 &lt;&lt; V850E_INTC_IC_IF_BIT)
multiline_comment|/* The ISPR (In-service priority register) contains one bit for each interrupt&n;   priority level, which is set to one when that level is currently being&n;   serviced (and thus blocking any interrupts of equal or lesser level).  */
DECL|macro|V850E_INTC_ISPR_ADDR
mdefine_line|#define V850E_INTC_ISPR_ADDR&t;  0xFFFFF1FA
DECL|macro|V850E_INTC_ISPR
mdefine_line|#define V850E_INTC_ISPR&t;&t;  (*(volatile u8 *)V850E_INTC_ISPR_ADDR)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Enable interrupt handling for interrupt IRQ.  */
DECL|function|v850e_intc_enable_irq
r_static
r_inline
r_void
id|v850e_intc_enable_irq
(paren
r_int
id|irq
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;clr1 %0, [%1]&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_BIT
(paren
id|irq
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_ADDR
(paren
id|irq
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable interrupt handling for interrupt IRQ.  Note that any&n;   interrupts received while disabled will be delivered once the&n;   interrupt is enabled again, unless they are explicitly cleared using&n;   `v850e_intc_clear_pending_irq&squot;.  */
DECL|function|v850e_intc_disable_irq
r_static
r_inline
r_void
id|v850e_intc_disable_irq
(paren
r_int
id|irq
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;set1 %0, [%1]&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_BIT
(paren
id|irq
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_ADDR
(paren
id|irq
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if interrupt handling for interrupt IRQ is enabled.  */
DECL|function|v850e_intc_irq_enabled
r_static
r_inline
r_int
id|v850e_intc_irq_enabled
(paren
r_int
id|irq
)paren
(brace
r_int
id|rval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;tst1 %1, [%2]; setf z, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|rval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_BIT
(paren
id|irq
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IMR_ADDR
(paren
id|irq
)paren
)paren
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
multiline_comment|/* Disable irqs from 0 until LIMIT.  LIMIT must be a multiple of 8.  */
DECL|function|_v850e_intc_disable_irqs
r_static
r_inline
r_void
id|_v850e_intc_disable_irqs
(paren
r_int
id|limit
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|V850E_INTC_IMR_BASE_ADDR
suffix:semicolon
id|limit
op_ge
l_int|8
suffix:semicolon
id|addr
op_increment
comma
id|limit
op_sub_assign
l_int|8
)paren
op_star
(paren
r_char
op_star
)paren
id|addr
op_assign
l_int|0xFF
suffix:semicolon
)brace
multiline_comment|/* Disable all irqs.  This is purposely a macro, because NUM_MACH_IRQS&n;   will be only be defined later.  */
DECL|macro|v850e_intc_disable_irqs
mdefine_line|#define v850e_intc_disable_irqs()   _v850e_intc_disable_irqs (NUM_MACH_IRQS)
multiline_comment|/* Clear any pending interrupts for IRQ.  */
DECL|function|v850e_intc_clear_pending_irq
r_static
r_inline
r_void
id|v850e_intc_clear_pending_irq
(paren
r_int
id|irq
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;clr1 %0, 0[%1]&quot;
op_scope_resolution
l_string|&quot;i&quot;
(paren
id|V850E_INTC_IC_IF_BIT
)paren
comma
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IC_ADDR
(paren
id|irq
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if interrupt IRQ is pending (but disabled).  */
DECL|function|v850e_intc_irq_pending
r_static
r_inline
r_int
id|v850e_intc_irq_pending
(paren
r_int
id|irq
)paren
(brace
r_int
id|rval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;tst1 %1, 0[%2]; setf nz, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|rval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|V850E_INTC_IC_IF_BIT
)paren
comma
l_string|&quot;r&quot;
(paren
id|V850E_INTC_IC_ADDR
(paren
id|irq
)paren
)paren
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
DECL|struct|v850e_intc_irq_init
r_struct
id|v850e_intc_irq_init
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
multiline_comment|/* Initialize HW_IRQ_TYPES for INTC-controlled irqs described in array&n;   INITS (which is terminated by an entry with the name field == 0).  */
r_extern
r_void
id|v850e_intc_init_irq_types
(paren
r_struct
id|v850e_intc_irq_init
op_star
id|inits
comma
r_struct
id|hw_interrupt_type
op_star
id|hw_irq_types
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_V850E_INTC_H__ */
eof
