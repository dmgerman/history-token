multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/timex.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  EBSA285 architecture timex specifications&n; */
multiline_comment|/*&n; * We assume a constant here; this satisfies the maths in linux/timex.h&n; * and linux/time.h.  CLOCK_TICK_RATE is actually system dependent, but&n; * this must be a constant.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(50000000/16)
eof
