multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; * Derived (i.e. mostly copied) from arch/i386/kernel/irq.c:&n; *&t;Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/smp.h&quot;
macro_line|#include &quot;linux/irq.h&quot;
macro_line|#include &quot;linux/kernel_stat.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/random.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/file.h&quot;
macro_line|#include &quot;linux/proc_fs.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/seq_file.h&quot;
macro_line|#include &quot;linux/profile.h&quot;
macro_line|#include &quot;linux/hardirq.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;asm/hw_irq.h&quot;
macro_line|#include &quot;asm/atomic.h&quot;
macro_line|#include &quot;asm/signal.h&quot;
macro_line|#include &quot;asm/system.h&quot;
macro_line|#include &quot;asm/errno.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;irq_kern.h&quot;
multiline_comment|/*&n; * Generic, controller-independent functions:&n; */
DECL|function|show_interrupts
r_int
id|show_interrupts
c_func
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
op_assign
op_star
(paren
id|loff_t
op_star
)paren
id|v
comma
id|j
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|j
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|j
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|NR_IRQS
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
id|action
op_assign
id|irq_desc
(braket
id|i
)braket
dot
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_goto
id|skip
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: &quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#else
id|for_each_online_cpu
c_func
(paren
id|j
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_cpu
c_func
(paren
id|j
)paren
dot
id|irqs
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %14s&quot;
comma
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
r_typename
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|skip
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|NR_IRQS
)paren
(brace
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * do_IRQ handles all normal device IRQ&squot;s (the special&n; * SMP cross-CPU interrupts have their own specific&n; * handlers).&n; */
DECL|function|do_IRQ
r_int
r_int
id|do_IRQ
c_func
(paren
r_int
id|irq
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|__do_IRQ
c_func
(paren
id|irq
comma
(paren
r_struct
id|pt_regs
op_star
)paren
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|um_request_irq
r_int
id|um_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
id|fd
comma
r_int
id|type
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
id|irqflags
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
r_int
id|err
suffix:semicolon
id|err
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fd
op_ne
op_minus
l_int|1
)paren
(brace
id|err
op_assign
id|activate_fd
c_func
(paren
id|irq
comma
id|fd
comma
id|type
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|um_request_irq
id|EXPORT_SYMBOL
c_func
(paren
id|um_request_irq
)paren
suffix:semicolon
DECL|variable|reactivate_fd
id|EXPORT_SYMBOL
c_func
(paren
id|reactivate_fd
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|irq_spinlock
)paren
suffix:semicolon
DECL|function|irq_lock
r_int
r_int
id|irq_lock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|function|irq_unlock
r_void
id|irq_unlock
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*  presently hw_interrupt_type must define (startup || enable) &amp;&amp;&n; *  disable &amp;&amp; end */
DECL|function|dummy
r_static
r_void
id|dummy
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|variable|SIGIO_irq_type
r_static
r_struct
id|hw_interrupt_type
id|SIGIO_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;SIGIO&quot;
comma
dot
id|disable
op_assign
id|dummy
comma
dot
id|enable
op_assign
id|dummy
comma
dot
id|ack
op_assign
id|dummy
comma
dot
id|end
op_assign
id|dummy
)brace
suffix:semicolon
DECL|variable|SIGVTALRM_irq_type
r_static
r_struct
id|hw_interrupt_type
id|SIGVTALRM_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;SIGVTALRM&quot;
comma
dot
id|shutdown
op_assign
id|dummy
comma
multiline_comment|/* never called */
dot
id|disable
op_assign
id|dummy
comma
dot
id|enable
op_assign
id|dummy
comma
dot
id|ack
op_assign
id|dummy
comma
dot
id|end
op_assign
id|dummy
)brace
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|handler
op_assign
op_amp
id|SIGVTALRM_irq_type
suffix:semicolon
id|enable_irq
c_func
(paren
id|TIMER_IRQ
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_IRQS
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
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|SIGIO_irq_type
suffix:semicolon
id|enable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|init_irq_signals
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
