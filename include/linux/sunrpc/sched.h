multiline_comment|/*&n; * linux/include/linux/sunrpc/sched.h&n; *&n; * Scheduling primitives for kernel Sun RPC.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_SCHED_H_
DECL|macro|_LINUX_SUNRPC_SCHED_H_
mdefine_line|#define _LINUX_SUNRPC_SCHED_H_
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
multiline_comment|/*&n; * This is the actual RPC procedure call info.&n; */
r_struct
id|rpc_procinfo
suffix:semicolon
DECL|struct|rpc_message
r_struct
id|rpc_message
(brace
DECL|member|rpc_proc
r_struct
id|rpc_procinfo
op_star
id|rpc_proc
suffix:semicolon
multiline_comment|/* Procedure information */
DECL|member|rpc_argp
r_void
op_star
id|rpc_argp
suffix:semicolon
multiline_comment|/* Arguments */
DECL|member|rpc_resp
r_void
op_star
id|rpc_resp
suffix:semicolon
multiline_comment|/* Result */
DECL|member|rpc_cred
r_struct
id|rpc_cred
op_star
id|rpc_cred
suffix:semicolon
multiline_comment|/* Credentials */
)brace
suffix:semicolon
r_struct
id|rpc_wait_queue
suffix:semicolon
DECL|struct|rpc_wait
r_struct
id|rpc_wait
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* wait queue links */
DECL|member|links
r_struct
id|list_head
id|links
suffix:semicolon
multiline_comment|/* Links to related tasks */
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
multiline_comment|/* sync: sleep on this q */
DECL|member|rpc_waitq
r_struct
id|rpc_wait_queue
op_star
id|rpc_waitq
suffix:semicolon
multiline_comment|/* RPC wait queue we&squot;re on */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the RPC task struct&n; */
DECL|struct|rpc_task
r_struct
id|rpc_task
(brace
macro_line|#ifdef RPC_DEBUG
DECL|member|tk_magic
r_int
r_int
id|tk_magic
suffix:semicolon
multiline_comment|/* 0xf00baa */
macro_line|#endif
DECL|member|tk_task
r_struct
id|list_head
id|tk_task
suffix:semicolon
multiline_comment|/* global list of tasks */
DECL|member|tk_client
r_struct
id|rpc_clnt
op_star
id|tk_client
suffix:semicolon
multiline_comment|/* RPC client */
DECL|member|tk_rqstp
r_struct
id|rpc_rqst
op_star
id|tk_rqstp
suffix:semicolon
multiline_comment|/* RPC request */
DECL|member|tk_status
r_int
id|tk_status
suffix:semicolon
multiline_comment|/* result of last operation */
multiline_comment|/*&n;&t; * RPC call state&n;&t; */
DECL|member|tk_msg
r_struct
id|rpc_message
id|tk_msg
suffix:semicolon
multiline_comment|/* RPC call info */
DECL|member|tk_buffer
id|__u32
op_star
id|tk_buffer
suffix:semicolon
multiline_comment|/* XDR buffer */
DECL|member|tk_bufsize
r_int
id|tk_bufsize
suffix:semicolon
DECL|member|tk_garb_retry
id|__u8
id|tk_garb_retry
comma
DECL|member|tk_cred_retry
id|tk_cred_retry
comma
DECL|member|tk_suid_retry
id|tk_suid_retry
suffix:semicolon
DECL|member|tk_cookie
r_int
r_int
id|tk_cookie
suffix:semicolon
multiline_comment|/* Cookie for batching tasks */
multiline_comment|/*&n;&t; * timeout_fn   to be executed by timer bottom half&n;&t; * callback&t;to be executed after waking up&n;&t; * action&t;next procedure for async tasks&n;&t; * exit&t;&t;exit async task and report to caller&n;&t; */
DECL|member|tk_timeout_fn
r_void
(paren
op_star
id|tk_timeout_fn
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_callback
r_void
(paren
op_star
id|tk_callback
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_action
r_void
(paren
op_star
id|tk_action
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_exit
r_void
(paren
op_star
id|tk_exit
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_release
r_void
(paren
op_star
id|tk_release
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_calldata
r_void
op_star
id|tk_calldata
suffix:semicolon
multiline_comment|/*&n;&t; * tk_timer is used for async processing by the RPC scheduling&n;&t; * primitives. You should not access this directly unless&n;&t; * you have a pathological interest in kernel oopses.&n;&t; */
DECL|member|tk_timer
r_struct
id|timer_list
id|tk_timer
suffix:semicolon
multiline_comment|/* kernel timer */
DECL|member|tk_timeout
r_int
r_int
id|tk_timeout
suffix:semicolon
multiline_comment|/* timeout for rpc_sleep() */
DECL|member|tk_flags
r_int
r_int
id|tk_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|tk_active
r_int
r_char
id|tk_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Task has been activated */
DECL|member|tk_priority
r_int
r_char
id|tk_priority
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Task priority */
DECL|member|tk_runstate
r_int
r_int
id|tk_runstate
suffix:semicolon
multiline_comment|/* Task run status */
DECL|member|tk_workqueue
r_struct
id|workqueue_struct
op_star
id|tk_workqueue
suffix:semicolon
multiline_comment|/* Normally rpciod, but could&n;&t;&t;&t;&t;&t;&t; * be any workqueue&n;&t;&t;&t;&t;&t;&t; */
r_union
(brace
DECL|member|tk_work
r_struct
id|work_struct
id|tk_work
suffix:semicolon
multiline_comment|/* Async task work queue */
DECL|member|tk_wait
r_struct
id|rpc_wait
id|tk_wait
suffix:semicolon
multiline_comment|/* RPC wait */
DECL|member|u
)brace
id|u
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
DECL|member|tk_pid
r_int
r_int
id|tk_pid
suffix:semicolon
multiline_comment|/* debugging aid */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|tk_auth
mdefine_line|#define tk_auth&t;&t;&t;tk_client-&gt;cl_auth
DECL|macro|tk_xprt
mdefine_line|#define tk_xprt&t;&t;&t;tk_client-&gt;cl_xprt
multiline_comment|/* support walking a list of tasks on a wait queue */
DECL|macro|task_for_each
mdefine_line|#define&t;task_for_each(task, pos, head) &bslash;&n;&t;list_for_each(pos, head) &bslash;&n;&t;&t;if ((task=list_entry(pos, struct rpc_task, u.tk_wait.list)),1)
DECL|macro|task_for_first
mdefine_line|#define&t;task_for_first(task, head) &bslash;&n;&t;if (!list_empty(head) &amp;&amp;  &bslash;&n;&t;    ((task=list_entry((head)-&gt;next, struct rpc_task, u.tk_wait.list)),1))
multiline_comment|/* .. and walking list of all tasks */
DECL|macro|alltask_for_each
mdefine_line|#define&t;alltask_for_each(task, pos, head) &bslash;&n;&t;list_for_each(pos, head) &bslash;&n;&t;&t;if ((task=list_entry(pos, struct rpc_task, tk_task)),1)
DECL|typedef|rpc_action
r_typedef
r_void
(paren
op_star
id|rpc_action
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * RPC task flags&n; */
DECL|macro|RPC_TASK_ASYNC
mdefine_line|#define RPC_TASK_ASYNC&t;&t;0x0001&t;&t;/* is an async task */
DECL|macro|RPC_TASK_SWAPPER
mdefine_line|#define RPC_TASK_SWAPPER&t;0x0002&t;&t;/* is swapping in/out */
DECL|macro|RPC_TASK_SETUID
mdefine_line|#define RPC_TASK_SETUID&t;&t;0x0004&t;&t;/* is setuid process */
DECL|macro|RPC_TASK_CHILD
mdefine_line|#define RPC_TASK_CHILD&t;&t;0x0008&t;&t;/* is child of other task */
DECL|macro|RPC_CALL_REALUID
mdefine_line|#define RPC_CALL_REALUID&t;0x0010&t;&t;/* try using real uid */
DECL|macro|RPC_CALL_MAJORSEEN
mdefine_line|#define RPC_CALL_MAJORSEEN&t;0x0020&t;&t;/* major timeout seen */
DECL|macro|RPC_TASK_ROOTCREDS
mdefine_line|#define RPC_TASK_ROOTCREDS&t;0x0040&t;&t;/* force root creds */
DECL|macro|RPC_TASK_DYNAMIC
mdefine_line|#define RPC_TASK_DYNAMIC&t;0x0080&t;&t;/* task was kmalloc&squot;ed */
DECL|macro|RPC_TASK_KILLED
mdefine_line|#define RPC_TASK_KILLED&t;&t;0x0100&t;&t;/* task was killed */
DECL|macro|RPC_TASK_SOFT
mdefine_line|#define RPC_TASK_SOFT&t;&t;0x0200&t;&t;/* Use soft timeouts */
DECL|macro|RPC_TASK_NOINTR
mdefine_line|#define RPC_TASK_NOINTR&t;&t;0x0400&t;&t;/* uninterruptible task */
DECL|macro|RPC_IS_ASYNC
mdefine_line|#define RPC_IS_ASYNC(t)&t;&t;((t)-&gt;tk_flags &amp; RPC_TASK_ASYNC)
DECL|macro|RPC_IS_SETUID
mdefine_line|#define RPC_IS_SETUID(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_SETUID)
DECL|macro|RPC_IS_CHILD
mdefine_line|#define RPC_IS_CHILD(t)&t;&t;((t)-&gt;tk_flags &amp; RPC_TASK_CHILD)
DECL|macro|RPC_IS_SWAPPER
mdefine_line|#define RPC_IS_SWAPPER(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_SWAPPER)
DECL|macro|RPC_DO_ROOTOVERRIDE
mdefine_line|#define RPC_DO_ROOTOVERRIDE(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_ROOTCREDS)
DECL|macro|RPC_ASSASSINATED
mdefine_line|#define RPC_ASSASSINATED(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_KILLED)
DECL|macro|RPC_IS_ACTIVATED
mdefine_line|#define RPC_IS_ACTIVATED(t)&t;((t)-&gt;tk_active)
DECL|macro|RPC_DO_CALLBACK
mdefine_line|#define RPC_DO_CALLBACK(t)&t;((t)-&gt;tk_callback != NULL)
DECL|macro|RPC_IS_SOFT
mdefine_line|#define RPC_IS_SOFT(t)&t;&t;((t)-&gt;tk_flags &amp; RPC_TASK_SOFT)
DECL|macro|RPC_TASK_UNINTERRUPTIBLE
mdefine_line|#define RPC_TASK_UNINTERRUPTIBLE(t) ((t)-&gt;tk_flags &amp; RPC_TASK_NOINTR)
DECL|macro|RPC_TASK_RUNNING
mdefine_line|#define RPC_TASK_RUNNING&t;0
DECL|macro|RPC_TASK_QUEUED
mdefine_line|#define RPC_TASK_QUEUED&t;&t;1
DECL|macro|RPC_TASK_WAKEUP
mdefine_line|#define RPC_TASK_WAKEUP&t;&t;2
DECL|macro|RPC_IS_RUNNING
mdefine_line|#define RPC_IS_RUNNING(t)&t;(test_bit(RPC_TASK_RUNNING, &amp;(t)-&gt;tk_runstate))
DECL|macro|rpc_set_running
mdefine_line|#define rpc_set_running(t)&t;(set_bit(RPC_TASK_RUNNING, &amp;(t)-&gt;tk_runstate))
DECL|macro|rpc_test_and_set_running
mdefine_line|#define rpc_test_and_set_running(t) &bslash;&n;&t;&t;&t;&t;(test_and_set_bit(RPC_TASK_RUNNING, &amp;(t)-&gt;tk_runstate))
DECL|macro|rpc_clear_running
mdefine_line|#define rpc_clear_running(t)&t;&bslash;&n;&t;do { &bslash;&n;&t;&t;smp_mb__before_clear_bit(); &bslash;&n;&t;&t;clear_bit(RPC_TASK_RUNNING, &amp;(t)-&gt;tk_runstate); &bslash;&n;&t;&t;smp_mb__after_clear_bit(); &bslash;&n;&t;} while (0)
DECL|macro|RPC_IS_QUEUED
mdefine_line|#define RPC_IS_QUEUED(t)&t;(test_bit(RPC_TASK_QUEUED, &amp;(t)-&gt;tk_runstate))
DECL|macro|rpc_set_queued
mdefine_line|#define rpc_set_queued(t)&t;(set_bit(RPC_TASK_QUEUED, &amp;(t)-&gt;tk_runstate))
DECL|macro|rpc_clear_queued
mdefine_line|#define rpc_clear_queued(t)&t;&bslash;&n;&t;do { &bslash;&n;&t;&t;smp_mb__before_clear_bit(); &bslash;&n;&t;&t;clear_bit(RPC_TASK_QUEUED, &amp;(t)-&gt;tk_runstate); &bslash;&n;&t;&t;smp_mb__after_clear_bit(); &bslash;&n;&t;} while (0)
DECL|macro|rpc_start_wakeup
mdefine_line|#define rpc_start_wakeup(t) &bslash;&n;&t;(test_and_set_bit(RPC_TASK_WAKEUP, &amp;(t)-&gt;tk_runstate) == 0)
DECL|macro|rpc_finish_wakeup
mdefine_line|#define rpc_finish_wakeup(t) &bslash;&n;&t;do { &bslash;&n;&t;&t;smp_mb__before_clear_bit(); &bslash;&n;&t;&t;clear_bit(RPC_TASK_WAKEUP, &amp;(t)-&gt;tk_runstate); &bslash;&n;&t;&t;smp_mb__after_clear_bit(); &bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Task priorities.&n; * Note: if you change these, you must also change&n; * the task initialization definitions below.&n; */
DECL|macro|RPC_PRIORITY_LOW
mdefine_line|#define RPC_PRIORITY_LOW&t;0
DECL|macro|RPC_PRIORITY_NORMAL
mdefine_line|#define RPC_PRIORITY_NORMAL&t;1
DECL|macro|RPC_PRIORITY_HIGH
mdefine_line|#define RPC_PRIORITY_HIGH&t;2
DECL|macro|RPC_NR_PRIORITY
mdefine_line|#define RPC_NR_PRIORITY&t;&t;(RPC_PRIORITY_HIGH+1)
multiline_comment|/*&n; * RPC synchronization objects&n; */
DECL|struct|rpc_wait_queue
r_struct
id|rpc_wait_queue
(brace
DECL|member|tasks
r_struct
id|list_head
id|tasks
(braket
id|RPC_NR_PRIORITY
)braket
suffix:semicolon
multiline_comment|/* task queue for each priority level */
DECL|member|cookie
r_int
r_int
id|cookie
suffix:semicolon
multiline_comment|/* cookie of last task serviced */
DECL|member|maxpriority
r_int
r_char
id|maxpriority
suffix:semicolon
multiline_comment|/* maximum priority (0 if queue is not a priority queue) */
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
multiline_comment|/* current priority */
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
multiline_comment|/* # task groups remaining serviced so far */
DECL|member|nr
r_int
r_char
id|nr
suffix:semicolon
multiline_comment|/* # tasks remaining for cookie */
macro_line|#ifdef RPC_DEBUG
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the # requests to send consecutively&n; * from a single cookie.  The aim is to improve&n; * performance of NFS operations such as read/write.&n; */
DECL|macro|RPC_BATCH_COUNT
mdefine_line|#define RPC_BATCH_COUNT&t;&t;&t;16
macro_line|#ifndef RPC_DEBUG
DECL|macro|RPC_WAITQ_INIT
macro_line|# define RPC_WAITQ_INIT(var,qname) { &bslash;&n;&t;&t;.tasks = { &bslash;&n;&t;&t;&t;[0] = LIST_HEAD_INIT(var.tasks[0]), &bslash;&n;&t;&t;&t;[1] = LIST_HEAD_INIT(var.tasks[1]), &bslash;&n;&t;&t;&t;[2] = LIST_HEAD_INIT(var.tasks[2]), &bslash;&n;&t;&t;}, &bslash;&n;&t;}
macro_line|#else
DECL|macro|RPC_WAITQ_INIT
macro_line|# define RPC_WAITQ_INIT(var,qname) { &bslash;&n;&t;&t;.tasks = { &bslash;&n;&t;&t;&t;[0] = LIST_HEAD_INIT(var.tasks[0]), &bslash;&n;&t;&t;&t;[1] = LIST_HEAD_INIT(var.tasks[1]), &bslash;&n;&t;&t;&t;[2] = LIST_HEAD_INIT(var.tasks[2]), &bslash;&n;&t;&t;}, &bslash;&n;&t;&t;.name = qname, &bslash;&n;&t;}
macro_line|#endif
DECL|macro|RPC_WAITQ
macro_line|# define RPC_WAITQ(var,qname)      struct rpc_wait_queue var = RPC_WAITQ_INIT(var,qname)
DECL|macro|RPC_IS_PRIORITY
mdefine_line|#define RPC_IS_PRIORITY(q)&t;&t;((q)-&gt;maxpriority &gt; 0)
multiline_comment|/*&n; * Function prototypes&n; */
r_struct
id|rpc_task
op_star
id|rpc_new_task
c_func
(paren
r_struct
id|rpc_clnt
op_star
comma
id|rpc_action
comma
r_int
id|flags
)paren
suffix:semicolon
r_struct
id|rpc_task
op_star
id|rpc_new_child
c_func
(paren
r_struct
id|rpc_clnt
op_star
comma
r_struct
id|rpc_task
op_star
id|parent
)paren
suffix:semicolon
r_void
id|rpc_init_task
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_struct
id|rpc_clnt
op_star
comma
id|rpc_action
id|exitfunc
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|rpc_release_task
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_killall_tasks
c_func
(paren
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_int
id|rpc_execute
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_run_child
c_func
(paren
r_struct
id|rpc_task
op_star
id|parent
comma
r_struct
id|rpc_task
op_star
id|child
comma
id|rpc_action
id|action
)paren
suffix:semicolon
r_void
id|rpc_init_priority_wait_queue
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_void
id|rpc_init_wait_queue
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_void
id|rpc_sleep_on
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_struct
id|rpc_task
op_star
comma
id|rpc_action
id|action
comma
id|rpc_action
id|timer
)paren
suffix:semicolon
r_void
id|rpc_wake_up_task
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_wake_up
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
)paren
suffix:semicolon
r_struct
id|rpc_task
op_star
id|rpc_wake_up_next
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
)paren
suffix:semicolon
r_void
id|rpc_wake_up_status
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|rpc_delay
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
op_star
id|rpc_malloc
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|rpciod_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpciod_down
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpciod_wake_up
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
r_void
id|rpc_show_tasks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_int
id|rpc_init_mempool
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpc_destroy_mempool
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|rpc_exit
r_static
r_inline
r_void
id|rpc_exit
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
r_int
id|status
)paren
(brace
id|task-&gt;tk_status
op_assign
id|status
suffix:semicolon
id|task-&gt;tk_action
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef RPC_DEBUG
DECL|function|rpc_qname
r_static
r_inline
r_const
r_char
op_star
id|rpc_qname
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
id|q
)paren
(brace
r_return
(paren
(paren
id|q
op_logical_and
id|q-&gt;name
)paren
ques
c_cond
id|q-&gt;name
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_SUNRPC_SCHED_H_ */
eof
