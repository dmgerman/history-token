multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/timex.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * 04-21-2000  RS Created file&n; * 05-03-2000 SJH Tick rate was wrong&n; *&n; */
multiline_comment|/*&n; * On the ARM720T, clock ticks are set to 128 Hz.&n; *&n; * NOTE: The actual RTC value is set in &squot;time.h&squot; which&n; *       must be changed when choosing a different tick&n; *       rate. The value of HZ in &squot;param.h&squot; must also&n; *       be changed to match below.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;128
eof
