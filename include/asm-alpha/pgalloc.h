macro_line|#ifndef _ALPHA_PGALLOC_H
DECL|macro|_ALPHA_PGALLOC_H
mdefine_line|#define _ALPHA_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__MMU_EXTERN_INLINE
mdefine_line|#define __MMU_EXTERN_INLINE
macro_line|#endif
r_extern
r_void
id|__load_new_mm_context
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Caches aren&squot;t brain-dead on the Alpha. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
multiline_comment|/* Note that the following two definitions are _highly_ dependent&n;   on the contexts in which they are used in the kernel.  I personally&n;   think it is criminal how loosely defined these macros are.  */
multiline_comment|/* We need to flush the kernel&squot;s icache after loading modules.  The&n;   only other use of this macro is in load_aout_interp which is not&n;   used on Alpha. &n;&n;   Note that this definition should *not* be used for userspace&n;   icache flushing.  While functional, it is _way_ overkill.  The&n;   icache is tagged with ASNs and it suffices to allocate a new ASN&n;   for the process.  */
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;imb()
macro_line|#else
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;smp_imb()
r_extern
r_void
id|smp_imb
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Use a few helper functions to hide the ugly broken ASN&n; * numbers on early Alphas (ev4 and ev45)&n; */
id|__EXTERN_INLINE
r_void
DECL|function|ev4_flush_tlb_current
id|ev4_flush_tlb_current
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|tbiap
c_func
(paren
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev5_flush_tlb_current
id|ev5_flush_tlb_current
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|flush_tlb_other
id|flush_tlb_other
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
op_star
id|mmc
op_assign
op_amp
id|mm-&gt;context
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Check it&squot;s not zero first to avoid cacheline ping pong when&n;&t; * possible.&n;&t; */
r_if
c_cond
(paren
op_star
id|mmc
)paren
op_star
id|mmc
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We need to flush the userspace icache after setting breakpoints in&n;   ptrace.  I don&squot;t think it&squot;s needed in do_swap_page, or do_no_page,&n;   but I don&squot;t know how to get rid of it either.&n;&n;   Instead of indiscriminately using imb, take advantage of the fact&n;   that icache entries are tagged with the ASN and load a new mm context.  */
multiline_comment|/* ??? Ought to use this in arch/alpha/kernel/signal.c too.  */
macro_line|#ifndef CONFIG_SMP
r_static
r_inline
r_void
DECL|function|flush_icache_page
id|flush_icache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|mm
)paren
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|mm-&gt;context
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#else
r_extern
r_void
id|flush_icache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Flush just one page in the current TLB set.&n; * We need to be very careful about the icache here, there&n; * is no way to invalidate a specific icache page..&n; */
id|__EXTERN_INLINE
r_void
DECL|function|ev4_flush_tlb_current_page
id|ev4_flush_tlb_current_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|tbi_flag
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
(brace
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|tbi_flag
op_assign
l_int|3
suffix:semicolon
)brace
id|tbi
c_func
(paren
id|tbi_flag
comma
id|addr
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev5_flush_tlb_current_page
id|ev5_flush_tlb_current_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|tbi
c_func
(paren
l_int|2
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|flush_tlb_current
macro_line|# define flush_tlb_current&t;&t;alpha_mv.mv_flush_tlb_current
DECL|macro|flush_tlb_current_page
macro_line|# define flush_tlb_current_page&t;&t;alpha_mv.mv_flush_tlb_current_page
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|flush_tlb_current
macro_line|#  define flush_tlb_current&t;&t;ev4_flush_tlb_current
DECL|macro|flush_tlb_current_page
macro_line|#  define flush_tlb_current_page&t;ev4_flush_tlb_current_page
macro_line|# else
DECL|macro|flush_tlb_current
macro_line|#  define flush_tlb_current&t;&t;ev5_flush_tlb_current
DECL|macro|flush_tlb_current_page
macro_line|#  define flush_tlb_current_page&t;ev5_flush_tlb_current_page
macro_line|# endif
macro_line|#endif
macro_line|#ifdef __MMU_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__MMU_EXTERN_INLINE
macro_line|#undef __MMU_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * Flush current user mapping.&n; */
DECL|function|flush_tlb
r_static
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_current
c_func
(paren
id|current-&gt;active_mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush a specified range of user mapping page tables&n; * from TLB.&n; * Although Alpha uses VPTE caches, this can be a nop, as Alpha does&n; * not have finegrained tlb flushing, so it will flush VPTE stuff&n; * during next flush_tlb_range.&n; */
DECL|function|flush_tlb_pgtables
r_static
r_inline
r_void
id|flush_tlb_pgtables
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
)brace
macro_line|#ifndef CONFIG_SMP
multiline_comment|/*&n; * Flush everything (kernel mapping may also have&n; * changed due to vmalloc/vfree)&n; */
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|tbia
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush a specified user mapping&n; */
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
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
op_eq
id|current-&gt;active_mm
)paren
id|flush_tlb_current
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|flush_tlb_other
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Page-granular tlb flush.&n; *&n; * do a tbisd (type = 2) normally, and a tbis (type = 3)&n; * if it is an executable mapping.  We want to avoid the&n; * itlb flush, because that potentially also does a&n; * icache flush.&n; */
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|flush_tlb_current_page
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
r_else
id|flush_tlb_other
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush a specified range of user mapping:  on the&n; * Alpha we flush the whole user tlb.&n; */
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*      &n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pmd_cache
r_int
r_int
op_star
id|pmd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|quicklists
suffix:semicolon
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|quicklists
mdefine_line|#define quicklists cpu_data[smp_processor_id()]
macro_line|#endif
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist (quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist (quicklists.pmd_cache)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist (quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size (quicklists.pgtable_cache_sz)
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm, pmd, pte)&t;pmd_set(pmd, pte)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pgd, pmd)&t;pgd_set(pgd, pmd)
r_extern
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_pgd_fast
r_static
r_inline
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_else
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_static
r_inline
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
op_assign
(paren
r_int
r_int
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_static
r_inline
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc_one
r_static
r_inline
id|pmd_t
op_star
id|pmd_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pmd_t
op_star
id|ret
op_assign
(paren
id|pmd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pmd_alloc_one_fast
r_static
r_inline
id|pmd_t
op_star
id|pmd_alloc_one_fast
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|pmd_free_fast
r_static
r_inline
r_void
id|pmd_free_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pmd
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|pmd_free_slow
r_static
r_inline
r_void
id|pmd_free_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_one
r_static
r_inline
id|pte_t
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_alloc_one_fast
r_static
r_inline
id|pte_t
op_star
id|pte_alloc_one_fast
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|pte_free_fast
r_static
r_inline
r_void
id|pte_free_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|pte_free_slow
r_static
r_inline
r_void
id|pte_free_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;pte_free_fast(pte)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;pmd_free_fast(pmd)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;&t;get_pgd_fast()
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ALPHA_PGALLOC_H */
eof
