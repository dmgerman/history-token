multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/generic.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
r_extern
r_void
id|__init
id|pxa_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|pxa_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SET_BANK
mdefine_line|#define SET_BANK(__nr,__start,__size) &bslash;&n;&t;mi-&gt;bank[__nr].start = (__start), &bslash;&n;&t;mi-&gt;bank[__nr].size = (__size), &bslash;&n;&t;mi-&gt;bank[__nr].node = (((unsigned)(__start) - PHYS_OFFSET) &gt;&gt; 27)
eof
