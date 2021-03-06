multiline_comment|/*&n; * include/asm-ppc/tlbflush.h&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_TLBFLUSH_H
DECL|macro|_PPC_TLBFLUSH_H
mdefine_line|#define _PPC_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
r_extern
r_void
id|_tlbie
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|_tlbia
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
macro_line|#ifndef CONFIG_44x
DECL|macro|__tlbia
mdefine_line|#define __tlbia()&t;asm volatile (&quot;sync; tlbia; isync&quot; : : : &quot;memory&quot;)
macro_line|#else
DECL|macro|__tlbia
mdefine_line|#define __tlbia&t;&t;_tlbia
macro_line|#endif
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
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
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page_nohash
r_static
r_inline
r_void
id|flush_tlb_page_nohash
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_range
r_static
r_inline
r_void
id|flush_tlb_kernel_range
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
(brace
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_FSL_BOOKE)
multiline_comment|/* TODO: determine if flush_tlb_range &amp; flush_tlb_kernel_range&n; * are best implemented as tlbia vs specific tlbie&squot;s */
DECL|macro|__tlbia
mdefine_line|#define __tlbia()&t;_tlbia()
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
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
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page_nohash
r_static
r_inline
r_void
id|flush_tlb_page_nohash
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_range
r_static
r_inline
r_void
id|flush_tlb_kernel_range
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
(brace
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_8xx)
DECL|macro|__tlbia
mdefine_line|#define __tlbia()&t;asm volatile (&quot;tlbia; sync&quot; : : : &quot;memory&quot;)
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
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
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page_nohash
r_static
r_inline
r_void
id|flush_tlb_page_nohash
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_range
r_static
r_inline
r_void
id|flush_tlb_kernel_range
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
(brace
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else&t;/* 6xx, 7xx, 7xxx cpus */
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|vm_area_struct
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
id|vmaddr
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_page_nohash
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
r_extern
r_void
id|flush_tlb_kernel_range
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
macro_line|#endif
multiline_comment|/*&n; * This is called in munmap when we have freed up some page-table&n; * pages.  We don&squot;t need to do anything here, there&squot;s nothing special&n; * about our page-table pages.  -- paulus&n; */
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
)brace
multiline_comment|/*&n; * This gets called at the end of handling a page fault, when&n; * the kernel has put a new PTE into the page table for the process.&n; * We use it to ensure coherency between the i-cache and d-cache&n; * for the page which has just been mapped in.&n; * On machines which use an MMU hash table, we use this to put a&n; * corresponding HPTE into the hash table ahead of time, instead of&n; * waiting for the inevitable extra hash-table miss exception.&n; */
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
macro_line|#endif /* _PPC_TLBFLUSH_H */
macro_line|#endif /*__KERNEL__ */
eof
