macro_line|#ifndef __LINUX_CPUMASK_H
DECL|macro|__LINUX_CPUMASK_H
mdefine_line|#define __LINUX_CPUMASK_H
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;asm/cpumask.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_possible_map
suffix:semicolon
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;cpus_weight(cpu_online_map)
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;&t;cpus_weight(cpu_possible_map)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;cpu_isset(cpu, cpu_online_map)
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;&t;cpu_isset(cpu, cpu_possible_map)
DECL|macro|for_each_cpu_mask
mdefine_line|#define for_each_cpu_mask(cpu, mask)&t;&t;&t;&t;&t;&bslash;&n;&t;for (cpu = first_cpu_const(mk_cpumask_const(mask));&t;&t;&bslash;&n;&t;&t;cpu &lt; NR_CPUS;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu = next_cpu_const(cpu, mk_cpumask_const(mask)))
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(cpu) for_each_cpu_mask(cpu, cpu_possible_map)
DECL|macro|for_each_online_cpu
mdefine_line|#define for_each_online_cpu(cpu) for_each_cpu_mask(cpu, cpu_online_map)
macro_line|#else
DECL|macro|cpu_online_map
mdefine_line|#define&t;cpu_online_map&t;&t;&t;cpumask_of_cpu(0)
DECL|macro|cpu_possible_map
mdefine_line|#define&t;cpu_possible_map&t;&t;cpumask_of_cpu(0)
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;1
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;&t;1
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;({ BUG_ON((cpu) != 0); 1; })
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;&t;({ BUG_ON((cpu) != 0); 1; })
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(cpu) for (cpu = 0; cpu &lt; 1; cpu++)
DECL|macro|for_each_online_cpu
mdefine_line|#define for_each_online_cpu(cpu) for (cpu = 0; cpu &lt; 1; cpu++)
macro_line|#endif
DECL|macro|cpumask_scnprintf
mdefine_line|#define cpumask_scnprintf(buf, buflen, map)&t;&t;&t;&t;&bslash;&n;&t;bitmap_scnprintf(buf, buflen, cpus_addr(map), NR_CPUS)
DECL|macro|cpumask_parse
mdefine_line|#define cpumask_parse(buf, buflen, map)&t;&t;&t;&t;&t;&bslash;&n;&t;bitmap_parse(buf, buflen, cpus_addr(map), NR_CPUS)
macro_line|#endif /* __LINUX_CPUMASK_H */
eof
