multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/leds-simpad.c&n; *&n; * Author: Juergen Messerer &lt;juergen.messerer@siemens.ch&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/arch/simpad.h&gt;
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
DECL|macro|LED_GREEN
mdefine_line|#define&t;LED_GREEN&t;(1)
DECL|macro|LED_MASK
mdefine_line|#define&t;LED_MASK&t;(1)
r_extern
r_void
id|set_cs3_bit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
r_extern
r_void
id|clear_cs3_bit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
DECL|function|simpad_leds_event
r_void
id|simpad_leds_event
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
singleline_comment|//local_irq_save(flags);
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
id|LED_GREEN
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
id|LED_GREEN
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
id|LED_GREEN
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_LEDS_TIMER
r_case
id|led_timer
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|led_state
op_amp
id|LED_STATE_CLAIMED
)paren
)paren
id|hw_led_state
op_xor_assign
id|LED_GREEN
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LEDS_CPU
r_case
id|led_idle_start
suffix:colon
r_break
suffix:semicolon
r_case
id|led_idle_end
suffix:colon
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
r_if
c_cond
(paren
id|led_state
op_amp
id|LED_STATE_CLAIMED
)paren
id|hw_led_state
op_or_assign
id|LED_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_green_off
suffix:colon
r_if
c_cond
(paren
id|led_state
op_amp
id|LED_STATE_CLAIMED
)paren
id|hw_led_state
op_and_assign
op_complement
id|LED_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_amber_on
suffix:colon
r_break
suffix:semicolon
r_case
id|led_amber_off
suffix:colon
r_break
suffix:semicolon
r_case
id|led_red_on
suffix:colon
r_break
suffix:semicolon
r_case
id|led_red_off
suffix:colon
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
id|set_cs3_bit
c_func
(paren
id|LED2_ON
)paren
suffix:semicolon
r_else
id|clear_cs3_bit
c_func
(paren
id|LED2_ON
)paren
suffix:semicolon
singleline_comment|//local_irq_restore(flags);
)brace
eof
