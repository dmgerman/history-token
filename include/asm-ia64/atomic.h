macro_line|#ifndef _ASM_IA64_ATOMIC_H
DECL|macro|_ASM_IA64_ATOMIC_H
mdefine_line|#define _ASM_IA64_ATOMIC_H
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; *&n; * NOTE: don&squot;t mess with the types below!  The &quot;unsigned long&quot; and&n; * &quot;int&quot; types were carefully placed so as to ensure proper operation&n; * of the macros.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * On IA-64, counter must always be volatile to ensure that that the&n; * memory accesses are ordered.&n; */
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_volatile
id|__s32
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;&t;((atomic_t) { (i) })
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;(((v)-&gt;counter) = (i))
r_static
id|__inline__
r_int
DECL|function|ia64_atomic_add
id|ia64_atomic_add
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__s32
id|old
comma
r_new
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|v
)paren
suffix:semicolon
id|old
op_assign
id|atomic_read
c_func
(paren
id|v
)paren
suffix:semicolon
r_new
op_assign
id|old
op_plus
id|i
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ia64_cmpxchg
c_func
(paren
l_string|&quot;acq&quot;
comma
id|v
comma
id|old
comma
id|old
op_plus
id|i
comma
r_sizeof
(paren
id|atomic_t
)paren
)paren
op_ne
id|old
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|ia64_atomic_sub
id|ia64_atomic_sub
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__s32
id|old
comma
r_new
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|v
)paren
suffix:semicolon
id|old
op_assign
id|atomic_read
c_func
(paren
id|v
)paren
suffix:semicolon
r_new
op_assign
id|old
op_minus
id|i
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ia64_cmpxchg
c_func
(paren
l_string|&quot;acq&quot;
comma
id|v
comma
id|old
comma
r_new
comma
r_sizeof
(paren
id|atomic_t
)paren
)paren
op_ne
id|old
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomically add I to V and return TRUE if the resulting value is&n; * negative.&n; */
r_static
id|__inline__
r_int
DECL|function|atomic_add_negative
id|atomic_add_negative
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|ia64_atomic_add
c_func
(paren
id|i
comma
id|v
)paren
OL
l_int|0
suffix:semicolon
)brace
DECL|macro|atomic_add_return
mdefine_line|#define atomic_add_return(i,v)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((__builtin_constant_p(i) &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t;  (   (i ==  1) || (i ==  4) || (i ==  8) || (i ==  16)&t;&t;&bslash;&n;&t;   || (i == -1) || (i == -4) || (i == -8) || (i == -16)))&t;&bslash;&n;&t; ? ia64_fetch_and_add(i, &amp;(v)-&gt;counter)&t;&t;&t;&t;&bslash;&n;&t; : ia64_atomic_add(i, v))
DECL|macro|atomic_sub_return
mdefine_line|#define atomic_sub_return(i,v)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((__builtin_constant_p(i) &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t;  (   (i ==  1) || (i ==  4) || (i ==  8) || (i ==  16)&t;&t;&bslash;&n;&t;   || (i == -1) || (i == -4) || (i == -8) || (i == -16)))&t;&bslash;&n;&t; ? ia64_fetch_and_add(-(i), &amp;(v)-&gt;counter)&t;&t;&t;&bslash;&n;&t; : ia64_atomic_sub(i, v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)&t;&t;atomic_sub_return(1, (v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)&t;&t;atomic_add_return(1, (v))
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v)&t;(atomic_sub_return((i), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;&t;(atomic_sub_return(1, (v)) == 0)
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v)&t;&t;(atomic_add_return(1, (v)) != 0)
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i,v)&t;&t;&t;atomic_add_return((i), (v))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i,v)&t;&t;&t;atomic_sub_return((i), (v))
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v)&t;&t;&t;atomic_add(1, (v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v)&t;&t;&t;atomic_sub(1, (v))
multiline_comment|/* Atomic operations are already serializing */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif /* _ASM_IA64_ATOMIC_H */
eof
