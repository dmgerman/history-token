macro_line|#ifndef _LINUX_SWAP_H
DECL|macro|_LINUX_SWAP_H
mdefine_line|#define _LINUX_SWAP_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|SWAP_FLAG_PREFER
mdefine_line|#define SWAP_FLAG_PREFER&t;0x8000&t;/* set if swap priority specified */
DECL|macro|SWAP_FLAG_PRIO_MASK
mdefine_line|#define SWAP_FLAG_PRIO_MASK&t;0x7fff
DECL|macro|SWAP_FLAG_PRIO_SHIFT
mdefine_line|#define SWAP_FLAG_PRIO_SHIFT&t;0
DECL|macro|MAX_SWAPFILES
mdefine_line|#define MAX_SWAPFILES 8
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
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Max bad pages in the new format..&n; */
DECL|macro|__swapoffset
mdefine_line|#define __swapoffset(x) ((unsigned long)&amp;((union swap_header *)0)-&gt;x)
DECL|macro|MAX_SWAP_BADPAGES
mdefine_line|#define MAX_SWAP_BADPAGES &bslash;&n;&t;((__swapoffset(magic.magic) - __swapoffset(info.badpages)) / sizeof(int))
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|SWP_USED
mdefine_line|#define SWP_USED&t;1
DECL|macro|SWP_WRITEOK
mdefine_line|#define SWP_WRITEOK&t;3
DECL|macro|SWAP_CLUSTER_MAX
mdefine_line|#define SWAP_CLUSTER_MAX 32
DECL|macro|SWAP_MAP_MAX
mdefine_line|#define SWAP_MAP_MAX&t;0x7fff
DECL|macro|SWAP_MAP_BAD
mdefine_line|#define SWAP_MAP_BAD&t;0x8000
DECL|struct|swap_info_struct
r_struct
id|swap_info_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|swap_device
id|kdev_t
id|swap_device
suffix:semicolon
DECL|member|sdev_lock
id|spinlock_t
id|sdev_lock
suffix:semicolon
DECL|member|swap_file
r_struct
id|dentry
op_star
id|swap_file
suffix:semicolon
DECL|member|swap_vfsmnt
r_struct
id|vfsmount
op_star
id|swap_vfsmnt
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
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* next entry on swap list */
)brace
suffix:semicolon
r_extern
r_int
id|nr_swap_pages
suffix:semicolon
id|FASTCALL
c_func
(paren
r_int
r_int
id|nr_free_pages
c_func
(paren
r_void
)paren
)paren
suffix:semicolon
id|FASTCALL
c_func
(paren
r_int
r_int
id|nr_inactive_clean_pages
c_func
(paren
r_void
)paren
)paren
suffix:semicolon
id|FASTCALL
c_func
(paren
r_int
r_int
id|nr_free_buffer_pages
c_func
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_int
id|nr_active_pages
suffix:semicolon
r_extern
r_int
id|nr_inactive_dirty_pages
suffix:semicolon
r_extern
id|atomic_t
id|nr_async_pages
suffix:semicolon
r_extern
r_struct
id|address_space
id|swapper_space
suffix:semicolon
r_extern
id|atomic_t
id|page_cache_size
suffix:semicolon
r_extern
id|atomic_t
id|buffermem_pages
suffix:semicolon
r_extern
id|spinlock_t
id|pagecache_lock
suffix:semicolon
r_extern
r_void
id|__remove_inode_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
multiline_comment|/* Incomplete types for prototype declarations: */
r_struct
id|task_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|sysinfo
suffix:semicolon
r_struct
id|zone_t
suffix:semicolon
multiline_comment|/* linux/mm/swap.c */
r_extern
r_int
id|memory_pressure
suffix:semicolon
r_extern
r_void
id|age_page_up
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|age_page_up_nolock
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|age_page_down
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|age_page_down_nolock
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|age_page_down_ageonly
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|deactivate_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|deactivate_page_nolock
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|activate_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|activate_page_nolock
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|lru_cache_add
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__lru_cache_del
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|lru_cache_del
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|recalculate_vm_stats
c_func
(paren
r_void
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
r_struct
id|page
op_star
id|reclaim_page
c_func
(paren
id|zone_t
op_star
)paren
suffix:semicolon
r_extern
id|wait_queue_head_t
id|kswapd_wait
suffix:semicolon
r_extern
id|wait_queue_head_t
id|kreclaimd_wait
suffix:semicolon
r_extern
r_int
id|page_launder
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|free_shortage
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|inactive_shortage
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wakeup_kswapd
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|try_to_free_pages
c_func
(paren
r_int
r_int
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/* linux/mm/page_io.c */
r_extern
r_void
id|rw_swap_page
c_func
(paren
r_int
comma
r_struct
id|page
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|rw_swap_page_nolock
c_func
(paren
r_int
comma
id|swp_entry_t
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/mm/page_alloc.c */
multiline_comment|/* linux/mm/swap_state.c */
r_extern
r_void
id|show_swap_cache_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|add_to_swap_cache
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
id|swap_check_entry
c_func
(paren
r_int
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
r_int
)paren
suffix:semicolon
DECL|macro|read_swap_cache
mdefine_line|#define read_swap_cache(entry) read_swap_cache_async(entry, 1);
multiline_comment|/* linux/mm/oom_kill.c */
r_extern
r_int
id|out_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oom_kill
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Make these inline later once they are working properly.&n; */
r_extern
r_void
id|__delete_from_swap_cache
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
id|delete_from_swap_cache
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
id|delete_from_swap_cache_nolock
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swapfile.c */
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
r_int
id|is_swap_partition
c_func
(paren
id|kdev_t
)paren
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
id|__get_swap_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|get_swaphandle_info
c_func
(paren
id|swp_entry_t
comma
r_int
r_int
op_star
comma
id|kdev_t
op_star
comma
r_struct
id|inode
op_star
op_star
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
id|swap_count
c_func
(paren
r_struct
id|page
op_star
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
DECL|macro|get_swap_page
mdefine_line|#define get_swap_page() __get_swap_page(1)
r_extern
r_void
id|__swap_free
c_func
(paren
id|swp_entry_t
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|swap_free
mdefine_line|#define swap_free(entry) __swap_free((entry), 1)
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
r_extern
r_struct
id|swap_list_t
id|swap_list
suffix:semicolon
id|asmlinkage
r_int
id|sys_swapoff
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_swapon
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|SWAP_CACHE_INFO
mdefine_line|#define SWAP_CACHE_INFO
macro_line|#ifdef SWAP_CACHE_INFO
r_extern
r_int
r_int
id|swap_cache_add_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_del_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_success
suffix:semicolon
macro_line|#endif
r_extern
id|spinlock_t
id|pagemap_lru_lock
suffix:semicolon
multiline_comment|/*&n; * Page aging defines.&n; * Since we do exponential decay of the page age, we&n; * can chose a fairly large maximum.&n; */
DECL|macro|PAGE_AGE_START
mdefine_line|#define PAGE_AGE_START 2
DECL|macro|PAGE_AGE_ADV
mdefine_line|#define PAGE_AGE_ADV 3
DECL|macro|PAGE_AGE_MAX
mdefine_line|#define PAGE_AGE_MAX 64
multiline_comment|/*&n; * List add/del helper macros. These must be called&n; * with the pagemap_lru_lock held!&n; */
DECL|macro|DEBUG_ADD_PAGE
mdefine_line|#define DEBUG_ADD_PAGE &bslash;&n;&t;if (PageActive(page) || PageInactiveDirty(page) || &bslash;&n;&t;&t;&t;&t;&t;PageInactiveClean(page)) BUG();
DECL|macro|ZERO_PAGE_BUG
mdefine_line|#define ZERO_PAGE_BUG &bslash;&n;&t;if (page_count(page) == 0) BUG();
DECL|macro|add_page_to_active_list
mdefine_line|#define add_page_to_active_list(page) { &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;&t;SetPageActive(page); &bslash;&n;&t;list_add(&amp;(page)-&gt;lru, &amp;active_list); &bslash;&n;&t;nr_active_pages++; &bslash;&n;}
DECL|macro|add_page_to_inactive_dirty_list
mdefine_line|#define add_page_to_inactive_dirty_list(page) { &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;&t;SetPageInactiveDirty(page); &bslash;&n;&t;list_add(&amp;(page)-&gt;lru, &amp;inactive_dirty_list); &bslash;&n;&t;nr_inactive_dirty_pages++; &bslash;&n;&t;page-&gt;zone-&gt;inactive_dirty_pages++; &bslash;&n;}
DECL|macro|add_page_to_inactive_clean_list
mdefine_line|#define add_page_to_inactive_clean_list(page) { &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;&t;SetPageInactiveClean(page); &bslash;&n;&t;list_add(&amp;(page)-&gt;lru, &amp;page-&gt;zone-&gt;inactive_clean_list); &bslash;&n;&t;page-&gt;zone-&gt;inactive_clean_pages++; &bslash;&n;}
DECL|macro|del_page_from_active_list
mdefine_line|#define del_page_from_active_list(page) { &bslash;&n;&t;list_del(&amp;(page)-&gt;lru); &bslash;&n;&t;ClearPageActive(page); &bslash;&n;&t;nr_active_pages--; &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;}
DECL|macro|del_page_from_inactive_dirty_list
mdefine_line|#define del_page_from_inactive_dirty_list(page) { &bslash;&n;&t;list_del(&amp;(page)-&gt;lru); &bslash;&n;&t;ClearPageInactiveDirty(page); &bslash;&n;&t;nr_inactive_dirty_pages--; &bslash;&n;&t;page-&gt;zone-&gt;inactive_dirty_pages--; &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;}
DECL|macro|del_page_from_inactive_clean_list
mdefine_line|#define del_page_from_inactive_clean_list(page) { &bslash;&n;&t;list_del(&amp;(page)-&gt;lru); &bslash;&n;&t;ClearPageInactiveClean(page); &bslash;&n;&t;page-&gt;zone-&gt;inactive_clean_pages--; &bslash;&n;&t;DEBUG_ADD_PAGE &bslash;&n;&t;ZERO_PAGE_BUG &bslash;&n;}
multiline_comment|/*&n; * In mm/swap.c::recalculate_vm_stats(), we substract&n; * inactive_target from memory_pressure every second.&n; * This means that memory_pressure is smoothed over&n; * 64 (1 &lt;&lt; INACTIVE_SHIFT) seconds.&n; */
DECL|macro|INACTIVE_SHIFT
mdefine_line|#define INACTIVE_SHIFT 6
DECL|macro|inactive_min
mdefine_line|#define inactive_min(a,b) ((a) &lt; (b) ? (a) : (b))
DECL|macro|inactive_target
mdefine_line|#define inactive_target inactive_min((memory_pressure &gt;&gt; INACTIVE_SHIFT), &bslash;&n;&t;&t;(num_physpages / 4))
multiline_comment|/*&n; * Ugly ugly ugly HACK to make sure the inactive lists&n; * don&squot;t fill up with unfreeable ramdisk pages. We really&n; * want to fix the ramdisk driver to mark its pages as&n; * unfreeable instead of using dirty buffer magic, but the&n; * next code-change time is when 2.5 is forked...&n; */
macro_line|#ifndef _LINUX_KDEV_T_H
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_MAJOR_H
macro_line|#include &lt;linux/major.h&gt;
macro_line|#endif
DECL|macro|page_ramdisk
mdefine_line|#define page_ramdisk(page) &bslash;&n;&t;(page-&gt;buffers &amp;&amp; (MAJOR(page-&gt;buffers-&gt;b_dev) == RAMDISK_MAJOR))
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
r_extern
r_void
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
macro_line|#endif /* __KERNEL__*/
macro_line|#endif /* _LINUX_SWAP_H */
eof
