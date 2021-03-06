multiline_comment|/****************************************************************************/
multiline_comment|/* &n; * linux/arch/sh/boards/snapgear/setup.c&n; *&n; * Copyright (C) 2002  David McCullough &lt;davidm@snapgear.com&gt;&n; * Copyright (C) 2003  Paul Mundt &lt;lethal@linux-sh.org&gt;&n; *&n; * Based on files with the following comments:&n; *&n; *           Copyright (C) 2000  Kazumoto Kojima&n; *&n; *           Modified for 7751 Solution Engine by&n; *           Ian da Silva and Jeremy Siegel, 2001.&n; */
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/mach/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/cpu/timer.h&gt;
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|secureedge5410_rtc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; * EraseConfig handling functions&n; */
DECL|function|eraseconfig_interrupt
r_static
id|irqreturn_t
id|eraseconfig_interrupt
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
r_volatile
r_char
id|dummy
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
op_star
(paren
r_volatile
r_char
op_star
)paren
l_int|0xb8000000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SnapGear: erase switch interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|eraseconfig_init
r_static
r_int
id|__init
id|eraseconfig_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SnapGear: EraseConfig init&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Setup &quot;EraseConfig&quot; switch on external IRQ 0 */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRL0_IRQ
comma
id|eraseconfig_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;Erase Config&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;SnapGear: failed to register IRQ%d for Reset witch&bslash;n&quot;
comma
id|IRL0_IRQ
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;SnapGear: registered EraseConfig switch on IRQ%d&bslash;n&quot;
comma
id|IRL0_IRQ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|eraseconfig_init
id|module_init
c_func
(paren
id|eraseconfig_init
)paren
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; * Initialize IRQ setting&n; *&n; * IRL0 = erase switch&n; * IRL1 = eth0&n; * IRL2 = eth1&n; * IRL3 = crypto&n; */
DECL|function|init_snapgear_IRQ
r_static
r_void
id|__init
id|init_snapgear_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* enable individual interrupt mode for externals */
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|INTC_ICR
)paren
op_or
id|INTC_ICR_IRLM
comma
id|INTC_ICR
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Setup SnapGear IRQ/IPR ...&bslash;n&quot;
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|IRL0_IRQ
comma
id|IRL0_IPR_ADDR
comma
id|IRL0_IPR_POS
comma
id|IRL0_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|IRL1_IRQ
comma
id|IRL1_IPR_ADDR
comma
id|IRL1_IPR_POS
comma
id|IRL1_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|IRL2_IRQ
comma
id|IRL2_IPR_ADDR
comma
id|IRL2_IPR_POS
comma
id|IRL2_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|IRL3_IRQ
comma
id|IRL3_IPR_ADDR
comma
id|IRL3_IPR_POS
comma
id|IRL3_PRIORITY
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Fast poll interrupt simulator.&n; */
multiline_comment|/*&n; * Leave all of the fast timer/fast poll stuff commented out for now, since&n; * it&squot;s not clear whether it actually works or not. Since it wasn&squot;t being used&n; * at all in 2.4, we&squot;ll assume it&squot;s not sane for 2.6 either.. -- PFM&n; */
macro_line|#if 0
mdefine_line|#define FAST_POLL&t;1000
singleline_comment|//#define FAST_POLL_INTR
mdefine_line|#define FASTTIMER_IRQ   17
mdefine_line|#define FASTTIMER_IPR_ADDR  INTC_IPRA
mdefine_line|#define FASTTIMER_IPR_POS    2
mdefine_line|#define FASTTIMER_PRIORITY   3
macro_line|#ifdef FAST_POLL_INTR
mdefine_line|#define TMU1_TCR_INIT&t;0x0020
macro_line|#else
mdefine_line|#define TMU1_TCR_INIT&t;0
macro_line|#endif
mdefine_line|#define TMU_TSTR_INIT&t;1
mdefine_line|#define TMU1_TCR_CALIB&t;0x0000
macro_line|#ifdef FAST_POLL_INTR
r_static
r_void
id|fast_timer_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|timer_status
suffix:semicolon
id|timer_status
op_assign
id|ctrl_inw
c_func
(paren
id|TMU1_TCR
)paren
suffix:semicolon
id|timer_status
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|timer_status
comma
id|TMU1_TCR
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * return the current ticks on the fast timer&n; */
r_int
r_int
id|fast_timer_count
c_func
(paren
r_void
)paren
(brace
r_return
id|ctrl_inl
c_func
(paren
id|TMU1_TCNT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * setup a fast timer for profiling etc etc&n; */
r_static
r_void
id|setup_fast_timer
c_func
(paren
)paren
(brace
r_int
r_int
id|interval
suffix:semicolon
macro_line|#ifdef FAST_POLL_INTR
id|interval
op_assign
(paren
id|current_cpu_data.module_clock
op_div
l_int|4
op_plus
id|FAST_POLL
op_div
l_int|2
)paren
op_div
id|FAST_POLL
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|FASTTIMER_IRQ
comma
id|FASTTIMER_IPR_ADDR
comma
id|FASTTIMER_IPR_POS
comma
id|FASTTIMER_PRIORITY
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SnapGear: %dHz fast timer on IRQ %d&bslash;n&quot;
comma
id|FAST_POLL
comma
id|FASTTIMER_IRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|FASTTIMER_IRQ
comma
id|fast_timer_irq
comma
l_int|0
comma
l_string|&quot;SnapGear fast timer&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s(%d): request_irq() failed?&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;SnapGear: fast timer running&bslash;n&quot;
comma
id|FAST_POLL
comma
id|FASTTIMER_IRQ
)paren
suffix:semicolon
id|interval
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#endif
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TMU_TSTR
)paren
op_amp
op_complement
l_int|0x2
comma
id|TMU_TSTR
)paren
suffix:semicolon
multiline_comment|/* disable timer 1 */
id|ctrl_outw
c_func
(paren
id|TMU1_TCR_INIT
comma
id|TMU1_TCR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU1_TCOR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU1_TCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|ctrl_inb
c_func
(paren
id|TMU_TSTR
)paren
op_or
l_int|0x2
comma
id|TMU_TSTR
)paren
suffix:semicolon
multiline_comment|/* enable timer 1 */
id|printk
c_func
(paren
l_string|&quot;Timer count 1 = 0x%x&bslash;n&quot;
comma
id|fast_timer_count
c_func
(paren
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Timer count 2 = 0x%x&bslash;n&quot;
comma
id|fast_timer_count
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/****************************************************************************/
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;SnapGear SecureEdge5410&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_snapgear
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|72
comma
dot
id|mv_inb
op_assign
id|snapgear_inb
comma
dot
id|mv_inw
op_assign
id|snapgear_inw
comma
dot
id|mv_inl
op_assign
id|snapgear_inl
comma
dot
id|mv_outb
op_assign
id|snapgear_outb
comma
dot
id|mv_outw
op_assign
id|snapgear_outw
comma
dot
id|mv_outl
op_assign
id|snapgear_outl
comma
dot
id|mv_inb_p
op_assign
id|snapgear_inb_p
comma
dot
id|mv_inw_p
op_assign
id|snapgear_inw
comma
dot
id|mv_inl_p
op_assign
id|snapgear_inl
comma
dot
id|mv_outb_p
op_assign
id|snapgear_outb_p
comma
dot
id|mv_outw_p
op_assign
id|snapgear_outw
comma
dot
id|mv_outl_p
op_assign
id|snapgear_outl
comma
dot
id|mv_isa_port2addr
op_assign
id|snapgear_isa_port2addr
comma
dot
id|mv_init_irq
op_assign
id|init_snapgear_IRQ
comma
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|snapgear
)paren
multiline_comment|/*&n; * Initialize the board&n; */
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
id|board_time_init
op_assign
id|secureedge5410_rtc_init
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
