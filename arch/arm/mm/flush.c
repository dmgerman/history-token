multiline_comment|/*&n; *  linux/arch/arm/mm/flush.c&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|function|__flush_dcache_page
r_static
r_void
id|__flush_dcache_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;active_mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
r_struct
id|prio_tree_iter
id|iter
suffix:semicolon
id|pgoff_t
id|pgoff
suffix:semicolon
id|__cpuc_flush_dcache_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * With a VIVT cache, we need to also write back&n;&t; * and invalidate any user data.&n;&t; */
id|pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|flush_dcache_mmap_lock
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|vma_prio_tree_foreach
c_func
(paren
id|mpnt
comma
op_amp
id|iter
comma
op_amp
id|mapping-&gt;i_mmap
comma
id|pgoff
comma
id|pgoff
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this VMA is not in our MM, we can ignore it.&n;&t;&t; */
r_if
c_cond
(paren
id|mpnt-&gt;vm_mm
op_ne
id|mm
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mpnt-&gt;vm_flags
op_amp
id|VM_MAYSHARE
)paren
)paren
r_continue
suffix:semicolon
id|offset
op_assign
(paren
id|pgoff
op_minus
id|mpnt-&gt;vm_pgoff
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|mpnt
comma
id|mpnt-&gt;vm_start
op_plus
id|offset
)paren
suffix:semicolon
)brace
id|flush_dcache_mmap_unlock
c_func
(paren
id|mapping
)paren
suffix:semicolon
)brace
DECL|function|flush_dcache_page
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
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page_mapping
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapping
op_logical_and
op_logical_neg
id|mapping_mapped
c_func
(paren
id|mapping
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
id|__flush_dcache_page
c_func
(paren
id|mapping
comma
id|page
)paren
suffix:semicolon
)brace
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
eof
