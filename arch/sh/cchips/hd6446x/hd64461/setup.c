multiline_comment|/*&n; *&t;$Id: setup.c,v 1.5 2004/03/16 00:07:50 lethal Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Hitachi HD64461 companion chip support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hd64461/hd64461.h&gt;
DECL|function|disable_hd64461_irq
r_static
r_void
id|disable_hd64461_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|nimr
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|HD64461_IRQBASE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|nimr
op_assign
id|inw
c_func
(paren
id|HD64461_NIMR
)paren
suffix:semicolon
id|nimr
op_or_assign
id|mask
suffix:semicolon
id|outw
c_func
(paren
id|nimr
comma
id|HD64461_NIMR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_hd64461_irq
r_static
r_void
id|enable_hd64461_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|nimr
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|HD64461_IRQBASE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|nimr
op_assign
id|inw
c_func
(paren
id|HD64461_NIMR
)paren
suffix:semicolon
id|nimr
op_and_assign
op_complement
id|mask
suffix:semicolon
id|outw
c_func
(paren
id|nimr
comma
id|HD64461_NIMR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|mask_and_ack_hd64461
r_static
r_void
id|mask_and_ack_hd64461
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_hd64461_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HD64461_ENABLER
r_if
c_cond
(paren
id|irq
op_eq
id|HD64461_IRQBASE
op_plus
l_int|13
)paren
id|outb
c_func
(paren
l_int|0x00
comma
id|HD64461_PCC1CSCR
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|end_hd64461_irq
r_static
r_void
id|end_hd64461_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_hd64461_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|startup_hd64461_irq
r_static
r_int
r_int
id|startup_hd64461_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_hd64461_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shutdown_hd64461_irq
r_static
r_void
id|shutdown_hd64461_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_hd64461_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|hd64461_irq_type
r_static
r_struct
id|hw_interrupt_type
id|hd64461_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;HD64461-IRQ&quot;
comma
dot
id|startup
op_assign
id|startup_hd64461_irq
comma
dot
id|shutdown
op_assign
id|shutdown_hd64461_irq
comma
dot
id|enable
op_assign
id|enable_hd64461_irq
comma
dot
id|disable
op_assign
id|disable_hd64461_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_hd64461
comma
dot
id|end
op_assign
id|end_hd64461_irq
comma
)brace
suffix:semicolon
DECL|function|hd64461_interrupt
r_static
id|irqreturn_t
id|hd64461_interrupt
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HD64461: spurious interrupt, nirr: 0x%x nimr: 0x%x&bslash;n&quot;
comma
id|inw
c_func
(paren
id|HD64461_NIRR
)paren
comma
id|inw
c_func
(paren
id|HD64461_NIMR
)paren
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
DECL|variable|hd64461_demux
)brace
id|hd64461_demux
(braket
id|HD64461_IRQ_NUM
)braket
suffix:semicolon
DECL|function|hd64461_register_irq_demux
r_void
id|hd64461_register_irq_demux
c_func
(paren
r_int
id|irq
comma
r_int
(paren
op_star
id|demux
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
)paren
comma
r_void
op_star
id|dev
)paren
(brace
id|hd64461_demux
(braket
id|irq
op_minus
id|HD64461_IRQBASE
)braket
dot
id|func
op_assign
id|demux
suffix:semicolon
id|hd64461_demux
(braket
id|irq
op_minus
id|HD64461_IRQBASE
)braket
dot
id|dev
op_assign
id|dev
suffix:semicolon
)brace
DECL|variable|hd64461_register_irq_demux
id|EXPORT_SYMBOL
c_func
(paren
id|hd64461_register_irq_demux
)paren
suffix:semicolon
DECL|function|hd64461_unregister_irq_demux
r_void
id|hd64461_unregister_irq_demux
c_func
(paren
r_int
id|irq
)paren
(brace
id|hd64461_demux
(braket
id|irq
op_minus
id|HD64461_IRQBASE
)braket
dot
id|func
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|hd64461_unregister_irq_demux
id|EXPORT_SYMBOL
c_func
(paren
id|hd64461_unregister_irq_demux
)paren
suffix:semicolon
DECL|function|hd64461_irq_demux
r_int
id|hd64461_irq_demux
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
id|CONFIG_HD64461_IRQ
)paren
(brace
r_int
r_int
id|bit
suffix:semicolon
r_int
r_int
id|nirr
op_assign
id|inw
c_func
(paren
id|HD64461_NIRR
)paren
suffix:semicolon
r_int
r_int
id|nimr
op_assign
id|inw
c_func
(paren
id|HD64461_NIMR
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|nirr
op_and_assign
op_complement
id|nimr
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|1
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|bit
op_lshift_assign
l_int|1
comma
id|i
op_increment
)paren
r_if
c_cond
(paren
id|nirr
op_amp
id|bit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|16
)paren
id|irq
op_assign
id|CONFIG_HD64461_IRQ
suffix:semicolon
r_else
(brace
id|irq
op_assign
id|HD64461_IRQBASE
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|hd64461_demux
(braket
id|i
)braket
dot
id|func
op_ne
l_int|0
)paren
(brace
id|irq
op_assign
id|hd64461_demux
(braket
id|i
)braket
dot
id|func
c_func
(paren
id|irq
comma
id|hd64461_demux
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|__irq_demux
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|irq0
r_static
r_struct
id|irqaction
id|irq0
op_assign
(brace
id|hd64461_interrupt
comma
id|SA_INTERRUPT
comma
l_int|0
comma
l_string|&quot;HD64461&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|setup_hd64461
r_int
id|__init
id|setup_hd64461
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_HD64461
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HD64461 configured at 0x%x on irq %d(mapped into %d to %d)&bslash;n&quot;
comma
id|CONFIG_HD64461_IOBASE
comma
id|CONFIG_HD64461_IRQ
comma
id|HD64461_IRQBASE
comma
id|HD64461_IRQBASE
op_plus
l_int|15
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7709)&t;/* Should be at processor specific part.. */
id|outw
c_func
(paren
l_int|0x2240
comma
id|INTC_ICR1
)paren
suffix:semicolon
macro_line|#endif
id|outw
c_func
(paren
l_int|0xffff
comma
id|HD64461_NIMR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|HD64461_IRQBASE
suffix:semicolon
id|i
OL
id|HD64461_IRQBASE
op_plus
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|hd64461_irq_type
suffix:semicolon
)brace
id|setup_irq
c_func
(paren
id|CONFIG_HD64461_IRQ
comma
op_amp
id|irq0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HD64461_ENABLER
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HD64461: enabling PCMCIA devices&bslash;n&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x4c
comma
id|HD64461_PCC1CSCIER
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|HD64461_PCC1CSCR
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_hd64461
id|module_init
c_func
(paren
id|setup_hd64461
)paren
suffix:semicolon
eof
