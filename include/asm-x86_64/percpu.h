macro_line|#ifndef _ASM_X8664_PERCPU_H_
DECL|macro|_ASM_X8664_PERCPU_H_
mdefine_line|#define _ASM_X8664_PERCPU_H_
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/* Same as asm-generic/percpu.h, except that we store the per cpu offset&n;   in the PDA. Longer term the PDA and every per cpu variable&n;   should be just put into a single section and referenced directly&n;   from %gs */
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/pda.h&gt;
DECL|macro|__per_cpu_offset
mdefine_line|#define __per_cpu_offset(cpu) (cpu_pda[cpu].data_offset)
DECL|macro|__my_cpu_offset
mdefine_line|#define __my_cpu_offset() read_pda(data_offset)
multiline_comment|/* Separate out the type, so (int[3], foo) works. */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) per_cpu__##name
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;per_cpu__##var, __per_cpu_offset(cpu)))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*RELOC_HIDE(&amp;per_cpu__##var, __my_cpu_offset()))
multiline_comment|/* A macro to avoid #include hell... */
DECL|macro|percpu_modcopy
mdefine_line|#define percpu_modcopy(pcpudst, src, size)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = 0; __i &lt; NR_CPUS; __i++)&t;&t;&t;&bslash;&n;&t;&t;if (cpu_possible(__i))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;memcpy((pcpudst)+__per_cpu_offset(__i),&t;&bslash;&n;&t;&t;&t;       (src), (size));&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* ! SMP */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) per_cpu__##name
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;((void)cpu, per_cpu__##var)
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;per_cpu__##var
macro_line|#endif&t;/* SMP */
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) per_cpu__##name
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(per_cpu__##var)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(per_cpu__##var)
r_extern
r_void
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_X8664_PERCPU_H_ */
eof
