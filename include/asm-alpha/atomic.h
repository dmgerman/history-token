macro_line|#ifndef _ALPHA_ATOMIC_H
DECL|macro|_ALPHA_ATOMIC_H
mdefine_line|#define _ALPHA_ATOMIC_H
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc...&n; *&n; * But use these as seldom as possible since they are much slower&n; * than regular operations.&n; */
multiline_comment|/*&n; * Counter is volatile to make sure gcc doesn&squot;t try to be clever&n; * and move things around on us. We need to use _exactly_ the address&n; * the user gave us, not some alias that contains the same information.&n; */
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
r_int
id|counter
suffix:semicolon
)brace
id|atomic64_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;&t;( (atomic_t) { (i) } )
DECL|macro|ATOMIC64_INIT
mdefine_line|#define ATOMIC64_INIT(i)&t;( (atomic64_t) { (i) } )
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter + 0)
DECL|macro|atomic64_read
mdefine_line|#define atomic64_read(v)&t;((v)-&gt;counter + 0)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;((v)-&gt;counter = (i))
DECL|macro|atomic64_set
mdefine_line|#define atomic64_set(v,i)&t;((v)-&gt;counter = (i))
multiline_comment|/*&n; * To get proper branch prediction for the main line, we must branch&n; * forward to code at the end of this object&squot;s .text section, then&n; * branch back to restart the operation.&n; */
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
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%1&bslash;n&quot;
l_string|&quot;&t;addl %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stl_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
DECL|function|atomic64_add
r_static
id|__inline__
r_void
id|atomic64_add
c_func
(paren
r_int
id|i
comma
id|atomic64_t
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
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;addq %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%1&bslash;n&quot;
l_string|&quot;&t;subl %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stl_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
DECL|function|atomic64_sub
r_static
id|__inline__
r_void
id|atomic64_sub
c_func
(paren
r_int
id|i
comma
id|atomic64_t
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
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;subq %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%1&bslash;n&quot;
l_string|&quot;&t;addl %0,%3,%2&bslash;n&quot;
l_string|&quot;&t;addl %0,%3,%0&bslash;n&quot;
l_string|&quot;&t;stl_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|result
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
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(a, v)&t;(atomic_add_return((a), (v)) &lt; 0)
DECL|function|atomic64_add_return
r_static
id|__inline__
r_int
id|atomic64_add_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;addq %0,%3,%2&bslash;n&quot;
l_string|&quot;&t;addq %0,%3,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|result
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
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%1&bslash;n&quot;
l_string|&quot;&t;subl %0,%3,%2&bslash;n&quot;
l_string|&quot;&t;subl %0,%3,%0&bslash;n&quot;
l_string|&quot;&t;stl_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|result
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
DECL|function|atomic64_sub_return
r_static
id|__inline__
r_int
id|atomic64_sub_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;subq %0,%3,%2&bslash;n&quot;
l_string|&quot;&t;subq %0,%3,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|result
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
DECL|macro|atomic64_dec_return
mdefine_line|#define atomic64_dec_return(v) atomic64_sub_return(1,(v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_return(1,(v))
DECL|macro|atomic64_inc_return
mdefine_line|#define atomic64_inc_return(v) atomic64_add_return(1,(v))
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
DECL|macro|atomic64_sub_and_test
mdefine_line|#define atomic64_sub_and_test(i,v) (atomic64_sub_return((i), (v)) == 0)
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v) (atomic_add_return(1, (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_return(1, (v)) == 0)
DECL|macro|atomic64_dec_and_test
mdefine_line|#define atomic64_dec_and_test(v) (atomic64_sub_return(1, (v)) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
DECL|macro|atomic64_inc
mdefine_line|#define atomic64_inc(v) atomic64_add(1,(v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
DECL|macro|atomic64_dec
mdefine_line|#define atomic64_dec(v) atomic64_sub(1,(v))
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;smp_mb()
macro_line|#endif /* _ALPHA_ATOMIC_H */
eof
