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
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;( (atomic_t) { (i) } )
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;((v)-&gt;counter = (i))
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
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) atomic_sub_return(1,(v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_return(1,(v))
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_return(1, (v)) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
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
