multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/tlbflush.h&n; *&n; *  Copyright (C) 1999-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; *&t;TLB Management&n; *&t;==============&n; *&n; *&t;The arch/arm/mm/tlb-*.S files implement these methods.&n; *&n; *&t;The TLB specific code is expected to perform whatever tests it&n; *&t;needs to determine if it should invalidate the TLB for each&n; *&t;call.  Start addresses are inclusive and end addresses are&n; *&t;exclusive; it is safe to round these addresses down.&n; *&n; *&t;flush_tlb_all()&n; *&n; *&t;&t;Invalidate the entire TLB.&n; *&n; *&t;flush_tlb_mm(mm)&n; *&n; *&t;&t;Invalidate all TLB entries in a particular address&n; *&t;&t;space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&n; *&t;flush_tlb_range(mm,start,end)&n; *&n; *&t;&t;Invalidate a range of TLB entries in the specified&n; *&t;&t;address space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&t;&t;- start - start address (may not be aligned)&n; *&t;&t;- end&t;- end address (exclusive, may not be aligned)&n; *&n; *&t;flush_tlb_page(vaddr,vma)&n; *&n; *&t;&t;Invalidate the specified page in the specified address range.&n; *&t;&t;- vaddr - virtual address (may not be aligned)&n; *&t;&t;- vma&t;- vma_struct describing address range&n; *&n; *&t;flush_kern_tlb_page(kaddr)&n; *&n; *&t;&t;Invalidate the TLB entry for the specified page.  The address&n; *&t;&t;will be in the kernels virtual memory space.  Current uses&n; *&t;&t;only require the D-TLB to be invalidated.&n; *&t;&t;- kaddr - Kernel virtual memory address&n; */
DECL|struct|cpu_tlb_fns
r_struct
id|cpu_tlb_fns
(brace
DECL|member|flush_kern_all
r_void
(paren
op_star
id|flush_kern_all
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|flush_user_mm
r_void
(paren
op_star
id|flush_user_mm
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
DECL|member|flush_user_range
r_void
(paren
op_star
id|flush_user_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
DECL|member|flush_user_page
r_void
(paren
op_star
id|flush_user_page
)paren
(paren
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
DECL|member|flush_kern_range
r_void
(paren
op_star
id|flush_kern_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|flush_kern_page
r_void
(paren
op_star
id|flush_kern_page
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Convert calls to our calling convention.&n; */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;__cpu_flush_kern_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;__cpu_flush_user_tlb_mm(mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,start,end)&t;__cpu_flush_user_tlb_range(start,end,vma)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,vaddr)&t;__cpu_flush_user_tlb_page(vaddr,vma)
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(s,e)&t;__cpu_flush_kern_tlb_range(s,e)
DECL|macro|flush_tlb_kernel_page
mdefine_line|#define flush_tlb_kernel_page(kaddr)&t;__cpu_flush_kern_tlb_page(kaddr)
multiline_comment|/*&n; * Now select the calling method&n; */
macro_line|#ifdef MULTI_TLB
r_extern
r_struct
id|cpu_tlb_fns
id|cpu_tlb
suffix:semicolon
DECL|macro|__cpu_flush_kern_tlb_all
mdefine_line|#define __cpu_flush_kern_tlb_all&t;cpu_tlb.flush_kern_all
DECL|macro|__cpu_flush_user_tlb_mm
mdefine_line|#define __cpu_flush_user_tlb_mm&t;&t;cpu_tlb.flush_user_mm
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;cpu_tlb.flush_user_range
DECL|macro|__cpu_flush_user_tlb_page
mdefine_line|#define __cpu_flush_user_tlb_page&t;cpu_tlb.flush_user_page
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;cpu_tlb.flush_kern_range
DECL|macro|__cpu_flush_kern_tlb_page
mdefine_line|#define __cpu_flush_kern_tlb_page&t;cpu_tlb.flush_kern_page
macro_line|#else
DECL|macro|__cpu_flush_kern_tlb_all
mdefine_line|#define __cpu_flush_kern_tlb_all&t;__glue(_TLB,_flush_kern_tlb_all)
DECL|macro|__cpu_flush_user_tlb_mm
mdefine_line|#define __cpu_flush_user_tlb_mm&t;&t;__glue(_TLB,_flush_user_tlb_mm)
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;__glue(_TLB,_flush_user_tlb_range)
DECL|macro|__cpu_flush_user_tlb_page
mdefine_line|#define __cpu_flush_user_tlb_page&t;__glue(_TLB,_flush_user_tlb_page)
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;__glue(_TLB,_flush_kern_tlb_range)
DECL|macro|__cpu_flush_kern_tlb_page
mdefine_line|#define __cpu_flush_kern_tlb_page&t;__glue(_TLB,_flush_kern_tlb_page)
r_extern
r_void
id|__cpu_flush_kern_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_flush_user_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_flush_user_tlb_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_flush_user_tlb_page
c_func
(paren
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_flush_kern_tlb_range
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
id|__cpu_flush_kern_tlb_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * if PG_dcache_dirty is set for the page, we need to ensure that any&n; * cache entries for the kernels virtual memory range are written&n; * back to the page.&n; */
r_extern
r_void
id|update_mmu_cache
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
comma
id|pte_t
id|pte
)paren
suffix:semicolon
multiline_comment|/*&n; * ARM processors do not cache TLB tables in RAM.&n; */
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm,start,end)&t;do { } while (0)
multiline_comment|/*&n; * Old ARM MEMC stuff.  This supports the reversed mapping handling that&n; * we have on the older 26-bit machines.  We don&squot;t have a MEMC chip, so...&n; */
DECL|macro|memc_update_all
mdefine_line|#define memc_update_all()&t;&t;do { } while (0)
DECL|macro|memc_update_mm
mdefine_line|#define memc_update_mm(mm)&t;&t;do { } while (0)
DECL|macro|memc_update_addr
mdefine_line|#define memc_update_addr(mm,pte,log)&t;do { } while (0)
DECL|macro|memc_clear
mdefine_line|#define memc_clear(mm,physaddr)&t;&t;do { } while (0)
eof
