multiline_comment|/*&n; * linux/arch/arm/mach-imx/leds.h&n; *&n; * Copyright (C) 2004 Sascha Hauer &lt;sascha@saschahauer.de&gt;&n; *&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;leds.h&quot;
r_static
r_int
id|__init
DECL|function|leds_init
id|leds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_mx1ads
c_func
(paren
)paren
)paren
(brace
id|leds_event
op_assign
id|mx1ads_leds_event
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|leds_init
id|__initcall
c_func
(paren
id|leds_init
)paren
suffix:semicolon
eof
