multiline_comment|/*&n; * linux/include/asm-arm/arch-iop80310/timex.h&n; *&n; * IOP310 architecture timex specifications&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ARCH_IQ80310
macro_line|#ifndef CONFIG_XSCALE_PMU_TIMER
multiline_comment|/* This is for the on-board timer */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 33000000 /* Underlying HZ */
macro_line|#else
multiline_comment|/* This is for the underlying xs80200 PMU clock. We run the core @ 733MHz */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;733000000
macro_line|#endif
macro_line|#else
macro_line|#error &quot;No IOP310 timex information for this architecture&quot;
macro_line|#endif
eof
