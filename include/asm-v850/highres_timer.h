multiline_comment|/*&n; * include/asm-v850/highres_timer.h -- High resolution timing routines&n; *&n; *  Copyright (C) 2001,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_HIGHRES_TIMER_H__
DECL|macro|__V850_HIGHRES_TIMER_H__
mdefine_line|#define __V850_HIGHRES_TIMER_H__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/entry.h&gt;
multiline_comment|/* Frequency of the `slow ticks&squot; (one tick each time the fast-tick&n;   counter overflows).  */
DECL|macro|HIGHRES_TIMER_SLOW_TICK_RATE
mdefine_line|#define HIGHRES_TIMER_SLOW_TICK_RATE&t;25
multiline_comment|/* Which timer in the V850E `Timer D&squot; we use.  */
DECL|macro|HIGHRES_TIMER_TIMER_D_UNIT
mdefine_line|#define HIGHRES_TIMER_TIMER_D_UNIT&t;3
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|highres_timer_start
(paren
r_void
)paren
comma
id|highres_timer_stop
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|highres_timer_reset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|highres_timer_read_ticks
(paren
id|u32
op_star
id|slow_ticks
comma
id|u32
op_star
id|fast_ticks
)paren
suffix:semicolon
r_extern
r_void
id|highres_timer_ticks_to_timeval
(paren
id|u32
id|slow_ticks
comma
id|u32
id|fast_ticks
comma
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_void
id|highres_timer_read
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_HIGHRES_TIMER_H__ */
eof
