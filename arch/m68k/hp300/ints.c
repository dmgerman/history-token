multiline_comment|/*&n; *  linux/arch/m68k/hp300/ints.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific interrupt handling.&n; *  We only use the autovector interrupts, and therefore we need to&n; *  maintain lists of devices sharing each ipl.&n; *  [ipl list code added by Peter Maydell &lt;pmaydell@chiark.greenend.org.uk&gt; 06/1998]&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;ints.h&quot;
multiline_comment|/* Each ipl has a linked list of interrupt service routines.&n; * Service routines are added via hp300_request_irq() and removed&n; * via hp300_free_irq(). The device driver should set IRQ_FLG_FAST&n; * if it needs to be serviced early (eg FIFOless UARTs); this will&n; * cause it to be added at the front of the queue rather than&n; * the back.&n; * Currently IRQ_FLG_SLOW and flags=0 are treated identically; if&n; * we needed three levels of priority we could distinguish them&n; * but this strikes me as mildly ugly...&n; */
multiline_comment|/* we start with no entries in any list */
DECL|variable|hp300_irq_list
r_static
id|irq_node_t
op_star
id|hp300_irq_list
(braket
id|HP300_NUM_IRQS
)braket
suffix:semicolon
DECL|variable|irqlist_lock
r_static
id|spinlock_t
id|irqlist_lock
suffix:semicolon
multiline_comment|/* This handler receives all interrupts, dispatching them to the registered handlers */
DECL|function|hp300_int_handler
r_static
id|irqreturn_t
id|hp300_int_handler
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
id|fp
)paren
(brace
id|irq_node_t
op_star
id|t
suffix:semicolon
multiline_comment|/* We just give every handler on the chain an opportunity to handle&n;         * the interrupt, in priority order.&n;         */
r_for
c_loop
(paren
id|t
op_assign
id|hp300_irq_list
(braket
id|irq
)braket
suffix:semicolon
id|t
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
(brace
id|t
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|t-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* We could put in some accounting routines, checks for stray interrupts,&n;         * etc, in here. Note that currently we can&squot;t tell whether or not&n;         * a handler handles the interrupt, though.&n;         */
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|hp300_default_handler
id|irqreturn_t
(paren
op_star
id|hp300_default_handler
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
(braket
l_int|0
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|1
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|2
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|3
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|4
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|5
)braket
op_assign
id|hp300_int_handler
comma
(braket
l_int|6
)braket
op_assign
id|hp300_int_handler
comma
)brace
suffix:semicolon
multiline_comment|/* dev_id had better be unique to each handler because it&squot;s the only way we have&n; * to distinguish handlers when removing them...&n; *&n; * It would be pretty easy to support IRQ_FLG_LOCK (handler is not replacable)&n; * and IRQ_FLG_REPLACE (handler replaces existing one with this dev_id)&n; * if we wanted to. IRQ_FLG_FAST is needed for devices where interrupt latency&n; * matters (eg the dreaded FIFOless UART...)&n; */
DECL|function|hp300_request_irq
r_int
id|hp300_request_irq
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
id|irq_node_t
op_star
id|t
comma
op_star
id|n
op_assign
id|new_irq_node
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
multiline_comment|/* oops, no free nodes */
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hp300_irq_list
(braket
id|irq
)braket
)paren
(brace
multiline_comment|/* no list yet */
id|hp300_irq_list
(braket
id|irq
)braket
op_assign
id|n
suffix:semicolon
id|n-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
multiline_comment|/* insert at head of list */
id|n-&gt;next
op_assign
id|hp300_irq_list
(braket
id|irq
)braket
suffix:semicolon
id|hp300_irq_list
(braket
id|irq
)braket
op_assign
id|n
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* insert at end of list */
r_for
c_loop
(paren
id|t
op_assign
id|hp300_irq_list
(braket
id|irq
)braket
suffix:semicolon
id|t-&gt;next
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
(brace
multiline_comment|/* do nothing */
suffix:semicolon
)brace
id|n-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;next
op_assign
id|n
suffix:semicolon
)brace
multiline_comment|/* Fill in n appropriately */
id|n-&gt;handler
op_assign
id|handler
suffix:semicolon
id|n-&gt;flags
op_assign
id|flags
suffix:semicolon
id|n-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|n-&gt;devname
op_assign
id|devname
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp300_free_irq
r_void
id|hp300_free_irq
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
id|irq_node_t
op_star
id|t
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
id|t
op_assign
id|hp300_irq_list
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
multiline_comment|/* no handlers at all for that IRQ */
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hp300_free_irq: attempt to remove nonexistent handler for IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;dev_id
op_eq
id|dev_id
)paren
(brace
multiline_comment|/* removing first handler on chain */
id|t-&gt;flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
multiline_comment|/* we probably don&squot;t really need these */
id|t-&gt;dev_id
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;devname
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* frees this irq_node_t */
id|hp300_irq_list
(braket
id|irq
)braket
op_assign
id|t-&gt;next
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* OK, must be removing from middle of the chain */
r_for
c_loop
(paren
id|t
op_assign
id|hp300_irq_list
(braket
id|irq
)braket
suffix:semicolon
id|t-&gt;next
op_logical_and
id|t-&gt;next-&gt;dev_id
op_ne
id|dev_id
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
multiline_comment|/* do nothing */
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;next
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hp300_free_irq: attempt to remove nonexistent handler for IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* remove the entry after t: */
id|t-&gt;next-&gt;flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|t-&gt;next-&gt;dev_id
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;next-&gt;devname
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;next-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;next
op_assign
id|t-&gt;next-&gt;next
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irqlist_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|show_hp300_interrupts
r_int
id|show_hp300_interrupts
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp300_init_IRQ
r_void
id|__init
id|hp300_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|irqlist_lock
)paren
suffix:semicolon
)brace
eof
