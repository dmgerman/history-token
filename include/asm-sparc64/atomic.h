multiline_comment|/* $Id: atomic.h,v 1.22 2001/07/11 23:56:07 davem Exp $&n; * atomic.h: Thankfully the V9 is at least reasonable for this&n; *           stuff.&n; *&n; * Copyright (C) 1996, 1997, 2000 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __ARCH_SPARC64_ATOMIC__
DECL|macro|__ARCH_SPARC64_ATOMIC__
mdefine_line|#define __ARCH_SPARC64_ATOMIC__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_volatile
r_int
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
DECL|member|counter
DECL|typedef|atomic64_t
r_typedef
r_struct
(brace
r_volatile
id|__s64
id|counter
suffix:semicolon
)brace
id|atomic64_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;&t;{ (i) }
DECL|macro|ATOMIC64_INIT
mdefine_line|#define ATOMIC64_INIT(i)&t;{ (i) }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic64_read
mdefine_line|#define atomic64_read(v)&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = i)
DECL|macro|atomic64_set
mdefine_line|#define atomic64_set(v, i)&t;(((v)-&gt;counter) = i)
r_extern
r_void
id|atomic_add
c_func
(paren
r_int
comma
id|atomic_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|atomic64_add
c_func
(paren
r_int
comma
id|atomic64_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|atomic_sub
c_func
(paren
r_int
comma
id|atomic_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|atomic64_sub
c_func
(paren
r_int
comma
id|atomic64_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atomic_add_ret
c_func
(paren
r_int
comma
id|atomic_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atomic64_add_ret
c_func
(paren
r_int
comma
id|atomic64_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atomic_sub_ret
c_func
(paren
r_int
comma
id|atomic_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atomic64_sub_ret
c_func
(paren
r_int
comma
id|atomic64_t
op_star
)paren
suffix:semicolon
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) atomic_sub_ret(1, v)
DECL|macro|atomic64_dec_return
mdefine_line|#define atomic64_dec_return(v) atomic64_sub_ret(1, v)
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_ret(1, v)
DECL|macro|atomic64_inc_return
mdefine_line|#define atomic64_inc_return(v) atomic64_add_ret(1, v)
DECL|macro|atomic_sub_return
mdefine_line|#define atomic_sub_return(i, v) atomic_sub_ret(i, v)
DECL|macro|atomic64_sub_return
mdefine_line|#define atomic64_sub_return(i, v) atomic64_sub_ret(i, v)
DECL|macro|atomic_add_return
mdefine_line|#define atomic_add_return(i, v) atomic_add_ret(i, v)
DECL|macro|atomic64_add_return
mdefine_line|#define atomic64_add_return(i, v) atomic64_add_ret(i, v)
multiline_comment|/*&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v) (atomic_inc_return(v) == 0)
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i, v) (atomic_sub_ret(i, v) == 0)
DECL|macro|atomic64_sub_and_test
mdefine_line|#define atomic64_sub_and_test(i, v) (atomic64_sub_ret(i, v) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_ret(1, v) == 0)
DECL|macro|atomic64_dec_and_test
mdefine_line|#define atomic64_dec_and_test(v) (atomic64_sub_ret(1, v) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1, v)
DECL|macro|atomic64_inc
mdefine_line|#define atomic64_inc(v) atomic64_add(1, v)
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1, v)
DECL|macro|atomic64_dec
mdefine_line|#define atomic64_dec(v) atomic64_sub(1, v)
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i, v) (atomic_add_ret(i, v) &lt; 0)
DECL|macro|atomic64_add_negative
mdefine_line|#define atomic64_add_negative(i, v) (atomic64_add_ret(i, v) &lt; 0)
multiline_comment|/* Atomic operations are already serializing */
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;membar(&quot;#StoreLoad | #LoadLoad&quot;)
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;membar(&quot;#StoreLoad | #StoreStore&quot;)
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;membar(&quot;#StoreLoad | #LoadLoad&quot;)
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;membar(&quot;#StoreLoad | #StoreStore&quot;)
macro_line|#else
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif
macro_line|#endif /* !(__ARCH_SPARC64_ATOMIC__) */
eof
