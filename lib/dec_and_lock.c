macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * This is an architecture-neutral, but slow,&n; * implementation of the notion of &quot;decrement&n; * a reference count, and return locked if it&n; * decremented to zero&quot;.&n; *&n; * NOTE NOTE NOTE! This is _not_ equivalent to&n; *&n; *&t;if (atomic_dec_and_test(&amp;atomic)) {&n; *&t;&t;spin_lock(&amp;lock);&n; *&t;&t;return 1;&n; *&t;}&n; *&t;return 0;&n; *&n; * because the spin-lock and the decrement must be&n; * &quot;atomic&quot;.&n; *&n; * This slow version gets the spinlock unconditionally,&n; * and releases it if it isn&squot;t needed. Architectures&n; * are encouraged to come up with better approaches,&n; * this is trivially done efficiently using a load-locked&n; * store-conditional approach, for example.&n; */
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
macro_line|#endif
eof
