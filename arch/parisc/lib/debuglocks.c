multiline_comment|/* &n; *    Debugging versions of SMP locking primitives.&n; *&n; *    Copyright (C) 2004 Thibaut VARENE &lt;varenet@parisc-linux.org&gt;&n; *&n; *    Some code stollen from alpha &amp; sparc64 ;)&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *    We use pdc_printf() throughout the file for all output messages, to avoid&n; *    losing messages because of disabled interrupts. Since we&squot;re using these&n; *    messages for debugging purposes, it makes sense not to send them to the&n; *    linux console.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/hardirq.h&gt;&t;/* in_interrupt() */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;&t;/* in_interrupt() */
macro_line|#include &lt;asm/pdc.h&gt;
DECL|macro|INIT_STUCK
macro_line|#undef INIT_STUCK
DECL|macro|INIT_STUCK
mdefine_line|#define INIT_STUCK 1L &lt;&lt; 30
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|function|_dbg_spin_lock
r_void
id|_dbg_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
id|base_file
comma
r_int
id|line_no
)paren
(brace
r_volatile
r_int
r_int
op_star
id|a
suffix:semicolon
r_int
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
r_void
op_star
id|inline_pc
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|started
op_assign
id|jiffies
suffix:semicolon
r_int
id|printed
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|try_again
suffix:colon
multiline_comment|/* Do the actual locking */
multiline_comment|/* &lt;T-Bone&gt; ggg: we can&squot;t get stuck on the outter loop?&n;&t; * &lt;ggg&gt; T-Bone: We can hit the outer loop&n;&t; *&t;alot if multiple CPUs are constantly racing for a lock&n;&t; *&t;and the backplane is NOT fair about which CPU sees&n;&t; *&t;the update first. But it won&squot;t hang since every failed&n;&t; *&t;attempt will drop us back into the inner loop and&n;&t; *&t;decrement `stuck&squot;.&n;&t; * &lt;ggg&gt; K-class and some of the others are NOT fair in the HW&n;&t; * &t;implementation so we could see false positives.&n;&t; * &t;But fixing the lock contention is easier than&n;&t; * &t;fixing the HW to be fair.&n;&t; * &lt;tausq&gt; __ldcw() returns 1 if we get the lock; otherwise we&n;&t; * &t;spin until the value of the lock changes, or we time out.&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|a
op_assign
id|__ldcw_align
c_func
(paren
id|lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|stuck
op_logical_and
(paren
id|__ldcw
c_func
(paren
id|a
)paren
op_eq
l_int|0
)paren
)paren
r_while
c_loop
(paren
(paren
op_star
id|a
op_eq
l_int|0
)paren
op_logical_and
op_decrement
id|stuck
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|stuck
op_le
l_int|0
)paren
)paren
(brace
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: spin_lock(%s/%p) stuck in %s at %p(%d)&quot;
l_string|&quot; owned by %s:%d in %s at %p(%d)&bslash;n&quot;
comma
id|base_file
comma
id|line_no
comma
id|lock-&gt;module
comma
id|lock
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|lock-&gt;bfile
comma
id|lock-&gt;bline
comma
id|lock-&gt;task-&gt;comm
comma
id|lock-&gt;previous
comma
id|lock-&gt;oncpu
)paren
suffix:semicolon
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
id|printed
op_assign
l_int|1
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
)brace
multiline_comment|/* Exiting.  Got the lock.  */
id|lock-&gt;oncpu
op_assign
id|cpu
suffix:semicolon
id|lock-&gt;previous
op_assign
id|inline_pc
suffix:semicolon
id|lock-&gt;task
op_assign
id|current
suffix:semicolon
id|lock-&gt;bfile
op_assign
(paren
r_char
op_star
)paren
id|base_file
suffix:semicolon
id|lock-&gt;bline
op_assign
id|line_no
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|printed
)paren
)paren
(brace
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: spin_lock grabbed in %s at %p(%d) %ld ticks&bslash;n&quot;
comma
id|base_file
comma
id|line_no
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|jiffies
op_minus
id|started
)paren
suffix:semicolon
)brace
)brace
DECL|function|_dbg_spin_unlock
r_void
id|_dbg_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
id|base_file
comma
r_int
id|line_no
)paren
(brace
id|CHECK_LOCK
c_func
(paren
id|lock
)paren
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|a
op_assign
id|__ldcw_align
c_func
(paren
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
op_star
id|a
op_ne
l_int|0
)paren
op_logical_and
id|lock-&gt;babble
)paren
)paren
(brace
id|lock-&gt;babble
op_decrement
suffix:semicolon
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: spin_unlock(%s:%p) not locked&bslash;n&quot;
comma
id|base_file
comma
id|line_no
comma
id|lock-&gt;module
comma
id|lock
)paren
suffix:semicolon
)brace
op_star
id|a
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_dbg_spin_trylock
r_int
id|_dbg_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
id|base_file
comma
r_int
id|line_no
)paren
(brace
r_int
id|ret
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|a
op_assign
id|__ldcw_align
c_func
(paren
id|lock
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|__ldcw
c_func
(paren
id|a
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|lock-&gt;oncpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|lock-&gt;previous
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|lock-&gt;task
op_assign
id|current
suffix:semicolon
)brace
r_else
(brace
id|lock-&gt;bfile
op_assign
(paren
r_char
op_star
)paren
id|base_file
suffix:semicolon
id|lock-&gt;bline
op_assign
id|line_no
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
macro_line|#ifdef CONFIG_DEBUG_RWLOCK
multiline_comment|/* Interrupts trouble detailed explanation, thx Grant:&n; *&n; * o writer (wants to modify data) attempts to acquire the rwlock&n; * o He gets the write lock.&n; * o Interupts are still enabled, we take an interrupt with the&n; *   write still holding the lock.&n; * o interrupt handler tries to acquire the rwlock for read.&n; * o deadlock since the writer can&squot;t release it at this point.&n; * &n; * In general, any use of spinlocks that competes between &quot;base&quot;&n; * level and interrupt level code will risk deadlock. Interrupts&n; * need to be disabled in the base level routines to avoid it.&n; * Or more precisely, only the IRQ the base level routine&n; * is competing with for the lock.  But it&squot;s more efficient/faster&n; * to just disable all interrupts on that CPU to guarantee&n; * once it gets the lock it can release it quickly too.&n; */
DECL|function|_dbg_write_lock
r_void
id|_dbg_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_const
r_char
op_star
id|bfile
comma
r_int
id|bline
)paren
(brace
r_void
op_star
id|inline_pc
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|started
op_assign
id|jiffies
suffix:semicolon
r_int
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
r_int
id|printed
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
)paren
(brace
multiline_comment|/* acquiring write lock in interrupt context, bad idea */
id|pdc_printf
c_func
(paren
l_string|&quot;write_lock caller: %s:%d, IRQs enabled,&bslash;n&quot;
comma
id|bfile
comma
id|bline
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Note: if interrupts are disabled (which is most likely), the printk&n;&t;will never show on the console. We might need a polling method to flush&n;&t;the dmesg buffer anyhow. */
id|retry
suffix:colon
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw-&gt;counter
op_ne
l_int|0
)paren
(brace
multiline_comment|/* this basically never happens */
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|stuck
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|unlikely
c_func
(paren
id|stuck
op_le
l_int|0
)paren
)paren
op_logical_and
(paren
id|rw-&gt;counter
OL
l_int|0
)paren
)paren
(brace
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: write_lock stuck on writer&quot;
l_string|&quot; in %s at %p(%d) %ld ticks&bslash;n&quot;
comma
id|bfile
comma
id|bline
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|jiffies
op_minus
id|started
)paren
suffix:semicolon
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
id|printed
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|stuck
op_le
l_int|0
)paren
)paren
(brace
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: write_lock stuck on reader&quot;
l_string|&quot; in %s at %p(%d) %ld ticks&bslash;n&quot;
comma
id|bfile
comma
id|bline
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|jiffies
op_minus
id|started
)paren
suffix:semicolon
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
id|printed
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rw-&gt;counter
op_ne
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_goto
id|retry
suffix:semicolon
)brace
multiline_comment|/* got it.  now leave without unlocking */
id|rw-&gt;counter
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* remember we are locked */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|printed
)paren
)paren
(brace
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: write_lock grabbed in %s at %p(%d) %ld ticks&bslash;n&quot;
comma
id|bfile
comma
id|bline
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|jiffies
op_minus
id|started
)paren
suffix:semicolon
)brace
)brace
DECL|function|_dbg_write_trylock
r_int
id|_dbg_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_const
r_char
op_star
id|bfile
comma
r_int
id|bline
)paren
(brace
macro_line|#if 0
r_void
op_star
id|inline_pc
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
)paren
(brace
multiline_comment|/* acquiring write lock in interrupt context, bad idea */
id|pdc_printf
c_func
(paren
l_string|&quot;write_lock caller: %s:%d, IRQs enabled,&bslash;n&quot;
comma
id|bfile
comma
id|bline
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Note: if interrupts are disabled (which is most likely), the printk&n;&t;will never show on the console. We might need a polling method to flush&n;&t;the dmesg buffer anyhow. */
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw-&gt;counter
op_ne
l_int|0
)paren
(brace
multiline_comment|/* this basically never happens */
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* got it.  now leave without unlocking */
id|rw-&gt;counter
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* remember we are locked */
macro_line|#if 0
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: try write_lock grabbed in %s at %p(%d)&bslash;n&quot;
comma
id|bfile
comma
id|bline
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|_dbg_read_lock
r_void
id|_dbg_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_const
r_char
op_star
id|bfile
comma
r_int
id|bline
)paren
(brace
macro_line|#if 0
r_void
op_star
id|inline_pc
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|started
op_assign
id|jiffies
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|rw-&gt;counter
op_increment
suffix:semicolon
macro_line|#if 0
id|pdc_printf
c_func
(paren
l_string|&quot;%s:%d: read_lock grabbed in %s at %p(%d) %ld ticks&bslash;n&quot;
comma
id|bfile
comma
id|bline
comma
id|current-&gt;comm
comma
id|inline_pc
comma
id|cpu
comma
id|jiffies
op_minus
id|started
)paren
suffix:semicolon
macro_line|#endif
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DEBUG_RWLOCK */
eof
