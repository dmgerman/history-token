multiline_comment|/*&n; *  linux/arch/arm/mm/copypage-v6.c&n; *&n; *  Copyright (C) 2002 Deep Blue Solutions Ltd, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/shmparam.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#if SHMLBA &gt; 16384
macro_line|#error FIX ME
macro_line|#endif
DECL|macro|from_address
mdefine_line|#define from_address&t;(0xffff8000)
DECL|macro|from_pgprot
mdefine_line|#define from_pgprot&t;PAGE_KERNEL
DECL|macro|to_address
mdefine_line|#define to_address&t;(0xffffc000)
DECL|macro|to_pgprot
mdefine_line|#define to_pgprot&t;PAGE_KERNEL
DECL|variable|from_pte
r_static
id|pte_t
op_star
id|from_pte
suffix:semicolon
DECL|variable|to_pte
r_static
id|pte_t
op_star
id|to_pte
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|v6_lock
)paren
suffix:semicolon
DECL|macro|DCACHE_COLOUR
mdefine_line|#define DCACHE_COLOUR(vaddr) ((vaddr &amp; (SHMLBA - 1)) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Copy the user page.  No aliasing to deal with so we can just&n; * attack the kernel&squot;s existing mapping of these pages.&n; */
DECL|function|v6_copy_user_page_nonaliasing
r_void
id|v6_copy_user_page_nonaliasing
c_func
(paren
r_void
op_star
id|kto
comma
r_const
r_void
op_star
id|kfrom
comma
r_int
r_int
id|vaddr
)paren
(brace
id|copy_page
c_func
(paren
id|kto
comma
id|kfrom
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the user page.  No aliasing to deal with so we can just&n; * attack the kernel&squot;s existing mapping of this page.&n; */
DECL|function|v6_clear_user_page_nonaliasing
r_void
id|v6_clear_user_page_nonaliasing
c_func
(paren
r_void
op_star
id|kaddr
comma
r_int
r_int
id|vaddr
)paren
(brace
id|clear_page
c_func
(paren
id|kaddr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy the page, taking account of the cache colour.&n; */
DECL|function|v6_copy_user_page_aliasing
r_void
id|v6_copy_user_page_aliasing
c_func
(paren
r_void
op_star
id|kto
comma
r_const
r_void
op_star
id|kfrom
comma
r_int
r_int
id|vaddr
)paren
(brace
r_int
r_int
id|offset
op_assign
id|DCACHE_COLOUR
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_int
r_int
id|from
comma
id|to
suffix:semicolon
multiline_comment|/*&n;&t; * Discard data in the kernel mapping for the new page.&n;&t; * FIXME: needs this MCRR to be supported.&n;&t; */
id|__asm__
c_func
(paren
l_string|&quot;mcrr&t;p15, 0, %1, %0, c6&t;@ 0xec401f06&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kto
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
id|kto
op_plus
id|PAGE_SIZE
op_minus
id|L1_CACHE_BYTES
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now copy the page using the same cache colour as the&n;&t; * pages ultimate destination.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|v6_lock
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|from_pte
op_plus
id|offset
comma
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|kfrom
)paren
op_rshift
id|PAGE_SHIFT
comma
id|from_pgprot
)paren
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|to_pte
op_plus
id|offset
comma
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|kto
)paren
op_rshift
id|PAGE_SHIFT
comma
id|to_pgprot
)paren
)paren
suffix:semicolon
id|from
op_assign
id|from_address
op_plus
(paren
id|offset
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|to
op_assign
id|to_address
op_plus
(paren
id|offset
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|from
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|to
)paren
suffix:semicolon
id|copy_page
c_func
(paren
(paren
r_void
op_star
)paren
id|to
comma
(paren
r_void
op_star
)paren
id|from
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|v6_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the user page.  We need to deal with the aliasing issues,&n; * so remap the kernel page into the same cache colour as the user&n; * page.&n; */
DECL|function|v6_clear_user_page_aliasing
r_void
id|v6_clear_user_page_aliasing
c_func
(paren
r_void
op_star
id|kaddr
comma
r_int
r_int
id|vaddr
)paren
(brace
r_int
r_int
id|offset
op_assign
id|DCACHE_COLOUR
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_int
r_int
id|to
op_assign
id|to_address
op_plus
(paren
id|offset
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Discard data in the kernel mapping for the new page&n;&t; * FIXME: needs this MCRR to be supported.&n;&t; */
id|__asm__
c_func
(paren
l_string|&quot;mcrr&t;p15, 0, %1, %0, c6&t;@ 0xec401f06&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kaddr
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
id|kaddr
op_plus
id|PAGE_SIZE
op_minus
id|L1_CACHE_BYTES
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now clear the page using the same cache colour as&n;&t; * the pages ultimate destination.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|v6_lock
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|to_pte
op_plus
id|offset
comma
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|kaddr
)paren
op_rshift
id|PAGE_SHIFT
comma
id|to_pgprot
)paren
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|to
)paren
suffix:semicolon
id|clear_page
c_func
(paren
(paren
r_void
op_star
)paren
id|to
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|v6_lock
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_struct
id|cpu_user_fns
id|v6_user_fns
id|__initdata
op_assign
(brace
dot
id|cpu_clear_user_page
op_assign
id|v6_clear_user_page_nonaliasing
comma
dot
id|cpu_copy_user_page
op_assign
id|v6_copy_user_page_nonaliasing
comma
)brace
suffix:semicolon
DECL|function|v6_userpage_init
r_static
r_int
id|__init
id|v6_userpage_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cache_is_vipt_aliasing
c_func
(paren
)paren
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
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|from_address
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
id|from_address
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
id|from_pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|from_address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|from_pte
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|to_pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|to_address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to_pte
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|cpu_user.cpu_clear_user_page
op_assign
id|v6_clear_user_page_aliasing
suffix:semicolon
id|cpu_user.cpu_copy_user_page
op_assign
id|v6_copy_user_page_aliasing
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|v6_userpage_init
id|__initcall
c_func
(paren
id|v6_userpage_init
)paren
suffix:semicolon
eof
