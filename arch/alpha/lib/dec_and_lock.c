multiline_comment|/*&n; * arch/alpha/lib/dec_and_lock.c&n; *&n; * ll/sc version of atomic_dec_and_lock()&n; * &n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
id|asm
(paren
l_string|&quot;.text&t;&t;&t;&t;&t;&bslash;n&bslash;&n;&t;.global _atomic_dec_and_lock&t;&t;&bslash;n&bslash;&n;&t;.ent _atomic_dec_and_lock&t;&t;&bslash;n&bslash;&n;&t;.align&t;4&t;&t;&t;&t;&bslash;n&bslash;&n;_atomic_dec_and_lock:&t;&t;&t;&t;&bslash;n&bslash;&n;&t;.prologue 0&t;&t;&t;&t;&bslash;n&bslash;&n;1:&t;ldl_l&t;$1, 0($16)&t;&t;&t;&bslash;n&bslash;&n;&t;subl&t;$1, 1, $1&t;&t;&t;&bslash;n&bslash;&n;&t;beq&t;$1, 2f&t;&t;&t;&t;&bslash;n&bslash;&n;&t;stl_c&t;$1, 0($16)&t;&t;&t;&bslash;n&bslash;&n;&t;beq&t;$1, 4f&t;&t;&t;&t;&bslash;n&bslash;&n;&t;mb&t;&t;&t;&t;&t;&bslash;n&bslash;&n;&t;clr&t;$0&t;&t;&t;&t;&bslash;n&bslash;&n;&t;ret&t;&t;&t;&t;&t;&bslash;n&bslash;&n;2:&t;br&t;$29, 3f&t;&t;&t;&t;&bslash;n&bslash;&n;3:&t;ldgp&t;$29, 0($29)&t;&t;&t;&bslash;n&bslash;&n;&t;br&t;$atomic_dec_and_lock_1..ng&t;&bslash;n&bslash;&n;&t;.subsection 2&t;&t;&t;&t;&bslash;n&bslash;&n;4:&t;br&t;1b&t;&t;&t;&t;&bslash;n&bslash;&n;&t;.previous&t;&t;&t;&t;&bslash;n&bslash;&n;&t;.end _atomic_dec_and_lock&quot;
)paren
suffix:semicolon
r_static
r_int
id|__attribute_used__
DECL|function|atomic_dec_and_lock_1
id|atomic_dec_and_lock_1
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
multiline_comment|/* Slow path */
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
eof
