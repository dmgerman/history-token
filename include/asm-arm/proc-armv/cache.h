multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/cache.h&n; *&n; *  Copyright (C) 1999-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/mman.h&gt;
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
mdefine_line|#define flush_cache_range(_mm,_start,_end)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;mm)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_start), (_end), 1); &bslash;&n;&t;} while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(_vma,_vmaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;mm) {&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_vmaddr),&t;&bslash;&n;&t;&t;&t;&t;(_vmaddr) + PAGE_SIZE,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
multiline_comment|/*&n; * This flushes back any buffered write data.  We have to clean the entries&n; * in the cache for this page.  This does not invalidate either I or D caches.&n; *&n; * Called from:&n; * 1. mm/filemap.c:filemap_nopage&n; * 2. mm/filemap.c:filemap_nopage&n; *    [via do_no_page - ok]&n; *&n; * 3. mm/memory.c:break_cow&n; *    [copy_cow_page doesn&squot;t do anything to the cache; insufficient cache&n; *     handling.  Need to add flush_dcache_page() here]&n; *&n; * 4. mm/memory.c:do_swap_page&n; *    [read_swap_cache_async doesn&squot;t do anything to the cache: insufficient&n; *     cache handling.  Need to add flush_dcache_page() here]&n; *&n; * 5. mm/memory.c:do_anonymous_page&n; *    [zero page, never written by kernel - ok]&n; *&n; * 6. mm/memory.c:do_no_page&n; *    [we will be calling update_mmu_cache, which will catch on PG_dcache_dirty]&n; *&n; * 7. mm/shmem.c:shmem_nopage&n; * 8. mm/shmem.c:shmem_nopage&n; *    [via do_no_page - ok]&n; *&n; * 9. fs/exec.c:put_dirty_page&n; *    [we call flush_dcache_page prior to this, which will flush out the&n; *     kernel virtual addresses from the dcache - ok]&n; */
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
multiline_comment|/*&n; * D cache only&n; */
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(_s,_e)&t;cpu_dcache_invalidate_range((_s),(_e))
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(_s,_e)&t;cpu_dcache_clean_range((_s),(_e))
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(_s,_e)&t;cpu_cache_clean_invalidate_range((_s),(_e),0)
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
(paren
id|page-&gt;mapping-&gt;i_mmap
)paren
op_logical_and
op_logical_neg
(paren
id|page-&gt;mapping-&gt;i_mmap_shared
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
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)&t;&t;cpu_dcache_clean_entry((unsigned long)(_s))
multiline_comment|/*&n; * I cache coherency stuff.&n; *&n; * This *is not* just icache.  It is to make data written to memory&n; * consistent such that instructions fetched from the region are what&n; * we expect.&n; *&n; * This generally means that we have to clean out the Dcache and write&n; * buffers, and maybe flush the Icache in the specified range.&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(_s,_e)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_icache_invalidate_range((_s), (_e));&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * This function is misnamed IMHO.  There are three places where it&n; * is called, each of which is preceded immediately by a call to&n; * flush_page_to_ram:&n; *&n; *  1. kernel/ptrace.c:access_one_page&n; *     called after we have written to the kernel view of a user page.&n; *     The user page has been expundged from the cache by flush_cache_page.&n; *     [we don&squot;t need to do anything here if we add a call to&n; *      flush_dcache_page]&n; *&n; *  2. mm/memory.c:do_swap_page&n; *     called after we have (possibly) written to the kernel view of a&n; *     user page, which has previously been removed (ie, has been through&n; *     the swap cache).&n; *     [if the flush_page_to_ram() conditions are satisfied, then ok]&n; *&n; *  3. mm/memory.c:do_no_page&n; *     [if the flush_page_to_ram() conditions are satisfied, then ok]&n; *&n; * Invalidating the icache at the kernels virtual page isn&squot;t really&n; * going to do us much good, since we wouldn&squot;t have executed any&n; * instructions there.&n; */
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;do { } while (0)
multiline_comment|/*&n; * Old ARM MEMC stuff.  This supports the reversed mapping handling that&n; * we have on the older 26-bit machines.  We don&squot;t have a MEMC chip, so...&n; */
DECL|macro|memc_update_all
mdefine_line|#define memc_update_all()&t;&t;do { } while (0)
DECL|macro|memc_update_mm
mdefine_line|#define memc_update_mm(mm)&t;&t;do { } while (0)
DECL|macro|memc_update_addr
mdefine_line|#define memc_update_addr(mm,pte,log)&t;do { } while (0)
DECL|macro|memc_clear
mdefine_line|#define memc_clear(mm,physaddr)&t;&t;do { } while (0)
multiline_comment|/*&n; * TLB flushing.&n; *&n; *  - flush_tlb_all()&t;&t;&t;flushes all processes TLBs&n; *  - flush_tlb_mm(mm)&t;&t;&t;flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr)&t;flushes TLB for specified page&n; *  - flush_tlb_range(mm, start, end)&t;flushes TLB for specified range of pages&n; *&n; * We drain the write buffer in here to ensure that the page tables in ram&n; * are really up to date.  It is more efficient to do this here...&n; */
multiline_comment|/*&n; * Notes:&n; *  current-&gt;active_mm is the currently active memory description.&n; *  current-&gt;mm == NULL iff we are lazy.&n; */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_tlb_invalidate_all();&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Flush all user virtual address space translations described by `_mm&squot;.&n; *&n; * Currently, this is always called for current-&gt;mm, which should be&n; * the same as current-&gt;active_mm.  This is currently not be called for&n; * the lazy TLB case.&n; */
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(_mm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;active_mm)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_tlb_invalidate_all();&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Flush the specified range of user virtual address space translations.&n; *&n; * _mm may not be current-&gt;active_mm, but may not be NULL.&n; */
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(_mm,_start,_end)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;active_mm)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_tlb_invalidate_range((_start), (_end));&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Flush the specified user virtual address space translation.&n; */
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(_vma,_page)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;active_mm)&t;&t;&bslash;&n;&t;&t;&t;cpu_tlb_invalidate_page((_page),&t;&t;&bslash;&n;&t;&t;&t;&t; ((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&bslash;&n;&t;} while (0)
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
eof
