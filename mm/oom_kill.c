multiline_comment|/*&n; *  linux/mm/oom_kill.c&n; * &n; *  Copyright (C)  1998,2000  Rik van Riel&n; *&t;Thanks go out to Claus Fischer for some serious inspiration and&n; *&t;for goading me into coding this file...&n; *&n; *  The routines in this file are used to kill a process when&n; *  we&squot;re seriously out of memory. This gets called from kswapd()&n; *  in linux/mm/vmscan.c when we really run out of memory.&n; *&n; *  Since we won&squot;t call these routines often (on a well-configured&n; *  machine) this file will double as a &squot;coding guide&squot; and a signpost&n; *  for newbie kernel hackers. It features several pointers to major&n; *  kernel subsystems and hints as to where to find out what things do.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
multiline_comment|/* #define DEBUG */
multiline_comment|/**&n; * int_sqrt - oom_kill.c internal function, rough approximation to sqrt&n; * @x: integer of which to calculate the sqrt&n; * &n; * A very rough approximation to the sqrt() function.&n; */
DECL|function|int_sqrt
r_static
r_int
r_int
id|int_sqrt
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|out
op_assign
id|x
suffix:semicolon
r_while
c_loop
(paren
id|x
op_amp
op_complement
(paren
r_int
r_int
)paren
l_int|1
)paren
id|x
op_rshift_assign
l_int|2
comma
id|out
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|x
)paren
id|out
op_sub_assign
id|out
op_rshift
l_int|2
suffix:semicolon
r_return
(paren
id|out
ques
c_cond
id|out
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * oom_badness - calculate a numeric value for how bad this task has been&n; * @p: task struct of which task we should calculate&n; *&n; * The formula used is relatively simple and documented inline in the&n; * function. The main rationale is that we want to select a good task&n; * to kill when we run out of memory.&n; *&n; * Good in this context means that:&n; * 1) we lose the minimum amount of work done&n; * 2) we recover a large amount of memory&n; * 3) we don&squot;t kill anything innocent of eating tons of memory&n; * 4) we want to kill the minimum amount of processes (one)&n; * 5) we try to kill the process the user expects us to kill, this&n; *    algorithm has been meticulously tuned to meet the principle&n; *    of least surprise ... (be careful when you change it)&n; */
DECL|function|badness
r_static
r_int
id|badness
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
id|points
comma
id|cpu_time
comma
id|run_time
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;flags
op_amp
id|PF_MEMDIE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The memory size of the process is the basis for the badness.&n;&t; */
id|points
op_assign
id|p-&gt;mm-&gt;total_vm
suffix:semicolon
multiline_comment|/*&n;&t; * CPU time is in seconds and run time is in minutes. There is no&n;&t; * particular reason for this other than that it turned out to work&n;&t; * very well in practice.&n;&t; */
id|cpu_time
op_assign
(paren
id|p-&gt;utime
op_plus
id|p-&gt;stime
)paren
op_rshift
(paren
id|SHIFT_HZ
op_plus
l_int|3
)paren
suffix:semicolon
id|run_time
op_assign
(paren
id|get_jiffies_64
c_func
(paren
)paren
op_minus
id|p-&gt;start_time
)paren
op_rshift
(paren
id|SHIFT_HZ
op_plus
l_int|10
)paren
suffix:semicolon
id|points
op_div_assign
id|int_sqrt
c_func
(paren
id|cpu_time
)paren
suffix:semicolon
id|points
op_div_assign
id|int_sqrt
c_func
(paren
id|int_sqrt
c_func
(paren
id|run_time
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Niced processes are most likely less important, so double&n;&t; * their badness points.&n;&t; */
r_if
c_cond
(paren
id|task_nice
c_func
(paren
id|p
)paren
OG
l_int|0
)paren
id|points
op_mul_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Superuser processes are usually more important, so we make it&n;&t; * less likely that we kill those.&n;&t; */
r_if
c_cond
(paren
id|cap_t
c_func
(paren
id|p-&gt;cap_effective
)paren
op_amp
id|CAP_TO_MASK
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
id|p-&gt;uid
op_eq
l_int|0
op_logical_or
id|p-&gt;euid
op_eq
l_int|0
)paren
id|points
op_div_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t want to kill a process with direct hardware access.&n;&t; * Not only could that mess up the hardware, but usually users&n;&t; * tend to only have this flag set on applications they think&n;&t; * of as important.&n;&t; */
r_if
c_cond
(paren
id|cap_t
c_func
(paren
id|p-&gt;cap_effective
)paren
op_amp
id|CAP_TO_MASK
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
id|points
op_div_assign
l_int|4
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;OOMkill: task %d (%s) got %d points&bslash;n&quot;
comma
id|p-&gt;pid
comma
id|p-&gt;comm
comma
id|points
)paren
suffix:semicolon
macro_line|#endif
r_return
id|points
suffix:semicolon
)brace
multiline_comment|/*&n; * Simple selection loop. We chose the process with the highest&n; * number of &squot;points&squot;. We expect the caller will lock the tasklist.&n; *&n; * (not docbooked, we don&squot;t want this one cluttering up the manual)&n; */
DECL|function|select_bad_process
r_static
r_struct
id|task_struct
op_star
id|select_bad_process
c_func
(paren
r_void
)paren
(brace
r_int
id|maxpoints
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|g
comma
op_star
id|p
suffix:semicolon
r_struct
id|task_struct
op_star
id|chosen
op_assign
l_int|NULL
suffix:semicolon
id|do_each_thread
c_func
(paren
id|g
comma
id|p
)paren
r_if
c_cond
(paren
id|p-&gt;pid
)paren
(brace
r_int
id|points
op_assign
id|badness
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|points
OG
id|maxpoints
)paren
(brace
id|chosen
op_assign
id|p
suffix:semicolon
id|maxpoints
op_assign
id|points
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;flags
op_amp
id|PF_SWAPOFF
)paren
r_return
id|p
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
r_return
id|chosen
suffix:semicolon
)brace
multiline_comment|/**&n; * We must be careful though to never send SIGKILL a process with&n; * CAP_SYS_RAW_IO set, send SIGTERM instead (but it&squot;s unlikely that&n; * we select a process with CAP_SYS_RAW_IO set).&n; */
DECL|function|__oom_kill_task
r_static
r_void
id|__oom_kill_task
c_func
(paren
id|task_t
op_star
id|p
)paren
(brace
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
op_logical_or
id|p-&gt;mm
op_eq
op_amp
id|init_mm
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tried to kill an mm-less task!&bslash;n&quot;
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Out of Memory: Killed process %d (%s).&bslash;n&quot;
comma
id|p-&gt;pid
comma
id|p-&gt;comm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We give our sacrificial lamb high priority and access to&n;&t; * all the memory it needs. That way it should be able to&n;&t; * exit() and clear out its resources quickly...&n;&t; */
id|p-&gt;time_slice
op_assign
id|HZ
suffix:semicolon
id|p-&gt;flags
op_or_assign
id|PF_MEMALLOC
op_or
id|PF_MEMDIE
suffix:semicolon
multiline_comment|/* This process has hardware access, be more careful. */
r_if
c_cond
(paren
id|cap_t
c_func
(paren
id|p-&gt;cap_effective
)paren
op_amp
id|CAP_TO_MASK
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
(brace
id|force_sig
c_func
(paren
id|SIGTERM
comma
id|p
)paren
suffix:semicolon
)brace
r_else
(brace
id|force_sig
c_func
(paren
id|SIGKILL
comma
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|oom_kill_task
r_static
r_struct
id|mm_struct
op_star
id|oom_kill_task
c_func
(paren
id|task_t
op_star
id|p
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
op_logical_or
id|mm
op_eq
op_amp
id|init_mm
)paren
r_return
l_int|NULL
suffix:semicolon
id|__oom_kill_task
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|mm
suffix:semicolon
)brace
multiline_comment|/**&n; * oom_kill - kill the &quot;best&quot; process when we run out of memory&n; *&n; * If we run out of memory, we have the choice between either&n; * killing a random task (bad), letting the system crash (worse)&n; * OR try to be smart about which process to kill. Note that we&n; * don&squot;t have to be perfect here, we just have to be good.&n; */
DECL|function|oom_kill
r_static
r_void
id|oom_kill
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|task_struct
op_star
id|g
comma
op_star
id|p
comma
op_star
id|q
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|retry
suffix:colon
id|p
op_assign
id|select_bad_process
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Found nothing?!?! Either we hang forever, or we panic. */
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Out of memory and no killable processes...&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|mm
op_assign
id|oom_kill_task
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|retry
suffix:semicolon
multiline_comment|/*&n;&t; * kill all processes that share the -&gt;mm (i.e. all threads),&n;&t; * but are in a different thread group&n;&t; */
id|do_each_thread
c_func
(paren
id|g
comma
id|q
)paren
r_if
c_cond
(paren
id|q-&gt;mm
op_eq
id|mm
op_logical_and
id|q-&gt;tgid
op_ne
id|p-&gt;tgid
)paren
id|__oom_kill_task
c_func
(paren
id|q
)paren
suffix:semicolon
id|while_each_thread
c_func
(paren
id|g
comma
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Fixed up OOM kill of mm-less task&bslash;n&quot;
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make kswapd go out of the way, so &quot;p&quot; has a good chance of&n;&t; * killing itself before someone else gets the chance to ask&n;&t; * for more memory.&n;&t; */
id|yield
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * out_of_memory - is the system out of memory?&n; */
DECL|function|out_of_memory
r_void
id|out_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * oom_lock protects out_of_memory()&squot;s static variables.&n;&t; * It&squot;s a global lock; this is not performance-critical.&n;&t; */
r_static
id|spinlock_t
id|oom_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_int
r_int
id|first
comma
id|last
comma
id|count
comma
id|lastkill
suffix:semicolon
r_int
r_int
id|now
comma
id|since
suffix:semicolon
multiline_comment|/*&n;&t; * Enough swap space left?  Not OOM.&n;&t; */
r_if
c_cond
(paren
id|nr_swap_pages
OG
l_int|0
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oom_lock
)paren
suffix:semicolon
id|now
op_assign
id|jiffies
suffix:semicolon
id|since
op_assign
id|now
op_minus
id|last
suffix:semicolon
id|last
op_assign
id|now
suffix:semicolon
multiline_comment|/*&n;&t; * If it&squot;s been a long time since last failure,&n;&t; * we&squot;re not oom.&n;&t; */
id|last
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
id|since
OG
l_int|5
op_star
id|HZ
)paren
r_goto
id|reset
suffix:semicolon
multiline_comment|/*&n;&t; * If we haven&squot;t tried for at least one second,&n;&t; * we&squot;re not really oom.&n;&t; */
id|since
op_assign
id|now
op_minus
id|first
suffix:semicolon
r_if
c_cond
(paren
id|since
OL
id|HZ
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * If we have gotten only a few failures,&n;&t; * we&squot;re not really oom. &n;&t; */
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|10
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * If we just killed a process, wait a while&n;&t; * to give that task a chance to exit. This&n;&t; * avoids killing multiple processes needlessly.&n;&t; */
id|since
op_assign
id|now
op_minus
id|lastkill
suffix:semicolon
r_if
c_cond
(paren
id|since
OL
id|HZ
op_star
l_int|5
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, really out of memory. Kill something.&n;&t; */
id|lastkill
op_assign
id|now
suffix:semicolon
multiline_comment|/* oom_kill() sleeps */
id|spin_unlock
c_func
(paren
op_amp
id|oom_lock
)paren
suffix:semicolon
id|oom_kill
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oom_lock
)paren
suffix:semicolon
id|reset
suffix:colon
multiline_comment|/*&n;&t; * We dropped the lock above, so check to be sure the variable&n;&t; * first only ever increases to prevent false OOM&squot;s.&n;&t; */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|now
comma
id|first
)paren
)paren
id|first
op_assign
id|now
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|oom_lock
)paren
suffix:semicolon
)brace
eof
