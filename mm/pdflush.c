multiline_comment|/*&n; * mm/pdflush.c - worker threads for writing back filesystem data&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * 09Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
multiline_comment|/*&n; * Minimum and maximum number of pdflush instances&n; */
DECL|macro|MIN_PDFLUSH_THREADS
mdefine_line|#define MIN_PDFLUSH_THREADS&t;2
DECL|macro|MAX_PDFLUSH_THREADS
mdefine_line|#define MAX_PDFLUSH_THREADS&t;8
r_static
r_void
id|start_one_pdflush_thread
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The pdflush threads are worker threads for writing back dirty data.&n; * Ideally, we&squot;d like one thread per active disk spindle.  But the disk&n; * topology is very hard to divine at this level.   Instead, we take&n; * care in various places to prevent more than one pdflush thread from&n; * performing writeback against a single filesystem.  pdflush threads&n; * have the PF_FLUSHER flag set in current-&gt;flags to aid in this.&n; */
multiline_comment|/*&n; * All the pdflush threads.  Protected by pdflush_lock&n; */
r_static
id|LIST_HEAD
c_func
(paren
id|pdflush_list
)paren
suffix:semicolon
DECL|variable|pdflush_lock
r_static
id|spinlock_t
id|pdflush_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * The count of currently-running pdflush threads.  Protected&n; * by pdflush_lock.&n; */
DECL|variable|nr_pdflush_threads
r_static
r_int
id|nr_pdflush_threads
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * The time at which the pdflush thread pool last went empty&n; */
DECL|variable|last_empty_jifs
r_static
r_int
r_int
id|last_empty_jifs
suffix:semicolon
multiline_comment|/*&n; * The pdflush thread.&n; *&n; * Thread pool management algorithm:&n; * &n; * - The minimum and maximum number of pdflush instances are bound&n; *   by MIN_PDFLUSH_THREADS and MAX_PDFLUSH_THREADS.&n; * &n; * - If there have been no idle pdflush instances for 1 second, create&n; *   a new one.&n; * &n; * - If the least-recently-went-to-sleep pdflush thread has been asleep&n; *   for more than one second, terminate a thread.&n; */
multiline_comment|/*&n; * A structure for passing work to a pdflush thread.  Also for passing&n; * state information between pdflush threads.  Protected by pdflush_lock.&n; */
DECL|struct|pdflush_work
r_struct
id|pdflush_work
(brace
DECL|member|who
r_struct
id|task_struct
op_star
id|who
suffix:semicolon
multiline_comment|/* The thread */
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* A callback function for pdflush to work on */
DECL|member|arg0
r_int
r_int
id|arg0
suffix:semicolon
multiline_comment|/* An argument to the callback function */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* On pdflush_list, when the thread is idle */
DECL|member|when_i_went_to_sleep
r_int
r_int
id|when_i_went_to_sleep
suffix:semicolon
)brace
suffix:semicolon
DECL|function|__pdflush
r_static
r_int
id|__pdflush
c_func
(paren
r_struct
id|pdflush_work
op_star
id|my_work
)paren
(brace
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|reparent_to_init
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;pdflush&quot;
)paren
suffix:semicolon
multiline_comment|/* interruptible sleep, so block all signals */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
l_int|0
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_FLUSHER
suffix:semicolon
id|my_work-&gt;fn
op_assign
l_int|NULL
suffix:semicolon
id|my_work-&gt;who
op_assign
id|current
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|pdflush_lock
)paren
suffix:semicolon
id|nr_pdflush_threads
op_increment
suffix:semicolon
singleline_comment|//&t;printk(&quot;pdflush %d [%d] starts&bslash;n&quot;, nr_pdflush_threads, current-&gt;pid);
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|pdflush_work
op_star
id|pdf
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|my_work-&gt;list
comma
op_amp
id|pdflush_list
)paren
suffix:semicolon
id|my_work-&gt;when_i_went_to_sleep
op_assign
id|jiffies
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|pdflush_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
id|refrigerator
c_func
(paren
id|PF_IOTHREAD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|my_work-&gt;fn
)paren
(paren
op_star
id|my_work-&gt;fn
)paren
(paren
id|my_work-&gt;arg0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Thread creation: For how long have there been zero&n;&t;&t; * available threads?&n;&t;&t; */
r_if
c_cond
(paren
id|jiffies
op_minus
id|last_empty_jifs
OG
l_int|1
op_star
id|HZ
)paren
(brace
multiline_comment|/* unlocked list_empty() test is OK here */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|pdflush_list
)paren
)paren
(brace
multiline_comment|/* unlocked test is OK here */
r_if
c_cond
(paren
id|nr_pdflush_threads
OL
id|MAX_PDFLUSH_THREADS
)paren
id|start_one_pdflush_thread
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|pdflush_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Thread destruction: For how long has the sleepiest&n;&t;&t; * thread slept?&n;&t;&t; */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|pdflush_list
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|nr_pdflush_threads
op_le
id|MIN_PDFLUSH_THREADS
)paren
r_continue
suffix:semicolon
id|pdf
op_assign
id|list_entry
c_func
(paren
id|pdflush_list.prev
comma
r_struct
id|pdflush_work
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_minus
id|pdf-&gt;when_i_went_to_sleep
OG
l_int|1
op_star
id|HZ
)paren
(brace
id|pdf-&gt;when_i_went_to_sleep
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* Limit exit rate */
r_break
suffix:semicolon
multiline_comment|/* exeunt */
)brace
id|my_work-&gt;fn
op_assign
l_int|NULL
suffix:semicolon
)brace
id|nr_pdflush_threads
op_decrement
suffix:semicolon
singleline_comment|//&t;printk(&quot;pdflush %d [%d] ends&bslash;n&quot;, nr_pdflush_threads, current-&gt;pid);
id|spin_unlock_irq
c_func
(paren
op_amp
id|pdflush_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Of course, my_work wants to be just a local in __pdflush().  It is&n; * separated out in this manner to hopefully prevent the compiler from&n; * performing unfortunate optimisations against the auto variables.  Because&n; * these are visible to other tasks and CPUs.  (No problem has actually&n; * been observed.  This is just paranoia).&n; */
DECL|function|pdflush
r_static
r_int
id|pdflush
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_struct
id|pdflush_work
id|my_work
suffix:semicolon
r_return
id|__pdflush
c_func
(paren
op_amp
id|my_work
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to wake up a pdflush thread, and get it to do some work for you.&n; * Returns zero if it indeed managed to find a worker thread, and passed your&n; * payload to it.&n; */
DECL|function|pdflush_operation
r_int
id|pdflush_operation
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|arg0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fn
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Hard to diagnose if it&squot;s deferred */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pdflush_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|pdflush_list
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pdflush_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_struct
id|pdflush_work
op_star
id|pdf
suffix:semicolon
id|pdf
op_assign
id|list_entry
c_func
(paren
id|pdflush_list.next
comma
r_struct
id|pdflush_work
comma
id|list
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|pdf-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|pdflush_list
)paren
)paren
id|last_empty_jifs
op_assign
id|jiffies
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pdflush_lock
comma
id|flags
)paren
suffix:semicolon
id|pdf-&gt;fn
op_assign
id|fn
suffix:semicolon
id|pdf-&gt;arg0
op_assign
id|arg0
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ? */
id|wake_up_process
c_func
(paren
id|pdf-&gt;who
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|start_one_pdflush_thread
r_static
r_void
id|start_one_pdflush_thread
c_func
(paren
r_void
)paren
(brace
id|kernel_thread
c_func
(paren
id|pdflush
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGNAL
)paren
suffix:semicolon
)brace
DECL|function|pdflush_init
r_static
r_int
id|__init
id|pdflush_init
c_func
(paren
r_void
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
id|MIN_PDFLUSH_THREADS
suffix:semicolon
id|i
op_increment
)paren
id|start_one_pdflush_thread
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pdflush_init
id|module_init
c_func
(paren
id|pdflush_init
)paren
suffix:semicolon
eof