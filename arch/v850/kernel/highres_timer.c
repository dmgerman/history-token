multiline_comment|/*&n; * arch/v850/kernel/highres_timer.c -- High resolution timing routines&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/nb85e_timer_d.h&gt;
macro_line|#include &lt;asm/highres_timer.h&gt;
DECL|macro|HIGHRES_TIMER_USEC_SHIFT
mdefine_line|#define HIGHRES_TIMER_USEC_SHIFT   12
multiline_comment|/* Pre-calculated constant used for converting ticks to real time&n;   units.  We initialize it to prevent it being put into BSS.  */
DECL|variable|highres_timer_usec_prescale
r_static
id|u32
id|highres_timer_usec_prescale
op_assign
l_int|1
suffix:semicolon
r_void
id|highres_timer_slow_tick_irq
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|highres_timer_slow_tick_irq
r_void
id|highres_timer_slow_tick_irq
(paren
r_void
)paren
(brace
multiline_comment|/* This is an interrupt handler, so it must be very careful to&n;&t;   not to trash any registers.  At this point, the stack-pointer&n;&t;   (r3) has been saved in the chip ram location ENTRY_SP by the&n;&t;   interrupt vector, so we can use it as a scratch register; we&n;&t;   must also restore it before returning.  */
id|asm
(paren
l_string|&quot;ld.w&t;%0[r0], sp;&quot;
l_string|&quot;add&t;1, sp;&quot;
l_string|&quot;st.w&t;sp, %0[r0];&quot;
l_string|&quot;ld.w&t;%1[r0], sp;&quot;
multiline_comment|/* restore pre-irq stack-pointer */
l_string|&quot;reti&quot;
op_scope_resolution
l_string|&quot;i&quot;
(paren
id|HIGHRES_TIMER_SLOW_TICKS_ADDR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ENTRY_SP_ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|highres_timer_reset
r_void
id|highres_timer_reset
(paren
r_void
)paren
(brace
id|NB85E_TIMER_D_TMD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
op_assign
l_int|0
suffix:semicolon
id|HIGHRES_TIMER_SLOW_TICKS
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|highres_timer_start
r_void
id|highres_timer_start
(paren
r_void
)paren
(brace
id|u32
id|fast_tick_rate
suffix:semicolon
multiline_comment|/* Start hardware timer.  */
id|nb85e_timer_d_configure
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
comma
id|HIGHRES_TIMER_SLOW_TICK_RATE
)paren
suffix:semicolon
id|fast_tick_rate
op_assign
(paren
id|NB85E_TIMER_D_BASE_FREQ
op_rshift
id|NB85E_TIMER_D_DIVLOG2
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
)paren
suffix:semicolon
multiline_comment|/* The obvious way of calculating microseconds from fast ticks&n;&t;   is to do:&n;&n;&t;     usec = fast_ticks * 10^6 / fast_tick_rate&n;&n;&t;   However, divisions are much slower than multiplications, and&n;&t;   the above calculation can overflow, so we do this instead:&n;&n;&t;     usec = fast_ticks * (10^6 * 2^12 / fast_tick_rate) / 2^12&n;&n;           since we can pre-calculate (10^6 * (2^12 / fast_tick_rate))&n;&t;   and use a shift for dividing by 2^12, this avoids division,&n;&t;   and is almost as accurate (it differs by about 2 microseconds&n;&t;   at the extreme value of the fast-tick counter&squot;s ranger).  */
id|highres_timer_usec_prescale
op_assign
(paren
(paren
l_int|1000000
op_lshift
id|HIGHRES_TIMER_USEC_SHIFT
)paren
op_div
id|fast_tick_rate
)paren
suffix:semicolon
multiline_comment|/* Enable the interrupt (which is hardwired to this use), and&n;&t;   give it the highest priority.  */
id|NB85E_INTC_IC
(paren
id|IRQ_INTCMD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|highres_timer_stop
r_void
id|highres_timer_stop
(paren
r_void
)paren
(brace
multiline_comment|/* Stop the timer.  */
id|NB85E_TIMER_D_TMCD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
op_assign
id|NB85E_TIMER_D_TMCD_CAE
suffix:semicolon
multiline_comment|/* Disable its interrupt, just in case.  */
id|nb85e_intc_disable_irq
(paren
id|IRQ_INTCMD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
)paren
suffix:semicolon
)brace
DECL|function|highres_timer_read_ticks
r_inline
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
(brace
r_int
id|flags
suffix:semicolon
id|u32
id|fast_ticks_1
comma
id|fast_ticks_2
comma
id|_slow_ticks
suffix:semicolon
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
id|fast_ticks_1
op_assign
id|NB85E_TIMER_D_TMD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
suffix:semicolon
id|_slow_ticks
op_assign
id|HIGHRES_TIMER_SLOW_TICKS
suffix:semicolon
id|fast_ticks_2
op_assign
id|NB85E_TIMER_D_TMD
(paren
id|HIGHRES_TIMER_TIMER_D_UNIT
)paren
suffix:semicolon
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fast_ticks_2
OL
id|fast_ticks_1
)paren
id|_slow_ticks
op_increment
suffix:semicolon
op_star
id|slow_ticks
op_assign
id|_slow_ticks
suffix:semicolon
op_star
id|fast_ticks
op_assign
id|fast_ticks_2
suffix:semicolon
)brace
DECL|function|highres_timer_ticks_to_timeval
r_inline
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
(brace
r_int
r_int
id|sec
comma
id|sec_rem
comma
id|usec
suffix:semicolon
id|usec
op_assign
(paren
(paren
id|fast_ticks
op_star
id|highres_timer_usec_prescale
)paren
op_rshift
id|HIGHRES_TIMER_USEC_SHIFT
)paren
suffix:semicolon
id|sec
op_assign
id|slow_ticks
op_div
id|HIGHRES_TIMER_SLOW_TICK_RATE
suffix:semicolon
id|sec_rem
op_assign
id|slow_ticks
op_mod
id|HIGHRES_TIMER_SLOW_TICK_RATE
suffix:semicolon
id|usec
op_add_assign
id|sec_rem
op_star
(paren
l_int|1000000
op_div
id|HIGHRES_TIMER_SLOW_TICK_RATE
)paren
suffix:semicolon
id|tv-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
suffix:semicolon
)brace
DECL|function|highres_timer_read
r_void
id|highres_timer_read
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|u32
id|fast_ticks
comma
id|slow_ticks
suffix:semicolon
id|highres_timer_read_ticks
(paren
op_amp
id|slow_ticks
comma
op_amp
id|fast_ticks
)paren
suffix:semicolon
id|highres_timer_ticks_to_timeval
(paren
id|slow_ticks
comma
id|fast_ticks
comma
id|tv
)paren
suffix:semicolon
)brace
eof
