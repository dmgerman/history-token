multiline_comment|/*&n; * linux/include/asm-cris/timex.h&n; *&n; * CRIS architecture timex specifications&n; */
macro_line|#ifndef _ASM_CRIS_TIMEX_H
DECL|macro|_ASM_CRIS_TIMEX_H
mdefine_line|#define _ASM_CRIS_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 19200 /* Underlying frequency of the HZ timer */
multiline_comment|/* The timer0 values gives ~52.1us resolution (1/19200) but interrupts at HZ*/
DECL|macro|TIMER0_FREQ
mdefine_line|#define TIMER0_FREQ (CLOCK_TICK_RATE)
DECL|macro|TIMER0_CLKSEL
mdefine_line|#define TIMER0_CLKSEL c19k2Hz
DECL|macro|TIMER0_DIV
mdefine_line|#define TIMER0_DIV (TIMER0_FREQ/(HZ))
multiline_comment|/* This is the slow one: */
multiline_comment|/*&n;#define GET_JIFFIES_USEC() &bslash;&n;  ( (*R_TIMER0_DATA - TIMER0_DIV) * (1000000/HZ)/TIMER0_DIV )&n;*/
multiline_comment|/* This is the fast version: */
r_extern
r_int
r_int
id|cris_timer0_value_us
(braket
id|TIMER0_DIV
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* in kernel/time.c */
DECL|macro|GET_JIFFIES_USEC
mdefine_line|#define GET_JIFFIES_USEC() (cris_timer0_value_us[*R_TIMER0_DATA])
multiline_comment|/*&n; * We don&squot;t have a cycle-counter.. but we do not support SMP anyway where this is&n; * used so it does not matter.&n; */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
