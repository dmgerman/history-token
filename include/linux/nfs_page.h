multiline_comment|/*&n; * linux/include/linux/nfs_page.h&n; *&n; * Copyright (C) 2000 Trond Myklebust&n; *&n; * NFS page cache wrapper.&n; */
macro_line|#ifndef _LINUX_NFS_PAGE_H
DECL|macro|_LINUX_NFS_PAGE_H
mdefine_line|#define _LINUX_NFS_PAGE_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/nfs_fs_sb.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/nfs_xdr.h&gt;
multiline_comment|/*&n; * Valid flags for a dirty buffer&n; */
DECL|macro|PG_BUSY
mdefine_line|#define PG_BUSY&t;&t;&t;0
DECL|struct|nfs_page
r_struct
id|nfs_page
(brace
DECL|member|wb_hash
r_struct
id|list_head
id|wb_hash
comma
multiline_comment|/* Inode */
DECL|member|wb_lru
id|wb_lru
comma
multiline_comment|/* superblock lru list */
DECL|member|wb_list
id|wb_list
comma
multiline_comment|/* Defines state of page: */
DECL|member|wb_list_head
op_star
id|wb_list_head
suffix:semicolon
multiline_comment|/*      read/write/commit */
DECL|member|wb_file
r_struct
id|file
op_star
id|wb_file
suffix:semicolon
DECL|member|wb_inode
r_struct
id|inode
op_star
id|wb_inode
suffix:semicolon
DECL|member|wb_cred
r_struct
id|rpc_cred
op_star
id|wb_cred
suffix:semicolon
DECL|member|wb_page
r_struct
id|page
op_star
id|wb_page
suffix:semicolon
multiline_comment|/* page to read in/write out */
DECL|member|wb_wait
id|wait_queue_head_t
id|wb_wait
suffix:semicolon
multiline_comment|/* wait queue */
DECL|member|wb_timeout
r_int
r_int
id|wb_timeout
suffix:semicolon
multiline_comment|/* when to read/write/commit */
DECL|member|wb_offset
r_int
r_int
id|wb_offset
comma
multiline_comment|/* Offset of read/write */
DECL|member|wb_bytes
id|wb_bytes
comma
multiline_comment|/* Length of request */
DECL|member|wb_count
id|wb_count
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|wb_flags
r_int
r_int
id|wb_flags
suffix:semicolon
DECL|member|wb_verf
r_struct
id|nfs_writeverf
id|wb_verf
suffix:semicolon
multiline_comment|/* Commit cookie */
)brace
suffix:semicolon
DECL|macro|NFS_WBACK_BUSY
mdefine_line|#define NFS_WBACK_BUSY(req)&t;(test_bit(PG_BUSY,&amp;(req)-&gt;wb_flags))
r_extern
r_struct
id|nfs_page
op_star
id|nfs_create_request
c_func
(paren
r_struct
id|rpc_cred
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|page
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
r_void
id|nfs_clear_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|nfs_release_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|nfs_list_add_request
c_func
(paren
r_struct
id|nfs_page
op_star
comma
r_struct
id|list_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_scan_lru
c_func
(paren
r_struct
id|list_head
op_star
comma
r_struct
id|list_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_scan_lru_timeout
c_func
(paren
r_struct
id|list_head
op_star
comma
r_struct
id|list_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_scan_list
c_func
(paren
r_struct
id|list_head
op_star
comma
r_struct
id|list_head
op_star
comma
r_struct
id|file
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
id|nfs_coalesce_requests
c_func
(paren
r_struct
id|list_head
op_star
comma
r_struct
id|list_head
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_wait_on_request
c_func
(paren
r_struct
id|nfs_page
op_star
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|nfs_wreq_lock
suffix:semicolon
multiline_comment|/*&n; * Lock the page of an asynchronous request without incrementing the wb_count&n; */
r_static
r_inline
r_int
DECL|function|nfs_lock_request_dontget
id|nfs_lock_request_dontget
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
id|test_and_set_bit
c_func
(paren
id|PG_BUSY
comma
op_amp
id|req-&gt;wb_flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Lock the page of an asynchronous request&n; */
r_static
r_inline
r_int
DECL|function|nfs_lock_request
id|nfs_lock_request
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
id|test_and_set_bit
c_func
(paren
id|PG_BUSY
comma
op_amp
id|req-&gt;wb_flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|req-&gt;wb_count
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|nfs_unlock_request
id|nfs_unlock_request
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
op_logical_neg
id|NFS_WBACK_BUSY
c_func
(paren
id|req
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NFS: Invalid unlock attempted&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|smp_mb__before_clear_bit
c_func
(paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_BUSY
comma
op_amp
id|req-&gt;wb_flags
)paren
suffix:semicolon
id|smp_mb__after_clear_bit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|req-&gt;wb_wait
)paren
)paren
id|wake_up_all
c_func
(paren
op_amp
id|req-&gt;wb_wait
)paren
suffix:semicolon
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_list_remove_request - Remove a request from its wb_list&n; * @req: request&n; */
r_static
r_inline
r_void
DECL|function|nfs_list_remove_request
id|nfs_list_remove_request
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
id|list_empty
c_func
(paren
op_amp
id|req-&gt;wb_list
)paren
)paren
r_return
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NFS: unlocked request attempted removed from list!&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;wb_list
)paren
suffix:semicolon
id|req-&gt;wb_list_head
op_assign
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|nfs_page
op_star
DECL|function|nfs_list_entry
id|nfs_list_entry
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|nfs_page
comma
id|wb_list
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|nfs_page
op_star
DECL|function|nfs_inode_wb_entry
id|nfs_inode_wb_entry
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|nfs_page
comma
id|wb_hash
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__nfs_add_lru
id|__nfs_add_lru
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|req-&gt;wb_lru
comma
id|head
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__nfs_del_lru
id|__nfs_del_lru
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
id|list_empty
c_func
(paren
op_amp
id|req-&gt;wb_lru
)paren
)paren
r_return
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;wb_lru
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|nfs_page
op_star
DECL|function|nfs_lru_entry
id|nfs_lru_entry
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|nfs_page
comma
id|wb_lru
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_NFS_PAGE_H */
eof
