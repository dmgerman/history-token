multiline_comment|/*&n; * linux/arch/arm/mach-omap/leds.c&n; *&n; * OMAP LEDs dispatcher&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;leds.h&quot;
r_static
r_int
id|__init
DECL|function|omap1510_leds_init
id|omap1510_leds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_innovator
c_func
(paren
)paren
)paren
id|leds_event
op_assign
id|innovator_leds_event
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
DECL|variable|omap1510_leds_init
id|__initcall
c_func
(paren
id|omap1510_leds_init
)paren
suffix:semicolon
eof
