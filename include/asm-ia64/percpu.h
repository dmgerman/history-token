macro_line|#ifndef _ASM_IA64_PERCPU_H
DECL|macro|_ASM_IA64_PERCPU_H
mdefine_line|#define _ASM_IA64_PERCPU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|THIS_CPU
mdefine_line|#define THIS_CPU(var)&t;(var##__per_cpu)  /* use this to mark accesses to per-CPU variables... */
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
macro_line|#ifndef MODULE
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) name##__per_cpu
macro_line|#endif
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) name##__per_cpu
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;(var##__per_cpu)
macro_line|#ifdef CONFIG_SMP
DECL|macro|per_cpu
macro_line|# define per_cpu(var, cpu)&t;(*RELOC_HIDE(&amp;var##__per_cpu, __per_cpu_offset[cpu]))
macro_line|#else
DECL|macro|per_cpu
macro_line|# define per_cpu(var, cpu)&t;__get_cpu_var(var)
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PERCPU_H */
eof
