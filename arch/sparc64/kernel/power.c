multiline_comment|/* $Id: power.c,v 1.10 2001/12/11 01:57:16 davem Exp $&n; * power.c: Power management driver.&n; *&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|variable|power_reg
r_static
r_int
r_int
id|power_reg
op_assign
l_int|0UL
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|powerd_wait
)paren
suffix:semicolon
DECL|variable|button_pressed
r_static
r_int
id|button_pressed
suffix:semicolon
DECL|function|power_handler
r_static
id|irqreturn_t
id|power_handler
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
r_if
c_cond
(paren
id|button_pressed
op_eq
l_int|0
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|powerd_wait
)paren
suffix:semicolon
id|button_pressed
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* FIXME: Check registers for status... */
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
r_extern
r_void
id|machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|machine_alt_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|poweroff_method
r_static
r_void
(paren
op_star
id|poweroff_method
)paren
(paren
r_void
)paren
op_assign
id|machine_alt_power_off
suffix:semicolon
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|power_reg
op_ne
l_int|0UL
)paren
(brace
multiline_comment|/* Both register bits seem to have the&n;&t;&t;&t; * same effect, so until I figure out&n;&t;&t;&t; * what the difference is...&n;&t;&t;&t; */
id|writel
c_func
(paren
id|AUXIO_PCIO_CPWR_OFF
op_or
id|AUXIO_PCIO_SPWR_OFF
comma
id|power_reg
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif /* CONFIG_PCI */
r_if
c_cond
(paren
id|poweroff_method
op_ne
l_int|NULL
)paren
(brace
id|poweroff_method
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* not reached */
)brace
)brace
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|function|powerd
r_static
r_int
id|powerd
c_func
(paren
r_void
op_star
id|__unused
)paren
(brace
r_static
r_char
op_star
id|envp
(braket
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=linux&quot;
comma
l_string|&quot;PATH=/sbin:/usr/sbin:/bin:/usr/bin&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;/sbin/shutdown&quot;
comma
l_string|&quot;-h&quot;
comma
l_string|&quot;now&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;powerd&quot;
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|powerd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|again
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|button_pressed
)paren
r_break
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|powerd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* Ok, down we go... */
r_if
c_cond
(paren
id|execve
c_func
(paren
l_string|&quot;/sbin/shutdown&quot;
comma
id|argv
comma
id|envp
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;powerd: shutdown execution failed&bslash;n&quot;
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|powerd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|button_pressed
op_assign
l_int|0
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|has_button_interrupt
r_static
r_int
id|__init
id|has_button_interrupt
c_func
(paren
r_struct
id|linux_ebus_device
op_star
id|edev
)paren
(brace
r_if
c_cond
(paren
id|edev-&gt;irqs
(braket
l_int|0
)braket
op_eq
id|PCI_IRQ_NONE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prom_node_has_property
c_func
(paren
id|edev-&gt;prom_node
comma
l_string|&quot;button&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|power_init
r_void
id|__init
id|power_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
suffix:semicolon
r_static
r_int
id|invoked
suffix:semicolon
r_if
c_cond
(paren
id|invoked
)paren
r_return
suffix:semicolon
id|invoked
op_assign
l_int|1
suffix:semicolon
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;power&quot;
)paren
)paren
r_goto
id|found
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
id|found
suffix:colon
id|power_reg
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
l_int|0x4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;power: Control reg at %016lx ... &quot;
comma
id|power_reg
)paren
suffix:semicolon
id|poweroff_method
op_assign
id|machine_halt
suffix:semicolon
multiline_comment|/* able to use the standard halt */
r_if
c_cond
(paren
id|has_button_interrupt
c_func
(paren
id|edev
)paren
)paren
(brace
r_if
c_cond
(paren
id|kernel_thread
c_func
(paren
id|powerd
comma
l_int|0
comma
id|CLONE_FS
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to start power daemon.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;powerd running.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|edev-&gt;irqs
(braket
l_int|0
)braket
comma
id|power_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;power&quot;
comma
(paren
r_void
op_star
)paren
id|power_reg
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;power: Error, cannot register IRQ handler.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;not using powerd.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PCI */
eof
