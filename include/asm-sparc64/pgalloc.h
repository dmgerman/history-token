multiline_comment|/* $Id: pgalloc.h,v 1.30 2001/12/21 04:56:17 davem Exp $ */
macro_line|#ifndef _SPARC64_PGALLOC_H
DECL|macro|_SPARC64_PGALLOC_H
mdefine_line|#define _SPARC64_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cpudata.h&gt;
multiline_comment|/* Page table allocation/freeing. */
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Sliiiicck */
DECL|macro|pgt_quicklists
mdefine_line|#define pgt_quicklists&t;cpu_data(smp_processor_id())
macro_line|#else
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pgcache_size
r_int
r_int
id|pgcache_size
suffix:semicolon
DECL|member|pgdcache_size
r_int
r_int
id|pgdcache_size
suffix:semicolon
)brace
id|pgt_quicklists
suffix:semicolon
macro_line|#endif
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(pgt_quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;(pgt_quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(pgt_quicklists.pgcache_size)
DECL|macro|pgd_cache_size
mdefine_line|#define pgd_cache_size&t;&t;(pgt_quicklists.pgdcache_size)
macro_line|#ifndef CONFIG_SMP
DECL|function|free_pgd_fast
r_static
id|__inline__
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;lru.prev
)paren
(brace
id|page-&gt;lru.next
op_assign
(paren
r_void
op_star
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
)brace
id|page-&gt;lru.prev
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|page-&gt;lru.prev
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|pgd
op_amp
(paren
id|PAGE_SIZE
op_div
l_int|2
)paren
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
)paren
suffix:semicolon
id|pgd_cache_size
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_pgd_fast
r_static
id|__inline__
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_struct
id|page
op_star
id|ret
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_struct
id|page
op_star
)paren
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|mask
op_assign
(paren
r_int
r_int
)paren
id|ret-&gt;lru.prev
suffix:semicolon
r_int
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|mask
op_and_assign
op_complement
l_int|1
suffix:semicolon
r_else
(brace
id|off
op_assign
id|PAGE_SIZE
op_div
l_int|2
suffix:semicolon
id|mask
op_and_assign
op_complement
l_int|2
suffix:semicolon
)brace
id|ret-&gt;lru.prev
op_assign
(paren
r_void
op_star
)paren
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|ret-&gt;lru.next
suffix:semicolon
id|ret
op_assign
(paren
r_struct
id|page
op_star
)paren
(paren
id|__page_address
c_func
(paren
id|ret
)paren
op_plus
id|off
)paren
suffix:semicolon
id|pgd_cache_size
op_decrement
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|ret
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
id|page-&gt;lru.prev
op_assign
(paren
r_void
op_star
)paren
l_int|2UL
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|page-&gt;lru.next
op_assign
(paren
r_void
op_star
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
id|pgd_cache_size
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SMP */
DECL|function|free_pgd_fast
r_static
id|__inline__
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
op_assign
(paren
r_int
r_int
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_pgd_fast
r_static
id|__inline__
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_static
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
macro_line|#endif /* CONFIG_SMP */
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;&t;/* is there D$ aliasing problem */
DECL|macro|VPTE_COLOR
mdefine_line|#define VPTE_COLOR(address)&t;&t;(((address) &gt;&gt; (PAGE_SHIFT + 10)) &amp; 1UL)
DECL|macro|DCACHE_COLOR
mdefine_line|#define DCACHE_COLOR(address)&t;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; 1UL)
macro_line|#else
DECL|macro|VPTE_COLOR
mdefine_line|#define VPTE_COLOR(address)&t;&t;0
DECL|macro|DCACHE_COLOR
mdefine_line|#define DCACHE_COLOR(address)&t;&t;0
macro_line|#endif
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(MM, PGD, PMD)&t;pgd_set(PGD, PMD)
DECL|function|pmd_alloc_one_fast
r_static
id|__inline__
id|pmd_t
op_star
id|pmd_alloc_one_fast
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_int
id|color
op_assign
l_int|0
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_quicklist
(braket
id|color
)braket
op_eq
l_int|NULL
)paren
id|color
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
(braket
id|color
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
(braket
id|color
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pmd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|pmd_alloc_one
r_static
id|__inline__
id|pmd_t
op_star
id|pmd_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc_one_fast
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
(brace
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
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
)paren
id|memset
c_func
(paren
id|pmd
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_return
id|pmd
suffix:semicolon
)brace
DECL|function|free_pmd_fast
r_static
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
r_int
r_int
id|color
op_assign
id|DCACHE_COLOR
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|pmd
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
(braket
id|color
)braket
suffix:semicolon
id|pte_quicklist
(braket
id|color
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_static
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
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(MM, PMD, PTE)&t;pmd_set(PMD, PTE)
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(MM,PMD,PTE_PAGE)&t;&t;&bslash;&n;&t;pmd_populate_kernel(MM,PMD,page_address(PTE_PAGE))
r_extern
id|pte_t
op_star
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_inline
r_struct
id|page
op_star
DECL|function|pte_alloc_one
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_one_kernel
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
r_return
id|virt_to_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pte_alloc_one_fast
r_static
id|__inline__
id|pte_t
op_star
id|pte_alloc_one_fast
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|color
op_assign
id|VPTE_COLOR
c_func
(paren
id|address
)paren
suffix:semicolon
r_int
r_int
op_star
id|ret
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
(braket
id|color
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
(braket
id|color
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pte_fast
r_static
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
r_int
r_int
id|color
op_assign
id|DCACHE_COLOR
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
(braket
id|color
)braket
suffix:semicolon
id|pte_quicklist
(braket
id|color
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|free_pte_slow
r_static
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
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(page_address(pte))
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;free_pmd_fast(pmd)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;&t;get_pgd_fast()
macro_line|#endif /* _SPARC64_PGALLOC_H */
eof
