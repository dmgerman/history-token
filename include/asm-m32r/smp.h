macro_line|#ifndef _ASM_M32R_SMP_H
DECL|macro|_ASM_M32R_SMP_H
mdefine_line|#define _ASM_M32R_SMP_H
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
DECL|macro|PHYSID_ARRAY_SIZE
mdefine_line|#define PHYSID_ARRAY_SIZE       1
DECL|struct|physid_mask
r_struct
id|physid_mask
(brace
DECL|member|mask
r_int
r_int
id|mask
(braket
id|PHYSID_ARRAY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|physid_mask_t
r_typedef
r_struct
id|physid_mask
id|physid_mask_t
suffix:semicolon
DECL|macro|physid_set
mdefine_line|#define physid_set(physid, map)                 set_bit(physid, (map).mask)
DECL|macro|physid_clear
mdefine_line|#define physid_clear(physid, map)               clear_bit(physid, (map).mask)
DECL|macro|physid_isset
mdefine_line|#define physid_isset(physid, map)               test_bit(physid, (map).mask)
DECL|macro|physid_test_and_set
mdefine_line|#define physid_test_and_set(physid, map)        test_and_set_bit(physid, (map).mask)
DECL|macro|physids_and
mdefine_line|#define physids_and(dst, src1, src2)            bitmap_and((dst).mask, (src1).mask, (src2).mask, MAX_APICS)
DECL|macro|physids_or
mdefine_line|#define physids_or(dst, src1, src2)             bitmap_or((dst).mask, (src1).mask, (src2).mask, MAX_APICS)
DECL|macro|physids_clear
mdefine_line|#define physids_clear(map)                      bitmap_zero((map).mask, MAX_APICS)
DECL|macro|physids_complement
mdefine_line|#define physids_complement(dst, src)            bitmap_complement((dst).mask,(src).mask, MAX_APICS)
DECL|macro|physids_empty
mdefine_line|#define physids_empty(map)                      bitmap_empty((map).mask, MAX_APICS)
DECL|macro|physids_equal
mdefine_line|#define physids_equal(map1, map2)               bitmap_equal((map1).mask, (map2).mask, MAX_APICS)
DECL|macro|physids_weight
mdefine_line|#define physids_weight(map)                     bitmap_weight((map).mask, MAX_APICS)
DECL|macro|physids_shift_right
mdefine_line|#define physids_shift_right(d, s, n)            bitmap_shift_right((d).mask, (s).mask, n, MAX_APICS)
DECL|macro|physids_shift_left
mdefine_line|#define physids_shift_left(d, s, n)             bitmap_shift_left((d).mask, (s).mask, n, MAX_APICS)
DECL|macro|physids_coerce
mdefine_line|#define physids_coerce(map)                     ((map).mask[0])
DECL|macro|physids_promote
mdefine_line|#define physids_promote(physids)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;physid_mask_t __physid_mask = PHYSID_MASK_NONE;&t;&t;&bslash;&n;&t;&t;__physid_mask.mask[0] = physids;&t;&t;&t;&bslash;&n;&t;&t;__physid_mask;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|physid_mask_of_physid
mdefine_line|#define physid_mask_of_physid(physid)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;physid_mask_t __physid_mask = PHYSID_MASK_NONE;&t;&t;&bslash;&n;&t;&t;physid_set(physid, __physid_mask);&t;&t;&t;&bslash;&n;&t;&t;__physid_mask;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|PHYSID_MASK_ALL
mdefine_line|#define PHYSID_MASK_ALL         { {[0 ... PHYSID_ARRAY_SIZE-1] = ~0UL} }
DECL|macro|PHYSID_MASK_NONE
mdefine_line|#define PHYSID_MASK_NONE        { {[0 ... PHYSID_ARRAY_SIZE-1] = 0UL} }
r_extern
id|physid_mask_t
id|phys_cpu_present_map
suffix:semicolon
multiline_comment|/*&n; * Some lowlevel functions might want to know about&n; * the real CPU ID &lt;-&gt; CPU # mapping.&n; */
r_extern
r_volatile
r_int
id|physid_2_cpu
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_2_physid
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|physid_to_cpu
mdefine_line|#define physid_to_cpu(physid)&t;physid_2_cpu[physid]
DECL|macro|cpu_to_physid
mdefine_line|#define cpu_to_physid(cpu_id)&t;cpu_2_physid[cpu_id]
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
r_extern
id|cpumask_t
id|cpu_callout_map
suffix:semicolon
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map cpu_callout_map
DECL|function|hard_smp_processor_id
r_static
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_return
(paren
r_int
)paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|M32R_CPUID_PORTL
suffix:semicolon
)brace
DECL|function|cpu_logical_map
r_static
id|__inline__
r_int
id|cpu_logical_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu
suffix:semicolon
)brace
DECL|function|cpu_number_map
r_static
id|__inline__
r_int
id|cpu_number_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu
suffix:semicolon
)brace
DECL|function|num_booting_cpus
r_static
id|__inline__
r_int
r_int
id|num_booting_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|cpus_weight
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
)brace
r_extern
r_void
id|smp_send_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|send_IPI_mask_phys
c_func
(paren
id|cpumask_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif&t;/* not __ASSEMBLY__ */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID (0xff)&t;/* No processor magic marker */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;(15)&t;/* Schedule penalty */
multiline_comment|/*&n; * M32R-mp IPI&n; */
DECL|macro|RESCHEDULE_IPI
mdefine_line|#define RESCHEDULE_IPI&t;&t;(M32R_IRQ_IPI0-M32R_IRQ_IPI0)
DECL|macro|INVALIDATE_TLB_IPI
mdefine_line|#define INVALIDATE_TLB_IPI&t;(M32R_IRQ_IPI1-M32R_IRQ_IPI0)
DECL|macro|CALL_FUNCTION_IPI
mdefine_line|#define CALL_FUNCTION_IPI&t;(M32R_IRQ_IPI2-M32R_IRQ_IPI0)
DECL|macro|LOCAL_TIMER_IPI
mdefine_line|#define LOCAL_TIMER_IPI&t;&t;(M32R_IRQ_IPI3-M32R_IRQ_IPI0)
DECL|macro|INVALIDATE_CACHE_IPI
mdefine_line|#define INVALIDATE_CACHE_IPI&t;(M32R_IRQ_IPI4-M32R_IRQ_IPI0)
DECL|macro|CPU_BOOT_IPI
mdefine_line|#define CPU_BOOT_IPI&t;&t;(M32R_IRQ_IPI5-M32R_IRQ_IPI0)
DECL|macro|IPI_SHIFT
mdefine_line|#define IPI_SHIFT&t;(0)
DECL|macro|NR_IPIS
mdefine_line|#define NR_IPIS&t;&t;(8)
macro_line|#endif&t;/* CONFIG_SMP */
macro_line|#endif&t;/* _ASM_M32R_SMP_H */
eof
