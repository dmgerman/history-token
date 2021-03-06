multiline_comment|/*&n; *  arch/s390/kernel/s390_ext.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Holger Smolinski (Holger.Smolinski@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Simple hash strategy: index = code &amp; 0xff;&n; * ext_int_hash[index] is the start of the list for all external interrupts&n; * that hash to this index. With the current set of external interrupts &n; * (0x1202 external call, 0x1004 cpu timer, 0x2401 hwc console, 0x4000&n; * iucv and 0x2603 pfault) this is always the first element. &n; */
DECL|variable|ext_int_hash
id|ext_int_info_t
op_star
id|ext_int_hash
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|function|register_external_interrupt
r_int
id|register_external_interrupt
c_func
(paren
id|__u16
id|code
comma
id|ext_int_handler_t
id|handler
)paren
(brace
id|ext_int_info_t
op_star
id|p
suffix:semicolon
r_int
id|index
suffix:semicolon
id|p
op_assign
(paren
id|ext_int_info_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ext_int_info_t
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p-&gt;code
op_assign
id|code
suffix:semicolon
id|p-&gt;handler
op_assign
id|handler
suffix:semicolon
id|index
op_assign
id|code
op_amp
l_int|0xff
suffix:semicolon
id|p-&gt;next
op_assign
id|ext_int_hash
(braket
id|index
)braket
suffix:semicolon
id|ext_int_hash
(braket
id|index
)braket
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_early_external_interrupt
r_int
id|register_early_external_interrupt
c_func
(paren
id|__u16
id|code
comma
id|ext_int_handler_t
id|handler
comma
id|ext_int_info_t
op_star
id|p
)paren
(brace
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;code
op_assign
id|code
suffix:semicolon
id|p-&gt;handler
op_assign
id|handler
suffix:semicolon
id|index
op_assign
id|code
op_amp
l_int|0xff
suffix:semicolon
id|p-&gt;next
op_assign
id|ext_int_hash
(braket
id|index
)braket
suffix:semicolon
id|ext_int_hash
(braket
id|index
)braket
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_external_interrupt
r_int
id|unregister_external_interrupt
c_func
(paren
id|__u16
id|code
comma
id|ext_int_handler_t
id|handler
)paren
(brace
id|ext_int_info_t
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
id|index
suffix:semicolon
id|index
op_assign
id|code
op_amp
l_int|0xff
suffix:semicolon
id|q
op_assign
l_int|NULL
suffix:semicolon
id|p
op_assign
id|ext_int_hash
(braket
id|index
)braket
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;code
op_eq
id|code
op_logical_and
id|p-&gt;handler
op_eq
id|handler
)paren
r_break
suffix:semicolon
id|q
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|q
op_ne
l_int|NULL
)paren
id|q-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
r_else
id|ext_int_hash
(braket
id|index
)braket
op_assign
id|p-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_early_external_interrupt
r_int
id|unregister_early_external_interrupt
c_func
(paren
id|__u16
id|code
comma
id|ext_int_handler_t
id|handler
comma
id|ext_int_info_t
op_star
id|p
)paren
(brace
id|ext_int_info_t
op_star
id|q
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
op_logical_or
id|p-&gt;code
op_ne
id|code
op_logical_or
id|p-&gt;handler
op_ne
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|index
op_assign
id|code
op_amp
l_int|0xff
suffix:semicolon
id|q
op_assign
id|ext_int_hash
(braket
id|index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|q
)paren
(brace
r_while
c_loop
(paren
id|q
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;next
op_eq
id|p
)paren
r_break
suffix:semicolon
id|q
op_assign
id|q-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|q-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_else
id|ext_int_hash
(braket
id|index
)braket
op_assign
id|p-&gt;next
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_extint
r_void
id|do_extint
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|code
)paren
(brace
id|ext_int_info_t
op_star
id|p
suffix:semicolon
r_int
id|index
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mc 0,0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S390_lowcore.int_clock
op_ge
id|S390_lowcore.jiffy_timer
)paren
multiline_comment|/**&n;&t;&t; * Make sure that the i/o interrupt did not &quot;overtake&quot;&n;&t;&t; * the last HZ timer interrupt.&n;&t;&t; */
id|account_ticks
c_func
(paren
id|regs
)paren
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|irqs
(braket
id|EXTERNAL_INTERRUPT
)braket
op_increment
suffix:semicolon
id|index
op_assign
id|code
op_amp
l_int|0xff
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|ext_int_hash
(braket
id|index
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|p-&gt;code
op_eq
id|code
)paren
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|p-&gt;handler
)paren
)paren
id|p
op_member_access_from_pointer
id|handler
c_func
(paren
id|regs
comma
id|code
)paren
suffix:semicolon
)brace
)brace
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|register_external_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|register_external_interrupt
)paren
suffix:semicolon
DECL|variable|unregister_external_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_external_interrupt
)paren
suffix:semicolon
eof
