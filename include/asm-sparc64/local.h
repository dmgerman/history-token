macro_line|#ifndef _ARCH_SPARC64_LOCAL_H
DECL|macro|_ARCH_SPARC64_LOCAL_H
mdefine_line|#define _ARCH_SPARC64_LOCAL_H
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|typedef|local_t
r_typedef
id|atomic64_t
id|local_t
suffix:semicolon
DECL|macro|LOCAL_INIT
mdefine_line|#define LOCAL_INIT(i)&t;ATOMIC64_INIT(i)
DECL|macro|local_read
mdefine_line|#define local_read(v)&t;atomic64_read(v)
DECL|macro|local_set
mdefine_line|#define local_set(v,i)&t;atomic64_set(v,i)
DECL|macro|local_inc
mdefine_line|#define local_inc(v)&t;atomic64_inc(v)
DECL|macro|local_dec
mdefine_line|#define local_dec(v)&t;atomic64_dec(v)
DECL|macro|local_add
mdefine_line|#define local_add(i, v)&t;atomic64_add(i, v)
DECL|macro|local_sub
mdefine_line|#define local_sub(i, v)&t;atomic64_sub(i, v)
DECL|macro|__local_inc
mdefine_line|#define __local_inc(v)&t;&t;((v)-&gt;counter++)
DECL|macro|__local_dec
mdefine_line|#define __local_dec(v)&t;&t;((v)-&gt;counter--)
DECL|macro|__local_add
mdefine_line|#define __local_add(i,v)&t;((v)-&gt;counter+=(i))
DECL|macro|__local_sub
mdefine_line|#define __local_sub(i,v)&t;((v)-&gt;counter-=(i))
multiline_comment|/* Use these for per-cpu local_t variables: on some archs they are&n; * much more efficient than these naive implementations.  Note they take&n; * a variable, not an address.&n; */
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
mdefine_line|#define __cpu_local_inc(v)&t;__local_inc(&amp;__get_cpu_var(v))
DECL|macro|__cpu_local_dec
mdefine_line|#define __cpu_local_dec(v)&t;__local_dec(&amp;__get_cpu_var(v))
DECL|macro|__cpu_local_add
mdefine_line|#define __cpu_local_add(i, v)&t;__local_add((i), &amp;__get_cpu_var(v))
DECL|macro|__cpu_local_sub
mdefine_line|#define __cpu_local_sub(i, v)&t;__local_sub((i), &amp;__get_cpu_var(v))
macro_line|#endif /* _ARCH_SPARC64_LOCAL_H */
eof
