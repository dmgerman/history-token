multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/timex.h&n; *&n; * IOP3xx architecture timex specifications&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ARCH_IQ80321) || defined(CONFIG_ARCH_IQ31244)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE IOP321_TICK_RATE
macro_line|#elif defined(CONFIG_ARCH_IQ80331) || defined(CONFIG_MACH_IQ80332)
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE IOP331_TICK_RATE
macro_line|#else
macro_line|#error &quot;No IOP3xx timex information for this architecture&quot;
macro_line|#endif
eof
