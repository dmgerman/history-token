multiline_comment|/*&n; *&t;arch/m68knommu/lib/delay.c&n; *&n; *&t;(C) Copyright 2004, Greg Ungerer &lt;gerg@snapgear.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
DECL|variable|udelay
id|EXPORT_SYMBOL
c_func
(paren
id|udelay
)paren
suffix:semicolon
DECL|function|udelay
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
id|_udelay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
eof
