multiline_comment|/*&n; * Read-Copy Update mechanism for mutual exclusion &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2001&n; *&n; * Author: Dipankar Sarma &lt;dipankar@in.ibm.com&gt;&n; * &n; * Based on the original work by Paul McKenney &lt;paul.mckenney@us.ibm.com&gt;&n; * and inputs from Rusty Russell, Andrea Arcangeli and Andi Kleen.&n; * Papers:&n; * http://www.rdrop.com/users/paulmck/paper/rclockpdcsproof.pdf&n; * http://lse.sourceforge.net/locking/rclock_OLS.2001.05.01c.sc.pdf (OLS2001)&n; *&n; * For detailed explanation of Read-Copy Update mechanism see -&n; * &t;&t;http://lse.sourceforge.net/locking/rcupdate.html&n; *&n; */
macro_line|#ifndef __LINUX_RCUPDATE_H
DECL|macro|__LINUX_RCUPDATE_H
mdefine_line|#define __LINUX_RCUPDATE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/seqlock.h&gt;
multiline_comment|/**&n; * struct rcu_head - callback structure for use with RCU&n; * @next: next update requests in a list&n; * @func: actual update function to call after the grace period.&n; */
DECL|struct|rcu_head
r_struct
id|rcu_head
(brace
DECL|member|next
r_struct
id|rcu_head
op_star
id|next
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_struct
id|rcu_head
op_star
id|head
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RCU_HEAD_INIT
mdefine_line|#define RCU_HEAD_INIT(head) { .next = NULL, .func = NULL }
DECL|macro|RCU_HEAD
mdefine_line|#define RCU_HEAD(head) struct rcu_head head = RCU_HEAD_INIT(head)
DECL|macro|INIT_RCU_HEAD
mdefine_line|#define INIT_RCU_HEAD(ptr) do { &bslash;&n;       (ptr)-&gt;next = NULL; (ptr)-&gt;func = NULL; &bslash;&n;} while (0)
multiline_comment|/* Global control variables for rcupdate callback mechanism. */
DECL|struct|rcu_ctrlblk
r_struct
id|rcu_ctrlblk
(brace
DECL|member|cur
r_int
id|cur
suffix:semicolon
multiline_comment|/* Current batch number.                      */
DECL|member|completed
r_int
id|completed
suffix:semicolon
multiline_comment|/* Number of the last completed batch         */
DECL|member|next_pending
r_int
id|next_pending
suffix:semicolon
multiline_comment|/* Is the next batch already waiting?         */
DECL|member|lock
id|seqcount_t
id|lock
suffix:semicolon
multiline_comment|/* For atomic reads of cur and next_pending.  */
DECL|variable|____cacheline_maxaligned_in_smp
)brace
id|____cacheline_maxaligned_in_smp
suffix:semicolon
multiline_comment|/* Is batch a before batch b ? */
DECL|function|rcu_batch_before
r_static
r_inline
r_int
id|rcu_batch_before
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_return
(paren
id|a
op_minus
id|b
)paren
OL
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Is batch a after batch b ? */
DECL|function|rcu_batch_after
r_static
r_inline
r_int
id|rcu_batch_after
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_return
(paren
id|a
op_minus
id|b
)paren
OG
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Per-CPU data for Read-Copy UPdate.&n; * nxtlist - new callbacks are added here&n; * curlist - current batch for which quiescent cycle started if any&n; */
DECL|struct|rcu_data
r_struct
id|rcu_data
(brace
multiline_comment|/* 1) quiescent state handling : */
DECL|member|quiescbatch
r_int
id|quiescbatch
suffix:semicolon
multiline_comment|/* Batch # for grace period */
DECL|member|qsctr
r_int
id|qsctr
suffix:semicolon
multiline_comment|/* User-mode/idle loop etc. */
DECL|member|last_qsctr
r_int
id|last_qsctr
suffix:semicolon
multiline_comment|/* value of qsctr at beginning */
multiline_comment|/* of rcu grace period */
DECL|member|qs_pending
r_int
id|qs_pending
suffix:semicolon
multiline_comment|/* core waits for quiesc state */
multiline_comment|/* 2) batch handling */
DECL|member|batch
r_int
id|batch
suffix:semicolon
multiline_comment|/* Batch # for current RCU batch */
DECL|member|nxtlist
r_struct
id|rcu_head
op_star
id|nxtlist
suffix:semicolon
DECL|member|nxttail
r_struct
id|rcu_head
op_star
op_star
id|nxttail
suffix:semicolon
DECL|member|curlist
r_struct
id|rcu_head
op_star
id|curlist
suffix:semicolon
DECL|member|curtail
r_struct
id|rcu_head
op_star
op_star
id|curtail
suffix:semicolon
DECL|member|donelist
r_struct
id|rcu_head
op_star
id|donelist
suffix:semicolon
DECL|member|donetail
r_struct
id|rcu_head
op_star
op_star
id|donetail
suffix:semicolon
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|rcu_data
comma
id|rcu_data
)paren
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|rcu_data
comma
id|rcu_bh_data
)paren
suffix:semicolon
r_extern
r_struct
id|rcu_ctrlblk
id|rcu_ctrlblk
suffix:semicolon
r_extern
r_struct
id|rcu_ctrlblk
id|rcu_bh_ctrlblk
suffix:semicolon
multiline_comment|/*&n; * Increment the quiscent state counter.&n; */
DECL|function|rcu_qsctr_inc
r_static
r_inline
r_void
id|rcu_qsctr_inc
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
id|rdp-&gt;qsctr
op_increment
suffix:semicolon
)brace
DECL|function|rcu_bh_qsctr_inc
r_static
r_inline
r_void
id|rcu_bh_qsctr_inc
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
id|rcu_bh_data
comma
id|cpu
)paren
suffix:semicolon
id|rdp-&gt;qsctr
op_increment
suffix:semicolon
)brace
DECL|function|__rcu_pending
r_static
r_inline
r_int
id|__rcu_pending
c_func
(paren
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
multiline_comment|/* This cpu has pending rcu entries and the grace period&n;&t; * for them has completed.&n;&t; */
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
r_return
l_int|1
suffix:semicolon
multiline_comment|/* This cpu has no pending entries, but there are new entries */
r_if
c_cond
(paren
op_logical_neg
id|rdp-&gt;curlist
op_logical_and
id|rdp-&gt;nxtlist
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* This cpu has finished callbacks to invoke */
r_if
c_cond
(paren
id|rdp-&gt;donelist
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* The rcu core waits for a quiescent state from the cpu */
r_if
c_cond
(paren
id|rdp-&gt;quiescbatch
op_ne
id|rcp-&gt;cur
op_logical_or
id|rdp-&gt;qs_pending
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* nothing to do */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rcu_pending
r_static
r_inline
r_int
id|rcu_pending
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|__rcu_pending
c_func
(paren
op_amp
id|rcu_ctrlblk
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
op_logical_or
id|__rcu_pending
c_func
(paren
op_amp
id|rcu_bh_ctrlblk
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
)brace
multiline_comment|/**&n; * rcu_read_lock - mark the beginning of an RCU read-side critical section.&n; *&n; * When synchronize_kernel() is invoked on one CPU while other CPUs&n; * are within RCU read-side critical sections, then the&n; * synchronize_kernel() is guaranteed to block until after all the other&n; * CPUs exit their critical sections.  Similarly, if call_rcu() is invoked&n; * on one CPU while other CPUs are within RCU read-side critical&n; * sections, invocation of the corresponding RCU callback is deferred&n; * until after the all the other CPUs exit their critical sections.&n; *&n; * Note, however, that RCU callbacks are permitted to run concurrently&n; * with RCU read-side critical sections.  One way that this can happen&n; * is via the following sequence of events: (1) CPU 0 enters an RCU&n; * read-side critical section, (2) CPU 1 invokes call_rcu() to register&n; * an RCU callback, (3) CPU 0 exits the RCU read-side critical section,&n; * (4) CPU 2 enters a RCU read-side critical section, (5) the RCU&n; * callback is invoked.  This is legal, because the RCU read-side critical&n; * section that was running concurrently with the call_rcu() (and which&n; * therefore might be referencing something that the corresponding RCU&n; * callback would free up) has completed before the corresponding&n; * RCU callback is invoked.&n; *&n; * RCU read-side critical sections may be nested.  Any deferred actions&n; * will be deferred until the outermost RCU read-side critical section&n; * completes.&n; *&n; * It is illegal to block while in an RCU read-side critical section.&n; */
DECL|macro|rcu_read_lock
mdefine_line|#define rcu_read_lock()&t;&t;preempt_disable()
multiline_comment|/**&n; * rcu_read_unlock - marks the end of an RCU read-side critical section.&n; *&n; * See rcu_read_lock() for more information.&n; */
DECL|macro|rcu_read_unlock
mdefine_line|#define rcu_read_unlock()&t;preempt_enable()
multiline_comment|/*&n; * So where is rcu_write_lock()?  It does not exist, as there is no&n; * way for writers to lock out RCU readers.  This is a feature, not&n; * a bug -- this property is what provides RCU&squot;s performance benefits.&n; * Of course, writers must coordinate with each other.  The normal&n; * spinlock primitives work well for this, but any other technique may be&n; * used as well.  RCU does not care how the writers keep out of each&n; * others&squot; way, as long as they do so.&n; */
multiline_comment|/**&n; * rcu_read_lock_bh - mark the beginning of a softirq-only RCU critical section&n; *&n; * This is equivalent of rcu_read_lock(), but to be used when updates&n; * are being done using call_rcu_bh(). Since call_rcu_bh() callbacks&n; * consider completion of a softirq handler to be a quiescent state,&n; * a process in RCU read-side critical section must be protected by&n; * disabling softirqs. Read-side critical sections in interrupt context&n; * can use just rcu_read_lock().&n; *&n; */
DECL|macro|rcu_read_lock_bh
mdefine_line|#define rcu_read_lock_bh()&t;local_bh_disable()
multiline_comment|/*&n; * rcu_read_unlock_bh - marks the end of a softirq-only RCU critical section&n; *&n; * See rcu_read_lock_bh() for more information.&n; */
DECL|macro|rcu_read_unlock_bh
mdefine_line|#define rcu_read_unlock_bh()&t;local_bh_enable()
multiline_comment|/**&n; * rcu_dereference - fetch an RCU-protected pointer in an&n; * RCU read-side critical section.  This pointer may later&n; * be safely dereferenced.&n; *&n; * Inserts memory barriers on architectures that require them&n; * (currently only the Alpha), and, more importantly, documents&n; * exactly which pointers are protected by RCU.&n; */
DECL|macro|rcu_dereference
mdefine_line|#define rcu_dereference(p)     ({ &bslash;&n;&t;&t;&t;&t;typeof(p) _________p1 = p; &bslash;&n;&t;&t;&t;&t;smp_read_barrier_depends(); &bslash;&n;&t;&t;&t;&t;(_________p1); &bslash;&n;&t;&t;&t;&t;})
multiline_comment|/**&n; * rcu_assign_pointer - assign (publicize) a pointer to a newly&n; * initialized structure that will be dereferenced by RCU read-side&n; * critical sections.  Returns the value assigned.&n; *&n; * Inserts memory barriers on architectures that require them&n; * (pretty much all of them other than x86), and also prevents&n; * the compiler from reordering the code that initializes the&n; * structure after the pointer assignment.  More importantly, this&n; * call documents which pointers will be dereferenced by RCU read-side&n; * code.&n; */
DECL|macro|rcu_assign_pointer
mdefine_line|#define rcu_assign_pointer(p, v)&t;({ &bslash;&n;&t;&t;&t;&t;&t;&t;smp_wmb(); &bslash;&n;&t;&t;&t;&t;&t;&t;(p) = (v); &bslash;&n;&t;&t;&t;&t;&t;})
r_extern
r_void
id|rcu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|rcu_restart_cpu
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Exported interfaces */
r_extern
r_void
id|FASTCALL
c_func
(paren
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
id|head
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
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
id|head
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|synchronize_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_RCUPDATE_H */
eof
