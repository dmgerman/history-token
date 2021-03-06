macro_line|#ifndef __ASM_TLBFLUSH_H
DECL|macro|__ASM_TLBFLUSH_H
mdefine_line|#define __ASM_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb_all() flushes all processes TLB entries&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB entries&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; */
r_extern
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_mm
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
id|local_flush_tlb_range
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
r_extern
r_void
id|local_flush_tlb_kernel_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_one
c_func
(paren
r_int
r_int
id|vaddr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
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
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_kernel_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
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
id|flush_tlb_one
c_func
(paren
r_int
r_int
id|vaddr
)paren
suffix:semicolon
macro_line|#else /* CONFIG_SMP */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;local_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;local_flush_tlb_mm(mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,vmaddr,end)&t;local_flush_tlb_range(vma, vmaddr, end)
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(vmaddr,end) &bslash;&n;&t;local_flush_tlb_kernel_range(vmaddr, end)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,page)&t;local_flush_tlb_page(vma, page)
DECL|macro|flush_tlb_one
mdefine_line|#define flush_tlb_one(vaddr)&t;&t;local_flush_tlb_one(vaddr)
macro_line|#endif /* CONFIG_SMP */
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
multiline_comment|/* Nothing to do on MIPS.  */
)brace
macro_line|#endif /* __ASM_TLBFLUSH_H */
eof
