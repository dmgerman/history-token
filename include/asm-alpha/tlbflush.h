macro_line|#ifndef _ALPHA_TLBFLUSH_H
DECL|macro|_ALPHA_TLBFLUSH_H
mdefine_line|#define _ALPHA_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
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
multiline_comment|/* Use a few helper functions to hide the ugly broken ASN&n;   numbers on early Alphas (ev4 and ev45).  */
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
multiline_comment|/* Flush just one page in the current TLB set.  We need to be very&n;   careful about the icache here, there is no way to invalidate a&n;   specific icache page.  */
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
multiline_comment|/* Flush current user mapping.  */
r_static
r_inline
r_void
DECL|function|flush_tlb
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
multiline_comment|/* Flush someone else&squot;s user mapping.  */
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
multiline_comment|/* Check it&squot;s not zero first to avoid cacheline ping pong&n;&t;   when possible.  */
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
multiline_comment|/* Flush a specified range of user mapping page tables from TLB.&n;   Although Alpha uses VPTE caches, this can be a nop, as Alpha does&n;   not have finegrained tlb flushing, so it will flush VPTE stuff&n;   during next flush_tlb_range.  */
r_static
r_inline
r_void
DECL|function|flush_tlb_pgtables
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
multiline_comment|/* Flush everything (kernel mapping may also have changed&n;   due to vmalloc/vfree).  */
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
multiline_comment|/* Flush a specified user mapping.  */
r_static
r_inline
r_void
DECL|function|flush_tlb_mm
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
multiline_comment|/* Page-granular tlb flush.  */
r_static
r_inline
r_void
DECL|function|flush_tlb_page
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
multiline_comment|/* Flush a specified range of user mapping.  On the Alpha we flush&n;   the whole user tlb.  */
r_static
r_inline
r_void
DECL|function|flush_tlb_range
id|flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
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
id|vma-&gt;vm_mm
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
id|vm_area_struct
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
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) flush_tlb_all()
macro_line|#endif /* _ALPHA_TLBFLUSH_H */
eof
