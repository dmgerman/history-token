macro_line|#ifndef __LINUX_CPUMASK_H
DECL|macro|__LINUX_CPUMASK_H
mdefine_line|#define __LINUX_CPUMASK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#if NR_CPUS &gt; BITS_PER_LONG &amp;&amp; NR_CPUS != 1
DECL|macro|CPU_ARRAY_SIZE
mdefine_line|#define CPU_ARRAY_SIZE&t;&t;BITS_TO_LONGS(NR_CPUS)
DECL|struct|cpumask
r_struct
id|cpumask
(brace
DECL|member|mask
r_int
r_int
id|mask
(braket
id|CPU_ARRAY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|cpumask_t
r_typedef
r_struct
id|cpumask
id|cpumask_t
suffix:semicolon
macro_line|#else
DECL|typedef|cpumask_t
r_typedef
r_int
r_int
id|cpumask_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
macro_line|#if NR_CPUS &gt; BITS_PER_LONG
macro_line|#include &lt;asm-generic/cpumask_array.h&gt;
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_arith.h&gt;
macro_line|#endif
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_up.h&gt;
macro_line|#endif
macro_line|#if NR_CPUS &lt;= 4*BITS_PER_LONG
macro_line|#include &lt;asm-generic/cpumask_const_value.h&gt;
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_const_reference.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;cpus_weight(cpu_online_map)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;cpu_isset(cpu, cpu_online_map)
macro_line|#else
DECL|macro|cpu_online_map
mdefine_line|#define&t;cpu_online_map&t;&t;&t;cpumask_of_cpu(0)
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;1
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;({ BUG_ON((cpu) != 0); 1; })
macro_line|#endif
DECL|function|next_online_cpu
r_static
r_inline
r_int
id|next_online_cpu
c_func
(paren
r_int
id|cpu
comma
id|cpumask_t
id|map
)paren
(brace
r_do
id|cpu
op_assign
id|next_cpu_const
c_func
(paren
id|cpu
comma
id|map
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cpu
OL
id|NR_CPUS
op_logical_and
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
r_return
id|cpu
suffix:semicolon
)brace
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(cpu, map)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (cpu = first_cpu_const(map);&t;&t;&t;&t;&bslash;&n;&t;&t;cpu &lt; NR_CPUS;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu = next_cpu_const(cpu,map))
DECL|macro|for_each_online_cpu
mdefine_line|#define for_each_online_cpu(cpu, map)&t;&t;&t;&t;&t;&bslash;&n;&t;for (cpu = first_cpu_const(map);&t;&t;&t;&t;&bslash;&n;&t;&t;cpu &lt; NR_CPUS;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu = next_online_cpu(cpu,map))
macro_line|#endif /* __LINUX_CPUMASK_H */
eof
