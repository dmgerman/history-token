multiline_comment|/*&n; *  include/asm-i386/mach-default/mach_timer.h&n; *&n; *  Machine specific calibrate_tsc() for generic.&n; *  Split out from timer_tsc.c by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
multiline_comment|/* ------ Calibrate the TSC ------- &n; * Return 2^32 * (1 / (TSC clocks per usec)) for do_fast_gettimeoffset().&n; * Too much 64-bit arithmetic here to do this cleanly in C, and for&n; * accuracy&squot;s sake we want to keep the overhead on the CTC speaker (channel 2)&n; * output busy loop as low as possible. We avoid reading the CTC registers&n; * directly because of the awkward 8-bit access mechanism of the 82C54&n; * device.&n; */
macro_line|#ifndef _MACH_TIMER_H
DECL|macro|_MACH_TIMER_H
mdefine_line|#define _MACH_TIMER_H
DECL|macro|CALIBRATE_LATCH
mdefine_line|#define CALIBRATE_LATCH&t;(5 * LATCH)
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
multiline_comment|/* Set the Gate high, disable speaker */
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
l_int|0x61
)paren
op_amp
op_complement
l_int|0x02
)paren
op_or
l_int|0x01
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now let&squot;s take care of CTC channel 2&n;&t; *&n;&t; * Set the Gate high, program CTC channel 2 for mode 0,&n;&t; * (interrupt on terminal count mode), binary count,&n;&t; * load 5 * LATCH count, (LSB and MSB) to begin countdown.&n;&t; *&n;&t; * Some devices need a delay here.&n;&t; */
id|outb
c_func
(paren
l_int|0xb0
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 0, LSB/MSB, Ch 2 */
id|outb_p
c_func
(paren
id|CALIBRATE_LATCH
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
multiline_comment|/* LSB of count */
id|outb_p
c_func
(paren
id|CALIBRATE_LATCH
op_rshift
l_int|8
comma
l_int|0x42
)paren
suffix:semicolon
multiline_comment|/* MSB of count */
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
op_star
id|count
op_assign
l_int|0L
suffix:semicolon
r_do
(brace
op_star
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
l_int|0x61
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* !_MACH_TIMER_H */
eof
