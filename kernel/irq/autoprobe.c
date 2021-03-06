multiline_comment|/*&n; * linux/kernel/irq/autoprobe.c&n; *&n; * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar&n; *&n; * This file contains the interrupt probing code and driver APIs.&n; */
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; * Autodetection depends on the fact that any interrupt that&n; * comes in on to an unassigned handler will get stuck with&n; * &quot;IRQ_WAITING&quot; cleared and the interrupt disabled.&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;probe_irq_on&t;- begin an interrupt autodetect&n; *&n; *&t;Commence probing for an interrupt. The interrupts are scanned&n; *&t;and a mask of potential interrupt lines is returned.&n; *&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
comma
id|delay
suffix:semicolon
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * something may have generated an irq long ago and we want to&n;&t; * flush such a longstanding irq before considering it as spurious.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|i
)braket
dot
id|action
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for longstanding interrupts to trigger. */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|50
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 20ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable any unassigned irqs&n;&t; * (we must startup again here because if a longstanding irq&n;&t; * happened in the previous stage, it may have masked itself)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;action
)paren
(brace
id|desc-&gt;status
op_or_assign
id|IRQ_AUTODETECT
op_or
id|IRQ_WAITING
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
)paren
id|desc-&gt;status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wait for spurious interrupts to trigger&n;&t; */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 100ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now filter out any obviously spurious interrupts&n;&t; */
id|val
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
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
multiline_comment|/* It triggered already - consider it spurious. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
OL
l_int|32
)paren
id|val
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|variable|probe_irq_on
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_on
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;probe_irq_mask - scan a bitmap of interrupt lines&n; *&t;@val:&t;mask of interrupts to consider&n; *&n; *&t;Scan the interrupt lines and return a bitmap of active&n; *&t;autodetect interrupts. The interrupt probe logic state&n; *&t;is then returned to its previous value.&n; *&n; *&t;Note: we need to scan all the irq&squot;s even though we will&n; *&t;only return autodetect irq numbers - just so that we reset&n; *&t;them all to a known state.&n; */
DECL|function|probe_irq_mask
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
id|i
suffix:semicolon
id|mask
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
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|16
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
id|mask
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
id|mask
op_amp
id|val
suffix:semicolon
)brace
DECL|variable|probe_irq_mask
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_mask
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;probe_irq_off&t;- end an interrupt autodetect&n; *&t;@val: mask of potential interrupts (unused)&n; *&n; *&t;Scans the unused interrupt lines and returns the line which&n; *&t;appears to have triggered the interrupt. If no interrupt was&n; *&t;found then zero is returned. If more than one interrupt is&n; *&t;found then minus the first candidate is returned to indicate&n; *&t;their is doubt.&n; *&n; *&t;The interrupt probe logic state is returned to its previous&n; *&t;value.&n; *&n; *&t;BUGS: When used in a module (which arguably shouldn&squot;t happen)&n; *&t;nothing prevents two IRQ probe callers from overlapping. The&n; *&t;results of this are non-optimal.&n; */
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|irq_found
op_assign
l_int|0
comma
id|nr_irqs
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
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nr_irqs
)paren
id|irq_found
op_assign
id|i
suffix:semicolon
id|nr_irqs
op_increment
suffix:semicolon
)brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_irqs
OG
l_int|1
)paren
id|irq_found
op_assign
op_minus
id|irq_found
suffix:semicolon
r_return
id|irq_found
suffix:semicolon
)brace
DECL|variable|probe_irq_off
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_off
)paren
suffix:semicolon
eof
