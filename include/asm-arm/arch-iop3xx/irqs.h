multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/irqs.h&n; *&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Whic iop3xx implementation is this?&n; */
macro_line|#ifdef CONFIG_ARCH_IOP310
macro_line|#include &quot;iop310-irqs.h&quot;
macro_line|#else
macro_line|#include &quot;iop321-irqs.h&quot;
macro_line|#endif
eof
