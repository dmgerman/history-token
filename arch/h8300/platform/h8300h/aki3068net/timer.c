multiline_comment|/*&n; *  linux/arch/h8300/platform/h8300h/aki3068net/timer.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourcefoge.jp&gt;&n; *&n; *  Platform depend Timer Handler&n; *&n; */
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
macro_line|#include &lt;asm/regs306x.h&gt;
DECL|macro|CMFA
mdefine_line|#define CMFA 6
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
id|outb
c_func
(paren
id|H8300_TIMER_COUNT_DATA
comma
id|TCORA2
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|_8TCSR2
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|40
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
id|_8TCR2
)paren
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
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|_8TCSR2
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
