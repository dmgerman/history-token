multiline_comment|/* $Id: atomic.h,v 1.21 2000/10/03 07:28:56 anton Exp $&n; * atomic.h: Thankfully the V9 is at least reasonable for this&n; *           stuff.&n; *&n; * Copyright (C) 1996, 1997, 2000 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __ARCH_SPARC64_ATOMIC__
DECL|macro|__ARCH_SPARC64_ATOMIC__
mdefine_line|#define __ARCH_SPARC64_ATOMIC__
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
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = i)
r_extern
r_int
id|__atomic_add
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
id|__atomic_sub
c_func
(paren
r_int
comma
id|atomic_t
op_star
)paren
suffix:semicolon
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v) ((void)__atomic_add(i, v))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v) ((void)__atomic_sub(i, v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) __atomic_sub(1, v)
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) __atomic_add(1, v)
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i, v) (__atomic_sub(i, v) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (__atomic_sub(1, v) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) ((void)__atomic_add(1, v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) ((void)__atomic_sub(1, v))
multiline_comment|/* Atomic operations are already serializing */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif /* !(__ARCH_SPARC64_ATOMIC__) */
eof
