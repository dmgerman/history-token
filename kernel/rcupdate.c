multiline_comment|/*&n; * Read-Copy Update mechanism for mutual exclusion&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2001&n; *&n; * Authors: Dipankar Sarma &lt;dipankar@in.ibm.com&gt;&n; *&t;    Manfred Spraul &lt;manfred@colorfullife.com&gt;&n; * &n; * Based on the original work by Paul McKenney &lt;paulmck@us.ibm.com&gt;&n; * and inputs from Rusty Russell, Andrea Arcangeli and Andi Kleen.&n; * Papers:&n; * http://www.rdrop.com/users/paulmck/paper/rclockpdcsproof.pdf&n; * http://lse.sourceforge.net/locking/rclock_OLS.2001.05.01c.sc.pdf (OLS2001)&n; *&n; * For detailed explanation of Read-Copy Update mechanism see -&n; * &t;&t;http://lse.sourceforge.net/locking/rcupdate.html&n; *&n; */
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
macro_line|#include &lt;linux/moduleparam.h&gt;
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
id|cur
op_assign
op_minus
l_int|300
comma
dot
id|completed
op_assign
op_minus
l_int|300
comma
dot
id|lock
op_assign
id|SEQCNT_ZERO
)brace
suffix:semicolon
DECL|variable|rcu_bh_ctrlblk
r_struct
id|rcu_ctrlblk
id|rcu_bh_ctrlblk
op_assign
(brace
dot
id|cur
op_assign
op_minus
l_int|300
comma
dot
id|completed
op_assign
op_minus
l_int|300
comma
dot
id|lock
op_assign
id|SEQCNT_ZERO
)brace
suffix:semicolon
multiline_comment|/* Bookkeeping of the progress of the grace period */
DECL|struct|rcu_state
r_struct
id|rcu_state
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Guard this struct and writes to rcu_ctrlblk */
DECL|member|cpumask
id|cpumask_t
id|cpumask
suffix:semicolon
multiline_comment|/* CPUs that need to switch in order    */
multiline_comment|/* for current batch to proceed.        */
)brace
suffix:semicolon
DECL|variable|____cacheline_maxaligned_in_smp
r_struct
id|rcu_state
id|rcu_state
id|____cacheline_maxaligned_in_smp
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|cpumask
op_assign
id|CPU_MASK_NONE
)brace
suffix:semicolon
DECL|variable|____cacheline_maxaligned_in_smp
r_struct
id|rcu_state
id|rcu_bh_state
id|____cacheline_maxaligned_in_smp
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|cpumask
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
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|rcu_data
comma
id|rcu_bh_data
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
DECL|variable|maxbatch
r_static
r_int
id|maxbatch
op_assign
l_int|10
suffix:semicolon
multiline_comment|/**&n; * call_rcu - Queue an RCU update request.&n; * @head: structure to be used for queueing the RCU updates.&n; * @func: actual update function to be invoked after the grace period&n; *&n; * The update function will be invoked as soon as all CPUs have performed &n; * a context switch or been seen in the idle loop or in a user process. &n; * The read-side of critical section that use call_rcu() for updation must &n; * be protected by rcu_read_lock()/rcu_read_unlock().&n; */
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
r_struct
id|rcu_head
op_star
id|rcu
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|rcu_data
op_star
id|rdp
suffix:semicolon
id|head-&gt;func
op_assign
id|func
suffix:semicolon
id|head-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|rdp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|rcu_data
)paren
suffix:semicolon
op_star
id|rdp-&gt;nxttail
op_assign
id|head
suffix:semicolon
id|rdp-&gt;nxttail
op_assign
op_amp
id|head-&gt;next
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * call_rcu_bh - Queue an RCU update request for which softirq handler&n; * completion is a quiescent state.&n; * @head: structure to be used for queueing the RCU updates.&n; * @func: actual update function to be invoked after the grace period&n; *&n; * The update function will be invoked as soon as all CPUs have performed&n; * a context switch or been seen in the idle loop or in a user process&n; * or has exited a softirq handler that it may have been executing.&n; * The read-side of critical section that use call_rcu_bh() for updation must&n; * be protected by rcu_read_lock_bh()/rcu_read_unlock_bh() if it is&n; * in process context.&n; */
DECL|function|call_rcu_bh
r_void
id|fastcall
id|call_rcu_bh
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
r_struct
id|rcu_head
op_star
id|rcu
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|rcu_data
op_star
id|rdp
suffix:semicolon
id|head-&gt;func
op_assign
id|func
suffix:semicolon
id|head-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|rdp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|rcu_bh_data
)paren
suffix:semicolon
op_star
id|rdp-&gt;nxttail
op_assign
id|head
suffix:semicolon
id|rdp-&gt;nxttail
op_assign
op_amp
id|head-&gt;next
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
id|rcu_data
op_star
id|rdp
)paren
(brace
r_struct
id|rcu_head
op_star
id|next
comma
op_star
id|list
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|list
op_assign
id|rdp-&gt;donelist
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
id|next
op_assign
id|rdp-&gt;donelist
op_assign
id|list-&gt;next
suffix:semicolon
id|list
op_member_access_from_pointer
id|func
c_func
(paren
id|list
)paren
suffix:semicolon
id|list
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
op_ge
id|maxbatch
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rdp-&gt;donelist
)paren
id|rdp-&gt;donetail
op_assign
op_amp
id|rdp-&gt;donelist
suffix:semicolon
r_else
id|tasklet_schedule
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|rcu_tasklet
comma
id|rdp-&gt;cpu
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Grace period handling:&n; * The grace period handling consists out of two steps:&n; * - A new grace period is started.&n; *   This is done by rcu_start_batch. The start is not broadcasted to&n; *   all cpus, they must pick this up by comparing rcp-&gt;cur with&n; *   rdp-&gt;quiescbatch. All cpus are recorded  in the&n; *   rcu_state.cpumask bitmap.&n; * - All cpus must go through a quiescent state.&n; *   Since the start of the grace period is not broadcasted, at least two&n; *   calls to rcu_check_quiescent_state are required:&n; *   The first call just notices that a new grace period is running. The&n; *   following calls check if there was a quiescent state since the beginning&n; *   of the grace period. If so, it updates rcu_state.cpumask. If&n; *   the bitmap is empty, then the grace period is completed.&n; *   rcu_check_quiescent_state calls rcu_start_batch(0) to start the next grace&n; *   period (if necessary).&n; */
multiline_comment|/*&n; * Register a new batch of callbacks, and start it up if there is currently no&n; * active batch and the batch to be registered has not already occurred.&n; * Caller must hold rcu_state.lock.&n; */
DECL|function|rcu_start_batch
r_static
r_void
id|rcu_start_batch
c_func
(paren
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_state
op_star
id|rsp
comma
r_int
id|next_pending
)paren
(brace
r_if
c_cond
(paren
id|next_pending
)paren
id|rcp-&gt;next_pending
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rcp-&gt;next_pending
op_logical_and
id|rcp-&gt;completed
op_eq
id|rcp-&gt;cur
)paren
(brace
multiline_comment|/* Can&squot;t change, since spin lock held. */
id|cpus_andnot
c_func
(paren
id|rsp-&gt;cpumask
comma
id|cpu_online_map
comma
id|nohz_cpu_mask
)paren
suffix:semicolon
id|write_seqcount_begin
c_func
(paren
op_amp
id|rcp-&gt;lock
)paren
suffix:semicolon
id|rcp-&gt;next_pending
op_assign
l_int|0
suffix:semicolon
id|rcp-&gt;cur
op_increment
suffix:semicolon
id|write_seqcount_end
c_func
(paren
op_amp
id|rcp-&gt;lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * cpu went through a quiescent state since the beginning of the grace period.&n; * Clear it from the cpu mask and complete the grace period if it was the last&n; * cpu. Start another grace period if someone has further entries pending&n; */
DECL|function|cpu_quiet
r_static
r_void
id|cpu_quiet
c_func
(paren
r_int
id|cpu
comma
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_state
op_star
id|rsp
)paren
(brace
id|cpu_clear
c_func
(paren
id|cpu
comma
id|rsp-&gt;cpumask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|rsp-&gt;cpumask
)paren
)paren
(brace
multiline_comment|/* batch completed ! */
id|rcp-&gt;completed
op_assign
id|rcp-&gt;cur
suffix:semicolon
id|rcu_start_batch
c_func
(paren
id|rcp
comma
id|rsp
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check if the cpu has gone through a quiescent state (say context&n; * switch). If so and if it already hasn&squot;t done so in this RCU&n; * quiescent cycle, then indicate that it has done so.&n; */
DECL|function|rcu_check_quiescent_state
r_static
r_void
id|rcu_check_quiescent_state
c_func
(paren
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_state
op_star
id|rsp
comma
r_struct
id|rcu_data
op_star
id|rdp
)paren
(brace
r_if
c_cond
(paren
id|rdp-&gt;quiescbatch
op_ne
id|rcp-&gt;cur
)paren
(brace
multiline_comment|/* new grace period: record qsctr value. */
id|rdp-&gt;qs_pending
op_assign
l_int|1
suffix:semicolon
id|rdp-&gt;last_qsctr
op_assign
id|rdp-&gt;qsctr
suffix:semicolon
id|rdp-&gt;quiescbatch
op_assign
id|rcp-&gt;cur
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Grace period already completed for this cpu?&n;&t; * qs_pending is checked instead of the actual bitmap to avoid&n;&t; * cacheline trashing.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rdp-&gt;qs_pending
)paren
r_return
suffix:semicolon
multiline_comment|/* &n;&t; * Races with local timer interrupt - in the worst case&n;&t; * we may miss one quiescent state of that CPU. That is&n;&t; * tolerable. So no need to disable interrupts.&n;&t; */
r_if
c_cond
(paren
id|rdp-&gt;qsctr
op_eq
id|rdp-&gt;last_qsctr
)paren
r_return
suffix:semicolon
id|rdp-&gt;qs_pending
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rsp-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * rdp-&gt;quiescbatch/rcp-&gt;cur and the cpu bitmap can come out of sync&n;&t; * during cpu startup. Ignore the quiescent state.&n;&t; */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|rdp-&gt;quiescbatch
op_eq
id|rcp-&gt;cur
)paren
)paren
id|cpu_quiet
c_func
(paren
id|rdp-&gt;cpu
comma
id|rcp
comma
id|rsp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rsp-&gt;lock
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
id|rcu_data
op_star
id|this_rdp
comma
r_struct
id|rcu_head
op_star
id|list
comma
r_struct
id|rcu_head
op_star
op_star
id|tail
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
op_star
id|this_rdp-&gt;nxttail
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
id|list
)paren
id|this_rdp-&gt;nxttail
op_assign
id|tail
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__rcu_offline_cpu
r_static
r_void
id|__rcu_offline_cpu
c_func
(paren
r_struct
id|rcu_data
op_star
id|this_rdp
comma
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_state
op_star
id|rsp
comma
r_struct
id|rcu_data
op_star
id|rdp
)paren
(brace
multiline_comment|/* if the cpu going offline owns the grace period&n;&t; * we can block indefinitely waiting for it, so flush&n;&t; * it here&n;&t; */
id|spin_lock_bh
c_func
(paren
op_amp
id|rsp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rcp-&gt;cur
op_ne
id|rcp-&gt;completed
)paren
id|cpu_quiet
c_func
(paren
id|rdp-&gt;cpu
comma
id|rcp
comma
id|rsp
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|rsp-&gt;lock
)paren
suffix:semicolon
id|rcu_move_batch
c_func
(paren
id|this_rdp
comma
id|rdp-&gt;curlist
comma
id|rdp-&gt;curtail
)paren
suffix:semicolon
id|rcu_move_batch
c_func
(paren
id|this_rdp
comma
id|rdp-&gt;nxtlist
comma
id|rdp-&gt;nxttail
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
r_struct
id|rcu_data
op_star
id|this_rdp
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|rcu_data
)paren
suffix:semicolon
r_struct
id|rcu_data
op_star
id|this_bh_rdp
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|rcu_bh_data
)paren
suffix:semicolon
id|__rcu_offline_cpu
c_func
(paren
id|this_rdp
comma
op_amp
id|rcu_ctrlblk
comma
op_amp
id|rcu_state
comma
op_amp
id|per_cpu
c_func
(paren
id|rcu_data
comma
id|cpu
)paren
)paren
suffix:semicolon
id|__rcu_offline_cpu
c_func
(paren
id|this_bh_rdp
comma
op_amp
id|rcu_bh_ctrlblk
comma
op_amp
id|rcu_bh_state
comma
op_amp
id|per_cpu
c_func
(paren
id|rcu_bh_data
comma
id|cpu
)paren
)paren
suffix:semicolon
id|put_cpu_var
c_func
(paren
id|rcu_data
)paren
suffix:semicolon
id|put_cpu_var
c_func
(paren
id|rcu_bh_data
)paren
suffix:semicolon
id|tasklet_kill_immediate
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|rcu_tasklet
comma
id|cpu
)paren
comma
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#else
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
)brace
macro_line|#endif
multiline_comment|/*&n; * This does the RCU processing work from tasklet context. &n; */
DECL|function|__rcu_process_callbacks
r_static
r_void
id|__rcu_process_callbacks
c_func
(paren
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_state
op_star
id|rsp
comma
r_struct
id|rcu_data
op_star
id|rdp
)paren
(brace
r_if
c_cond
(paren
id|rdp-&gt;curlist
op_logical_and
op_logical_neg
id|rcu_batch_before
c_func
(paren
id|rcp-&gt;completed
comma
id|rdp-&gt;batch
)paren
)paren
(brace
op_star
id|rdp-&gt;donetail
op_assign
id|rdp-&gt;curlist
suffix:semicolon
id|rdp-&gt;donetail
op_assign
id|rdp-&gt;curtail
suffix:semicolon
id|rdp-&gt;curlist
op_assign
l_int|NULL
suffix:semicolon
id|rdp-&gt;curtail
op_assign
op_amp
id|rdp-&gt;curlist
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
id|rdp-&gt;nxtlist
op_logical_and
op_logical_neg
id|rdp-&gt;curlist
)paren
(brace
r_int
id|next_pending
comma
id|seq
suffix:semicolon
id|rdp-&gt;curlist
op_assign
id|rdp-&gt;nxtlist
suffix:semicolon
id|rdp-&gt;curtail
op_assign
id|rdp-&gt;nxttail
suffix:semicolon
id|rdp-&gt;nxtlist
op_assign
l_int|NULL
suffix:semicolon
id|rdp-&gt;nxttail
op_assign
op_amp
id|rdp-&gt;nxtlist
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * start the next batch of callbacks&n;&t;&t; */
r_do
(brace
id|seq
op_assign
id|read_seqcount_begin
c_func
(paren
op_amp
id|rcp-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* determine batch number */
id|rdp-&gt;batch
op_assign
id|rcp-&gt;cur
op_plus
l_int|1
suffix:semicolon
id|next_pending
op_assign
id|rcp-&gt;next_pending
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqcount_retry
c_func
(paren
op_amp
id|rcp-&gt;lock
comma
id|seq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_pending
)paren
(brace
multiline_comment|/* and start it/schedule start if it&squot;s a new batch */
id|spin_lock
c_func
(paren
op_amp
id|rsp-&gt;lock
)paren
suffix:semicolon
id|rcu_start_batch
c_func
(paren
id|rcp
comma
id|rsp
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rsp-&gt;lock
)paren
suffix:semicolon
)brace
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
id|rcp
comma
id|rsp
comma
id|rdp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdp-&gt;donelist
)paren
id|rcu_do_batch
c_func
(paren
id|rdp
)paren
suffix:semicolon
)brace
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
id|__rcu_process_callbacks
c_func
(paren
op_amp
id|rcu_ctrlblk
comma
op_amp
id|rcu_state
comma
op_amp
id|__get_cpu_var
c_func
(paren
id|rcu_data
)paren
)paren
suffix:semicolon
id|__rcu_process_callbacks
c_func
(paren
op_amp
id|rcu_bh_ctrlblk
comma
op_amp
id|rcu_bh_state
comma
op_amp
id|__get_cpu_var
c_func
(paren
id|rcu_bh_data
)paren
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
(brace
id|rcu_qsctr_inc
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|rcu_bh_qsctr_inc
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|in_softirq
c_func
(paren
)paren
)paren
id|rcu_bh_qsctr_inc
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|rcu_tasklet
comma
id|cpu
)paren
)paren
suffix:semicolon
)brace
DECL|function|rcu_init_percpu_data
r_static
r_void
id|rcu_init_percpu_data
c_func
(paren
r_int
id|cpu
comma
r_struct
id|rcu_ctrlblk
op_star
id|rcp
comma
r_struct
id|rcu_data
op_star
id|rdp
)paren
(brace
id|memset
c_func
(paren
id|rdp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|rdp
)paren
)paren
suffix:semicolon
id|rdp-&gt;curtail
op_assign
op_amp
id|rdp-&gt;curlist
suffix:semicolon
id|rdp-&gt;nxttail
op_assign
op_amp
id|rdp-&gt;nxtlist
suffix:semicolon
id|rdp-&gt;donetail
op_assign
op_amp
id|rdp-&gt;donelist
suffix:semicolon
id|rdp-&gt;quiescbatch
op_assign
id|rcp-&gt;completed
suffix:semicolon
id|rdp-&gt;qs_pending
op_assign
l_int|0
suffix:semicolon
id|rdp-&gt;cpu
op_assign
id|cpu
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
r_struct
id|rcu_data
op_star
id|rdp
op_assign
op_amp
id|per_cpu
c_func
(paren
id|rcu_data
comma
id|cpu
)paren
suffix:semicolon
r_struct
id|rcu_data
op_star
id|bh_rdp
op_assign
op_amp
id|per_cpu
c_func
(paren
id|rcu_bh_data
comma
id|cpu
)paren
suffix:semicolon
id|rcu_init_percpu_data
c_func
(paren
id|cpu
comma
op_amp
id|rcu_ctrlblk
comma
id|rdp
)paren
suffix:semicolon
id|rcu_init_percpu_data
c_func
(paren
id|cpu
comma
op_amp
id|rcu_bh_ctrlblk
comma
id|bh_rdp
)paren
suffix:semicolon
id|tasklet_init
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|rcu_tasklet
comma
id|cpu
)paren
comma
id|rcu_process_callbacks
comma
l_int|0UL
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
DECL|struct|rcu_synchronize
r_struct
id|rcu_synchronize
(brace
DECL|member|head
r_struct
id|rcu_head
id|head
suffix:semicolon
DECL|member|completion
r_struct
id|completion
id|completion
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Because of FASTCALL declaration of complete, we use this wrapper */
DECL|function|wakeme_after_rcu
r_static
r_void
id|wakeme_after_rcu
c_func
(paren
r_struct
id|rcu_head
op_star
id|head
)paren
(brace
r_struct
id|rcu_synchronize
op_star
id|rcu
suffix:semicolon
id|rcu
op_assign
id|container_of
c_func
(paren
id|head
comma
r_struct
id|rcu_synchronize
comma
id|head
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|rcu-&gt;completion
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
id|rcu_synchronize
id|rcu
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|rcu.completion
)paren
suffix:semicolon
multiline_comment|/* Will wake me after RCU finished */
id|call_rcu
c_func
(paren
op_amp
id|rcu.head
comma
id|wakeme_after_rcu
)paren
suffix:semicolon
multiline_comment|/* Wait for it */
id|wait_for_completion
c_func
(paren
op_amp
id|rcu.completion
)paren
suffix:semicolon
)brace
id|module_param
c_func
(paren
id|maxbatch
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|call_rcu
id|EXPORT_SYMBOL
c_func
(paren
id|call_rcu
)paren
suffix:semicolon
DECL|variable|call_rcu_bh
id|EXPORT_SYMBOL
c_func
(paren
id|call_rcu_bh
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
