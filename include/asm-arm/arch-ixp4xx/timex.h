multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp4xx/timex.h&n; * &n; */
macro_line|#include &lt;asm/hardware.h&gt;
multiline_comment|/*&n; * We use IXP425 General purpose timer for our timer needs, it runs at 66 MHz&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE (IXP4XX_PERIPHERAL_BUS_CLOCK * 1000000)
eof
