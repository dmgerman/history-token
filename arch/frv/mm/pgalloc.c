multiline_comment|/* pgalloc.c: page directory &amp; page table allocation&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|variable|pgd_cache
id|kmem_cache_t
op_star
id|pgd_cache
suffix:semicolon
DECL|function|pte_alloc_one_kernel
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
(brace
id|pte_t
op_star
id|pte
op_assign
(paren
id|pte_t
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
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_alloc_one
r_struct
id|page
op_star
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
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHPTE
id|page
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
op_or
id|__GFP_REPEAT
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|page
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|page
)paren
id|clear_highpage
c_func
(paren
id|page
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|__set_pmd
r_void
id|__set_pmd
c_func
(paren
id|pmd_t
op_star
id|pmdptr
comma
r_int
r_int
id|pmd
)paren
(brace
r_int
r_int
op_star
id|__ste_p
op_assign
id|pmdptr-&gt;ste
suffix:semicolon
r_int
id|loop
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
(brace
id|memset
c_func
(paren
id|__ste_p
comma
l_int|0
comma
id|PME_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|BUG_ON
c_func
(paren
id|pmd
op_amp
(paren
l_int|0x3f00
op_or
id|xAMPRx_SS
op_or
l_int|0xe
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
id|PME_SIZE
suffix:semicolon
id|loop
OG
l_int|0
suffix:semicolon
id|loop
op_sub_assign
l_int|4
)paren
(brace
op_star
id|__ste_p
op_increment
op_assign
id|pmd
suffix:semicolon
id|pmd
op_add_assign
id|__frv_PT_SIZE
suffix:semicolon
)brace
)brace
id|frv_dcache_writeback
c_func
(paren
(paren
r_int
r_int
)paren
id|pmdptr
comma
(paren
r_int
r_int
)paren
(paren
id|pmdptr
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * List of all pgd&squot;s needed for non-PAE so it can invalidate entries&n; * in both cached and uncached pgd&squot;s; not needed for PAE since the&n; * kernel pmd is shared. If PAE were not to share the pmd a similar&n; * tactic would be needed. This is essentially codepath-based locking&n; * against pageattr.c; it is the unique case in which a valid change&n; * of kernel pagetables can&squot;t be lazily synchronized by vmalloc faults.&n; * vmalloc faults work because attached pagetables are never freed.&n; * If the locking proves to be non-performant, a ticketing scheme with&n; * checks at dup_mmap(), exec(), and other mmlist addition points&n; * could be used. The locking scheme was chosen on the basis of&n; * manfred&squot;s recommendations and having no core impact whatsoever.&n; * -- wli&n; */
DECL|variable|pgd_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|pgd_lock
)paren
suffix:semicolon
DECL|variable|pgd_list
r_struct
id|page
op_star
id|pgd_list
suffix:semicolon
DECL|function|pgd_list_add
r_static
r_inline
r_void
id|pgd_list_add
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
id|page-&gt;index
op_assign
(paren
r_int
r_int
)paren
id|pgd_list
suffix:semicolon
r_if
c_cond
(paren
id|pgd_list
)paren
id|pgd_list
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
op_amp
id|page-&gt;index
suffix:semicolon
id|pgd_list
op_assign
id|page
suffix:semicolon
id|page
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
op_amp
id|pgd_list
suffix:semicolon
)brace
DECL|function|pgd_list_del
r_static
r_inline
r_void
id|pgd_list_del
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
id|next
comma
op_star
op_star
id|pprev
comma
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|next
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page-&gt;index
suffix:semicolon
id|pprev
op_assign
(paren
r_struct
id|page
op_star
op_star
)paren
id|page
op_member_access_from_pointer
r_private
suffix:semicolon
op_star
id|pprev
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
id|next
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
id|pprev
suffix:semicolon
)brace
DECL|function|pgd_ctor
r_void
id|pgd_ctor
c_func
(paren
r_void
op_star
id|pgd
comma
id|kmem_cache_t
op_star
id|cache
comma
r_int
r_int
id|unused
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|PTRS_PER_PMD
op_eq
l_int|1
)paren
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
id|pgd_t
op_star
)paren
id|pgd
op_plus
id|USER_PGDS_IN_LAST_PML4
comma
id|swapper_pg_dir
op_plus
id|USER_PGDS_IN_LAST_PML4
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PGDS_IN_LAST_PML4
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PTRS_PER_PMD
OG
l_int|1
)paren
r_return
suffix:semicolon
id|pgd_list_add
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pgd
comma
l_int|0
comma
id|USER_PGDS_IN_LAST_PML4
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* never called when PTRS_PER_PMD &gt; 1 */
DECL|function|pgd_dtor
r_void
id|pgd_dtor
c_func
(paren
r_void
op_star
id|pgd
comma
id|kmem_cache_t
op_star
id|cache
comma
r_int
r_int
id|unused
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* can be called from interrupt context */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|pgd_list_del
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pgd_alloc
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
id|kmem_cache_alloc
c_func
(paren
id|pgd_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
r_return
id|pgd
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
DECL|function|pgd_free
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
multiline_comment|/* in the non-PAE case, clear_page_tables() clears user pgd entries */
id|kmem_cache_free
c_func
(paren
id|pgd_cache
comma
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pgtable_cache_init
r_void
id|__init
id|pgtable_cache_init
c_func
(paren
r_void
)paren
(brace
id|pgd_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;pgd&quot;
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
comma
l_int|0
comma
id|pgd_ctor
comma
id|pgd_dtor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_cache
)paren
id|panic
c_func
(paren
l_string|&quot;pgtable_cache_init(): Cannot create pgd cache&quot;
)paren
suffix:semicolon
)brace
eof
