multiline_comment|/*&n; * drivers/power/process.c - Functions for starting/stopping processes on &n; *                           suspend transitions.&n; *&n; * Originally from swsusp.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef DEBUG_SLOW
DECL|macro|MDELAY
mdefine_line|#define MDELAY(a) mdelay(a)
macro_line|#else
DECL|macro|MDELAY
mdefine_line|#define MDELAY(a)
macro_line|#endif
multiline_comment|/* &n; * Timeout for stopping processes&n; */
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;(6 * HZ)
DECL|macro|INTERESTING
mdefine_line|#define INTERESTING(p) &bslash;&n;&t;&t;&t;/* We don&squot;t want to touch kernel_threads..*/ &bslash;&n;&t;&t;&t;if (p-&gt;flags &amp; PF_IOTHREAD) &bslash;&n;&t;&t;&t;&t;continue; &bslash;&n;&t;&t;&t;if (p == current) &bslash;&n;&t;&t;&t;&t;continue; &bslash;&n;&t;&t;&t;if (p-&gt;state == TASK_ZOMBIE) &bslash;&n;&t;&t;&t;&t;continue;
multiline_comment|/* Refrigerator is place where frozen processes are stored :-). */
DECL|function|refrigerator
r_void
id|refrigerator
c_func
(paren
r_int
r_int
id|flag
)paren
(brace
multiline_comment|/* You need correct to work with real-time processes.&n;&t;   OTOH, this way one process may see (via /proc/) some other&n;&t;   process in stopped state (and thereby discovered we were&n;&t;   suspended. We probably do not care. &n;&t; */
r_int
id|save
suffix:semicolon
id|save
op_assign
id|current-&gt;state
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s entered refrigerator&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;=&quot;
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_FREEZE
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* We have signaled a kernel thread, which isn&squot;t normal behaviour&n;&t;&t;&t;&t;&t;   and that may lead to 100%CPU sucking because those threads&n;&t;&t;&t;&t;&t;   just don&squot;t manage signals. */
id|current-&gt;flags
op_or_assign
id|PF_FROZEN
suffix:semicolon
r_while
c_loop
(paren
id|current-&gt;flags
op_amp
id|PF_FROZEN
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s left refrigerator&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|save
suffix:semicolon
)brace
multiline_comment|/* 0 = success, else # of processes that we failed to stop */
DECL|function|freeze_processes
r_int
id|freeze_processes
c_func
(paren
r_void
)paren
(brace
r_int
id|todo
suffix:semicolon
r_int
r_int
id|start_time
suffix:semicolon
r_struct
id|task_struct
op_star
id|g
comma
op_star
id|p
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Stopping tasks: &quot;
)paren
suffix:semicolon
id|start_time
op_assign
id|jiffies
suffix:semicolon
r_do
(brace
id|todo
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|do_each_thread
c_func
(paren
id|g
comma
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|INTERESTING
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;flags
op_amp
id|PF_FROZEN
)paren
r_continue
suffix:semicolon
multiline_comment|/* FIXME: smp problem here: we may not access other process&squot; flags&n;&t;&t;&t;   without locking */
id|p-&gt;flags
op_or_assign
id|PF_FREEZE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|p-&gt;sighand-&gt;siglock
comma
id|flags
)paren
suffix:semicolon
id|signal_wake_up
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|p-&gt;sighand-&gt;siglock
comma
id|flags
)paren
suffix:semicolon
id|todo
op_increment
suffix:semicolon
)brace
id|while_each_thread
c_func
(paren
id|g
comma
id|p
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Yield is okay here */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|start_time
op_plus
id|TIMEOUT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot; stopping tasks failed (%d tasks remaining)&bslash;n&quot;
comma
id|todo
)paren
suffix:semicolon
r_return
id|todo
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|todo
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;|&bslash;n&quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_atomic
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|thaw_processes
r_void
id|thaw_processes
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|g
comma
op_star
id|p
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Restarting tasks...&quot;
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|do_each_thread
c_func
(paren
id|g
comma
id|p
)paren
(brace
id|INTERESTING
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;flags
op_amp
id|PF_FROZEN
)paren
id|p-&gt;flags
op_and_assign
op_complement
id|PF_FROZEN
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; Strange, %s not stopped&bslash;n&quot;
comma
id|p-&gt;comm
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|while_each_thread
c_func
(paren
id|g
comma
id|p
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; done&bslash;n&quot;
)paren
suffix:semicolon
id|MDELAY
c_func
(paren
l_int|500
)paren
suffix:semicolon
)brace
DECL|variable|refrigerator
id|EXPORT_SYMBOL
c_func
(paren
id|refrigerator
)paren
suffix:semicolon
eof
