macro_line|#ifndef _ASM_IA64_PERCPU_H
DECL|macro|_ASM_IA64_PERCPU_H
mdefine_line|#define _ASM_IA64_PERCPU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|PERCPU_ENOUGH_ROOM
mdefine_line|#define PERCPU_ENOUGH_ROOM PERCPU_PAGE_SIZE
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
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) name##__per_cpu
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) name##__per_cpu
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;(var##__per_cpu)
macro_line|#ifdef CONFIG_SMP
DECL|macro|per_cpu
macro_line|# define per_cpu(var, cpu)&t;(*RELOC_HIDE(&amp;var##__per_cpu, __per_cpu_offset[cpu]))
r_extern
r_void
id|percpu_modcopy
c_func
(paren
r_void
op_star
id|pcpudst
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|size
)paren
suffix:semicolon
macro_line|#else
DECL|macro|per_cpu
macro_line|# define per_cpu(var, cpu)&t;((void)cpu, __get_cpu_var(var))
macro_line|#endif
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(var##__per_cpu)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(var##__per_cpu)
r_extern
r_void
id|setup_per_cpu_areas
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PERCPU_H */
eof
