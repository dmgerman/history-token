macro_line|#ifndef _LINUX_SWAP_H
DECL|macro|_LINUX_SWAP_H
mdefine_line|#define _LINUX_SWAP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|SWAP_FLAG_PREFER
mdefine_line|#define SWAP_FLAG_PREFER&t;0x8000&t;/* set if swap priority specified */
DECL|macro|SWAP_FLAG_PRIO_MASK
mdefine_line|#define SWAP_FLAG_PRIO_MASK&t;0x7fff
DECL|macro|SWAP_FLAG_PRIO_SHIFT
mdefine_line|#define SWAP_FLAG_PRIO_SHIFT&t;0
DECL|function|current_is_kswapd
r_static
r_inline
r_int
id|current_is_kswapd
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;flags
op_amp
id|PF_KSWAPD
suffix:semicolon
)brace
multiline_comment|/*&n; * MAX_SWAPFILES defines the maximum number of swaptypes: things which can&n; * be swapped to.  The swap type and the offset into that swap type are&n; * encoded into pte&squot;s and into pgoff_t&squot;s in the swapcache.  Using five bits&n; * for the type means that the maximum number of swapcache pages is 27 bits&n; * on 32-bit-pgoff_t architectures.  And that assumes that the architecture packs&n; * the type/offset into the pte as 5/27 as well.&n; */
DECL|macro|MAX_SWAPFILES_SHIFT
mdefine_line|#define MAX_SWAPFILES_SHIFT&t;5
DECL|macro|MAX_SWAPFILES
mdefine_line|#define MAX_SWAPFILES&t;&t;(1 &lt;&lt; MAX_SWAPFILES_SHIFT)
multiline_comment|/*&n; * Magic header for a swap area. The first part of the union is&n; * what the swap magic looks like for the old (limited to 128MB)&n; * swap area format, the second part of the union adds - in the&n; * old reserved area - some extra information. Note that the first&n; * kilobyte is reserved for boot loader or disk label stuff...&n; *&n; * Having the magic at the end of the PAGE_SIZE makes detecting swap&n; * areas somewhat tricky on machines that support multiple page sizes.&n; * For 2.5 we&squot;ll probably want to move the magic to just beyond the&n; * bootbits...&n; */
DECL|union|swap_header
r_union
id|swap_header
(brace
r_struct
(brace
DECL|member|reserved
r_char
id|reserved
(braket
id|PAGE_SIZE
op_minus
l_int|10
)braket
suffix:semicolon
DECL|member|magic
r_char
id|magic
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* SWAP-SPACE or SWAPSPACE2 */
DECL|member|magic
)brace
id|magic
suffix:semicolon
r_struct
(brace
DECL|member|bootbits
r_char
id|bootbits
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Space for disklabel etc. */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|last_page
r_int
r_int
id|last_page
suffix:semicolon
DECL|member|nr_badpages
r_int
r_int
id|nr_badpages
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|125
)braket
suffix:semicolon
DECL|member|badpages
r_int
r_int
id|badpages
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A swap entry has to fit into a &quot;unsigned long&quot;, as&n;  * the entry is hidden in the &quot;index&quot; field of the&n;  * swapper address space.&n;  */
r_typedef
r_struct
(brace
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|typedef|swp_entry_t
)brace
id|swp_entry_t
suffix:semicolon
multiline_comment|/*&n; * current-&gt;reclaim_state points to one of these when a task is running&n; * memory reclaim&n; */
DECL|struct|reclaim_state
r_struct
id|reclaim_state
(brace
DECL|member|reclaimed_slab
r_int
r_int
id|reclaimed_slab
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|address_space
suffix:semicolon
r_struct
id|sysinfo
suffix:semicolon
r_struct
id|writeback_control
suffix:semicolon
r_struct
id|zone
suffix:semicolon
multiline_comment|/*&n; * A swap extent maps a range of a swapfile&squot;s PAGE_SIZE pages onto a range of&n; * disk blocks.  A list of swap extents maps the entire swapfile.  (Where the&n; * term `swapfile&squot; refers to either a blockdevice or an IS_REG file.  Apart&n; * from setup, they&squot;re handled identically.&n; *&n; * We always assume that blocks are of size PAGE_SIZE.&n; */
DECL|struct|swap_extent
r_struct
id|swap_extent
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|start_page
id|pgoff_t
id|start_page
suffix:semicolon
DECL|member|nr_pages
id|pgoff_t
id|nr_pages
suffix:semicolon
DECL|member|start_block
id|sector_t
id|start_block
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Max bad pages in the new format..&n; */
DECL|macro|__swapoffset
mdefine_line|#define __swapoffset(x) ((unsigned long)&amp;((union swap_header *)0)-&gt;x)
DECL|macro|MAX_SWAP_BADPAGES
mdefine_line|#define MAX_SWAP_BADPAGES &bslash;&n;&t;((__swapoffset(magic.magic) - __swapoffset(info.badpages)) / sizeof(int))
r_enum
(brace
DECL|enumerator|SWP_USED
id|SWP_USED
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* is slot in swap_info[] used? */
DECL|enumerator|SWP_WRITEOK
id|SWP_WRITEOK
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* ok to write to this swap?&t;*/
DECL|enumerator|SWP_ACTIVE
id|SWP_ACTIVE
op_assign
(paren
id|SWP_USED
op_or
id|SWP_WRITEOK
)paren
comma
)brace
suffix:semicolon
DECL|macro|SWAP_CLUSTER_MAX
mdefine_line|#define SWAP_CLUSTER_MAX 32
DECL|macro|SWAP_MAP_MAX
mdefine_line|#define SWAP_MAP_MAX&t;0x7fff
DECL|macro|SWAP_MAP_BAD
mdefine_line|#define SWAP_MAP_BAD&t;0x8000
multiline_comment|/*&n; * The in-memory structure used to track swap areas.&n; * extent_list.prev points at the lowest-index extent.  That list is&n; * sorted.&n; */
DECL|struct|swap_info_struct
r_struct
id|swap_info_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|sdev_lock
id|spinlock_t
id|sdev_lock
suffix:semicolon
DECL|member|swap_file
r_struct
id|file
op_star
id|swap_file
suffix:semicolon
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
DECL|member|extent_list
r_struct
id|list_head
id|extent_list
suffix:semicolon
DECL|member|nr_extents
r_int
id|nr_extents
suffix:semicolon
DECL|member|curr_swap_extent
r_struct
id|swap_extent
op_star
id|curr_swap_extent
suffix:semicolon
DECL|member|old_block_size
r_int
id|old_block_size
suffix:semicolon
DECL|member|swap_map
r_int
r_int
op_star
id|swap_map
suffix:semicolon
DECL|member|lowest_bit
r_int
r_int
id|lowest_bit
suffix:semicolon
DECL|member|highest_bit
r_int
r_int
id|highest_bit
suffix:semicolon
DECL|member|cluster_next
r_int
r_int
id|cluster_next
suffix:semicolon
DECL|member|cluster_nr
r_int
r_int
id|cluster_nr
suffix:semicolon
DECL|member|prio
r_int
id|prio
suffix:semicolon
multiline_comment|/* swap priority */
DECL|member|pages
r_int
id|pages
suffix:semicolon
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
DECL|member|inuse_pages
r_int
r_int
id|inuse_pages
suffix:semicolon
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* next entry on swap list */
)brace
suffix:semicolon
DECL|struct|swap_list_t
r_struct
id|swap_list_t
(brace
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of priority-ordered swapfile list */
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* swapfile to be used next */
)brace
suffix:semicolon
multiline_comment|/* Swap 50% full? Release swapcache more aggressively.. */
DECL|macro|vm_swap_full
mdefine_line|#define vm_swap_full() (nr_swap_pages*2 &lt; total_swap_pages)
multiline_comment|/* linux/mm/oom_kill.c */
r_extern
r_void
id|out_of_memory
c_func
(paren
r_int
r_int
id|__nocast
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/* linux/mm/memory.c */
r_extern
r_void
id|swapin_readahead
c_func
(paren
id|swp_entry_t
comma
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* linux/mm/page_alloc.c */
r_extern
r_int
r_int
id|totalram_pages
suffix:semicolon
r_extern
r_int
r_int
id|totalhigh_pages
suffix:semicolon
r_extern
r_int
id|nr_swap_pages
suffix:semicolon
r_extern
r_int
r_int
id|nr_free_pages
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nr_free_pages_pgdat
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nr_free_buffer_pages
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nr_free_pagecache_pages
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swap.c */
r_extern
r_void
id|FASTCALL
c_func
(paren
id|lru_cache_add
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|lru_cache_add_active
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|activate_page
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|mark_page_accessed
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|lru_add_drain
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rotate_reclaimable_page
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
id|swap_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* linux/mm/vmscan.c */
r_extern
r_int
id|try_to_free_pages
c_func
(paren
r_struct
id|zone
op_star
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|shrink_all_memory
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|vm_swappiness
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* linux/mm/shmem.c */
r_extern
r_int
id|shmem_unuse
c_func
(paren
id|swp_entry_t
id|entry
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MMU */
r_extern
r_void
id|swap_unplug_io_fn
c_func
(paren
r_struct
id|backing_dev_info
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SWAP
multiline_comment|/* linux/mm/page_io.c */
r_extern
r_int
id|swap_readpage
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|swap_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
suffix:semicolon
r_extern
r_int
id|rw_swap_page_sync
c_func
(paren
r_int
comma
id|swp_entry_t
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swap_state.c */
r_extern
r_struct
id|address_space
id|swapper_space
suffix:semicolon
DECL|macro|total_swapcache_pages
mdefine_line|#define total_swapcache_pages  swapper_space.nrpages
r_extern
r_void
id|show_swap_cache_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|add_to_swap
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|move_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
comma
id|swp_entry_t
)paren
suffix:semicolon
r_extern
r_int
id|move_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_struct
id|address_space
op_star
)paren
suffix:semicolon
r_extern
r_void
id|free_page_and_swap_cache
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|free_pages_and_swap_cache
c_func
(paren
r_struct
id|page
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|lookup_swap_cache
c_func
(paren
id|swp_entry_t
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|read_swap_cache_async
c_func
(paren
id|swp_entry_t
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swapfile.c */
r_extern
r_int
id|total_swap_pages
suffix:semicolon
r_extern
r_int
r_int
id|nr_swapfiles
suffix:semicolon
r_extern
r_struct
id|swap_info_struct
id|swap_info
(braket
)braket
suffix:semicolon
r_extern
r_void
id|si_swapinfo
c_func
(paren
r_struct
id|sysinfo
op_star
)paren
suffix:semicolon
r_extern
id|swp_entry_t
id|get_swap_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|swap_duplicate
c_func
(paren
id|swp_entry_t
)paren
suffix:semicolon
r_extern
r_int
id|valid_swaphandles
c_func
(paren
id|swp_entry_t
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|swap_free
c_func
(paren
id|swp_entry_t
)paren
suffix:semicolon
r_extern
r_void
id|free_swap_and_cache
c_func
(paren
id|swp_entry_t
)paren
suffix:semicolon
r_extern
id|sector_t
id|map_swap_page
c_func
(paren
r_struct
id|swap_info_struct
op_star
comma
id|pgoff_t
)paren
suffix:semicolon
r_extern
r_struct
id|swap_info_struct
op_star
id|get_swap_info_struct
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|can_share_swap_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|remove_exclusive_swap_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_struct
id|backing_dev_info
suffix:semicolon
r_extern
r_struct
id|swap_list_t
id|swap_list
suffix:semicolon
r_extern
id|spinlock_t
id|swaplock
suffix:semicolon
DECL|macro|swap_list_lock
mdefine_line|#define swap_list_lock()&t;spin_lock(&amp;swaplock)
DECL|macro|swap_list_unlock
mdefine_line|#define swap_list_unlock()&t;spin_unlock(&amp;swaplock)
DECL|macro|swap_device_lock
mdefine_line|#define swap_device_lock(p)&t;spin_lock(&amp;p-&gt;sdev_lock)
DECL|macro|swap_device_unlock
mdefine_line|#define swap_device_unlock(p)&t;spin_unlock(&amp;p-&gt;sdev_lock)
multiline_comment|/* linux/mm/thrash.c */
r_extern
r_struct
id|mm_struct
op_star
id|swap_token_mm
suffix:semicolon
r_extern
r_int
r_int
id|swap_token_default_timeout
suffix:semicolon
r_extern
r_void
id|grab_swap_token
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_swap_token
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
DECL|function|has_swap_token
r_static
r_inline
r_int
id|has_swap_token
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_return
(paren
id|mm
op_eq
id|swap_token_mm
)paren
suffix:semicolon
)brace
DECL|function|put_swap_token
r_static
r_inline
r_void
id|put_swap_token
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|has_swap_token
c_func
(paren
id|mm
)paren
)paren
id|__put_swap_token
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SWAP */
DECL|macro|total_swap_pages
mdefine_line|#define total_swap_pages&t;&t;&t;0
DECL|macro|total_swapcache_pages
mdefine_line|#define total_swapcache_pages&t;&t;&t;0UL
DECL|macro|si_swapinfo
mdefine_line|#define si_swapinfo(val) &bslash;&n;&t;do { (val)-&gt;freeswap = (val)-&gt;totalswap = 0; } while (0)
DECL|macro|free_page_and_swap_cache
mdefine_line|#define free_page_and_swap_cache(page) &bslash;&n;&t;page_cache_release(page)
DECL|macro|free_pages_and_swap_cache
mdefine_line|#define free_pages_and_swap_cache(pages, nr) &bslash;&n;&t;release_pages((pages), (nr), 0);
DECL|macro|show_swap_cache_info
mdefine_line|#define show_swap_cache_info()&t;&t;&t;/*NOTHING*/
DECL|macro|free_swap_and_cache
mdefine_line|#define free_swap_and_cache(swp)&t;&t;/*NOTHING*/
DECL|macro|swap_duplicate
mdefine_line|#define swap_duplicate(swp)&t;&t;&t;/*NOTHING*/
DECL|macro|swap_free
mdefine_line|#define swap_free(swp)&t;&t;&t;&t;/*NOTHING*/
DECL|macro|read_swap_cache_async
mdefine_line|#define read_swap_cache_async(swp,vma,addr)&t;NULL
DECL|macro|lookup_swap_cache
mdefine_line|#define lookup_swap_cache(swp)&t;&t;&t;NULL
DECL|macro|valid_swaphandles
mdefine_line|#define valid_swaphandles(swp, off)&t;&t;0
DECL|macro|can_share_swap_page
mdefine_line|#define can_share_swap_page(p)&t;&t;&t;0
DECL|macro|move_to_swap_cache
mdefine_line|#define move_to_swap_cache(p, swp)&t;&t;1
DECL|macro|move_from_swap_cache
mdefine_line|#define move_from_swap_cache(p, i, m)&t;&t;1
DECL|macro|__delete_from_swap_cache
mdefine_line|#define __delete_from_swap_cache(p)&t;&t;/*NOTHING*/
DECL|macro|delete_from_swap_cache
mdefine_line|#define delete_from_swap_cache(p)&t;&t;/*NOTHING*/
DECL|macro|swap_token_default_timeout
mdefine_line|#define swap_token_default_timeout&t;&t;0
DECL|function|remove_exclusive_swap_page
r_static
r_inline
r_int
id|remove_exclusive_swap_page
c_func
(paren
r_struct
id|page
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_swap_page
r_static
r_inline
id|swp_entry_t
id|get_swap_page
c_func
(paren
r_void
)paren
(brace
id|swp_entry_t
id|entry
suffix:semicolon
id|entry.val
op_assign
l_int|0
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* linux/mm/thrash.c */
DECL|macro|put_swap_token
mdefine_line|#define put_swap_token(x) do { } while(0)
DECL|macro|grab_swap_token
mdefine_line|#define grab_swap_token()  do { } while(0)
DECL|macro|has_swap_token
mdefine_line|#define has_swap_token(x) 0
macro_line|#endif /* CONFIG_SWAP */
macro_line|#endif /* __KERNEL__*/
macro_line|#endif /* _LINUX_SWAP_H */
eof
