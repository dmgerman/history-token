multiline_comment|/*&n; *  linux/include/asm-arm/cacheflush.h&n; *&n; *  Copyright (C) 1999-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_CACHEFLUSH_H
DECL|macro|_ASMARM_CACHEFLUSH_H
mdefine_line|#define _ASMARM_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/glue.h&gt;
multiline_comment|/*&n; *&t;Cache Model&n; *&t;===========&n; */
DECL|macro|_CACHE
macro_line|#undef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#undef MULTI_CACHE
macro_line|#if defined(CONFIG_CPU_ARM610) || defined(CONFIG_CPU_ARM710)
macro_line|# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
macro_line|# else
DECL|macro|_CACHE
macro_line|#  define _CACHE v3
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM720T)
macro_line|# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
macro_line|# else
DECL|macro|_CACHE
macro_line|#  define _CACHE v4
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || &bslash;&n;    defined(CONFIG_CPU_ARM925T) || defined(CONFIG_CPU_ARM1020)
DECL|macro|MULTI_CACHE
macro_line|# define MULTI_CACHE 1
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM926T)
macro_line|# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
macro_line|# else
DECL|macro|_CACHE
macro_line|#  define _CACHE arm926
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SA110) || defined(CONFIG_CPU_SA1100)
macro_line|# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
macro_line|# else
DECL|macro|_CACHE
macro_line|#  define _CACHE v4wb
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
macro_line|# else
DECL|macro|_CACHE
macro_line|#  define _CACHE xscale
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_V6)
singleline_comment|//# ifdef _CACHE
DECL|macro|MULTI_CACHE
macro_line|#  define MULTI_CACHE 1
singleline_comment|//# else
singleline_comment|//#  define _CACHE v6
singleline_comment|//# endif
macro_line|#endif
macro_line|#if !defined(_CACHE) &amp;&amp; !defined(MULTI_CACHE)
macro_line|#error Unknown cache maintainence model
macro_line|#endif
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty PG_arch_1
multiline_comment|/*&n; *&t;MM Cache Management&n; *&t;===================&n; *&n; *&t;The arch/arm/mm/cache-*.S and arch/arm/mm/proc-*.S files&n; *&t;implement these methods.&n; *&n; *&t;Start addresses are inclusive and end addresses are exclusive;&n; *&t;start addresses should be rounded down, end addresses up.&n; *&n; *&t;See Documentation/cachetlb.txt for more information.&n; *&t;Please note that the implementation of these, and the required&n; *&t;effects are cache-type (VIVT/VIPT/PIPT) specific.&n; *&n; *&t;flush_cache_kern_all()&n; *&n; *&t;&t;Unconditionally clean and invalidate the entire cache.&n; *&n; *&t;flush_cache_user_mm(mm)&n; *&n; *&t;&t;Clean and invalidate all user space cache entries&n; *&t;&t;before a change of page tables.&n; *&n; *&t;flush_cache_user_range(start, end, flags)&n; *&n; *&t;&t;Clean and invalidate a range of cache entries in the&n; *&t;&t;specified address space before a change of page tables.&n; *&t;&t;- start - user start address (inclusive, page aligned)&n; *&t;&t;- end   - user end address   (exclusive, page aligned)&n; *&t;&t;- flags - vma-&gt;vm_flags field&n; *&n; *&t;coherent_kern_range(start, end)&n; *&n; *&t;&t;Ensure coherency between the Icache and the Dcache in the&n; *&t;&t;region described by start, end.  If you have non-snooping&n; *&t;&t;Harvard caches, you need to implement this function.&n; *&t;&t;- start  - virtual start address&n; *&t;&t;- end    - virtual end address&n; *&n; *&t;DMA Cache Coherency&n; *&t;===================&n; *&n; *&t;dma_inv_range(start, end)&n; *&n; *&t;&t;Invalidate (discard) the specified virtual address range.&n; *&t;&t;May not write back any entries.  If &squot;start&squot; or &squot;end&squot;&n; *&t;&t;are not cache line aligned, those lines must be written&n; *&t;&t;back.&n; *&t;&t;- start  - virtual start address&n; *&t;&t;- end    - virtual end address&n; *&n; *&t;dma_clean_range(start, end)&n; *&n; *&t;&t;Clean (write back) the specified virtual address range.&n; *&t;&t;- start  - virtual start address&n; *&t;&t;- end    - virtual end address&n; *&n; *&t;dma_flush_range(start, end)&n; *&n; *&t;&t;Clean and invalidate the specified virtual address range.&n; *&t;&t;- start  - virtual start address&n; *&t;&t;- end    - virtual end address&n; */
DECL|struct|cpu_cache_fns
r_struct
id|cpu_cache_fns
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
DECL|member|flush_user_all
r_void
(paren
op_star
id|flush_user_all
)paren
(paren
r_void
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
r_int
r_int
)paren
suffix:semicolon
DECL|member|coherent_kern_range
r_void
(paren
op_star
id|coherent_kern_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|coherent_user_range
r_void
(paren
op_star
id|coherent_user_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|flush_kern_dcache_page
r_void
(paren
op_star
id|flush_kern_dcache_page
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|dma_inv_range
r_void
(paren
op_star
id|dma_inv_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|dma_clean_range
r_void
(paren
op_star
id|dma_clean_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|dma_flush_range
r_void
(paren
op_star
id|dma_flush_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Select the calling method&n; */
macro_line|#ifdef MULTI_CACHE
r_extern
r_struct
id|cpu_cache_fns
id|cpu_cache
suffix:semicolon
DECL|macro|__cpuc_flush_kern_all
mdefine_line|#define __cpuc_flush_kern_all&t;&t;cpu_cache.flush_kern_all
DECL|macro|__cpuc_flush_user_all
mdefine_line|#define __cpuc_flush_user_all&t;&t;cpu_cache.flush_user_all
DECL|macro|__cpuc_flush_user_range
mdefine_line|#define __cpuc_flush_user_range&t;&t;cpu_cache.flush_user_range
DECL|macro|__cpuc_coherent_kern_range
mdefine_line|#define __cpuc_coherent_kern_range&t;cpu_cache.coherent_kern_range
DECL|macro|__cpuc_coherent_user_range
mdefine_line|#define __cpuc_coherent_user_range&t;cpu_cache.coherent_user_range
DECL|macro|__cpuc_flush_dcache_page
mdefine_line|#define __cpuc_flush_dcache_page&t;cpu_cache.flush_kern_dcache_page
multiline_comment|/*&n; * These are private to the dma-mapping API.  Do not use directly.&n; * Their sole purpose is to ensure that data held in the cache&n; * is visible to DMA, or data written by DMA to system memory is&n; * visible to the CPU.&n; */
DECL|macro|dmac_inv_range
mdefine_line|#define dmac_inv_range&t;&t;&t;cpu_cache.dma_inv_range
DECL|macro|dmac_clean_range
mdefine_line|#define dmac_clean_range&t;&t;cpu_cache.dma_clean_range
DECL|macro|dmac_flush_range
mdefine_line|#define dmac_flush_range&t;&t;cpu_cache.dma_flush_range
macro_line|#else
DECL|macro|__cpuc_flush_kern_all
mdefine_line|#define __cpuc_flush_kern_all&t;&t;__glue(_CACHE,_flush_kern_cache_all)
DECL|macro|__cpuc_flush_user_all
mdefine_line|#define __cpuc_flush_user_all&t;&t;__glue(_CACHE,_flush_user_cache_all)
DECL|macro|__cpuc_flush_user_range
mdefine_line|#define __cpuc_flush_user_range&t;&t;__glue(_CACHE,_flush_user_cache_range)
DECL|macro|__cpuc_coherent_kern_range
mdefine_line|#define __cpuc_coherent_kern_range&t;__glue(_CACHE,_coherent_kern_range)
DECL|macro|__cpuc_coherent_user_range
mdefine_line|#define __cpuc_coherent_user_range&t;__glue(_CACHE,_coherent_user_range)
DECL|macro|__cpuc_flush_dcache_page
mdefine_line|#define __cpuc_flush_dcache_page&t;__glue(_CACHE,_flush_kern_dcache_page)
r_extern
r_void
id|__cpuc_flush_kern_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cpuc_flush_user_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cpuc_flush_user_range
c_func
(paren
r_int
r_int
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
id|__cpuc_coherent_kern_range
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
id|__cpuc_coherent_user_range
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
id|__cpuc_flush_dcache_page
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * These are private to the dma-mapping API.  Do not use directly.&n; * Their sole purpose is to ensure that data held in the cache&n; * is visible to DMA, or data written by DMA to system memory is&n; * visible to the CPU.&n; */
DECL|macro|dmac_inv_range
mdefine_line|#define dmac_inv_range&t;&t;&t;__glue(_CACHE,_dma_inv_range)
DECL|macro|dmac_clean_range
mdefine_line|#define dmac_clean_range&t;&t;__glue(_CACHE,_dma_clean_range)
DECL|macro|dmac_flush_range
mdefine_line|#define dmac_flush_range&t;&t;__glue(_CACHE,_dma_flush_range)
r_extern
r_void
id|dmac_inv_range
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
id|dmac_clean_range
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
id|dmac_flush_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * flush_cache_vmap() is used when creating mappings (eg, via vmap,&n; * vmalloc, ioremap etc) in kernel space for pages.  Since the&n; * direct-mappings of these pages may contain cached data, we need&n; * to do a full cache flush to ensure that writebacks don&squot;t corrupt&n; * data placed into these pages via the new mappings.&n; */
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;flush_cache_all()
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;flush_cache_all()
multiline_comment|/*&n; * Copy user data from/to a page which is mapped into a different&n; * processes address space.  Really, we want to allow our &quot;user&n; * space&quot; model to handle this.&n; */
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_cache_page(vma, vaddr);&t;&bslash;&n;&t;&t;memcpy(dst, src, len);&t;&t;&bslash;&n;&t;&t;flush_dcache_page(page);&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_cache_page(vma, vaddr);&t;&bslash;&n;&t;&t;memcpy(dst, src, len);&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Convert calls to our calling convention.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;__cpuc_flush_kern_all()
DECL|function|flush_cache_mm
r_static
r_inline
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm-&gt;cpu_vm_mask
)paren
)paren
id|__cpuc_flush_user_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|flush_cache_range
id|flush_cache_range
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
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm-&gt;cpu_vm_mask
)paren
)paren
id|__cpuc_flush_user_range
c_func
(paren
id|start
op_amp
id|PAGE_MASK
comma
id|PAGE_ALIGN
c_func
(paren
id|end
)paren
comma
id|vma-&gt;vm_flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|flush_cache_page
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|user_addr
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm-&gt;cpu_vm_mask
)paren
)paren
(brace
r_int
r_int
id|addr
op_assign
id|user_addr
op_amp
id|PAGE_MASK
suffix:semicolon
id|__cpuc_flush_user_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
comma
id|vma-&gt;vm_flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * flush_cache_user_range is used when we want to ensure that the&n; * Harvard caches are synchronised for the user space address range.&n; * This is used for the ARM private sys_cacheflush system call.&n; */
DECL|macro|flush_cache_user_range
mdefine_line|#define flush_cache_user_range(vma,start,end) &bslash;&n;&t;__cpuc_coherent_user_range((start) &amp; PAGE_MASK, PAGE_ALIGN(end))
multiline_comment|/*&n; * Perform necessary cache operations to ensure that data previously&n; * stored within this range of addresses can be executed by the CPU.&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(s,e)&t;&t;__cpuc_coherent_kern_range(s,e)
multiline_comment|/*&n; * Perform necessary cache operations to ensure that the TLB will&n; * see data written in the specified area.&n; */
DECL|macro|clean_dcache_area
mdefine_line|#define clean_dcache_area(start,size)&t;cpu_dcache_clean_area(start, size)
multiline_comment|/*&n; * flush_dcache_page is used when the kernel has written to the page&n; * cache page at virtual address page-&gt;virtual.&n; *&n; * If this page isn&squot;t mapped (ie, page_mapping == NULL), or it might&n; * have userspace mappings, then we _must_ always clean + invalidate&n; * the dcache entries associated with the kernel mapping.&n; *&n; * Otherwise we can defer the operation, and clean the cache when we are&n; * about to change to user space.  This is the same method as used on SPARC64.&n; * See update_mmu_cache for the user space part.&n; */
r_extern
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|macro|flush_dcache_mmap_lock
mdefine_line|#define flush_dcache_mmap_lock(mapping) &bslash;&n;&t;spin_lock_irq(&amp;(mapping)-&gt;tree_lock)
DECL|macro|flush_dcache_mmap_unlock
mdefine_line|#define flush_dcache_mmap_unlock(mapping) &bslash;&n;&t;spin_unlock_irq(&amp;(mapping)-&gt;tree_lock)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,page,addr,len) &bslash;&n;&t;flush_dcache_page(page)
multiline_comment|/*&n; * We don&squot;t appear to need to do anything here.  In fact, if we did, we&squot;d&n; * duplicate cache flushing elsewhere performed by flush_dcache_page().&n; */
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;do { } while (0)
DECL|macro|__cacheid_present
mdefine_line|#define __cacheid_present(val)&t;&t;(val != read_cpuid(CPUID_ID))
DECL|macro|__cacheid_vivt
mdefine_line|#define __cacheid_vivt(val)&t;&t;((val &amp; (15 &lt;&lt; 25)) != (14 &lt;&lt; 25))
DECL|macro|__cacheid_vipt
mdefine_line|#define __cacheid_vipt(val)&t;&t;((val &amp; (15 &lt;&lt; 25)) == (14 &lt;&lt; 25))
DECL|macro|__cacheid_vipt_nonaliasing
mdefine_line|#define __cacheid_vipt_nonaliasing(val)&t;((val &amp; (15 &lt;&lt; 25 | 1 &lt;&lt; 23)) == (14 &lt;&lt; 25))
DECL|macro|__cacheid_vipt_aliasing
mdefine_line|#define __cacheid_vipt_aliasing(val)&t;((val &amp; (15 &lt;&lt; 25 | 1 &lt;&lt; 23)) == (14 &lt;&lt; 25 | 1 &lt;&lt; 23))
macro_line|#if defined(CONFIG_CPU_CACHE_VIVT) &amp;&amp; !defined(CONFIG_CPU_CACHE_VIPT)
DECL|macro|cache_is_vivt
mdefine_line|#define cache_is_vivt()&t;&t;&t;1
DECL|macro|cache_is_vipt
mdefine_line|#define cache_is_vipt()&t;&t;&t;0
DECL|macro|cache_is_vipt_nonaliasing
mdefine_line|#define cache_is_vipt_nonaliasing()&t;0
DECL|macro|cache_is_vipt_aliasing
mdefine_line|#define cache_is_vipt_aliasing()&t;0
macro_line|#elif defined(CONFIG_CPU_CACHE_VIPT)
DECL|macro|cache_is_vivt
mdefine_line|#define cache_is_vivt()&t;&t;&t;0
DECL|macro|cache_is_vipt
mdefine_line|#define cache_is_vipt()&t;&t;&t;1
DECL|macro|cache_is_vipt_nonaliasing
mdefine_line|#define cache_is_vipt_nonaliasing()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;__cacheid_vipt_nonaliasing(__val);&t;&t;&t;&bslash;&n;&t;})
DECL|macro|cache_is_vipt_aliasing
mdefine_line|#define cache_is_vipt_aliasing()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;__cacheid_vipt_aliasing(__val);&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#else
DECL|macro|cache_is_vivt
mdefine_line|#define cache_is_vivt()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;(!__cacheid_present(__val)) || __cacheid_vivt(__val);&t;&bslash;&n;&t;})
DECL|macro|cache_is_vipt
mdefine_line|#define cache_is_vipt()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;__cacheid_present(__val) &amp;&amp; __cacheid_vipt(__val);&t;&bslash;&n;&t;})
DECL|macro|cache_is_vipt_nonaliasing
mdefine_line|#define cache_is_vipt_nonaliasing()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;__cacheid_present(__val) &amp;&amp;&t;&t;&t;&t;&bslash;&n;&t;&t; __cacheid_vipt_nonaliasing(__val);&t;&t;&t;&bslash;&n;&t;})
DECL|macro|cache_is_vipt_aliasing
mdefine_line|#define cache_is_vipt_aliasing()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = read_cpuid(CPUID_CACHETYPE);&t;&bslash;&n;&t;&t;__cacheid_present(__val) &amp;&amp;&t;&t;&t;&t;&bslash;&n;&t;&t; __cacheid_vipt_aliasing(__val);&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif
macro_line|#endif
eof
