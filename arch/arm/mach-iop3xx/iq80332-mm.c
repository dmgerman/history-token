multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/mm.c&n; *&n; * Low level memory initialization for iq80332 platform&n; *&n; * Author: Dave Jiang &lt;dave.jiang@intel.com&gt;&n; * Copyright (C) 2004 Intel Corp.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * IQ80332 specific IO mappings&n; *&n; * We use RedBoot&squot;s setup for the onboard devices.&n; */
DECL|function|iq80332_map_io
r_void
id|__init
id|iq80332_map_io
c_func
(paren
r_void
)paren
(brace
id|iop331_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
eof
