macro_line|#ifndef _LINUX_RMAP_H
DECL|macro|_LINUX_RMAP_H
mdefine_line|#define _LINUX_RMAP_H
multiline_comment|/*&n; * Declarations for Reverse Mapping functions in mm/rmap.c&n; * Its structures are declared within that file.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|page_map_lock
mdefine_line|#define page_map_lock(page) &bslash;&n;&t;bit_spin_lock(PG_maplock, (unsigned long *)&amp;(page)-&gt;flags)
DECL|macro|page_map_unlock
mdefine_line|#define page_map_unlock(page) &bslash;&n;&t;bit_spin_unlock(PG_maplock, (unsigned long *)&amp;(page)-&gt;flags)
macro_line|#ifdef CONFIG_MMU
r_void
id|fastcall
id|page_add_anon_rmap
c_func
(paren
r_struct
id|page
op_star
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_void
id|fastcall
id|page_add_file_rmap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_void
id|fastcall
id|page_remove_rmap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * page_dup_rmap - duplicate pte mapping to a page&n; * @page:&t;the page to add the mapping to&n; *&n; * For copy_page_range only: minimal extract from page_add_rmap,&n; * avoiding unnecessary tests (already checked) so it&squot;s quicker.&n; */
DECL|function|page_dup_rmap
r_static
r_inline
r_void
id|page_dup_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|page_map_lock
c_func
(paren
id|page
)paren
suffix:semicolon
id|page-&gt;mapcount
op_increment
suffix:semicolon
id|page_map_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_int
id|fastcall
id|mremap_move_anon_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/**&n; * mremap_moved_anon_rmap - does new address clash with that noted?&n; * @page:&t;the page just brought back in from swap&n; * @addr:&t;the user virtual address at which it is mapped&n; *&n; * Returns boolean, true if addr clashes with address already in page.&n; *&n; * For do_swap_page and unuse_pte: anonmm rmap cannot find the page if&n; * it&squot;s at different addresses in different mms, so caller must take a&n; * copy of the page to avoid that: not very clever, but too rare a case&n; * to merit cleverness.&n; */
DECL|function|mremap_moved_anon_rmap
r_static
r_inline
r_int
id|mremap_moved_anon_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|page-&gt;index
op_ne
(paren
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * make_page_exclusive - try to make page exclusive to one mm&n; * @vma&t;&t;the vm_area_struct covering this address&n; * @addr&t;the user virtual address of the page in question&n; *&n; * Assumes that the page at this address is anonymous (COWable),&n; * and that the caller holds mmap_sem for reading or for writing.&n; *&n; * For mremap&squot;s move_page_tables and for swapoff&squot;s unuse_process:&n; * not a general purpose routine, and in general may not succeed.&n; * But move_page_tables loops until it succeeds, and unuse_process&n; * holds the original page locked, which protects against races.&n; */
DECL|function|make_page_exclusive
r_static
r_inline
r_int
id|make_page_exclusive
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
r_if
c_cond
(paren
id|handle_mm_fault
c_func
(paren
id|vma-&gt;vm_mm
comma
id|vma
comma
id|addr
comma
l_int|1
)paren
op_ne
id|VM_FAULT_OOM
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from kernel/fork.c to manage anonymous memory&n; */
r_void
id|init_rmap
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|exec_rmap
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_int
id|dup_rmap
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_struct
id|mm_struct
op_star
id|oldmm
)paren
suffix:semicolon
r_void
id|exit_rmap
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Called from mm/vmscan.c to handle paging out&n; */
r_int
id|fastcall
id|page_referenced
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_int
id|fastcall
id|try_to_unmap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
macro_line|#else&t;/* !CONFIG_MMU */
DECL|macro|init_rmap
mdefine_line|#define init_rmap()&t;&t;do {} while (0)
DECL|macro|exec_rmap
mdefine_line|#define exec_rmap(mm)&t;&t;(0)
DECL|macro|dup_rmap
mdefine_line|#define dup_rmap(mm, oldmm)&t;(0)
DECL|macro|exit_rmap
mdefine_line|#define exit_rmap(mm)&t;&t;do {} while (0)
DECL|macro|page_referenced
mdefine_line|#define page_referenced(page)&t;TestClearPageReferenced(page)
DECL|macro|try_to_unmap
mdefine_line|#define try_to_unmap(page)&t;SWAP_FAIL
macro_line|#endif&t;/* CONFIG_MMU */
multiline_comment|/*&n; * Return values of try_to_unmap&n; */
DECL|macro|SWAP_SUCCESS
mdefine_line|#define SWAP_SUCCESS&t;0
DECL|macro|SWAP_AGAIN
mdefine_line|#define SWAP_AGAIN&t;1
DECL|macro|SWAP_FAIL
mdefine_line|#define SWAP_FAIL&t;2
macro_line|#endif&t;/* _LINUX_RMAP_H */
eof
