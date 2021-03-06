multiline_comment|/*&n; *  linux/arch/h8300/platform/h8s/edosk2674/timer.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Platform depend Timer Handler&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/regs267x.h&gt;
DECL|macro|CMFA
mdefine_line|#define CMFA 6
DECL|macro|CMIEA
mdefine_line|#define CMIEA 0x40
DECL|macro|CCLR_CMA
mdefine_line|#define CCLR_CMA 0x08
DECL|macro|CLK_DIV8192
mdefine_line|#define CLK_DIV8192 0x03
DECL|macro|H8300_TIMER_FREQ
mdefine_line|#define H8300_TIMER_FREQ CONFIG_CPU_CLOCK*1000/8192 /* Timer input freq. */
DECL|function|platform_timer_setup
r_void
id|__init
id|platform_timer_setup
c_func
(paren
id|irqreturn_t
(paren
op_star
id|timer_int
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
multiline_comment|/* 8bit timer module enabled */
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|MSTPCRL
)paren
op_amp
op_complement
l_int|0x01
comma
id|MSTPCRL
)paren
suffix:semicolon
multiline_comment|/* setup 8bit timer ch1 */
id|ctrl_outb
c_func
(paren
id|H8300_TIMER_FREQ
op_div
id|HZ
comma
id|_8TCORA1
)paren
suffix:semicolon
multiline_comment|/* set interval */
id|ctrl_outb
c_func
(paren
l_int|0x00
comma
id|_8TCSR1
)paren
suffix:semicolon
multiline_comment|/* no output */
id|request_irq
c_func
(paren
l_int|76
comma
id|timer_int
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|0
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|CMIEA
op_or
id|CCLR_CMA
op_or
id|CLK_DIV8192
comma
id|_8TCR1
)paren
suffix:semicolon
multiline_comment|/* start count */
)brace
DECL|function|platform_timer_eoi
r_void
id|platform_timer_eoi
c_func
(paren
r_void
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|_8TCSR1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|CMFA
)paren
suffix:semicolon
)brace
DECL|function|platform_gettod
r_void
id|platform_gettod
c_func
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
(brace
multiline_comment|/* FIXME! not RTC support */
op_star
id|year
op_assign
op_star
id|mon
op_assign
op_star
id|day
op_assign
op_star
id|hour
op_assign
op_star
id|min
op_assign
op_star
id|sec
op_assign
l_int|0
suffix:semicolon
)brace
eof
