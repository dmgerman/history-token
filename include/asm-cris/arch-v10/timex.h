multiline_comment|/*&n; * Use prescale timer at 25000 Hz instead of the baudrate timer at &n; * 19200 to get rid of the 64ppm to fast timer (and we get better &n; * resolution within a jiffie as well. &n; */
macro_line|#ifndef _ASM_CRIS_ARCH_TIMEX_H
DECL|macro|_ASM_CRIS_ARCH_TIMEX_H
mdefine_line|#define _ASM_CRIS_ARCH_TIMEX_H
multiline_comment|/* The prescaler clock runs at 25MHz, we divide it by 1000 in the prescaler */
multiline_comment|/* If you change anything here you must check time.c as well... */
DECL|macro|PRESCALE_FREQ
mdefine_line|#define PRESCALE_FREQ 25000000
DECL|macro|PRESCALE_VALUE
mdefine_line|#define PRESCALE_VALUE 1000
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 25000 /* Underlying frequency of the HZ timer */
multiline_comment|/* The timer0 values gives 40us resolution (1/25000) but interrupts at HZ*/
DECL|macro|TIMER0_FREQ
mdefine_line|#define TIMER0_FREQ (CLOCK_TICK_RATE)
DECL|macro|TIMER0_CLKSEL
mdefine_line|#define TIMER0_CLKSEL flexible
DECL|macro|TIMER0_DIV
mdefine_line|#define TIMER0_DIV (TIMER0_FREQ/(HZ))
DECL|macro|GET_JIFFIES_USEC
mdefine_line|#define GET_JIFFIES_USEC() &bslash;&n;  ( (TIMER0_DIV - *R_TIMER0_DATA) * (1000000/HZ)/TIMER0_DIV )
r_int
r_int
id|get_ns_in_jiffie
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_us_in_jiffie_highres
r_extern
r_inline
r_int
r_int
id|get_us_in_jiffie_highres
c_func
(paren
r_void
)paren
(brace
r_return
id|get_ns_in_jiffie
c_func
(paren
)paren
op_div
l_int|1000
suffix:semicolon
)brace
macro_line|#endif
eof
