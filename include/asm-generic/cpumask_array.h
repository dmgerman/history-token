macro_line|#ifndef __ASM_GENERIC_CPUMASK_ARRAY_H
DECL|macro|__ASM_GENERIC_CPUMASK_ARRAY_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_ARRAY_H
multiline_comment|/*&n; * Array-based cpu bitmaps. An array of unsigned longs is used to contain&n; * the bitmap, and then contained in a structure so it may be passed by&n; * value.&n; */
DECL|macro|CPU_ARRAY_SIZE
mdefine_line|#define CPU_ARRAY_SIZE&t;&t;BITS_TO_LONGS(NR_CPUS)
DECL|macro|cpu_set
mdefine_line|#define cpu_set(cpu, map)&t;&t;set_bit(cpu, (map).mask)
DECL|macro|cpu_clear
mdefine_line|#define cpu_clear(cpu, map)&t;&t;clear_bit(cpu, (map).mask)
DECL|macro|cpu_isset
mdefine_line|#define cpu_isset(cpu, map)&t;&t;test_bit(cpu, (map).mask)
DECL|macro|cpu_test_and_set
mdefine_line|#define cpu_test_and_set(cpu, map)&t;test_and_set_bit(cpu, (map).mask)
DECL|macro|cpus_and
mdefine_line|#define cpus_and(dst,src1,src2)&t;bitmap_and((dst).mask,(src1).mask, (src2).mask, NR_CPUS)
DECL|macro|cpus_or
mdefine_line|#define cpus_or(dst,src1,src2)&t;bitmap_or((dst).mask, (src1).mask, (src2).mask, NR_CPUS)
DECL|macro|cpus_clear
mdefine_line|#define cpus_clear(map)&t;&t;bitmap_clear((map).mask, NR_CPUS)
DECL|macro|cpus_complement
mdefine_line|#define cpus_complement(map)&t;bitmap_complement((map).mask, NR_CPUS)
DECL|macro|cpus_equal
mdefine_line|#define cpus_equal(map1, map2)&t;bitmap_equal((map1).mask, (map2).mask, NR_CPUS)
DECL|macro|cpus_empty
mdefine_line|#define cpus_empty(map)&t;&t;bitmap_empty(map.mask, NR_CPUS)
DECL|macro|cpus_weight
mdefine_line|#define cpus_weight(map)&t;&t;bitmap_weight((map).mask, NR_CPUS)
DECL|macro|cpus_shift_right
mdefine_line|#define cpus_shift_right(d, s, n)&t;bitmap_shift_right((d).mask, (s).mask, n, NR_CPUS)
DECL|macro|cpus_shift_left
mdefine_line|#define cpus_shift_left(d, s, n)&t;bitmap_shift_left((d).mask, (s).mask, n, NR_CPUS)
DECL|macro|first_cpu
mdefine_line|#define first_cpu(map)&t;&t;find_first_bit((map).mask, NR_CPUS)
DECL|macro|next_cpu
mdefine_line|#define next_cpu(cpu, map)&t;find_next_bit((map).mask, NR_CPUS, cpu + 1)
multiline_comment|/* only ever use this for things that are _never_ used on large boxen */
DECL|macro|cpus_coerce
mdefine_line|#define cpus_coerce(map)&t;((map).mask[0])
DECL|macro|cpus_promote
mdefine_line|#define cpus_promote(map)&t;({ cpumask_t __cpu_mask = CPU_MASK_NONE;&bslash;&n;&t;&t;&t;&t;&t;__cpu_mask.mask[0] = map;&t;&bslash;&n;&t;&t;&t;&t;&t;__cpu_mask;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;})
DECL|macro|cpumask_of_cpu
mdefine_line|#define cpumask_of_cpu(cpu)&t;({ cpumask_t __cpu_mask = CPU_MASK_NONE;&bslash;&n;&t;&t;&t;&t;&t;cpu_set(cpu, __cpu_mask);&t;&bslash;&n;&t;&t;&t;&t;&t;__cpu_mask;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;})
DECL|macro|any_online_cpu
mdefine_line|#define any_online_cpu(map)&t;find_first_bit((map).mask, NR_CPUS)
multiline_comment|/*&n; * um, these need to be usable as static initializers&n; */
DECL|macro|CPU_MASK_ALL
mdefine_line|#define CPU_MASK_ALL&t;{ {[0 ... CPU_ARRAY_SIZE-1] = ~0UL} }
DECL|macro|CPU_MASK_NONE
mdefine_line|#define CPU_MASK_NONE&t;{ {[0 ... CPU_ARRAY_SIZE-1] =  0UL} }
macro_line|#endif /* __ASM_GENERIC_CPUMASK_ARRAY_H */
eof
