multiline_comment|/*&n; *  linux/arch/h8300/platform/h8s/generic/timer.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Platform depend Timer Handler&n; *&n; */
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
DECL|macro|REGS
mdefine_line|#define REGS(regs) __REGS(regs)
DECL|macro|__REGS
mdefine_line|#define __REGS(regs) #regs
DECL|function|platform_timer_setup
r_int
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
r_int
r_char
id|mstpcrl
suffix:semicolon
id|mstpcrl
op_assign
id|inb
c_func
(paren
id|MSTPCRL
)paren
suffix:semicolon
multiline_comment|/* Enable timer */
id|mstpcrl
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
id|outb
c_func
(paren
id|mstpcrl
comma
id|MSTPCRL
)paren
suffix:semicolon
id|outb
c_func
(paren
id|H8300_TIMER_COUNT_DATA
comma
id|_8TCORA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|_8TCSR1
)paren
suffix:semicolon
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
id|outb
c_func
(paren
l_int|0x40
op_or
l_int|0x08
op_or
l_int|0x03
comma
id|_8TCR1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|platform_timer_eoi
r_void
id|platform_timer_eoi
c_func
(paren
r_void
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;bclr #6,@&quot;
id|REGS
c_func
(paren
id|_8TCSR1
)paren
l_string|&quot;:8&quot;
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
