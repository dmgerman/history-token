macro_line|#ifndef __ASM_GENERIC_CPUMASK_UP_H
DECL|macro|__ASM_GENERIC_CPUMASK_UP_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_UP_H
DECL|macro|cpus_coerce
mdefine_line|#define cpus_coerce(map)&t;(map)
DECL|macro|cpu_set
mdefine_line|#define cpu_set(cpu, map)&t;&t;do { cpus_coerce(map) = 1UL; } while (0)
DECL|macro|cpu_clear
mdefine_line|#define cpu_clear(cpu, map)&t;&t;do { cpus_coerce(map) = 0UL; } while (0)
DECL|macro|cpu_isset
mdefine_line|#define cpu_isset(cpu, map)&t;&t;(cpus_coerce(map) != 0UL)
DECL|macro|cpu_test_and_set
mdefine_line|#define cpu_test_and_set(cpu, map)&t;test_and_set_bit(0, (map).mask)
DECL|macro|cpus_and
mdefine_line|#define cpus_and(dst, src1, src2)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (cpus_coerce(src1) &amp;&amp; cpus_coerce(src2))&t;&t;&bslash;&n;&t;&t;&t;cpus_coerce(dst) = 1UL;&t;&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpus_coerce(dst) = 0UL;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|cpus_or
mdefine_line|#define cpus_or(dst, src1, src2)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (cpus_coerce(src1) || cpus_coerce(src2))&t;&t;&bslash;&n;&t;&t;&t;cpus_coerce(dst) = 1UL;&t;&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpus_coerce(dst) = 0UL;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|cpus_clear
mdefine_line|#define cpus_clear(map)&t;&t;&t;do { cpus_coerce(map) = 0UL; } while (0)
DECL|macro|cpus_complement
mdefine_line|#define cpus_complement(map)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpus_coerce(map) = !cpus_coerce(map);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|cpus_equal
mdefine_line|#define cpus_equal(map1, map2)&t;&t;(cpus_coerce(map1) == cpus_coerce(map2))
DECL|macro|cpus_empty
mdefine_line|#define cpus_empty(map)&t;&t;&t;(cpus_coerce(map) == 0UL)
DECL|macro|cpus_weight
mdefine_line|#define cpus_weight(map)&t;&t;(cpus_coerce(map) ? 1UL : 0UL)
DECL|macro|cpus_shift_right
mdefine_line|#define cpus_shift_right(d, s, n)&t;do { cpus_coerce(d) = 0UL; } while (0)
DECL|macro|cpus_shift_left
mdefine_line|#define cpus_shift_left(d, s, n)&t;do { cpus_coerce(d) = 0UL; } while (0)
DECL|macro|first_cpu
mdefine_line|#define first_cpu(map)&t;&t;&t;(cpus_coerce(map) ? 0 : 1)
DECL|macro|next_cpu
mdefine_line|#define next_cpu(cpu, map)&t;&t;1
multiline_comment|/* only ever use this for things that are _never_ used on large boxen */
DECL|macro|cpus_promote
mdefine_line|#define cpus_promote(map)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpumask_t __tmp__;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpus_coerce(__tmp__) = map;&t;&t;&t;&t;&bslash;&n;&t;&t;__tmp__;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|cpumask_of_cpu
mdefine_line|#define cpumask_of_cpu(cpu)&t;&t;cpus_promote(1)
DECL|macro|any_online_cpu
mdefine_line|#define any_online_cpu(map)&t;&t;(cpus_coerce(map) ? 0 : 1)
multiline_comment|/*&n; * um, these need to be usable as static initializers&n; */
DECL|macro|CPU_MASK_ALL
mdefine_line|#define CPU_MASK_ALL&t;1UL
DECL|macro|CPU_MASK_NONE
mdefine_line|#define CPU_MASK_NONE&t;0UL
macro_line|#endif /* __ASM_GENERIC_CPUMASK_UP_H */
eof
