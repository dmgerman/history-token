multiline_comment|/*&n; * linux/arch/arm/mach-pxa/leds.c&n; *&n; * xscale LEDs dispatcher&n; *&n; * Copyright (C) 2001 Nicolas Pitre&n; *&n; * Copyright (c) 2001 Jeff Sutherland, Accelent Systems Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;leds.h&quot;
r_static
r_int
id|__init
DECL|function|pxa_leds_init
id|pxa_leds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_lubbock
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|lubbock_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_pxa_idp
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|idp_leds_event
suffix:semicolon
id|leds_event
c_func
(paren
id|led_start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pxa_leds_init
id|__initcall
c_func
(paren
id|pxa_leds_init
)paren
suffix:semicolon
eof
