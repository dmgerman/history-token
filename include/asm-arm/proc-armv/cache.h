multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/cache.h&n; *&n; *  Copyright (C) 1999-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/mman.h&gt;
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
multiline_comment|/*&n; * This flushes back any buffered write data.  We have to clean the entries&n; * in the cache for this page.  This does not invalidate either I or D caches.&n; */
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
multiline_comment|/*&n; * FIXME: We currently clean the dcache for this page.  Should we&n; * also invalidate the Dcache?  And what about the Icache? -- rmk&n; */
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;cpu_dcache_clean_page(page_address(page))
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)&t;&t;cpu_dcache_clean_entry((unsigned long)(_s))
multiline_comment|/*&n; * I cache only&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(_s,_e)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_icache_invalidate_range((_s), (_e));&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((vma)-&gt;vm_flags &amp; PROT_EXEC)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_icache_invalidate_page(page_address(pg));&t;&bslash;&n;&t;} while (0)
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
eof
