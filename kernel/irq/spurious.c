multiline_comment|/*&n; * linux/kernel/irq/spurious.c&n; *&n; * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar&n; *&n; * This file contains spurious interrupt handling.&n; */
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; * If 99,900 of the previous 100,000 interrupts have not been handled&n; * then assume that the IRQ is stuck in some manner. Drop a diagnostic&n; * and try to turn the IRQ off.&n; *&n; * (The other 100-of-100,000 interrupts may have been a correctly&n; *  functioning device sharing an IRQ with the failing one)&n; *&n; * Called under desc-&gt;lock&n; */
r_static
r_void
DECL|function|__report_bad_irq
id|__report_bad_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|irq_desc_t
op_star
id|desc
comma
id|irqreturn_t
id|action_ret
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|action_ret
op_ne
id|IRQ_HANDLED
op_logical_and
id|action_ret
op_ne
id|IRQ_NONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;irq event %d: bogus return value %x&bslash;n&quot;
comma
id|irq
comma
id|action_ret
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;irq %d: nobody cared!&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;handlers:&bslash;n&quot;
)paren
suffix:semicolon
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_while
c_loop
(paren
id|action
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[&lt;%p&gt;]&quot;
comma
id|action-&gt;handler
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot; (%s)&quot;
comma
(paren
r_int
r_int
)paren
id|action-&gt;handler
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|report_bad_irq
r_void
id|report_bad_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|irq_desc_t
op_star
id|desc
comma
id|irqreturn_t
id|action_ret
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|__report_bad_irq
c_func
(paren
id|irq
comma
id|desc
comma
id|action_ret
)paren
suffix:semicolon
)brace
)brace
DECL|function|note_interrupt
r_void
id|note_interrupt
c_func
(paren
r_int
r_int
id|irq
comma
id|irq_desc_t
op_star
id|desc
comma
id|irqreturn_t
id|action_ret
)paren
(brace
r_if
c_cond
(paren
id|action_ret
op_ne
id|IRQ_HANDLED
)paren
(brace
id|desc-&gt;irqs_unhandled
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|action_ret
op_ne
id|IRQ_NONE
)paren
id|report_bad_irq
c_func
(paren
id|irq
comma
id|desc
comma
id|action_ret
)paren
suffix:semicolon
)brace
id|desc-&gt;irq_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;irq_count
OL
l_int|100000
)paren
r_return
suffix:semicolon
id|desc-&gt;irq_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;irqs_unhandled
OG
l_int|99900
)paren
(brace
multiline_comment|/*&n;&t;&t; * The interrupt is stuck&n;&t;&t; */
id|__report_bad_irq
c_func
(paren
id|irq
comma
id|desc
comma
id|action_ret
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now kill the IRQ&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Disabling IRQ #%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|desc-&gt;irqs_unhandled
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|noirqdebug
r_int
id|noirqdebug
suffix:semicolon
DECL|function|noirqdebug_setup
r_static
r_int
id|__init
id|noirqdebug_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|noirqdebug
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IRQ lockup detection disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;noirqdebug&quot;
comma
id|noirqdebug_setup
)paren
suffix:semicolon
eof
