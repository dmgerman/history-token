multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/time.h&n; *&n; * Copyright (c) 1996-2000 Russell King.&n; *&n; * Changelog:&n; *  24-Sep-1996&t;RMK&t;Created&n; *  10-Oct-1996&t;RMK&t;Brought up to date with arch-sa110eval&n; *  04-Dec-1997&t;RMK&t;Updated for new arch/arm/time.c&n; */
r_extern
r_void
id|ioctime_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|timer_interrupt
r_static
r_void
id|timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|do_set_rtc
c_func
(paren
)paren
suffix:semicolon
id|do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
(brace
multiline_comment|/* Twinkle the lights. */
r_static
r_int
id|count
comma
id|state
op_assign
l_int|0xff00
suffix:semicolon
r_if
c_cond
(paren
id|count
op_decrement
op_eq
l_int|0
)paren
(brace
id|state
op_xor_assign
l_int|0x100
suffix:semicolon
id|count
op_assign
l_int|25
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|LED_ADDRESS
)paren
op_assign
id|state
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|ioctime_init
c_func
(paren
)paren
suffix:semicolon
id|timer_irq.handler
op_assign
id|timer_interrupt
suffix:semicolon
id|setup_arm_irq
c_func
(paren
id|IRQ_TIMER
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
eof
