multiline_comment|/*&n; *  linux/arch/m68k/hp300/time.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific time handling code.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &quot;ints.h&quot;
multiline_comment|/* Clock hardware definitions */
DECL|macro|CLOCKBASE
mdefine_line|#define CLOCKBASE&t;0xf05f8000
DECL|macro|CLKCR1
mdefine_line|#define&t;CLKCR1&t;&t;0x1
DECL|macro|CLKCR2
mdefine_line|#define&t;CLKCR2&t;&t;0x3
DECL|macro|CLKCR3
mdefine_line|#define&t;CLKCR3&t;&t;CLKCR1
DECL|macro|CLKSR
mdefine_line|#define&t;CLKSR&t;&t;CLKCR2
DECL|macro|CLKMSB1
mdefine_line|#define&t;CLKMSB1&t;&t;0x5
DECL|macro|CLKMSB2
mdefine_line|#define&t;CLKMSB2&t;&t;0x9
DECL|macro|CLKMSB3
mdefine_line|#define&t;CLKMSB3&t;&t;0xD
multiline_comment|/* This is for machines which generate the exact clock. */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY (1000000/HZ)
DECL|macro|INTVAL
mdefine_line|#define INTVAL ((10000 / 4) - 1)
DECL|function|hp300_tick
r_static
id|irqreturn_t
id|hp300_tick
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
id|tmp
suffix:semicolon
id|irqreturn_t
(paren
op_star
id|vector
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
op_assign
id|dev_id
suffix:semicolon
id|in_8
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKSR
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movpw %1@(5),%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|CLOCKBASE
)paren
)paren
suffix:semicolon
r_return
id|vector
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|hp300_gettimeoffset
r_int
r_int
id|hp300_gettimeoffset
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Read current timer 1 value */
r_int
r_char
id|lsb
comma
id|msb1
comma
id|msb2
suffix:semicolon
r_int
r_int
id|ticks
suffix:semicolon
id|msb1
op_assign
id|in_8
c_func
(paren
id|CLOCKBASE
op_plus
l_int|5
)paren
suffix:semicolon
id|lsb
op_assign
id|in_8
c_func
(paren
id|CLOCKBASE
op_plus
l_int|7
)paren
suffix:semicolon
id|msb2
op_assign
id|in_8
c_func
(paren
id|CLOCKBASE
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msb1
op_ne
id|msb2
)paren
multiline_comment|/* A carry happened while we were reading.  Read it again */
id|lsb
op_assign
id|in_8
c_func
(paren
id|CLOCKBASE
op_plus
l_int|7
)paren
suffix:semicolon
id|ticks
op_assign
id|INTVAL
op_minus
(paren
(paren
id|msb2
op_lshift
l_int|8
)paren
op_or
id|lsb
)paren
suffix:semicolon
r_return
(paren
id|USECS_PER_JIFFY
op_star
id|ticks
)paren
op_div
id|INTVAL
suffix:semicolon
)brace
DECL|function|hp300_sched_init
r_void
id|__init
id|hp300_sched_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|vector
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
id|out_8
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKCR2
comma
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* select CR1 */
id|out_8
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKCR1
comma
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* reset */
id|asm
r_volatile
(paren
l_string|&quot; movpw %0,%1@(5)&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|INTVAL
)paren
comma
l_string|&quot;a&quot;
(paren
id|CLOCKBASE
)paren
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|6
comma
id|hp300_tick
comma
id|IRQ_FLG_STD
comma
l_string|&quot;timer tick&quot;
comma
id|vector
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKCR2
comma
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* select CR1 */
id|out_8
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKCR1
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* enable irq */
)brace
eof
