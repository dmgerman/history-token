macro_line|#ifndef __ASM_GENERIC_CPUMASK_ARITH_H
DECL|macro|__ASM_GENERIC_CPUMASK_ARITH_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_ARITH_H
multiline_comment|/*&n; * Arithmetic type -based cpu bitmaps. A single unsigned long is used&n; * to contain the whole cpu bitmap.&n; */
DECL|macro|cpu_set
mdefine_line|#define cpu_set(cpu, map)&t;&t;set_bit(cpu, &amp;(map))
DECL|macro|cpu_clear
mdefine_line|#define cpu_clear(cpu, map)&t;&t;clear_bit(cpu, &amp;(map))
DECL|macro|cpu_isset
mdefine_line|#define cpu_isset(cpu, map)&t;&t;test_bit(cpu, &amp;(map))
DECL|macro|cpu_test_and_set
mdefine_line|#define cpu_test_and_set(cpu, map)&t;test_and_set_bit(cpu, &amp;(map))
DECL|macro|cpus_and
mdefine_line|#define cpus_and(dst,src1,src2)&t;&t;do { dst = (src1) &amp; (src2); } while (0)
DECL|macro|cpus_or
mdefine_line|#define cpus_or(dst,src1,src2)&t;&t;do { dst = (src1) | (src2); } while (0)
DECL|macro|cpus_clear
mdefine_line|#define cpus_clear(map)&t;&t;&t;do { map = 0; } while (0)
DECL|macro|cpus_complement
mdefine_line|#define cpus_complement(map)&t;&t;do { map = ~(map); } while (0)
DECL|macro|cpus_equal
mdefine_line|#define cpus_equal(map1, map2)&t;&t;((map1) == (map2))
DECL|macro|cpus_empty
mdefine_line|#define cpus_empty(map)&t;&t;&t;((map) == 0)
macro_line|#if BITS_PER_LONG == 32
DECL|macro|cpus_weight
mdefine_line|#define cpus_weight(map)&t;&t;hweight32(map)
macro_line|#elif BITS_PER_LONG == 64
DECL|macro|cpus_weight
mdefine_line|#define cpus_weight(map)&t;&t;hweight64(map)
macro_line|#endif
DECL|macro|cpus_shift_right
mdefine_line|#define cpus_shift_right(dst, src, n)&t;do { dst = (src) &gt;&gt; (n); } while (0)
DECL|macro|cpus_shift_left
mdefine_line|#define cpus_shift_left(dst, src, n)&t;do { dst = (src) &lt;&lt; (n); } while (0)
DECL|macro|any_online_cpu
mdefine_line|#define any_online_cpu(map)&t;&t;({ (map) ? first_cpu(map) : NR_CPUS; })
DECL|macro|CPU_MASK_ALL
mdefine_line|#define CPU_MASK_ALL&t;(~((cpumask_t)0) &gt;&gt; (8*sizeof(cpumask_t) - NR_CPUS))
DECL|macro|CPU_MASK_NONE
mdefine_line|#define CPU_MASK_NONE&t;((cpumask_t)0)
multiline_comment|/* only ever use this for things that are _never_ used on large boxen */
DECL|macro|cpus_coerce
mdefine_line|#define cpus_coerce(map)&t;&t;((unsigned long)(map))
DECL|macro|cpus_promote
mdefine_line|#define cpus_promote(map)&t;&t;({ map; })
DECL|macro|cpumask_of_cpu
mdefine_line|#define cpumask_of_cpu(cpu)&t;&t;({ ((cpumask_t)1) &lt;&lt; (cpu); })
DECL|macro|first_cpu
mdefine_line|#define first_cpu(map)&t;&t;&t;__ffs(map)
DECL|macro|next_cpu
mdefine_line|#define next_cpu(cpu, map)&t;&t;find_next_bit(&amp;(map), NR_CPUS, cpu + 1)
macro_line|#endif /* __ASM_GENERIC_CPUMASK_ARITH_H */
eof
