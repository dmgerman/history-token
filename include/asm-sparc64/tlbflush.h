macro_line|#ifndef _SPARC64_TLBFLUSH_H
DECL|macro|_SPARC64_TLBFLUSH_H
mdefine_line|#define _SPARC64_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* TLB flush operations. */
r_extern
r_void
id|flush_tlb_pending
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,start,end)&t;&bslash;&n;&t;do { (void)(start); flush_tlb_pending(); } while (0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,addr)&t;flush_tlb_pending()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;flush_tlb_pending()
r_extern
r_void
id|__flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_page
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|page
comma
r_int
r_int
id|r
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_kernel_range
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;__flush_tlb_all()
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start,end) &bslash;&n;&t;__flush_tlb_kernel_range(start,end)
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|smp_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_kernel_range
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
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;smp_flush_tlb_all()
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) &bslash;&n;&t;smp_flush_tlb_kernel_range(start, end)
macro_line|#endif /* ! CONFIG_SMP */
r_extern
r_void
id|flush_tlb_pgtables
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
macro_line|#endif /* _SPARC64_TLBFLUSH_H */
eof
