multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/leds-system3.c&n; *&n; * Copyright (C) 2001 Stefan Eletzhofer &lt;stefan.eletzhofer@gmx.de&gt;&n; *&n; * Original (leds-footbridge.c) by Russell King&n; *&n; * $Id: leds-system3.c,v 1.1.6.1 2001/12/04 15:19:26 seletz Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * $Log: leds-system3.c,v $&n; * Revision 1.1.6.1  2001/12/04 15:19:26  seletz&n; * - merged from linux_2_4_13_ac5_rmk2&n; *&n; * Revision 1.1.4.2  2001/11/19 17:58:53  seletz&n; * - cleanup&n; *&n; * Revision 1.1.4.1  2001/11/16 13:49:54  seletz&n; * - dummy LED support for PT Digital Board&n; *&n; * Revision 1.1.2.1  2001/10/15 16:03:39  seletz&n; * - dummy function&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;leds.h&quot;
DECL|macro|LED_STATE_ENABLED
mdefine_line|#define LED_STATE_ENABLED&t;1
DECL|macro|LED_STATE_CLAIMED
mdefine_line|#define LED_STATE_CLAIMED&t;2
DECL|variable|led_state
r_static
r_int
r_int
id|led_state
suffix:semicolon
DECL|variable|hw_led_state
r_static
r_int
r_int
id|hw_led_state
suffix:semicolon
DECL|function|system3_leds_event
r_void
id|system3_leds_event
c_func
(paren
id|led_event_t
id|evt
)paren
(brace
multiline_comment|/* TODO: support LEDs */
)brace
eof
