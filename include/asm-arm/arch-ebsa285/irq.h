multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/irq.h&n; *&n; *  Copyright (C) 1996-1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   22-Aug-1998 RMK&t;Restructured IRQ routines&n; *   03-Sep-1998 PJB&t;Merged CATS support&n; *   20-Jan-1998 RMK&t;Started merge of EBSA286, CATS and NetWinder&n; *   26-Jan-1999 PJB&t;Don&squot;t use IACK on CATS&n; *   16-Mar-1999 RMK&t;Added autodetect of ISA PICs&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|variable|isa_irq
r_int
id|isa_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|fixup_irq
r_static
r_inline
r_int
id|fixup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
macro_line|#ifdef PCIIACK_BASE
r_if
c_cond
(paren
id|irq
op_eq
id|isa_irq
)paren
id|irq
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|PCIIACK_BASE
suffix:semicolon
macro_line|#endif
r_return
id|irq
suffix:semicolon
)brace
eof
