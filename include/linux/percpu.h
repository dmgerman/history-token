macro_line|#ifndef __LINUX_PERCPU_H
DECL|macro|__LINUX_PERCPU_H
mdefine_line|#define __LINUX_PERCPU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
DECL|macro|__per_cpu_data
mdefine_line|#define __per_cpu_data&t;__attribute__((section(&quot;.data.percpu&quot;)))
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#else
DECL|macro|__per_cpu_data
mdefine_line|#define __per_cpu_data
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;var
DECL|macro|this_cpu
mdefine_line|#define this_cpu(var)&t;&t;&t;&t;var
macro_line|#endif
macro_line|#endif /* __LINUX_PERCPU_H */
eof
