multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/timex.h&n; *&n; * IOP3xx architecture timex specifications&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ARCH_IQ80321)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 200000000
macro_line|#else
macro_line|#error &quot;No IOP3xx timex information for this architecture&quot;
macro_line|#endif
eof
