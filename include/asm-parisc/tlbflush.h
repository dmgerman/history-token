macro_line|#ifndef _PARISC_TLBFLUSH_H
DECL|macro|_PARISC_TLBFLUSH_H
mdefine_line|#define _PARISC_TLBFLUSH_H
multiline_comment|/* TLB flushing routines.... */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * flush_tlb_mm()&n; *&n; * XXX This code is NOT valid for HP-UX compatibility processes,&n; * (although it will probably work 99% of the time). HP-UX&n; * processes are free to play with the space id&squot;s and save them&n; * over long periods of time, etc. so we have to preserve the&n; * space and just flush the entire tlb. We need to check the&n; * personality in order to do that, but the personality is not&n; * currently being set correctly.&n; *&n; * Of course, Linux processes could do the same thing, but&n; * we don&squot;t support that (and the compilers, dynamic linker,&n; * etc. do not do that).&n; */
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
op_amp
id|init_mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Should never happen */
macro_line|#ifdef CONFIG_SMP
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
l_int|0
)paren
id|free_sid
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
id|mm-&gt;context
op_assign
id|alloc_sid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|load_context
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|flush_tlb_pgtables
r_extern
id|__inline__
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
multiline_comment|/* For one page, it&squot;s not worth testing the split_tlb variable */
id|mtsp
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
l_int|1
)paren
suffix:semicolon
id|pdtlb
c_func
(paren
id|addr
)paren
suffix:semicolon
id|pitlb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
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
r_int
r_int
id|npages
suffix:semicolon
id|npages
op_assign
(paren
(paren
id|end
op_minus
(paren
id|start
op_amp
id|PAGE_MASK
)paren
)paren
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|npages
op_ge
l_int|512
)paren
multiline_comment|/* XXX arbitrary, should be tuned */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|mtsp
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|split_tlb
)paren
(brace
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|pdtlb
c_func
(paren
id|start
)paren
suffix:semicolon
id|pitlb
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|pdtlb
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) flush_tlb_all()
macro_line|#endif
eof
