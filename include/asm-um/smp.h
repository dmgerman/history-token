macro_line|#ifndef __UM_SMP_H
DECL|macro|__UM_SMP_H
mdefine_line|#define __UM_SMP_H
macro_line|#ifdef CONFIG_SMP
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/bitops.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;linux/cpumask.h&quot;
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current_thread-&gt;cpu)
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(n) (n)
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(n) (n)
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;15 /* Pick a number, any number */
r_extern
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID -1
r_extern
r_int
id|ncpus
suffix:semicolon
DECL|function|smp_cpus_done
r_extern
r_inline
r_void
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|maxcpus
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif
eof
