macro_line|#ifndef _ASM_M32R_MMU_CONTEXT_H
DECL|macro|_ASM_M32R_MMU_CONTEXT_H
mdefine_line|#define _ASM_M32R_MMU_CONTEXT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
DECL|macro|MMU_CONTEXT_ASID_MASK
mdefine_line|#define MMU_CONTEXT_ASID_MASK      (0x000000FF)
DECL|macro|MMU_CONTEXT_VERSION_MASK
mdefine_line|#define MMU_CONTEXT_VERSION_MASK   (0xFFFFFF00)
DECL|macro|MMU_CONTEXT_FIRST_VERSION
mdefine_line|#define MMU_CONTEXT_FIRST_VERSION  (0x00000100)
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT                 (0x00000000)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Cache of MMU context last used.&n; */
macro_line|#ifndef CONFIG_SMP
r_extern
r_int
r_int
id|mmu_context_cache_dat
suffix:semicolon
DECL|macro|mmu_context_cache
mdefine_line|#define mmu_context_cache&t;mmu_context_cache_dat
DECL|macro|mm_context
mdefine_line|#define mm_context(mm)&t;&t;mm-&gt;context
macro_line|#else /* not CONFIG_SMP */
r_extern
r_int
r_int
id|mmu_context_cache_dat
(braket
)braket
suffix:semicolon
DECL|macro|mmu_context_cache
mdefine_line|#define mmu_context_cache&t;mmu_context_cache_dat[smp_processor_id()]
DECL|macro|mm_context
mdefine_line|#define mm_context(mm)&t;&t;mm-&gt;context[smp_processor_id()]
macro_line|#endif /* not CONFIG_SMP */
DECL|macro|set_tlb_tag
mdefine_line|#define set_tlb_tag(entry, tag)&t;&t;(*entry = (tag &amp; PAGE_MASK)|get_asid())
DECL|macro|set_tlb_data
mdefine_line|#define set_tlb_data(entry, data)&t;(*entry = (data | _PAGE_PRESENT))
macro_line|#ifdef CONFIG_MMU
DECL|macro|enter_lazy_tlb
mdefine_line|#define enter_lazy_tlb(mm, tsk)&t;do { } while (0)
DECL|function|get_new_mmu_context
r_static
r_inline
r_void
id|get_new_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|mc
op_assign
op_increment
id|mmu_context_cache
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mc
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
)paren
(brace
multiline_comment|/* We exhaust ASID of this version.&n;&t;&t;   Flush all TLB and start new cycle. */
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fix version if needed.&n;&t;&t;   Note that we avoid version #0 to distingush NO_CONTEXT. */
r_if
c_cond
(paren
op_logical_neg
id|mc
)paren
id|mmu_context_cache
op_assign
id|mc
op_assign
id|MMU_CONTEXT_FIRST_VERSION
suffix:semicolon
)brace
id|mm_context
c_func
(paren
id|mm
)paren
op_assign
id|mc
suffix:semicolon
)brace
multiline_comment|/*&n; * Get MMU context if needed.&n; */
DECL|function|get_mmu_context
r_static
r_inline
r_void
id|get_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
)paren
(brace
r_int
r_int
id|mc
op_assign
id|mmu_context_cache
suffix:semicolon
multiline_comment|/* Check if we have old version of context.&n;&t;&t;   If it&squot;s old, we need to get new context with new version. */
r_if
c_cond
(paren
(paren
id|mm_context
c_func
(paren
id|mm
)paren
op_xor
id|mc
)paren
op_amp
id|MMU_CONTEXT_VERSION_MASK
)paren
id|get_new_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|function|init_new_context
r_static
r_inline
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
macro_line|#ifndef CONFIG_SMP
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
macro_line|#else /* CONFIG_SMP */
r_int
id|num_cpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|mm-&gt;context
(braket
id|i
)braket
op_assign
id|NO_CONTEXT
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while (0)
DECL|function|set_asid
r_static
r_inline
r_void
id|set_asid
c_func
(paren
r_int
r_int
id|asid
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|MASID
op_assign
(paren
id|asid
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
)brace
DECL|function|get_asid
r_static
r_inline
r_int
r_int
id|get_asid
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|asid
suffix:semicolon
id|asid
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
id|MASID
suffix:semicolon
id|asid
op_and_assign
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_return
id|asid
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_context
r_static
r_inline
r_void
id|activate_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|get_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|set_asid
c_func
(paren
id|mm_context
c_func
(paren
id|mm
)paren
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
)brace
DECL|function|switch_mm
r_static
r_inline
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SMP */
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|cpu_set
c_func
(paren
id|cpu
comma
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Set MPTB = next-&gt;pgd */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|MPTB
op_assign
(paren
r_int
r_int
)paren
id|next-&gt;pgd
suffix:semicolon
id|activate_context
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_else
r_if
c_cond
(paren
op_logical_neg
id|cpu_test_and_set
c_func
(paren
id|cpu
comma
id|next-&gt;cpu_vm_mask
)paren
)paren
id|activate_context
c_func
(paren
id|next
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk, mm)&t;do { } while (0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next)&t;&bslash;&n;&t;switch_mm((prev), (next), NULL)
macro_line|#else
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(mm)             do { } while (0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)        (0)
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)             do { } while (0)
DECL|macro|set_asid
mdefine_line|#define set_asid(asid)                  do { } while (0)
DECL|macro|get_asid
mdefine_line|#define get_asid()                      (0)
DECL|macro|activate_context
mdefine_line|#define activate_context(mm)            do { } while (0)
DECL|macro|switch_mm
mdefine_line|#define switch_mm(prev,next,tsk)        do { } while (0)
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(mm,tsk)           do { } while (0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev,next)          do { } while (0)
DECL|macro|enter_lazy_tlb
mdefine_line|#define enter_lazy_tlb(mm,tsk)          do { } while (0)
macro_line|#endif /* CONFIG_MMU */
macro_line|#endif /* not __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_M32R_MMU_CONTEXT_H */
eof
