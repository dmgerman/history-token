multiline_comment|/* $Id: irq.c,v 1.20 2004/01/13 05:52:11 kkojima Exp $&n; *&n; * linux/arch/sh/kernel/irq.c&n; *&n; *&t;Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar&n; *&n; *&n; * SuperH version:  Copyright (C) 1999  Niibe Yutaka&n; */
multiline_comment|/*&n; * IRQs are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/*&n; * &squot;what should we do if we get a hw irq event on an illegal vector&squot;.&n; * each architecture has to answer this themselves, it doesn&squot;t deserve&n; * a generic callback i think.&n; */
DECL|function|ack_bad_irq
r_void
id|ack_bad_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unexpected IRQ trap at vector %02x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_PROC_FS)
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
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
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
id|ACTUAL_NR_IRQS
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
id|unlock
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
id|unlock
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
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|do_IRQ
id|asmlinkage
r_int
id|do_IRQ
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;stc&t;r2_bank, %0&bslash;n&bslash;t&quot;
l_string|&quot;shlr2&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;shlr2&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;shlr&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;add&t;#-16, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=z&quot;
(paren
id|irq
)paren
)paren
suffix:semicolon
id|irq
op_assign
id|irq_demux
c_func
(paren
id|irq
)paren
suffix:semicolon
id|__do_IRQ
c_func
(paren
id|irq
comma
op_amp
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
eof
