multiline_comment|/*&n; *  linux/arch/arm/mm/minicache.c&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This handles the mini data cache, as found on SA11x0 and XScale&n; * processors.  When we copy a user page page, we map it in such a way&n; * that accesses to this page will not touch the main data cache, but&n; * will be cached in the mini data cache.  This prevents us thrashing&n; * the main data cache on page faults.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * 0xffff8000 to 0xffffffff is reserved for any ARM architecture&n; * specific hacks for copying pages efficiently.&n; */
DECL|macro|minicache_address
mdefine_line|#define minicache_address (0xffff8000)
DECL|macro|minicache_pgprot
mdefine_line|#define minicache_pgprot __pgprot(L_PTE_PRESENT | L_PTE_YOUNG | &bslash;&n;&t;&t;&t;&t;  L_PTE_CACHEABLE)
DECL|variable|minicache_pte
r_static
id|pte_t
op_star
id|minicache_pte
suffix:semicolon
multiline_comment|/*&n; * Note that this is intended to be called only from the copy_user_page&n; * asm code; anything else will require special locking to prevent the&n; * mini-cache space being re-used.  (Note: probably preempt unsafe).&n; *&n; * We rely on the fact that the minicache is 2K, and we&squot;ll be pushing&n; * 4K of data through it, so we don&squot;t actually have to specifically&n; * flush the minicache when we change the mapping.&n; *&n; * Note also: assert(PAGE_OFFSET &lt;= virt &lt; high_memory).&n; * Unsafe: preempt, kmap.&n; */
DECL|function|map_page_minicache
r_int
r_int
id|map_page_minicache
c_func
(paren
r_int
r_int
id|virt
)paren
(brace
id|set_pte
c_func
(paren
id|minicache_pte
comma
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|virt
)paren
op_rshift
id|PAGE_SHIFT
comma
id|minicache_pgprot
)paren
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|minicache_address
)paren
suffix:semicolon
r_return
id|minicache_address
suffix:semicolon
)brace
DECL|function|minicache_init
r_static
r_int
id|__init
id|minicache_init
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|minicache_address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|minicache_address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|minicache_pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|minicache_address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minicache_pte
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|minicache_init
id|core_initcall
c_func
(paren
id|minicache_init
)paren
suffix:semicolon
eof
