multiline_comment|/*&n; * linux/fs/nfs/direct.c&n; *&n; * Copyright (C) 2001 by Chuck Lever &lt;cel@netapp.com&gt;&n; *&n; * High-performance uncached I/O for the Linux NFS client&n; *&n; * There are important applications whose performance or correctness&n; * depends on uncached access to file data.  Database clusters&n; * (multiple copies of the same instance running on separate hosts) &n; * implement their own cache coherency protocol that subsumes file&n; * system cache protocols.  Applications that process datasets &n; * considerably larger than the client&squot;s memory do not always benefit &n; * from a local cache.  A streaming video server, for instance, has no &n; * need to cache the contents of a file.&n; *&n; * When an application requests uncached I/O, all read and write requests&n; * are made directly to the server; data stored or fetched via these&n; * requests is not cached in the Linux page cache.  The client does not&n; * correct unaligned requests from applications.  All requested bytes are&n; * held on permanent storage before a direct write system call returns to&n; * an application.&n; *&n; * Solaris implements an uncached I/O facility called directio() that&n; * is used for backups and sequential I/O to very large files.  Solaris&n; * also supports uncaching whole NFS partitions with &quot;-o forcedirectio,&quot;&n; * an undocumented mount option.&n; *&n; * Designed by Jeff Kimmel, Chuck Lever, and Trond Myklebust.&n; *&n; * 18 Dec 2001&t;Initial implementation for 2.4  --cel&n; * 08 Jul 2002&t;Version for 2.4.19, with bug fixes --trondmy&n; * 24 Sep 2002&t;Rewrite to use asynchronous RPCs, port to 2.5  --cel&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;(NFSDBG_PAGECACHE | NFSDBG_VFS)
DECL|macro|VERF_SIZE
mdefine_line|#define VERF_SIZE&t;&t;(2 * sizeof(__u32))
multiline_comment|/**&n; * nfs_get_user_pages - find and set up page representing user buffer&n; * addr: user-space address of target buffer&n; * size: total size in bytes of target buffer&n; * @pages: returned array of page struct pointers underlying target buffer&n; * write: whether or not buffer is target of a write operation&n; */
r_static
r_inline
r_int
DECL|function|nfs_get_user_pages
id|nfs_get_user_pages
c_func
(paren
r_int
r_int
id|addr
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
comma
r_int
id|rw
)paren
(brace
r_int
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_int
id|page_count
op_assign
(paren
r_int
)paren
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
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
op_plus
l_int|2U
suffix:semicolon
op_star
id|pages
op_assign
(paren
r_struct
id|page
op_star
op_star
)paren
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
id|addr
comma
id|page_count
comma
(paren
id|rw
op_eq
id|WRITE
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
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: get_user_pages result %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_free_user_pages - tear down page struct array&n; * @pages: array of page struct pointers underlying target buffer&n; */
r_static
r_inline
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
id|count
)paren
(brace
r_int
id|page
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|page_cache_release
c_func
(paren
id|pages
(braket
id|page
op_increment
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pages
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_iov2pagelist - convert an array of iovecs to a list of page requests&n; * @inode: inode of target file&n; * @cred: credentials of user who requested I/O&n; * @iov: array of vectors that define I/O buffer&n; * offset: where in file to begin the read&n; * nr_segs: size of iovec array&n; * @requests: append new page requests to this list head&n; */
r_static
r_int
DECL|function|nfs_iov2pagelist
id|nfs_iov2pagelist
c_func
(paren
r_int
id|rw
comma
r_const
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|rpc_cred
op_star
id|cred
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
comma
r_struct
id|list_head
op_star
id|requests
)paren
(brace
r_int
id|seg
suffix:semicolon
r_int
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
multiline_comment|/* for each iovec in the array... */
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
id|nr_segs
suffix:semicolon
id|seg
op_increment
)paren
(brace
r_const
r_int
r_int
id|user_addr
op_assign
(paren
r_int
r_int
)paren
id|iov
(braket
id|seg
)braket
dot
id|iov_base
suffix:semicolon
r_int
id|bytes
op_assign
id|iov
(braket
id|seg
)braket
dot
id|iov_len
suffix:semicolon
r_int
r_int
id|pg_offset
op_assign
(paren
id|user_addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
r_int
id|page_count
comma
id|page
op_assign
l_int|0
suffix:semicolon
id|page_count
op_assign
id|nfs_get_user_pages
c_func
(paren
id|user_addr
comma
id|bytes
comma
op_amp
id|pages
comma
id|rw
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
id|nfs_release_list
c_func
(paren
id|requests
)paren
suffix:semicolon
r_return
id|page_count
suffix:semicolon
)brace
multiline_comment|/* ...build as many page requests as required */
r_while
c_loop
(paren
id|bytes
OG
l_int|0
)paren
(brace
r_struct
id|nfs_page
op_star
r_new
suffix:semicolon
r_const
r_int
r_int
id|pg_bytes
op_assign
(paren
id|bytes
OG
id|PAGE_SIZE
)paren
ques
c_cond
id|PAGE_SIZE
suffix:colon
id|bytes
suffix:semicolon
r_new
op_assign
id|nfs_create_request
c_func
(paren
(paren
r_struct
id|rpc_cred
op_star
)paren
id|cred
comma
(paren
r_struct
id|inode
op_star
)paren
id|inode
comma
id|pages
(braket
id|page
)braket
comma
id|pg_offset
comma
id|pg_bytes
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
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
id|page_count
)paren
suffix:semicolon
id|nfs_release_list
c_func
(paren
id|requests
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
r_new
op_member_access_from_pointer
id|wb_index
op_assign
id|offset
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
r_new
comma
id|requests
)paren
suffix:semicolon
multiline_comment|/* after the first page */
id|pg_offset
op_assign
l_int|0
suffix:semicolon
id|offset
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|tot_bytes
op_add_assign
id|pg_bytes
suffix:semicolon
id|bytes
op_sub_assign
id|pg_bytes
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
multiline_comment|/* don&squot;t release pages here -- I/O completion will do that */
id|nfs_free_user_pages
c_func
(paren
id|pages
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|tot_bytes
suffix:semicolon
)brace
multiline_comment|/**&n; * do_nfs_direct_IO - Read or write data without caching&n; * @inode: inode of target file&n; * @cred: credentials of user who requested I/O&n; * @iov: array of vectors that define I/O buffer&n; * offset: where in file to begin the read&n; * nr_segs: size of iovec array&n; *&n; * Break the passed-in iovec into a series of page-sized or smaller&n; * requests, where each page is mapped for direct user-land I/O.&n; *&n; * For each of these pages, create an NFS page request and&n; * append it to an automatic list of page requests.&n; *&n; * When all page requests have been queued, start the I/O on the&n; * whole list.  The underlying routines coalesce the pages on the&n; * list into a bunch of asynchronous &quot;r/wsize&quot; network requests.&n; *&n; * I/O completion automatically unmaps and releases the pages.&n; */
r_static
r_int
DECL|function|do_nfs_direct_IO
id|do_nfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_const
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|rpc_cred
op_star
id|cred
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|requests
)paren
suffix:semicolon
r_int
id|result
comma
id|tot_bytes
suffix:semicolon
id|result
op_assign
id|nfs_iov2pagelist
c_func
(paren
id|rw
comma
id|inode
comma
id|cred
comma
id|iov
comma
id|offset
comma
id|nr_segs
comma
op_amp
id|requests
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|tot_bytes
op_assign
id|result
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
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
OL
id|PAGE_SIZE
)paren
)paren
(brace
id|result
op_assign
id|nfs_direct_read_sync
c_func
(paren
id|inode
comma
id|cred
comma
id|iov
comma
id|offset
comma
id|nr_segs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
id|nfs_pagein_list
c_func
(paren
op_amp
id|requests
comma
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rpages
)paren
suffix:semicolon
id|nfs_wait_for_reads
c_func
(paren
op_amp
id|requests
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|wsize
OL
id|PAGE_SIZE
)paren
)paren
id|result
op_assign
id|nfs_direct_write_sync
c_func
(paren
id|inode
comma
id|cred
comma
id|iov
comma
id|offset
comma
id|nr_segs
)paren
suffix:semicolon
r_else
id|result
op_assign
id|nfs_flush_list
c_func
(paren
op_amp
id|requests
comma
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|wpages
comma
id|FLUSH_WAIT
)paren
suffix:semicolon
multiline_comment|/* invalidate cache so non-direct readers pick up changes */
id|invalidate_inode_pages
c_func
(paren
(paren
r_struct
id|inode
op_star
)paren
id|inode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_return
id|tot_bytes
suffix:semicolon
)brace
multiline_comment|/**&n; * nfs_direct_IO - NFS address space operation for direct I/O&n; * rw: direction (read or write)&n; * @file: file struct of target file&n; * @iov: array of vectors that define I/O buffer&n; * offset: offset in file to begin the operation&n; * nr_segs: size of iovec array&n; *&n; * The inode&squot;s i_sem is no longer held by the VFS layer before it calls&n; * this function to do a write.&n; */
r_int
DECL|function|nfs_direct_IO
id|nfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
multiline_comment|/* None of this works yet, so prevent it from compiling. */
macro_line|#if 0
r_int
id|result
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_const
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode-&gt;i_mapping-&gt;host
suffix:semicolon
r_const
r_struct
id|rpc_cred
op_star
id|cred
op_assign
id|nfs_file_cred
c_func
(paren
id|file
)paren
suffix:semicolon
macro_line|#endif
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;NFS: direct_IO(%s) (%s/%s) off/no(%Lu/%lu)&bslash;n&quot;
comma
(paren
(paren
id|rw
op_eq
id|READ
)paren
ques
c_cond
l_string|&quot;READ&quot;
suffix:colon
l_string|&quot;WRITE&quot;
)paren
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|offset
comma
id|nr_segs
)paren
suffix:semicolon
id|result
op_assign
id|do_nfs_direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|cred
comma
id|iov
comma
id|offset
comma
id|nr_segs
)paren
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;NFS: direct_IO result = %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
