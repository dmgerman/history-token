macro_line|#ifndef _ASM_GENERIC_PERCPU_H_
DECL|macro|_ASM_GENERIC_PERCPU_H_
mdefine_line|#define _ASM_GENERIC_PERCPU_H_
macro_line|#include &lt;linux/compiler.h&gt;
DECL|macro|__GENERIC_PER_CPU
mdefine_line|#define __GENERIC_PER_CPU
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Separate out the type, so (int[3], foo) works. */
macro_line|#ifndef MODULE
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) name##__per_cpu
macro_line|#endif
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;var##__per_cpu, __per_cpu_offset[cpu]))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) per_cpu(var, smp_processor_id())
macro_line|#else /* ! SMP */
multiline_comment|/* Can&squot;t define per-cpu variables in modules.  Sorry --RR */
macro_line|#ifndef MODULE
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) name##__per_cpu
macro_line|#endif
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;var##__per_cpu
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;var##__per_cpu
macro_line|#endif
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) name##__per_cpu
macro_line|#endif /* _ASM_GENERIC_PERCPU_H_ */
eof
