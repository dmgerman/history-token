multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
multiline_comment|/*&n; * Implementation for VFS_DOUNMOUNT.&n; */
r_int
DECL|function|fs_dounmount
id|fs_dounmount
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
r_int
id|flags
comma
id|vnode_t
op_star
id|rootvp
comma
id|cred_t
op_star
id|cr
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|bhvtovfs
c_func
(paren
id|bdp
)paren
suffix:semicolon
id|bhv_desc_t
op_star
id|fbdp
op_assign
id|vfsp-&gt;vfs_fbhv
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for sync to finish and lock vfsp.  This also sets the&n;&t; * VFS_OFFLINE flag.  Once we do this we can give up reference&n;&t; * the root vnode which we hold to avoid the another unmount&n;&t; * ripping the vfs out from under us before we get to lock it.&n;&t; * The VFS_DOUNMOUNT calling convention is that the reference&n;&t; * on the rot vnode is released whether the call succeeds or&n;&t; * fails.&n;&t; */
r_if
c_cond
(paren
id|rootvp
)paren
id|VN_RELE
c_func
(paren
id|rootvp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now invoke SYNC and UNMOUNT ops, using the PVFS versions is&n;&t; * OK since we already have a behavior lock as a result of&n;&t; * being in VFS_DOUNMOUNT.  It is necessary to do things this&n;&t; * way since using the VFS versions would cause us to get the&n;&t; * behavior lock twice which can cause deadlock as well as&n;&t; * making the coding of vfs relocation unnecessarilty difficult&n;&t; * by making relocations invoked by unmount occur in a different&n;&t; * environment than those invoked by mount-update.&n;&t; */
id|PVFS_SYNC
c_func
(paren
id|fbdp
comma
id|SYNC_ATTR
op_or
id|SYNC_DELWRI
comma
id|cr
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|PVFS_UNMOUNT
c_func
(paren
id|fbdp
comma
id|flags
comma
id|cr
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Stub for no-op vnode operations that return error status.&n; */
r_int
DECL|function|fs_noerr
id|fs_noerr
c_func
(paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Operation unsupported under this file system.&n; */
r_int
DECL|function|fs_nosys
id|fs_nosys
c_func
(paren
)paren
(brace
r_return
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/*&n; * Stub for inactive, strategy, and read/write lock/unlock.  Does nothing.&n; */
multiline_comment|/* ARGSUSED */
r_void
DECL|function|fs_noval
id|fs_noval
c_func
(paren
)paren
(brace
)brace
multiline_comment|/*&n; * vnode pcache layer for vnode_tosspages.&n; * &squot;last&squot; parameter unused but left in for IRIX compatibility&n; */
r_void
DECL|function|fs_tosspages
id|fs_tosspages
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|xfs_off_t
id|first
comma
id|xfs_off_t
id|last
comma
r_int
id|fiopt
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|BHV_TO_VNODE
c_func
(paren
id|bdp
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VN_CACHED
c_func
(paren
id|vp
)paren
)paren
id|truncate_inode_pages
c_func
(paren
id|ip-&gt;i_mapping
comma
id|first
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vnode pcache layer for vnode_flushinval_pages.&n; * &squot;last&squot; parameter unused but left in for IRIX compatibility&n; */
r_void
DECL|function|fs_flushinval_pages
id|fs_flushinval_pages
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|xfs_off_t
id|first
comma
id|xfs_off_t
id|last
comma
r_int
id|fiopt
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|BHV_TO_VNODE
c_func
(paren
id|bdp
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VN_CACHED
c_func
(paren
id|vp
)paren
)paren
(brace
id|filemap_fdatawait
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawrite
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|ip-&gt;i_mapping
comma
id|first
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * vnode pcache layer for vnode_flush_pages.&n; * &squot;last&squot; parameter unused but left in for IRIX compatibility&n; */
r_int
DECL|function|fs_flush_pages
id|fs_flush_pages
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|xfs_off_t
id|first
comma
id|xfs_off_t
id|last
comma
r_uint64
id|flags
comma
r_int
id|fiopt
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|BHV_TO_VNODE
c_func
(paren
id|bdp
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VN_CACHED
c_func
(paren
id|vp
)paren
)paren
(brace
id|filemap_fdatawait
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawrite
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|ip-&gt;i_mapping
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
