multiline_comment|/*&n; * linux/arch/sh/boards/adx/irq.c&n; *&n; * Copyright (C) 2001 A&amp;D Co., Ltd.&n; *&n; * I/O routine and setup routines for A&amp;D ADX Board&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|function|init_adx_IRQ
r_void
id|init_adx_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*      printk(&quot;init_adx_IRQ()&bslash;n&quot;);*/
multiline_comment|/* setup irq_mask_register */
id|irq_mask_register
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xa6000008
suffix:semicolon
multiline_comment|/* cover all external interrupt area by maskreg_irq_type&n;         * (Actually, irq15 doesn&squot;t exist)&n;         */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|make_maskreg_irq
c_func
(paren
id|i
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
eof
