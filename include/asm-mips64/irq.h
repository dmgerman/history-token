multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle&n; * Copyright (C) 1995, 96, 97, 98, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 Kanoj Sarcar&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 256
multiline_comment|/*&n; * Number of levels in INT_PEND0. Can be set to 128 if we also&n; * consider INT_PEND1.&n; */
DECL|macro|PERNODE_LEVELS
mdefine_line|#define PERNODE_LEVELS&t;64
r_extern
r_int
id|node_level_to_irq
(braket
id|MAX_COMPACT_NODES
)braket
(braket
id|PERNODE_LEVELS
)braket
suffix:semicolon
multiline_comment|/*&n; * we need to map irq&squot;s up to at least bit 7 of the INT_MASK0_A register&n; * since bits 0-6 are pre-allocated for other purposes.&n; */
DECL|macro|LEAST_LEVEL
mdefine_line|#define LEAST_LEVEL&t;7
DECL|macro|FAST_IRQ_TO_LEVEL
mdefine_line|#define FAST_IRQ_TO_LEVEL(i)&t;((i) + LEAST_LEVEL)
DECL|macro|LEVEL_TO_IRQ
mdefine_line|#define LEVEL_TO_IRQ(c, l) &bslash;&n;&t;&t;&t;(node_level_to_irq[CPUID_TO_COMPACT_NODEID(c)][(l)])
macro_line|#ifdef CONFIG_I8259
DECL|function|irq_cannonicalize
r_static
r_inline
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
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
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(irq) (irq)&t;/* Sane hardware, sane code ... */
macro_line|#endif
r_struct
id|irqaction
suffix:semicolon
r_extern
r_int
id|i8259_setup_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
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
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Machine specific interrupt initialization  */
r_extern
r_void
(paren
op_star
id|irq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
eof
