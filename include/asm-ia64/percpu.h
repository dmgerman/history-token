macro_line|#ifndef _ASM_IA64_PERCPU_H
DECL|macro|_ASM_IA64_PERCPU_H
mdefine_line|#define _ASM_IA64_PERCPU_H
multiline_comment|/*&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|PERCPU_ENOUGH_ROOM
mdefine_line|#define PERCPU_ENOUGH_ROOM PERCPU_PAGE_SIZE
macro_line|#ifdef __ASSEMBLY__
DECL|macro|THIS_CPU
macro_line|# define THIS_CPU(var)&t;(per_cpu__##var)  /* use this to mark accesses to per-CPU variables... */
macro_line|#else /* !__ASSEMBLY__ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#ifdef HAVE_MODEL_SMALL_ATTRIBUTE
DECL|macro|__SMALL_ADDR_AREA
macro_line|# define __SMALL_ADDR_AREA&t;__attribute__((__model__ (__small__)))
macro_line|#else
DECL|macro|__SMALL_ADDR_AREA
macro_line|# define __SMALL_ADDR_AREA
macro_line|#endif
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name)&t;&t;&t;&t;&bslash;&n;&t;extern __SMALL_ADDR_AREA __typeof__(type) per_cpu__##name
multiline_comment|/* Separate out the type, so (int[3], foo) works. */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name)&t;&t;&t;&t;&bslash;&n;&t;__attribute__((__section__(&quot;.data.percpu&quot;)))&t;&t;&bslash;&n;&t;__SMALL_ADDR_AREA __typeof__(type) per_cpu__##name
multiline_comment|/*&n; * Pretty much a literal copy of asm-generic/percpu.h, except that percpu_modcopy() is an&n; * external routine, to avoid include-hell.&n; */
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Equal to __per_cpu_offset[smp_processor_id()], but faster to access: */
id|DECLARE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|local_per_cpu_offset
)paren
suffix:semicolon
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)  (*RELOC_HIDE(&amp;per_cpu__##var, __per_cpu_offset[cpu]))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*RELOC_HIDE(&amp;per_cpu__##var, __ia64_per_cpu_var(local_per_cpu_offset)))
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
r_extern
r_void
id|setup_per_cpu_areas
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* ! SMP */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;(*((void)cpu, &amp;per_cpu__##var))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;per_cpu__##var
macro_line|#endif&t;/* SMP */
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var)&t;&t;EXPORT_SYMBOL(per_cpu__##var)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var)&t;&t;EXPORT_SYMBOL_GPL(per_cpu__##var)
multiline_comment|/*&n; * Be extremely careful when taking the address of this variable!  Due to virtual&n; * remapping, it is different from the canonical address returned by __get_cpu_var(var)!&n; * On the positive side, using __ia64_per_cpu_var() instead of __get_cpu_var() is slightly&n; * more efficient.&n; */
DECL|macro|__ia64_per_cpu_var
mdefine_line|#define __ia64_per_cpu_var(var)&t;(per_cpu__##var)
r_extern
r_void
op_star
id|per_cpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PERCPU_H */
eof
