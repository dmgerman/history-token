multiline_comment|/*&n; * linux/fs/nfs/direct.c&n; *&n; * Copyright (C) 2003 by Chuck Lever &lt;cel@netapp.com&gt;&n; *&n; * High-performance uncached I/O for the Linux NFS client&n; *&n; * There are important applications whose performance or correctness&n; * depends on uncached access to file data.  Database clusters&n; * (multiple copies of the same instance running on separate hosts) &n; * implement their own cache coherency protocol that subsumes file&n; * system cache protocols.  Applications that process datasets &n; * considerably larger than the client&squot;s memory do not always benefit &n; * from a local cache.  A streaming video server, for instance, has no &n; * need to cache the contents of a file.&n; *&n; * When an application requests uncached I/O, all read and write requests&n; * are made directly to the server; data stored or fetched via these&n; * requests is not cached in the Linux page cache.  The client does not&n; * correct unaligned requests from applications.  All requested bytes are&n; * held on permanent storage before a direct write system call returns to&n; * an application.&n; *&n; * Solaris implements an uncached I/O facility called directio() that&n; * is used for backups and sequential I/O to very large files.  Solaris&n; * also supports uncaching whole NFS partitions with &quot;-o forcedirectio,&quot;&n; * an undocumented mount option.&n; *&n; * Designed by Jeff Kimmel, Chuck Lever, and Trond Myklebust, with&n; * help from Andrew Morton.&n; *&n; * 18 Dec 2001&t;Initial implementation for 2.4  --cel&n; * 08 Jul 2002&t;Version for 2.4.19, with bug fixes --trondmy&n; * 08 Jun 2003&t;Port to 2.5 APIs  --cel&n; * 31 Mar 2004&t;Handle direct I/O without VFS support  --cel&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_VFS
DECL|macro|MAX_DIRECTIO_SIZE
mdefine_line|#define MAX_DIRECTIO_SIZE&t;(4096UL &lt;&lt; PAGE_SHIFT)
multiline_comment|/**&n; * nfs_get_user_pages - find and set up pages underlying user&squot;s buffer&n; * rw: direction (read or write)&n; * user_addr: starting address of this segment of user&squot;s buffer&n; * count: size of this segment&n; * @pages: returned array of page struct pointers underlying user&squot;s buffer&n; */
r_static
r_inline
r_int
DECL|function|nfs_get_user_pages
id|nfs_get_user_pages
c_func
(paren
r_int
id|rw
comma
r_int
r_int
id|user_addr
comma
r_int
id|size
comma
r_struct
id|page
op_star
op_star
op_star
id|pages
)paren
(brace
r_int
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_int
r_int
id|page_count
suffix:semicolon
r_int
id|array_size
suffix:semicolon
multiline_comment|/* set an arbitrary limit to prevent arithmetic overflow */
r_if
c_cond
(paren
id|size
OG
id|MAX_DIRECTIO_SIZE
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
id|page_count
op_assign
(paren
id|user_addr
op_plus
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|page_count
op_sub_assign
id|user_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|array_size
op_assign
(paren
id|page_count
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
op_star
id|pages
op_assign
id|kmalloc
c_func
(paren
id|array_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pages
)paren
(brace
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|result
op_assign
id|get_user_pages
c_func
(paren
id|current
comma
id|current-&gt;mm
comma
id|user_addr
comma
id|page_count
comma
(paren
id|rw
op_eq
id|READ
)paren
comma
l_int|0
comma
op_star
id|pages
comma
l_int|NULL
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_free_user_pages - tear down page struct array&n; * @pages: array of page struct pointers underlying target buffer&n; */
r_static
r_void
DECL|function|nfs_free_user_pages
id|nfs_free_user_pages
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|npages
comma
r_int
id|do_dirty
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|npages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|do_dirty
)paren
id|set_page_dirty_lock
c_func
(paren
id|pages
(braket
id|i
)braket
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|pages
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_read_seg - Read in one iov segment.  Generate separate&n; *                        read RPCs for each &quot;rsize&quot; bytes.&n; * @inode: target inode&n; * @ctx: target file open context&n; * user_addr: starting address of this segment of user&squot;s buffer&n; * count: size of this segment&n; * file_offset: offset in file to begin the operation&n; * @pages: array of addresses of page structs defining user&squot;s buffer&n; * nr_pages: size of pages array&n; */
r_static
r_int
DECL|function|nfs_direct_read_seg
id|nfs_direct_read_seg
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_open_context
op_star
id|ctx
comma
r_int
r_int
id|user_addr
comma
r_int
id|count
comma
id|loff_t
id|file_offset
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|nr_pages
)paren
(brace
r_const
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
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
r_int
id|curpage
op_assign
l_int|0
suffix:semicolon
r_struct
id|nfs_read_data
id|rdata
op_assign
(brace
dot
id|inode
op_assign
id|inode
comma
dot
id|cred
op_assign
id|ctx-&gt;cred
comma
dot
id|args
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|context
op_assign
id|ctx
comma
)brace
comma
dot
id|res
op_assign
(brace
dot
id|fattr
op_assign
op_amp
id|rdata.fattr
comma
)brace
comma
)brace
suffix:semicolon
id|rdata.args.pgbase
op_assign
id|user_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|rdata.args.offset
op_assign
id|file_offset
suffix:semicolon
r_do
(brace
r_int
id|result
suffix:semicolon
id|rdata.args.count
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|rdata.args.count
OG
id|rsize
)paren
id|rdata.args.count
op_assign
id|rsize
suffix:semicolon
id|rdata.args.pages
op_assign
op_amp
id|pages
(braket
id|curpage
)braket
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: direct read: c=%u o=%Ld ua=%lu, pb=%u, cp=%u&bslash;n&quot;
comma
id|rdata.args.count
comma
(paren
r_int
r_int
)paren
id|rdata.args.offset
comma
id|user_addr
op_plus
id|tot_bytes
comma
id|rdata.args.pgbase
comma
id|curpage
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
op_amp
id|rdata
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
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
r_return
id|result
suffix:semicolon
)brace
id|tot_bytes
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|rdata.res.eof
)paren
r_break
suffix:semicolon
id|rdata.args.offset
op_add_assign
id|result
suffix:semicolon
id|rdata.args.pgbase
op_add_assign
id|result
suffix:semicolon
id|curpage
op_add_assign
id|rdata.args.pgbase
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|rdata.args.pgbase
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
id|count
op_sub_assign
id|result
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* XXX: should we zero the rest of the user&squot;s buffer if we&n;&t; *      hit eof? */
r_return
id|tot_bytes
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_read - For each iov segment, map the user&squot;s buffer&n; *                   then generate read RPCs.&n; * @inode: target inode&n; * @ctx: target file open context&n; * @iov: array of vectors that define I/O buffer&n; * file_offset: offset in file to begin the operation&n; * nr_segs: size of iovec array&n; *&n; * generic_file_direct_IO has already pushed out any non-direct&n; * writes so that this read will see them when we read from the&n; * server.&n; */
r_static
id|ssize_t
DECL|function|nfs_direct_read
id|nfs_direct_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_open_context
op_star
id|ctx
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|file_offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
id|ssize_t
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|seg
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|seg
OL
id|nr_segs
)paren
op_logical_and
(paren
id|tot_bytes
op_ge
l_int|0
)paren
)paren
(brace
id|ssize_t
id|result
suffix:semicolon
r_int
id|page_count
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_const
r_struct
id|iovec
op_star
id|vec
op_assign
op_amp
id|iov
(braket
id|seg
op_increment
)braket
suffix:semicolon
r_int
r_int
id|user_addr
op_assign
(paren
r_int
r_int
)paren
id|vec-&gt;iov_base
suffix:semicolon
r_int
id|size
op_assign
id|vec-&gt;iov_len
suffix:semicolon
id|page_count
op_assign
id|nfs_get_user_pages
c_func
(paren
id|READ
comma
id|user_addr
comma
id|size
comma
op_amp
id|pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_count
OL
l_int|0
)paren
(brace
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|page_count
suffix:semicolon
)brace
id|result
op_assign
id|nfs_direct_read_seg
c_func
(paren
id|inode
comma
id|ctx
comma
id|user_addr
comma
id|size
comma
id|file_offset
comma
id|pages
comma
id|page_count
)paren
suffix:semicolon
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
id|page_count
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|tot_bytes
op_add_assign
id|result
suffix:semicolon
id|file_offset
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|size
)paren
r_break
suffix:semicolon
)brace
r_return
id|tot_bytes
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_write_seg - Write out one iov segment.  Generate separate&n; *                        write RPCs for each &quot;wsize&quot; bytes, then commit.&n; * @inode: target inode&n; * @ctx: target file open context&n; * user_addr: starting address of this segment of user&squot;s buffer&n; * count: size of this segment&n; * file_offset: offset in file to begin the operation&n; * @pages: array of addresses of page structs defining user&squot;s buffer&n; * nr_pages: size of pages array&n; */
r_static
r_int
DECL|function|nfs_direct_write_seg
id|nfs_direct_write_seg
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_open_context
op_star
id|ctx
comma
r_int
r_int
id|user_addr
comma
r_int
id|count
comma
id|loff_t
id|file_offset
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|nr_pages
)paren
(brace
r_const
r_int
r_int
id|wsize
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|wsize
suffix:semicolon
r_int
id|request
suffix:semicolon
r_int
id|curpage
comma
id|need_commit
comma
id|result
comma
id|tot_bytes
suffix:semicolon
r_struct
id|nfs_writeverf
id|first_verf
suffix:semicolon
r_struct
id|nfs_write_data
id|wdata
op_assign
(brace
dot
id|inode
op_assign
id|inode
comma
dot
id|cred
op_assign
id|ctx-&gt;cred
comma
dot
id|args
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|context
op_assign
id|ctx
comma
)brace
comma
dot
id|res
op_assign
(brace
dot
id|fattr
op_assign
op_amp
id|wdata.fattr
comma
dot
id|verf
op_assign
op_amp
id|wdata.verf
comma
)brace
comma
)brace
suffix:semicolon
id|wdata.args.stable
op_assign
id|NFS_UNSTABLE
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_or
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|version
op_eq
l_int|2
op_logical_or
id|count
op_le
id|wsize
)paren
id|wdata.args.stable
op_assign
id|NFS_FILE_SYNC
suffix:semicolon
id|nfs_begin_data_update
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retry
suffix:colon
id|need_commit
op_assign
l_int|0
suffix:semicolon
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
id|curpage
op_assign
l_int|0
suffix:semicolon
id|request
op_assign
id|count
suffix:semicolon
id|wdata.args.pgbase
op_assign
id|user_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|wdata.args.offset
op_assign
id|file_offset
suffix:semicolon
r_do
(brace
id|wdata.args.count
op_assign
id|request
suffix:semicolon
r_if
c_cond
(paren
id|wdata.args.count
OG
id|wsize
)paren
id|wdata.args.count
op_assign
id|wsize
suffix:semicolon
id|wdata.args.pages
op_assign
op_amp
id|pages
(braket
id|curpage
)braket
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: direct write: c=%u o=%Ld ua=%lu, pb=%u, cp=%u&bslash;n&quot;
comma
id|wdata.args.count
comma
(paren
r_int
r_int
)paren
id|wdata.args.offset
comma
id|user_addr
op_plus
id|tot_bytes
comma
id|wdata.args.pgbase
comma
id|curpage
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
id|write
c_func
(paren
op_amp
id|wdata
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tot_bytes
op_eq
l_int|0
)paren
id|memcpy
c_func
(paren
op_amp
id|first_verf.verifier
comma
op_amp
id|wdata.verf.verifier
comma
r_sizeof
(paren
id|first_verf.verifier
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wdata.verf.committed
op_ne
id|NFS_FILE_SYNC
)paren
(brace
id|need_commit
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|first_verf.verifier
comma
op_amp
id|wdata.verf.verifier
comma
r_sizeof
(paren
id|first_verf.verifier
)paren
)paren
)paren
suffix:semicolon
r_goto
id|sync_retry
suffix:semicolon
)brace
id|tot_bytes
op_add_assign
id|result
suffix:semicolon
multiline_comment|/* in case of a short write: stop now, let the app recover */
r_if
c_cond
(paren
id|result
OL
id|wdata.args.count
)paren
r_break
suffix:semicolon
id|wdata.args.offset
op_add_assign
id|result
suffix:semicolon
id|wdata.args.pgbase
op_add_assign
id|result
suffix:semicolon
id|curpage
op_add_assign
id|wdata.args.pgbase
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|wdata.args.pgbase
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
id|request
op_sub_assign
id|result
suffix:semicolon
)brace
r_while
c_loop
(paren
id|request
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Commit data written so far, even in the event of an error&n;&t; */
r_if
c_cond
(paren
id|need_commit
)paren
(brace
id|wdata.args.count
op_assign
id|tot_bytes
suffix:semicolon
id|wdata.args.offset
op_assign
id|file_offset
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
id|commit
c_func
(paren
op_amp
id|wdata
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
op_logical_or
id|memcmp
c_func
(paren
op_amp
id|first_verf.verifier
comma
op_amp
id|wdata.verf.verifier
comma
r_sizeof
(paren
id|first_verf.verifier
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|sync_retry
suffix:semicolon
)brace
id|result
op_assign
id|tot_bytes
suffix:semicolon
id|out
suffix:colon
id|nfs_end_data_update_defer
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
id|sync_retry
suffix:colon
id|wdata.args.stable
op_assign
id|NFS_FILE_SYNC
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_write - For each iov segment, map the user&squot;s buffer&n; *                    then generate write and commit RPCs.&n; * @inode: target inode&n; * @ctx: target file open context&n; * @iov: array of vectors that define I/O buffer&n; * file_offset: offset in file to begin the operation&n; * nr_segs: size of iovec array&n; *&n; * Upon return, generic_file_direct_IO invalidates any cached pages&n; * that non-direct readers might access, so they will pick up these&n; * writes immediately.&n; */
DECL|function|nfs_direct_write
r_static
r_int
id|nfs_direct_write
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_open_context
op_star
id|ctx
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|file_offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
id|ssize_t
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|seg
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|seg
OL
id|nr_segs
)paren
op_logical_and
(paren
id|tot_bytes
op_ge
l_int|0
)paren
)paren
(brace
id|ssize_t
id|result
suffix:semicolon
r_int
id|page_count
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_const
r_struct
id|iovec
op_star
id|vec
op_assign
op_amp
id|iov
(braket
id|seg
op_increment
)braket
suffix:semicolon
r_int
r_int
id|user_addr
op_assign
(paren
r_int
r_int
)paren
id|vec-&gt;iov_base
suffix:semicolon
r_int
id|size
op_assign
id|vec-&gt;iov_len
suffix:semicolon
id|page_count
op_assign
id|nfs_get_user_pages
c_func
(paren
id|WRITE
comma
id|user_addr
comma
id|size
comma
op_amp
id|pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_count
OL
l_int|0
)paren
(brace
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|page_count
suffix:semicolon
)brace
id|result
op_assign
id|nfs_direct_write_seg
c_func
(paren
id|inode
comma
id|ctx
comma
id|user_addr
comma
id|size
comma
id|file_offset
comma
id|pages
comma
id|page_count
)paren
suffix:semicolon
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
id|page_count
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tot_bytes
OG
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|tot_bytes
op_add_assign
id|result
suffix:semicolon
id|file_offset
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|size
)paren
r_break
suffix:semicolon
)brace
r_return
id|tot_bytes
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_IO - NFS address space operation for direct I/O&n; * rw: direction (read or write)&n; * @iocb: target I/O control block&n; * @iov: array of vectors that define I/O buffer&n; * file_offset: offset in file to begin the operation&n; * nr_segs: size of iovec array&n; *&n; */
id|ssize_t
DECL|function|nfs_direct_IO
id|nfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|kiocb
op_star
id|iocb
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|file_offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
id|ssize_t
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|nfs_open_context
op_star
id|ctx
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/*&n;&t; * No support for async yet&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_sync_kiocb
c_func
(paren
id|iocb
)paren
)paren
r_return
id|result
suffix:semicolon
id|ctx
op_assign
(paren
r_struct
id|nfs_open_context
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_switch
c_cond
(paren
id|rw
)paren
(brace
r_case
id|READ
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFS: direct_IO(read) (%s) off/no(%Lu/%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
comma
id|file_offset
comma
id|nr_segs
)paren
suffix:semicolon
id|result
op_assign
id|nfs_direct_read
c_func
(paren
id|inode
comma
id|ctx
comma
id|iov
comma
id|file_offset
comma
id|nr_segs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFS: direct_IO(write) (%s) off/no(%Lu/%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
comma
id|file_offset
comma
id|nr_segs
)paren
suffix:semicolon
id|result
op_assign
id|nfs_direct_write
c_func
(paren
id|inode
comma
id|ctx
comma
id|iov
comma
id|file_offset
comma
id|nr_segs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_file_direct_read - file direct read operation for NFS files&n; * @iocb: target I/O control block&n; * @buf: user&squot;s buffer into which to read data&n; * count: number of bytes to read&n; * pos: byte offset in file where reading starts&n; *&n; * We use this function for direct reads instead of calling&n; * generic_file_aio_read() in order to avoid gfar&squot;s check to see if&n; * the request starts before the end of the file.  For that check&n; * to work, we must generate a GETATTR before each direct read, and&n; * even then there is a window between the GETATTR and the subsequent&n; * READ where the file size could change.  So our preference is simply&n; * to do all reads the application wants, and the server will take&n; * care of managing the end of file boundary.&n; * &n; * This function also eliminates unnecessarily updating the file&squot;s&n; * atime locally, as the NFS server sets the file&squot;s atime, and this&n; * client must read the updated atime from the server back into its&n; * cache.&n; */
id|ssize_t
DECL|function|nfs_file_direct_read
id|nfs_file_direct_read
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
id|ssize_t
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|loff_t
op_star
id|ppos
op_assign
op_amp
id|iocb-&gt;ki_pos
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|nfs_open_context
op_star
id|ctx
op_assign
(paren
r_struct
id|nfs_open_context
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|file-&gt;f_mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|mapping-&gt;host
suffix:semicolon
r_struct
id|iovec
id|iov
op_assign
(brace
dot
id|iov_base
op_assign
id|buf
comma
dot
id|iov_len
op_assign
id|count
comma
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfs: direct read(%s/%s, %lu@%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_sync_kiocb
c_func
(paren
id|iocb
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|iov.iov_base
comma
id|iov.iov_len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;nrpages
)paren
(brace
id|retval
op_assign
id|filemap_fdatawrite
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
id|nfs_direct_read
c_func
(paren
id|inode
comma
id|ctx
comma
op_amp
id|iov
comma
id|pos
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
op_star
id|ppos
op_assign
id|pos
op_plus
id|retval
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_file_direct_write - file direct write operation for NFS files&n; * @iocb: target I/O control block&n; * @buf: user&squot;s buffer from which to write data&n; * count: number of bytes to write&n; * pos: byte offset in file where writing starts&n; *&n; * We use this function for direct writes instead of calling&n; * generic_file_aio_write() in order to avoid taking the inode&n; * semaphore and updating the i_size.  The NFS server will set&n; * the new i_size and this client must read the updated size&n; * back into its cache.  We let the server do generic write&n; * parameter checking and report problems.&n; *&n; * We also avoid an unnecessary invocation of generic_osync_inode(),&n; * as it is fairly meaningless to sync the metadata of an NFS file.&n; *&n; * We eliminate local atime updates, see direct read above.&n; *&n; * We avoid unnecessary page cache invalidations for normal cached&n; * readers of this file.&n; *&n; * Note that O_APPEND is not supported for NFS direct writes, as there&n; * is no atomic O_APPEND write facility in the NFS protocol.&n; */
id|ssize_t
DECL|function|nfs_file_direct_write
id|nfs_file_direct_write
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
id|ssize_t
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|loff_t
op_star
id|ppos
op_assign
op_amp
id|iocb-&gt;ki_pos
suffix:semicolon
r_int
r_int
id|limit
op_assign
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|nfs_open_context
op_star
id|ctx
op_assign
(paren
r_struct
id|nfs_open_context
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|file-&gt;f_mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|mapping-&gt;host
suffix:semicolon
r_struct
id|iovec
id|iov
op_assign
(brace
dot
id|iov_base
op_assign
(paren
r_char
id|__user
op_star
)paren
id|buf
comma
dot
id|iov_len
op_assign
id|count
comma
)brace
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: direct write(%s/%s(%ld), %lu@%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_sync_kiocb
c_func
(paren
id|iocb
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|iov.iov_base
comma
id|iov.iov_len
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_error
)paren
(brace
id|retval
op_assign
id|file-&gt;f_error
suffix:semicolon
id|file-&gt;f_error
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EFBIG
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_ne
id|RLIM_INFINITY
)paren
(brace
r_if
c_cond
(paren
id|pos
op_ge
id|limit
)paren
(brace
id|send_sig
c_func
(paren
id|SIGXFSZ
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|limit
op_minus
(paren
r_int
r_int
)paren
id|pos
)paren
id|count
op_assign
id|limit
op_minus
(paren
r_int
r_int
)paren
id|pos
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;nrpages
)paren
(brace
id|retval
op_assign
id|filemap_fdatawrite
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
id|nfs_direct_write
c_func
(paren
id|inode
comma
id|ctx
comma
op_amp
id|iov
comma
id|pos
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;nrpages
)paren
id|invalidate_inode_pages2
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
op_star
id|ppos
op_assign
id|pos
op_plus
id|retval
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof
