macro_line|#ifndef _ASM_GENERIC_PERCPU_H_
DECL|macro|_ASM_GENERIC_PERCPU_H_
mdefine_line|#define _ASM_GENERIC_PERCPU_H_
DECL|macro|__GENERIC_PER_CPU
mdefine_line|#define __GENERIC_PER_CPU
macro_line|#include &lt;linux/compiler.h&gt;
r_extern
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;var, __per_cpu_offset[cpu]))
DECL|macro|this_cpu
mdefine_line|#define this_cpu(var) per_cpu(var, smp_processor_id())
macro_line|#endif /* _ASM_GENERIC_PERCPU_H_ */
eof
