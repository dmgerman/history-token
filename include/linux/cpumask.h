macro_line|#ifndef __LINUX_CPUMASK_H
DECL|macro|__LINUX_CPUMASK_H
mdefine_line|#define __LINUX_CPUMASK_H
multiline_comment|/*&n; * Cpumasks provide a bitmap suitable for representing the&n; * set of CPU&squot;s in a system, one bit position per CPU number.&n; *&n; * See detailed comments in the file linux/bitmap.h describing the&n; * data type on which these cpumasks are based.&n; *&n; * For details of cpumask_scnprintf() and cpumask_parse(),&n; * see bitmap_scnprintf() and bitmap_parse() in lib/bitmap.c.&n; *&n; * The available cpumask operations are:&n; *&n; * void cpu_set(cpu, mask)&t;&t;turn on bit &squot;cpu&squot; in mask&n; * void cpu_clear(cpu, mask)&t;&t;turn off bit &squot;cpu&squot; in mask&n; * void cpus_setall(mask)&t;&t;set all bits&n; * void cpus_clear(mask)&t;&t;clear all bits&n; * int cpu_isset(cpu, mask)&t;&t;true iff bit &squot;cpu&squot; set in mask&n; * int cpu_test_and_set(cpu, mask)&t;test and set bit &squot;cpu&squot; in mask&n; *&n; * void cpus_and(dst, src1, src2)&t;dst = src1 &amp; src2  [intersection]&n; * void cpus_or(dst, src1, src2)&t;dst = src1 | src2  [union]&n; * void cpus_xor(dst, src1, src2)&t;dst = src1 ^ src2&n; * void cpus_andnot(dst, src1, src2)&t;dst = src1 &amp; ~src2&n; * void cpus_complement(dst, src)&t;dst = ~src&n; *&n; * int cpus_equal(mask1, mask2)&t;&t;Does mask1 == mask2?&n; * int cpus_intersects(mask1, mask2)&t;Do mask1 and mask2 intersect?&n; * int cpus_subset(mask1, mask2)&t;Is mask1 a subset of mask2?&n; * int cpus_empty(mask)&t;&t;&t;Is mask empty (no bits sets)?&n; * int cpus_full(mask)&t;&t;&t;Is mask full (all bits sets)?&n; * int cpus_weight(mask)&t;&t;Hamming weigh - number of set bits&n; *&n; * void cpus_shift_right(dst, src, n)&t;Shift right&n; * void cpus_shift_left(dst, src, n)&t;Shift left&n; *&n; * int first_cpu(mask)&t;&t;&t;Number lowest set bit, or NR_CPUS&n; * int next_cpu(cpu, mask)&t;&t;Next cpu past &squot;cpu&squot;, or NR_CPUS&n; *&n; * cpumask_t cpumask_of_cpu(cpu)&t;Return cpumask with bit &squot;cpu&squot; set&n; * CPU_MASK_ALL&t;&t;&t;&t;Initializer - all bits set&n; * CPU_MASK_NONE&t;&t;&t;Initializer - no bits set&n; * unsigned long *cpus_addr(mask)&t;Array of unsigned long&squot;s in mask&n; *&n; * int cpumask_scnprintf(buf, len, mask) Format cpumask for printing&n; * int cpumask_parse(ubuf, ulen, mask)&t;Parse ascii string as cpumask&n; *&n; * for_each_cpu_mask(cpu, mask)&t;&t;for-loop cpu over mask&n; *&n; * int num_online_cpus()&t;&t;Number of online CPUs&n; * int num_possible_cpus()&t;&t;Number of all possible CPUs&n; * int num_present_cpus()&t;&t;Number of present CPUs&n; *&n; * int cpu_online(cpu)&t;&t;&t;Is some cpu online?&n; * int cpu_possible(cpu)&t;&t;Is some cpu possible?&n; * int cpu_present(cpu)&t;&t;&t;Is some cpu present (can schedule)?&n; *&n; * int any_online_cpu(mask)&t;&t;First online cpu in mask&n; *&n; * for_each_cpu(cpu)&t;&t;&t;for-loop cpu over cpu_possible_map&n; * for_each_online_cpu(cpu)&t;&t;for-loop cpu over cpu_online_map&n; * for_each_present_cpu(cpu)&t;&t;for-loop cpu over cpu_present_map&n; *&n; * Subtlety:&n; * 1) The &squot;type-checked&squot; form of cpu_isset() causes gcc (3.3.2, anyway)&n; *    to generate slightly worse code.  Note for example the additional&n; *    40 lines of assembly code compiling the &quot;for each possible cpu&quot;&n; *    loops buried in the disk_stat_read() macros calls when compiling&n; *    drivers/block/genhd.c (arch i386, CONFIG_SMP=y).  So use a simple&n; *    one-line #define for cpu_isset(), instead of wrapping an inline&n; *    inside a macro, the way we do the other calls.&n; */
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
DECL|typedef|cpumask_t
r_typedef
r_struct
(brace
id|DECLARE_BITMAP
c_func
(paren
id|bits
comma
id|NR_CPUS
)paren
suffix:semicolon
)brace
id|cpumask_t
suffix:semicolon
r_extern
id|cpumask_t
id|_unused_cpumask_arg_
suffix:semicolon
DECL|macro|cpu_set
mdefine_line|#define cpu_set(cpu, dst) __cpu_set((cpu), &amp;(dst))
DECL|function|__cpu_set
r_static
r_inline
r_void
id|__cpu_set
c_func
(paren
r_int
id|cpu
comma
r_volatile
id|cpumask_t
op_star
id|dstp
)paren
(brace
id|set_bit
c_func
(paren
id|cpu
comma
id|dstp-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|cpu_clear
mdefine_line|#define cpu_clear(cpu, dst) __cpu_clear((cpu), &amp;(dst))
DECL|function|__cpu_clear
r_static
r_inline
r_void
id|__cpu_clear
c_func
(paren
r_int
id|cpu
comma
r_volatile
id|cpumask_t
op_star
id|dstp
)paren
(brace
id|clear_bit
c_func
(paren
id|cpu
comma
id|dstp-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_setall
mdefine_line|#define cpus_setall(dst) __cpus_setall(&amp;(dst), NR_CPUS)
DECL|function|__cpus_setall
r_static
r_inline
r_void
id|__cpus_setall
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_fill
c_func
(paren
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_clear
mdefine_line|#define cpus_clear(dst) __cpus_clear(&amp;(dst), NR_CPUS)
DECL|function|__cpus_clear
r_static
r_inline
r_void
id|__cpus_clear
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_zero
c_func
(paren
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
multiline_comment|/* No static inline type checking - see Subtlety (1) above. */
DECL|macro|cpu_isset
mdefine_line|#define cpu_isset(cpu, cpumask) test_bit((cpu), (cpumask).bits)
DECL|macro|cpu_test_and_set
mdefine_line|#define cpu_test_and_set(cpu, cpumask) __cpu_test_and_set((cpu), &amp;(cpumask))
DECL|function|__cpu_test_and_set
r_static
r_inline
r_int
id|__cpu_test_and_set
c_func
(paren
r_int
id|cpu
comma
id|cpumask_t
op_star
id|addr
)paren
(brace
r_return
id|test_and_set_bit
c_func
(paren
id|cpu
comma
id|addr-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_and
mdefine_line|#define cpus_and(dst, src1, src2) __cpus_and(&amp;(dst), &amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_and
r_static
r_inline
r_void
id|__cpus_and
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_and
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_or
mdefine_line|#define cpus_or(dst, src1, src2) __cpus_or(&amp;(dst), &amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_or
r_static
r_inline
r_void
id|__cpus_or
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_or
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_xor
mdefine_line|#define cpus_xor(dst, src1, src2) __cpus_xor(&amp;(dst), &amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_xor
r_static
r_inline
r_void
id|__cpus_xor
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_xor
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_andnot
mdefine_line|#define cpus_andnot(dst, src1, src2) &bslash;&n;&t;&t;&t;&t;__cpus_andnot(&amp;(dst), &amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_andnot
r_static
r_inline
r_void
id|__cpus_andnot
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_andnot
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_complement
mdefine_line|#define cpus_complement(dst, src) __cpus_complement(&amp;(dst), &amp;(src), NR_CPUS)
DECL|function|__cpus_complement
r_static
r_inline
r_void
id|__cpus_complement
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_complement
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_equal
mdefine_line|#define cpus_equal(src1, src2) __cpus_equal(&amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_equal
r_static
r_inline
r_int
id|__cpus_equal
c_func
(paren
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_equal
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_intersects
mdefine_line|#define cpus_intersects(src1, src2) __cpus_intersects(&amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_intersects
r_static
r_inline
r_int
id|__cpus_intersects
c_func
(paren
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_intersects
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_subset
mdefine_line|#define cpus_subset(src1, src2) __cpus_subset(&amp;(src1), &amp;(src2), NR_CPUS)
DECL|function|__cpus_subset
r_static
r_inline
r_int
id|__cpus_subset
c_func
(paren
r_const
id|cpumask_t
op_star
id|src1p
comma
r_const
id|cpumask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_subset
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_empty
mdefine_line|#define cpus_empty(src) __cpus_empty(&amp;(src), NR_CPUS)
DECL|function|__cpus_empty
r_static
r_inline
r_int
id|__cpus_empty
c_func
(paren
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_empty
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_full
mdefine_line|#define cpus_full(cpumask) __cpus_full(&amp;(cpumask), NR_CPUS)
DECL|function|__cpus_full
r_static
r_inline
r_int
id|__cpus_full
c_func
(paren
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_full
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_weight
mdefine_line|#define cpus_weight(cpumask) __cpus_weight(&amp;(cpumask), NR_CPUS)
DECL|function|__cpus_weight
r_static
r_inline
r_int
id|__cpus_weight
c_func
(paren
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_weight
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_shift_right
mdefine_line|#define cpus_shift_right(dst, src, n) &bslash;&n;&t;&t;&t;__cpus_shift_right(&amp;(dst), &amp;(src), (n), NR_CPUS)
DECL|function|__cpus_shift_right
r_static
r_inline
r_void
id|__cpus_shift_right
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|n
comma
r_int
id|nbits
)paren
(brace
id|bitmap_shift_right
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|n
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpus_shift_left
mdefine_line|#define cpus_shift_left(dst, src, n) &bslash;&n;&t;&t;&t;__cpus_shift_left(&amp;(dst), &amp;(src), (n), NR_CPUS)
DECL|function|__cpus_shift_left
r_static
r_inline
r_void
id|__cpus_shift_left
c_func
(paren
id|cpumask_t
op_star
id|dstp
comma
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|n
comma
r_int
id|nbits
)paren
(brace
id|bitmap_shift_left
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|n
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|first_cpu
mdefine_line|#define first_cpu(src) __first_cpu(&amp;(src), NR_CPUS)
DECL|function|__first_cpu
r_static
r_inline
r_int
id|__first_cpu
c_func
(paren
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|find_first_bit
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|next_cpu
mdefine_line|#define next_cpu(n, src) __next_cpu((n), &amp;(src), NR_CPUS)
DECL|function|__next_cpu
r_static
r_inline
r_int
id|__next_cpu
c_func
(paren
r_int
id|n
comma
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|find_next_bit
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
comma
id|n
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|cpumask_of_cpu
mdefine_line|#define cpumask_of_cpu(cpu)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;typeof(_unused_cpumask_arg_) m;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(m) == sizeof(unsigned long)) {&t;&t;&t;&bslash;&n;&t;&t;m.bits[0] = 1UL&lt;&lt;(cpu);&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpus_clear(m);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_set((cpu), m);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;m;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|CPU_MASK_LAST_WORD
mdefine_line|#define CPU_MASK_LAST_WORD BITMAP_LAST_WORD_MASK(NR_CPUS)
macro_line|#if NR_CPUS &lt;= BITS_PER_LONG
DECL|macro|CPU_MASK_ALL
mdefine_line|#define CPU_MASK_ALL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((cpumask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[BITS_TO_LONGS(NR_CPUS)-1] = CPU_MASK_LAST_WORD&t;&t;&t;&bslash;&n;} })
macro_line|#else
DECL|macro|CPU_MASK_ALL
mdefine_line|#define CPU_MASK_ALL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((cpumask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[0 ... BITS_TO_LONGS(NR_CPUS)-2] = ~0UL,&t;&t;&t;&bslash;&n;&t;[BITS_TO_LONGS(NR_CPUS)-1] = CPU_MASK_LAST_WORD&t;&t;&t;&bslash;&n;} })
macro_line|#endif
DECL|macro|CPU_MASK_NONE
mdefine_line|#define CPU_MASK_NONE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((cpumask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[0 ... BITS_TO_LONGS(NR_CPUS)-1] =  0UL&t;&t;&t;&t;&bslash;&n;} })
DECL|macro|CPU_MASK_CPU0
mdefine_line|#define CPU_MASK_CPU0&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((cpumask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[0] =  1UL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} })
DECL|macro|cpus_addr
mdefine_line|#define cpus_addr(src) ((src).bits)
DECL|macro|cpumask_scnprintf
mdefine_line|#define cpumask_scnprintf(buf, len, src) &bslash;&n;&t;&t;&t;__cpumask_scnprintf((buf), (len), &amp;(src), NR_CPUS)
DECL|function|__cpumask_scnprintf
r_static
r_inline
r_int
id|__cpumask_scnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_const
id|cpumask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_scnprintf
c_func
(paren
id|buf
comma
id|len
comma
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|cpumask_parse
mdefine_line|#define cpumask_parse(ubuf, ulen, src) &bslash;&n;&t;&t;&t;__cpumask_parse((ubuf), (ulen), &amp;(src), NR_CPUS)
DECL|function|__cpumask_parse
r_static
r_inline
r_int
id|__cpumask_parse
c_func
(paren
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|len
comma
id|cpumask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_parse
c_func
(paren
id|buf
comma
id|len
comma
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
macro_line|#if NR_CPUS &gt; 1
DECL|macro|for_each_cpu_mask
mdefine_line|#define for_each_cpu_mask(cpu, mask)&t;&t;&bslash;&n;&t;for ((cpu) = first_cpu(mask);&t;&t;&bslash;&n;&t;&t;(cpu) &lt; NR_CPUS;&t;&t;&bslash;&n;&t;&t;(cpu) = next_cpu((cpu), (mask)))
macro_line|#else /* NR_CPUS == 1 */
DECL|macro|for_each_cpu_mask
mdefine_line|#define for_each_cpu_mask(cpu, mask) for ((cpu) = 0; (cpu) &lt; 1; (cpu)++)
macro_line|#endif /* NR_CPUS */
multiline_comment|/*&n; * The following particular system cpumasks and operations manage&n; * possible, present and online cpus.  Each of them is a fixed size&n; * bitmap of size NR_CPUS.&n; *&n; *  #ifdef CONFIG_HOTPLUG_CPU&n; *     cpu_possible_map - all NR_CPUS bits set&n; *     cpu_present_map  - has bit &squot;cpu&squot; set iff cpu is populated&n; *     cpu_online_map   - has bit &squot;cpu&squot; set iff cpu available to scheduler&n; *  #else&n; *     cpu_possible_map - has bit &squot;cpu&squot; set iff cpu is populated&n; *     cpu_present_map  - copy of cpu_possible_map&n; *     cpu_online_map   - has bit &squot;cpu&squot; set iff cpu available to scheduler&n; *  #endif&n; *&n; *  In either case, NR_CPUS is fixed at compile time, as the static&n; *  size of these bitmaps.  The cpu_possible_map is fixed at boot&n; *  time, as the set of CPU id&squot;s that it is possible might ever&n; *  be plugged in at anytime during the life of that system boot.&n; *  The cpu_present_map is dynamic(*), representing which CPUs&n; *  are currently plugged in.  And cpu_online_map is the dynamic&n; *  subset of cpu_present_map, indicating those CPUs available&n; *  for scheduling.&n; *&n; *  If HOTPLUG is enabled, then cpu_possible_map is forced to have&n; *  all NR_CPUS bits set, otherwise it is just the set of CPUs that&n; *  ACPI reports present at boot.&n; *&n; *  If HOTPLUG is enabled, then cpu_present_map varies dynamically,&n; *  depending on what ACPI reports as currently plugged in, otherwise&n; *  cpu_present_map is just a copy of cpu_possible_map.&n; *&n; *  (*) Well, cpu_present_map is dynamic in the hotplug case.  If not&n; *      hotplug, it&squot;s a copy of cpu_possible_map, hence fixed at boot.&n; *&n; * Subtleties:&n; * 1) UP arch&squot;s (NR_CPUS == 1, CONFIG_SMP not defined) hardcode&n; *    assumption that their single CPU is online.  The UP&n; *    cpu_{online,possible,present}_maps are placebos.  Changing them&n; *    will have no useful affect on the following num_*_cpus()&n; *    and cpu_*() macros in the UP case.  This ugliness is a UP&n; *    optimization - don&squot;t waste any instructions or memory references&n; *    asking if you&squot;re online or how many CPUs there are if there is&n; *    only one CPU.&n; * 2) Most SMP arch&squot;s #define some of these maps to be some&n; *    other map specific to that arch.  Therefore, the following&n; *    must be #define macros, not inlines.  To see why, examine&n; *    the assembly code produced by the following.  Note that&n; *    set1() writes phys_x_map, but set2() writes x_map:&n; *        int x_map, phys_x_map;&n; *        #define set1(a) x_map = a&n; *        inline void set2(int a) { x_map = a; }&n; *        #define x_map phys_x_map&n; *        main(){ set1(3); set2(5); }&n; */
r_extern
id|cpumask_t
id|cpu_possible_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_present_map
suffix:semicolon
macro_line|#if NR_CPUS &gt; 1
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;cpus_weight(cpu_online_map)
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;cpus_weight(cpu_possible_map)
DECL|macro|num_present_cpus
mdefine_line|#define num_present_cpus()&t;cpus_weight(cpu_present_map)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;cpu_isset((cpu), cpu_online_map)
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;cpu_isset((cpu), cpu_possible_map)
DECL|macro|cpu_present
mdefine_line|#define cpu_present(cpu)&t;cpu_isset((cpu), cpu_present_map)
macro_line|#else
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;1
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;1
DECL|macro|num_present_cpus
mdefine_line|#define num_present_cpus()&t;1
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;((cpu) == 0)
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;((cpu) == 0)
DECL|macro|cpu_present
mdefine_line|#define cpu_present(cpu)&t;((cpu) == 0)
macro_line|#endif
DECL|macro|any_online_cpu
mdefine_line|#define any_online_cpu(mask)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int cpu;&t;&t;&t;&t;&bslash;&n;&t;for_each_cpu_mask(cpu, (mask))&t;&t;&bslash;&n;&t;&t;if (cpu_online(cpu))&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&bslash;&n;&t;cpu;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(cpu)&t;  for_each_cpu_mask((cpu), cpu_possible_map)
DECL|macro|for_each_online_cpu
mdefine_line|#define for_each_online_cpu(cpu)  for_each_cpu_mask((cpu), cpu_online_map)
DECL|macro|for_each_present_cpu
mdefine_line|#define for_each_present_cpu(cpu) for_each_cpu_mask((cpu), cpu_present_map)
macro_line|#endif /* __LINUX_CPUMASK_H */
eof
