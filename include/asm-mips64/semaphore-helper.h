multiline_comment|/*&n; * SMP- and interrupt-safe semaphores helper functions.&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * (C) Copyright 1999 Andrea Arcangeli&n; * (C) Copyright 1999, 2001 Ralf Baechle&n; * (C) Copyright 1999, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SEMAPHORE_HELPER_H
DECL|macro|_ASM_SEMAPHORE_HELPER_H
mdefine_line|#define _ASM_SEMAPHORE_HELPER_H
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
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|waking_non_zero
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tll&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;blez&bslash;t%1, 2f&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0, %1, 1&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0, %2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0, 1b&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
l_string|&quot;.text&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;waking
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_interruptible:&n; *&t;1&t;got the lock&n; *&t;0&t;go to sleep&n; *&t;-EINTR&t;interrupted&n; *&n; * We must undo the sem-&gt;count down_interruptible decrement&n; * simultaneously and atomicly with the sem-&gt;waking adjustment,&n; * otherwise we can race with wake_one_more.&n; *&n; * This is accomplished by doing a 64-bit ll/sc on the 2 32-bit words.&n; *&n; * Pseudocode:&n; *&n; * If(sem-&gt;waking &gt; 0) {&n; *&t;Decrement(sem-&gt;waking)&n; *&t;Return(SUCCESS)&n; * } else If(segnal_pending(tsk)) {&n; *&t;Increment(sem-&gt;count)&n; *&t;Return(-EINTR)&n; * } else {&n; *&t;Return(SLEEP)&n; * }&n; */
r_static
r_inline
r_int
DECL|function|waking_non_zero_interruptible
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
macro_line|#ifdef __MIPSEB__
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t# waking_non_zero_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;0:&bslash;tlld&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 0&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$1, %1, 0&bslash;n&bslash;t&quot;
l_string|&quot;blez&bslash;t$1, 1f&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t%1, %1, -1&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 1&bslash;n&bslash;t&quot;
l_string|&quot;b&bslash;t2f&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tbeqz&bslash;t%3, 2f&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;dli&bslash;t$1, 0x0000000100000000&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%1, %1, $1&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;tscd&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%1, 0b&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|sem
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EINTR
)paren
)paren
suffix:semicolon
macro_line|#elif defined(__MIPSEL__)
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t# waking_non_zero_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;t&t;noat&bslash;n&quot;
l_string|&quot;0:&bslash;tlld&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 0&bslash;n&bslash;t&quot;
l_string|&quot;blez&bslash;t%1, 1f&bslash;n&bslash;t&quot;
l_string|&quot;dli&bslash;t$1, 0x0000000100000000&bslash;n&bslash;t&quot;
l_string|&quot;dsubu&bslash;t%1, %1, $1&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 1&bslash;n&bslash;t&quot;
l_string|&quot;b&bslash;t2f&bslash;n&quot;
l_string|&quot;1:&bslash;tbeqz&bslash;t%3, 2f&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, %4&bslash;n&bslash;t&quot;
multiline_comment|/* &n;&t; * It would be nice to assume that sem-&gt;count&n;&t; * is != -1, but we will guard against that case&n;&t; */
l_string|&quot;daddiu&bslash;t$1, %1, 1&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t$1, $1, 0&bslash;n&bslash;t&quot;
l_string|&quot;dsrl32&bslash;t$1, $1, 0&bslash;n&bslash;t&quot;
l_string|&quot;dsrl32&bslash;t%1, %1, 0&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t%1, %1, 0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%1, %1, $1&bslash;n&quot;
l_string|&quot;2:&bslash;tscd&bslash;t%1, %2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t&t;%1, 0b&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|sem
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EINTR
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_trylock is unused.  we do everything in &n; * down_trylock and let non-ll/sc hosts bounce around.&n; */
r_static
r_inline
r_int
DECL|function|waking_non_zero_trylock
id|waking_non_zero_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SEMAPHORE_HELPER_H */
eof
