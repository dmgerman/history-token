multiline_comment|/* rwsem.c: R/W semaphores: contention handling functions&n; *&n; * Written by David Howells (dhowells@redhat.com).&n; * Derived from arch/i386/kernel/semaphore.c&n; */
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|struct|rwsem_waiter
r_struct
id|rwsem_waiter
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|RWSEM_WAITING_FOR_READ
mdefine_line|#define RWSEM_WAITING_FOR_READ&t;0x00000001
DECL|macro|RWSEM_WAITING_FOR_WRITE
mdefine_line|#define RWSEM_WAITING_FOR_WRITE&t;0x00000002
)brace
suffix:semicolon
macro_line|#if RWSEM_DEBUG
DECL|macro|rwsemtrace
macro_line|#undef rwsemtrace
DECL|function|rwsemtrace
r_void
id|rwsemtrace
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_const
r_char
op_star
id|str
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sem=%p&bslash;n&quot;
comma
id|sem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(sem)=%08lx&bslash;n&quot;
comma
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;debug
)paren
id|printk
c_func
(paren
l_string|&quot;[%d] %s({%08lx})&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|str
comma
id|sem-&gt;count
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * handle the lock being released whilst there are processes blocked on it that can now run&n; * - if we come here, then:&n; *   - the &squot;active part&squot; of the count (&amp;0x0000ffff) reached zero but has been re-incremented&n; *   - the &squot;waiting part&squot; of the count (&amp;0xffff0000) is negative (and will still be so)&n; *   - there must be someone on the queue&n; * - the spinlock must be held by the caller&n; * - woken process blocks are discarded from the list after having task zeroed&n; * - writers are only woken if wakewrite is non-zero&n; */
DECL|function|__rwsem_do_wake
r_static
r_inline
r_struct
id|rw_semaphore
op_star
id|__rwsem_do_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_int
id|wakewrite
)paren
(brace
r_struct
id|rwsem_waiter
op_star
id|waiter
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_int
r_int
id|oldcount
comma
id|woken
comma
id|loop
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering __rwsem_do_wake&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wakewrite
)paren
r_goto
id|dont_wake_writers
suffix:semicolon
multiline_comment|/* only wake someone up if we can transition the active part of the count from 0 -&gt; 1 */
id|try_again
suffix:colon
id|oldcount
op_assign
id|rwsem_atomic_update
c_func
(paren
id|RWSEM_ACTIVE_BIAS
comma
id|sem
)paren
op_minus
id|RWSEM_ACTIVE_BIAS
suffix:semicolon
r_if
c_cond
(paren
id|oldcount
op_amp
id|RWSEM_ACTIVE_MASK
)paren
r_goto
id|undo
suffix:semicolon
id|waiter
op_assign
id|list_entry
c_func
(paren
id|sem-&gt;wait_list.next
comma
r_struct
id|rwsem_waiter
comma
id|list
)paren
suffix:semicolon
multiline_comment|/* try to grant a single write lock if there&squot;s a writer at the front of the queue&n;&t; * - note we leave the &squot;active part&squot; of the count incremented by 1 and the waiting part&n;&t; *   incremented by 0x00010000&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|waiter-&gt;flags
op_amp
id|RWSEM_WAITING_FOR_WRITE
)paren
)paren
r_goto
id|readers_only
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|waiter-&gt;list
)paren
suffix:semicolon
id|tsk
op_assign
id|waiter-&gt;task
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|waiter-&gt;task
op_assign
l_int|NULL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|put_task_struct
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* don&squot;t want to wake any writers */
id|dont_wake_writers
suffix:colon
id|waiter
op_assign
id|list_entry
c_func
(paren
id|sem-&gt;wait_list.next
comma
r_struct
id|rwsem_waiter
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waiter-&gt;flags
op_amp
id|RWSEM_WAITING_FOR_WRITE
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* grant an infinite number of read locks to the readers at the front of the queue&n;&t; * - note we increment the &squot;active part&squot; of the count by the number of readers (less one&n;&t; *   for the activity decrement we&squot;ve already done) before waking any processes up&n;&t; */
id|readers_only
suffix:colon
id|woken
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|woken
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|waiter-&gt;list.next
op_eq
op_amp
id|sem-&gt;wait_list
)paren
r_break
suffix:semicolon
id|waiter
op_assign
id|list_entry
c_func
(paren
id|waiter-&gt;list.next
comma
r_struct
id|rwsem_waiter
comma
id|list
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|waiter-&gt;flags
op_amp
id|RWSEM_WAITING_FOR_READ
)paren
suffix:semicolon
id|loop
op_assign
id|woken
suffix:semicolon
id|woken
op_mul_assign
id|RWSEM_ACTIVE_BIAS
op_minus
id|RWSEM_WAITING_BIAS
suffix:semicolon
id|woken
op_sub_assign
id|RWSEM_ACTIVE_BIAS
suffix:semicolon
id|rwsem_atomic_add
c_func
(paren
id|woken
comma
id|sem
)paren
suffix:semicolon
id|next
op_assign
id|sem-&gt;wait_list.next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|loop
OG
l_int|0
suffix:semicolon
id|loop
op_decrement
)paren
(brace
id|waiter
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|rwsem_waiter
comma
id|list
)paren
suffix:semicolon
id|next
op_assign
id|waiter-&gt;list.next
suffix:semicolon
id|tsk
op_assign
id|waiter-&gt;task
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|waiter-&gt;task
op_assign
l_int|NULL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|put_task_struct
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
id|sem-&gt;wait_list.next
op_assign
id|next
suffix:semicolon
id|next-&gt;prev
op_assign
op_amp
id|sem-&gt;wait_list
suffix:semicolon
id|out
suffix:colon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving __rwsem_do_wake&quot;
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
multiline_comment|/* undo the change to count, but check for a transition 1-&gt;0 */
id|undo
suffix:colon
r_if
c_cond
(paren
id|rwsem_atomic_update
c_func
(paren
op_minus
id|RWSEM_ACTIVE_BIAS
comma
id|sem
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
)brace
multiline_comment|/*&n; * wait for a lock to be granted&n; */
DECL|function|rwsem_down_failed_common
r_static
r_inline
r_struct
id|rw_semaphore
op_star
id|rwsem_down_failed_common
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_struct
id|rwsem_waiter
op_star
id|waiter
comma
r_int
r_int
id|adjustment
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* set up my own style of waitqueue */
id|spin_lock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
id|waiter-&gt;task
op_assign
id|tsk
suffix:semicolon
id|get_task_struct
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|waiter-&gt;list
comma
op_amp
id|sem-&gt;wait_list
)paren
suffix:semicolon
multiline_comment|/* note that we&squot;re now waiting on the lock, but no longer actively read-locking */
id|count
op_assign
id|rwsem_atomic_update
c_func
(paren
id|adjustment
comma
id|sem
)paren
suffix:semicolon
multiline_comment|/* if there are no longer active locks, wake the front queued process(es) up&n;&t; * - it might even be this process, since the waker takes a more active part&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|count
op_amp
id|RWSEM_ACTIVE_MASK
)paren
)paren
id|sem
op_assign
id|__rwsem_do_wake
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
multiline_comment|/* wait to be given the lock */
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
id|waiter-&gt;task
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/*&n; * wait for the read lock to be granted&n; */
DECL|function|rwsem_down_read_failed
r_struct
id|rw_semaphore
id|fastcall
id|__sched
op_star
id|rwsem_down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|rwsem_waiter
id|waiter
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering rwsem_down_read_failed&quot;
)paren
suffix:semicolon
id|waiter.flags
op_assign
id|RWSEM_WAITING_FOR_READ
suffix:semicolon
id|rwsem_down_failed_common
c_func
(paren
id|sem
comma
op_amp
id|waiter
comma
id|RWSEM_WAITING_BIAS
op_minus
id|RWSEM_ACTIVE_BIAS
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving rwsem_down_read_failed&quot;
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/*&n; * wait for the write lock to be granted&n; */
DECL|function|rwsem_down_write_failed
r_struct
id|rw_semaphore
id|fastcall
id|__sched
op_star
id|rwsem_down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|rwsem_waiter
id|waiter
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering rwsem_down_write_failed&quot;
)paren
suffix:semicolon
id|waiter.flags
op_assign
id|RWSEM_WAITING_FOR_WRITE
suffix:semicolon
id|rwsem_down_failed_common
c_func
(paren
id|sem
comma
op_amp
id|waiter
comma
op_minus
id|RWSEM_ACTIVE_BIAS
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving rwsem_down_write_failed&quot;
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/*&n; * handle waking up a waiter on the semaphore&n; * - up_read has decremented the active part of the count if we come here&n; */
DECL|function|rwsem_wake
r_struct
id|rw_semaphore
id|fastcall
op_star
id|rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering rwsem_wake&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
multiline_comment|/* do nothing if list empty */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sem-&gt;wait_list
)paren
)paren
id|sem
op_assign
id|__rwsem_do_wake
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving rwsem_wake&quot;
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/*&n; * downgrade a write lock into a read lock&n; * - caller incremented waiting part of count, and discovered it to be still negative&n; * - just wake up any readers at the front of the queue&n; */
DECL|function|rwsem_downgrade_wake
r_struct
id|rw_semaphore
id|fastcall
op_star
id|rwsem_downgrade_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering rwsem_downgrade_wake&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
multiline_comment|/* do nothing if list empty */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sem-&gt;wait_list
)paren
)paren
id|sem
op_assign
id|__rwsem_do_wake
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving rwsem_downgrade_wake&quot;
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
DECL|variable|rwsem_down_read_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|rwsem_down_read_failed
)paren
suffix:semicolon
DECL|variable|rwsem_down_write_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|rwsem_down_write_failed
)paren
suffix:semicolon
DECL|variable|rwsem_wake
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|rwsem_wake
)paren
suffix:semicolon
DECL|variable|rwsem_downgrade_wake
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|rwsem_downgrade_wake
)paren
suffix:semicolon
macro_line|#if RWSEM_DEBUG
DECL|variable|rwsemtrace
id|EXPORT_SYMBOL
c_func
(paren
id|rwsemtrace
)paren
suffix:semicolon
macro_line|#endif
eof
