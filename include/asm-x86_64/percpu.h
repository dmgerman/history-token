macro_line|#ifndef __ARCH_X8664_PERCPU__
DECL|macro|__ARCH_X8664_PERCPU__
mdefine_line|#define __ARCH_X8664_PERCPU__
macro_line|#include &lt;asm/pda.h&gt;
multiline_comment|/* var is in discarded region: offset to particular copy we want */
DECL|macro|this_cpu
mdefine_line|#define this_cpu(var)     (*RELOC_HIDE(&amp;var, read_pda(cpudata_offset)))
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu) (*RELOC_HIDE(&amp;var, per_cpu_pda[cpu]))
r_void
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ARCH_X8664_PERCPU__ */
eof
