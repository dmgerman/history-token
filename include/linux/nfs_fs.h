multiline_comment|/*&n; *  linux/include/linux/nfs_fs.h&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  OS-specific nfs filesystem definitions and declarations&n; */
macro_line|#ifndef _LINUX_NFS_FS_H
DECL|macro|_LINUX_NFS_FS_H
mdefine_line|#define _LINUX_NFS_FS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/nfs_fs_sb.h&gt;
macro_line|#include &lt;linux/sunrpc/debug.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs3.h&gt;
macro_line|#include &lt;linux/nfs4.h&gt;
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/nfs_xdr.h&gt;
multiline_comment|/*&n; * Enable debugging support for nfs client.&n; * Requires RPC_DEBUG.&n; */
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFS_DEBUG
macro_line|# define NFS_DEBUG
macro_line|#endif
DECL|macro|NFS_MAX_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_MAX_FILE_IO_BUFFER_SIZE&t;32768
DECL|macro|NFS_DEF_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_DEF_FILE_IO_BUFFER_SIZE&t;4096
multiline_comment|/*&n; * The upper limit on timeouts for the exponential backoff algorithm.&n; */
DECL|macro|NFS_WRITEBACK_DELAY
mdefine_line|#define NFS_WRITEBACK_DELAY&t;&t;(5*HZ)
DECL|macro|NFS_WRITEBACK_LOCKDELAY
mdefine_line|#define NFS_WRITEBACK_LOCKDELAY&t;&t;(60*HZ)
DECL|macro|NFS_COMMIT_DELAY
mdefine_line|#define NFS_COMMIT_DELAY&t;&t;(5*HZ)
multiline_comment|/*&n; * superblock magic number for NFS&n; */
DECL|macro|NFS_SUPER_MAGIC
mdefine_line|#define NFS_SUPER_MAGIC&t;&t;&t;0x6969
multiline_comment|/*&n; * These are the default flags for swap requests&n; */
DECL|macro|NFS_RPC_SWAPFLAGS
mdefine_line|#define NFS_RPC_SWAPFLAGS&t;&t;(RPC_TASK_SWAPPER|RPC_TASK_ROOTCREDS)
DECL|macro|NFS_RW_SYNC
mdefine_line|#define NFS_RW_SYNC&t;&t;0x0001&t;/* O_SYNC handling */
DECL|macro|NFS_RW_SWAP
mdefine_line|#define NFS_RW_SWAP&t;&t;0x0002&t;/* This is a swap request */
multiline_comment|/*&n; * When flushing a cluster of dirty pages, there can be different&n; * strategies:&n; */
DECL|macro|FLUSH_AGING
mdefine_line|#define FLUSH_AGING&t;&t;0&t;/* only flush old buffers */
DECL|macro|FLUSH_SYNC
mdefine_line|#define FLUSH_SYNC&t;&t;1&t;/* file being synced, or contention */
DECL|macro|FLUSH_WAIT
mdefine_line|#define FLUSH_WAIT&t;&t;2&t;/* wait for completion */
DECL|macro|FLUSH_STABLE
mdefine_line|#define FLUSH_STABLE&t;&t;4&t;/* commit to stable storage */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * NFSv3 Access mode cache&n; */
DECL|struct|nfs_access_cache
r_struct
id|nfs_access_cache
(brace
DECL|member|jiffies
r_int
r_int
id|jiffies
suffix:semicolon
DECL|member|cred
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
DECL|member|mask
r_int
id|mask
suffix:semicolon
DECL|member|err
r_int
id|err
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * nfs fs inode data in memory&n; */
DECL|struct|nfs_inode
r_struct
id|nfs_inode
(brace
multiline_comment|/*&n;&t; * The 64bit &squot;inode number&squot;&n;&t; */
DECL|member|fileid
id|__u64
id|fileid
suffix:semicolon
multiline_comment|/*&n;&t; * NFS file handle&n;&t; */
DECL|member|fh
r_struct
id|nfs_fh
id|fh
suffix:semicolon
multiline_comment|/*&n;&t; * Various flags&n;&t; */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * read_cache_jiffies is when we started read-caching this inode,&n;&t; * and read_cache_mtime is the mtime of the inode at that time.&n;&t; * attrtimeo is for how long the cached information is assumed&n;&t; * to be valid. A successful attribute revalidation doubles&n;&t; * attrtimeo (up to acregmax/acdirmax), a failure resets it to&n;&t; * acregmin/acdirmin.&n;&t; *&n;&t; * We need to revalidate the cached attrs for this inode if&n;&t; *&n;&t; *&t;jiffies - read_cache_jiffies &gt; attrtimeo&n;&t; *&n;&t; * and invalidate any cached data/flush out any dirty pages if&n;&t; * we find that&n;&t; *&n;&t; *&t;mtime != read_cache_mtime&n;&t; */
DECL|member|read_cache_jiffies
r_int
r_int
id|read_cache_jiffies
suffix:semicolon
DECL|member|read_cache_ctime
r_struct
id|timespec
id|read_cache_ctime
suffix:semicolon
DECL|member|read_cache_mtime
r_struct
id|timespec
id|read_cache_mtime
suffix:semicolon
DECL|member|read_cache_isize
id|__u64
id|read_cache_isize
suffix:semicolon
DECL|member|attrtimeo
r_int
r_int
id|attrtimeo
suffix:semicolon
DECL|member|attrtimeo_timestamp
r_int
r_int
id|attrtimeo_timestamp
suffix:semicolon
DECL|member|change_attr
id|__u64
id|change_attr
suffix:semicolon
multiline_comment|/* v4 only */
multiline_comment|/*&n;&t; * Timestamp that dates the change made to read_cache_mtime.&n;&t; * This is of use for dentry revalidation&n;&t; */
DECL|member|cache_mtime_jiffies
r_int
r_int
id|cache_mtime_jiffies
suffix:semicolon
DECL|member|cache_access
r_struct
id|nfs_access_cache
id|cache_access
suffix:semicolon
multiline_comment|/*&n;&t; * This is the cookie verifier used for NFSv3 readdir&n;&t; * operations&n;&t; */
DECL|member|cookieverf
id|__u32
id|cookieverf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * This is the list of dirty unwritten pages.&n;&t; */
DECL|member|dirty
r_struct
id|list_head
id|dirty
suffix:semicolon
DECL|member|commit
r_struct
id|list_head
id|commit
suffix:semicolon
DECL|member|nfs_page_tree
r_struct
id|radix_tree_root
id|nfs_page_tree
suffix:semicolon
DECL|member|ndirty
r_int
r_int
id|ndirty
comma
DECL|member|ncommit
id|ncommit
comma
DECL|member|npages
id|npages
suffix:semicolon
multiline_comment|/* Credentials for shared mmap */
DECL|member|mm_cred
r_struct
id|rpc_cred
op_star
id|mm_cred
suffix:semicolon
DECL|member|nfs_i_wait
id|wait_queue_head_t
id|nfs_i_wait
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Legal inode flag values&n; */
DECL|macro|NFS_INO_STALE
mdefine_line|#define NFS_INO_STALE&t;&t;0x0001&t;&t;/* possible stale inode */
DECL|macro|NFS_INO_ADVISE_RDPLUS
mdefine_line|#define NFS_INO_ADVISE_RDPLUS   0x0002          /* advise readdirplus */
DECL|macro|NFS_INO_REVALIDATING
mdefine_line|#define NFS_INO_REVALIDATING&t;0x0004&t;&t;/* revalidating attrs */
DECL|macro|NFS_INO_FLUSH
mdefine_line|#define NFS_INO_FLUSH&t;&t;0x0008&t;&t;/* inode is due for flushing */
DECL|function|NFS_I
r_static
r_inline
r_struct
id|nfs_inode
op_star
id|NFS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|nfs_inode
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|macro|NFS_SB
mdefine_line|#define NFS_SB(s)&t;&t;((struct nfs_server *)(s-&gt;s_fs_info))
DECL|macro|NFS_FH
mdefine_line|#define NFS_FH(inode)&t;&t;&t;(&amp;NFS_I(inode)-&gt;fh)
DECL|macro|NFS_SERVER
mdefine_line|#define NFS_SERVER(inode)&t;&t;(NFS_SB(inode-&gt;i_sb))
DECL|macro|NFS_CLIENT
mdefine_line|#define NFS_CLIENT(inode)&t;&t;(NFS_SERVER(inode)-&gt;client)
DECL|macro|NFS_PROTO
mdefine_line|#define NFS_PROTO(inode)&t;&t;(NFS_SERVER(inode)-&gt;rpc_ops)
DECL|macro|NFS_ADDR
mdefine_line|#define NFS_ADDR(inode)&t;&t;&t;(RPC_PEERADDR(NFS_CLIENT(inode)))
DECL|macro|NFS_COOKIEVERF
mdefine_line|#define NFS_COOKIEVERF(inode)&t;&t;(NFS_I(inode)-&gt;cookieverf)
DECL|macro|NFS_READTIME
mdefine_line|#define NFS_READTIME(inode)&t;&t;(NFS_I(inode)-&gt;read_cache_jiffies)
DECL|macro|NFS_MTIME_UPDATE
mdefine_line|#define NFS_MTIME_UPDATE(inode)&t;&t;(NFS_I(inode)-&gt;cache_mtime_jiffies)
DECL|macro|NFS_CACHE_CTIME
mdefine_line|#define NFS_CACHE_CTIME(inode)&t;&t;(NFS_I(inode)-&gt;read_cache_ctime)
DECL|macro|NFS_CACHE_MTIME
mdefine_line|#define NFS_CACHE_MTIME(inode)&t;&t;(NFS_I(inode)-&gt;read_cache_mtime)
DECL|macro|NFS_CACHE_ISIZE
mdefine_line|#define NFS_CACHE_ISIZE(inode)&t;&t;(NFS_I(inode)-&gt;read_cache_isize)
DECL|macro|NFS_CHANGE_ATTR
mdefine_line|#define NFS_CHANGE_ATTR(inode)&t;&t;(NFS_I(inode)-&gt;change_attr)
DECL|macro|NFS_CACHEINV
mdefine_line|#define NFS_CACHEINV(inode) &bslash;&n;do { &bslash;&n;&t;NFS_READTIME(inode) = jiffies - NFS_MAXATTRTIMEO(inode) - 1; &bslash;&n;} while (0)
DECL|macro|NFS_ATTRTIMEO
mdefine_line|#define NFS_ATTRTIMEO(inode)&t;&t;(NFS_I(inode)-&gt;attrtimeo)
DECL|macro|NFS_MINATTRTIMEO
mdefine_line|#define NFS_MINATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmin &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmin)
DECL|macro|NFS_MAXATTRTIMEO
mdefine_line|#define NFS_MAXATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmax &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmax)
DECL|macro|NFS_ATTRTIMEO_UPDATE
mdefine_line|#define NFS_ATTRTIMEO_UPDATE(inode)&t;(NFS_I(inode)-&gt;attrtimeo_timestamp)
DECL|macro|NFS_FLAGS
mdefine_line|#define NFS_FLAGS(inode)&t;&t;(NFS_I(inode)-&gt;flags)
DECL|macro|NFS_REVALIDATING
mdefine_line|#define NFS_REVALIDATING(inode)&t;&t;(NFS_FLAGS(inode) &amp; NFS_INO_REVALIDATING)
DECL|macro|NFS_STALE
mdefine_line|#define NFS_STALE(inode)&t;&t;(NFS_FLAGS(inode) &amp; NFS_INO_STALE)
DECL|macro|NFS_FILEID
mdefine_line|#define NFS_FILEID(inode)&t;&t;(NFS_I(inode)-&gt;fileid)
DECL|function|nfs_server_capable
r_static
r_inline
r_int
id|nfs_server_capable
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cap
)paren
(brace
r_return
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|caps
op_amp
id|cap
suffix:semicolon
)brace
DECL|function|NFS_USE_READDIRPLUS
r_static
r_inline
r_int
id|NFS_USE_READDIRPLUS
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|NFS_FLAGS
c_func
(paren
id|inode
)paren
op_amp
id|NFS_INO_ADVISE_RDPLUS
suffix:semicolon
)brace
r_static
r_inline
DECL|function|page_offset
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
r_static
r_inline
DECL|function|req_offset
id|loff_t
id|req_offset
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
r_return
(paren
(paren
(paren
id|loff_t
)paren
id|req-&gt;wb_index
)paren
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|req-&gt;wb_offset
suffix:semicolon
)brace
multiline_comment|/*&n; * linux/fs/nfs/inode.c&n; */
r_extern
r_void
id|nfs_zap_caches
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|nfs_fhget
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__nfs_refresh_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|kstat
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_permission
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__nfs_revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/file.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|nfs_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|nfs_file_aops
suffix:semicolon
r_static
id|__inline__
r_struct
id|rpc_cred
op_star
DECL|function|nfs_file_cred
id|nfs_file_cred
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|rpc_cred
op_star
id|cred
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|cred
op_assign
(paren
r_struct
id|rpc_cred
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
r_if
c_cond
(paren
id|cred
op_logical_and
id|cred-&gt;cr_magic
op_ne
id|RPCAUTH_CRED_MAGIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|cred
suffix:semicolon
)brace
multiline_comment|/*&n; * linux/fs/nfs/direct.c&n; */
r_extern
r_int
id|nfs_direct_IO
c_func
(paren
r_int
comma
r_struct
id|file
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
id|loff_t
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/dir.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|nfs_dir_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|nfs_dentry_operations
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/symlink.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/locks.c&n; */
r_extern
r_int
id|nfs_lock
c_func
(paren
r_struct
id|file
op_star
comma
r_int
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/unlink.c&n; */
r_extern
r_int
id|nfs_async_unlink
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_complete_unlink
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/write.c&n; */
r_extern
r_int
id|nfs_writepage
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
id|nfs_writepages
c_func
(paren
r_struct
id|address_space
op_star
comma
r_struct
id|writeback_control
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_incompatible
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
suffix:semicolon
r_extern
r_int
id|nfs_updatepage
c_func
(paren
r_struct
id|file
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
id|nfs_writeback_done
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|nfs_writedata_release
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_NFS_V3) || defined(CONFIG_NFS_V4)
r_extern
r_void
id|nfs_commit_release
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|nfs_commit_done
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Try to write back everything synchronously (but check the&n; * return value!)&n; */
r_extern
r_int
id|nfs_sync_file
c_func
(paren
r_struct
id|inode
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_file
c_func
(paren
r_struct
id|inode
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_list
c_func
(paren
r_struct
id|list_head
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_NFS_V3) || defined(CONFIG_NFS_V4)
r_extern
r_int
id|nfs_commit_file
c_func
(paren
r_struct
id|inode
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_commit_list
c_func
(paren
r_struct
id|list_head
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#else
r_static
r_inline
r_int
DECL|function|nfs_commit_file
id|nfs_commit_file
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_static
r_inline
r_int
DECL|function|nfs_have_writebacks
id|nfs_have_writebacks
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|NFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|npages
op_ne
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfs_wb_all
id|nfs_wb_all
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|FLUSH_WAIT
)paren
suffix:semicolon
r_return
(paren
id|error
OL
l_int|0
)paren
ques
c_cond
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back all requests on one page - we do this before reading it.&n; */
r_static
r_inline
r_int
DECL|function|nfs_wb_page
id|nfs_wb_page
c_func
(paren
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
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
l_int|0
comma
id|page-&gt;index
comma
l_int|1
comma
id|FLUSH_WAIT
op_or
id|FLUSH_STABLE
)paren
suffix:semicolon
r_return
(paren
id|error
OL
l_int|0
)paren
ques
c_cond
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back all pending writes for one user.. &n; */
r_static
r_inline
r_int
DECL|function|nfs_wb_file
id|nfs_wb_file
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
id|file
comma
l_int|0
comma
l_int|0
comma
id|FLUSH_WAIT
)paren
suffix:semicolon
r_return
(paren
id|error
OL
l_int|0
)paren
ques
c_cond
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
multiline_comment|/*&n; * linux/fs/nfs/read.c&n; */
r_extern
r_int
id|nfs_readpage
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
id|nfs_readpages
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|address_space
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
id|nfs_pagein_list
c_func
(paren
r_struct
id|list_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|nfs_readpage_result
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_readdata_release
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/mount_clnt.c&n; * (Used only by nfsroot module)&n; */
r_extern
r_int
id|nfsroot_mount
c_func
(paren
r_struct
id|sockaddr_in
op_star
comma
r_char
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * inline functions&n; */
r_static
r_inline
r_int
DECL|function|nfs_revalidate_inode
id|nfs_revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|NFS_READTIME
c_func
(paren
id|inode
)paren
op_plus
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
id|NFS_STALE
c_func
(paren
id|inode
)paren
ques
c_cond
op_minus
id|ESTALE
suffix:colon
l_int|0
suffix:semicolon
r_return
id|__nfs_revalidate_inode
c_func
(paren
id|server
comma
id|inode
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfs_refresh_inode
id|nfs_refresh_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_if
c_cond
(paren
(paren
id|fattr-&gt;valid
op_amp
id|NFS_ATTR_FATTR
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__nfs_refresh_inode
c_func
(paren
id|inode
comma
id|fattr
)paren
suffix:semicolon
)brace
r_static
r_inline
id|loff_t
DECL|function|nfs_size_to_loff_t
id|nfs_size_to_loff_t
c_func
(paren
id|__u64
id|size
)paren
(brace
id|loff_t
id|maxsz
op_assign
(paren
(paren
(paren
id|loff_t
)paren
id|ULONG_MAX
)paren
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|maxsz
)paren
r_return
id|maxsz
suffix:semicolon
r_return
(paren
id|loff_t
)paren
id|size
suffix:semicolon
)brace
r_static
r_inline
id|ino_t
DECL|function|nfs_fileid_to_ino_t
id|nfs_fileid_to_ino_t
c_func
(paren
id|u64
id|fileid
)paren
(brace
id|ino_t
id|ino
op_assign
(paren
id|ino_t
)paren
id|fileid
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|ino_t
)paren
OL
r_sizeof
(paren
id|u64
)paren
)paren
id|ino
op_xor_assign
id|fileid
op_rshift
(paren
r_sizeof
(paren
id|u64
)paren
op_minus
r_sizeof
(paren
id|ino_t
)paren
)paren
op_star
l_int|8
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
multiline_comment|/* NFS root */
r_extern
r_void
op_star
id|nfs_root_data
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|nfs_wait_event
mdefine_line|#define nfs_wait_event(clnt, wq, condition)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (clnt-&gt;cl_intr) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sigset_t oldmask;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;rpc_clnt_sigmask(clnt, &amp;oldmask);&t;&t;&t;&bslash;&n;&t;&t;__retval = wait_event_interruptible(wq, condition);&t;&bslash;&n;&t;&t;rpc_clnt_sigunmask(clnt, &amp;oldmask);&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait_event(wq, condition);&t;&t;&t;&t;&bslash;&n;&t;__retval;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|NFS_JUKEBOX_RETRY_TIME
mdefine_line|#define NFS_JUKEBOX_RETRY_TIME (5 * HZ)
macro_line|#ifdef CONFIG_NFS_V4
DECL|struct|nfs4_client
r_struct
id|nfs4_client
(brace
DECL|member|cl_count
id|atomic_t
id|cl_count
suffix:semicolon
multiline_comment|/* refcount */
DECL|member|cl_clientid
id|u64
id|cl_clientid
suffix:semicolon
multiline_comment|/* constant */
DECL|member|cl_confirm
id|nfs4_verifier
id|cl_confirm
suffix:semicolon
multiline_comment|/*&n;         * Starts a list of lockowners, linked through lo_list.&n;&t; */
DECL|member|cl_lockowners
r_struct
id|list_head
id|cl_lockowners
suffix:semicolon
multiline_comment|/* protected by state_spinlock */
)brace
suffix:semicolon
multiline_comment|/* nfs4proc.c */
r_extern
r_int
id|nfs4_proc_renew
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* nfs4renewd.c */
r_extern
r_int
id|nfs4_init_renewd
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NFS_V4 */
macro_line|#ifdef CONFIG_NFS_V4
r_extern
r_struct
id|nfs4_client
op_star
id|nfs4_get_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nfs4_put_client
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
suffix:semicolon
r_struct
id|nfs4_mount_data
suffix:semicolon
r_static
r_inline
r_int
DECL|function|create_nfsv4_state
id|create_nfsv4_state
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs4_mount_data
op_star
id|data
)paren
(brace
id|server-&gt;nfs4_state
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|destroy_nfsv4_state
id|destroy_nfsv4_state
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
)paren
(brace
r_if
c_cond
(paren
id|server-&gt;mnt_path
)paren
(brace
id|kfree
c_func
(paren
id|server-&gt;mnt_path
)paren
suffix:semicolon
id|server-&gt;mnt_path
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|server-&gt;nfs4_state
)paren
(brace
id|nfs4_put_client
c_func
(paren
id|server-&gt;nfs4_state
)paren
suffix:semicolon
id|server-&gt;nfs4_state
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|macro|create_nfsv4_state
mdefine_line|#define create_nfsv4_state(server, data)  0
DECL|macro|destroy_nfsv4_state
mdefine_line|#define destroy_nfsv4_state(server)       do { } while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * NFS debug flags&n; */
DECL|macro|NFSDBG_VFS
mdefine_line|#define NFSDBG_VFS&t;&t;0x0001
DECL|macro|NFSDBG_DIRCACHE
mdefine_line|#define NFSDBG_DIRCACHE&t;&t;0x0002
DECL|macro|NFSDBG_LOOKUPCACHE
mdefine_line|#define NFSDBG_LOOKUPCACHE&t;0x0004
DECL|macro|NFSDBG_PAGECACHE
mdefine_line|#define NFSDBG_PAGECACHE&t;0x0008
DECL|macro|NFSDBG_PROC
mdefine_line|#define NFSDBG_PROC&t;&t;0x0010
DECL|macro|NFSDBG_XDR
mdefine_line|#define NFSDBG_XDR&t;&t;0x0020
DECL|macro|NFSDBG_FILE
mdefine_line|#define NFSDBG_FILE&t;&t;0x0040
DECL|macro|NFSDBG_ROOT
mdefine_line|#define NFSDBG_ROOT&t;&t;0x0080
DECL|macro|NFSDBG_ALL
mdefine_line|#define NFSDBG_ALL&t;&t;0xFFFF
macro_line|#ifdef __KERNEL__
DECL|macro|ifdebug
macro_line|# undef ifdebug
macro_line|# ifdef NFS_DEBUG
DECL|macro|ifdebug
macro_line|#  define ifdebug(fac)&t;&t;if (nfs_debug &amp; NFSDBG_##fac)
macro_line|# else
DECL|macro|ifdebug
macro_line|#  define ifdebug(fac)&t;&t;if (0)
macro_line|# endif
macro_line|#endif /* __KERNEL */
macro_line|#endif
eof
