multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/timex.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Created:&t;Jun 15, 2001&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_PXA25x)
multiline_comment|/* PXA250/210 timer base */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 3686400
macro_line|#elif defined(CONFIG_PXA27x)
multiline_comment|/* PXA27x timer base */
macro_line|#ifdef CONFIG_MACH_MAINSTONE
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 3249600
macro_line|#else
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 3250000
macro_line|#endif
macro_line|#endif
eof
