macro_line|#ifndef _ASM_IA64_PERCPU_H
DECL|macro|_ASM_IA64_PERCPU_H
mdefine_line|#define _ASM_IA64_PERCPU_H
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|THIS_CPU
mdefine_line|#define THIS_CPU(var)&t;(var)&t;/* use this to mark accesses to per-CPU variables... */
macro_line|#else /* !__ASSEMBLY__ */
macro_line|#include &lt;linux/threads.h&gt;
r_extern
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;(*(__typeof__(&amp;(var))) ((void *) &amp;(var) + __per_cpu_offset[cpu]))
DECL|macro|this_cpu
mdefine_line|#define this_cpu(var)&t;&t;(var)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PERCPU_H */
eof
