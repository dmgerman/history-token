multiline_comment|/*&n; * Read-Copy Update mechanism for mutual exclusion &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (c) IBM Corporation, 2001&n; *&n; * Author: Dipankar Sarma &lt;dipankar@in.ibm.com&gt;&n; * &n; * Based on the original work by Paul McKenney &lt;paul.mckenney@us.ibm.com&gt;&n; * and inputs from Rusty Russell, Andrea Arcangeli and Andi Kleen.&n; * Papers:&n; * http://www.rdrop.com/users/paulmck/paper/rclockpdcsproof.pdf&n; * http://lse.sourceforge.net/locking/rclock_OLS.2001.05.01c.sc.pdf (OLS2001)&n; *&n; * For detailed explanation of Read-Copy Update mechanism see -&n; * &t;&t;http://lse.sourceforge.net/locking/rcupdate.html&n; *&n; */
macro_line|#ifndef __LINUX_RCUPDATE_H
DECL|macro|__LINUX_RCUPDATE_H
mdefine_line|#define __LINUX_RCUPDATE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
multiline_comment|/**&n; * struct rcu_head - callback structure for use with RCU&n; * @list: list_head to queue the update requests&n; * @func: actual update function to call after the grace period.&n; * @arg: argument to be passed to the actual update function.&n; */
DECL|struct|rcu_head
r_struct
id|rcu_head
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|obj
)paren
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RCU_HEAD_INIT
mdefine_line|#define RCU_HEAD_INIT(head) &bslash;&n;&t;&t;{ list: LIST_HEAD_INIT(head.list), func: NULL, arg: NULL }
DECL|macro|RCU_HEAD
mdefine_line|#define RCU_HEAD(head) struct rcu_head head = RCU_HEAD_INIT(head)
DECL|macro|INIT_RCU_HEAD
mdefine_line|#define INIT_RCU_HEAD(ptr) do { &bslash;&n;       INIT_LIST_HEAD(&amp;(ptr)-&gt;list); (ptr)-&gt;func = NULL; (ptr)-&gt;arg = NULL; &bslash;&n;} while (0)
multiline_comment|/* Control variables for rcupdate callback mechanism. */
DECL|struct|rcu_ctrlblk
r_struct
id|rcu_ctrlblk
(brace
DECL|member|mutex
id|spinlock_t
id|mutex
suffix:semicolon
multiline_comment|/* Guard this struct                  */
DECL|member|curbatch
r_int
id|curbatch
suffix:semicolon
multiline_comment|/* Current batch number.&t;      */
DECL|member|maxbatch
r_int
id|maxbatch
suffix:semicolon
multiline_comment|/* Max requested batch number.        */
DECL|member|rcu_cpu_mask
id|cpumask_t
id|rcu_cpu_mask
suffix:semicolon
multiline_comment|/* CPUs that need to switch in order  */
multiline_comment|/* for current batch to proceed.      */
)brace
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
DECL|member|batch
r_int
id|batch
suffix:semicolon
multiline_comment|/* Batch # for current RCU batch */
DECL|member|nxtlist
r_struct
id|list_head
id|nxtlist
suffix:semicolon
DECL|member|curlist
r_struct
id|list_head
id|curlist
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
r_extern
r_struct
id|rcu_ctrlblk
id|rcu_ctrlblk
suffix:semicolon
DECL|macro|RCU_qsctr
mdefine_line|#define RCU_qsctr(cpu) &t;&t;(per_cpu(rcu_data, (cpu)).qsctr)
DECL|macro|RCU_last_qsctr
mdefine_line|#define RCU_last_qsctr(cpu) &t;(per_cpu(rcu_data, (cpu)).last_qsctr)
DECL|macro|RCU_batch
mdefine_line|#define RCU_batch(cpu) &t;&t;(per_cpu(rcu_data, (cpu)).batch)
DECL|macro|RCU_nxtlist
mdefine_line|#define RCU_nxtlist(cpu) &t;(per_cpu(rcu_data, (cpu)).nxtlist)
DECL|macro|RCU_curlist
mdefine_line|#define RCU_curlist(cpu) &t;(per_cpu(rcu_data, (cpu)).curlist)
DECL|macro|RCU_QSCTR_INVALID
mdefine_line|#define RCU_QSCTR_INVALID&t;0
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
r_if
c_cond
(paren
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
id|rcu_batch_before
c_func
(paren
id|RCU_batch
c_func
(paren
id|cpu
)paren
comma
id|rcu_ctrlblk.curbatch
)paren
)paren
op_logical_or
(paren
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
)paren
op_logical_or
id|cpu_isset
c_func
(paren
id|cpu
comma
id|rcu_ctrlblk.rcu_cpu_mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|rcu_read_lock
mdefine_line|#define rcu_read_lock()&t;&t;preempt_disable()
DECL|macro|rcu_read_unlock
mdefine_line|#define rcu_read_unlock()&t;preempt_enable()
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
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|arg
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
