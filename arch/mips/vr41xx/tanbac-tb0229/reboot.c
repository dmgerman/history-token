multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/tanbac-tb0229/reboot.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Depending on TANBAC TB0229(VR4131DIMM) of reboot system call.&n; *&n; * Copyright 2003 Megasolution Inc.&n; *                matsu@megasolution.jp&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/tb0229.h&gt;
DECL|macro|tb0229_hard_reset
mdefine_line|#define tb0229_hard_reset()&t;writew(0, TB0219_RESET_REGS)
DECL|function|tanbac_tb0229_restart
r_void
id|tanbac_tb0229_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
macro_line|#ifdef CONFIG_TANBAC_TB0219
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|tb0229_hard_reset
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#else
id|vr41xx_restart
c_func
(paren
id|command
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
