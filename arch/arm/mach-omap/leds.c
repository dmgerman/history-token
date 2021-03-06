multiline_comment|/*&n; * linux/arch/arm/mach-omap/leds.c&n; *&n; * OMAP LEDs dispatcher&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &quot;leds.h&quot;
r_static
r_int
id|__init
DECL|function|omap_leds_init
id|omap_leds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_omap_innovator
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|innovator_leds_event
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_omap_h2
c_func
(paren
)paren
op_logical_or
id|machine_is_omap_perseus2
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|h2p2_dbg_leds_event
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|osk_leds_event
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_omap_h2
c_func
(paren
)paren
op_logical_or
id|machine_is_omap_perseus2
c_func
(paren
)paren
op_logical_or
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* LED1/LED2 pins can be used as GPIO (as done here), or by&n;&t;&t; * the LPG (works even in deep sleep!), to drive a bicolor&n;&t;&t; * LED on the H2 sample board, and another on the H2/P2&n;&t;&t; * &quot;surfer&quot; expansion board.&n;&t;&t; *&n;&t;&t; * The same pins drive a LED on the OSK Mistral board, but&n;&t;&t; * that&squot;s a different kind of LED (just one color at a time).&n;&t;&t; */
id|omap_cfg_reg
c_func
(paren
id|P18_1610_GPIO3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|omap_request_gpio
c_func
(paren
l_int|3
)paren
op_eq
l_int|0
)paren
id|omap_set_gpio_direction
c_func
(paren
l_int|3
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;LED: can&squot;t get GPIO3/red?&bslash;n&quot;
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|MPUIO4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|omap_request_gpio
c_func
(paren
id|OMAP_MPUIO
c_func
(paren
l_int|4
)paren
)paren
op_eq
l_int|0
)paren
id|omap_set_gpio_direction
c_func
(paren
id|OMAP_MPUIO
c_func
(paren
l_int|4
)paren
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;LED: can&squot;t get MPUIO4/green?&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
DECL|variable|omap_leds_init
id|__initcall
c_func
(paren
id|omap_leds_init
)paren
suffix:semicolon
eof
