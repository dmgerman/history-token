multiline_comment|/* $Id: semaphore.c,v 1.9 2001/11/18 00:12:56 davem Exp $&n; * semaphore.c: Sparc64 semaphore implementation.&n; *&n; * This is basically the PPC semaphore scheme ported to use&n; * the sparc64 atomic instructions, so see the PPC code for&n; * credits.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*&n; * Atomically update sem-&gt;count.&n; * This does the equivalent of the following:&n; *&n; *&t;old_count = sem-&gt;count;&n; *&t;tmp = MAX(old_count, 0) + incr;&n; *&t;sem-&gt;count = tmp;&n; *&t;return old_count;&n; */
DECL|function|__sem_update_count
r_static
id|__inline__
r_int
id|__sem_update_count
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_int
id|incr
)paren
(brace
r_int
id|old_count
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! __sem_update_count old_count(%0) tmp(%1) incr(%4) &amp;sem-&gt;count(%3)&bslash;n&quot;
l_string|&quot;1:&t;ldsw&t;[%3], %0&bslash;n&quot;
l_string|&quot;&t;mov&t;%0, %1&bslash;n&quot;
l_string|&quot;&t;cmp&t;%0, 0&bslash;n&quot;
l_string|&quot;&t;movl&t;%%icc, 0, %1&bslash;n&quot;
l_string|&quot;&t;add&t;%1, %4, %1&bslash;n&quot;
l_string|&quot;&t;cas&t;[%3], %0, %1&bslash;n&quot;
l_string|&quot;&t;cmp&t;%0, %1&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; membar #StoreLoad | #StoreStore&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old_count
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;r&quot;
(paren
id|incr
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|old_count
suffix:semicolon
)brace
DECL|function|__up
r_static
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|__sem_update_count
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|up
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count + 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 0)&n;&t; *&t;&t;__up(sem);&n;&t; *&n;&t; * The (old_val &lt; 0) test is equivalent to&n;&t; * the more straightforward (new_val &lt;= 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! up sem(%0)&bslash;n&quot;
l_string|&quot;&t;membar&t;#StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;add&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; addcc&t;%%g7, 1, %%g0&bslash;n&quot;
l_string|&quot;&t;ble,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__up
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|__down
r_static
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|__sem_update_count
c_func
(paren
id|sem
comma
op_minus
l_int|1
)paren
op_le
l_int|0
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|down
r_void
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 1)&n;&t; *&t;&t;__down(sem);&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down sem(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|down_trylock
r_int
id|down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;if (old_val &lt; 1) {&n;&t; *&t;&t;ret = 1;&n;&t; *&t;} else {&n;&t; *&t;&t;sem-&gt;count = new_val;&n;&t; *&t;&t;ret = 0;&n;&t; *&t;}&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down_trylock sem(%1) ret(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%1], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 2f&bslash;n&quot;
l_string|&quot;&t; mov&t;1, %0&bslash;n&quot;
l_string|&quot;&t;cas&t;[%1], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; mov&t;0, %0&bslash;n&quot;
l_string|&quot;&t;membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__down_interruptible
r_static
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|__sem_update_count
c_func
(paren
id|sem
comma
op_minus
l_int|1
)paren
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|__sem_update_count
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
)brace
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|down_interruptible
r_int
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 1)&n;&t; *&t;&t;ret = __down_interruptible(sem);&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down_interruptible sem(%2) ret(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%2], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%2], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%2, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%3&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l3, %%g3&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%o0, %%g0, %0&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down_interruptible
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
