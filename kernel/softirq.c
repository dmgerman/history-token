multiline_comment|/*&n; *&t;linux/kernel/softirq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * Rewritten. Old one was good in 2.2, but in 2.3 it was immoral. --ANK (990903)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/kthread.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n;   - No shared variables, all the data are CPU local.&n;   - If a softirq needs serialization, let it serialize itself&n;     by its own spinlocks.&n;   - Even if softirq is serialized, only local cpu is marked for&n;     execution. Hence, we get something sort of weak cpu binding.&n;     Though it is still not clear, will it result in better locality&n;     or will not.&n;&n;   Examples:&n;   - NET RX softirq. It is multithreaded and does not require&n;     any global serialization.&n;   - NET TX softirq. It kicks software netdevice queues, hence&n;     it is logically serialized per device, but this serialization&n;     is invisible to common code.&n;   - Tasklets: serialized wrt itself.&n; */
macro_line|#ifndef __ARCH_IRQ_STAT
DECL|variable|____cacheline_aligned
id|irq_cpustat_t
id|irq_stat
(braket
id|NR_CPUS
)braket
id|____cacheline_aligned
suffix:semicolon
DECL|variable|irq_stat
id|EXPORT_SYMBOL
c_func
(paren
id|irq_stat
)paren
suffix:semicolon
macro_line|#endif
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
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|ksoftirqd
)paren
suffix:semicolon
multiline_comment|/*&n; * we cannot loop indefinitely here to avoid userspace starvation,&n; * but we also don&squot;t want to introduce a worst case 1/HZ latency&n; * to the pending events, so lets the scheduler to balance&n; * the softirq load for us.&n; */
DECL|function|wakeup_softirqd
r_static
r_inline
r_void
id|wakeup_softirqd
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Interrupts are disabled: no need to stop preemption */
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|__get_cpu_var
c_func
(paren
id|ksoftirqd
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
multiline_comment|/*&n; * We restart softirq processing MAX_SOFTIRQ_RESTART times,&n; * and we fall back to softirqd after that.&n; *&n; * This number has been established via experimentation.&n; * The two things to balance is latency against fairness -&n; * we want to handle softirqs as soon as possible, but they&n; * should not be able to lock up the box.&n; */
DECL|macro|MAX_SOFTIRQ_RESTART
mdefine_line|#define MAX_SOFTIRQ_RESTART 10
DECL|function|__do_softirq
id|asmlinkage
r_void
id|__do_softirq
c_func
(paren
r_void
)paren
(brace
r_struct
id|softirq_action
op_star
id|h
suffix:semicolon
id|__u32
id|pending
suffix:semicolon
r_int
id|max_restart
op_assign
id|MAX_SOFTIRQ_RESTART
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|pending
op_assign
id|local_softirq_pending
c_func
(paren
)paren
suffix:semicolon
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|restart
suffix:colon
multiline_comment|/* Reset the pending bitmask before enabling irqs */
id|local_softirq_pending
c_func
(paren
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
(brace
id|h
op_member_access_from_pointer
id|action
c_func
(paren
id|h
)paren
suffix:semicolon
id|rcu_bh_qsctr_inc
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
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
id|local_softirq_pending
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pending
op_logical_and
op_decrement
id|max_restart
)paren
r_goto
id|restart
suffix:semicolon
r_if
c_cond
(paren
id|pending
)paren
id|wakeup_softirqd
c_func
(paren
)paren
suffix:semicolon
id|__local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef __ARCH_HAS_DO_SOFTIRQ
DECL|function|do_softirq
id|asmlinkage
r_void
id|do_softirq
c_func
(paren
r_void
)paren
(brace
id|__u32
id|pending
suffix:semicolon
r_int
r_int
id|flags
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
id|pending
op_assign
id|local_softirq_pending
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pending
)paren
id|__do_softirq
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|do_softirq
id|EXPORT_SYMBOL
c_func
(paren
id|do_softirq
)paren
suffix:semicolon
macro_line|#endif
DECL|function|local_bh_enable
r_void
id|local_bh_enable
c_func
(paren
r_void
)paren
(brace
id|WARN_ON
c_func
(paren
id|irqs_disabled
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Keep preemption disabled until we are done with&n;&t; * softirq processing:&n; &t; */
id|sub_preempt_count
c_func
(paren
id|SOFTIRQ_OFFSET
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
op_logical_and
id|local_softirq_pending
c_func
(paren
)paren
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
id|dec_preempt_count
c_func
(paren
)paren
suffix:semicolon
id|preempt_check_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|local_bh_enable
id|EXPORT_SYMBOL
c_func
(paren
id|local_bh_enable
)paren
suffix:semicolon
macro_line|#ifdef __ARCH_IRQ_EXIT_IRQS_DISABLED
DECL|macro|invoke_softirq
macro_line|# define invoke_softirq()&t;__do_softirq()
macro_line|#else
DECL|macro|invoke_softirq
macro_line|# define invoke_softirq()&t;do_softirq()
macro_line|#endif
multiline_comment|/*&n; * Exit an interrupt context. Process softirqs if needed and possible:&n; */
DECL|function|irq_exit
r_void
id|irq_exit
c_func
(paren
r_void
)paren
(brace
id|account_system_vtime
c_func
(paren
id|current
)paren
suffix:semicolon
id|sub_preempt_count
c_func
(paren
id|IRQ_EXIT_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
op_logical_and
id|local_softirq_pending
c_func
(paren
)paren
)paren
id|invoke_softirq
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function must run with irqs disabled!&n; */
DECL|function|raise_softirq_irqoff
r_inline
id|fastcall
r_void
id|raise_softirq_irqoff
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
id|__raise_softirq_irqoff
c_func
(paren
id|nr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or softirq, we&squot;re done&n;&t; * (this also catches softirq-disabled code). We will&n;&t; * actually run the softirq once we return from&n;&t; * the irq or softirq.&n;&t; *&n;&t; * Otherwise we wake up ksoftirqd to make sure we&n;&t; * schedule the softirq soon.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
id|wakeup_softirqd
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|raise_softirq_irqoff
id|EXPORT_SYMBOL
c_func
(paren
id|raise_softirq_irqoff
)paren
suffix:semicolon
DECL|function|raise_softirq
r_void
id|fastcall
id|raise_softirq
c_func
(paren
r_int
r_int
id|nr
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
id|raise_softirq_irqoff
c_func
(paren
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
DECL|variable|open_softirq
id|EXPORT_SYMBOL
c_func
(paren
id|open_softirq
)paren
suffix:semicolon
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
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|tasklet_head
comma
id|tasklet_vec
)paren
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|tasklet_head
comma
id|tasklet_hi_vec
)paren
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|function|__tasklet_schedule
r_void
id|fastcall
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
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|raise_softirq_irqoff
c_func
(paren
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
DECL|variable|__tasklet_schedule
id|EXPORT_SYMBOL
c_func
(paren
id|__tasklet_schedule
)paren
suffix:semicolon
DECL|function|__tasklet_hi_schedule
r_void
id|fastcall
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
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|raise_softirq_irqoff
c_func
(paren
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
DECL|variable|__tasklet_hi_schedule
id|EXPORT_SYMBOL
c_func
(paren
id|__tasklet_hi_schedule
)paren
suffix:semicolon
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
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
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
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|__raise_softirq_irqoff
c_func
(paren
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
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
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
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
op_assign
id|t
suffix:semicolon
id|__raise_softirq_irqoff
c_func
(paren
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
DECL|variable|tasklet_init
id|EXPORT_SYMBOL
c_func
(paren
id|tasklet_init
)paren
suffix:semicolon
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
DECL|variable|tasklet_kill
id|EXPORT_SYMBOL
c_func
(paren
id|tasklet_kill
)paren
suffix:semicolon
DECL|function|softirq_init
r_void
id|__init
id|softirq_init
c_func
(paren
r_void
)paren
(brace
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
id|PF_NOFREEZE
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|kthread_should_stop
c_func
(paren
)paren
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_softirq_pending
c_func
(paren
)paren
)paren
(brace
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_while
c_loop
(paren
id|local_softirq_pending
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Preempt disable stops cpu going offline.&n;&t;&t;&t;   If already offline, we&squot;ll be on wrong CPU:&n;&t;&t;&t;   don&squot;t process */
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
(paren
r_int
)paren
id|__bind_cpu
)paren
)paren
r_goto
id|wait_to_die
suffix:semicolon
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|wait_to_die
suffix:colon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Wait for kthread_stop */
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|kthread_should_stop
c_func
(paren
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
multiline_comment|/*&n; * tasklet_kill_immediate is called to remove a tasklet which can already be&n; * scheduled for execution on @cpu.&n; *&n; * Unlike tasklet_kill, this function removes the tasklet&n; * _immediately_, even if the tasklet is in TASKLET_STATE_SCHED state.&n; *&n; * When this function is called, @cpu must be in the CPU_DEAD state.&n; */
DECL|function|tasklet_kill_immediate
r_void
id|tasklet_kill_immediate
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
comma
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|tasklet_struct
op_star
op_star
id|i
suffix:semicolon
id|BUG_ON
c_func
(paren
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|test_bit
c_func
(paren
id|TASKLET_STATE_RUN
comma
op_amp
id|t-&gt;state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* CPU is dead, so no lock needed. */
r_for
c_loop
(paren
id|i
op_assign
op_amp
id|per_cpu
c_func
(paren
id|tasklet_vec
comma
id|cpu
)paren
dot
id|list
suffix:semicolon
op_star
id|i
suffix:semicolon
id|i
op_assign
op_amp
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_star
id|i
op_eq
id|t
)paren
(brace
op_star
id|i
op_assign
id|t-&gt;next
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|takeover_tasklets
r_static
r_void
id|takeover_tasklets
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|tasklet_struct
op_star
op_star
id|i
suffix:semicolon
multiline_comment|/* CPU is dead, so no lock needed. */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Find end, append list for that CPU. */
r_for
c_loop
(paren
id|i
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|tasklet_vec
)paren
dot
id|list
suffix:semicolon
op_star
id|i
suffix:semicolon
id|i
op_assign
op_amp
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|i
op_assign
id|per_cpu
c_func
(paren
id|tasklet_vec
comma
id|cpu
)paren
dot
id|list
suffix:semicolon
id|per_cpu
c_func
(paren
id|tasklet_vec
comma
id|cpu
)paren
dot
id|list
op_assign
l_int|NULL
suffix:semicolon
id|raise_softirq_irqoff
c_func
(paren
id|TASKLET_SOFTIRQ
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|tasklet_hi_vec
)paren
dot
id|list
suffix:semicolon
op_star
id|i
suffix:semicolon
id|i
op_assign
op_amp
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|i
op_assign
id|per_cpu
c_func
(paren
id|tasklet_hi_vec
comma
id|cpu
)paren
dot
id|list
suffix:semicolon
id|per_cpu
c_func
(paren
id|tasklet_hi_vec
comma
id|cpu
)paren
dot
id|list
op_assign
l_int|NULL
suffix:semicolon
id|raise_softirq_irqoff
c_func
(paren
id|HI_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
DECL|function|cpu_callback
r_static
r_int
id|__devinit
id|cpu_callback
c_func
(paren
r_struct
id|notifier_block
op_star
id|nfb
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
id|hotcpu
op_assign
(paren
r_int
r_int
)paren
id|hcpu
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
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
id|BUG_ON
c_func
(paren
id|per_cpu
c_func
(paren
id|tasklet_vec
comma
id|hotcpu
)paren
dot
id|list
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|per_cpu
c_func
(paren
id|tasklet_hi_vec
comma
id|hotcpu
)paren
dot
id|list
)paren
suffix:semicolon
id|p
op_assign
id|kthread_create
c_func
(paren
id|ksoftirqd
comma
id|hcpu
comma
l_string|&quot;ksoftirqd/%d&quot;
comma
id|hotcpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ksoftirqd for %i failed&bslash;n&quot;
comma
id|hotcpu
)paren
suffix:semicolon
r_return
id|NOTIFY_BAD
suffix:semicolon
)brace
id|kthread_bind
c_func
(paren
id|p
comma
id|hotcpu
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|ksoftirqd
comma
id|hotcpu
)paren
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_ONLINE
suffix:colon
id|wake_up_process
c_func
(paren
id|per_cpu
c_func
(paren
id|ksoftirqd
comma
id|hotcpu
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_CPU
r_case
id|CPU_UP_CANCELED
suffix:colon
multiline_comment|/* Unbind so it can run.  Fall thru. */
id|kthread_bind
c_func
(paren
id|per_cpu
c_func
(paren
id|ksoftirqd
comma
id|hotcpu
)paren
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_case
id|CPU_DEAD
suffix:colon
id|p
op_assign
id|per_cpu
c_func
(paren
id|ksoftirqd
comma
id|hotcpu
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|ksoftirqd
comma
id|hotcpu
)paren
op_assign
l_int|NULL
suffix:semicolon
id|kthread_stop
c_func
(paren
id|p
)paren
suffix:semicolon
id|takeover_tasklets
c_func
(paren
id|hotcpu
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
DECL|variable|cpu_nfb
r_static
r_struct
id|notifier_block
id|__devinitdata
id|cpu_nfb
op_assign
(brace
dot
id|notifier_call
op_assign
id|cpu_callback
)brace
suffix:semicolon
DECL|function|spawn_ksoftirqd
id|__init
r_int
id|spawn_ksoftirqd
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|cpu
op_assign
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
suffix:semicolon
id|cpu_callback
c_func
(paren
op_amp
id|cpu_nfb
comma
id|CPU_UP_PREPARE
comma
id|cpu
)paren
suffix:semicolon
id|cpu_callback
c_func
(paren
op_amp
id|cpu_nfb
comma
id|CPU_ONLINE
comma
id|cpu
)paren
suffix:semicolon
id|register_cpu_notifier
c_func
(paren
op_amp
id|cpu_nfb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
