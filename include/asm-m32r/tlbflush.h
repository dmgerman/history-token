macro_line|#ifndef _ASM_M32R_TLBFLUSH_H
DECL|macro|_ASM_M32R_TLBFLUSH_H
mdefine_line|#define _ASM_M32R_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; */
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
comma
r_int
r_int
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
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
macro_line|#ifdef CONFIG_MMU
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;local_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;local_flush_tlb_mm(mm)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page)&t;local_flush_tlb_page(vma, page)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma, start, end)&t;&bslash;&n;&t;local_flush_tlb_range(vma, start, end)
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end)&t;local_flush_tlb_all()
macro_line|#else&t;/* CONFIG_MMU */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;do { } while (0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, vmaddr)&t;do { } while (0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma, start, end)&t;do { } while (0)
macro_line|#endif&t;/* CONFIG_MMU */
macro_line|#else&t;/* CONFIG_SMP */
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
comma
r_int
r_int
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
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;smp_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;smp_flush_tlb_mm(mm)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page)&t;smp_flush_tlb_page(vma, page)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma, start, end)&t;&bslash;&n;&t;smp_flush_tlb_range(vma, start, end)
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end)&t;smp_flush_tlb_all()
macro_line|#endif&t;/* CONFIG_SMP */
DECL|function|__flush_tlb_page
r_static
id|__inline__
r_void
id|__flush_tlb_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|tmpreg0
comma
id|tmpreg1
comma
id|tmpreg2
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;seth&t;%0, #high(%4)&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%3, @(%5, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;ldi&t;%1, #1&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%1, @(%6, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;add3&t;%1, %0, %7&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%2, @(%6, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;bnez&t;%2, 1b&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%0, @%1+&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%1, @%1&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%2, @+%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%2, @+%1&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|page
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMU_REG_BASE
)paren
comma
l_string|&quot;i&quot;
(paren
id|MSVA_offset
)paren
comma
l_string|&quot;i&quot;
(paren
id|MTOP_offset
)paren
comma
l_string|&quot;i&quot;
(paren
id|MIDXI_offset
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_all
r_static
id|__inline__
r_void
id|__flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmpreg0
comma
id|tmpreg1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;seth&t;%0, #high(%2)&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;or3&t;%0, %0, #low(%2)&t;&bslash;n&bslash;t&quot;
l_string|&quot;ldi&t;%1, #0xc&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%1, @%0&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%1, @%0&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bnez&t;%1, 1b&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg1
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MTOP
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm, start, end)&t;do { } while (0)
r_extern
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
suffix:semicolon
macro_line|#endif&t;/* _ASM_M32R_TLBFLUSH_H */
eof
