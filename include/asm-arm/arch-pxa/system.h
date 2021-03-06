multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/system.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Created:&t;Jun 15, 2001&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;pxa-regs.h&quot;
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
id|cpu_do_idle
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/* Initialize the watchdog and let it fire */
id|OWER
op_assign
id|OWER_WME
suffix:semicolon
id|OSSR
op_assign
id|OSSR_M3
suffix:semicolon
id|OSMR3
op_assign
id|OSCR
op_plus
l_int|368640
suffix:semicolon
multiline_comment|/* ... in 100 ms */
)brace
)brace
eof
