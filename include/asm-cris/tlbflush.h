macro_line|#ifndef _CRIS_TLBFLUSH_H
DECL|macro|_CRIS_TLBFLUSH_H
mdefine_line|#define _CRIS_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/*&n; * TLB flushing (implemented in arch/cris/mm/tlb.c):&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; *&n; */
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
id|mm
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
id|vma
comma
r_int
r_int
id|addr
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
DECL|function|flush_tlb_pgtables
r_extern
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
multiline_comment|/* CRIS does not keep any page table caches in TLB */
)brace
DECL|function|flush_tlb
r_extern
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) flush_tlb_all()
macro_line|#endif /* _CRIS_TLBFLUSH_H */
eof
