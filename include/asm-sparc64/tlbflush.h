macro_line|#ifndef _SPARC64_TLBFLUSH_H
DECL|macro|_SPARC64_TLBFLUSH_H
mdefine_line|#define _SPARC64_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* TLB flush operations. */
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
id|__flush_tlb_mm
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|r
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_range
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|start
comma
r_int
r_int
id|r
comma
r_int
r_int
id|end
comma
r_int
r_int
id|pgsz
comma
r_int
r_int
id|size
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;__flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(__mm) &bslash;&n;do { if(CTX_VALID((__mm)-&gt;context)) &bslash;&n;&t;__flush_tlb_mm(CTX_HWBITS((__mm)-&gt;context), SECONDARY_CONTEXT); &bslash;&n;} while(0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(__vma, start, end) &bslash;&n;do { if(CTX_VALID((__vma)-&gt;vm_mm-&gt;context)) { &bslash;&n;&t;unsigned long __start = (start)&amp;PAGE_MASK; &bslash;&n;&t;unsigned long __end = PAGE_ALIGN(end); &bslash;&n;&t;__flush_tlb_range(CTX_HWBITS((__vma)-&gt;vm_mm-&gt;context), __start, &bslash;&n;&t;&t;&t;  SECONDARY_CONTEXT, __end, PAGE_SIZE, &bslash;&n;&t;&t;&t;  (__end - __start)); &bslash;&n;     } &bslash;&n;} while(0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page) &bslash;&n;do { struct mm_struct *__mm = (vma)-&gt;vm_mm; &bslash;&n;     if(CTX_VALID(__mm-&gt;context)) &bslash;&n;&t;__flush_tlb_page(CTX_HWBITS(__mm-&gt;context), (page)&amp;PAGE_MASK, &bslash;&n;&t;&t;&t; SECONDARY_CONTEXT); &bslash;&n;} while(0)
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
id|smp_flush_tlb_mm
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
id|smp_flush_tlb_range
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
id|smp_flush_tlb_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|page
)paren
suffix:semicolon
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;smp_flush_cache_all()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;smp_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;smp_flush_tlb_mm(mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma, start, end) &bslash;&n;&t;smp_flush_tlb_range(vma, start, end)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page) &bslash;&n;&t;smp_flush_tlb_page((vma)-&gt;vm_mm, page)
macro_line|#endif /* ! CONFIG_SMP */
macro_line|#endif /* _SPARC64_TLBFLUSH_H */
eof
