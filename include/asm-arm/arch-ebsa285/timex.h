multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/timex.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  EBSA285 architecture timex specifications&n; */
multiline_comment|/*&n; * On EBSA285 boards, the clock runs at 50MHz and is&n; * divided by a 4-bit prescaler.  Other boards use an&n; * ISA derived timer, and this is unused.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(mem_fclk_21285 / 16)
eof
