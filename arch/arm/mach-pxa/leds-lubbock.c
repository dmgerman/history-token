multiline_comment|/*&n; * linux/arch/arm/mach-pxa/leds-lubbock.c&n; *&n; * Copyright (C) 2000 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *&n; * Copyright (c) 2001 Jeff Sutherland &lt;jeffs@accelent.com&gt;&n; *&n; * Original (leds-footbridge.c) by Russell King&n; *&n; * Major surgery on April 2004 by Nicolas Pitre for less global&n; * namespace collision.  Mostly adapted the Mainstone version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;leds.h&quot;
multiline_comment|/*&n; * 8 discrete leds available for general use:&n; *&n; * Note: bits [15-8] are used to enable/blank the 8 7 segment hex displays&n; * so be sure to not monkey with them here.&n; */
DECL|macro|D28
mdefine_line|#define D28&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|D27
mdefine_line|#define D27&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|D26
mdefine_line|#define D26&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|D25
mdefine_line|#define D25&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|D24
mdefine_line|#define D24&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|D23
mdefine_line|#define D23&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|D22
mdefine_line|#define D22&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|D21
mdefine_line|#define D21&t;&t;&t;(1 &lt;&lt; 7)
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
DECL|function|lubbock_leds_event
r_void
id|lubbock_leds_event
c_func
(paren
id|led_event_t
id|evt
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
id|evt
)paren
(brace
r_case
id|led_start
suffix:colon
id|hw_led_state
op_assign
l_int|0
suffix:semicolon
id|led_state
op_assign
id|LED_STATE_ENABLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_stop
suffix:colon
id|led_state
op_and_assign
op_complement
id|LED_STATE_ENABLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_claim
suffix:colon
id|led_state
op_or_assign
id|LED_STATE_CLAIMED
suffix:semicolon
id|hw_led_state
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_release
suffix:colon
id|led_state
op_and_assign
op_complement
id|LED_STATE_CLAIMED
suffix:semicolon
id|hw_led_state
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_LEDS_TIMER
r_case
id|led_timer
suffix:colon
id|hw_led_state
op_xor_assign
id|D26
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LEDS_CPU
r_case
id|led_idle_start
suffix:colon
id|hw_led_state
op_and_assign
op_complement
id|D27
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_idle_end
suffix:colon
id|hw_led_state
op_or_assign
id|D27
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|led_halted
suffix:colon
r_break
suffix:semicolon
r_case
id|led_green_on
suffix:colon
id|hw_led_state
op_or_assign
id|D21
suffix:semicolon
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_green_off
suffix:colon
id|hw_led_state
op_and_assign
op_complement
id|D21
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_amber_on
suffix:colon
id|hw_led_state
op_or_assign
id|D22
suffix:semicolon
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_amber_off
suffix:colon
id|hw_led_state
op_and_assign
op_complement
id|D22
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_red_on
suffix:colon
id|hw_led_state
op_or_assign
id|D23
suffix:semicolon
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_red_off
suffix:colon
id|hw_led_state
op_and_assign
op_complement
id|D23
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|led_state
op_amp
id|LED_STATE_ENABLED
)paren
id|LUB_DISC_BLNK_LED
op_assign
(paren
id|LUB_DISC_BLNK_LED
op_or
l_int|0xff
)paren
op_amp
op_complement
id|hw_led_state
suffix:semicolon
r_else
id|LUB_DISC_BLNK_LED
op_or_assign
l_int|0xff
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
