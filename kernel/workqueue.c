multiline_comment|/*&n; * linux/kernel/workqueue.c&n; *&n; * Generic mechanism for defining kernel helper threads for running&n; * arbitrary tasks in process context.&n; *&n; * Started by Ingo Molnar, Copyright (C) 2002&n; *&n; * Derived from the taskqueue/keventd code by:&n; *&n; *   David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *   Andrew Morton &lt;andrewm@uow.edu.au&gt;&n; *   Kai Petzke &lt;wpp@marie.physik.tu-berlin.de&gt;&n; *   Theodore Ts&squot;o &lt;tytso@mit.edu&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kthread.h&gt;
multiline_comment|/*&n; * The per-CPU workqueue.&n; *&n; * The sequence counters are for flush_scheduled_work().  It wants to wait&n; * until until all currently-scheduled works are completed, but it doesn&squot;t&n; * want to be livelocked by new, incoming ones.  So it waits until&n; * remove_sequence is &gt;= the insert_sequence which pertained when&n; * flush_scheduled_work() was called.&n; */
DECL|struct|cpu_workqueue_struct
r_struct
id|cpu_workqueue_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|remove_sequence
r_int
id|remove_sequence
suffix:semicolon
multiline_comment|/* Least-recently added (next to run) */
DECL|member|insert_sequence
r_int
id|insert_sequence
suffix:semicolon
multiline_comment|/* Next to add */
DECL|member|worklist
r_struct
id|list_head
id|worklist
suffix:semicolon
DECL|member|more_work
id|wait_queue_head_t
id|more_work
suffix:semicolon
DECL|member|work_done
id|wait_queue_head_t
id|work_done
suffix:semicolon
DECL|member|wq
r_struct
id|workqueue_struct
op_star
id|wq
suffix:semicolon
DECL|member|thread
id|task_t
op_star
id|thread
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
multiline_comment|/*&n; * The externally visible workqueue abstraction is an array of&n; * per-CPU workqueues:&n; */
DECL|struct|workqueue_struct
r_struct
id|workqueue_struct
(brace
DECL|member|cpu_wq
r_struct
id|cpu_workqueue_struct
id|cpu_wq
(braket
id|NR_CPUS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Preempt must be disabled. */
DECL|function|__queue_work
r_static
r_void
id|__queue_work
c_func
(paren
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
comma
r_struct
id|work_struct
op_star
id|work
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
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|work-&gt;wq_data
op_assign
id|cwq
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|work-&gt;entry
comma
op_amp
id|cwq-&gt;worklist
)paren
suffix:semicolon
id|cwq-&gt;insert_sequence
op_increment
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|cwq-&gt;more_work
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Queue work on a workqueue. Return non-zero if it was successfully&n; * added.&n; *&n; * We queue the work to the CPU it was submitted, but there is no&n; * guarantee that it will be processed by that CPU.&n; */
DECL|function|queue_work
r_int
id|queue_work
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
comma
r_struct
id|work_struct
op_star
id|work
)paren
(brace
r_int
id|ret
op_assign
l_int|0
comma
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|work-&gt;pending
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|work-&gt;entry
)paren
)paren
suffix:semicolon
id|__queue_work
c_func
(paren
id|wq-&gt;cpu_wq
op_plus
id|cpu
comma
id|work
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|delayed_work_timer_fn
r_static
r_void
id|delayed_work_timer_fn
c_func
(paren
r_int
r_int
id|__data
)paren
(brace
r_struct
id|work_struct
op_star
id|work
op_assign
(paren
r_struct
id|work_struct
op_star
)paren
id|__data
suffix:semicolon
r_struct
id|workqueue_struct
op_star
id|wq
op_assign
id|work-&gt;wq_data
suffix:semicolon
id|__queue_work
c_func
(paren
id|wq-&gt;cpu_wq
op_plus
id|smp_processor_id
c_func
(paren
)paren
comma
id|work
)paren
suffix:semicolon
)brace
DECL|function|queue_delayed_work
r_int
id|queue_delayed_work
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
comma
r_struct
id|work_struct
op_star
id|work
comma
r_int
r_int
id|delay
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|timer_list
op_star
id|timer
op_assign
op_amp
id|work-&gt;timer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|work-&gt;pending
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
id|timer_pending
c_func
(paren
id|timer
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|work-&gt;entry
)paren
)paren
suffix:semicolon
multiline_comment|/* This stores wq for the moment, for the timer_fn */
id|work-&gt;wq_data
op_assign
id|wq
suffix:semicolon
id|timer-&gt;expires
op_assign
id|jiffies
op_plus
id|delay
suffix:semicolon
id|timer-&gt;data
op_assign
(paren
r_int
r_int
)paren
id|work
suffix:semicolon
id|timer-&gt;function
op_assign
id|delayed_work_timer_fn
suffix:semicolon
id|add_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|run_workqueue
r_static
r_inline
r_void
id|run_workqueue
c_func
(paren
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Keep taking off work from the queue until&n;&t; * done.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cwq-&gt;worklist
)paren
)paren
(brace
r_struct
id|work_struct
op_star
id|work
op_assign
id|list_entry
c_func
(paren
id|cwq-&gt;worklist.next
comma
r_struct
id|work_struct
comma
id|entry
)paren
suffix:semicolon
r_void
(paren
op_star
id|f
)paren
(paren
r_void
op_star
)paren
op_assign
id|work-&gt;func
suffix:semicolon
r_void
op_star
id|data
op_assign
id|work-&gt;data
suffix:semicolon
id|list_del_init
c_func
(paren
id|cwq-&gt;worklist.next
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|work-&gt;wq_data
op_ne
id|cwq
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|work-&gt;pending
)paren
suffix:semicolon
id|f
c_func
(paren
id|data
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|cwq-&gt;remove_sequence
op_increment
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|cwq-&gt;work_done
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cwq-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|worker_thread
r_static
r_int
id|worker_thread
c_func
(paren
r_void
op_star
id|__cwq
)paren
(brace
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
op_assign
id|__cwq
suffix:semicolon
r_int
id|cpu
op_assign
id|cwq
op_minus
id|cwq-&gt;wq-&gt;cpu_wq
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|k_sigaction
id|sa
suffix:semicolon
id|sigset_t
id|blocked
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_IOTHREAD
suffix:semicolon
id|set_user_nice
c_func
(paren
id|current
comma
op_minus
l_int|10
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Block and flush all signals */
id|sigfillset
c_func
(paren
op_amp
id|blocked
)paren
suffix:semicolon
id|sigprocmask
c_func
(paren
id|SIG_BLOCK
comma
op_amp
id|blocked
comma
l_int|NULL
)paren
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* SIG_IGN makes children autoreap: see do_notify_parent(). */
id|sa.sa.sa_handler
op_assign
id|SIG_IGN
suffix:semicolon
id|sa.sa.sa_flags
op_assign
l_int|0
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|sa.sa.sa_mask
comma
id|sigmask
c_func
(paren
id|SIGCHLD
)paren
)paren
suffix:semicolon
id|do_sigaction
c_func
(paren
id|SIGCHLD
comma
op_amp
id|sa
comma
(paren
r_struct
id|k_sigaction
op_star
)paren
l_int|0
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
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|cwq-&gt;more_work
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|cwq-&gt;worklist
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_else
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|cwq-&gt;more_work
comma
op_amp
id|wait
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
id|cwq-&gt;worklist
)paren
)paren
id|run_workqueue
c_func
(paren
id|cwq
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * flush_workqueue - ensure that any scheduled work has run to completion.&n; *&n; * Forces execution of the workqueue and blocks until its completion.&n; * This is typically used in driver shutdown handlers.&n; *&n; * This function will sample each workqueue&squot;s current insert_sequence number and&n; * will sleep until the head sequence is greater than or equal to that.  This&n; * means that we sleep until all works which were queued on entry have been&n; * handled, but we are not livelocked by new incoming ones.&n; *&n; * This function used to run the workqueues itself.  Now we just wait for the&n; * helper threads to do it.&n; */
DECL|function|flush_workqueue
r_void
id|flush_workqueue
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
)paren
(brace
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
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
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_int
id|sequence_needed
suffix:semicolon
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
id|cwq
op_assign
id|wq-&gt;cpu_wq
op_plus
id|cpu
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|cwq-&gt;lock
)paren
suffix:semicolon
id|sequence_needed
op_assign
id|cwq-&gt;insert_sequence
suffix:semicolon
r_while
c_loop
(paren
id|sequence_needed
op_minus
id|cwq-&gt;remove_sequence
OG
l_int|0
)paren
(brace
id|prepare_to_wait
c_func
(paren
op_amp
id|cwq-&gt;work_done
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cwq-&gt;lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|cwq-&gt;lock
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
op_amp
id|cwq-&gt;work_done
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cwq-&gt;lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|create_workqueue_thread
r_static
r_int
id|create_workqueue_thread
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
comma
r_const
r_char
op_star
id|name
comma
r_int
id|cpu
)paren
(brace
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
op_assign
id|wq-&gt;cpu_wq
op_plus
id|cpu
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|cwq-&gt;lock
)paren
suffix:semicolon
id|cwq-&gt;wq
op_assign
id|wq
suffix:semicolon
id|cwq-&gt;thread
op_assign
l_int|NULL
suffix:semicolon
id|cwq-&gt;insert_sequence
op_assign
l_int|0
suffix:semicolon
id|cwq-&gt;remove_sequence
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cwq-&gt;worklist
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|cwq-&gt;more_work
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|cwq-&gt;work_done
)paren
suffix:semicolon
id|p
op_assign
id|kthread_create
c_func
(paren
id|worker_thread
comma
id|cwq
comma
l_string|&quot;%s/%d&quot;
comma
id|name
comma
id|cpu
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
r_return
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
id|cwq-&gt;thread
op_assign
id|p
suffix:semicolon
id|kthread_bind
c_func
(paren
id|p
comma
id|cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_workqueue
r_struct
id|workqueue_struct
op_star
id|create_workqueue
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|cpu
comma
id|destroy
op_assign
l_int|0
suffix:semicolon
r_struct
id|workqueue_struct
op_star
id|wq
suffix:semicolon
id|BUG_ON
c_func
(paren
id|strlen
c_func
(paren
id|name
)paren
OG
l_int|10
)paren
suffix:semicolon
id|wq
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|wq
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
r_return
l_int|NULL
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
id|create_workqueue_thread
c_func
(paren
id|wq
comma
id|name
comma
id|cpu
)paren
OL
l_int|0
)paren
id|destroy
op_assign
l_int|1
suffix:semicolon
r_else
id|wake_up_process
c_func
(paren
id|wq-&gt;cpu_wq
(braket
id|cpu
)braket
dot
id|thread
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Was there any error during startup? If yes then clean up:&n;&t; */
r_if
c_cond
(paren
id|destroy
)paren
(brace
id|destroy_workqueue
c_func
(paren
id|wq
)paren
suffix:semicolon
id|wq
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|wq
suffix:semicolon
)brace
DECL|function|cleanup_workqueue_thread
r_static
r_void
id|cleanup_workqueue_thread
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
comma
r_int
id|cpu
)paren
(brace
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
suffix:semicolon
id|cwq
op_assign
id|wq-&gt;cpu_wq
op_plus
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|cwq-&gt;thread
)paren
id|kthread_stop
c_func
(paren
id|cwq-&gt;thread
)paren
suffix:semicolon
)brace
DECL|function|destroy_workqueue
r_void
id|destroy_workqueue
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
)paren
(brace
r_int
id|cpu
suffix:semicolon
id|flush_workqueue
c_func
(paren
id|wq
)paren
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
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
id|cleanup_workqueue_thread
c_func
(paren
id|wq
comma
id|cpu
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
)brace
DECL|variable|keventd_wq
r_static
r_struct
id|workqueue_struct
op_star
id|keventd_wq
suffix:semicolon
DECL|function|schedule_work
r_int
id|schedule_work
c_func
(paren
r_struct
id|work_struct
op_star
id|work
)paren
(brace
r_return
id|queue_work
c_func
(paren
id|keventd_wq
comma
id|work
)paren
suffix:semicolon
)brace
DECL|function|schedule_delayed_work
r_int
id|schedule_delayed_work
c_func
(paren
r_struct
id|work_struct
op_star
id|work
comma
r_int
r_int
id|delay
)paren
(brace
r_return
id|queue_delayed_work
c_func
(paren
id|keventd_wq
comma
id|work
comma
id|delay
)paren
suffix:semicolon
)brace
DECL|function|flush_scheduled_work
r_void
id|flush_scheduled_work
c_func
(paren
r_void
)paren
(brace
id|flush_workqueue
c_func
(paren
id|keventd_wq
)paren
suffix:semicolon
)brace
DECL|function|keventd_up
r_int
id|keventd_up
c_func
(paren
r_void
)paren
(brace
r_return
id|keventd_wq
op_ne
l_int|NULL
suffix:semicolon
)brace
DECL|function|current_is_keventd
r_int
id|current_is_keventd
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpu_workqueue_struct
op_star
id|cwq
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|keventd_wq
)paren
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
id|cwq
op_assign
id|keventd_wq-&gt;cpu_wq
op_plus
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|current
op_eq
id|cwq-&gt;thread
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_workqueues
r_void
id|init_workqueues
c_func
(paren
r_void
)paren
(brace
id|keventd_wq
op_assign
id|create_workqueue
c_func
(paren
l_string|&quot;events&quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|keventd_wq
)paren
suffix:semicolon
)brace
DECL|variable|create_workqueue
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|create_workqueue
)paren
suffix:semicolon
DECL|variable|queue_work
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|queue_work
)paren
suffix:semicolon
DECL|variable|queue_delayed_work
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|queue_delayed_work
)paren
suffix:semicolon
DECL|variable|flush_workqueue
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|flush_workqueue
)paren
suffix:semicolon
DECL|variable|destroy_workqueue
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|destroy_workqueue
)paren
suffix:semicolon
DECL|variable|schedule_work
id|EXPORT_SYMBOL
c_func
(paren
id|schedule_work
)paren
suffix:semicolon
DECL|variable|schedule_delayed_work
id|EXPORT_SYMBOL
c_func
(paren
id|schedule_delayed_work
)paren
suffix:semicolon
DECL|variable|flush_scheduled_work
id|EXPORT_SYMBOL
c_func
(paren
id|flush_scheduled_work
)paren
suffix:semicolon
eof
