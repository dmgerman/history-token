multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994 - 2001 Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
r_extern
id|asmlinkage
r_void
id|jazz_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * On systems with i8259-style interrupt controllers we assume for&n; * driver compatibility reasons interrupts 0 - 15 to be the i8295&n; * interrupts even if the hardware uses a different interrupt numbering.&n; */
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|jazz_handle_int
)paren
suffix:semicolon
id|init_generic_irq
c_func
(paren
)paren
suffix:semicolon
id|init_i8259_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Integrated i8259  */
macro_line|#if 0
id|init_jazz_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Actually we&squot;ve got more interrupts to handle ...  */
r_for
c_loop
(paren
id|i
op_assign
id|PCIMT_IRQ_INT2
suffix:semicolon
id|i
op_le
id|PCIMT_IRQ_ETHERNET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|pciasic_irq_type
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
