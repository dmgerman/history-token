multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; *&n; * But use these as seldom as possible since they are much more slower&n; * than regular operations.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1999, 2000 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_ATOMIC_H
DECL|macro|_ASM_ATOMIC_H
mdefine_line|#define _ASM_ATOMIC_H
macro_line|#include &lt;asm/sgidefs.h&gt;
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
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)    { (i) }
multiline_comment|/*&n; * atomic_read - read atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically reads the value of @v.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;((v)-&gt;counter)
multiline_comment|/*&n; * atomic_set - set atomic variable&n; * @v: pointer of type atomic_t&n; * @i: required value&n; *&n; * Atomically sets the value of @v to @i.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;((v)-&gt;counter = (i))
DECL|function|atomic_add
r_extern
id|__inline__
r_void
id|atomic_add
c_func
(paren
r_int
id|i
comma
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tll&bslash;t%0,%1&bslash;t&bslash;t&bslash;t# atomic_add&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0,1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
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
multiline_comment|/*&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_sub
r_extern
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tll&bslash;t%0,%1&bslash;t&bslash;t&bslash;t# atomic_sub&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0,1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
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
multiline_comment|/*&n; * Same as above, but return the result value&n; */
DECL|function|atomic_add_return
r_extern
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
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# atomic_add_return&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0,%1,%3&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0,%1,%3&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
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
id|result
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_extern
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
r_int
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# atomic_sub_return&bslash;n&quot;
l_string|&quot;1:&bslash;tll&bslash;t%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,%1,%3&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,%1,%3&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
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
id|result
suffix:semicolon
)brace
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) atomic_sub_return(1,(v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_return(1,(v))
multiline_comment|/*&n; * atomic_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
multiline_comment|/*&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; * atomic_inc_and_test is currently not implemented for mips64.&n; */
multiline_comment|/*&n; * atomic_dec_and_test - decrement by 1 and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all other&n; * cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_return(1, (v)) == 0)
multiline_comment|/*&n; * atomic_inc - increment atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
multiline_comment|/*&n; * atomic_dec - decrement and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
multiline_comment|/*&n; * atomic_add_negative - add and test if negative&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; *&n; * atomic_add_negative is currently not implemented for mips64.&n; */
multiline_comment|/* Atomic operations are already serializing */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif /* defined(__KERNEL__) */
macro_line|#endif /* _ASM_ATOMIC_H */
eof
