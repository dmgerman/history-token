multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/cache.h&n; *&n; *  Copyright (C) 1999-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/glue.h&gt;
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty PG_arch_1
multiline_comment|/*&n; * Cache handling for 32-bit ARM processors.&n; *&n; * Note that on ARM, we have a more accurate specification than that&n; * Linux&squot;s &quot;flush&quot;.  We therefore do not use &quot;flush&quot; here, but instead&n; * use:&n; *&n; * clean:      the act of pushing dirty cache entries out to memory.&n; * invalidate: the act of discarding data held within the cache,&n; *             whether it is dirty or not.&n; */
multiline_comment|/*&n; * Generic I + D cache&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_cache_clean_invalidate_all();&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* This is always called for current-&gt;mm */
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(_mm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;active_mm)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_all();&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(_vma,_start,_end)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;active_mm)&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_start), (_end), 1); &bslash;&n;&t;} while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(_vma,_vmaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;active_mm) {&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_vmaddr),&t;&bslash;&n;&t;&t;&t;&t;(_vmaddr) + PAGE_SIZE,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
multiline_comment|/*&n; * This flushes back any buffered write data.  We have to clean the entries&n; * in the cache for this page.  This does not invalidate either I or D caches.&n; *&n; * Called from:&n; *  1. fs/exec.c:put_dirty_page&t;&t;&t;&t;- ok&n; *     - page came from alloc_page(), so page-&gt;mapping = NULL.&n; *     - flush_dcache_page called immediately prior.&n; *&n; *  2. kernel/ptrace.c:access_one_page&t;&t;&t;- flush_icache_page&n; *     - flush_cache_page takes care of the user space side of the mapping.&n; *     - page is either a page cache page (with page-&gt;mapping set, and&n; *       hence page-&gt;mapping-&gt;i_mmap{,shared} also set) or an anonymous&n; *       page.  I think this is ok.&n; *&n; *  3. kernel/ptrace.c:access_one_page&t;&t;&t;- bad&n; *     - flush_cache_page takes care of the user space side of the mapping.&n; *     - no apparant cache protection, reading the kernel virtual alias&n; *&n; *  4. mm/filemap.c:filemap_no_page&t;&t;&t;- ok&n; *     - add_to_page_cache_* clears PG_arch_1.&n; *     - page-&gt;mapping != NULL.&n; *     - i_mmap or i_mmap_shared will be non-null if mmap&squot;d&n; *     - called from (8).&n; *&n; *  5. mm/memory.c:break_cow,do_wp_page&t;&t;&t;- {copy,clear}_user_page&n; *     - need to ensure that copy_cow_page has pushed all data from the dcache&n; *       to the page.&n; *       - calls&n; *         - clear_user_highpage -&gt; clear_user_page&n; *         - copy_user_highpage -&gt; copy_user_page&n; *&n; *  6. mm/memory.c:do_swap_page&t;&t;&t;&t;- flush_icache_page&n; *     - flush_icache_page called afterwards - if flush_icache_page does the&n; *       same as flush_dcache_page, update_mmu_cache will do the work for us.&n; *     - update_mmu_cache called.&n; *&n; *  7. mm/memory.c:do_anonymous_page&t;&t;&t;- {copy,clear}_user_page&n; *     - calls clear_user_highpage.  See (5)&n; *&n; *  8. mm/memory.c:do_no_page&t;&t;&t;&t;- flush_icache_page&n; *     - flush_icache_page called afterwards - if flush_icache_page does the&n; *       same as flush_dcache_page, update_mmu_cache will do the work for us.&n; *     - update_mmu_cache called.&n; *     - When we place a user mapping, we will call update_mmu_cache,&n; *       which will catch PG_arch_1 set.&n; *&n; *  9. mm/shmem.c:shmem_no_page&t;&t;&t;&t;- ok&n; *     - shmem_get_page clears PG_arch_1, as does add_to_page_cache (duplicate)&n; *     - page-&gt;mapping != NULL.&n; *     - i_mmap or i_mmap_shared will be non-null if mmap&squot;d&n; *     - called from (8).&n; *&n; * 10. mm/swapfile.c:try_to_unuse&t;&t;&t;- bad&n; *     - this looks really dodgy - we&squot;re putting pages from the swap cache&n; *       straight into processes, and the only cache handling appears to&n; *       be flush_page_to_ram.&n; */
DECL|macro|flush_page_to_ram_ok
mdefine_line|#define flush_page_to_ram_ok
macro_line|#ifdef flush_page_to_ram_ok
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;do { } while (0)
macro_line|#else
DECL|function|flush_page_to_ram
r_static
id|__inline__
r_void
id|flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|cpu_flush_ram_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * D cache only&n; */
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(_s,_e)&t;cpu_dcache_invalidate_range((_s),(_e))
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(_s,_e)&t;cpu_dcache_clean_range((_s),(_e))
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(_s,_e)&t;cpu_cache_clean_invalidate_range((_s),(_e),0)
DECL|macro|mapping_mapped
mdefine_line|#define mapping_mapped(map)&t;((map)-&gt;i_mmap || (map)-&gt;i_mmap_shared)
multiline_comment|/*&n; * flush_dcache_page is used when the kernel has written to the page&n; * cache page at virtual address page-&gt;virtual.&n; *&n; * If this page isn&squot;t mapped (ie, page-&gt;mapping = NULL), or it has&n; * userspace mappings (page-&gt;mapping-&gt;i_mmap or page-&gt;mapping-&gt;i_mmap_shared)&n; * then we _must_ always clean + invalidate the dcache entries associated&n; * with the kernel mapping.&n; *&n; * Otherwise we can defer the operation, and clean the cache when we are&n; * about to change to user space.  This is the same method as used on SPARC64.&n; * See update_mmu_cache for the user space part.&n; */
DECL|function|flush_dcache_page
r_static
r_inline
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
op_logical_neg
id|mapping_mapped
c_func
(paren
id|page-&gt;mapping
)paren
)paren
id|set_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_else
(brace
r_int
r_int
id|virt
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|virt
comma
id|virt
op_plus
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * flush_icache_page makes the kernel page address consistent with the&n; * user space mappings.  The functionality is the same as flush_dcache_page,&n; * except we can do an optimisation and only clean the caches here if&n; * vma-&gt;vm_mm == current-&gt;active_mm.&n; *&n; * This function is misnamed IMHO.  There are three places where it&n; * is called, each of which is preceded immediately by a call to&n; * flush_page_to_ram:&n; */
macro_line|#ifdef flush_page_to_ram_ok
DECL|function|flush_icache_page
r_static
r_inline
r_void
id|flush_icache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
op_logical_neg
id|mapping_mapped
c_func
(paren
id|page-&gt;mapping
)paren
)paren
id|set_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
(brace
r_int
r_int
id|virt
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|virt
comma
id|virt
op_plus
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;do { } while (0)
macro_line|#endif
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)&t;&t;cpu_dcache_clean_entry((unsigned long)(_s))
multiline_comment|/*&n; * I cache coherency stuff.&n; *&n; * This *is not* just icache.  It is to make data written to memory&n; * consistent such that instructions fetched from the region are what&n; * we expect.&n; *&n; * This generally means that we have to clean out the Dcache and write&n; * buffers, and maybe flush the Icache in the specified range.&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(_s,_e)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_icache_invalidate_range((_s), (_e));&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; *&t;TLB Management&n; *&t;==============&n; *&n; *&t;The arch/arm/mm/tlb-*.S files implement this methods.&n; *&n; *&t;The TLB specific code is expected to perform whatever tests it&n; *&t;needs to determine if it should invalidate the TLB for each&n; *&t;call.  Start addresses are inclusive and end addresses are&n; *&t;exclusive; it is safe to round these addresses down.&n; *&n; *&t;flush_tlb_all()&n; *&n; *&t;&t;Invalidate the entire TLB.&n; *&n; *&t;flush_tlb_mm(mm)&n; *&n; *&t;&t;Invalidate all TLB entries in a particular address&n; *&t;&t;space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&n; *&t;flush_tlb_range(mm,start,end)&n; *&n; *&t;&t;Invalidate a range of TLB entries in the specified&n; *&t;&t;address space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&t;&t;- start - start address (may not be aligned)&n; *&t;&t;- end&t;- end address (exclusive, may not be aligned)&n; *&n; *&t;flush_tlb_page(vaddr,vma)&n; *&n; *&t;&t;Invalidate the specified page in the specified address range.&n; *&t;&t;- vaddr - virtual address (may not be aligned)&n; *&t;&t;- vma&t;- vma_struct describing address range&n; *&n; *&t;flush_kern_tlb_page(kaddr)&n; *&n; *&t;&t;Invalidate the TLB entry for the specified page.  The address&n; *&t;&t;will be in the kernels virtual memory space.  Current uses&n; *&t;&t;only require the D-TLB to be invalidated.&n; *&t;&t;- kaddr - Kernel virtual memory address&n; */
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
DECL|macro|flush_kern_tlb_page
mdefine_line|#define flush_kern_tlb_page(kaddr)&t;__cpu_flush_kern_tlb_page(kaddr)
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
