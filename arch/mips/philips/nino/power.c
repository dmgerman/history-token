multiline_comment|/*&n; *  linux/arch/mips/philips/nino/power.c&n; *&n; *  Copyright (C) 2000 Jim Pick &lt;jim@jimpick.com&gt;&n; *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Power management routines on the Philips Nino.&n; */
macro_line|#include &lt;asm/tx3912.h&gt;
DECL|function|nino_wait
r_void
id|nino_wait
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We stop the CPU to conserve power */
id|PowerControl
op_or_assign
id|PWR_STOPCPU
suffix:semicolon
multiline_comment|/* &n;&t; * We wait until an interrupt happens...&n;&t; */
multiline_comment|/* We resume here */
id|PowerControl
op_and_assign
op_complement
id|PWR_STOPCPU
suffix:semicolon
multiline_comment|/* Give ourselves a little delay */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
)brace
eof
