macro_line|#ifndef _LINUX_KTHREAD_H
DECL|macro|_LINUX_KTHREAD_H
mdefine_line|#define _LINUX_KTHREAD_H
multiline_comment|/* Simple interface for creating and stopping kernel threads without mess. */
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/**&n; * kthread_create: create a kthread.&n; * @threadfn: the function to run until signal_pending(current).&n; * @data: data ptr for @threadfn.&n; * @namefmt: printf-style name for the thread.&n; *&n; * Description: This helper function creates and names a kernel&n; * thread.  The thread will be stopped: use wake_up_process() to start&n; * it.  See also kthread_run(), kthread_create_on_cpu().&n; *&n; * When woken, the thread will run @threadfn() with @data as its&n; * argument. @threadfn can either call do_exit() directly if it is a&n; * standalone thread for which noone will call kthread_stop(), or&n; * return when &squot;kthread_should_stop()&squot; is true (which means&n; * kthread_stop() has been called).  The return value should be zero&n; * or a negative error number: it will be passed to kthread_stop().&n; *&n; * Returns a task_struct or ERR_PTR(-ENOMEM).&n; */
r_struct
id|task_struct
op_star
id|kthread_create
c_func
(paren
r_int
(paren
op_star
id|threadfn
)paren
(paren
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
comma
r_const
r_char
id|namefmt
(braket
)braket
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/**&n; * kthread_run: create and wake a thread.&n; * @threadfn: the function to run until signal_pending(current).&n; * @data: data ptr for @threadfn.&n; * @namefmt: printf-style name for the thread.&n; *&n; * Description: Convenient wrapper for kthread_create() followed by&n; * wake_up_process().  Returns the kthread, or ERR_PTR(-ENOMEM). */
DECL|macro|kthread_run
mdefine_line|#define kthread_run(threadfn, data, namefmt, ...)&t;&t;&t;   &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;struct task_struct *__k&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;= kthread_create(threadfn, data, namefmt, ## __VA_ARGS__); &bslash;&n;&t;if (!IS_ERR(__k))&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;wake_up_process(__k);&t;&t;&t;&t;&t;   &bslash;&n;&t;__k;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;})
multiline_comment|/**&n; * kthread_bind: bind a just-created kthread to a cpu.&n; * @k: thread created by kthread_create().&n; * @cpu: cpu (might not be online, must be possible) for @k to run on.&n; *&n; * Description: This function is equivalent to set_cpus_allowed(),&n; * except that @cpu doesn&squot;t need to be online, and the thread must be&n; * stopped (ie. just returned from kthread_create().&n; */
r_void
id|kthread_bind
c_func
(paren
r_struct
id|task_struct
op_star
id|k
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/**&n; * kthread_stop: stop a thread created by kthread_create().&n; * @k: thread created by kthread_create().&n; *&n; * Sets kthread_should_stop() for @k to return true, wakes it, and&n; * waits for it to exit.  Your threadfn() must not call do_exit()&n; * itself if you use this function!  This can also be called after&n; * kthread_create() instead of calling wake_up_process(): the thread&n; * will exit without calling threadfn().&n; *&n; * Returns the result of threadfn(), or -EINTR if wake_up_process()&n; * was never called. */
r_int
id|kthread_stop
c_func
(paren
r_struct
id|task_struct
op_star
id|k
)paren
suffix:semicolon
multiline_comment|/**&n; * kthread_should_stop: should this kthread return now?&n; *&n; * When someone calls kthread_stop on your kthread, it will be woken&n; * and this will return true.  You should then return, and your return&n; * value will be passed through to kthread_stop().&n; */
r_int
id|kthread_should_stop
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_KTHREAD_H */
eof
