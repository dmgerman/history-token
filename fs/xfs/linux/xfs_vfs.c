multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_clnt.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_imap.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
r_int
DECL|function|vfs_mount
id|vfs_mount
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|xfs_mount_args
op_star
id|args
comma
r_struct
id|cred
op_star
id|cr
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_mount
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_mount
)paren
(paren
id|next
comma
id|args
comma
id|cr
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_parseargs
id|vfs_parseargs
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_char
op_star
id|s
comma
r_struct
id|xfs_mount_args
op_star
id|args
comma
r_int
id|f
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_parseargs
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_parseargs
)paren
(paren
id|next
comma
id|s
comma
id|args
comma
id|f
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_showargs
id|vfs_showargs
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_showargs
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_showargs
)paren
(paren
id|next
comma
id|m
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_unmount
id|vfs_unmount
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_int
id|fl
comma
r_struct
id|cred
op_star
id|cr
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_unmount
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_unmount
)paren
(paren
id|next
comma
id|fl
comma
id|cr
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_mntupdate
id|vfs_mntupdate
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_int
op_star
id|fl
comma
r_struct
id|xfs_mount_args
op_star
id|args
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_mntupdate
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_mntupdate
)paren
(paren
id|next
comma
id|fl
comma
id|args
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_root
id|vfs_root
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|vnode
op_star
op_star
id|vpp
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_root
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_root
)paren
(paren
id|next
comma
id|vpp
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_statvfs
id|vfs_statvfs
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
id|xfs_statfs_t
op_star
id|sp
comma
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_statvfs
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_statvfs
)paren
(paren
id|next
comma
id|sp
comma
id|vp
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_sync
id|vfs_sync
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_int
id|fl
comma
r_struct
id|cred
op_star
id|cr
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_sync
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_sync
)paren
(paren
id|next
comma
id|fl
comma
id|cr
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_vget
id|vfs_vget
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|vnode
op_star
op_star
id|vpp
comma
r_struct
id|fid
op_star
id|fidp
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_vget
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_vget
)paren
(paren
id|next
comma
id|vpp
comma
id|fidp
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_dmapiops
id|vfs_dmapiops
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
id|caddr_t
id|addr
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_dmapiops
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_dmapiops
)paren
(paren
id|next
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|vfs_quotactl
id|vfs_quotactl
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_int
id|cmd
comma
r_int
id|id
comma
id|caddr_t
id|addr
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_quotactl
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
r_return
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_quotactl
)paren
(paren
id|next
comma
id|cmd
comma
id|id
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|vfs_init_vnode
id|vfs_init_vnode
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|vnode
op_star
id|vp
comma
r_struct
id|bhv_desc
op_star
id|bp
comma
r_int
id|unlock
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_init_vnode
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_init_vnode
)paren
(paren
id|next
comma
id|vp
comma
id|bp
comma
id|unlock
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|vfs_force_shutdown
id|vfs_force_shutdown
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_int
id|fl
comma
r_char
op_star
id|file
comma
r_int
id|line
)paren
(brace
r_struct
id|bhv_desc
op_star
id|next
op_assign
id|bdp
suffix:semicolon
id|ASSERT
c_func
(paren
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|bhvtovfsops
c_func
(paren
id|next
)paren
)paren
op_member_access_from_pointer
id|vfs_force_shutdown
)paren
id|next
op_assign
id|BHV_NEXT
c_func
(paren
id|next
)paren
suffix:semicolon
(paren
(paren
op_star
id|bhvtovfsops
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|vfs_force_shutdown
)paren
(paren
id|next
comma
id|fl
comma
id|file
comma
id|line
)paren
)paren
suffix:semicolon
)brace
id|vfs_t
op_star
DECL|function|vfs_allocate
id|vfs_allocate
c_func
(paren
r_void
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
suffix:semicolon
id|vfsp
op_assign
id|kmem_zalloc
c_func
(paren
r_sizeof
(paren
id|vfs_t
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|bhv_head_init
c_func
(paren
id|VFS_BHVHEAD
c_func
(paren
id|vfsp
)paren
comma
l_string|&quot;vfs&quot;
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|vfsp-&gt;vfs_wait_sync_task
)paren
suffix:semicolon
r_return
id|vfsp
suffix:semicolon
)brace
r_void
DECL|function|vfs_deallocate
id|vfs_deallocate
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
)paren
(brace
id|bhv_head_destroy
c_func
(paren
id|VFS_BHVHEAD
c_func
(paren
id|vfsp
)paren
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|vfsp
comma
r_sizeof
(paren
id|vfs_t
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|vfs_insertops
id|vfs_insertops
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
comma
r_struct
id|bhv_vfsops
op_star
id|vfsops
)paren
(brace
r_struct
id|bhv_desc
op_star
id|bdp
suffix:semicolon
id|bdp
op_assign
id|kmem_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|bhv_desc
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|bhv_desc_init
c_func
(paren
id|bdp
comma
l_int|NULL
comma
id|vfsp
comma
id|vfsops
)paren
suffix:semicolon
id|bhv_insert
c_func
(paren
op_amp
id|vfsp-&gt;vfs_bh
comma
id|bdp
)paren
suffix:semicolon
)brace
r_void
DECL|function|vfs_insertbhv
id|vfs_insertbhv
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
comma
r_struct
id|bhv_desc
op_star
id|bdp
comma
r_struct
id|vfsops
op_star
id|vfsops
comma
r_void
op_star
id|mount
)paren
(brace
id|bhv_desc_init
c_func
(paren
id|bdp
comma
id|mount
comma
id|vfsp
comma
id|vfsops
)paren
suffix:semicolon
id|bhv_insert_initial
c_func
(paren
op_amp
id|vfsp-&gt;vfs_bh
comma
id|bdp
)paren
suffix:semicolon
)brace
r_void
DECL|function|bhv_remove_vfsops
id|bhv_remove_vfsops
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
comma
r_int
id|pos
)paren
(brace
r_struct
id|bhv_desc
op_star
id|bhv
suffix:semicolon
id|bhv
op_assign
id|bhv_lookup_range
c_func
(paren
op_amp
id|vfsp-&gt;vfs_bh
comma
id|pos
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bhv
)paren
r_return
suffix:semicolon
id|bhv_remove
c_func
(paren
op_amp
id|vfsp-&gt;vfs_bh
comma
id|bhv
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|bhv
comma
r_sizeof
(paren
op_star
id|bhv
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|bhv_remove_all_vfsops
id|bhv_remove_all_vfsops
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
comma
r_int
id|freebase
)paren
(brace
r_struct
id|xfs_mount
op_star
id|mp
suffix:semicolon
id|bhv_remove_vfsops
c_func
(paren
id|vfsp
comma
id|VFS_POSITION_QM
)paren
suffix:semicolon
id|bhv_remove_vfsops
c_func
(paren
id|vfsp
comma
id|VFS_POSITION_DM
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|freebase
)paren
r_return
suffix:semicolon
id|mp
op_assign
id|XFS_BHVTOM
c_func
(paren
id|bhv_lookup
c_func
(paren
id|VFS_BHVHEAD
c_func
(paren
id|vfsp
)paren
comma
op_amp
id|xfs_vfsops
)paren
)paren
suffix:semicolon
id|VFS_REMOVEBHV
c_func
(paren
id|vfsp
comma
op_amp
id|mp-&gt;m_bhv
)paren
suffix:semicolon
id|xfs_mount_free
c_func
(paren
id|mp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|bhv_insert_all_vfsops
id|bhv_insert_all_vfsops
c_func
(paren
r_struct
id|vfs
op_star
id|vfsp
)paren
(brace
r_struct
id|xfs_mount
op_star
id|mp
suffix:semicolon
id|mp
op_assign
id|xfs_mount_init
c_func
(paren
)paren
suffix:semicolon
id|vfs_insertbhv
c_func
(paren
id|vfsp
comma
op_amp
id|mp-&gt;m_bhv
comma
op_amp
id|xfs_vfsops
comma
id|mp
)paren
suffix:semicolon
id|vfs_insertdmapi
c_func
(paren
id|vfsp
)paren
suffix:semicolon
id|vfs_insertquota
c_func
(paren
id|vfsp
)paren
suffix:semicolon
)brace
eof
