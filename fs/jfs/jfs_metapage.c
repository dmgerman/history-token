multiline_comment|/*&n; *   Copyright (C) International Business Machines Corp., 2000-2003&n; *   Portions Copyright (C) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_superblock.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_metapage.h&quot;
macro_line|#include &quot;jfs_txnmgr.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
DECL|variable|meta_lock
r_static
id|spinlock_t
id|meta_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifdef CONFIG_JFS_STATISTICS
r_struct
(brace
DECL|member|pagealloc
id|uint
id|pagealloc
suffix:semicolon
multiline_comment|/* # of page allocations */
DECL|member|pagefree
id|uint
id|pagefree
suffix:semicolon
multiline_comment|/* # of page frees */
DECL|member|lockwait
id|uint
id|lockwait
suffix:semicolon
multiline_comment|/* # of sleeping lock_metapage() calls */
DECL|variable|mpStat
)brace
id|mpStat
suffix:semicolon
macro_line|#endif
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS 10&t;&t;/* This makes hash_table 1 4K page */
DECL|macro|HASH_SIZE
mdefine_line|#define HASH_SIZE (1 &lt;&lt; HASH_BITS)
DECL|variable|hash_table
r_static
r_struct
id|metapage
op_star
op_star
id|hash_table
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|hash_order
r_static
r_int
r_int
id|hash_order
suffix:semicolon
DECL|function|metapage_locked
r_static
r_inline
r_int
id|metapage_locked
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|META_locked
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
)brace
DECL|function|trylock_metapage
r_static
r_inline
r_int
id|trylock_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_return
id|test_and_set_bit
c_func
(paren
id|META_locked
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
)brace
DECL|function|unlock_metapage
r_static
r_inline
r_void
id|unlock_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
id|clear_bit
c_func
(paren
id|META_locked
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mp-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|__lock_metapage
r_static
r_void
id|__lock_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|INCREMENT
c_func
(paren
id|mpStat.lockwait
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|mp-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_do
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|metapage_locked
c_func
(paren
id|mp
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|trylock_metapage
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|mp-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/* needs meta_lock */
DECL|function|lock_metapage
r_static
r_inline
r_void
id|lock_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_if
c_cond
(paren
id|trylock_metapage
c_func
(paren
id|mp
)paren
)paren
id|__lock_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
)brace
DECL|macro|METAPOOL_MIN_PAGES
mdefine_line|#define METAPOOL_MIN_PAGES 32
DECL|variable|metapage_cache
r_static
id|kmem_cache_t
op_star
id|metapage_cache
suffix:semicolon
DECL|variable|metapage_mempool
r_static
id|mempool_t
op_star
id|metapage_mempool
suffix:semicolon
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|metapage
op_star
id|mp
op_assign
(paren
r_struct
id|metapage
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
id|mp-&gt;lid
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;lsn
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;flag
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|mp-&gt;clsn
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;log
op_assign
l_int|NULL
suffix:semicolon
id|set_bit
c_func
(paren
id|META_free
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mp-&gt;wait
)paren
suffix:semicolon
)brace
)brace
DECL|function|alloc_metapage
r_static
r_inline
r_struct
id|metapage
op_star
id|alloc_metapage
c_func
(paren
r_int
id|no_wait
)paren
(brace
r_return
id|mempool_alloc
c_func
(paren
id|metapage_mempool
comma
id|no_wait
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_NOFS
)paren
suffix:semicolon
)brace
DECL|function|free_metapage
r_static
r_inline
r_void
id|free_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
id|mp-&gt;flag
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|META_free
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|mp
comma
id|metapage_mempool
)paren
suffix:semicolon
)brace
DECL|function|metapage_init
r_int
id|__init
id|metapage_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Allocate the metapage structures&n;&t; */
id|metapage_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;jfs_mp&quot;
comma
r_sizeof
(paren
r_struct
id|metapage
)paren
comma
l_int|0
comma
l_int|0
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|metapage_cache
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|metapage_mempool
op_assign
id|mempool_create
c_func
(paren
id|METAPOOL_MIN_PAGES
comma
id|mempool_alloc_slab
comma
id|mempool_free_slab
comma
id|metapage_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|metapage_mempool
op_eq
l_int|NULL
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|metapage_cache
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now the hash list&n;&t; */
r_for
c_loop
(paren
id|hash_order
op_assign
l_int|0
suffix:semicolon
(paren
(paren
id|PAGE_SIZE
op_lshift
id|hash_order
)paren
op_div
r_sizeof
(paren
r_void
op_star
)paren
)paren
OL
id|HASH_SIZE
suffix:semicolon
id|hash_order
op_increment
)paren
suffix:semicolon
id|hash_table
op_assign
(paren
r_struct
id|metapage
op_star
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|hash_order
)paren
suffix:semicolon
m_assert
(paren
id|hash_table
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hash_table
comma
l_int|0
comma
id|PAGE_SIZE
op_lshift
id|hash_order
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|metapage_exit
r_void
id|metapage_exit
c_func
(paren
r_void
)paren
(brace
id|mempool_destroy
c_func
(paren
id|metapage_mempool
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|metapage_cache
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Basically same hash as in pagemap.h, but using our hash table&n; */
DECL|function|meta_hash
r_static
r_struct
id|metapage
op_star
op_star
id|meta_hash
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
DECL|macro|i
mdefine_line|#define i (((unsigned long)mapping)/ &bslash;&n;&t;   (sizeof(struct inode) &amp; ~(sizeof(struct inode) -1 )))
DECL|macro|s
mdefine_line|#define s(x) ((x) + ((x) &gt;&gt; HASH_BITS))
r_return
id|hash_table
op_plus
(paren
id|s
c_func
(paren
id|i
op_plus
id|index
)paren
op_amp
(paren
id|HASH_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
DECL|macro|i
macro_line|#undef i
DECL|macro|s
macro_line|#undef s
)brace
DECL|function|search_hash
r_static
r_struct
id|metapage
op_star
id|search_hash
c_func
(paren
r_struct
id|metapage
op_star
op_star
id|hash_ptr
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
r_struct
id|metapage
op_star
id|ptr
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
op_star
id|hash_ptr
suffix:semicolon
id|ptr
suffix:semicolon
id|ptr
op_assign
id|ptr-&gt;hash_next
)paren
(brace
r_if
c_cond
(paren
(paren
id|ptr-&gt;mapping
op_eq
id|mapping
)paren
op_logical_and
(paren
id|ptr-&gt;index
op_eq
id|index
)paren
)paren
r_return
id|ptr
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|add_to_hash
r_static
r_void
id|add_to_hash
c_func
(paren
r_struct
id|metapage
op_star
id|mp
comma
r_struct
id|metapage
op_star
op_star
id|hash_ptr
)paren
(brace
r_if
c_cond
(paren
op_star
id|hash_ptr
)paren
(paren
op_star
id|hash_ptr
)paren
op_member_access_from_pointer
id|hash_prev
op_assign
id|mp
suffix:semicolon
id|mp-&gt;hash_prev
op_assign
l_int|NULL
suffix:semicolon
id|mp-&gt;hash_next
op_assign
op_star
id|hash_ptr
suffix:semicolon
op_star
id|hash_ptr
op_assign
id|mp
suffix:semicolon
)brace
DECL|function|remove_from_hash
r_static
r_void
id|remove_from_hash
c_func
(paren
r_struct
id|metapage
op_star
id|mp
comma
r_struct
id|metapage
op_star
op_star
id|hash_ptr
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;hash_prev
)paren
id|mp-&gt;hash_prev-&gt;hash_next
op_assign
id|mp-&gt;hash_next
suffix:semicolon
r_else
(brace
m_assert
(paren
op_star
id|hash_ptr
op_eq
id|mp
)paren
suffix:semicolon
op_star
id|hash_ptr
op_assign
id|mp-&gt;hash_next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp-&gt;hash_next
)paren
id|mp-&gt;hash_next-&gt;hash_prev
op_assign
id|mp-&gt;hash_prev
suffix:semicolon
)brace
DECL|function|__get_metapage
r_struct
id|metapage
op_star
id|__get_metapage
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|lblock
comma
r_int
r_int
id|size
comma
r_int
id|absolute
comma
r_int
r_int
r_new
)paren
(brace
r_struct
id|metapage
op_star
op_star
id|hash_ptr
suffix:semicolon
r_int
id|l2BlocksPerPage
suffix:semicolon
r_int
id|l2bsize
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_struct
id|metapage
op_star
id|mp
suffix:semicolon
r_int
r_int
id|page_index
suffix:semicolon
r_int
r_int
id|page_offset
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;__get_metapage: inode = 0x%p, lblock = 0x%lx&quot;
comma
id|inode
comma
id|lblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|absolute
)paren
id|mapping
op_assign
id|inode-&gt;i_sb-&gt;s_bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_else
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|hash_ptr
op_assign
id|meta_hash
c_func
(paren
id|mapping
comma
id|lblock
)paren
suffix:semicolon
id|mp
op_assign
id|search_hash
c_func
(paren
id|hash_ptr
comma
id|mapping
comma
id|lblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
(brace
id|page_found
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_discard
comma
op_amp
id|mp-&gt;flag
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|jfs_error
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;__get_metapage: using a &quot;
l_string|&quot;discarded metapage&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|META_discard
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
)brace
id|mp-&gt;count
op_increment
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;__get_metapage: found 0x%p, in hash&quot;
comma
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;logical_size
op_ne
id|size
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|jfs_error
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;__get_metapage: mp-&gt;logical_size != size&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|lock_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|l2bsize
op_assign
id|inode-&gt;i_blkbits
suffix:semicolon
id|l2BlocksPerPage
op_assign
id|PAGE_CACHE_SHIFT
op_minus
id|l2bsize
suffix:semicolon
id|page_index
op_assign
id|lblock
op_rshift
id|l2BlocksPerPage
suffix:semicolon
id|page_offset
op_assign
(paren
id|lblock
op_minus
(paren
id|page_index
op_lshift
id|l2BlocksPerPage
)paren
)paren
op_lshift
id|l2bsize
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page_offset
op_plus
id|size
)paren
OG
id|PAGE_CACHE_SIZE
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|jfs_err
c_func
(paren
l_string|&quot;MetaData crosses page boundary!!&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Locks held on aggregate inode pages are usually&n;&t;&t; * not held long, and they are taken in critical code&n;&t;&t; * paths (committing dirty inodes, txCommit thread) &n;&t;&t; * &n;&t;&t; * Attempt to get metapage without blocking, tapping into&n;&t;&t; * reserves if necessary.&n;&t;&t; */
id|mp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|JFS_IP
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fileset
op_eq
id|AGGREGATE_I
)paren
(brace
id|mp
op_assign
id|mempool_alloc
c_func
(paren
id|metapage_mempool
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * mempool is supposed to protect us from&n;&t;&t;&t;&t; * failing here.  We will try a blocking&n;&t;&t;&t;&t; * call, but a deadlock is possible here&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;__get_metapage: atomic call to mempool_alloc failed.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Will attempt blocking call&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
(brace
r_struct
id|metapage
op_star
id|mp2
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|mp
op_assign
id|mempool_alloc
c_func
(paren
id|metapage_mempool
comma
id|GFP_NOFS
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
multiline_comment|/* we dropped the meta_lock, we need to search the&n;&t;&t;&t; * hash again.&n;&t;&t;&t; */
id|mp2
op_assign
id|search_hash
c_func
(paren
id|hash_ptr
comma
id|mapping
comma
id|lblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp2
)paren
(brace
id|free_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|mp
op_assign
id|mp2
suffix:semicolon
r_goto
id|page_found
suffix:semicolon
)brace
)brace
id|mp-&gt;flag
op_assign
l_int|0
suffix:semicolon
id|lock_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|absolute
)paren
id|set_bit
c_func
(paren
id|META_absolute
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|mp-&gt;xflag
op_assign
id|COMMIT_PAGE
suffix:semicolon
id|mp-&gt;count
op_assign
l_int|1
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mp-&gt;nohomeok
comma
l_int|0
)paren
suffix:semicolon
id|mp-&gt;mapping
op_assign
id|mapping
suffix:semicolon
id|mp-&gt;index
op_assign
id|lblock
suffix:semicolon
id|mp-&gt;page
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;logical_size
op_assign
id|size
suffix:semicolon
id|add_to_hash
c_func
(paren
id|mp
comma
id|hash_ptr
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
)paren
(brace
id|jfs_info
c_func
(paren
l_string|&quot;__get_metapage: Calling grab_cache_page&quot;
)paren
suffix:semicolon
id|mp-&gt;page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
id|page_index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mp-&gt;page
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;grab_cache_page failed!&quot;
)paren
suffix:semicolon
r_goto
id|freeit
suffix:semicolon
)brace
r_else
(brace
id|INCREMENT
c_func
(paren
id|mpStat.pagealloc
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|jfs_info
c_func
(paren
l_string|&quot;__get_metapage: Calling read_cache_page&quot;
)paren
suffix:semicolon
id|mp-&gt;page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|lblock
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|mp-&gt;page
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;read_cache_page failed!&quot;
)paren
suffix:semicolon
r_goto
id|freeit
suffix:semicolon
)brace
r_else
id|INCREMENT
c_func
(paren
id|mpStat.pagealloc
)paren
suffix:semicolon
)brace
id|mp-&gt;data
op_assign
id|kmap
c_func
(paren
id|mp-&gt;page
)paren
op_plus
id|page_offset
suffix:semicolon
)brace
id|jfs_info
c_func
(paren
l_string|&quot;__get_metapage: returning = 0x%p&quot;
comma
id|mp
)paren
suffix:semicolon
r_return
id|mp
suffix:semicolon
id|freeit
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|remove_from_hash
c_func
(paren
id|mp
comma
id|hash_ptr
)paren
suffix:semicolon
id|free_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hold_metapage
r_void
id|hold_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
comma
r_int
id|force
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|mp-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
(brace
id|ASSERT
(paren
op_logical_neg
(paren
id|test_bit
c_func
(paren
id|META_forced
comma
op_amp
id|mp-&gt;flag
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trylock_metapage
c_func
(paren
id|mp
)paren
)paren
id|set_bit
c_func
(paren
id|META_forced
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
)brace
r_else
id|lock_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
)brace
DECL|function|__write_metapage
r_static
r_void
id|__write_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_int
id|l2bsize
op_assign
id|mp-&gt;mapping-&gt;host-&gt;i_blkbits
suffix:semicolon
r_int
id|l2BlocksPerPage
op_assign
id|PAGE_CACHE_SHIFT
op_minus
id|l2bsize
suffix:semicolon
r_int
r_int
id|page_index
suffix:semicolon
r_int
r_int
id|page_offset
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;__write_metapage: mp = 0x%p&quot;
comma
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_discard
comma
op_amp
id|mp-&gt;flag
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This metadata is no longer valid&n;&t;&t; */
id|clear_bit
c_func
(paren
id|META_dirty
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|page_index
op_assign
id|mp-&gt;page-&gt;index
suffix:semicolon
id|page_offset
op_assign
(paren
id|mp-&gt;index
op_minus
(paren
id|page_index
op_lshift
id|l2BlocksPerPage
)paren
)paren
op_lshift
id|l2bsize
suffix:semicolon
id|lock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|rc
op_assign
id|mp-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|mp-&gt;page
comma
id|page_offset
comma
id|page_offset
op_plus
id|mp-&gt;logical_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;prepare_write return %d!&quot;
comma
id|rc
)paren
suffix:semicolon
id|ClearPageUptodate
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|META_dirty
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|rc
op_assign
id|mp-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|mp-&gt;page
comma
id|page_offset
comma
id|page_offset
op_plus
id|mp-&gt;logical_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;commit_write returned %d&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|META_dirty
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;__write_metapage done&quot;
)paren
suffix:semicolon
)brace
DECL|function|sync_metapage
r_static
r_inline
r_void
id|sync_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|mp-&gt;page
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* we&squot;re done with this page - no need to check for errors */
r_if
c_cond
(paren
id|page_has_buffers
c_func
(paren
id|page
)paren
)paren
id|write_one_page
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
r_else
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|release_metapage
r_void
id|release_metapage
c_func
(paren
r_struct
id|metapage
op_star
id|mp
)paren
(brace
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;release_metapage: mp = 0x%p, flag = 0x%lx&quot;
comma
id|mp
comma
id|mp-&gt;flag
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_forced
comma
op_amp
id|mp-&gt;flag
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|META_forced
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|mp-&gt;count
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
m_assert
(paren
id|mp-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|mp-&gt;count
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|mp-&gt;nohomeok
)paren
)paren
(brace
id|unlock_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|remove_from_hash
c_func
(paren
id|mp
comma
id|meta_hash
c_func
(paren
id|mp-&gt;mapping
comma
id|mp-&gt;index
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;page
)paren
(brace
id|kunmap
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|mp-&gt;data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_dirty
comma
op_amp
id|mp-&gt;flag
)paren
)paren
id|__write_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_sync
comma
op_amp
id|mp-&gt;flag
)paren
)paren
(brace
id|sync_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|META_sync
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|META_discard
comma
op_amp
id|mp-&gt;flag
)paren
)paren
(brace
id|lock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|block_invalidatepage
c_func
(paren
id|mp-&gt;page
comma
l_int|0
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
)brace
id|page_cache_release
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|INCREMENT
c_func
(paren
id|mpStat.pagefree
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp-&gt;lsn
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Remove metapage from logsynclist.&n;&t;&t;&t; */
id|log
op_assign
id|mp-&gt;log
suffix:semicolon
id|LOGSYNC_LOCK
c_func
(paren
id|log
)paren
suffix:semicolon
id|mp-&gt;log
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;lsn
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;clsn
op_assign
l_int|0
suffix:semicolon
id|log-&gt;count
op_decrement
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|mp-&gt;synclist
)paren
suffix:semicolon
id|LOGSYNC_UNLOCK
c_func
(paren
id|log
)paren
suffix:semicolon
)brace
id|free_metapage
c_func
(paren
id|mp
)paren
suffix:semicolon
)brace
)brace
DECL|function|__invalidate_metapages
r_void
id|__invalidate_metapages
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|addr
comma
r_int
id|len
)paren
(brace
r_struct
id|metapage
op_star
op_star
id|hash_ptr
suffix:semicolon
r_int
r_int
id|lblock
suffix:semicolon
r_int
id|l2BlocksPerPage
op_assign
id|PAGE_CACHE_SHIFT
op_minus
id|ip-&gt;i_blkbits
suffix:semicolon
multiline_comment|/* All callers are interested in block device&squot;s mapping */
r_struct
id|address_space
op_star
id|mapping
op_assign
id|ip-&gt;i_sb-&gt;s_bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_struct
id|metapage
op_star
id|mp
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/*&n;&t; * First, mark metapages to discard.  They will eventually be&n;&t; * released, but should not be written.&n;&t; */
r_for
c_loop
(paren
id|lblock
op_assign
id|addr
suffix:semicolon
id|lblock
OL
id|addr
op_plus
id|len
suffix:semicolon
id|lblock
op_add_assign
l_int|1
op_lshift
id|l2BlocksPerPage
)paren
(brace
id|hash_ptr
op_assign
id|meta_hash
c_func
(paren
id|mapping
comma
id|lblock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|mp
op_assign
id|search_hash
c_func
(paren
id|hash_ptr
comma
id|mapping
comma
id|lblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
(brace
id|set_bit
c_func
(paren
id|META_discard
comma
op_amp
id|mp-&gt;flag
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|lock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
id|block_invalidatepage
c_func
(paren
id|mp-&gt;page
comma
l_int|0
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|mp-&gt;page
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|meta_lock
)paren
suffix:semicolon
id|page
op_assign
id|find_lock_page
c_func
(paren
id|mapping
comma
id|lblock
op_rshift
id|l2BlocksPerPage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|block_invalidatepage
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#ifdef CONFIG_JFS_STATISTICS
DECL|function|jfs_mpstat_read
r_int
id|jfs_mpstat_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;JFS Metapage statistics&bslash;n&quot;
l_string|&quot;=======================&bslash;n&quot;
l_string|&quot;page allocations = %d&bslash;n&quot;
l_string|&quot;page frees = %d&bslash;n&quot;
l_string|&quot;lock waits = %d&bslash;n&quot;
comma
id|mpStat.pagealloc
comma
id|mpStat.pagefree
comma
id|mpStat.lockwait
)paren
suffix:semicolon
id|begin
op_assign
id|offset
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_else
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
eof
