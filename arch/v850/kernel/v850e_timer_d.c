multiline_comment|/*&n; * include/asm-v850/v850e_timer_d.c -- `Timer D&squot; component often used&n; *&t;with V850E CPUs&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/v850e_utils.h&gt;
macro_line|#include &lt;asm/v850e_timer_d.h&gt;
multiline_comment|/* Start interval timer TIMER (0-3).  The timer will issue the&n;   corresponding INTCMD interrupt RATE times per second.&n;   This function does not enable the interrupt.  */
DECL|function|v850e_timer_d_configure
r_void
id|v850e_timer_d_configure
(paren
r_int
id|timer
comma
r_int
id|rate
)paren
(brace
r_int
id|divlog2
comma
id|count
suffix:semicolon
multiline_comment|/* Calculate params for timer.  */
r_if
c_cond
(paren
op_logical_neg
id|calc_counter_params
(paren
id|V850E_TIMER_D_BASE_FREQ
comma
id|rate
comma
id|V850E_TIMER_D_TMCD_CS_MIN
comma
id|V850E_TIMER_D_TMCD_CS_MAX
comma
l_int|16
comma
op_amp
id|divlog2
comma
op_amp
id|count
)paren
)paren
id|printk
(paren
id|KERN_WARNING
l_string|&quot;Cannot find interval timer %d setting suitable&quot;
l_string|&quot; for rate of %dHz.&bslash;n&quot;
l_string|&quot;Using rate of %dHz instead.&bslash;n&quot;
comma
id|timer
comma
id|rate
comma
(paren
id|V850E_TIMER_D_BASE_FREQ
op_rshift
id|divlog2
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Do the actual hardware timer initialization:  */
multiline_comment|/* Enable timer.  */
id|V850E_TIMER_D_TMCD
c_func
(paren
id|timer
)paren
op_assign
id|V850E_TIMER_D_TMCD_CAE
suffix:semicolon
multiline_comment|/* Set clock divider.  */
id|V850E_TIMER_D_TMCD
c_func
(paren
id|timer
)paren
op_assign
id|V850E_TIMER_D_TMCD_CAE
op_or
id|V850E_TIMER_D_TMCD_CS
c_func
(paren
id|divlog2
)paren
suffix:semicolon
multiline_comment|/* Set timer compare register.  */
id|V850E_TIMER_D_CMD
c_func
(paren
id|timer
)paren
op_assign
id|count
suffix:semicolon
multiline_comment|/* Start counting.  */
id|V850E_TIMER_D_TMCD
c_func
(paren
id|timer
)paren
op_assign
id|V850E_TIMER_D_TMCD_CAE
op_or
id|V850E_TIMER_D_TMCD_CS
c_func
(paren
id|divlog2
)paren
op_or
id|V850E_TIMER_D_TMCD_CE
suffix:semicolon
)brace
eof
