macro_line|#ifndef ASMARM_SEMAPHORE_HELPER_H
DECL|macro|ASMARM_SEMAPHORE_HELPER_H
mdefine_line|#define ASMARM_SEMAPHORE_HELPER_H
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; */
DECL|function|wake_one_more
r_static
r_inline
r_void
id|wake_one_more
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
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
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_le
l_int|0
)paren
id|sem-&gt;waking
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|waking_non_zero
r_static
r_inline
r_int
id|waking_non_zero
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;waking
OG
l_int|0
)paren
(brace
id|sem-&gt;waking
op_decrement
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking non zero interruptible&n; *&t;1&t;got the lock&n; *&t;0&t;go to sleep&n; *&t;-EINTR&t;interrupted&n; *&n; * We must undo the sem-&gt;count down_interruptible() increment while we are&n; * protected by the spinlock in order to make this atomic_inc() with the&n; * atomic_read() in wake_one_more(), otherwise we can race. -arca&n; */
DECL|function|waking_non_zero_interruptible
r_static
r_inline
r_int
id|waking_non_zero_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_struct
id|task_struct
op_star
id|tsk
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;waking
OG
l_int|0
)paren
(brace
id|sem-&gt;waking
op_decrement
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_try_lock:&n; *&t;1&t;failed to lock&n; *&t;0&t;got the lock&n; *&n; * We must undo the sem-&gt;count down_interruptible() increment while we are&n; * protected by the spinlock in order to make this atomic_inc() with the&n; * atomic_read() in wake_one_more(), otherwise we can race. -arca&n; */
DECL|function|waking_non_zero_trylock
r_static
r_inline
r_int
id|waking_non_zero_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;waking
op_le
l_int|0
)paren
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_else
(brace
id|sem-&gt;waking
op_decrement
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
