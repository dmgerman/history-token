macro_line|#ifndef _LINUX_PAGEMAP_H
DECL|macro|_LINUX_PAGEMAP_H
mdefine_line|#define _LINUX_PAGEMAP_H
multiline_comment|/*&n; * Copyright 1995 Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
multiline_comment|/*&n; * Bits in mapping-&gt;flags.  The lower __GFP_BITS_SHIFT bits are the page&n; * allocation mode flags.&n; */
DECL|macro|AS_EIO
mdefine_line|#define&t;AS_EIO&t;&t;(__GFP_BITS_SHIFT + 0)&t;/* IO error on async write */
DECL|macro|AS_ENOSPC
mdefine_line|#define AS_ENOSPC&t;(__GFP_BITS_SHIFT + 1)&t;/* ENOSPC on async write */
DECL|function|mapping_gfp_mask
r_static
r_inline
r_int
r_int
id|__nocast
id|mapping_gfp_mask
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_return
id|mapping-&gt;flags
op_amp
id|__GFP_BITS_MASK
suffix:semicolon
)brace
multiline_comment|/*&n; * This is non-atomic.  Only to be used before the mapping is activated.&n; * Probably needs a barrier...&n; */
DECL|function|mapping_set_gfp_mask
r_static
r_inline
r_void
id|mapping_set_gfp_mask
c_func
(paren
r_struct
id|address_space
op_star
id|m
comma
r_int
id|mask
)paren
(brace
id|m-&gt;flags
op_assign
(paren
id|m-&gt;flags
op_amp
op_complement
id|__GFP_BITS_MASK
)paren
op_or
id|mask
suffix:semicolon
)brace
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
comma
r_int
id|cold
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
id|mapping_gfp_mask
c_func
(paren
id|x
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|page_cache_alloc_cold
r_static
r_inline
r_struct
id|page
op_star
id|page_cache_alloc_cold
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
id|mapping_gfp_mask
c_func
(paren
id|x
)paren
op_or
id|__GFP_COLD
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
r_int
id|find_get_pages_tag
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|pgoff_t
op_star
id|index
comma
r_int
id|tag
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
id|mapping_gfp_mask
c_func
(paren
id|mapping
)paren
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
id|read_cache_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|list_head
op_star
id|pages
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
comma
r_int
id|gfp_mask
)paren
suffix:semicolon
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
comma
r_int
id|gfp_mask
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
r_extern
id|atomic_t
id|nr_pagecache
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|PAGECACHE_ACCT_THRESHOLD
mdefine_line|#define PAGECACHE_ACCT_THRESHOLD        max(16, NR_CPUS * 2)
id|DECLARE_PER_CPU
c_func
(paren
r_int
comma
id|nr_pagecache_local
)paren
suffix:semicolon
multiline_comment|/*&n; * pagecache_acct implements approximate accounting for pagecache.&n; * vm_enough_memory() do not need high accuracy. Writers will keep&n; * an offset in their per-cpu arena and will spill that into the&n; * global count whenever the absolute value of the local count&n; * exceeds the counter&squot;s threshold.&n; *&n; * MUST be protected from preemption.&n; * current protection is mapping-&gt;page_lock.&n; */
DECL|function|pagecache_acct
r_static
r_inline
r_void
id|pagecache_acct
c_func
(paren
r_int
id|count
)paren
(brace
r_int
op_star
id|local
suffix:semicolon
id|local
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|nr_pagecache_local
)paren
suffix:semicolon
op_star
id|local
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_star
id|local
OG
id|PAGECACHE_ACCT_THRESHOLD
op_logical_or
op_star
id|local
OL
op_minus
id|PAGECACHE_ACCT_THRESHOLD
)paren
(brace
id|atomic_add
c_func
(paren
op_star
id|local
comma
op_amp
id|nr_pagecache
)paren
suffix:semicolon
op_star
id|local
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|function|pagecache_acct
r_static
r_inline
r_void
id|pagecache_acct
c_func
(paren
r_int
id|count
)paren
(brace
id|atomic_add
c_func
(paren
id|count
comma
op_amp
id|nr_pagecache
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_page_cache_size
r_static
r_inline
r_int
r_int
id|get_page_cache_size
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
id|atomic_read
c_func
(paren
op_amp
id|nr_pagecache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
OL
l_int|0
)paren
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Return byte-offset into filesystem object for page.&n; */
DECL|function|page_offset
r_static
r_inline
id|loff_t
id|page_offset
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
(paren
(paren
id|loff_t
)paren
id|page-&gt;index
)paren
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
)brace
DECL|function|linear_page_index
r_static
r_inline
id|pgoff_t
id|linear_page_index
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
id|pgoff_t
id|pgoff
op_assign
(paren
id|address
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pgoff
op_add_assign
id|vma-&gt;vm_pgoff
suffix:semicolon
r_return
id|pgoff
op_rshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Fault a userspace page into pagetables.  Return non-zero on a fault.&n; *&n; * This assumes that two userspace pages are always sufficient.  That&squot;s&n; * not true if PAGE_CACHE_SIZE &gt; PAGE_SIZE.&n; */
DECL|function|fault_in_pages_writeable
r_static
r_inline
r_int
id|fault_in_pages_writeable
c_func
(paren
r_char
id|__user
op_star
id|uaddr
comma
r_int
id|size
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Writing zeroes into userspace here is OK, because we know that if&n;&t; * the zero gets there, we&squot;ll be overwriting it.&n;&t; */
id|ret
op_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|uaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
r_char
id|__user
op_star
id|end
op_assign
id|uaddr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the page was already mapped, this will get a cache miss&n;&t;&t; * for sure, so try to avoid doing it.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|uaddr
op_amp
id|PAGE_MASK
)paren
op_ne
(paren
(paren
r_int
r_int
)paren
id|end
op_amp
id|PAGE_MASK
)paren
)paren
id|ret
op_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|end
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fault_in_pages_readable
r_static
r_inline
r_void
id|fault_in_pages_readable
c_func
(paren
r_const
r_char
id|__user
op_star
id|uaddr
comma
r_int
id|size
)paren
(brace
r_volatile
r_char
id|c
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|__get_user
c_func
(paren
id|c
comma
id|uaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
r_const
r_char
id|__user
op_star
id|end
op_assign
id|uaddr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|uaddr
op_amp
id|PAGE_MASK
)paren
op_ne
(paren
(paren
r_int
r_int
)paren
id|end
op_amp
id|PAGE_MASK
)paren
)paren
id|__get_user
c_func
(paren
id|c
comma
id|end
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* _LINUX_PAGEMAP_H */
eof
