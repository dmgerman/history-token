macro_line|#ifndef __ASM_GENERIC_CPUMASK_CONST_REFERENCE_H
DECL|macro|__ASM_GENERIC_CPUMASK_CONST_REFERENCE_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_CONST_REFERENCE_H
DECL|struct|cpumask_ref
r_struct
id|cpumask_ref
(brace
DECL|member|val
r_const
id|cpumask_t
op_star
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|cpumask_const_t
r_typedef
r_const
r_struct
id|cpumask_ref
id|cpumask_const_t
suffix:semicolon
DECL|macro|mk_cpumask_const
mdefine_line|#define mk_cpumask_const(map)&t;&t;((cpumask_const_t){ &amp;(map) })
DECL|macro|cpu_isset_const
mdefine_line|#define cpu_isset_const(cpu, map)&t;cpu_isset(cpu, *(map).val)
DECL|macro|cpus_and_const
mdefine_line|#define cpus_and_const(dst,src1,src2)&t;cpus_and(dst,*(src1).val,*(src2).val)
DECL|macro|cpus_or_const
mdefine_line|#define cpus_or_const(dst,src1,src2)&t;cpus_or(dst,*(src1).val,*(src2).val)
DECL|macro|cpus_equal_const
mdefine_line|#define cpus_equal_const(map1, map2)&t;cpus_equal(*(map1).val, *(map2).val)
DECL|macro|cpus_copy_const
mdefine_line|#define cpus_copy_const(map1, map2)&t;bitmap_copy((map1).mask, (map2).val-&gt;mask, NR_CPUS)
DECL|macro|cpus_empty_const
mdefine_line|#define cpus_empty_const(map)&t;&t;cpus_empty(*(map).val)
DECL|macro|cpus_weight_const
mdefine_line|#define cpus_weight_const(map)&t;&t;cpus_weight(*(map).val)
DECL|macro|first_cpu_const
mdefine_line|#define first_cpu_const(map)&t;&t;first_cpu(*(map).val)
DECL|macro|next_cpu_const
mdefine_line|#define next_cpu_const(cpu, map)&t;next_cpu(cpu, *(map).val)
multiline_comment|/* only ever use this for things that are _never_ used on large boxen */
DECL|macro|cpus_coerce_const
mdefine_line|#define cpus_coerce_const(map)&t;&t;cpus_coerce(*(map).val)
DECL|macro|any_online_cpu_const
mdefine_line|#define any_online_cpu_const(map)&t;any_online_cpu(*(map).val)
macro_line|#endif /* __ASM_GENERIC_CPUMASK_CONST_REFERENCE_H */
eof
