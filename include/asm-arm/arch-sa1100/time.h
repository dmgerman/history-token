multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/time.h&n; *&n; * Copyright (C) 1998 Deborah Wallach.&n; * Twiddles  (C) 1999 &t;Hugo Fiennes &lt;hugo@empeg.com&gt;&n; * &n; * 2000/03/29 (C) Nicolas Pitre &lt;nico@cam.org&gt;&n; *&t;Rewritten: big cleanup, much simpler, better HZ accuracy.&n; *&n; */
DECL|macro|RTC_DEF_DIVIDER
mdefine_line|#define RTC_DEF_DIVIDER&t;&t;(32768 - 1)
DECL|macro|RTC_DEF_TRIM
mdefine_line|#define RTC_DEF_TRIM            0
DECL|function|sa1100_get_rtc_time
r_static
r_int
r_int
id|__init
id|sa1100_get_rtc_time
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * According to the manual we should be able to let RTTR be zero&n;&t; * and then a default diviser for a 32.768KHz clock is used.&n;&t; * Apparently this doesn&squot;t work, at least for my SA1110 rev 5.&n;&t; * If the clock divider is uninitialized then reset it to the&n;&t; * default value to get the 1Hz clock.&n;&t; */
r_if
c_cond
(paren
id|RTTR
op_eq
l_int|0
)paren
(brace
id|RTTR
op_assign
id|RTC_DEF_DIVIDER
op_plus
(paren
id|RTC_DEF_TRIM
op_lshift
l_int|16
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: uninitialized Real Time Clock&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* The current RTC value probably doesn&squot;t make sense either */
id|RCNR
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|RCNR
suffix:semicolon
)brace
DECL|function|sa1100_set_rtc
r_static
r_int
id|sa1100_set_rtc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|current_time
op_assign
id|xtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|RTSR
op_amp
id|RTSR_ALE
)paren
(brace
multiline_comment|/* make sure not to forward the clock over an alarm */
r_int
r_int
id|alarm
op_assign
id|RTAR
suffix:semicolon
r_if
c_cond
(paren
id|current_time
op_ge
id|alarm
op_logical_and
id|alarm
op_ge
id|RCNR
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|RCNR
op_assign
id|current_time
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* IRQs are disabled before entering here from do_gettimeofday() */
DECL|function|sa1100_gettimeoffset
r_static
r_int
r_int
id|sa1100_gettimeoffset
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks_to_match
comma
id|elapsed
comma
id|usec
suffix:semicolon
multiline_comment|/* Get ticks before next timer match */
id|ticks_to_match
op_assign
id|OSMR0
op_minus
id|OSCR
suffix:semicolon
multiline_comment|/* We need elapsed ticks since last match */
id|elapsed
op_assign
id|LATCH
op_minus
id|ticks_to_match
suffix:semicolon
multiline_comment|/* Now convert them to usec */
id|usec
op_assign
(paren
r_int
r_int
)paren
(paren
id|elapsed
op_star
(paren
id|tick_nsec
op_div
l_int|1000
)paren
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|usec
suffix:semicolon
)brace
multiline_comment|/*&n; * We will be entered with IRQs enabled.&n; *&n; * Loop until we get ahead of the free running timer.&n; * This ensures an exact clock tick count and time accuracy.&n; * IRQs are disabled inside the loop to ensure coherence between&n; * lost_ticks (updated in do_timer()) and the match reg value, so we&n; * can use do_gettimeofday() from interrupt handlers.&n; */
DECL|function|sa1100_timer_interrupt
r_static
r_void
id|sa1100_timer_interrupt
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
r_int
r_int
id|next_match
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_do
(brace
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|OSSR
op_assign
id|OSSR_M0
suffix:semicolon
multiline_comment|/* Clear match on timer 0 */
id|next_match
op_assign
(paren
id|OSMR0
op_add_assign
id|LATCH
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|do_set_rtc
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
(paren
id|next_match
op_minus
id|OSCR
)paren
op_le
l_int|0
)paren
suffix:semicolon
id|do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|gettimeoffset
op_assign
id|sa1100_gettimeoffset
suffix:semicolon
id|set_rtc
op_assign
id|sa1100_set_rtc
suffix:semicolon
id|xtime.tv_sec
op_assign
id|sa1100_get_rtc_time
c_func
(paren
)paren
suffix:semicolon
id|timer_irq.handler
op_assign
id|sa1100_timer_interrupt
suffix:semicolon
id|OSMR0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set initial match at 0 */
id|OSSR
op_assign
l_int|0xf
suffix:semicolon
multiline_comment|/* clear status on all timers */
id|setup_irq
c_func
(paren
id|IRQ_OST0
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
id|OIER
op_or_assign
id|OIER_E0
suffix:semicolon
multiline_comment|/* enable match on timer 0 to cause interrupts */
id|OSCR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize free-running timer, force first match */
)brace
eof
