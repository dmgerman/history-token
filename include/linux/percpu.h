macro_line|#ifndef __LINUX_PERCPU_H
DECL|macro|__LINUX_PERCPU_H
mdefine_line|#define __LINUX_PERCPU_H
macro_line|#include &lt;linux/spinlock.h&gt; /* For preempt_disable() */
macro_line|#include &lt;asm/percpu.h&gt;
DECL|macro|get_cpu_var
mdefine_line|#define get_cpu_var(var) ({ preempt_disable(); __get_cpu_var(var); })
DECL|macro|put_cpu_var
mdefine_line|#define put_cpu_var(var) preempt_enable()
macro_line|#endif /* __LINUX_PERCPU_H */
eof
