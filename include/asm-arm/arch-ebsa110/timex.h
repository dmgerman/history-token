multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/timex.h&n; *&n; *  Copyright (C) 1997, 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  EBSA110 architecture timex specifications&n; */
multiline_comment|/*&n; * On the EBSA, the clock ticks at weird rates.&n; * This is therefore not used to calculate the&n; * divisor.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;47894000
eof
