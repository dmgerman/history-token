macro_line|#ifndef _SPARC_TLBFLUSH_H
DECL|macro|_SPARC_TLBFLUSH_H
mdefine_line|#define _SPARC_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
singleline_comment|// #include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&t;XXX Exists?&n; *  - flush_tlb_all() flushes all processes TLBs &n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; */
macro_line|#ifdef CONFIG_SMP
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_tlb_all
comma
r_void
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_tlb_mm
comma
r_struct
id|mm_struct
op_star
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_tlb_range
comma
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
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_tlb_page
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|local_flush_tlb_all
mdefine_line|#define local_flush_tlb_all() BTFIXUP_CALL(local_flush_tlb_all)()
DECL|macro|local_flush_tlb_mm
mdefine_line|#define local_flush_tlb_mm(mm) BTFIXUP_CALL(local_flush_tlb_mm)(mm)
DECL|macro|local_flush_tlb_range
mdefine_line|#define local_flush_tlb_range(vma,start,end) BTFIXUP_CALL(local_flush_tlb_range)(vma,start,end)
DECL|macro|local_flush_tlb_page
mdefine_line|#define local_flush_tlb_page(vma,addr) BTFIXUP_CALL(local_flush_tlb_page)(vma,addr)
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
id|vm_area_struct
op_star
id|mm
comma
r_int
r_int
id|page
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_tlb_all
comma
r_void
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_tlb_mm
comma
r_struct
id|mm_struct
op_star
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_tlb_range
comma
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
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_tlb_page
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
singleline_comment|// Thanks to Anton Blanchard, our pagetables became uncached in 2.4. Wee!
singleline_comment|// extern void flush_tlb_pgtables(struct mm_struct *mm,
singleline_comment|//     unsigned long start, unsigned long end);
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm, start, end)&t;do{ }while(0)
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() BTFIXUP_CALL(flush_tlb_all)()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm) BTFIXUP_CALL(flush_tlb_mm)(mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,start,end) BTFIXUP_CALL(flush_tlb_range)(vma,start,end)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,addr) BTFIXUP_CALL(flush_tlb_page)(vma,addr)
singleline_comment|// #define flush_tlb() flush_tlb_mm(current-&gt;active_mm)&t;/* XXX Sure? */
multiline_comment|/*&n; * This is a kludge, until I know better. --zaitcev XXX&n; */
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) flush_tlb_all()
macro_line|#endif /* _SPARC_TLBFLUSH_H */
eof
