macro_line|#ifndef _LINUX_RMAP_H
DECL|macro|_LINUX_RMAP_H
mdefine_line|#define _LINUX_RMAP_H
multiline_comment|/*&n; * Declarations for Reverse Mapping functions in mm/rmap.c&n; * Its structures are declared within that file.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|page_map_lock
mdefine_line|#define page_map_lock(page) &bslash;&n;&t;bit_spin_lock(PG_maplock, (unsigned long *)&amp;(page)-&gt;flags)
DECL|macro|page_map_unlock
mdefine_line|#define page_map_unlock(page) &bslash;&n;&t;bit_spin_unlock(PG_maplock, (unsigned long *)&amp;(page)-&gt;flags)
macro_line|#ifdef CONFIG_MMU
multiline_comment|/*&n; * rmap interfaces called when adding or removing pte of page&n; */
r_void
id|page_add_anon_rmap
c_func
(paren
r_struct
id|page
op_star
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|page_add_file_rmap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_void
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
multiline_comment|/*&n; * Called from mm/vmscan.c to handle paging out&n; */
r_int
id|page_referenced
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_int
id|try_to_unmap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
macro_line|#else&t;/* !CONFIG_MMU */
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
