multiline_comment|/*&n; * linux/arch/arm/mach-imx/leds-mx1ads.c&n; *&n; * Copyright (c) 2004 Sascha Hauer &lt;sascha@saschahauer.de&gt;&n; *&n; * Original (leds-footbridge.c) by Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;leds.h&quot;
multiline_comment|/*&n; * The MX1ADS Board has only one usable LED,&n; * so select only the timer led or the&n; * cpu usage led&n; */
r_void
DECL|function|mx1ads_leds_event
id|mx1ads_leds_event
c_func
(paren
id|led_event_t
id|ledevt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ledevt
)paren
(brace
macro_line|#ifdef CONFIG_LEDS_CPU
r_case
id|led_idle_start
suffix:colon
id|DR
c_func
(paren
l_int|0
)paren
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_idle_end
suffix:colon
id|DR
c_func
(paren
l_int|0
)paren
op_or_assign
l_int|1
op_lshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LEDS_TIMER
r_case
id|led_timer
suffix:colon
id|DR
c_func
(paren
l_int|0
)paren
op_xor_assign
l_int|1
op_lshift
l_int|2
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
