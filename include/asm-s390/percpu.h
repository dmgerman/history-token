macro_line|#ifndef __ARCH_S390_PERCPU__
DECL|macro|__ARCH_S390_PERCPU__
mdefine_line|#define __ARCH_S390_PERCPU__
macro_line|#include &lt;asm-generic/percpu.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
multiline_comment|/*&n; * s390 uses the generic implementation for per cpu data, with the exception that&n; * the offset of the cpu local data area is cached in the cpu&squot;s lowcore memory&n; */
DECL|macro|__get_cpu_var
macro_line|#undef __get_cpu_var
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*RELOC_HIDE(&amp;per_cpu__##var, S390_lowcore.percpu_offset))
macro_line|#endif /* __ARCH_S390_PERCPU__ */
eof
