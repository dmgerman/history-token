macro_line|#ifndef _ASM_IA64_LOCAL_H
DECL|macro|_ASM_IA64_LOCAL_H
mdefine_line|#define _ASM_IA64_LOCAL_H
multiline_comment|/*&n; * Copyright (C) 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/percpu.h&gt;
r_typedef
r_struct
(brace
DECL|member|val
id|atomic64_t
id|val
suffix:semicolon
DECL|typedef|local_t
)brace
id|local_t
suffix:semicolon
DECL|macro|LOCAL_INIT
mdefine_line|#define LOCAL_INIT(i)&t;((local_t) { { (i) } })
DECL|macro|local_read
mdefine_line|#define local_read(l)&t;atomic64_read(&amp;(l)-&gt;val)
DECL|macro|local_set
mdefine_line|#define local_set(l, i)&t;atomic64_set(&amp;(l)-&gt;val, i)
DECL|macro|local_inc
mdefine_line|#define local_inc(l)&t;atomic64_inc(&amp;(l)-&gt;val)
DECL|macro|local_dec
mdefine_line|#define local_dec(l)&t;atomic64_dec(&amp;(l)-&gt;val)
DECL|macro|local_add
mdefine_line|#define local_add(l)&t;atomic64_add(&amp;(l)-&gt;val)
DECL|macro|local_sub
mdefine_line|#define local_sub(l)&t;atomic64_sub(&amp;(l)-&gt;val)
multiline_comment|/* Non-atomic variants, i.e., preemption disabled and won&squot;t be touched in interrupt, etc.  */
DECL|macro|__local_inc
mdefine_line|#define __local_inc(l)&t;&t;(++(l)-&gt;val.counter)
DECL|macro|__local_dec
mdefine_line|#define __local_dec(l)&t;&t;(--(l)-&gt;val.counter)
DECL|macro|__local_add
mdefine_line|#define __local_add(i,l)&t;((l)-&gt;val.counter += (i))
DECL|macro|__local_sub
mdefine_line|#define __local_sub(i,l)&t;((l)-&gt;val.counter -= (i))
multiline_comment|/*&n; * Use these for per-cpu local_t variables.  Note they take a variable (eg. mystruct.foo),&n; * not an address.&n; */
DECL|macro|cpu_local_read
mdefine_line|#define cpu_local_read(v)&t;local_read(&amp;__ia64_per_cpu_var(v))
DECL|macro|cpu_local_set
mdefine_line|#define cpu_local_set(v, i)&t;local_set(&amp;__ia64_per_cpu_var(v), (i))
DECL|macro|cpu_local_inc
mdefine_line|#define cpu_local_inc(v)&t;local_inc(&amp;__ia64_per_cpu_var(v))
DECL|macro|cpu_local_dec
mdefine_line|#define cpu_local_dec(v)&t;local_dec(&amp;__ia64_per_cpu_var(v))
DECL|macro|cpu_local_add
mdefine_line|#define cpu_local_add(i, v)&t;local_add((i), &amp;__ia64_per_cpu_var(v))
DECL|macro|cpu_local_sub
mdefine_line|#define cpu_local_sub(i, v)&t;local_sub((i), &amp;__ia64_per_cpu_var(v))
multiline_comment|/*&n; * Non-atomic increments, i.e., preemption disabled and won&squot;t be touched in interrupt,&n; * etc.&n; */
DECL|macro|__cpu_local_inc
mdefine_line|#define __cpu_local_inc(v)&t;__local_inc(&amp;__ia64_per_cpu_var(v))
DECL|macro|__cpu_local_dec
mdefine_line|#define __cpu_local_dec(v)&t;__local_dec(&amp;__ia64_per_cpu_var(v))
DECL|macro|__cpu_local_add
mdefine_line|#define __cpu_local_add(i, v)&t;__local_add((i), &amp;__ia64_per_cpu_var(v))
DECL|macro|__cpu_local_sub
mdefine_line|#define __cpu_local_sub(i, v)&t;__local_sub((i), &amp;__ia64_per_cpu_var(v))
macro_line|#endif /* _ASM_IA64_LOCAL_H */
eof
