multiline_comment|/*&n; *&t;linux/arch/mips/dec/kn02-irq.c&n; *&n; *&t;DECstation 5000/200 (KN02) Control and Status Register&n; *&t;interrupts.&n; *&n; *&t;Copyright (c) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/dec/kn02.h&gt;
multiline_comment|/*&n; * Bits 7:0 of the Control Register are write-only -- the&n; * corresponding bits of the Status Register have a different&n; * meaning.  Hence we use a cache.  It speeds up things a bit&n; * as well.&n; *&n; * There is no default value -- it has to be initialized.&n; */
DECL|variable|cached_kn02_csr
id|u32
id|cached_kn02_csr
suffix:semicolon
DECL|variable|kn02_lock
id|spinlock_t
id|kn02_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|kn02_irq_base
r_static
r_int
id|kn02_irq_base
suffix:semicolon
DECL|function|unmask_kn02_irq
r_static
r_inline
r_void
id|unmask_kn02_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
id|u32
op_star
id|csr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|KN02_CSR_BASE
suffix:semicolon
id|cached_kn02_csr
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|kn02_irq_base
op_plus
l_int|16
)paren
)paren
suffix:semicolon
op_star
id|csr
op_assign
id|cached_kn02_csr
suffix:semicolon
)brace
DECL|function|mask_kn02_irq
r_static
r_inline
r_void
id|mask_kn02_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
id|u32
op_star
id|csr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|KN02_CSR_BASE
suffix:semicolon
id|cached_kn02_csr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|kn02_irq_base
op_plus
l_int|16
)paren
)paren
suffix:semicolon
op_star
id|csr
op_assign
id|cached_kn02_csr
suffix:semicolon
)brace
DECL|function|enable_kn02_irq
r_static
r_inline
r_void
id|enable_kn02_irq
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
id|unmask_kn02_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|disable_kn02_irq
r_static
r_inline
r_void
id|disable_kn02_irq
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
id|mask_kn02_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_kn02_irq
r_static
r_int
r_int
id|startup_kn02_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_kn02_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|shutdown_kn02_irq
mdefine_line|#define shutdown_kn02_irq disable_kn02_irq
DECL|function|ack_kn02_irq
r_static
r_void
id|ack_kn02_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|kn02_lock
)paren
suffix:semicolon
id|mask_kn02_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kn02_lock
)paren
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|end_kn02_irq
r_static
r_void
id|end_kn02_irq
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
id|enable_kn02_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|kn02_irq_type
r_static
r_struct
id|hw_interrupt_type
id|kn02_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;KN02-CSR&quot;
comma
dot
id|startup
op_assign
id|startup_kn02_irq
comma
dot
id|shutdown
op_assign
id|shutdown_kn02_irq
comma
dot
id|enable
op_assign
id|enable_kn02_irq
comma
dot
id|disable
op_assign
id|disable_kn02_irq
comma
dot
id|ack
op_assign
id|ack_kn02_irq
comma
dot
id|end
op_assign
id|end_kn02_irq
comma
)brace
suffix:semicolon
DECL|function|init_kn02_irqs
r_void
id|__init
id|init_kn02_irqs
c_func
(paren
r_int
id|base
)paren
(brace
r_volatile
id|u32
op_star
id|csr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|KN02_CSR_BASE
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Mask interrupts. */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
id|cached_kn02_csr
op_and_assign
op_complement
id|KN03_CSR_IOINTEN
suffix:semicolon
op_star
id|csr
op_assign
id|cached_kn02_csr
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|base
suffix:semicolon
id|i
OL
id|base
op_plus
id|KN02_IRQ_LINES
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
l_int|0
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
id|kn02_irq_type
suffix:semicolon
)brace
id|kn02_irq_base
op_assign
id|base
suffix:semicolon
)brace
eof
