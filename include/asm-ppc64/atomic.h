multiline_comment|/*&n; * PowerPC64 atomic operations&n; *&n; * Copyright (C) 2001 Paul Mackerras &lt;paulus@au.ibm.com&gt;, IBM&n; * Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_PPC64_ATOMIC_H_ 
DECL|macro|_ASM_PPC64_ATOMIC_H_
mdefine_line|#define _ASM_PPC64_ATOMIC_H_
macro_line|#include &lt;asm/memory.h&gt;
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
mdefine_line|#define atomic_set(v,i)&t;&t;(((v)-&gt;counter) = (i))
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
c_func
(paren
r_int
id|a
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;%0,0,%3&t;&t;# atomic_add&bslash;n&bslash;&n;&t;add&t;%0,%2,%0&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
c_func
(paren
r_int
id|a
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%2&t;&t;# atomic_add_return&bslash;n&bslash;&n;&t;add&t;%0,%1,%0&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(a, v)&t;(atomic_add_return((a), (v)) &lt; 0)
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|a
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;%0,0,%3&t;&t;# atomic_sub&bslash;n&bslash;&n;&t;subf&t;%0,%2,%0&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
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
id|a
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%2&t;&t;# atomic_sub_return&bslash;n&bslash;&n;&t;subf&t;%0,%1,%0&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
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
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;%0,0,%2&t;&t;# atomic_inc&bslash;n&bslash;&n;&t;addic&t;%0,%0,1&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc_return
r_static
id|__inline__
r_int
id|atomic_inc_return
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%1&t;&t;# atomic_inc_return&bslash;n&bslash;&n;&t;addic&t;%0,%0,1&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
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
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;%0,0,%2&t;&t;# atomic_dec&bslash;n&bslash;&n;&t;addic&t;%0,%0,-1&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_return
r_static
id|__inline__
r_int
id|atomic_dec_return
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%1&t;&t;# atomic_dec_return&bslash;n&bslash;&n;&t;addic&t;%0,%0,-1&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(a, v)&t;(atomic_sub_return((a), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;&t;(atomic_dec_return((v)) == 0)
multiline_comment|/*&n; * Atomically test *v and decrement if it is greater than 0.&n; * The function returns the old value of *v minus 1.&n; */
DECL|function|atomic_dec_if_positive
r_static
id|__inline__
r_int
id|atomic_dec_if_positive
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|t
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%1&t;&t;# atomic_dec_if_positive&bslash;n&bslash;&n;&t;addic.&t;%0,%0,-1&bslash;n&bslash;&n;&t;blt-&t;2f&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
l_string|&quot;&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()     smp_mb()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()      smp_mb()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()     smp_mb()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()      smp_mb()
macro_line|#endif /* _ASM_PPC64_ATOMIC_H_ */
eof
