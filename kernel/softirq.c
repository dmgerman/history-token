multiline_comment|/*&n; *&t;linux/kernel/softirq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * Fixed a disable_bh()/enable_bh() race (was causing a console lockup)&n; * due bh_mask_count not atomic handling. Copyright (C) 1998  Andrea Arcangeli&n; *&n; * Rewritten. Old one was good in 2.2, but in 2.3 it was immoral. --ANK (990903)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
multiline_comment|/*&n;   - No shared variables, all the data are CPU local.&n;   - If a softirq needs serialization, let it serialize itself&n;     by its own spinlocks.&n;   - Even if softirq is serialized, only local cpu is marked for&n;     execution. Hence, we get something sort of weak cpu binding.&n;     Though it is still not clear, will it result in better locality&n;     or will not.&n;   - These softirqs are not masked by global cli() and start_bh_atomic()&n;     (by clear reasons). Hence, old parts of code still using global locks&n;     MUST NOT use softirqs, but insert interfacing routines acquiring&n;     global locks. F.e. look at BHs implementation.&n;&n;   Examples:&n;   - NET RX softirq. It is multithreaded and does not require&n;     any global serialization.&n;   - NET TX softirq. It kicks software netdevice queues, hence&n;     it is logically serialized per device, but this serialization&n;     is invisible to common code.&n;   - Tasklets: serialized wrt itself.&n;   - Bottom halves: globally serialized, grr...&n; */
DECL|variable|irq_stat
id|irq_cpustat_t
id|irq_stat
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__cacheline_aligned_in_smp
r_static
r_struct
id|softirq_action
id|softirq_vec
(braket
l_int|32
)braket
id|__cacheline_aligned_in_smp
suffix:semicolon
multiline_comment|/*&n; * we cannot loop indefinitely here to avoid userspace starvation,&n; * but we also don&squot;t want to introduce a worst case 1/HZ latency&n; * to the pending events, so lets the scheduler to balance&n; * the softirq load for us.&n; */
DECL|function|wakeup_softirqd
r_static
r_inline
r_void
id|wakeup_softirqd
c_func
(paren
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|ksoftirqd_task
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_logical_and
id|tsk-&gt;state
op_ne
id|TASK_RUNNING
)paren
id|wake_up_process
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|do_softirq
id|asmlinkage
r_void
id|do_softirq
c_func
(paren
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
id|__u32
id|pending
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|__u32
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
r_return
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
id|pending
op_assign
id|softirq_pending
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pending
)paren
(brace
r_struct
id|softirq_action
op_star
id|h
suffix:semicolon
id|mask
op_assign
op_complement
id|pending
suffix:semicolon
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|restart
suffix:colon
multiline_comment|/* Reset the pending bitmask before enabling irqs */
id|softirq_pending
c_func
(paren
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|h
op_assign
id|softirq_vec
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pending
op_amp
l_int|1
)paren
id|h
op_member_access_from_pointer
id|action
c_func
(paren
id|h
)paren
suffix:semicolon
id|h
op_increment
suffix:semicolon
id|pending
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pending
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|pending
op_assign
id|softirq_pending
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pending
op_amp
id|mask
)paren
(brace
id|mask
op_and_assign
op_complement
id|pending
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
id|__local_bh_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pending
)paren
id|wakeup_softirqd
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function must run with irq disabled!&n; */
DECL|function|cpu_raise_softirq
r_inline
r_void
id|cpu_raise_softirq
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
id|nr
)paren
(brace
id|__cpu_raise_softirq
c_func
(paren
id|cpu
comma
id|nr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or bh, we&squot;re done&n;&t; * (this also catches bh-disabled code). We will&n;&t; * actually run the softirq once we return from&n;&t; * the irq or bh.&n;&t; *&n;&t; * Otherwise we wake up ksoftirqd to make sure we&n;&t; * schedule the softirq soon.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_irq_count
c_func
(paren
id|cpu
)paren
op_or
id|local_bh_count
c_func
(paren
id|cpu
)paren
)paren
)paren
id|wakeup_softirqd
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|raise_softirq
r_void
id|raise_softirq
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|open_softirq
r_void
id|open_softirq
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|action
)paren
(paren
r_struct
id|softirq_action
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
id|softirq_vec
(braket
id|nr
)braket
dot
id|data
op_assign
id|data
suffix:semicolon
id|softirq_vec
(braket
id|nr
)braket
dot
id|action
op_assign
id|action
suffix:semicolon
)brace
multiline_comment|/* Tasklets */
DECL|struct|tasklet_head
r_struct
id|tasklet_head
(brace
DECL|member|list
r_struct
id|tasklet_struct
op_star
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Some compilers disobey section attribute on statics when not&n;   initialized -- RR */
DECL|variable|__per_cpu_data
r_static
r_struct
id|tasklet_head
id|tasklet_vec
id|__per_cpu_data
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|variable|__per_cpu_data
r_static
r_struct
id|tasklet_head
id|tasklet_hi_vec
id|__per_cpu_data
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|function|__tasklet_schedule
r_void
id|__tasklet_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
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
id|t-&gt;next
op_assign
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|TASKLET_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__tasklet_hi_schedule
r_void
id|__tasklet_hi_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
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
id|t-&gt;next
op_assign
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|HI_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|tasklet_action
r_static
r_void
id|tasklet_action
c_func
(paren
r_struct
id|softirq_action
op_star
id|a
)paren
(brace
r_struct
id|tasklet_struct
op_star
id|list
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|list
op_assign
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|tasklet_struct
op_star
id|t
op_assign
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tasklet_trylock
c_func
(paren
id|t
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|t-&gt;count
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|t
op_member_access_from_pointer
id|func
c_func
(paren
id|t-&gt;data
)paren
suffix:semicolon
id|tasklet_unlock
c_func
(paren
id|t
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|tasklet_unlock
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|t-&gt;next
op_assign
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|TASKLET_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|tasklet_hi_action
r_static
r_void
id|tasklet_hi_action
c_func
(paren
r_struct
id|softirq_action
op_star
id|a
)paren
(brace
r_struct
id|tasklet_struct
op_star
id|list
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|list
op_assign
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|tasklet_struct
op_star
id|t
op_assign
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tasklet_trylock
c_func
(paren
id|t
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|t-&gt;count
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|t
op_member_access_from_pointer
id|func
c_func
(paren
id|t-&gt;data
)paren
suffix:semicolon
id|tasklet_unlock
c_func
(paren
id|t
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|tasklet_unlock
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|t-&gt;next
op_assign
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|this_cpu
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|HI_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|tasklet_init
r_void
id|tasklet_init
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|data
)paren
(brace
id|t-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|t-&gt;state
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|t-&gt;count
comma
l_int|0
)paren
suffix:semicolon
id|t-&gt;func
op_assign
id|func
suffix:semicolon
id|t-&gt;data
op_assign
id|data
suffix:semicolon
)brace
DECL|function|tasklet_kill
r_void
id|tasklet_kill
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Attempt to kill tasklet from interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
(brace
r_do
id|yield
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
suffix:semicolon
)brace
id|tasklet_unlock_wait
c_func
(paren
id|t
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
suffix:semicolon
)brace
multiline_comment|/* Old style BHs */
DECL|variable|bh_base
r_static
r_void
(paren
op_star
id|bh_base
(braket
l_int|32
)braket
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|bh_task_vec
r_struct
id|tasklet_struct
id|bh_task_vec
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* BHs are serialized by spinlock global_bh_lock.&n;&n;   It is still possible to make synchronize_bh() as&n;   spin_unlock_wait(&amp;global_bh_lock). This operation is not used&n;   by kernel now, so that this lock is not made private only&n;   due to wait_on_irq().&n;&n;   It can be removed only after auditing all the BHs.&n; */
DECL|variable|global_bh_lock
id|spinlock_t
id|global_bh_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|bh_action
r_static
r_void
id|bh_action
c_func
(paren
r_int
r_int
id|nr
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
id|spin_trylock
c_func
(paren
op_amp
id|global_bh_lock
)paren
)paren
r_goto
id|resched
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hardirq_trylock
c_func
(paren
id|cpu
)paren
)paren
r_goto
id|resched_unlock
suffix:semicolon
r_if
c_cond
(paren
id|bh_base
(braket
id|nr
)braket
)paren
id|bh_base
(braket
id|nr
)braket
(paren
)paren
suffix:semicolon
id|hardirq_endlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|global_bh_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|resched_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|global_bh_lock
)paren
suffix:semicolon
id|resched
suffix:colon
id|mark_bh
c_func
(paren
id|nr
)paren
suffix:semicolon
)brace
DECL|function|init_bh
r_void
id|init_bh
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|routine
)paren
(paren
r_void
)paren
)paren
(brace
id|bh_base
(braket
id|nr
)braket
op_assign
id|routine
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|remove_bh
r_void
id|remove_bh
c_func
(paren
r_int
id|nr
)paren
(brace
id|tasklet_kill
c_func
(paren
id|bh_task_vec
op_plus
id|nr
)paren
suffix:semicolon
id|bh_base
(braket
id|nr
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|softirq_init
r_void
id|__init
id|softirq_init
c_func
(paren
)paren
(brace
r_int
id|i
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|tasklet_init
c_func
(paren
id|bh_task_vec
op_plus
id|i
comma
id|bh_action
comma
id|i
)paren
suffix:semicolon
id|open_softirq
c_func
(paren
id|TASKLET_SOFTIRQ
comma
id|tasklet_action
comma
l_int|NULL
)paren
suffix:semicolon
id|open_softirq
c_func
(paren
id|HI_SOFTIRQ
comma
id|tasklet_hi_action
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|__run_task_queue
r_void
id|__run_task_queue
c_func
(paren
id|task_queue
op_star
id|list
)paren
(brace
r_struct
id|list_head
id|head
comma
op_star
id|next
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|head
comma
id|list
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|next
op_assign
id|head.next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|head
)paren
(brace
r_void
(paren
op_star
id|f
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_struct
id|tq_struct
op_star
id|p
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
id|p
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|tq_struct
comma
id|list
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
id|f
op_assign
id|p-&gt;routine
suffix:semicolon
id|data
op_assign
id|p-&gt;data
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|p-&gt;sync
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
id|f
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
)brace
DECL|function|ksoftirqd
r_static
r_int
id|ksoftirqd
c_func
(paren
r_void
op_star
id|__bind_cpu
)paren
(brace
r_int
id|cpu
op_assign
(paren
r_int
)paren
(paren
r_int
)paren
id|__bind_cpu
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|set_user_nice
c_func
(paren
id|current
comma
l_int|19
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_IOTHREAD
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/* Migrate to the right CPU */
id|set_cpus_allowed
c_func
(paren
id|current
comma
l_int|1UL
op_lshift
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|cpu
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;ksoftirqd_CPU%d&quot;
comma
id|cpu
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|ksoftirqd_task
c_func
(paren
id|cpu
)paren
op_assign
id|current
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_while
c_loop
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
(brace
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
)brace
DECL|function|spawn_ksoftirqd
r_static
id|__init
r_int
id|spawn_ksoftirqd
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|kernel_thread
c_func
(paren
id|ksoftirqd
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|cpu
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGNAL
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;spawn_ksoftirqd() failed for cpu %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_else
r_while
c_loop
(paren
op_logical_neg
id|ksoftirqd_task
c_func
(paren
id|cpu
)paren
)paren
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|spawn_ksoftirqd
id|__initcall
c_func
(paren
id|spawn_ksoftirqd
)paren
suffix:semicolon
eof
