multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_rw.h&quot;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|variable|linvfs_file_vm_ops
r_static
r_struct
id|vm_operations_struct
id|linvfs_file_vm_ops
suffix:semicolon
id|STATIC
r_inline
id|ssize_t
DECL|function|__linvfs_read
id|__linvfs_read
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
id|ioflags
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|iovec
id|iov
op_assign
(brace
id|buf
comma
id|count
)brace
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|ssize_t
id|rval
suffix:semicolon
id|BUG_ON
c_func
(paren
id|iocb-&gt;ki_pos
op_ne
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|file-&gt;f_flags
op_amp
id|O_DIRECT
)paren
)paren
id|ioflags
op_or_assign
id|IO_ISDIRECT
suffix:semicolon
id|VOP_READ
c_func
(paren
id|vp
comma
id|iocb
comma
op_amp
id|iov
comma
l_int|1
comma
op_amp
id|iocb-&gt;ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_read
id|linvfs_read
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
r_return
id|__linvfs_read
c_func
(paren
id|iocb
comma
id|buf
comma
l_int|0
comma
id|count
comma
id|pos
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_read_invis
id|linvfs_read_invis
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
r_return
id|__linvfs_read
c_func
(paren
id|iocb
comma
id|buf
comma
id|IO_INVIS
comma
id|count
comma
id|pos
)paren
suffix:semicolon
)brace
id|STATIC
r_inline
id|ssize_t
DECL|function|__linvfs_write
id|__linvfs_write
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
id|ioflags
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|iovec
id|iov
op_assign
(brace
(paren
r_void
id|__user
op_star
)paren
id|buf
comma
id|count
)brace
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_mapping-&gt;host
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ssize_t
id|rval
suffix:semicolon
id|BUG_ON
c_func
(paren
id|iocb-&gt;ki_pos
op_ne
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|file-&gt;f_flags
op_amp
id|O_DIRECT
)paren
)paren
(brace
id|ioflags
op_or_assign
id|IO_ISDIRECT
suffix:semicolon
id|VOP_WRITE
c_func
(paren
id|vp
comma
id|iocb
comma
op_amp
id|iov
comma
l_int|1
comma
op_amp
id|iocb-&gt;ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
)brace
r_else
(brace
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|VOP_WRITE
c_func
(paren
id|vp
comma
id|iocb
comma
op_amp
id|iov
comma
l_int|1
comma
op_amp
id|iocb-&gt;ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
id|rval
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_write
id|linvfs_write
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
r_return
id|__linvfs_write
c_func
(paren
id|iocb
comma
id|buf
comma
l_int|0
comma
id|count
comma
id|pos
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_write_invis
id|linvfs_write_invis
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
r_return
id|__linvfs_write
c_func
(paren
id|iocb
comma
id|buf
comma
id|IO_INVIS
comma
id|count
comma
id|pos
)paren
suffix:semicolon
)brace
id|STATIC
r_inline
id|ssize_t
DECL|function|__linvfs_readv
id|__linvfs_readv
c_func
(paren
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
r_int
id|ioflags
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_mapping-&gt;host
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|kiocb
id|kiocb
suffix:semicolon
id|ssize_t
id|rval
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|kiocb
comma
id|file
)paren
suffix:semicolon
id|kiocb.ki_pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|file-&gt;f_flags
op_amp
id|O_DIRECT
)paren
)paren
id|ioflags
op_or_assign
id|IO_ISDIRECT
suffix:semicolon
id|VOP_READ
c_func
(paren
id|vp
comma
op_amp
id|kiocb
comma
id|iov
comma
id|nr_segs
comma
op_amp
id|kiocb.ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
op_eq
op_minus
id|EIOCBQUEUED
)paren
id|rval
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|kiocb
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|kiocb.ki_pos
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_readv
id|linvfs_readv
c_func
(paren
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
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|__linvfs_readv
c_func
(paren
id|file
comma
id|iov
comma
l_int|0
comma
id|nr_segs
comma
id|ppos
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_readv_invis
id|linvfs_readv_invis
c_func
(paren
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
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|__linvfs_readv
c_func
(paren
id|file
comma
id|iov
comma
id|IO_INVIS
comma
id|nr_segs
comma
id|ppos
)paren
suffix:semicolon
)brace
id|STATIC
r_inline
id|ssize_t
DECL|function|__linvfs_writev
id|__linvfs_writev
c_func
(paren
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
r_int
id|ioflags
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_mapping-&gt;host
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|kiocb
id|kiocb
suffix:semicolon
id|ssize_t
id|rval
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|kiocb
comma
id|file
)paren
suffix:semicolon
id|kiocb.ki_pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|file-&gt;f_flags
op_amp
id|O_DIRECT
)paren
)paren
(brace
id|ioflags
op_or_assign
id|IO_ISDIRECT
suffix:semicolon
id|VOP_WRITE
c_func
(paren
id|vp
comma
op_amp
id|kiocb
comma
id|iov
comma
id|nr_segs
comma
op_amp
id|kiocb.ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
)brace
r_else
(brace
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|VOP_WRITE
c_func
(paren
id|vp
comma
op_amp
id|kiocb
comma
id|iov
comma
id|nr_segs
comma
op_amp
id|kiocb.ki_pos
comma
id|ioflags
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rval
op_eq
op_minus
id|EIOCBQUEUED
)paren
id|rval
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|kiocb
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|kiocb.ki_pos
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_writev
id|linvfs_writev
c_func
(paren
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
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|__linvfs_writev
c_func
(paren
id|file
comma
id|iov
comma
l_int|0
comma
id|nr_segs
comma
id|ppos
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_writev_invis
id|linvfs_writev_invis
c_func
(paren
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
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|__linvfs_writev
c_func
(paren
id|file
comma
id|iov
comma
id|IO_INVIS
comma
id|nr_segs
comma
id|ppos
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_sendfile
id|linvfs_sendfile
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|count
comma
id|read_actor_t
id|actor
comma
r_void
id|__user
op_star
id|target
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|ssize_t
id|rval
suffix:semicolon
id|VOP_SENDFILE
c_func
(paren
id|vp
comma
id|filp
comma
id|ppos
comma
l_int|0
comma
id|count
comma
id|actor
comma
id|target
comma
l_int|NULL
comma
id|rval
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_open
id|linvfs_open
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
id|filp
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_LARGEFILE
)paren
op_logical_and
id|i_size_read
c_func
(paren
id|inode
)paren
OG
id|MAX_NON_LFS
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
id|ASSERT
c_func
(paren
id|vp
)paren
suffix:semicolon
id|VOP_OPEN
c_func
(paren
id|vp
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_release
id|linvfs_release
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
id|filp
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vp
)paren
id|VOP_RELEASE
c_func
(paren
id|vp
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_fsync
id|linvfs_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|flags
op_assign
id|FSYNC_WAIT
suffix:semicolon
r_if
c_cond
(paren
id|datasync
)paren
id|flags
op_or_assign
id|FSYNC_DATA
suffix:semicolon
id|ASSERT
c_func
(paren
id|vp
)paren
suffix:semicolon
id|VOP_FSYNC
c_func
(paren
id|vp
comma
id|flags
comma
l_int|NULL
comma
(paren
id|xfs_off_t
)paren
l_int|0
comma
(paren
id|xfs_off_t
)paren
op_minus
l_int|1
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * linvfs_readdir maps to VOP_READDIR().&n; * We need to build a uio, cred, ...&n; */
DECL|macro|nextdp
mdefine_line|#define nextdp(dp)      ((struct xfs_dirent *)((char *)(dp) + (dp)-&gt;d_reclen))
id|STATIC
r_int
DECL|function|linvfs_readdir
id|linvfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|vnode_t
op_star
id|vp
suffix:semicolon
id|uio_t
id|uio
suffix:semicolon
id|iovec_t
id|iov
suffix:semicolon
r_int
id|eof
op_assign
l_int|0
suffix:semicolon
id|caddr_t
id|read_buf
suffix:semicolon
r_int
id|namelen
comma
id|size
op_assign
l_int|0
suffix:semicolon
r_int
id|rlen
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|xfs_off_t
id|start_offset
comma
id|curr_offset
suffix:semicolon
id|xfs_dirent_t
op_star
id|dbp
op_assign
l_int|NULL
suffix:semicolon
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|vp
)paren
suffix:semicolon
multiline_comment|/* Try fairly hard to get memory */
r_do
(brace
r_if
c_cond
(paren
(paren
id|read_buf
op_assign
(paren
id|caddr_t
)paren
id|kmalloc
c_func
(paren
id|rlen
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_break
suffix:semicolon
id|rlen
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rlen
op_ge
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|uio.uio_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|uio.uio_segflg
op_assign
id|UIO_SYSSPACE
suffix:semicolon
id|curr_offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_ne
l_int|0x7fffffff
)paren
id|uio.uio_offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_else
id|uio.uio_offset
op_assign
l_int|0xffffffff
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|eof
)paren
(brace
id|uio.uio_resid
op_assign
id|iov.iov_len
op_assign
id|rlen
suffix:semicolon
id|iov.iov_base
op_assign
id|read_buf
suffix:semicolon
id|uio.uio_iovcnt
op_assign
l_int|1
suffix:semicolon
id|start_offset
op_assign
id|uio.uio_offset
suffix:semicolon
id|VOP_READDIR
c_func
(paren
id|vp
comma
op_amp
id|uio
comma
l_int|NULL
comma
op_amp
id|eof
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|uio.uio_offset
op_eq
id|start_offset
)paren
op_logical_or
id|error
)paren
(brace
id|size
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|size
op_assign
id|rlen
op_minus
id|uio.uio_resid
suffix:semicolon
id|dbp
op_assign
(paren
id|xfs_dirent_t
op_star
)paren
id|read_buf
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|namelen
op_assign
id|strlen
c_func
(paren
id|dbp-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|dbp-&gt;d_name
comma
id|namelen
comma
(paren
id|loff_t
)paren
id|curr_offset
op_amp
l_int|0x7fffffff
comma
(paren
id|ino_t
)paren
id|dbp-&gt;d_ino
comma
id|DT_UNKNOWN
)paren
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
id|size
op_sub_assign
id|dbp-&gt;d_reclen
suffix:semicolon
id|curr_offset
op_assign
(paren
id|loff_t
)paren
id|dbp-&gt;d_off
multiline_comment|/* &amp; 0x7fffffff */
suffix:semicolon
id|dbp
op_assign
id|nextdp
c_func
(paren
id|dbp
)paren
suffix:semicolon
)brace
)brace
id|done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
id|filp-&gt;f_pos
op_assign
id|uio.uio_offset
op_amp
l_int|0x7fffffff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dbp
)paren
id|filp-&gt;f_pos
op_assign
id|curr_offset
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|read_buf
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_file_mmap
id|linvfs_file_mmap
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|inode
op_star
id|ip
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|ip
)paren
suffix:semicolon
id|vattr_t
id|va
op_assign
(brace
dot
id|va_mask
op_assign
id|XFS_AT_UPDATIME
)brace
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vp-&gt;v_type
op_eq
id|VREG
)paren
op_logical_and
(paren
id|vp-&gt;v_vfsp-&gt;vfs_flag
op_amp
id|VFS_DMI
)paren
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|XFS_VFSTOM
c_func
(paren
id|vp-&gt;v_vfsp
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|XFS_SEND_MMAP
c_func
(paren
id|mp
comma
id|vma
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
id|vma-&gt;vm_ops
op_assign
op_amp
id|linvfs_file_vm_ops
suffix:semicolon
id|VOP_SETATTR
c_func
(paren
id|vp
comma
op_amp
id|va
comma
id|XFS_AT_UPDATIME
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_ioctl
id|linvfs_ioctl
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|VOP_IOCTL
c_func
(paren
id|vp
comma
id|inode
comma
id|filp
comma
l_int|0
comma
id|cmd
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
id|error
)paren
suffix:semicolon
id|VMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTE:  some of the ioctl&squot;s return positive #&squot;s as a&n;&t; *&t;  byte count indicating success, such as&n;&t; *&t;  readlink_by_handle.  So we don&squot;t &quot;sign flip&quot;&n;&t; *&t;  like most other routines.  This means true&n;&t; *&t;  errors need to be returned as a negative value.&n;&t; */
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_ioctl_invis
id|linvfs_ioctl_invis
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|vp
)paren
suffix:semicolon
id|VOP_IOCTL
c_func
(paren
id|vp
comma
id|inode
comma
id|filp
comma
id|IO_INVIS
comma
id|cmd
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
id|error
)paren
suffix:semicolon
id|VMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTE:  some of the ioctl&squot;s return positive #&squot;s as a&n;&t; *&t;  byte count indicating success, such as&n;&t; *&t;  readlink_by_handle.  So we don&squot;t &quot;sign flip&quot;&n;&t; *&t;  like most other routines.  This means true&n;&t; *&t;  errors need to be returned as a negative value.&n;&t; */
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifdef HAVE_VMOP_MPROTECT
id|STATIC
r_int
DECL|function|linvfs_mprotect
id|linvfs_mprotect
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|newflags
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|vma-&gt;vm_file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vp-&gt;v_type
op_eq
id|VREG
)paren
op_logical_and
(paren
id|vp-&gt;v_vfsp-&gt;vfs_flag
op_amp
id|VFS_DMI
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_MAYSHARE
)paren
op_logical_and
(paren
id|newflags
op_amp
id|VM_WRITE
)paren
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|XFS_VFSTOM
c_func
(paren
id|vp-&gt;v_vfsp
)paren
suffix:semicolon
id|error
op_assign
id|XFS_SEND_MMAP
c_func
(paren
id|mp
comma
id|vma
comma
id|VM_WRITE
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif /* HAVE_VMOP_MPROTECT */
DECL|variable|linvfs_file_operations
r_struct
id|file_operations
id|linvfs_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|do_sync_read
comma
dot
id|write
op_assign
id|do_sync_write
comma
dot
id|readv
op_assign
id|linvfs_readv
comma
dot
id|writev
op_assign
id|linvfs_writev
comma
dot
id|aio_read
op_assign
id|linvfs_read
comma
dot
id|aio_write
op_assign
id|linvfs_write
comma
dot
id|sendfile
op_assign
id|linvfs_sendfile
comma
dot
id|ioctl
op_assign
id|linvfs_ioctl
comma
dot
id|mmap
op_assign
id|linvfs_file_mmap
comma
dot
id|open
op_assign
id|linvfs_open
comma
dot
id|release
op_assign
id|linvfs_release
comma
dot
id|fsync
op_assign
id|linvfs_fsync
comma
)brace
suffix:semicolon
DECL|variable|linvfs_invis_file_operations
r_struct
id|file_operations
id|linvfs_invis_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|do_sync_read
comma
dot
id|write
op_assign
id|do_sync_write
comma
dot
id|readv
op_assign
id|linvfs_readv_invis
comma
dot
id|writev
op_assign
id|linvfs_writev_invis
comma
dot
id|aio_read
op_assign
id|linvfs_read_invis
comma
dot
id|aio_write
op_assign
id|linvfs_write_invis
comma
dot
id|sendfile
op_assign
id|linvfs_sendfile
comma
dot
id|ioctl
op_assign
id|linvfs_ioctl_invis
comma
dot
id|mmap
op_assign
id|linvfs_file_mmap
comma
dot
id|open
op_assign
id|linvfs_open
comma
dot
id|release
op_assign
id|linvfs_release
comma
dot
id|fsync
op_assign
id|linvfs_fsync
comma
)brace
suffix:semicolon
DECL|variable|linvfs_dir_operations
r_struct
id|file_operations
id|linvfs_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|linvfs_readdir
comma
dot
id|ioctl
op_assign
id|linvfs_ioctl
comma
dot
id|fsync
op_assign
id|linvfs_fsync
comma
)brace
suffix:semicolon
DECL|variable|linvfs_file_vm_ops
r_static
r_struct
id|vm_operations_struct
id|linvfs_file_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|filemap_nopage
comma
macro_line|#ifdef HAVE_VMOP_MPROTECT
dot
id|mprotect
op_assign
id|linvfs_mprotect
comma
macro_line|#endif
)brace
suffix:semicolon
eof
