multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/leds.c&n; *&n; * SA1100 LEDs dispatcher&n; * &n; * Copyright (C) 2001 Nicolas Pitre&n; */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;leds.h&quot;
r_static
r_int
id|__init
DECL|function|sa1100_leds_init
id|sa1100_leds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_assabet
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|assabet_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_consus
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|consus_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_badge4
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|badge4_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_brutus
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|brutus_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_cerf
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|cerf_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_flexanet
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|flexanet_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_graphicsclient
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|graphicsclient_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_hackkit
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|hackkit_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_lart
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|lart_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_pfs168
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|pfs168_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_graphicsmaster
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|graphicsmaster_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_adsbitsy
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|adsbitsy_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_pt_system3
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|system3_leds_event
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_simpad
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|simpad_leds_event
suffix:semicolon
multiline_comment|/* what about machine registry? including led, apm... -zecke */
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
DECL|variable|sa1100_leds_init
id|core_initcall
c_func
(paren
id|sa1100_leds_init
)paren
suffix:semicolon
eof
