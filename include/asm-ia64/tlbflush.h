macro_line|#ifndef _ASM_IA64_TLBFLUSH_H
DECL|macro|_ASM_IA64_TLBFLUSH_H
mdefine_line|#define _ASM_IA64_TLBFLUSH_H
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Now for some TLB flushing routines.  This is the kind of stuff that&n; * can be very expensive, so try to avoid them whenever possible.&n; */
multiline_comment|/*&n; * Flush everything (kernel mapping may also have changed due to&n; * vmalloc/vfree).&n; */
r_extern
r_void
id|__flush_tlb_all
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_flush_tlb_all
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flush_tlb_all
macro_line|# define flush_tlb_all()&t;smp_flush_tlb_all()
macro_line|#else
DECL|macro|flush_tlb_all
macro_line|# define flush_tlb_all()&t;__flush_tlb_all()
macro_line|#endif
multiline_comment|/*&n; * Flush a specified user mapping&n; */
r_static
r_inline
r_void
DECL|function|flush_tlb_mm
id|flush_tlb_mm
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
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
(brace
multiline_comment|/* This is called, e.g., as a result of exec().  */
id|get_new_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|reload_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
)brace
r_extern
r_void
id|flush_tlb_range
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
suffix:semicolon
multiline_comment|/*&n; * Page-granular tlb flush.&n; */
r_static
r_inline
r_void
DECL|function|flush_tlb_page
id|flush_tlb_page
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
macro_line|#ifdef CONFIG_SMP
id|flush_tlb_range
c_func
(paren
id|vma
comma
(paren
id|addr
op_amp
id|PAGE_MASK
)paren
comma
(paren
id|addr
op_amp
id|PAGE_MASK
)paren
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
id|asm
r_volatile
(paren
l_string|&quot;ptc.l %0,%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|PAGE_SHIFT
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|vma-&gt;vm_mm-&gt;context
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Flush the TLB entries mapping the virtually mapped linear page&n; * table corresponding to address range [START-END).&n; */
r_static
r_inline
r_void
DECL|function|flush_tlb_pgtables
id|flush_tlb_pgtables
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
multiline_comment|/*&n;&t; * Deprecated.  The virtual page table is now flushed via the normal gather/flush&n;&t; * interface (see tlb.h).&n;&t; */
)brace
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end)&t;flush_tlb_all()&t;/* XXX fix me */
macro_line|#endif /* _ASM_IA64_TLBFLUSH_H */
eof
