multiline_comment|/*&n; * Read-Copy Update mechanism for mutual exclusion&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2001&n; *&n; * Author: Dipankar Sarma &lt;dipankar@in.ibm.com&gt;&n; * &n; * Based on the original work by Paul McKenney &lt;paul.mckenney@us.ibm.com&gt;&n; * and inputs from Rusty Russell, Andrea Arcangeli and Andi Kleen.&n; * Papers:&n; * http://www.rdrop.com/users/paulmck/paper/rclockpdcsproof.pdf&n; * http://lse.sourceforge.net/locking/rclock_OLS.2001.05.01c.sc.pdf (OLS2001)&n; *&n; * For detailed explanation of Read-Copy Update mechanism see -&n; * &t;&t;http://lse.sourceforge.net/locking/rcupdate.html&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
multiline_comment|/* Definition for rcupdate control block. */
DECL|variable|rcu_ctrlblk
r_struct
id|rcu_ctrlblk
id|rcu_ctrlblk
op_assign
(brace
dot
id|mutex
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|curbatch
op_assign
l_int|1
comma
dot
id|maxbatch
op_assign
l_int|1
comma
dot
id|rcu_cpu_mask
op_assign
id|CPU_MASK_NONE
)brace
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|rcu_data
comma
id|rcu_data
)paren
op_assign
(brace
l_int|0L
)brace
suffix:semicolon
multiline_comment|/* Fake initialization required by compiler */
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|tasklet_struct
comma
id|rcu_tasklet
)paren
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|macro|RCU_tasklet
mdefine_line|#define RCU_tasklet(cpu) (per_cpu(rcu_tasklet, cpu))
multiline_comment|/**&n; * call_rcu - Queue an RCU update request.&n; * @head: structure to be used for queueing the RCU updates.&n; * @func: actual update function to be invoked after the grace period&n; * @arg: argument to be passed to the update function&n; *&n; * The update function will be invoked as soon as all CPUs have performed &n; * a context switch or been seen in the idle loop or in a user process. &n; * The read-side of critical section that use call_rcu() for updation must &n; * be protected by rcu_read_lock()/rcu_read_unlock().&n; */
DECL|function|call_rcu
r_void
id|fastcall
id|call_rcu
c_func
(paren
r_struct
id|rcu_head
op_star
id|head
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|head-&gt;func
op_assign
id|func
suffix:semicolon
id|head-&gt;arg
op_assign
id|arg
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|head-&gt;list
comma
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Invoke the completed RCU callbacks. They are expected to be in&n; * a per-cpu list.&n; */
DECL|function|rcu_do_batch
r_static
r_void
id|rcu_do_batch
c_func
(paren
r_struct
id|list_head
op_star
id|list
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|rcu_head
op_star
id|head
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|list
)paren
)paren
(brace
id|entry
op_assign
id|list-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
id|entry
)paren
suffix:semicolon
id|head
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|rcu_head
comma
id|list
)paren
suffix:semicolon
id|head
op_member_access_from_pointer
id|func
c_func
(paren
id|head-&gt;arg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Register a new batch of callbacks, and start it up if there is currently no&n; * active batch and the batch to be registered has not already occurred.&n; * Caller must hold the rcu_ctrlblk lock.&n; */
DECL|function|rcu_start_batch
r_static
r_void
id|rcu_start_batch
c_func
(paren
r_int
id|newbatch
)paren
(brace
r_if
c_cond
(paren
id|rcu_batch_before
c_func
(paren
id|rcu_ctrlblk.maxbatch
comma
id|newbatch
)paren
)paren
(brace
id|rcu_ctrlblk.maxbatch
op_assign
id|newbatch
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rcu_batch_before
c_func
(paren
id|rcu_ctrlblk.maxbatch
comma
id|rcu_ctrlblk.curbatch
)paren
op_logical_or
op_logical_neg
id|cpus_empty
c_func
(paren
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Can&squot;t change, since spin lock held. */
id|rcu_ctrlblk.rcu_cpu_mask
op_assign
id|cpu_online_map
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if the cpu has gone through a quiescent state (say context&n; * switch). If so and if it already hasn&squot;t done so in this RCU&n; * quiescent cycle, then indicate that it has done so.&n; */
DECL|function|rcu_check_quiescent_state
r_static
r_void
id|rcu_check_quiescent_state
c_func
(paren
r_void
)paren
(brace
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
op_logical_neg
id|cpu_isset
c_func
(paren
id|cpu
comma
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* &n;&t; * Races with local timer interrupt - in the worst case&n;&t; * we may miss one quiescent state of that CPU. That is&n;&t; * tolerable. So no need to disable interrupts.&n;&t; */
r_if
c_cond
(paren
id|RCU_last_qsctr
c_func
(paren
id|cpu
)paren
op_eq
id|RCU_QSCTR_INVALID
)paren
(brace
id|RCU_last_qsctr
c_func
(paren
id|cpu
)paren
op_assign
id|RCU_qsctr
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|RCU_qsctr
c_func
(paren
id|cpu
)paren
op_eq
id|RCU_last_qsctr
c_func
(paren
id|cpu
)paren
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|cpu
comma
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|rcu_ctrlblk.rcu_cpu_mask
)paren
suffix:semicolon
id|RCU_last_qsctr
c_func
(paren
id|cpu
)paren
op_assign
id|RCU_QSCTR_INVALID
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|rcu_ctrlblk.curbatch
op_increment
suffix:semicolon
id|rcu_start_batch
c_func
(paren
id|rcu_ctrlblk.maxbatch
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
multiline_comment|/* warning! helper for rcu_offline_cpu. do not use elsewhere without reviewing&n; * locking requirements, the list it&squot;s pulling from has to belong to a cpu&n; * which is dead and hence not processing interrupts.&n; */
DECL|function|rcu_move_batch
r_static
r_void
id|rcu_move_batch
c_func
(paren
r_struct
id|list_head
op_star
id|list
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|list
)paren
)paren
(brace
id|entry
op_assign
id|list-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
id|entry
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
id|entry
comma
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rcu_offline_cpu
r_static
r_void
id|rcu_offline_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if the cpu going offline owns the grace period&n;&t; * we can block indefinitely waiting for it, so flush&n;&t; * it here&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rcu_ctrlblk.rcu_cpu_mask
)paren
r_goto
id|unlock
suffix:semicolon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|rcu_ctrlblk.rcu_cpu_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
(brace
id|rcu_ctrlblk.curbatch
op_increment
suffix:semicolon
multiline_comment|/* We may avoid calling start batch if&n;&t;&t; * we are starting the batch only&n;&t;&t; * because of the DEAD CPU (the current&n;&t;&t; * CPU will start a new batch anyway for&n;&t;&t; * the callbacks we will move to current CPU).&n;&t;&t; * However, we will avoid this optimisation&n;&t;&t; * for now.&n;&t;&t; */
id|rcu_start_batch
c_func
(paren
id|rcu_ctrlblk.maxbatch
)paren
suffix:semicolon
)brace
id|unlock
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
id|rcu_move_batch
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|rcu_move_batch
c_func
(paren
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|tasklet_kill_immediate
c_func
(paren
op_amp
id|RCU_tasklet
c_func
(paren
id|cpu
)paren
comma
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * This does the RCU processing work from tasklet context. &n; */
DECL|function|rcu_process_callbacks
r_static
r_void
id|rcu_process_callbacks
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
op_logical_and
id|rcu_batch_after
c_func
(paren
id|rcu_ctrlblk.curbatch
comma
id|RCU_batch
c_func
(paren
id|cpu
)paren
)paren
)paren
(brace
id|list_splice
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
comma
op_amp
id|list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
)paren
(brace
id|list_splice
c_func
(paren
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
comma
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * start the next batch of callbacks&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
id|RCU_batch
c_func
(paren
id|cpu
)paren
op_assign
id|rcu_ctrlblk.curbatch
op_plus
l_int|1
suffix:semicolon
id|rcu_start_batch
c_func
(paren
id|RCU_batch
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rcu_ctrlblk.mutex
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
id|rcu_check_quiescent_state
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|list
)paren
)paren
id|rcu_do_batch
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
)brace
DECL|function|rcu_check_callbacks
r_void
id|rcu_check_callbacks
c_func
(paren
r_int
id|cpu
comma
r_int
id|user
)paren
(brace
r_if
c_cond
(paren
id|user
op_logical_or
(paren
id|idle_cpu
c_func
(paren
id|cpu
)paren
op_logical_and
op_logical_neg
id|in_softirq
c_func
(paren
)paren
op_logical_and
id|hardirq_count
c_func
(paren
)paren
op_le
(paren
l_int|1
op_lshift
id|HARDIRQ_SHIFT
)paren
)paren
)paren
id|RCU_qsctr
c_func
(paren
id|cpu
)paren
op_increment
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|RCU_tasklet
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
DECL|function|rcu_online_cpu
r_static
r_void
id|__devinit
id|rcu_online_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
id|memset
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|rcu_data
comma
id|cpu
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rcu_data
)paren
)paren
suffix:semicolon
id|tasklet_init
c_func
(paren
op_amp
id|RCU_tasklet
c_func
(paren
id|cpu
)paren
comma
id|rcu_process_callbacks
comma
l_int|0UL
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|RCU_nxtlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|RCU_curlist
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
DECL|function|rcu_cpu_notify
r_static
r_int
id|__devinit
id|rcu_cpu_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|action
comma
r_void
op_star
id|hcpu
)paren
(brace
r_int
id|cpu
op_assign
(paren
r_int
)paren
id|hcpu
suffix:semicolon
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|CPU_UP_PREPARE
suffix:colon
id|rcu_online_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_CPU
r_case
id|CPU_DEAD
suffix:colon
id|rcu_offline_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
DECL|variable|rcu_nb
r_static
r_struct
id|notifier_block
id|__devinitdata
id|rcu_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|rcu_cpu_notify
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initializes rcu mechanism.  Assumed to be called early.&n; * That is before local timer(SMP) or jiffie timer (uniproc) is setup.&n; * Note that rcu_qsctr and friends are implicitly&n; * initialized due to the choice of ``0&squot;&squot; for RCU_CTR_INVALID.&n; */
DECL|function|rcu_init
r_void
id|__init
id|rcu_init
c_func
(paren
r_void
)paren
(brace
id|rcu_cpu_notify
c_func
(paren
op_amp
id|rcu_nb
comma
id|CPU_UP_PREPARE
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Register notifier for non-boot CPUs */
id|register_cpu_notifier
c_func
(paren
op_amp
id|rcu_nb
)paren
suffix:semicolon
)brace
multiline_comment|/* Because of FASTCALL declaration of complete, we use this wrapper */
DECL|function|wakeme_after_rcu
r_static
r_void
id|wakeme_after_rcu
c_func
(paren
r_void
op_star
id|completion
)paren
(brace
id|complete
c_func
(paren
id|completion
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * synchronize-kernel - wait until all the CPUs have gone&n; * through a &quot;quiescent&quot; state. It may sleep.&n; */
DECL|function|synchronize_kernel
r_void
id|synchronize_kernel
c_func
(paren
r_void
)paren
(brace
r_struct
id|rcu_head
id|rcu
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|completion
)paren
suffix:semicolon
multiline_comment|/* Will wake me after RCU finished */
id|call_rcu
c_func
(paren
op_amp
id|rcu
comma
id|wakeme_after_rcu
comma
op_amp
id|completion
)paren
suffix:semicolon
multiline_comment|/* Wait for it */
id|wait_for_completion
c_func
(paren
op_amp
id|completion
)paren
suffix:semicolon
)brace
DECL|variable|call_rcu
id|EXPORT_SYMBOL
c_func
(paren
id|call_rcu
)paren
suffix:semicolon
DECL|variable|synchronize_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_kernel
)paren
suffix:semicolon
eof
