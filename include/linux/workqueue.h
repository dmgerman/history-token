multiline_comment|/*&n; * workqueue.h --- work queue handling for Linux.&n; */
macro_line|#ifndef _LINUX_WORKQUEUE_H
DECL|macro|_LINUX_WORKQUEUE_H
mdefine_line|#define _LINUX_WORKQUEUE_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
r_struct
id|workqueue_struct
suffix:semicolon
DECL|struct|work_struct
r_struct
id|work_struct
(brace
DECL|member|pending
r_int
r_int
id|pending
suffix:semicolon
DECL|member|entry
r_struct
id|list_head
id|entry
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
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|wq_data
r_void
op_star
id|wq_data
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__WORK_INITIALIZER
mdefine_line|#define __WORK_INITIALIZER(n, f, d) {&t;&t;&t;&t;&bslash;&n;        .entry&t;= { &amp;(n).entry, &amp;(n).entry },&t;&t;&t;&bslash;&n;&t;.func = (f),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.data = (d),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.timer = TIMER_INITIALIZER(NULL, 0, 0),&t;&t;&t;&bslash;&n;&t;}
DECL|macro|DECLARE_WORK
mdefine_line|#define DECLARE_WORK(n, f, d)&t;&t;&t;&t;&t;&bslash;&n;&t;struct work_struct n = __WORK_INITIALIZER(n, f, d)
multiline_comment|/*&n; * initialize a work-struct&squot;s func and data pointers:&n; */
DECL|macro|PREPARE_WORK
mdefine_line|#define PREPARE_WORK(_work, _func, _data)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(_work)-&gt;func = _func;&t;&t;&t;&t;&bslash;&n;&t;&t;(_work)-&gt;data = _data;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * initialize all of a work-struct:&n; */
DECL|macro|INIT_WORK
mdefine_line|#define INIT_WORK(_work, _func, _data)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;INIT_LIST_HEAD(&amp;(_work)-&gt;entry);&t;&t;&bslash;&n;&t;&t;(_work)-&gt;pending = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;PREPARE_WORK((_work), (_func), (_data));&t;&bslash;&n;&t;&t;init_timer(&amp;(_work)-&gt;timer);&t;&t;&t;&bslash;&n;&t;} while (0)
r_extern
r_struct
id|workqueue_struct
op_star
id|__create_workqueue
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|singlethread
)paren
suffix:semicolon
DECL|macro|create_workqueue
mdefine_line|#define create_workqueue(name) __create_workqueue((name), 0)
DECL|macro|create_singlethread_workqueue
mdefine_line|#define create_singlethread_workqueue(name) __create_workqueue((name), 1)
r_extern
r_void
id|destroy_workqueue
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
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
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
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
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|flush_workqueue
c_func
(paren
r_struct
id|workqueue_struct
op_star
id|wq
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|schedule_work
c_func
(paren
r_struct
id|work_struct
op_star
id|work
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
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
)paren
suffix:semicolon
r_extern
r_int
id|schedule_delayed_work_on
c_func
(paren
r_int
id|cpu
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
suffix:semicolon
r_extern
r_void
id|flush_scheduled_work
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|current_is_keventd
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|keventd_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_workqueues
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cancel_rearming_delayed_work
c_func
(paren
r_struct
id|work_struct
op_star
id|work
)paren
suffix:semicolon
multiline_comment|/*&n; * Kill off a pending schedule_delayed_work().  Note that the work callback&n; * function may still be running on return from cancel_delayed_work().  Run&n; * flush_scheduled_work() to wait on it.&n; */
DECL|function|cancel_delayed_work
r_static
r_inline
r_int
id|cancel_delayed_work
c_func
(paren
r_struct
id|work_struct
op_star
id|work
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|del_timer_sync
c_func
(paren
op_amp
id|work-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|work-&gt;pending
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
