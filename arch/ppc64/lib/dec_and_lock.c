multiline_comment|/*&n; * ppc64 version of atomic_dec_and_lock() using cmpxchg&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * This is an implementation of the notion of &quot;decrement a&n; * reference count, and return locked if it decremented to zero&quot;.&n; *&n; * This implementation can be used on any architecture that&n; * has a cmpxchg, and where atomic-&gt;value is an int holding&n; * the value of the atomic (i.e. the high bits aren&squot;t used&n; * for a lock or anything like that).&n; *&n; * N.B. ATOMIC_DEC_AND_LOCK gets defined in include/linux/spinlock.h&n; * if spinlocks are empty and thus atomic_dec_and_lock is defined&n; * to be atomic_dec_and_test - in that case we don&squot;t need it&n; * defined here as well.&n; */
macro_line|#ifndef ATOMIC_DEC_AND_LOCK
DECL|function|atomic_dec_and_lock
r_int
id|atomic_dec_and_lock
c_func
(paren
id|atomic_t
op_star
id|atomic
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
id|counter
suffix:semicolon
r_int
id|newcount
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|counter
op_assign
id|atomic_read
c_func
(paren
id|atomic
)paren
suffix:semicolon
id|newcount
op_assign
id|counter
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newcount
)paren
r_break
suffix:semicolon
multiline_comment|/* do it the slow way */
id|newcount
op_assign
id|cmpxchg
c_func
(paren
op_amp
id|atomic-&gt;counter
comma
id|counter
comma
id|newcount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newcount
op_eq
id|counter
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
id|atomic
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atomic_dec_and_lock
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_dec_and_lock
)paren
suffix:semicolon
macro_line|#endif /* ATOMIC_DEC_AND_LOCK */
eof
