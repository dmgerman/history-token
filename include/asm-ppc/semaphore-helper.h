macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SEMAPHORE_HELPER_H
DECL|macro|_PPC_SEMAPHORE_HELPER_H
mdefine_line|#define _PPC_SEMAPHORE_HELPER_H
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * Adapted for PowerPC by Gary Thomas and Paul Mackerras&n; */
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * These two (wake_one_more and waking_non_zero) _must_ execute&n; * atomically wrt each other.&n; *&n; * This is trivially done with load with reservation and&n; * store conditional on the ppc.&n; */
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
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;waking
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
id|ret
comma
id|tmp
suffix:semicolon
multiline_comment|/* Atomic decrement sem-&gt;waking iff it is &gt; 0 */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx %1,0,%2&bslash;n&quot;
multiline_comment|/* tmp = sem-&gt;waking */
l_string|&quot;&t;cmpwi 0,%1,0&bslash;n&quot;
multiline_comment|/* test tmp */
l_string|&quot;&t;addic %1,%1,-1&bslash;n&quot;
multiline_comment|/* --tmp */
l_string|&quot;&t;ble- 2f&bslash;n&quot;
multiline_comment|/* exit if tmp was &lt;= 0 */
l_string|&quot;&t;stwcx. %1,0,%2&bslash;n&quot;
multiline_comment|/* update sem-&gt;waking */
l_string|&quot;&t;bne- 1b&bslash;n&quot;
multiline_comment|/* try again if update failed*/
l_string|&quot;&t;li %0,1&bslash;n&quot;
multiline_comment|/* ret = 1 */
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;waking
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_interruptible:&n; *&t;1&t;got the lock&n; *&t;0&t;go to sleep&n; *&t;-EINTR&t;interrupted&n; */
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
id|ret
comma
id|tmp
suffix:semicolon
multiline_comment|/* Atomic decrement sem-&gt;waking iff it is &gt; 0 */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx %1,0,%2&bslash;n&quot;
multiline_comment|/* tmp = sem-&gt;waking */
l_string|&quot;&t;cmpwi 0,%1,0&bslash;n&quot;
multiline_comment|/* test tmp */
l_string|&quot;&t;addic %1,%1,-1&bslash;n&quot;
multiline_comment|/* --tmp */
l_string|&quot;&t;ble- 2f&bslash;n&quot;
multiline_comment|/* exit if tmp was &lt;= 0 */
l_string|&quot;&t;stwcx. %1,0,%2&bslash;n&quot;
multiline_comment|/* update sem-&gt;waking */
l_string|&quot;&t;bne- 1b&bslash;n&quot;
multiline_comment|/* try again if update failed*/
l_string|&quot;&t;li %0,1&bslash;n&quot;
multiline_comment|/* ret = 1 */
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;waking
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
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
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_trylock:&n; *&t;1&t;failed to lock&n; *&t;0&t;got the lock&n; */
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
id|ret
comma
id|tmp
suffix:semicolon
multiline_comment|/* Atomic decrement sem-&gt;waking iff it is &gt; 0 */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx %1,0,%2&bslash;n&quot;
multiline_comment|/* tmp = sem-&gt;waking */
l_string|&quot;&t;cmpwi 0,%1,0&bslash;n&quot;
multiline_comment|/* test tmp */
l_string|&quot;&t;addic %1,%1,-1&bslash;n&quot;
multiline_comment|/* --tmp */
l_string|&quot;&t;ble- 2f&bslash;n&quot;
multiline_comment|/* exit if tmp was &lt;= 0 */
l_string|&quot;&t;stwcx. %1,0,%2&bslash;n&quot;
multiline_comment|/* update sem-&gt;waking */
l_string|&quot;&t;bne- 1b&bslash;n&quot;
multiline_comment|/* try again if update failed*/
l_string|&quot;&t;li %0,0&bslash;n&quot;
multiline_comment|/* ret = 0 */
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;waking
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* _PPC_SEMAPHORE_HELPER_H */
macro_line|#endif /* __KERNEL__ */
eof
