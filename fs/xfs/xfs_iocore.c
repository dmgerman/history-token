multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_itable.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode_item.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_bit.h&quot;
macro_line|#include &quot;xfs_rw.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
macro_line|#include &quot;xfs_trans_space.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
id|STATIC
id|xfs_fsize_t
DECL|function|xfs_size_fn
id|xfs_size_fn
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
r_return
(paren
id|ip-&gt;i_d.di_size
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_ioinit
id|xfs_ioinit
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
comma
r_struct
id|xfs_mount_args
op_star
id|mntargs
comma
r_int
id|flags
)paren
(brace
r_return
id|xfs_mountfs
c_func
(paren
id|vfsp
comma
id|XFS_VFSTOM
c_func
(paren
id|vfsp
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|xfs_iocore_xfs
id|xfs_ioops_t
id|xfs_iocore_xfs
op_assign
(brace
dot
id|xfs_ioinit
op_assign
(paren
id|xfs_ioinit_t
)paren
id|xfs_ioinit
comma
dot
id|xfs_bmapi_func
op_assign
(paren
id|xfs_bmapi_t
)paren
id|xfs_bmapi
comma
dot
id|xfs_bmap_eof_func
op_assign
(paren
id|xfs_bmap_eof_t
)paren
id|xfs_bmap_eof
comma
dot
id|xfs_iomap_write_direct
op_assign
(paren
id|xfs_iomap_write_direct_t
)paren
id|xfs_iomap_write_direct
comma
dot
id|xfs_iomap_write_delay
op_assign
(paren
id|xfs_iomap_write_delay_t
)paren
id|xfs_iomap_write_delay
comma
dot
id|xfs_iomap_write_allocate
op_assign
(paren
id|xfs_iomap_write_allocate_t
)paren
id|xfs_iomap_write_allocate
comma
dot
id|xfs_iomap_write_unwritten
op_assign
(paren
id|xfs_iomap_write_unwritten_t
)paren
id|xfs_iomap_write_unwritten
comma
dot
id|xfs_ilock
op_assign
(paren
id|xfs_lock_t
)paren
id|xfs_ilock
comma
dot
id|xfs_lck_map_shared
op_assign
(paren
id|xfs_lck_map_shared_t
)paren
id|xfs_ilock_map_shared
comma
dot
id|xfs_ilock_demote
op_assign
(paren
id|xfs_lock_demote_t
)paren
id|xfs_ilock_demote
comma
dot
id|xfs_ilock_nowait
op_assign
(paren
id|xfs_lock_nowait_t
)paren
id|xfs_ilock_nowait
comma
dot
id|xfs_unlock
op_assign
(paren
id|xfs_unlk_t
)paren
id|xfs_iunlock
comma
dot
id|xfs_size_func
op_assign
(paren
id|xfs_size_t
)paren
id|xfs_size_fn
comma
dot
id|xfs_iodone
op_assign
(paren
id|xfs_iodone_t
)paren
id|fs_noerr
comma
)brace
suffix:semicolon
r_void
DECL|function|xfs_iocore_inode_reinit
id|xfs_iocore_inode_reinit
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|xfs_iocore_t
op_star
id|io
op_assign
op_amp
id|ip-&gt;i_iocore
suffix:semicolon
id|io-&gt;io_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_d.di_flags
op_amp
id|XFS_DIFLAG_REALTIME
)paren
id|io-&gt;io_flags
op_or_assign
id|XFS_IOCORE_RT
suffix:semicolon
id|io-&gt;io_dmevmask
op_assign
id|ip-&gt;i_d.di_dmevmask
suffix:semicolon
id|io-&gt;io_dmstate
op_assign
id|ip-&gt;i_d.di_dmstate
suffix:semicolon
)brace
r_void
DECL|function|xfs_iocore_inode_init
id|xfs_iocore_inode_init
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|xfs_iocore_t
op_star
id|io
op_assign
op_amp
id|ip-&gt;i_iocore
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|io-&gt;io_mount
op_assign
id|mp
suffix:semicolon
macro_line|#ifdef DEBUG
id|io-&gt;io_lock
op_assign
op_amp
id|ip-&gt;i_lock
suffix:semicolon
id|io-&gt;io_iolock
op_assign
op_amp
id|ip-&gt;i_iolock
suffix:semicolon
macro_line|#endif
id|io-&gt;io_obj
op_assign
(paren
r_void
op_star
)paren
id|ip
suffix:semicolon
id|xfs_iocore_inode_reinit
c_func
(paren
id|ip
)paren
suffix:semicolon
)brace
eof
