macro_line|#ifndef __ASM_GENERIC_CPUMASK_CONST_VALUE_H
DECL|macro|__ASM_GENERIC_CPUMASK_CONST_VALUE_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_CONST_VALUE_H
DECL|typedef|cpumask_const_t
r_typedef
r_const
id|cpumask_t
id|cpumask_const_t
suffix:semicolon
DECL|macro|mk_cpumask_const
mdefine_line|#define mk_cpumask_const(map)&t;&t;((cpumask_const_t)(map))
DECL|macro|cpu_isset_const
mdefine_line|#define cpu_isset_const(cpu, map)&t;cpu_isset(cpu, map)
DECL|macro|cpus_and_const
mdefine_line|#define cpus_and_const(dst,src1,src2)&t;cpus_and(dst, src1, src2)
DECL|macro|cpus_or_const
mdefine_line|#define cpus_or_const(dst,src1,src2)&t;cpus_or(dst, src1, src2)
DECL|macro|cpus_equal_const
mdefine_line|#define cpus_equal_const(map1, map2)&t;cpus_equal(map1, map2)
DECL|macro|cpus_empty_const
mdefine_line|#define cpus_empty_const(map)&t;&t;cpus_empty(map)
DECL|macro|cpus_copy_const
mdefine_line|#define cpus_copy_const(map1, map2)&t;do { map1 = (cpumask_t)map2; } while (0)
DECL|macro|cpus_weight_const
mdefine_line|#define cpus_weight_const(map)&t;&t;cpus_weight(map)
DECL|macro|first_cpu_const
mdefine_line|#define first_cpu_const(map)&t;&t;first_cpu(map)
DECL|macro|next_cpu_const
mdefine_line|#define next_cpu_const(cpu, map)&t;next_cpu(cpu, map)
multiline_comment|/* only ever use this for things that are _never_ used on large boxen */
DECL|macro|cpus_coerce_const
mdefine_line|#define cpus_coerce_const(map)&t;&t;cpus_coerce(map)
DECL|macro|any_online_cpu_const
mdefine_line|#define any_online_cpu_const(map)&t;any_online_cpu(map)
macro_line|#endif /* __ASM_GENERIC_CPUMASK_CONST_VALUE_H */
eof
