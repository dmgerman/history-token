multiline_comment|/*&n; *  linux/include/asm-arm/pgalloc.h&n; *&n; *  Copyright (C) 2000-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGALLOC_H
DECL|macro|_ASMARM_PGALLOC_H
mdefine_line|#define _ASMARM_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Get the cache handling stuff now.&n; */
macro_line|#include &lt;asm/proc/cache.h&gt;
multiline_comment|/*&n; * ARM processors do not cache TLB tables in RAM.&n; */
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm,start,end)&t;do { } while (0)
multiline_comment|/*&n; * Processor specific parts...&n; */
macro_line|#include &lt;asm/proc/pgalloc.h&gt;
multiline_comment|/*&n; * Page table cache stuff&n; */
macro_line|#ifndef CONFIG_NO_PGT_CACHE
macro_line|#ifdef CONFIG_SMP
macro_line|#error Pgtable caches have to be per-CPU, so that no locking is needed.
macro_line|#endif&t;/* CONFIG_SMP */
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
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|quicklists
suffix:semicolon
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;(quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(quicklists.pgtable_cache_sz)
multiline_comment|/* used for quicklists */
DECL|macro|__pgd_next
mdefine_line|#define __pgd_next(pgd) (((unsigned long *)pgd)[1])
DECL|macro|__pte_next
mdefine_line|#define __pte_next(pte)&t;(((unsigned long *)pte)[0])
DECL|function|get_pgd_fast
r_static
r_inline
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
id|__pgd_next
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|1
)braket
op_assign
id|ret
(braket
l_int|2
)braket
suffix:semicolon
id|clean_dcache_entry
c_func
(paren
id|ret
op_plus
l_int|1
)paren
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_static
r_inline
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|__pgd_next
c_func
(paren
id|pgd
)paren
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
)brace
DECL|function|pte_alloc_one_fast
r_static
r_inline
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
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pte_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|__pte_next
c_func
(paren
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
id|clean_dcache_entry
c_func
(paren
id|ret
)paren
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
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
r_inline
r_void
id|free_pte_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|__pte_next
c_func
(paren
id|pte
)paren
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
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
)brace
macro_line|#else&t;/* CONFIG_NO_PGT_CACHE */
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;&t;((unsigned long *)0)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;&t;((unsigned long *)0)
DECL|macro|get_pgd_fast
mdefine_line|#define get_pgd_fast()&t;&t;&t;((pgd_t *)0)
DECL|macro|pte_alloc_one_fast
mdefine_line|#define pte_alloc_one_fast(mm,addr)&t;((pte_t *)0)
DECL|macro|free_pgd_fast
mdefine_line|#define free_pgd_fast(pgd)&t;&t;free_pgd_slow(pgd)
DECL|macro|free_pte_fast
mdefine_line|#define free_pte_fast(pte)&t;&t;pte_free_slow(pte)
macro_line|#endif&t;/* CONFIG_NO_PGT_CACHE */
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;&t;free_pte_fast(pte)
multiline_comment|/*&n; * Since we have only two-level page tables, these are trivial&n; */
DECL|macro|pmd_alloc_one_fast
mdefine_line|#define pmd_alloc_one_fast(mm,addr)&t;({ BUG(); ((pmd_t *)1); })
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm,addr)&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free_slow
mdefine_line|#define pmd_free_slow(pmd)&t;&t;do { } while (0)
DECL|macro|pmd_free_fast
mdefine_line|#define pmd_free_fast(pmd)&t;&t;do { } while (0)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm,pmd,pte)&t;BUG()
r_extern
id|pgd_t
op_star
id|get_pgd_slow
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
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|function|pgd_alloc
r_static
r_inline
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pgd
op_assign
id|get_pgd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
id|pgd
op_assign
id|get_pgd_slow
c_func
(paren
id|mm
)paren
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;&t;free_pgd_fast(pgd)
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
