macro_line|#ifndef __LINUX_CPUMASK_H
DECL|macro|__LINUX_CPUMASK_H
mdefine_line|#define __LINUX_CPUMASK_H
macro_line|#include &lt;linux/threads.h&gt;
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
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;1
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;({ BUG_ON((cpu) != 0); 1; })
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;&t;({ BUG_ON((cpu) != 0); 1; })
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(cpu) for (cpu = 0; cpu &lt; 1; cpu++)
DECL|macro|for_each_online_cpu
mdefine_line|#define for_each_online_cpu(cpu) for (cpu = 0; cpu &lt; 1; cpu++)
macro_line|#endif
r_extern
r_int
id|__mask_snprintf_len
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
comma
r_const
r_int
r_int
op_star
id|maskp
comma
r_int
r_int
id|maskbytes
)paren
suffix:semicolon
DECL|macro|cpumask_snprintf
mdefine_line|#define cpumask_snprintf(buf, buflen, map)&t;&t;&t;&t;&bslash;&n;&t;__mask_snprintf_len(buf, buflen, cpus_addr(map), sizeof(map))
r_extern
r_int
id|__mask_parse_len
c_func
(paren
r_const
r_char
id|__user
op_star
id|ubuf
comma
r_int
r_int
id|ubuflen
comma
r_int
r_int
op_star
id|maskp
comma
r_int
r_int
id|maskbytes
)paren
suffix:semicolon
DECL|macro|cpumask_parse
mdefine_line|#define cpumask_parse(buf, buflen, map)&t;&t;&t;&t;&t;&bslash;&n;&t;__mask_parse_len(buf, buflen, cpus_addr(map), sizeof(map))
macro_line|#endif /* __LINUX_CPUMASK_H */
eof
