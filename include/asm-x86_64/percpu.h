macro_line|#ifndef _ASM_X8664_PERCPU_H_
DECL|macro|_ASM_X8664_PERCPU_H_
mdefine_line|#define _ASM_X8664_PERCPU_H_
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/pda.h&gt;
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
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.percpu&quot;))) __typeof__(type) name##__per_cpu
macro_line|#endif
multiline_comment|/* Completely hide the relocation from the compiler to avoid problems with &n;   the optimizer */
DECL|macro|__per_cpu
mdefine_line|#define __per_cpu(offset,base) &bslash;&n;&t;({ typeof(base) ptr = (void *)base; &bslash;&n;&t;   asm(&quot;addq %1,%0&quot; : &quot;=r&quot; (ptr) : &quot;r&quot; (offset), &quot;0&quot; (ptr)); ptr; })
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var,cpu) (*__per_cpu(__per_cpu_offset[cpu], &amp;var##__per_cpu)) 
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*__per_cpu(read_pda(cpudata_offset), &amp;var##__per_cpu))
macro_line|#else /* ! SMP */
multiline_comment|/* Can&squot;t define per-cpu variables in modules.  Sorry --RR */
macro_line|#ifndef MODULE
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) name##__per_cpu
macro_line|#endif
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;((void)cpu, var##__per_cpu)
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var)&t;&t;&t;var##__per_cpu
macro_line|#endif
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) name##__per_cpu
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
