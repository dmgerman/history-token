macro_line|#ifndef __ARCH_I386_ATOMIC__
DECL|macro|__ARCH_I386_ATOMIC__
mdefine_line|#define __ARCH_I386_ATOMIC__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOCK
mdefine_line|#define LOCK &quot;lock ; &quot;
macro_line|#else
DECL|macro|LOCK
mdefine_line|#define LOCK &quot;&quot;
macro_line|#endif
multiline_comment|/*&n; * Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
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
multiline_comment|/**&n; * atomic_read - read atomic variable&n; * @v: pointer of type atomic_t&n; * &n; * Atomically reads the value of @v.&n; */
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
multiline_comment|/**&n; * atomic_set - set atomic variable&n; * @v: pointer of type atomic_t&n; * @i: required value&n; * &n; * Atomically sets the value of @v to @i.&n; */
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;(((v)-&gt;counter) = (i))
multiline_comment|/**&n; * atomic_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; * &n; * Atomically adds @i to @v.&n; */
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
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
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;addl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; * &n; * Atomically subtracts @i from @v.&n; */
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
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
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;subl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; * &n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.&n; */
DECL|function|atomic_sub_and_test
r_static
id|__inline__
r_int
id|atomic_sub_and_test
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
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;subl %2,%0; sete %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_inc - increment atomic variable&n; * @v: pointer of type atomic_t&n; * &n; * Atomically increments @v by 1.&n; */
DECL|function|atomic_inc
r_static
id|__inline__
r_void
id|atomic_inc
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;incl %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_dec - decrement atomic variable&n; * @v: pointer of type atomic_t&n; * &n; * Atomically decrements @v by 1.&n; */
DECL|function|atomic_dec
r_static
id|__inline__
r_void
id|atomic_dec
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;decl %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_dec_and_test - decrement and test&n; * @v: pointer of type atomic_t&n; * &n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all other&n; * cases.&n; */
DECL|function|atomic_dec_and_test
r_static
id|__inline__
r_int
id|atomic_dec_and_test
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;decl %0; sete %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|c
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_inc_and_test - increment and test &n; * @v: pointer of type atomic_t&n; * &n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|function|atomic_inc_and_test
r_static
id|__inline__
r_int
id|atomic_inc_and_test
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;incl %0; sete %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|c
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_add_negative - add and test if negative&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; * &n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.&n; */
DECL|function|atomic_add_negative
r_static
id|__inline__
r_int
id|atomic_add_negative
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
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;addl %2,%0; sets %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_add_return - add and return&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns @i + @v&n; */
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
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
r_int
id|__i
suffix:semicolon
macro_line|#ifdef CONFIG_M386
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|boot_cpu_data.x86
op_eq
l_int|3
)paren
)paren
(brace
r_goto
id|no_xadd
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Modern 486+ processor */
id|__i
op_assign
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;xaddl %0, %1;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
comma
l_string|&quot;0&quot;
(paren
id|i
)paren
)paren
suffix:semicolon
r_return
id|i
op_plus
id|__i
suffix:semicolon
macro_line|#ifdef CONFIG_M386
id|no_xadd
suffix:colon
multiline_comment|/* Legacy 386 processor */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|__i
op_assign
id|atomic_read
c_func
(paren
id|v
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
id|v
comma
id|i
op_plus
id|__i
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|i
op_plus
id|__i
suffix:semicolon
macro_line|#endif
)brace
DECL|function|atomic_sub_return
r_static
id|__inline__
r_int
id|atomic_sub_return
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
r_return
id|atomic_add_return
c_func
(paren
op_minus
id|i
comma
id|v
)paren
suffix:semicolon
)brace
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)  (atomic_add_return(1,v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)  (atomic_sub_return(1,v))
multiline_comment|/* These are x86-specific, used by some header files */
DECL|macro|atomic_clear_mask
mdefine_line|#define atomic_clear_mask(mask, addr) &bslash;&n;__asm__ __volatile__(LOCK &quot;andl %0,%1&quot; &bslash;&n;: : &quot;r&quot; (~(mask)),&quot;m&quot; (*addr) : &quot;memory&quot;)
DECL|macro|atomic_set_mask
mdefine_line|#define atomic_set_mask(mask, addr) &bslash;&n;__asm__ __volatile__(LOCK &quot;orl %0,%1&quot; &bslash;&n;: : &quot;r&quot; (mask),&quot;m&quot; (*(addr)) : &quot;memory&quot;)
multiline_comment|/* Atomic operations are already serializing on x86 */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif
eof
