multiline_comment|/* atomic.h: These still suck, but the I-cache hit rate is higher.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 2000 Anton Blanchard (anton@linuxcare.com.au)&n; */
macro_line|#ifndef __ARCH_SPARC_ATOMIC__
DECL|macro|__ARCH_SPARC_ATOMIC__
mdefine_line|#define __ARCH_SPARC_ATOMIC__
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef __KERNEL__
macro_line|#ifndef CONFIG_SMP
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)  { (i) }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)          ((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)        (((v)-&gt;counter) = i)
macro_line|#else
multiline_comment|/* We do the bulk of the actual work out of line in two common&n; * routines in assembler, see arch/sparc/lib/atomic.S for the&n; * &quot;fun&quot; details.&n; *&n; * For SMP the trick is you embed the spin lock byte within&n; * the word, use the low byte so signedness is easily retained&n; * via a quick arithmetic shift.  It looks like this:&n; *&n; *&t;----------------------------------------&n; *&t;| signed 24-bit counter value |  lock  |  atomic_t&n; *&t;----------------------------------------&n; *&t; 31                          8 7      0&n; */
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i &lt;&lt; 8) }
DECL|function|atomic_read
r_static
id|__inline__
r_int
id|atomic_read
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|ret
op_assign
id|v-&gt;counter
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_amp
l_int|0xff
)paren
(brace
id|ret
op_assign
id|v-&gt;counter
suffix:semicolon
)brace
r_return
id|ret
op_rshift
l_int|8
suffix:semicolon
)brace
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = ((i) &lt;&lt; 8))
macro_line|#endif
DECL|function|__atomic_add
r_static
id|__inline__
r_int
id|__atomic_add
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_register
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
id|ptr
op_assign
op_amp
id|v-&gt;counter
suffix:semicolon
id|increment
op_assign
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_add
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|increment
suffix:semicolon
)brace
DECL|function|__atomic_sub
r_static
id|__inline__
r_int
id|__atomic_sub
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_register
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
id|ptr
op_assign
op_amp
id|v-&gt;counter
suffix:semicolon
id|increment
op_assign
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_sub
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|increment
suffix:semicolon
)brace
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v) ((void)__atomic_add((i), (v)))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v) ((void)__atomic_sub((i), (v)))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) __atomic_sub(1, (v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) __atomic_add(1, (v))
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i, v) (__atomic_sub((i), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (__atomic_sub(1, (v)) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) ((void)__atomic_add(1, (v)))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) ((void)__atomic_sub(1, (v)))
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i, v) (__atomic_add((i), (v)) &lt; 0)
multiline_comment|/* Atomic operations are already serializing */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif /* !(__KERNEL__) */
macro_line|#endif /* !(__ARCH_SPARC_ATOMIC__) */
eof
