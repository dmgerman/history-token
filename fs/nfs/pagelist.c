multiline_comment|/*&n; * linux/fs/nfs/pagelist.c&n; *&n; * A set of helper functions for managing NFS read and write requests.&n; * The main purpose of these routines is to provide support for the&n; * coalescing of several requests into a single RPC call.&n; *&n; * Copyright 2000, 2001 (c) Trond Myklebust &lt;trond.myklebust@fys.uio.no&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs3.h&gt;
macro_line|#include &lt;linux/nfs4.h&gt;
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
DECL|macro|NFS_PARANOIA
mdefine_line|#define NFS_PARANOIA 1
multiline_comment|/*&n; * Spinlock&n; */
DECL|variable|nfs_wreq_lock
id|spinlock_t
id|nfs_wreq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|nfs_page_cachep
r_static
id|kmem_cache_t
op_star
id|nfs_page_cachep
suffix:semicolon
r_static
r_inline
r_struct
id|nfs_page
op_star
DECL|function|nfs_page_alloc
id|nfs_page_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|nfs_page
op_star
id|p
suffix:semicolon
id|p
op_assign
id|kmem_cache_alloc
c_func
(paren
id|nfs_page_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|p-&gt;wb_list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|p-&gt;wb_wait
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|nfs_page_free
id|nfs_page_free
c_func
(paren
r_struct
id|nfs_page
op_star
id|p
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|nfs_page_cachep
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_create_request - Create an NFS read/write request.&n; * @file: file descriptor to use&n; * @inode: inode to which the request is attached&n; * @page: page to write&n; * @offset: starting offset within the page for the write&n; * @count: number of bytes to read/write&n; *&n; * The page must be locked by the caller. This makes sure we never&n; * create two different requests for the same page, and avoids&n; * a possible deadlock when we reach the hard limit on the number&n; * of dirty pages.&n; * User should ensure it is safe to sleep in this function.&n; */
r_struct
id|nfs_page
op_star
DECL|function|nfs_create_request
id|nfs_create_request
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|nfs_server
op_star
id|server
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
multiline_comment|/* Deal with hard limits.  */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* try to allocate the request struct */
id|req
op_assign
id|nfs_page_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_ne
l_int|NULL
)paren
r_break
suffix:semicolon
multiline_comment|/* Try to free up at least one request in order to stay&n;&t;&t; * below the hard limit&n;&t;&t; */
r_if
c_cond
(paren
id|signalled
c_func
(paren
)paren
op_logical_and
(paren
id|server-&gt;flags
op_amp
id|NFS_MOUNT_INTR
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ERESTARTSYS
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the request struct. Initially, we assume a&n;&t; * long write-back delay. This will be adjusted in&n;&t; * update_nfs_request below if the region is not locked. */
id|req-&gt;wb_page
op_assign
id|page
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|req-&gt;wb_complete
comma
l_int|0
)paren
suffix:semicolon
id|req-&gt;wb_index
op_assign
id|page-&gt;index
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|req-&gt;wb_offset
op_assign
id|offset
suffix:semicolon
id|req-&gt;wb_pgbase
op_assign
id|offset
suffix:semicolon
id|req-&gt;wb_bytes
op_assign
id|count
suffix:semicolon
id|req-&gt;wb_inode
op_assign
id|inode
suffix:semicolon
id|req-&gt;wb_count
op_assign
l_int|1
suffix:semicolon
id|server-&gt;rpc_ops
op_member_access_from_pointer
id|request_init
c_func
(paren
id|req
comma
id|file
)paren
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_clear_request - Free up all resources allocated to the request&n; * @req:&n; *&n; * Release all resources associated with a write request after it&n; * has completed.&n; */
DECL|function|nfs_clear_request
r_void
id|nfs_clear_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;wb_state
)paren
id|req-&gt;wb_state
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Release struct file or cached credential */
r_if
c_cond
(paren
id|req-&gt;wb_file
)paren
(brace
id|fput
c_func
(paren
id|req-&gt;wb_file
)paren
suffix:semicolon
id|req-&gt;wb_file
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;wb_cred
)paren
(brace
id|put_rpccred
c_func
(paren
id|req-&gt;wb_cred
)paren
suffix:semicolon
id|req-&gt;wb_cred
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;wb_page
)paren
(brace
id|page_cache_release
c_func
(paren
id|req-&gt;wb_page
)paren
suffix:semicolon
id|req-&gt;wb_page
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * nfs_release_request - Release the count on an NFS read/write request&n; * @req: request to release&n; *&n; * Note: Should never be called with the spinlock held!&n; */
r_void
DECL|function|nfs_release_request
id|nfs_release_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|req-&gt;wb_count
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
macro_line|#ifdef NFS_PARANOIA
id|BUG_ON
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|req-&gt;wb_list
)paren
)paren
suffix:semicolon
id|BUG_ON
(paren
id|NFS_WBACK_BUSY
c_func
(paren
id|req
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Release struct file or cached credential */
id|nfs_clear_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_page_free
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_list_add_request - Insert a request into a sorted list&n; * @req: request&n; * @head: head of list into which to insert the request.&n; *&n; * Note that the wb_list is sorted by page index in order to facilitate&n; * coalescing of requests.&n; * We use an insertion sort that is optimized for the case of appended&n; * writes.&n; */
r_void
DECL|function|nfs_list_add_request
id|nfs_list_add_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
macro_line|#ifdef NFS_PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|req-&gt;wb_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NFS: Add to list failed!&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|list_for_each_prev
c_func
(paren
id|pos
comma
id|head
)paren
(brace
r_struct
id|nfs_page
op_star
id|p
op_assign
id|nfs_list_entry
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;wb_index
OL
id|req-&gt;wb_index
)paren
r_break
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|req-&gt;wb_list
comma
id|pos
)paren
suffix:semicolon
id|req-&gt;wb_list_head
op_assign
id|head
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_wait_on_request - Wait for a request to complete.&n; * @req: request to wait upon.&n; *&n; * Interruptible by signals only if mounted with intr flag.&n; * The user is responsible for holding a count on the request.&n; */
r_int
DECL|function|nfs_wait_on_request
id|nfs_wait_on_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|req-&gt;wb_inode
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NFS_WBACK_BUSY
c_func
(paren
id|req
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|nfs_wait_event
c_func
(paren
id|clnt
comma
id|req-&gt;wb_wait
comma
op_logical_neg
id|NFS_WBACK_BUSY
c_func
(paren
id|req
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_coalesce_requests - Split coalesced requests out from a list.&n; * @head: source list&n; * @dst: destination list&n; * @nmax: maximum number of requests to coalesce&n; *&n; * Moves a maximum of &squot;nmax&squot; elements from one list to another.&n; * The elements are checked to ensure that they form a contiguous set&n; * of pages, and that the RPC credentials are the same.&n; */
r_int
DECL|function|nfs_coalesce_requests
id|nfs_coalesce_requests
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|list_head
op_star
id|dst
comma
r_int
r_int
id|nmax
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|npages
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|head
)paren
)paren
(brace
r_struct
id|nfs_page
op_star
id|prev
op_assign
id|req
suffix:semicolon
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|head-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;wb_cred
op_ne
id|prev-&gt;wb_cred
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;wb_index
op_ne
(paren
id|prev-&gt;wb_index
op_plus
l_int|1
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;wb_pgbase
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
id|req
comma
id|dst
)paren
suffix:semicolon
id|npages
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;wb_pgbase
op_plus
id|req-&gt;wb_bytes
op_ne
id|PAGE_CACHE_SIZE
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|npages
op_ge
id|nmax
)paren
r_break
suffix:semicolon
)brace
r_return
id|npages
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_scan_list - Scan a list for matching requests&n; * @head: One of the NFS inode request lists&n; * @dst: Destination list&n; * @idx_start: lower bound of page-&gt;index to scan&n; * @npages: idx_start + npages sets the upper bound to scan.&n; *&n; * Moves elements from one of the inode request lists.&n; * If the number of requests is set to 0, the entire address_space&n; * starting at index idx_start, is scanned.&n; * The requests are *not* checked to ensure that they form a contiguous set.&n; * You must be holding the nfs_wreq_lock when calling this function&n; */
r_int
DECL|function|nfs_scan_list
id|nfs_scan_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|list_head
op_star
id|dst
comma
r_int
r_int
id|idx_start
comma
r_int
r_int
id|npages
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_int
r_int
id|idx_end
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|npages
op_eq
l_int|0
)paren
id|idx_end
op_assign
op_complement
l_int|0
suffix:semicolon
r_else
id|idx_end
op_assign
id|idx_start
op_plus
id|npages
op_minus
l_int|1
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
id|head
)paren
(brace
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;wb_index
OL
id|idx_start
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;wb_index
OG
id|idx_end
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nfs_lock_request
c_func
(paren
id|req
)paren
)paren
r_continue
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
id|req
comma
id|dst
)paren
suffix:semicolon
id|res
op_increment
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|nfs_init_nfspagecache
r_int
id|nfs_init_nfspagecache
c_func
(paren
r_void
)paren
(brace
id|nfs_page_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;nfs_page&quot;
comma
r_sizeof
(paren
r_struct
id|nfs_page
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfs_page_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nfs_destroy_nfspagecache
r_void
id|nfs_destroy_nfspagecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|nfs_page_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;nfs_page: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
