multiline_comment|/*&n; *  linux/arch/h8300/platform/h8300h/generic/timer.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Platform depend Timer Handler&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#if defined(CONFIG_H83007) || defined(CONFIG_H83068)
macro_line|#include &lt;asm/regs306x.h&gt;
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
multiline_comment|/* setup 8bit timer ch2 */
id|ctrl_outb
c_func
(paren
id|H8300_TIMER_FREQ
op_div
id|HZ
comma
id|TCORA2
)paren
suffix:semicolon
multiline_comment|/* set interval */
id|ctrl_outb
c_func
(paren
l_int|0x00
comma
id|_8TCSR2
)paren
suffix:semicolon
multiline_comment|/* no output */
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
id|ctrl_outb
c_func
(paren
id|CMIEA
op_or
id|CCLR_CMA
op_or
id|CLK_DIV8192
comma
id|_8TCR2
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
macro_line|#endif
macro_line|#if defined(CONFIG_H83002) || defined(CONFIG_H83048)
multiline_comment|/* FIXME! */
DECL|macro|TSTR
mdefine_line|#define TSTR 0x00ffff60
DECL|macro|TSNC
mdefine_line|#define TSNC 0x00ffff61
DECL|macro|TMDR
mdefine_line|#define TMDR 0x00ffff62
DECL|macro|TFCR
mdefine_line|#define TFCR 0x00ffff63
DECL|macro|TOER
mdefine_line|#define TOER 0x00ffff90
DECL|macro|TOCR
mdefine_line|#define TOCR 0x00ffff91
multiline_comment|/* ITU0 */
DECL|macro|TCR
mdefine_line|#define TCR  0x00ffff64
DECL|macro|TIOR
mdefine_line|#define TIOR 0x00ffff65
DECL|macro|TIER
mdefine_line|#define TIER 0x00ffff66
DECL|macro|TSR
mdefine_line|#define TSR  0x00ffff67
DECL|macro|TCNT
mdefine_line|#define TCNT 0x00ffff68
DECL|macro|GRA
mdefine_line|#define GRA  0x00ffff6a
DECL|macro|GRB
mdefine_line|#define GRB  0x00ffff6c
DECL|macro|CCLR_CMGRA
mdefine_line|#define CCLR_CMGRA 0x20
DECL|macro|CLK_DIV8
mdefine_line|#define CLK_DIV8 0x03
DECL|macro|H8300_TIMER_FREQ
mdefine_line|#define H8300_TIMER_FREQ CONFIG_CPU_CLOCK*1000/8 /* Timer input freq. */
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
op_star
(paren
r_int
r_int
op_star
)paren
id|GRA
op_assign
id|H8300_TIMER_FREQ
op_div
id|HZ
suffix:semicolon
multiline_comment|/* set interval */
op_star
(paren
r_int
r_int
op_star
)paren
id|TCNT
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear counter */
id|ctrl_outb
c_func
(paren
l_int|0x80
op_or
id|CCLR_CMGRA
op_or
id|CLK_DIV8
comma
id|TCR
)paren
suffix:semicolon
multiline_comment|/* set ITU0 clock */
id|ctrl_outb
c_func
(paren
l_int|0x88
comma
id|TIOR
)paren
suffix:semicolon
multiline_comment|/* no output */
id|request_irq
c_func
(paren
l_int|26
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
l_int|0xf9
comma
id|TIER
)paren
suffix:semicolon
multiline_comment|/* compare match GRA interrupt */
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TSNC
)paren
op_amp
op_complement
l_int|0x01
comma
id|TSNC
)paren
suffix:semicolon
multiline_comment|/* ITU0 async */
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TMDR
)paren
op_amp
op_complement
l_int|0x01
comma
id|TMDR
)paren
suffix:semicolon
multiline_comment|/* ITU0 normal mode */
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TSTR
)paren
op_or
l_int|0x01
comma
id|TSTR
)paren
suffix:semicolon
multiline_comment|/* ITU0 Start */
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
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TSR
)paren
op_amp
op_complement
l_int|0x01
comma
id|TSR
)paren
suffix:semicolon
)brace
macro_line|#endif
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
