macro_line|#ifndef __ARCH_SPARC64_PERCPU__
DECL|macro|__ARCH_SPARC64_PERCPU__
mdefine_line|#define __ARCH_SPARC64_PERCPU__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__per_cpu_base
suffix:semicolon
r_extern
r_int
r_int
id|__per_cpu_shift
suffix:semicolon
DECL|macro|__per_cpu_offset
mdefine_line|#define __per_cpu_offset(__cpu) &bslash;&n;&t;(__per_cpu_base + ((unsigned long)(__cpu) &lt;&lt; __per_cpu_shift))
multiline_comment|/* Separate out the type, so (int[3], foo) works. */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) per_cpu__##name
r_register
r_int
r_int
id|__local_per_cpu_offset
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;per_cpu__##var, __per_cpu_offset(cpu)))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*RELOC_HIDE(&amp;per_cpu__##var, __local_per_cpu_offset))
multiline_comment|/* A macro to avoid #include hell... */
DECL|macro|percpu_modcopy
mdefine_line|#define percpu_modcopy(pcpudst, src, size)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = 0; __i &lt; NR_CPUS; __i++)&t;&t;&t;&bslash;&n;&t;&t;if (cpu_possible(__i))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;memcpy((pcpudst)+__per_cpu_offset(__i),&t;&bslash;&n;&t;&t;&t;       (src), (size));&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* ! SMP */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) per_cpu__##name
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;(*((void)cpu, &amp;per_cpu__##var))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;per_cpu__##var
macro_line|#endif&t;/* SMP */
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) per_cpu__##name
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(per_cpu__##var)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(per_cpu__##var)
macro_line|#endif /* __ARCH_SPARC64_PERCPU__ */
eof
