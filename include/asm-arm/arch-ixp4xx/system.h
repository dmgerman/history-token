multiline_comment|/*&n; * include/asm-arm/arch-ixp4x//system.h &n; *&n; * Copyright (C) 2002 Intel Corporation.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;asm/hardware.h&gt;
DECL|function|arch_idle
r_static
r_inline
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|hlt_counter
)paren
id|cpu_do_idle
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|arch_reset
r_static
r_inline
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
l_int|1
op_logical_and
id|mode
op_eq
l_char|&squot;s&squot;
)paren
(brace
multiline_comment|/* Jump into ROM at address 0 */
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Use on-chip reset capability */
multiline_comment|/* set the &quot;key&quot; register to enable access to&n;&t;&t; * &quot;timer&quot; and &quot;enable&quot; registers&n;&t;&t; */
op_star
id|IXP4XX_OSWK
op_assign
l_int|0x482e
suffix:semicolon
multiline_comment|/* write 0 to the timer register for an immidiate reset */
op_star
id|IXP4XX_OSWT
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable watchdog interrupt, enable reset, enable count */
op_star
id|IXP4XX_OSWE
op_assign
l_int|0x3
suffix:semicolon
)brace
)brace
eof
