macro_line|#ifndef _ARCH_X8664_LOCAL_H
DECL|macro|_ARCH_X8664_LOCAL_H
mdefine_line|#define _ARCH_X8664_LOCAL_H
macro_line|#include &lt;linux/percpu.h&gt;
r_typedef
r_struct
(brace
DECL|member|counter
r_volatile
r_int
r_int
id|counter
suffix:semicolon
DECL|typedef|local_t
)brace
id|local_t
suffix:semicolon
DECL|macro|LOCAL_INIT
mdefine_line|#define LOCAL_INIT(i)&t;{ (i) }
DECL|macro|local_read
mdefine_line|#define local_read(v)&t;((v)-&gt;counter)
DECL|macro|local_set
mdefine_line|#define local_set(v,i)&t;(((v)-&gt;counter) = (i))
DECL|function|local_inc
r_static
id|__inline__
r_void
id|local_inc
c_func
(paren
id|local_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
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
DECL|function|local_dec
r_static
id|__inline__
r_void
id|local_dec
c_func
(paren
id|local_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
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
DECL|function|local_add
r_static
id|__inline__
r_void
id|local_add
c_func
(paren
r_int
r_int
id|i
comma
id|local_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
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
DECL|function|local_sub
r_static
id|__inline__
r_void
id|local_sub
c_func
(paren
r_int
r_int
id|i
comma
id|local_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
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
multiline_comment|/* On x86, these are no better than the atomic variants. */
DECL|macro|__local_inc
mdefine_line|#define __local_inc(l)&t;&t;local_inc(l)
DECL|macro|__local_dec
mdefine_line|#define __local_dec(l)&t;&t;local_dec(l)
DECL|macro|__local_add
mdefine_line|#define __local_add(i,l)&t;local_add((i),(l))
DECL|macro|__local_sub
mdefine_line|#define __local_sub(i,l)&t;local_sub((i),(l))
multiline_comment|/* Use these for per-cpu local_t variables: on some archs they are&n; * much more efficient than these naive implementations.  Note they take&n; * a variable, not an address.&n; *&n; * This could be done better if we moved the per cpu data directly&n; * after GS.&n; */
DECL|macro|cpu_local_read
mdefine_line|#define cpu_local_read(v)&t;local_read(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_set
mdefine_line|#define cpu_local_set(v, i)&t;local_set(&amp;__get_cpu_var(v), (i))
DECL|macro|cpu_local_inc
mdefine_line|#define cpu_local_inc(v)&t;local_inc(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_dec
mdefine_line|#define cpu_local_dec(v)&t;local_dec(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_add
mdefine_line|#define cpu_local_add(i, v)&t;local_add((i), &amp;__get_cpu_var(v))
DECL|macro|cpu_local_sub
mdefine_line|#define cpu_local_sub(i, v)&t;local_sub((i), &amp;__get_cpu_var(v))
DECL|macro|__cpu_local_inc
mdefine_line|#define __cpu_local_inc(v)&t;cpu_local_inc(v)
DECL|macro|__cpu_local_dec
mdefine_line|#define __cpu_local_dec(v)&t;cpu_local_dec(v)
DECL|macro|__cpu_local_add
mdefine_line|#define __cpu_local_add(i, v)&t;cpu_local_add((i), (v))
DECL|macro|__cpu_local_sub
mdefine_line|#define __cpu_local_sub(i, v)&t;cpu_local_sub((i), (v))
macro_line|#endif /* _ARCH_I386_LOCAL_H */
eof
