multiline_comment|/*&n; *  include/asm-i386/mach-pc9800/mach_timer.h&n; *&n; *  Machine specific calibrate_tsc() for PC-9800.&n; *  Written by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
multiline_comment|/* ------ Calibrate the TSC ------- &n; * PC-9800:&n; *  CTC cannot be used because some models (especially&n; *  note-machines) may disable clock to speaker channel (#1)&n; *  unless speaker is enabled.  We use ARTIC instead.&n; */
macro_line|#ifndef _MACH_TIMER_H
DECL|macro|_MACH_TIMER_H
mdefine_line|#define _MACH_TIMER_H
DECL|macro|CALIBRATE_LATCH
mdefine_line|#define CALIBRATE_LATCH&t;(5 * 307200/HZ) /* 0.050sec * 307200Hz = 15360 */
DECL|function|mach_prepare_counter
r_static
r_inline
r_void
id|mach_prepare_counter
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* ARTIC can&squot;t be stopped nor reset. So we wait roundup. */
r_while
c_loop
(paren
id|inw
c_func
(paren
l_int|0x5c
)paren
)paren
suffix:semicolon
)brace
DECL|function|mach_countup
r_static
r_inline
r_void
id|mach_countup
c_func
(paren
r_int
r_int
op_star
id|count
)paren
(brace
r_do
(brace
op_star
id|count
op_assign
id|inw
c_func
(paren
l_int|0x5c
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|count
OL
id|CALIBRATE_LATCH
)paren
suffix:semicolon
)brace
macro_line|#endif /* !_MACH_TIMER_H */
eof
