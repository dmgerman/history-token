macro_line|#ifndef _ASM_PGALLOC_H
DECL|macro|_ASM_PGALLOC_H
mdefine_line|#define _ASM_PGALLOC_H
multiline_comment|/* The usual comment is &quot;Caches aren&squot;t brain-dead on the &lt;architecture&gt;&quot;.&n; * Unfortunately, that doesn&squot;t apply to PA-RISC. */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/* Internal use D/I cache flushing routines... */
multiline_comment|/* XXX: these functions must not access memory between f[di]ce instructions. */
DECL|function|__flush_dcache_range
r_static
r_inline
r_void
id|__flush_dcache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
macro_line|#if 0
r_register
r_int
r_int
id|count
op_assign
(paren
id|size
op_div
id|L1_CACHE_BYTES
)paren
suffix:semicolon
r_register
r_int
r_int
id|loop
op_assign
id|cache_info.dc_loop
suffix:semicolon
r_register
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|64
op_star
l_int|1024
)paren
(brace
multiline_comment|/* Just punt and clear the whole damn thing */
id|flush_data_cache
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
comma
id|start
op_add_assign
id|L1_CACHE_BYTES
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|loop
suffix:semicolon
id|j
op_increment
)paren
(brace
id|fdce
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
macro_line|#else
id|flush_data_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|__flush_icache_range
r_static
r_inline
r_void
id|__flush_icache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
macro_line|#if 0
r_register
r_int
r_int
id|count
op_assign
(paren
id|size
op_div
id|L1_CACHE_BYTES
)paren
suffix:semicolon
r_register
r_int
r_int
id|loop
op_assign
id|cache_info.ic_loop
suffix:semicolon
r_register
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|64
op_star
l_int|1024
)paren
(brace
multiline_comment|/* Just punt and clear the whole damn thing */
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
comma
id|start
op_add_assign
id|L1_CACHE_BYTES
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|loop
suffix:semicolon
id|j
op_increment
)paren
(brace
id|fice
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
macro_line|#else
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_void
DECL|function|flush_kernel_dcache_range
id|flush_kernel_dcache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_register
r_int
r_int
id|end
op_assign
id|start
op_plus
id|size
suffix:semicolon
r_register
r_int
r_int
id|i
suffix:semicolon
id|start
op_and_assign
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
id|kernel_fdc
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;syncdma&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__flush_page_to_ram
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;flush_all_caches()
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(foo)&t;&t;&t;flush_all_caches()
macro_line|#if 0
multiline_comment|/* This is how I think the cache flushing should be done -- mrw */
r_extern
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
id|mm
op_eq
id|current-&gt;mm
)paren
(brace
id|flush_user_dcache_range
c_func
(paren
id|mm-&gt;start_data
comma
id|mm-&gt;end_data
)paren
suffix:semicolon
id|flush_user_icache_range
c_func
(paren
id|mm-&gt;start_code
comma
id|mm-&gt;end_code
)paren
suffix:semicolon
)brace
r_else
(brace
id|flush_other_dcache_range
c_func
(paren
id|mm-&gt;context
comma
id|mm-&gt;start_data
comma
id|mm-&gt;end_data
)paren
suffix:semicolon
id|flush_other_icache_range
c_func
(paren
id|mm-&gt;context
comma
id|mm-&gt;start_code
comma
id|mm-&gt;end_code
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end) do { &bslash;&n;                __flush_dcache_range(start, (unsigned long)end - (unsigned long)start); &bslash;&n;                __flush_icache_range(start, (unsigned long)end - (unsigned long)start); &bslash;&n;} while(0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr) do { &bslash;&n;                __flush_dcache_range(vmaddr, PAGE_SIZE); &bslash;&n;                __flush_icache_range(vmaddr, PAGE_SIZE); &bslash;&n;} while(0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&bslash;&n;        __flush_page_to_ram((unsigned long)page_address(page))
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end) &bslash;&n;        __flush_icache_range(start, end - start)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma, page, addr, len) &bslash;&n;&t;flush_icache_page((vma), (page))
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, page) &bslash;&n;&t;__flush_icache_range(page_address(page), PAGE_SIZE)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page) &bslash;&n;&t;__flush_dcache_range(page_address(page), PAGE_SIZE)
multiline_comment|/* TLB flushing routines.... */
r_extern
r_void
id|flush_data_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_instruction_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() do { &bslash;&n;        flush_data_tlb(); &bslash;&n;&t;flush_instruction_tlb(); &bslash;&n;} while(0);
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() &t;flush_tlb()&t;/* XXX p[id]tlb */
DECL|function|flush_tlb_pgtables
r_extern
id|__inline__
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
DECL|function|flush_instruction_tlb_range
r_static
r_inline
r_void
id|flush_instruction_tlb_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
macro_line|#if 0
r_register
r_int
r_int
id|count
op_assign
(paren
id|size
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
r_register
r_int
r_int
id|loop
op_assign
id|cache_info.it_loop
suffix:semicolon
r_register
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
comma
id|start
op_add_assign
id|PAGE_SIZE
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|loop
suffix:semicolon
id|j
op_increment
)paren
(brace
id|pitlbe
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
macro_line|#else
id|flush_instruction_tlb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|flush_data_tlb_range
r_static
r_inline
r_void
id|flush_data_tlb_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
macro_line|#if 0
r_register
r_int
r_int
id|count
op_assign
(paren
id|size
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
r_register
r_int
r_int
id|loop
op_assign
id|cache_info.dt_loop
suffix:semicolon
r_register
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
comma
id|start
op_add_assign
id|PAGE_SIZE
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|loop
suffix:semicolon
id|j
op_increment
)paren
(brace
id|pdtlbe
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
macro_line|#else
id|flush_data_tlb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|__flush_tlb_range
r_static
r_inline
r_void
id|__flush_tlb_range
c_func
(paren
r_int
r_int
id|space
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|old_sr1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
r_return
suffix:semicolon
)brace
id|old_sr1
op_assign
id|mfsp
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|mtsp
c_func
(paren
id|space
comma
l_int|1
)paren
suffix:semicolon
id|flush_data_tlb_range
c_func
(paren
id|start
comma
id|size
)paren
suffix:semicolon
id|flush_instruction_tlb_range
c_func
(paren
id|start
comma
id|size
)paren
suffix:semicolon
id|mtsp
c_func
(paren
id|old_sr1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__flush_tlb_space
c_func
(paren
r_int
r_int
id|space
)paren
suffix:semicolon
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
macro_line|#if 0
id|__flush_tlb_space
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
macro_line|#else
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|addr
)paren
(brace
id|__flush_tlb_range
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
id|addr
comma
id|PAGE_SIZE
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
id|__flush_tlb_range
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE: Many of the below macros use PT_NLEVELS because&n; *       it is convenient that PT_NLEVELS == LOG2(pte size in bytes),&n; *       i.e. we use 3 level page tables when we use 8 byte pte&squot;s&n; *       (for 64 bit) and 2 level page tables when we use 4 byte pte&squot;s&n; */
macro_line|#ifdef __LP64__
DECL|macro|PT_NLEVELS
mdefine_line|#define PT_NLEVELS 3
DECL|macro|PT_INITIAL
mdefine_line|#define PT_INITIAL 4 /* Number of initial page tables */
macro_line|#else
DECL|macro|PT_NLEVELS
mdefine_line|#define PT_NLEVELS 2
DECL|macro|PT_INITIAL
mdefine_line|#define PT_INITIAL 2 /* Number of initial page tables */
macro_line|#endif
multiline_comment|/* Definitions for 1st level */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT  (PAGE_SHIFT + (PT_NLEVELS - 1)*(PAGE_SHIFT - PT_NLEVELS))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    (1UL &lt;&lt; (PAGE_SHIFT - PT_NLEVELS))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
multiline_comment|/* Definitions for 2nd level */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       (PAGE_SHIFT + (PAGE_SHIFT - PT_NLEVELS))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
macro_line|#if PT_NLEVELS == 3
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    (1UL &lt;&lt; (PAGE_SHIFT - PT_NLEVELS))
macro_line|#else
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    1
macro_line|#endif
multiline_comment|/* Definitions for 3rd level */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    (1UL &lt;&lt; (PAGE_SHIFT - PT_NLEVELS))
DECL|macro|get_pgd_fast
mdefine_line|#define get_pgd_fast get_pgd_slow
DECL|macro|free_pgd_fast
mdefine_line|#define free_pgd_fast free_pgd_slow
DECL|function|get_pgd_slow
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|gateway_pgd_offset
suffix:semicolon
r_extern
r_int
r_int
id|gateway_pgd_entry
suffix:semicolon
id|pgd_t
op_star
id|ret
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|memset
(paren
id|ret
comma
l_int|0
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Install HP-UX and Linux gateway page translations */
id|pgd_val
c_func
(paren
op_star
(paren
id|ret
op_plus
id|gateway_pgd_offset
)paren
)paren
op_assign
id|gateway_pgd_entry
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_extern
id|__inline__
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
macro_line|#if PT_NLEVELS == 3
multiline_comment|/* Three Level Page Table Support for pmd&squot;s */
DECL|function|get_pmd_fast
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_fast
c_func
(paren
r_void
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* la la */
)brace
macro_line|#if 0
r_extern
id|__inline__
r_void
id|free_pmd_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
macro_line|#else
DECL|macro|free_pmd_fast
mdefine_line|#define free_pmd_fast free_pmd_slow
macro_line|#endif
DECL|function|get_pmd_slow
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_slow
c_func
(paren
r_void
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
)paren
id|clear_page
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_extern
id|__inline__
r_void
id|free_pmd_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__bad_pgd
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|function|pmd_alloc
r_extern
r_inline
id|pmd_t
op_star
id|pmd_alloc
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|getnew
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|fix
suffix:semicolon
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|address
suffix:semicolon
id|getnew
suffix:colon
(brace
id|pmd_t
op_star
id|page
op_assign
id|get_pmd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
id|page
op_assign
id|get_pmd_slow
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_else
id|free_pmd_fast
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|fix
suffix:colon
id|__bad_pgd
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Two Level Page Table Support for pmd&squot;s */
DECL|function|pmd_alloc
r_extern
r_inline
id|pmd_t
op_star
id|pmd_alloc
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
)brace
DECL|function|free_pmd_fast
r_extern
r_inline
r_void
id|free_pmd_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
macro_line|#endif
DECL|function|get_pte_fast
r_extern
id|__inline__
id|pte_t
op_star
id|get_pte_fast
c_func
(paren
r_void
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* la la */
)brace
macro_line|#if 0
r_extern
id|__inline__
r_void
id|free_pte_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
)brace
macro_line|#else
DECL|macro|free_pte_fast
mdefine_line|#define free_pte_fast free_pte_slow
macro_line|#endif
r_extern
id|pte_t
op_star
id|get_pte_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address_preadjusted
)paren
suffix:semicolon
DECL|function|free_pte_slow
r_extern
id|__inline__
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel&t;pmd_alloc
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel&t;pte_alloc
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(pte)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)           free_pmd_fast(pmd)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;&t;get_pgd_fast()
r_extern
r_void
id|__bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
DECL|function|pte_alloc
r_extern
r_inline
id|pte_t
op_star
id|pte_alloc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|getnew
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|fix
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
id|getnew
suffix:colon
(brace
id|pte_t
op_star
id|page
op_assign
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|fix
suffix:colon
id|__bad_pmd
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
