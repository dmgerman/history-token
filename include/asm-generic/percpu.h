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
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) __typeof__(type) name##__per_cpu
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;var##__per_cpu, __per_cpu_offset[cpu]))
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) per_cpu(var, smp_processor_id())
DECL|function|percpu_modcopy
r_static
r_inline
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
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|memcpy
c_func
(paren
id|pcpudst
op_plus
id|__per_cpu_offset
(braket
id|i
)braket
comma
id|src
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#else /* ! SMP */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) name##__per_cpu
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;((void)cpu, var##__per_cpu)
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;var##__per_cpu
macro_line|#endif&t;/* SMP */
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) name##__per_cpu
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(var##__per_cpu)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(var##__per_cpu)
macro_line|#endif /* _ASM_GENERIC_PERCPU_H_ */
eof
