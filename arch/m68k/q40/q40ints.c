multiline_comment|/*&n; * arch/m68k/q40/q40ints.c&n; *&n; * Copyright (C) 1999,2001 Richard Zidlicky&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * .. used to be loosely based on bvme6000ints.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
macro_line|#include &lt;asm/q40ints.h&gt;
multiline_comment|/* &n; * Q40 IRQs are defined as follows: &n; *            3,4,5,6,7,10,11,14,15 : ISA dev IRQs&n; *            16-31: reserved&n; *            32   : keyboard int&n; *            33   : frame int (50/200 Hz periodic timer)&n; *            34   : sample int (10/20 KHz periodic timer)&n; *          &n;*/
r_extern
r_int
id|ints_inited
suffix:semicolon
id|irqreturn_t
id|q40_irq2_handler
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_extern
id|irqreturn_t
(paren
op_star
id|q40_sys_default_handler
(braket
)braket
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
suffix:semicolon
r_static
id|irqreturn_t
id|q40_defhand
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
id|fp
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|sys_default_handler
c_func
(paren
r_int
id|lev
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
suffix:semicolon
DECL|macro|DEVNAME_SIZE
mdefine_line|#define DEVNAME_SIZE 24
DECL|struct|q40_irq_node
r_static
r_struct
id|q40_irq_node
(brace
DECL|member|handler
id|irqreturn_t
(paren
op_star
id|handler
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
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
multiline_comment|/*        struct q40_irq_node *next;*/
DECL|member|devname
r_char
id|devname
(braket
id|DEVNAME_SIZE
)braket
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|variable|irq_tab
)brace
id|irq_tab
(braket
id|Q40_IRQ_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|q40_ablecount
r_int
r_int
id|q40_ablecount
(braket
id|Q40_IRQ_MAX
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n; * void q40_init_IRQ (void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function is called during kernel startup to initialize&n; * the q40 IRQ handling routines.&n; */
DECL|variable|disabled
r_static
r_int
id|disabled
op_assign
l_int|0
suffix:semicolon
DECL|function|q40_init_IRQ
r_void
id|q40_init_IRQ
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|disabled
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|Q40_IRQ_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_tab
(braket
id|i
)braket
dot
id|handler
op_assign
id|q40_defhand
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&t;&t;irq_tab[i].next = NULL;*/
id|irq_tab
(braket
id|i
)braket
dot
id|devname
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|count
op_assign
l_int|0
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|state
op_assign
l_int|0
suffix:semicolon
id|q40_ablecount
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* all enabled */
)brace
multiline_comment|/* setup handler for ISA ints */
id|sys_request_irq
c_func
(paren
id|IRQ2
comma
id|q40_irq2_handler
comma
l_int|0
comma
l_string|&quot;q40 ISA and master chip&quot;
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* now enable some ints.. */
id|master_outb
c_func
(paren
l_int|1
comma
id|EXT_ENABLE_REG
)paren
suffix:semicolon
multiline_comment|/* ISA IRQ 5-15 */
multiline_comment|/* make sure keyboard IRQ is disabled */
id|master_outb
c_func
(paren
l_int|0
comma
id|KEY_IRQ_ENABLE_REG
)paren
suffix:semicolon
)brace
DECL|function|q40_request_irq
r_int
id|q40_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|irqreturn_t
(paren
op_star
id|handler
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
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
multiline_comment|/*printk(&quot;q40_request_irq %d, %s&bslash;n&quot;,irq,devname);*/
r_if
c_cond
(paren
id|irq
OG
id|Q40_IRQ_MAX
op_logical_or
(paren
id|irq
OG
l_int|15
op_logical_and
id|irq
OL
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* test for ISA ints not implemented by HW */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|8
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|13
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: ISA IRQ %d from %s not implemented by HW&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
r_case
l_int|11
suffix:colon
id|printk
c_func
(paren
l_string|&quot;warning IRQ 10 and 11 not distinguishable&bslash;n&quot;
)paren
suffix:semicolon
id|irq
op_assign
l_int|10
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
OL
id|Q40_IRQ_SAMPLE
)paren
(brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|dev_id
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IRQ %d from %s is not replaceable&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_tab
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*printk(&quot;IRQ %d set to handler %p&bslash;n&quot;,irq,handler);*/
r_if
c_cond
(paren
id|dev_id
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: dev_id == NULL in request_irq&bslash;n&quot;
)paren
suffix:semicolon
id|dev_id
op_assign
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
id|irq_tab
(braket
id|irq
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|strlcpy
c_func
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|devname
comma
id|devname
comma
r_sizeof
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|devname
)paren
)paren
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|state
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Q40_IRQ_SAMPLE :somewhat special actions required here ..*/
id|sys_request_irq
c_func
(paren
l_int|4
comma
id|handler
comma
id|flags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|6
comma
id|handler
comma
id|flags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|q40_free_irq
r_void
id|q40_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|irq
OG
id|Q40_IRQ_MAX
op_logical_or
(paren
id|irq
OG
l_int|15
op_logical_and
id|irq
OL
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d, dev_id %x &bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
(paren
r_int
)paren
id|dev_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* test for ISA ints not implemented by HW */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|8
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|13
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: ISA IRQ %d from %x invalid&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
(paren
r_int
)paren
id|dev_id
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|11
suffix:colon
id|irq
op_assign
l_int|10
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
OL
id|Q40_IRQ_SAMPLE
)paren
(brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_tab
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|handler
op_assign
id|q40_defhand
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* irq_tab[irq].devname = NULL; */
multiline_comment|/* do not reset state !! */
)brace
r_else
(brace
multiline_comment|/* == Q40_IRQ_SAMPLE */
id|sys_free_irq
c_func
(paren
l_int|4
comma
id|dev_id
)paren
suffix:semicolon
id|sys_free_irq
c_func
(paren
l_int|6
comma
id|dev_id
)paren
suffix:semicolon
)brace
)brace
DECL|function|q40_process_int
id|irqreturn_t
id|q40_process_int
(paren
r_int
id|level
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unexpected interrupt %x&bslash;n&quot;
comma
id|level
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* &n; * this stuff doesn&squot;t really belong here..&n;*/
DECL|variable|ql_ticks
r_int
id|ql_ticks
suffix:semicolon
multiline_comment|/* 200Hz ticks since last jiffie */
DECL|variable|sound_ticks
r_static
r_int
id|sound_ticks
suffix:semicolon
DECL|macro|SVOL
mdefine_line|#define SVOL 45
DECL|function|q40_mksound
r_void
id|q40_mksound
c_func
(paren
r_int
r_int
id|hz
comma
r_int
r_int
id|ticks
)paren
(brace
multiline_comment|/* for now ignore hz, except that hz==0 switches off sound */
multiline_comment|/* simply alternate the ampl (128-SVOL)-(128+SVOL)-..-.. at 200Hz */
r_if
c_cond
(paren
id|hz
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sound_ticks
)paren
id|sound_ticks
op_assign
l_int|1
suffix:semicolon
op_star
id|DAC_LEFT
op_assign
l_int|128
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
l_int|128
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* sound itself is done in q40_timer_int */
r_if
c_cond
(paren
id|sound_ticks
op_eq
l_int|0
)paren
id|sound_ticks
op_assign
l_int|1000
suffix:semicolon
multiline_comment|/* pretty long beep */
id|sound_ticks
op_assign
id|ticks
op_lshift
l_int|1
suffix:semicolon
)brace
DECL|variable|q40_timer_routine
r_static
id|irqreturn_t
(paren
op_star
id|q40_timer_routine
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
suffix:semicolon
DECL|function|q40_timer_int
r_static
id|irqreturn_t
id|q40_timer_int
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|ql_ticks
op_assign
id|ql_ticks
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sound_ticks
)paren
(brace
r_int
r_char
id|sval
op_assign
(paren
id|sound_ticks
op_amp
l_int|1
)paren
ques
c_cond
l_int|128
op_minus
id|SVOL
suffix:colon
l_int|128
op_plus
id|SVOL
suffix:semicolon
id|sound_ticks
op_decrement
suffix:semicolon
op_star
id|DAC_LEFT
op_assign
id|sval
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
id|sval
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ql_ticks
)paren
id|q40_timer_routine
c_func
(paren
id|irq
comma
id|dev
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|q40_sched_init
r_void
id|q40_sched_init
(paren
id|irqreturn_t
(paren
op_star
id|timer_routine
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
id|timer_irq
suffix:semicolon
id|q40_timer_routine
op_assign
id|timer_routine
suffix:semicolon
id|timer_irq
op_assign
id|Q40_IRQ_FRAME
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|timer_irq
comma
id|q40_timer_int
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
id|q40_timer_int
)paren
)paren
id|panic
(paren
l_string|&quot;Couldn&squot;t register timer int&quot;
)paren
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|FRAME_CLEAR_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|FRAME_RATE_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * tables to translate bits into IRQ numbers &n; * it is a good idea to order the entries by priority&n; * &n;*/
DECL|struct|IRQ_TABLE
DECL|member|mask
DECL|member|irq
r_struct
id|IRQ_TABLE
(brace
r_int
id|mask
suffix:semicolon
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if 0
r_static
r_struct
id|IRQ_TABLE
id|iirqs
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#endif
DECL|variable|eirqs
r_static
r_struct
id|IRQ_TABLE
id|eirqs
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* complain only this many times about spurious ints : */
DECL|variable|ccleirq
r_static
r_int
id|ccleirq
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* ISA dev IRQ&squot;s*/
multiline_comment|/*static int cclirq=60;*/
multiline_comment|/* internal */
multiline_comment|/* FIXME: add shared ints,mask,unmask,probing.... */
DECL|macro|IRQ_INPROGRESS
mdefine_line|#define IRQ_INPROGRESS 1
multiline_comment|/*static unsigned short saved_mask;*/
singleline_comment|//static int do_tint=0;
DECL|macro|DEBUG_Q40INT
mdefine_line|#define DEBUG_Q40INT
multiline_comment|/*#define IP_USE_DISABLE */
multiline_comment|/* would be nice, but crashes ???? */
DECL|variable|mext_disabled
r_static
r_int
id|mext_disabled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ext irq disabled by master chip? */
DECL|variable|aliased_irq
r_static
r_int
id|aliased_irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* how many times inside handler ?*/
multiline_comment|/* got level 2 interrupt, dispatch to ISA or keyboard/timer IRQs */
DECL|function|q40_irq2_handler
id|irqreturn_t
id|q40_irq2_handler
(paren
r_int
id|vec
comma
r_void
op_star
id|devname
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
id|mir
comma
id|mer
suffix:semicolon
r_int
id|irq
comma
id|i
suffix:semicolon
singleline_comment|//repeat:
id|mir
op_assign
id|master_inb
c_func
(paren
id|IIRQ_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mir
op_amp
id|Q40_IRQ_FRAME_MASK
)paren
(brace
id|irq_tab
(braket
id|Q40_IRQ_FRAME
)braket
dot
id|count
op_increment
suffix:semicolon
id|irq_tab
(braket
id|Q40_IRQ_FRAME
)braket
dot
id|handler
c_func
(paren
id|Q40_IRQ_FRAME
comma
id|irq_tab
(braket
id|Q40_IRQ_FRAME
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|FRAME_CLEAR_REG
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mir
op_amp
id|Q40_IRQ_SER_MASK
)paren
op_logical_or
(paren
id|mir
op_amp
id|Q40_IRQ_EXT_MASK
)paren
)paren
(brace
id|mer
op_assign
id|master_inb
c_func
(paren
id|EIRQ_REG
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|eirqs
(braket
id|i
)braket
dot
id|mask
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mer
op_amp
(paren
id|eirqs
(braket
id|i
)braket
dot
id|mask
)paren
)paren
(brace
id|irq
op_assign
id|eirqs
(braket
id|i
)braket
dot
id|irq
suffix:semicolon
multiline_comment|/*&n; * There is a little mess wrt which IRQ really caused this irq request. The&n; * main problem is that IIRQ_REG and EIRQ_REG reflect the state when they&n; * are read - which is long after the request came in. In theory IRQs should&n; * not just go away but they occassionally do&n; */
r_if
c_cond
(paren
id|irq
OG
l_int|4
op_logical_and
id|irq
op_le
l_int|15
op_logical_and
id|mext_disabled
)paren
(brace
multiline_comment|/*aliased_irq++;*/
r_goto
id|iirq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|handler
op_eq
id|q40_defhand
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;handler for IRQ %d not defined&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* ignore uninited INTs :-( */
)brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
)braket
dot
id|state
op_amp
id|IRQ_INPROGRESS
)paren
(brace
multiline_comment|/* some handlers do local_irq_enable() for irq latency reasons, */
multiline_comment|/* however reentering an active irq handler is not permitted */
macro_line|#ifdef IP_USE_DISABLE
multiline_comment|/* in theory this is the better way to do it because it still */
multiline_comment|/* lets through eg the serial irqs, unfortunately it crashes */
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|disabled
op_assign
l_int|1
suffix:semicolon
macro_line|#else
multiline_comment|/*printk(&quot;IRQ_INPROGRESS detected for irq %d, disabling - %s disabled&bslash;n&quot;,irq,disabled ? &quot;already&quot; : &quot;not yet&quot;); */
id|fp-&gt;sr
op_assign
(paren
(paren
(paren
id|fp-&gt;sr
)paren
op_amp
(paren
op_complement
l_int|0x700
)paren
)paren
op_plus
l_int|0x200
)paren
suffix:semicolon
id|disabled
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_goto
id|iirq
suffix:semicolon
)brace
id|irq_tab
(braket
id|irq
)braket
dot
id|count
op_increment
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|state
op_or_assign
id|IRQ_INPROGRESS
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|handler
c_func
(paren
id|irq
comma
id|irq_tab
(braket
id|irq
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
id|irq_tab
(braket
id|irq
)braket
dot
id|state
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/* naively enable everything, if that fails than    */
multiline_comment|/* this function will be reentered immediately thus */
multiline_comment|/* getting another chance to disable the IRQ        */
r_if
c_cond
(paren
id|disabled
)paren
(brace
macro_line|#ifdef IP_USE_DISABLE
r_if
c_cond
(paren
id|irq
OG
l_int|4
)paren
(brace
id|disabled
op_assign
l_int|0
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#else
id|disabled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*printk(&quot;reenabling irq %d&bslash;n&quot;,irq); */
macro_line|#endif
)brace
singleline_comment|// used to do &squot;goto repeat;&squot; her, this delayed bh processing too long
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mer
op_logical_and
id|ccleirq
OG
l_int|0
op_logical_and
op_logical_neg
id|aliased_irq
)paren
id|printk
c_func
(paren
l_string|&quot;ISA interrupt from unknown source? EIRQ_REG = %x&bslash;n&quot;
comma
id|mer
)paren
comma
id|ccleirq
op_decrement
suffix:semicolon
)brace
id|iirq
suffix:colon
id|mir
op_assign
id|master_inb
c_func
(paren
id|IIRQ_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mir
op_amp
id|Q40_IRQ_KEYB_MASK
)paren
(brace
id|irq_tab
(braket
id|Q40_IRQ_KEYBOARD
)braket
dot
id|count
op_increment
suffix:semicolon
id|irq_tab
(braket
id|Q40_IRQ_KEYBOARD
)braket
dot
id|handler
c_func
(paren
id|Q40_IRQ_KEYBOARD
comma
id|irq_tab
(braket
id|Q40_IRQ_KEYBOARD
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|show_q40_interrupts
r_int
id|show_q40_interrupts
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|Q40_IRQ_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|i
)braket
dot
id|count
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%sIRQ %02d: %8d  %s%s&bslash;n&quot;
comma
(paren
id|i
op_le
l_int|15
)paren
ques
c_cond
l_string|&quot;ISA-&quot;
suffix:colon
l_string|&quot;    &quot;
comma
id|i
comma
id|irq_tab
(braket
id|i
)braket
dot
id|count
comma
id|irq_tab
(braket
id|i
)braket
dot
id|devname
(braket
l_int|0
)braket
ques
c_cond
id|irq_tab
(braket
id|i
)braket
dot
id|devname
suffix:colon
l_string|&quot;?&quot;
comma
id|irq_tab
(braket
id|i
)braket
dot
id|handler
op_eq
id|q40_defhand
ques
c_cond
l_string|&quot; (now unassigned)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|q40_defhand
r_static
id|irqreturn_t
id|q40_defhand
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
id|fp
)paren
(brace
id|printk
(paren
l_string|&quot;Unknown q40 interrupt 0x%02x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
DECL|function|sys_default_handler
r_static
id|irqreturn_t
id|sys_default_handler
c_func
(paren
r_int
id|lev
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
id|printk
(paren
l_string|&quot;Uninitialised interrupt level %d&bslash;n&quot;
comma
id|lev
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
DECL|variable|q40_sys_default_handler
id|irqreturn_t
(paren
op_star
id|q40_sys_default_handler
(braket
id|SYS_IRQS
)braket
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
(brace
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
comma
id|sys_default_handler
)brace
suffix:semicolon
DECL|function|q40_enable_irq
r_void
id|q40_enable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ge
l_int|5
op_logical_and
id|irq
op_le
l_int|15
)paren
(brace
id|mext_disabled
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|mext_disabled
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;q40_enable_irq : nested disable/enable&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mext_disabled
op_eq
l_int|0
)paren
id|master_outb
c_func
(paren
l_int|1
comma
id|EXT_ENABLE_REG
)paren
suffix:semicolon
)brace
)brace
DECL|function|q40_disable_irq
r_void
id|q40_disable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/* disable ISA iqs : only do something if the driver has been&n;   * verified to be Q40 &quot;compatible&quot; - right now IDE, NE2K&n;   * Any driver should not attempt to sleep across disable_irq !!&n;   */
r_if
c_cond
(paren
id|irq
op_ge
l_int|5
op_logical_and
id|irq
op_le
l_int|15
)paren
(brace
id|master_outb
c_func
(paren
l_int|0
comma
id|EXT_ENABLE_REG
)paren
suffix:semicolon
id|mext_disabled
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|mext_disabled
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;disable_irq nesting count %d&bslash;n&quot;
comma
id|mext_disabled
)paren
suffix:semicolon
)brace
)brace
DECL|function|q40_probe_irq_on
r_int
r_int
id|q40_probe_irq_on
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;irq probing not working - reconfigure the driver to avoid this&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|q40_probe_irq_off
r_int
id|q40_probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; * compile-command: &quot;m68k-linux-gcc -D__KERNEL__ -I/home/rz/lx/linux-2.2.6/include -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -pipe -fno-strength-reduce -ffixed-a2 -m68040   -c -o q40ints.o q40ints.c&quot;&n; * End:&n; */
eof
