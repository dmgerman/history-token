macro_line|#ifndef _LINUX_PAGEMAP_H
DECL|macro|_LINUX_PAGEMAP_H
mdefine_line|#define _LINUX_PAGEMAP_H
multiline_comment|/*&n; * Copyright 1995 Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
multiline_comment|/*&n; * The page cache can done in larger chunks than&n; * one page, because it allows for more efficient&n; * throughput (it can then be mapped into user&n; * space in smaller chunks for same flexibility).&n; *&n; * Or rather, it _will_ be done in larger chunks.&n; */
DECL|macro|PAGE_CACHE_SHIFT
mdefine_line|#define PAGE_CACHE_SHIFT&t;PAGE_SHIFT
DECL|macro|PAGE_CACHE_SIZE
mdefine_line|#define PAGE_CACHE_SIZE&t;&t;PAGE_SIZE
DECL|macro|PAGE_CACHE_MASK
mdefine_line|#define PAGE_CACHE_MASK&t;&t;PAGE_MASK
DECL|macro|PAGE_CACHE_ALIGN
mdefine_line|#define PAGE_CACHE_ALIGN(addr)&t;(((addr)+PAGE_CACHE_SIZE-1)&amp;PAGE_CACHE_MASK)
DECL|macro|page_cache_get
mdefine_line|#define page_cache_get(page)&t;&t;get_page(page)
DECL|macro|page_cache_release
mdefine_line|#define page_cache_release(page)&t;put_page(page)
r_void
id|release_pages
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|function|page_cache_alloc
r_static
r_inline
r_struct
id|page
op_star
id|page_cache_alloc
c_func
(paren
r_struct
id|address_space
op_star
id|x
)paren
(brace
r_return
id|alloc_pages
c_func
(paren
id|x-&gt;gfp_mask
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|typedef|filler_t
r_typedef
r_int
id|filler_t
c_func
(paren
r_void
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|find_get_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|find_lock_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|find_trylock_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|find_or_create_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
comma
r_int
r_int
id|gfp_mask
)paren
suffix:semicolon
r_extern
r_int
r_int
id|find_get_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|pgoff_t
id|start
comma
r_int
r_int
id|nr_pages
comma
r_struct
id|page
op_star
op_star
id|pages
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns locked page at given index in given cache, creating it if needed.&n; */
DECL|function|grab_cache_page
r_static
r_inline
r_struct
id|page
op_star
id|grab_cache_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
(brace
r_return
id|find_or_create_page
c_func
(paren
id|mapping
comma
id|index
comma
id|mapping-&gt;gfp_mask
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|page
op_star
id|grab_cache_page_nowait
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|read_cache_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
comma
id|filler_t
op_star
id|filler
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|add_to_page_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_int
id|add_to_page_cache_lru
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_extern
r_void
id|remove_from_page_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|__remove_from_page_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|function|___add_to_page_cache
r_static
r_inline
r_void
id|___add_to_page_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|mapping-&gt;clean_pages
)paren
suffix:semicolon
id|page-&gt;mapping
op_assign
id|mapping
suffix:semicolon
id|page-&gt;index
op_assign
id|index
suffix:semicolon
id|mapping-&gt;nrpages
op_increment
suffix:semicolon
id|inc_page_state
c_func
(paren
id|nr_pagecache
)paren
suffix:semicolon
)brace
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__lock_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|unlock_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
)paren
suffix:semicolon
DECL|function|lock_page
r_static
r_inline
r_void
id|lock_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|TestSetPageLocked
c_func
(paren
id|page
)paren
)paren
id|__lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is exported only for wait_on_page_locked/wait_on_page_writeback.&n; * Never use this directly!&n; */
r_extern
r_void
id|FASTCALL
c_func
(paren
id|wait_on_page_bit
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|bit_nr
)paren
)paren
suffix:semicolon
multiline_comment|/* &n; * Wait for a page to be unlocked.&n; *&n; * This must be called with the caller &quot;holding&quot; the page,&n; * ie with increased &quot;page-&gt;count&quot; so that the page won&squot;t&n; * go away during the wait..&n; */
DECL|function|wait_on_page_locked
r_static
r_inline
r_void
id|wait_on_page_locked
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|wait_on_page_bit
c_func
(paren
id|page
comma
id|PG_locked
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Wait for a page to complete writeback&n; */
DECL|function|wait_on_page_writeback
r_static
r_inline
r_void
id|wait_on_page_writeback
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
id|wait_on_page_bit
c_func
(paren
id|page
comma
id|PG_writeback
)paren
suffix:semicolon
)brace
r_extern
r_void
id|end_page_writeback
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_PAGEMAP_H */
eof
