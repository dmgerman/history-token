macro_line|#ifndef __UM_SMP_H
DECL|macro|__UM_SMP_H
mdefine_line|#define __UM_SMP_H
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/bitops.h&quot;
macro_line|#include &quot;asm/current.h&quot;
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current-&gt;thread_info-&gt;cpu)
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
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu) (cpu_online_map &amp; (1&lt;&lt;(cpu)))
r_extern
r_int
id|ncpus
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu) (cpu &lt; ncpus)
DECL|function|num_online_cpus
r_extern
r_inline
r_int
r_int
id|num_online_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|hweight32
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
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
