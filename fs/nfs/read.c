multiline_comment|/*&n; * linux/fs/nfs/read.c&n; *&n; * Block I/O for NFS&n; *&n; * Partial copy of Linus&squot; read cache modifications to fs/nfs/file.c&n; * modified for async RPC by okir@monad.swb.de&n; *&n; * We do an ugly hack here in order to return proper error codes to the&n; * user program when a read request failed: since generic_file_read&n; * only checks the return value of inode-&gt;i_op-&gt;readpage() which is always 0&n; * for async RPC, we set the error bit of the page to 1 when an error occurs,&n; * and make nfs_readpage transmit requests synchronously when encountering this.&n; * This is only a small problem, though, since we now retry all operations&n; * within the RPC code when root squashing is suspected.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_PAGECACHE
r_static
r_int
id|nfs_pagein_one
c_func
(paren
r_struct
id|list_head
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|variable|nfs_rdata_cachep
r_static
id|kmem_cache_t
op_star
id|nfs_rdata_cachep
suffix:semicolon
DECL|variable|nfs_rdata_mempool
r_static
id|mempool_t
op_star
id|nfs_rdata_mempool
suffix:semicolon
DECL|macro|MIN_POOL_READ
mdefine_line|#define MIN_POOL_READ&t;(32)
DECL|function|nfs_readdata_alloc
r_static
id|__inline__
r_struct
id|nfs_read_data
op_star
id|nfs_readdata_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|nfs_read_data
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|nfs_read_data
op_star
)paren
id|mempool_alloc
c_func
(paren
id|nfs_rdata_mempool
comma
id|SLAB_NOFS
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
id|p-&gt;pages
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|nfs_readdata_free
r_static
id|__inline__
r_void
id|nfs_readdata_free
c_func
(paren
r_struct
id|nfs_read_data
op_star
id|p
)paren
(brace
id|mempool_free
c_func
(paren
id|p
comma
id|nfs_rdata_mempool
)paren
suffix:semicolon
)brace
DECL|function|nfs_readdata_release
r_void
id|nfs_readdata_release
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs_read_data
op_star
id|data
op_assign
(paren
r_struct
id|nfs_read_data
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
id|nfs_readdata_free
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page synchronously.&n; */
r_static
r_int
DECL|function|nfs_readpage_sync
id|nfs_readpage_sync
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
)paren
(brace
r_struct
id|rpc_cred
op_star
id|cred
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rsize
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
suffix:semicolon
r_int
r_int
id|count
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|flags
op_assign
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
ques
c_cond
id|NFS_RPC_SWAPFLAGS
suffix:colon
l_int|0
suffix:semicolon
r_int
id|eof
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage_sync(%p)&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|cred
op_assign
id|nfs_file_cred
c_func
(paren
id|file
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This works now because the socket layer never tries to DMA&n;&t; * into this buffer directly.&n;&t; */
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|rsize
)paren
id|rsize
op_assign
id|count
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_proc_read(%s, (%s/%Ld), %Lu, %u)&bslash;n&quot;
comma
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|hostname
comma
id|inode-&gt;i_sb-&gt;s_id
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|inode
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|offset
comma
id|rsize
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
id|cred
comma
op_amp
id|fattr
comma
id|flags
comma
id|offset
comma
id|rsize
comma
id|page
comma
op_amp
id|eof
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Even if we had a partial success we can&squot;t mark the page&n;&t;&t; * cache valid.&n;&t;&t; */
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EISDIR
)paren
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|io_error
suffix:semicolon
)brace
id|count
op_sub_assign
id|result
suffix:semicolon
id|offset
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|rsize
)paren
multiline_comment|/* NFSv2ism */
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
id|memclear_highpage_flush
c_func
(paren
id|page
comma
id|offset
comma
id|count
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
id|ClearPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|io_error
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_readpage_async
id|nfs_readpage_async
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
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|one_request
)paren
suffix:semicolon
r_struct
id|nfs_page
op_star
r_new
suffix:semicolon
r_new
op_assign
id|nfs_create_request
c_func
(paren
id|nfs_file_cred
c_func
(paren
id|file
)paren
comma
id|inode
comma
id|page
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
r_new
)paren
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
id|nfs_lock_request
c_func
(paren
r_new
)paren
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
r_new
comma
op_amp
id|one_request
)paren
suffix:semicolon
id|nfs_pagein_one
c_func
(paren
op_amp
id|one_request
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the NFS read request struct&n; */
r_static
r_void
DECL|function|nfs_read_rpcsetup
id|nfs_read_rpcsetup
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|nfs_read_data
op_star
id|data
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|pages
op_assign
id|data-&gt;pagevec
suffix:semicolon
id|count
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
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|head-&gt;next
)paren
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
op_amp
id|data-&gt;pages
)paren
suffix:semicolon
op_star
id|pages
op_increment
op_assign
id|req-&gt;wb_page
suffix:semicolon
id|count
op_add_assign
id|req-&gt;wb_bytes
suffix:semicolon
)brace
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|data-&gt;pages.next
)paren
suffix:semicolon
id|data-&gt;inode
op_assign
id|inode
op_assign
id|req-&gt;wb_inode
suffix:semicolon
id|data-&gt;cred
op_assign
id|req-&gt;wb_cred
suffix:semicolon
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|read_setup
c_func
(paren
id|data
comma
id|count
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: %4d initiated read call (req %s/%Ld, %u bytes @ offset %Lu.&bslash;n&quot;
comma
id|data-&gt;task.tk_pid
comma
id|inode-&gt;i_sb-&gt;s_id
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|inode
)paren
comma
id|count
comma
(paren
r_int
r_int
r_int
)paren
id|req_offset
c_func
(paren
id|req
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|nfs_async_read_error
id|nfs_async_read_error
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_struct
id|page
op_star
id|page
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
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|head-&gt;next
)paren
suffix:semicolon
id|page
op_assign
id|req-&gt;wb_page
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|nfs_clear_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_unlock_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|nfs_pagein_one
id|nfs_pagein_one
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
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
r_struct
id|nfs_read_data
op_star
id|data
suffix:semicolon
id|sigset_t
id|oldset
suffix:semicolon
id|data
op_assign
id|nfs_readdata_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_goto
id|out_bad
suffix:semicolon
id|nfs_read_rpcsetup
c_func
(paren
id|head
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Start the async call */
id|rpc_clnt_sigmask
c_func
(paren
id|clnt
comma
op_amp
id|oldset
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|rpc_execute
c_func
(paren
op_amp
id|data-&gt;task
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|rpc_clnt_sigunmask
c_func
(paren
id|clnt
comma
op_amp
id|oldset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_bad
suffix:colon
id|nfs_async_read_error
c_func
(paren
id|head
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_int
DECL|function|nfs_pagein_list
id|nfs_pagein_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_int
id|rpages
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|one_request
)paren
suffix:semicolon
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pages
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
id|pages
op_add_assign
id|nfs_coalesce_requests
c_func
(paren
id|head
comma
op_amp
id|one_request
comma
id|rpages
)paren
suffix:semicolon
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|one_request.next
)paren
suffix:semicolon
id|error
op_assign
id|nfs_pagein_one
c_func
(paren
op_amp
id|one_request
comma
id|req-&gt;wb_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
r_return
id|pages
suffix:semicolon
id|nfs_async_read_error
c_func
(paren
id|head
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the callback from RPC telling us whether a reply was&n; * received or some error occurred (timeout or socket shutdown).&n; */
r_void
DECL|function|nfs_readpage_result
id|nfs_readpage_result
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs_read_data
op_star
id|data
op_assign
(paren
r_struct
id|nfs_read_data
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_struct
id|nfs_fattr
op_star
id|fattr
op_assign
op_amp
id|data-&gt;fattr
suffix:semicolon
r_int
r_int
id|count
op_assign
id|data-&gt;res.count
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: %4d nfs_readpage_result, (status %d)&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_status
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|data-&gt;pages
)paren
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|data-&gt;pages.next
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|req-&gt;wb_page
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
OL
id|PAGE_CACHE_SIZE
)paren
(brace
id|memclear_highpage_flush
c_func
(paren
id|page
comma
id|req-&gt;wb_pgbase
op_plus
id|count
comma
id|req-&gt;wb_bytes
op_minus
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;res.eof
op_logical_or
(paren
(paren
id|fattr-&gt;valid
op_amp
id|NFS_ATTR_FATTR
)paren
op_logical_and
(paren
(paren
id|req_offset
c_func
(paren
id|req
)paren
op_plus
id|count
)paren
op_ge
id|fattr-&gt;size
)paren
)paren
)paren
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|count
OL
id|req-&gt;wb_bytes
)paren
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|count
op_sub_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
r_else
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: read (%s/%Ld %d@%Ld)&bslash;n&quot;
comma
id|req-&gt;wb_inode-&gt;i_sb-&gt;s_id
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|req-&gt;wb_inode
)paren
comma
id|req-&gt;wb_bytes
comma
(paren
r_int
r_int
)paren
id|req_offset
c_func
(paren
id|req
)paren
)paren
suffix:semicolon
id|nfs_clear_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_unlock_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Read a page over NFS.&n; * We read the page synchronously in the following cases:&n; *  -&t;The NFS rsize is smaller than PAGE_CACHE_SIZE. We could kludge our way&n; *&t;around this by creating several consecutive read requests, but&n; *&t;that&squot;s hardly worth it.&n; *  -&t;The error flag is set for this page. This happens only when a&n; *&t;previous async read operation failed.&n; */
r_int
DECL|function|nfs_readpage
id|nfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage (%p %ld@%lu)&bslash;n&quot;
comma
id|page
comma
id|PAGE_CACHE_SIZE
comma
id|page-&gt;index
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to flush any pending writes to the file..&n;&t; *&n;&t; * NOTE! Because we own the page lock, there cannot&n;&t; * be any new pending writes generated at this point&n;&t; * for this page (other pages can be written to).&n;&t; */
id|error
op_assign
id|nfs_wb_page
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageError
c_func
(paren
id|page
)paren
op_logical_and
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
op_ge
id|PAGE_CACHE_SIZE
)paren
(brace
id|error
op_assign
id|nfs_readpage_async
c_func
(paren
id|file
comma
id|inode
comma
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
id|nfs_readpage_sync
c_func
(paren
id|file
comma
id|inode
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
op_logical_and
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Aiee.. nfs swap-in of page failed!&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_error
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|struct|nfs_readdesc
r_struct
id|nfs_readdesc
(brace
DECL|member|head
r_struct
id|list_head
op_star
id|head
suffix:semicolon
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|readpage_sync_filler
id|readpage_sync_filler
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|nfs_readdesc
op_star
id|desc
op_assign
(paren
r_struct
id|nfs_readdesc
op_star
)paren
id|data
suffix:semicolon
r_return
id|nfs_readpage_sync
c_func
(paren
id|desc-&gt;filp
comma
id|page-&gt;mapping-&gt;host
comma
id|page
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|readpage_async_filler
id|readpage_async_filler
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|nfs_readdesc
op_star
id|desc
op_assign
(paren
r_struct
id|nfs_readdesc
op_star
)paren
id|data
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|nfs_page
op_star
r_new
suffix:semicolon
id|nfs_wb_page
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
r_new
op_assign
id|nfs_create_request
c_func
(paren
id|nfs_file_cred
c_func
(paren
id|desc-&gt;filp
)paren
comma
id|inode
comma
id|page
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
r_new
)paren
)paren
(brace
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
id|nfs_lock_request
c_func
(paren
r_new
)paren
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
r_new
comma
id|desc-&gt;head
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|nfs_readpages
id|nfs_readpages
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
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
r_int
id|nr_pages
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
r_struct
id|nfs_readdesc
id|desc
op_assign
(brace
dot
id|filp
op_assign
id|filp
comma
dot
id|head
op_assign
op_amp
id|head
comma
)brace
suffix:semicolon
r_struct
id|nfs_server
op_star
id|server
op_assign
id|NFS_SERVER
c_func
(paren
id|mapping-&gt;host
)paren
suffix:semicolon
r_int
id|is_sync
op_assign
id|server-&gt;rsize
OL
id|PAGE_CACHE_SIZE
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|read_cache_pages
c_func
(paren
id|mapping
comma
id|pages
comma
id|is_sync
ques
c_cond
id|readpage_sync_filler
suffix:colon
id|readpage_async_filler
comma
op_amp
id|desc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|head
)paren
)paren
(brace
r_int
id|err
op_assign
id|nfs_pagein_list
c_func
(paren
op_amp
id|head
comma
id|server-&gt;rpages
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|err
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nfs_init_readpagecache
r_int
id|nfs_init_readpagecache
c_func
(paren
r_void
)paren
(brace
id|nfs_rdata_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;nfs_read_data&quot;
comma
r_sizeof
(paren
r_struct
id|nfs_read_data
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
id|nfs_rdata_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|nfs_rdata_mempool
op_assign
id|mempool_create
c_func
(paren
id|MIN_POOL_READ
comma
id|mempool_alloc_slab
comma
id|mempool_free_slab
comma
id|nfs_rdata_cachep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfs_rdata_mempool
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
DECL|function|nfs_destroy_readpagecache
r_void
id|nfs_destroy_readpagecache
c_func
(paren
r_void
)paren
(brace
id|mempool_destroy
c_func
(paren
id|nfs_rdata_mempool
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|nfs_rdata_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;nfs_read_data: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
