macro_line|#ifndef _M68K_PGTABLE_H
DECL|macro|_M68K_PGTABLE_H
mdefine_line|#define _M68K_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the m68k page table tree.&n; */
macro_line|#include &lt;asm/virtconvert.h&gt;
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)&t;&t;&t;&t;&t;&bslash;&n;&t;do{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*(pteptr) = (pteval);&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
macro_line|#ifdef CONFIG_SUN3
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       17
macro_line|#else
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
macro_line|#endif
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
macro_line|#ifdef CONFIG_SUN3
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     17
macro_line|#else
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;25
macro_line|#endif
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the m68k is configured as three-level,&n; * so we do have PMD level physically.&n; */
macro_line|#ifdef CONFIG_SUN3
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE   16
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD   1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD   2048
macro_line|#else
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;8
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;128
macro_line|#endif
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
multiline_comment|/* Virtual address region for use by kernel_map() */
macro_line|#ifdef CONFIG_SUN3
DECL|macro|KMAP_START
mdefine_line|#define KMAP_START     0x0DC00000
DECL|macro|KMAP_END
mdefine_line|#define KMAP_END       0x0E000000
macro_line|#else
DECL|macro|KMAP_START
mdefine_line|#define&t;KMAP_START&t;0xd0000000
DECL|macro|KMAP_END
mdefine_line|#define&t;KMAP_END&t;0xf0000000
macro_line|#endif
macro_line|#ifndef CONFIG_SUN3
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START (((unsigned long) high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END KMAP_START
macro_line|#else
r_extern
r_int
r_int
id|vmalloc_end
suffix:semicolon
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START 0x0f800000
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END vmalloc_end
macro_line|#endif /* CONFIG_SUN3 */
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_void
op_star
id|empty_zero_page
suffix:semicolon
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(virt_to_page(empty_zero_page))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;       2
multiline_comment|/*&n; * Check if the addr/len goes up to the end of a physical&n; * memory chunk.  Used for DMA functions.&n; */
macro_line|#ifdef CONFIG_SINGLE_MEMORY_CHUNK
multiline_comment|/*&n; * It makes no sense to consider whether we cross a memory boundary if&n; * we support just one physical chunk of memory.&n; */
DECL|function|mm_end_of_chunk
r_static
r_inline
r_int
id|mm_end_of_chunk
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|kernel_set_cachemode
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|cmode
)paren
suffix:semicolon
multiline_comment|/*&n; * The m68k doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.  The Sun3 does, but&n; * they are updated on demand.&n; */
DECL|function|update_mmu_cache
r_static
r_inline
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
id|address
comma
id|pte_t
id|pte
)paren
(brace
)brace
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
multiline_comment|/* MMU-specific headers */
macro_line|#ifdef CONFIG_SUN3
macro_line|#include &lt;asm/sun3_pgtable.h&gt;
macro_line|#else
macro_line|#include &lt;asm/motorola_pgtable.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * Macro to mark a page protection value as &quot;uncacheable&quot;.&n; */
macro_line|#ifdef SUN3_PAGE_NOCACHE
DECL|macro|__SUN3_PAGE_NOCACHE
macro_line|# define __SUN3_PAGE_NOCACHE&t;SUN3_PAGE_NOCACHE
macro_line|#else
DECL|macro|__SUN3_PAGE_NOCACHE
macro_line|# define __SUN3_PAGE_NOCACHE&t;0
macro_line|#endif
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(MMU_IS_SUN3&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; ? (__pgprot(pgprot_val(prot) | __SUN3_PAGE_NOCACHE))&t;&t;&t;&bslash;&n;&t; : ((MMU_IS_851 || MMU_IS_030)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    ? (__pgprot(pgprot_val(prot) | _PAGE_NOCACHE030))&t;&t;&t;&bslash;&n;&t;    : (MMU_IS_040 || MMU_IS_060)&t;&t;&t;&t;&t;&bslash;&n;&t;    ? (__pgprot((pgprot_val(prot) &amp; _CACHEMASK040) | _PAGE_NOCACHE_S))&t;&bslash;&n;&t;    : (prot)))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif /* _M68K_PGTABLE_H */
eof
