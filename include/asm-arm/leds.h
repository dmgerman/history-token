multiline_comment|/*&n; *  linux/include/asm-arm/leds.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Event-driven interface for LEDs on machines&n; *  Added led_start and led_stop- Alex Holden, 28th Dec 1998.&n; */
macro_line|#ifndef ASM_ARM_LEDS_H
DECL|macro|ASM_ARM_LEDS_H
mdefine_line|#define ASM_ARM_LEDS_H
macro_line|#include &lt;linux/config.h&gt;
r_typedef
r_enum
(brace
DECL|enumerator|led_idle_start
id|led_idle_start
comma
DECL|enumerator|led_idle_end
id|led_idle_end
comma
DECL|enumerator|led_timer
id|led_timer
comma
DECL|enumerator|led_start
id|led_start
comma
DECL|enumerator|led_stop
id|led_stop
comma
DECL|enumerator|led_claim
id|led_claim
comma
multiline_comment|/* override idle &amp; timer leds */
DECL|enumerator|led_release
id|led_release
comma
multiline_comment|/* restore idle &amp; timer leds */
DECL|enumerator|led_green_on
id|led_green_on
comma
DECL|enumerator|led_green_off
id|led_green_off
comma
DECL|enumerator|led_amber_on
id|led_amber_on
comma
DECL|enumerator|led_amber_off
id|led_amber_off
comma
DECL|enumerator|led_red_on
id|led_red_on
comma
DECL|enumerator|led_red_off
id|led_red_off
comma
multiline_comment|/*&n;&t; * I want this between led_timer and led_start, but&n;&t; * someone has decided to export this to user space&n;&t; */
DECL|enumerator|led_halted
id|led_halted
DECL|typedef|led_event_t
)brace
id|led_event_t
suffix:semicolon
multiline_comment|/* Use this routine to handle LEDs */
macro_line|#ifdef CONFIG_LEDS
r_extern
r_void
(paren
op_star
id|leds_event
)paren
(paren
id|led_event_t
)paren
suffix:semicolon
macro_line|#else
DECL|macro|leds_event
mdefine_line|#define leds_event(e)
macro_line|#endif
macro_line|#endif
eof
