multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; *&n; * Portions Copyright (c) 1989, 1993&n; *&t;The Regents of the University of California.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. Neither the name of the University nor the names of its contributors&n; *    may be used to endorse or promote products derived from this software&n; *    without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef __XFS_VNODE_H__
DECL|macro|__XFS_VNODE_H__
mdefine_line|#define __XFS_VNODE_H__
r_struct
id|uio
suffix:semicolon
r_struct
id|file
suffix:semicolon
r_struct
id|vattr
suffix:semicolon
r_struct
id|xfs_iomap
suffix:semicolon
r_struct
id|attrlist_cursor_kern
suffix:semicolon
multiline_comment|/*&n; * Vnode types.  VNON means no type.&n; */
DECL|enum|vtype
DECL|enumerator|VNON
DECL|enumerator|VREG
DECL|enumerator|VDIR
DECL|enumerator|VBLK
DECL|enumerator|VCHR
DECL|enumerator|VLNK
DECL|enumerator|VFIFO
DECL|enumerator|VBAD
DECL|enumerator|VSOCK
r_enum
id|vtype
(brace
id|VNON
comma
id|VREG
comma
id|VDIR
comma
id|VBLK
comma
id|VCHR
comma
id|VLNK
comma
id|VFIFO
comma
id|VBAD
comma
id|VSOCK
)brace
suffix:semicolon
DECL|typedef|vnumber_t
r_typedef
id|xfs_ino_t
id|vnumber_t
suffix:semicolon
DECL|typedef|vname_t
r_typedef
r_struct
id|dentry
id|vname_t
suffix:semicolon
DECL|typedef|vn_bhv_head_t
r_typedef
id|bhv_head_t
id|vn_bhv_head_t
suffix:semicolon
multiline_comment|/*&n; * MP locking protocols:&n; *&t;v_flag, v_vfsp&t;&t;&t;&t;VN_LOCK/VN_UNLOCK&n; *&t;v_type&t;&t;&t;&t;&t;read-only or fs-dependent&n; */
DECL|struct|vnode
r_typedef
r_struct
id|vnode
(brace
DECL|member|v_flag
id|__u32
id|v_flag
suffix:semicolon
multiline_comment|/* vnode flags (see below) */
DECL|member|v_type
r_enum
id|vtype
id|v_type
suffix:semicolon
multiline_comment|/* vnode type */
DECL|member|v_vfsp
r_struct
id|vfs
op_star
id|v_vfsp
suffix:semicolon
multiline_comment|/* ptr to containing VFS */
DECL|member|v_number
id|vnumber_t
id|v_number
suffix:semicolon
multiline_comment|/* in-core vnode number */
DECL|member|v_bh
id|vn_bhv_head_t
id|v_bh
suffix:semicolon
multiline_comment|/* behavior head */
DECL|member|v_lock
id|spinlock_t
id|v_lock
suffix:semicolon
multiline_comment|/* VN_LOCK/VN_UNLOCK */
DECL|member|v_inode
r_struct
id|inode
id|v_inode
suffix:semicolon
multiline_comment|/* Linux inode */
macro_line|#ifdef XFS_VNODE_TRACE
DECL|member|v_trace
r_struct
id|ktrace
op_star
id|v_trace
suffix:semicolon
multiline_comment|/* trace header structure    */
macro_line|#endif
DECL|typedef|vnode_t
)brace
id|vnode_t
suffix:semicolon
DECL|macro|v_fbhv
mdefine_line|#define v_fbhv&t;&t;&t;v_bh.bh_first&t;       /* first behavior */
DECL|macro|v_fops
mdefine_line|#define v_fops&t;&t;&t;v_bh.bh_first-&gt;bd_ops  /* first behavior ops */
DECL|macro|VNODE_POSITION_BASE
mdefine_line|#define VNODE_POSITION_BASE&t;BHV_POSITION_BASE&t;/* chain bottom */
DECL|macro|VNODE_POSITION_TOP
mdefine_line|#define VNODE_POSITION_TOP&t;BHV_POSITION_TOP&t;/* chain top */
DECL|macro|VNODE_POSITION_INVALID
mdefine_line|#define VNODE_POSITION_INVALID&t;BHV_POSITION_INVALID&t;/* invalid pos. num */
r_typedef
r_enum
(brace
DECL|enumerator|VN_BHV_UNKNOWN
id|VN_BHV_UNKNOWN
comma
multiline_comment|/* not specified */
DECL|enumerator|VN_BHV_XFS
id|VN_BHV_XFS
comma
multiline_comment|/* xfs */
DECL|enumerator|VN_BHV_DM
id|VN_BHV_DM
comma
multiline_comment|/* data migration */
DECL|enumerator|VN_BHV_QM
id|VN_BHV_QM
comma
multiline_comment|/* quota manager */
DECL|enumerator|VN_BHV_IO
id|VN_BHV_IO
comma
multiline_comment|/* IO path */
DECL|enumerator|VN_BHV_END
id|VN_BHV_END
multiline_comment|/* housekeeping end-of-range */
DECL|typedef|vn_bhv_t
)brace
id|vn_bhv_t
suffix:semicolon
DECL|macro|VNODE_POSITION_XFS
mdefine_line|#define VNODE_POSITION_XFS&t;(VNODE_POSITION_BASE)
DECL|macro|VNODE_POSITION_DM
mdefine_line|#define VNODE_POSITION_DM&t;(VNODE_POSITION_BASE+10)
DECL|macro|VNODE_POSITION_QM
mdefine_line|#define VNODE_POSITION_QM&t;(VNODE_POSITION_BASE+20)
DECL|macro|VNODE_POSITION_IO
mdefine_line|#define VNODE_POSITION_IO&t;(VNODE_POSITION_BASE+30)
multiline_comment|/*&n; * Macros for dealing with the behavior descriptor inside of the vnode.&n; */
DECL|macro|BHV_TO_VNODE
mdefine_line|#define BHV_TO_VNODE(bdp)&t;((vnode_t *)BHV_VOBJ(bdp))
DECL|macro|BHV_TO_VNODE_NULL
mdefine_line|#define BHV_TO_VNODE_NULL(bdp)&t;((vnode_t *)BHV_VOBJNULL(bdp))
DECL|macro|VN_BHV_HEAD
mdefine_line|#define VN_BHV_HEAD(vp)&t;&t;&t;((bhv_head_t *)(&amp;((vp)-&gt;v_bh)))
DECL|macro|vn_bhv_head_init
mdefine_line|#define vn_bhv_head_init(bhp,name)&t;bhv_head_init(bhp,name)
DECL|macro|vn_bhv_remove
mdefine_line|#define vn_bhv_remove(bhp,bdp)&t;&t;bhv_remove(bhp,bdp)
DECL|macro|vn_bhv_lookup
mdefine_line|#define vn_bhv_lookup(bhp,ops)&t;&t;bhv_lookup(bhp,ops)
DECL|macro|vn_bhv_lookup_unlocked
mdefine_line|#define vn_bhv_lookup_unlocked(bhp,ops) bhv_lookup_unlocked(bhp,ops)
multiline_comment|/*&n; * Vnode to Linux inode mapping.&n; */
DECL|macro|LINVFS_GET_VP
mdefine_line|#define LINVFS_GET_VP(inode)&t;((vnode_t *)list_entry(inode, vnode_t, v_inode))
DECL|macro|LINVFS_GET_IP
mdefine_line|#define LINVFS_GET_IP(vp)&t;(&amp;(vp)-&gt;v_inode)
multiline_comment|/*&n; * Convert between vnode types and inode formats (since POSIX.1&n; * defines mode word of stat structure in terms of inode formats).&n; */
r_extern
r_enum
id|vtype
id|iftovt_tab
(braket
)braket
suffix:semicolon
r_extern
id|u_short
id|vttoif_tab
(braket
)braket
suffix:semicolon
DECL|macro|IFTOVT
mdefine_line|#define IFTOVT(mode)&t;(iftovt_tab[((mode) &amp; S_IFMT) &gt;&gt; 12])
DECL|macro|VTTOIF
mdefine_line|#define VTTOIF(indx)&t;(vttoif_tab[(int)(indx)])
DECL|macro|MAKEIMODE
mdefine_line|#define MAKEIMODE(indx, mode)&t;(int)(VTTOIF(indx) | (mode))
multiline_comment|/*&n; * Vnode flags.&n; */
DECL|macro|VINACT
mdefine_line|#define VINACT&t;&t;       0x1&t;/* vnode is being inactivated&t;*/
DECL|macro|VRECLM
mdefine_line|#define VRECLM&t;&t;       0x2&t;/* vnode is being reclaimed&t;*/
DECL|macro|VWAIT
mdefine_line|#define VWAIT&t;&t;       0x4&t;/* waiting for VINACT/VRECLM to end */
DECL|macro|VMODIFIED
mdefine_line|#define VMODIFIED&t;       0x8&t;/* XFS inode state possibly differs */
multiline_comment|/* to the Linux inode state.&t;*/
multiline_comment|/*&n; * Values for the VOP_RWLOCK and VOP_RWUNLOCK flags parameter.&n; */
DECL|enum|vrwlock
r_typedef
r_enum
id|vrwlock
(brace
DECL|enumerator|VRWLOCK_NONE
id|VRWLOCK_NONE
comma
DECL|enumerator|VRWLOCK_READ
id|VRWLOCK_READ
comma
DECL|enumerator|VRWLOCK_WRITE
id|VRWLOCK_WRITE
comma
DECL|enumerator|VRWLOCK_WRITE_DIRECT
id|VRWLOCK_WRITE_DIRECT
comma
DECL|enumerator|VRWLOCK_TRY_READ
id|VRWLOCK_TRY_READ
comma
DECL|enumerator|VRWLOCK_TRY_WRITE
id|VRWLOCK_TRY_WRITE
DECL|typedef|vrwlock_t
)brace
id|vrwlock_t
suffix:semicolon
multiline_comment|/*&n; * Return values for VOP_INACTIVE.  A return value of&n; * VN_INACTIVE_NOCACHE implies that the file system behavior&n; * has disassociated its state and bhv_desc_t from the vnode.&n; */
DECL|macro|VN_INACTIVE_CACHE
mdefine_line|#define&t;VN_INACTIVE_CACHE&t;0
DECL|macro|VN_INACTIVE_NOCACHE
mdefine_line|#define&t;VN_INACTIVE_NOCACHE&t;1
multiline_comment|/*&n; * Values for the cmd code given to VOP_VNODE_CHANGE.&n; */
DECL|enum|vchange
r_typedef
r_enum
id|vchange
(brace
DECL|enumerator|VCHANGE_FLAGS_FRLOCKS
id|VCHANGE_FLAGS_FRLOCKS
op_assign
l_int|0
comma
DECL|enumerator|VCHANGE_FLAGS_ENF_LOCKING
id|VCHANGE_FLAGS_ENF_LOCKING
op_assign
l_int|1
comma
DECL|enumerator|VCHANGE_FLAGS_TRUNCATED
id|VCHANGE_FLAGS_TRUNCATED
op_assign
l_int|2
comma
DECL|enumerator|VCHANGE_FLAGS_PAGE_DIRTY
id|VCHANGE_FLAGS_PAGE_DIRTY
op_assign
l_int|3
comma
DECL|enumerator|VCHANGE_FLAGS_IOEXCL_COUNT
id|VCHANGE_FLAGS_IOEXCL_COUNT
op_assign
l_int|4
DECL|typedef|vchange_t
)brace
id|vchange_t
suffix:semicolon
DECL|typedef|vop_open_t
r_typedef
r_int
(paren
op_star
id|vop_open_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_read_t
r_typedef
id|ssize_t
(paren
op_star
id|vop_read_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|kiocb
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
r_int
comma
id|loff_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_write_t
r_typedef
id|ssize_t
(paren
op_star
id|vop_write_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|kiocb
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
r_int
comma
id|loff_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_sendfile_t
r_typedef
id|ssize_t
(paren
op_star
id|vop_sendfile_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|file
op_star
comma
id|loff_t
op_star
comma
r_int
comma
r_int
comma
id|read_actor_t
comma
r_void
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_ioctl_t
r_typedef
r_int
(paren
op_star
id|vop_ioctl_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
r_int
r_int
comma
r_void
id|__user
op_star
)paren
suffix:semicolon
DECL|typedef|vop_getattr_t
r_typedef
r_int
(paren
op_star
id|vop_getattr_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|vattr
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_setattr_t
r_typedef
r_int
(paren
op_star
id|vop_setattr_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|vattr
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_access_t
r_typedef
r_int
(paren
op_star
id|vop_access_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_lookup_t
r_typedef
r_int
(paren
op_star
id|vop_lookup_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
id|vnode_t
op_star
op_star
comma
r_int
comma
id|vnode_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_create_t
r_typedef
r_int
(paren
op_star
id|vop_create_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|vattr
op_star
comma
id|vnode_t
op_star
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_remove_t
r_typedef
r_int
(paren
op_star
id|vop_remove_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_link_t
r_typedef
r_int
(paren
op_star
id|vop_link_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vnode_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_rename_t
r_typedef
r_int
(paren
op_star
id|vop_rename_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
id|vnode_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_mkdir_t
r_typedef
r_int
(paren
op_star
id|vop_mkdir_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|vattr
op_star
comma
id|vnode_t
op_star
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_rmdir_t
r_typedef
r_int
(paren
op_star
id|vop_rmdir_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_readdir_t
r_typedef
r_int
(paren
op_star
id|vop_readdir_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|uio
op_star
comma
r_struct
id|cred
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|typedef|vop_symlink_t
r_typedef
r_int
(paren
op_star
id|vop_symlink_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
r_struct
id|vattr
op_star
comma
r_char
op_star
comma
id|vnode_t
op_star
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_readlink_t
r_typedef
r_int
(paren
op_star
id|vop_readlink_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|uio
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_fsync_t
r_typedef
r_int
(paren
op_star
id|vop_fsync_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
comma
id|xfs_off_t
comma
id|xfs_off_t
)paren
suffix:semicolon
DECL|typedef|vop_inactive_t
r_typedef
r_int
(paren
op_star
id|vop_inactive_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_fid2_t
r_typedef
r_int
(paren
op_star
id|vop_fid2_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|fid
op_star
)paren
suffix:semicolon
DECL|typedef|vop_release_t
r_typedef
r_int
(paren
op_star
id|vop_release_t
)paren
(paren
id|bhv_desc_t
op_star
)paren
suffix:semicolon
DECL|typedef|vop_rwlock_t
r_typedef
r_int
(paren
op_star
id|vop_rwlock_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vrwlock_t
)paren
suffix:semicolon
DECL|typedef|vop_rwunlock_t
r_typedef
r_void
(paren
op_star
id|vop_rwunlock_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vrwlock_t
)paren
suffix:semicolon
DECL|typedef|vop_bmap_t
r_typedef
r_int
(paren
op_star
id|vop_bmap_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|xfs_off_t
comma
id|ssize_t
comma
r_int
comma
r_struct
id|xfs_iomap
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|typedef|vop_reclaim_t
r_typedef
r_int
(paren
op_star
id|vop_reclaim_t
)paren
(paren
id|bhv_desc_t
op_star
)paren
suffix:semicolon
DECL|typedef|vop_attr_get_t
r_typedef
r_int
(paren
op_star
id|vop_attr_get_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_attr_set_t
r_typedef
r_int
(paren
op_star
id|vop_attr_set_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_attr_remove_t
r_typedef
r_int
(paren
op_star
id|vop_attr_remove_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_attr_list_t
r_typedef
r_int
(paren
op_star
id|vop_attr_list_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|attrlist_cursor_kern
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
DECL|typedef|vop_link_removed_t
r_typedef
r_void
(paren
op_star
id|vop_link_removed_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vnode_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vop_vnode_change_t
r_typedef
r_void
(paren
op_star
id|vop_vnode_change_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|vchange_t
comma
id|__psint_t
)paren
suffix:semicolon
DECL|typedef|vop_ptossvp_t
r_typedef
r_void
(paren
op_star
id|vop_ptossvp_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|xfs_off_t
comma
id|xfs_off_t
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vop_pflushinvalvp_t
r_typedef
r_void
(paren
op_star
id|vop_pflushinvalvp_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|xfs_off_t
comma
id|xfs_off_t
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vop_pflushvp_t
r_typedef
r_int
(paren
op_star
id|vop_pflushvp_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|xfs_off_t
comma
id|xfs_off_t
comma
r_uint64
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vop_iflush_t
r_typedef
r_int
(paren
op_star
id|vop_iflush_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|struct|vnodeops
r_typedef
r_struct
id|vnodeops
(brace
DECL|member|vn_position
id|bhv_position_t
id|vn_position
suffix:semicolon
multiline_comment|/* position within behavior chain */
DECL|member|vop_open
id|vop_open_t
id|vop_open
suffix:semicolon
DECL|member|vop_read
id|vop_read_t
id|vop_read
suffix:semicolon
DECL|member|vop_write
id|vop_write_t
id|vop_write
suffix:semicolon
DECL|member|vop_sendfile
id|vop_sendfile_t
id|vop_sendfile
suffix:semicolon
DECL|member|vop_ioctl
id|vop_ioctl_t
id|vop_ioctl
suffix:semicolon
DECL|member|vop_getattr
id|vop_getattr_t
id|vop_getattr
suffix:semicolon
DECL|member|vop_setattr
id|vop_setattr_t
id|vop_setattr
suffix:semicolon
DECL|member|vop_access
id|vop_access_t
id|vop_access
suffix:semicolon
DECL|member|vop_lookup
id|vop_lookup_t
id|vop_lookup
suffix:semicolon
DECL|member|vop_create
id|vop_create_t
id|vop_create
suffix:semicolon
DECL|member|vop_remove
id|vop_remove_t
id|vop_remove
suffix:semicolon
DECL|member|vop_link
id|vop_link_t
id|vop_link
suffix:semicolon
DECL|member|vop_rename
id|vop_rename_t
id|vop_rename
suffix:semicolon
DECL|member|vop_mkdir
id|vop_mkdir_t
id|vop_mkdir
suffix:semicolon
DECL|member|vop_rmdir
id|vop_rmdir_t
id|vop_rmdir
suffix:semicolon
DECL|member|vop_readdir
id|vop_readdir_t
id|vop_readdir
suffix:semicolon
DECL|member|vop_symlink
id|vop_symlink_t
id|vop_symlink
suffix:semicolon
DECL|member|vop_readlink
id|vop_readlink_t
id|vop_readlink
suffix:semicolon
DECL|member|vop_fsync
id|vop_fsync_t
id|vop_fsync
suffix:semicolon
DECL|member|vop_inactive
id|vop_inactive_t
id|vop_inactive
suffix:semicolon
DECL|member|vop_fid2
id|vop_fid2_t
id|vop_fid2
suffix:semicolon
DECL|member|vop_rwlock
id|vop_rwlock_t
id|vop_rwlock
suffix:semicolon
DECL|member|vop_rwunlock
id|vop_rwunlock_t
id|vop_rwunlock
suffix:semicolon
DECL|member|vop_bmap
id|vop_bmap_t
id|vop_bmap
suffix:semicolon
DECL|member|vop_reclaim
id|vop_reclaim_t
id|vop_reclaim
suffix:semicolon
DECL|member|vop_attr_get
id|vop_attr_get_t
id|vop_attr_get
suffix:semicolon
DECL|member|vop_attr_set
id|vop_attr_set_t
id|vop_attr_set
suffix:semicolon
DECL|member|vop_attr_remove
id|vop_attr_remove_t
id|vop_attr_remove
suffix:semicolon
DECL|member|vop_attr_list
id|vop_attr_list_t
id|vop_attr_list
suffix:semicolon
DECL|member|vop_link_removed
id|vop_link_removed_t
id|vop_link_removed
suffix:semicolon
DECL|member|vop_vnode_change
id|vop_vnode_change_t
id|vop_vnode_change
suffix:semicolon
DECL|member|vop_tosspages
id|vop_ptossvp_t
id|vop_tosspages
suffix:semicolon
DECL|member|vop_flushinval_pages
id|vop_pflushinvalvp_t
id|vop_flushinval_pages
suffix:semicolon
DECL|member|vop_flush_pages
id|vop_pflushvp_t
id|vop_flush_pages
suffix:semicolon
DECL|member|vop_release
id|vop_release_t
id|vop_release
suffix:semicolon
DECL|member|vop_iflush
id|vop_iflush_t
id|vop_iflush
suffix:semicolon
DECL|typedef|vnodeops_t
)brace
id|vnodeops_t
suffix:semicolon
multiline_comment|/*&n; * VOP&squot;s.&n; */
DECL|macro|_VOP_
mdefine_line|#define _VOP_(op, vp)&t;(*((vnodeops_t *)(vp)-&gt;v_fops)-&gt;op)
DECL|macro|VOP_READ
mdefine_line|#define VOP_READ(vp,file,iov,segs,offset,ioflags,cr,rv)&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_read, vp)((vp)-&gt;v_fbhv,file,iov,segs,offset,ioflags,cr)
DECL|macro|VOP_WRITE
mdefine_line|#define VOP_WRITE(vp,file,iov,segs,offset,ioflags,cr,rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_write, vp)((vp)-&gt;v_fbhv,file,iov,segs,offset,ioflags,cr)
DECL|macro|VOP_SENDFILE
mdefine_line|#define VOP_SENDFILE(vp,f,off,ioflags,cnt,act,targ,cr,rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_sendfile, vp)((vp)-&gt;v_fbhv,f,off,ioflags,cnt,act,targ,cr)
DECL|macro|VOP_BMAP
mdefine_line|#define VOP_BMAP(vp,of,sz,rw,b,n,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_bmap, vp)((vp)-&gt;v_fbhv,of,sz,rw,b,n)
DECL|macro|VOP_OPEN
mdefine_line|#define VOP_OPEN(vp, cr, rv)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_open, vp)((vp)-&gt;v_fbhv, cr)
DECL|macro|VOP_GETATTR
mdefine_line|#define VOP_GETATTR(vp, vap, f, cr, rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_getattr, vp)((vp)-&gt;v_fbhv, vap, f, cr)
DECL|macro|VOP_SETATTR
mdefine_line|#define&t;VOP_SETATTR(vp, vap, f, cr, rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_setattr, vp)((vp)-&gt;v_fbhv, vap, f, cr)
DECL|macro|VOP_ACCESS
mdefine_line|#define&t;VOP_ACCESS(vp, mode, cr, rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_access, vp)((vp)-&gt;v_fbhv, mode, cr)
DECL|macro|VOP_LOOKUP
mdefine_line|#define&t;VOP_LOOKUP(vp,d,vpp,f,rdir,cr,rv)&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_lookup, vp)((vp)-&gt;v_fbhv,d,vpp,f,rdir,cr)
DECL|macro|VOP_CREATE
mdefine_line|#define VOP_CREATE(dvp,d,vap,vpp,cr,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_create, dvp)((dvp)-&gt;v_fbhv,d,vap,vpp,cr)
DECL|macro|VOP_REMOVE
mdefine_line|#define VOP_REMOVE(dvp,d,cr,rv)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_remove, dvp)((dvp)-&gt;v_fbhv,d,cr)
DECL|macro|VOP_LINK
mdefine_line|#define&t;VOP_LINK(tdvp,fvp,d,cr,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_link, tdvp)((tdvp)-&gt;v_fbhv,fvp,d,cr)
DECL|macro|VOP_RENAME
mdefine_line|#define&t;VOP_RENAME(fvp,fnm,tdvp,tnm,cr,rv)&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_rename, fvp)((fvp)-&gt;v_fbhv,fnm,tdvp,tnm,cr)
DECL|macro|VOP_MKDIR
mdefine_line|#define&t;VOP_MKDIR(dp,d,vap,vpp,cr,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_mkdir, dp)((dp)-&gt;v_fbhv,d,vap,vpp,cr)
DECL|macro|VOP_RMDIR
mdefine_line|#define&t;VOP_RMDIR(dp,d,cr,rv)&t; &t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_rmdir, dp)((dp)-&gt;v_fbhv,d,cr)
DECL|macro|VOP_READDIR
mdefine_line|#define&t;VOP_READDIR(vp,uiop,cr,eofp,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_readdir, vp)((vp)-&gt;v_fbhv,uiop,cr,eofp)
DECL|macro|VOP_SYMLINK
mdefine_line|#define&t;VOP_SYMLINK(dvp,d,vap,tnm,vpp,cr,rv)&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_symlink, dvp) ((dvp)-&gt;v_fbhv,d,vap,tnm,vpp,cr)
DECL|macro|VOP_READLINK
mdefine_line|#define&t;VOP_READLINK(vp,uiop,fl,cr,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_readlink, vp)((vp)-&gt;v_fbhv,uiop,fl,cr)
DECL|macro|VOP_FSYNC
mdefine_line|#define&t;VOP_FSYNC(vp,f,cr,b,e,rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_fsync, vp)((vp)-&gt;v_fbhv,f,cr,b,e)
DECL|macro|VOP_INACTIVE
mdefine_line|#define VOP_INACTIVE(vp, cr, rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_inactive, vp)((vp)-&gt;v_fbhv, cr)
DECL|macro|VOP_RELEASE
mdefine_line|#define VOP_RELEASE(vp, rv)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_release, vp)((vp)-&gt;v_fbhv)
DECL|macro|VOP_FID2
mdefine_line|#define VOP_FID2(vp, fidp, rv)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_fid2, vp)((vp)-&gt;v_fbhv, fidp)
DECL|macro|VOP_RWLOCK
mdefine_line|#define VOP_RWLOCK(vp,i)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(void)_VOP_(vop_rwlock, vp)((vp)-&gt;v_fbhv, i)
DECL|macro|VOP_RWLOCK_TRY
mdefine_line|#define VOP_RWLOCK_TRY(vp,i)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_VOP_(vop_rwlock, vp)((vp)-&gt;v_fbhv, i)
DECL|macro|VOP_RWUNLOCK
mdefine_line|#define VOP_RWUNLOCK(vp,i)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(void)_VOP_(vop_rwunlock, vp)((vp)-&gt;v_fbhv, i)
DECL|macro|VOP_FRLOCK
mdefine_line|#define VOP_FRLOCK(vp,c,fl,flags,offset,fr,rv)&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_frlock, vp)((vp)-&gt;v_fbhv,c,fl,flags,offset,fr)
DECL|macro|VOP_RECLAIM
mdefine_line|#define VOP_RECLAIM(vp, rv)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_reclaim, vp)((vp)-&gt;v_fbhv)
DECL|macro|VOP_ATTR_GET
mdefine_line|#define VOP_ATTR_GET(vp, name, val, vallenp, fl, cred, rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_attr_get, vp)((vp)-&gt;v_fbhv,name,val,vallenp,fl,cred)
DECL|macro|VOP_ATTR_SET
mdefine_line|#define&t;VOP_ATTR_SET(vp, name, val, vallen, fl, cred, rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_attr_set, vp)((vp)-&gt;v_fbhv,name,val,vallen,fl,cred)
DECL|macro|VOP_ATTR_REMOVE
mdefine_line|#define&t;VOP_ATTR_REMOVE(vp, name, flags, cred, rv)&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_attr_remove, vp)((vp)-&gt;v_fbhv,name,flags,cred)
DECL|macro|VOP_ATTR_LIST
mdefine_line|#define&t;VOP_ATTR_LIST(vp, buf, buflen, fl, cursor, cred, rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_attr_list, vp)((vp)-&gt;v_fbhv,buf,buflen,fl,cursor,cred)
DECL|macro|VOP_LINK_REMOVED
mdefine_line|#define VOP_LINK_REMOVED(vp, dvp, linkzero)&t;&t;&t;&t;&bslash;&n;&t;(void)_VOP_(vop_link_removed, vp)((vp)-&gt;v_fbhv, dvp, linkzero)
DECL|macro|VOP_VNODE_CHANGE
mdefine_line|#define VOP_VNODE_CHANGE(vp, cmd, val)&t;&t;&t;&t;&t;&bslash;&n;&t;(void)_VOP_(vop_vnode_change, vp)((vp)-&gt;v_fbhv,cmd,val)
multiline_comment|/*&n; * These are page cache functions that now go thru VOPs.&n; * &squot;last&squot; parameter is unused and left in for IRIX compatibility&n; */
DECL|macro|VOP_TOSS_PAGES
mdefine_line|#define VOP_TOSS_PAGES(vp, first, last, fiopt)&t;&t;&t;&t;&bslash;&n;&t;_VOP_(vop_tosspages, vp)((vp)-&gt;v_fbhv,first, last, fiopt)
multiline_comment|/*&n; * &squot;last&squot; parameter is unused and left in for IRIX compatibility&n; */
DECL|macro|VOP_FLUSHINVAL_PAGES
mdefine_line|#define VOP_FLUSHINVAL_PAGES(vp, first, last, fiopt)&t;&t;&t;&bslash;&n;&t;_VOP_(vop_flushinval_pages, vp)((vp)-&gt;v_fbhv,first,last,fiopt)
multiline_comment|/*&n; * &squot;last&squot; parameter is unused and left in for IRIX compatibility&n; */
DECL|macro|VOP_FLUSH_PAGES
mdefine_line|#define VOP_FLUSH_PAGES(vp, first, last, flags, fiopt, rv)&t;&t;&bslash;&n;&t;rv = _VOP_(vop_flush_pages, vp)((vp)-&gt;v_fbhv,first,last,flags,fiopt)
DECL|macro|VOP_IOCTL
mdefine_line|#define VOP_IOCTL(vp, inode, filp, fl, cmd, arg, rv)&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_ioctl, vp)((vp)-&gt;v_fbhv,inode,filp,fl,cmd,arg)
DECL|macro|VOP_IFLUSH
mdefine_line|#define VOP_IFLUSH(vp, flags, rv)&t;&t;&t;&t;&t;&bslash;&n;&t;rv = _VOP_(vop_iflush, vp)((vp)-&gt;v_fbhv, flags)
multiline_comment|/*&n; * Flags for read/write calls - same values as IRIX&n; */
DECL|macro|IO_ISAIO
mdefine_line|#define IO_ISAIO&t;0x00001&t;&t;/* don&squot;t wait for completion */
DECL|macro|IO_ISDIRECT
mdefine_line|#define IO_ISDIRECT&t;0x00004&t;&t;/* bypass page cache */
DECL|macro|IO_INVIS
mdefine_line|#define IO_INVIS&t;0x00020&t;&t;/* don&squot;t update inode timestamps */
multiline_comment|/*&n; * Flags for VOP_IFLUSH call&n; */
DECL|macro|FLUSH_SYNC
mdefine_line|#define FLUSH_SYNC&t;&t;1&t;/* wait for flush to complete&t;*/
DECL|macro|FLUSH_INODE
mdefine_line|#define FLUSH_INODE&t;&t;2&t;/* flush the inode itself&t;*/
DECL|macro|FLUSH_LOG
mdefine_line|#define FLUSH_LOG&t;&t;4&t;/* force the last log entry for&n;&t;&t;&t;&t;&t; * this inode out to disk&t;*/
multiline_comment|/*&n; * Flush/Invalidate options for VOP_TOSS_PAGES, VOP_FLUSHINVAL_PAGES and&n; *&t;VOP_FLUSH_PAGES.&n; */
DECL|macro|FI_NONE
mdefine_line|#define FI_NONE&t;&t;&t;0&t;/* none */
DECL|macro|FI_REMAPF
mdefine_line|#define FI_REMAPF&t;&t;1&t;/* Do a remapf prior to the operation */
DECL|macro|FI_REMAPF_LOCKED
mdefine_line|#define FI_REMAPF_LOCKED&t;2&t;/* Do a remapf prior to the operation.&n;&t;&t;&t;&t;&t;   Prevent VM access to the pages until&n;&t;&t;&t;&t;&t;   the operation completes. */
multiline_comment|/*&n; * Vnode attributes.  va_mask indicates those attributes the caller&n; * wants to set or extract.&n; */
DECL|struct|vattr
r_typedef
r_struct
id|vattr
(brace
DECL|member|va_mask
r_int
id|va_mask
suffix:semicolon
multiline_comment|/* bit-mask of attributes present */
DECL|member|va_type
r_enum
id|vtype
id|va_type
suffix:semicolon
multiline_comment|/* vnode type (for create) */
DECL|member|va_mode
id|mode_t
id|va_mode
suffix:semicolon
multiline_comment|/* file access mode and type */
DECL|member|va_nlink
id|nlink_t
id|va_nlink
suffix:semicolon
multiline_comment|/* number of references to file */
DECL|member|va_uid
id|uid_t
id|va_uid
suffix:semicolon
multiline_comment|/* owner user id */
DECL|member|va_gid
id|gid_t
id|va_gid
suffix:semicolon
multiline_comment|/* owner group id */
DECL|member|va_nodeid
id|xfs_ino_t
id|va_nodeid
suffix:semicolon
multiline_comment|/* file id */
DECL|member|va_size
id|xfs_off_t
id|va_size
suffix:semicolon
multiline_comment|/* file size in bytes */
DECL|member|va_blocksize
id|u_long
id|va_blocksize
suffix:semicolon
multiline_comment|/* blocksize preferred for i/o */
DECL|member|va_atime
r_struct
id|timespec
id|va_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|va_mtime
r_struct
id|timespec
id|va_mtime
suffix:semicolon
multiline_comment|/* time of last modification */
DECL|member|va_ctime
r_struct
id|timespec
id|va_ctime
suffix:semicolon
multiline_comment|/* time file changed */
DECL|member|va_gen
id|u_int
id|va_gen
suffix:semicolon
multiline_comment|/* generation number of file */
DECL|member|va_rdev
id|xfs_dev_t
id|va_rdev
suffix:semicolon
multiline_comment|/* device the special file represents */
DECL|member|va_nblocks
id|__int64_t
id|va_nblocks
suffix:semicolon
multiline_comment|/* number of blocks allocated */
DECL|member|va_xflags
id|u_long
id|va_xflags
suffix:semicolon
multiline_comment|/* random extended file flags */
DECL|member|va_extsize
id|u_long
id|va_extsize
suffix:semicolon
multiline_comment|/* file extent size */
DECL|member|va_nextents
id|u_long
id|va_nextents
suffix:semicolon
multiline_comment|/* number of extents in file */
DECL|member|va_anextents
id|u_long
id|va_anextents
suffix:semicolon
multiline_comment|/* number of attr extents in file */
DECL|member|va_projid
r_int
id|va_projid
suffix:semicolon
multiline_comment|/* project id */
DECL|typedef|vattr_t
)brace
id|vattr_t
suffix:semicolon
multiline_comment|/*&n; * setattr or getattr attributes&n; */
DECL|macro|XFS_AT_TYPE
mdefine_line|#define XFS_AT_TYPE&t;&t;0x00000001
DECL|macro|XFS_AT_MODE
mdefine_line|#define XFS_AT_MODE&t;&t;0x00000002
DECL|macro|XFS_AT_UID
mdefine_line|#define XFS_AT_UID&t;&t;0x00000004
DECL|macro|XFS_AT_GID
mdefine_line|#define XFS_AT_GID&t;&t;0x00000008
DECL|macro|XFS_AT_FSID
mdefine_line|#define XFS_AT_FSID&t;&t;0x00000010
DECL|macro|XFS_AT_NODEID
mdefine_line|#define XFS_AT_NODEID&t;&t;0x00000020
DECL|macro|XFS_AT_NLINK
mdefine_line|#define XFS_AT_NLINK&t;&t;0x00000040
DECL|macro|XFS_AT_SIZE
mdefine_line|#define XFS_AT_SIZE&t;&t;0x00000080
DECL|macro|XFS_AT_ATIME
mdefine_line|#define XFS_AT_ATIME&t;&t;0x00000100
DECL|macro|XFS_AT_MTIME
mdefine_line|#define XFS_AT_MTIME&t;&t;0x00000200
DECL|macro|XFS_AT_CTIME
mdefine_line|#define XFS_AT_CTIME&t;&t;0x00000400
DECL|macro|XFS_AT_RDEV
mdefine_line|#define XFS_AT_RDEV&t;&t;0x00000800
DECL|macro|XFS_AT_BLKSIZE
mdefine_line|#define XFS_AT_BLKSIZE&t;&t;0x00001000
DECL|macro|XFS_AT_NBLOCKS
mdefine_line|#define XFS_AT_NBLOCKS&t;&t;0x00002000
DECL|macro|XFS_AT_VCODE
mdefine_line|#define XFS_AT_VCODE&t;&t;0x00004000
DECL|macro|XFS_AT_MAC
mdefine_line|#define XFS_AT_MAC&t;&t;0x00008000
DECL|macro|XFS_AT_UPDATIME
mdefine_line|#define XFS_AT_UPDATIME&t;&t;0x00010000
DECL|macro|XFS_AT_UPDMTIME
mdefine_line|#define XFS_AT_UPDMTIME&t;&t;0x00020000
DECL|macro|XFS_AT_UPDCTIME
mdefine_line|#define XFS_AT_UPDCTIME&t;&t;0x00040000
DECL|macro|XFS_AT_ACL
mdefine_line|#define XFS_AT_ACL&t;&t;0x00080000
DECL|macro|XFS_AT_CAP
mdefine_line|#define XFS_AT_CAP&t;&t;0x00100000
DECL|macro|XFS_AT_INF
mdefine_line|#define XFS_AT_INF&t;&t;0x00200000
DECL|macro|XFS_AT_XFLAGS
mdefine_line|#define XFS_AT_XFLAGS&t;&t;0x00400000
DECL|macro|XFS_AT_EXTSIZE
mdefine_line|#define XFS_AT_EXTSIZE&t;&t;0x00800000
DECL|macro|XFS_AT_NEXTENTS
mdefine_line|#define XFS_AT_NEXTENTS&t;&t;0x01000000
DECL|macro|XFS_AT_ANEXTENTS
mdefine_line|#define XFS_AT_ANEXTENTS&t;0x02000000
DECL|macro|XFS_AT_PROJID
mdefine_line|#define XFS_AT_PROJID&t;&t;0x04000000
DECL|macro|XFS_AT_SIZE_NOPERM
mdefine_line|#define XFS_AT_SIZE_NOPERM&t;0x08000000
DECL|macro|XFS_AT_GENCOUNT
mdefine_line|#define XFS_AT_GENCOUNT&t;&t;0x10000000
DECL|macro|XFS_AT_ALL
mdefine_line|#define XFS_AT_ALL&t;(XFS_AT_TYPE|XFS_AT_MODE|XFS_AT_UID|XFS_AT_GID|&bslash;&n;&t;&t;XFS_AT_FSID|XFS_AT_NODEID|XFS_AT_NLINK|XFS_AT_SIZE|&bslash;&n;&t;&t;XFS_AT_ATIME|XFS_AT_MTIME|XFS_AT_CTIME|XFS_AT_RDEV|&bslash;&n;&t;&t;XFS_AT_BLKSIZE|XFS_AT_NBLOCKS|XFS_AT_VCODE|XFS_AT_MAC|&bslash;&n;&t;&t;XFS_AT_ACL|XFS_AT_CAP|XFS_AT_INF|XFS_AT_XFLAGS|XFS_AT_EXTSIZE|&bslash;&n;&t;&t;XFS_AT_NEXTENTS|XFS_AT_ANEXTENTS|XFS_AT_PROJID|XFS_AT_GENCOUNT)
DECL|macro|XFS_AT_STAT
mdefine_line|#define XFS_AT_STAT&t;(XFS_AT_TYPE|XFS_AT_MODE|XFS_AT_UID|XFS_AT_GID|&bslash;&n;&t;&t;XFS_AT_FSID|XFS_AT_NODEID|XFS_AT_NLINK|XFS_AT_SIZE|&bslash;&n;&t;&t;XFS_AT_ATIME|XFS_AT_MTIME|XFS_AT_CTIME|XFS_AT_RDEV|&bslash;&n;&t;&t;XFS_AT_BLKSIZE|XFS_AT_NBLOCKS|XFS_AT_PROJID)
DECL|macro|XFS_AT_TIMES
mdefine_line|#define XFS_AT_TIMES&t;(XFS_AT_ATIME|XFS_AT_MTIME|XFS_AT_CTIME)
DECL|macro|XFS_AT_UPDTIMES
mdefine_line|#define XFS_AT_UPDTIMES&t;(XFS_AT_UPDATIME|XFS_AT_UPDMTIME|XFS_AT_UPDCTIME)
DECL|macro|XFS_AT_NOSET
mdefine_line|#define XFS_AT_NOSET&t;(XFS_AT_NLINK|XFS_AT_RDEV|XFS_AT_FSID|XFS_AT_NODEID|&bslash;&n;&t;&t;XFS_AT_TYPE|XFS_AT_BLKSIZE|XFS_AT_NBLOCKS|XFS_AT_VCODE|&bslash;&n;&t;&t;XFS_AT_NEXTENTS|XFS_AT_ANEXTENTS|XFS_AT_GENCOUNT)
multiline_comment|/*&n; *  Modes.&n; */
DECL|macro|VSUID
mdefine_line|#define VSUID&t;S_ISUID&t;&t;/* set user id on execution */
DECL|macro|VSGID
mdefine_line|#define VSGID&t;S_ISGID&t;&t;/* set group id on execution */
DECL|macro|VSVTX
mdefine_line|#define VSVTX&t;S_ISVTX&t;&t;/* save swapped text even after use */
DECL|macro|VREAD
mdefine_line|#define VREAD&t;S_IRUSR&t;&t;/* read, write, execute permissions */
DECL|macro|VWRITE
mdefine_line|#define VWRITE&t;S_IWUSR
DECL|macro|VEXEC
mdefine_line|#define VEXEC&t;S_IXUSR
DECL|macro|MODEMASK
mdefine_line|#define MODEMASK S_IALLUGO&t;/* mode bits plus permission bits */
multiline_comment|/*&n; * Check whether mandatory file locking is enabled.&n; */
DECL|macro|MANDLOCK
mdefine_line|#define MANDLOCK(vp, mode)&t;&bslash;&n;&t;((vp)-&gt;v_type == VREG &amp;&amp; ((mode) &amp; (VSGID|(VEXEC&gt;&gt;3))) == VSGID)
r_extern
r_void
id|vn_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|vn_wait
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
id|vnode_t
op_star
id|vn_initialize
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Acquiring and invalidating vnodes:&n; *&n; *&t;if (vn_get(vp, version, 0))&n; *&t;&t;...;&n; *&t;vn_purge(vp, version);&n; *&n; * vn_get and vn_purge must be called with vmap_t arguments, sampled&n; * while a lock that the vnode&squot;s VOP_RECLAIM function acquires is&n; * held, to ensure that the vnode sampled with the lock held isn&squot;t&n; * recycled (VOP_RECLAIMed) or deallocated between the release of the lock&n; * and the subsequent vn_get or vn_purge.&n; */
multiline_comment|/*&n; * vnode_map structures _must_ match vn_epoch and vnode structure sizes.&n; */
DECL|struct|vnode_map
r_typedef
r_struct
id|vnode_map
(brace
DECL|member|v_vfsp
id|vfs_t
op_star
id|v_vfsp
suffix:semicolon
DECL|member|v_number
id|vnumber_t
id|v_number
suffix:semicolon
multiline_comment|/* in-core vnode number */
DECL|member|v_ino
id|xfs_ino_t
id|v_ino
suffix:semicolon
multiline_comment|/* inode #&t;*/
DECL|typedef|vmap_t
)brace
id|vmap_t
suffix:semicolon
DECL|macro|VMAP
mdefine_line|#define VMAP(vp, vmap)&t;{(vmap).v_vfsp&t; = (vp)-&gt;v_vfsp,&t;&bslash;&n;&t;&t;&t; (vmap).v_number = (vp)-&gt;v_number,&t;&bslash;&n;&t;&t;&t; (vmap).v_ino&t; = (vp)-&gt;v_inode.i_ino; }
r_extern
r_void
id|vn_purge
c_func
(paren
r_struct
id|vnode
op_star
comma
id|vmap_t
op_star
)paren
suffix:semicolon
r_extern
id|vnode_t
op_star
id|vn_get
c_func
(paren
r_struct
id|vnode
op_star
comma
id|vmap_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|vn_revalidate
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_revalidate_core
c_func
(paren
r_struct
id|vnode
op_star
comma
id|vattr_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_remove
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
DECL|function|vn_count
r_static
r_inline
r_int
id|vn_count
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
op_member_access_from_pointer
id|i_count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Vnode reference counting functions (and macros for compatibility).&n; */
r_extern
id|vnode_t
op_star
id|vn_hold
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_rele
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
macro_line|#if defined(XFS_VNODE_TRACE)
DECL|macro|VN_HOLD
mdefine_line|#define VN_HOLD(vp)&t;&t;&bslash;&n;&t;((void)vn_hold(vp),&t;&bslash;&n;&t;  vn_trace_hold(vp, __FILE__, __LINE__, (inst_t *)__return_address))
DECL|macro|VN_RELE
mdefine_line|#define VN_RELE(vp)&t;&t;&bslash;&n;&t;  (vn_trace_rele(vp, __FILE__, __LINE__, (inst_t *)__return_address), &bslash;&n;&t;   iput(LINVFS_GET_IP(vp)))
macro_line|#else
DECL|macro|VN_HOLD
mdefine_line|#define VN_HOLD(vp)&t;&t;((void)vn_hold(vp))
DECL|macro|VN_RELE
mdefine_line|#define VN_RELE(vp)&t;&t;(iput(LINVFS_GET_IP(vp)))
macro_line|#endif
multiline_comment|/*&n; * Vname handling macros.&n; */
DECL|macro|VNAME
mdefine_line|#define VNAME(dentry)&t;&t;((char *) (dentry)-&gt;d_name.name)
DECL|macro|VNAMELEN
mdefine_line|#define VNAMELEN(dentry)&t;((dentry)-&gt;d_name.len)
DECL|macro|VNAME_TO_VNODE
mdefine_line|#define VNAME_TO_VNODE(dentry)&t;(LINVFS_GET_VP((dentry)-&gt;d_inode))
multiline_comment|/*&n; * Vnode spinlock manipulation.&n; */
DECL|macro|VN_LOCK
mdefine_line|#define VN_LOCK(vp)&t;&t;mutex_spinlock(&amp;(vp)-&gt;v_lock)
DECL|macro|VN_UNLOCK
mdefine_line|#define VN_UNLOCK(vp, s)&t;mutex_spinunlock(&amp;(vp)-&gt;v_lock, s)
DECL|macro|VN_FLAGSET
mdefine_line|#define VN_FLAGSET(vp,b)&t;vn_flagset(vp,b)
DECL|macro|VN_FLAGCLR
mdefine_line|#define VN_FLAGCLR(vp,b)&t;vn_flagclr(vp,b)
DECL|function|vn_flagset
r_static
id|__inline__
r_void
id|vn_flagset
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
id|uint
id|flag
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|vp-&gt;v_lock
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_or_assign
id|flag
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vp-&gt;v_lock
)paren
suffix:semicolon
)brace
DECL|function|vn_flagclr
r_static
id|__inline__
r_void
id|vn_flagclr
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
id|uint
id|flag
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|vp-&gt;v_lock
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_and_assign
op_complement
id|flag
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vp-&gt;v_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Update modify/access/change times on the vnode&n; */
DECL|macro|VN_MTIMESET
mdefine_line|#define VN_MTIMESET(vp, tvp)&t;(LINVFS_GET_IP(vp)-&gt;i_mtime = *(tvp))
DECL|macro|VN_ATIMESET
mdefine_line|#define VN_ATIMESET(vp, tvp)&t;(LINVFS_GET_IP(vp)-&gt;i_atime = *(tvp))
DECL|macro|VN_CTIMESET
mdefine_line|#define VN_CTIMESET(vp, tvp)&t;(LINVFS_GET_IP(vp)-&gt;i_ctime = *(tvp))
multiline_comment|/*&n; * Dealing with bad inodes&n; */
DECL|function|vn_mark_bad
r_static
r_inline
r_void
id|vn_mark_bad
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
id|make_bad_inode
c_func
(paren
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
)brace
DECL|function|VN_BAD
r_static
r_inline
r_int
id|VN_BAD
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_return
id|is_bad_inode
c_func
(paren
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Some useful predicates.&n; */
DECL|macro|VN_MAPPED
mdefine_line|#define VN_MAPPED(vp)&t;mapping_mapped(LINVFS_GET_IP(vp)-&gt;i_mapping)
DECL|macro|VN_CACHED
mdefine_line|#define VN_CACHED(vp)&t;(LINVFS_GET_IP(vp)-&gt;i_mapping-&gt;nrpages)
DECL|macro|VN_DIRTY
mdefine_line|#define VN_DIRTY(vp)&t;mapping_tagged(LINVFS_GET_IP(vp)-&gt;i_mapping, &bslash;&n;&t;&t;&t;&t;&t;PAGECACHE_TAG_DIRTY)
DECL|macro|VMODIFY
mdefine_line|#define VMODIFY(vp)&t;VN_FLAGSET(vp, VMODIFIED)
DECL|macro|VUNMODIFY
mdefine_line|#define VUNMODIFY(vp)&t;VN_FLAGCLR(vp, VMODIFIED)
multiline_comment|/*&n; * Flags to VOP_SETATTR/VOP_GETATTR.&n; */
DECL|macro|ATTR_UTIME
mdefine_line|#define&t;ATTR_UTIME&t;0x01&t;/* non-default utime(2) request */
DECL|macro|ATTR_DMI
mdefine_line|#define&t;ATTR_DMI&t;0x08&t;/* invocation from a DMI function */
DECL|macro|ATTR_LAZY
mdefine_line|#define&t;ATTR_LAZY&t;0x80&t;/* set/get attributes lazily */
DECL|macro|ATTR_NONBLOCK
mdefine_line|#define&t;ATTR_NONBLOCK&t;0x100&t;/* return EAGAIN if operation would block */
multiline_comment|/*&n; * Flags to VOP_FSYNC and VOP_RECLAIM.&n; */
DECL|macro|FSYNC_NOWAIT
mdefine_line|#define FSYNC_NOWAIT&t;0&t;/* asynchronous flush */
DECL|macro|FSYNC_WAIT
mdefine_line|#define FSYNC_WAIT&t;0x1&t;/* synchronous fsync or forced reclaim */
DECL|macro|FSYNC_INVAL
mdefine_line|#define FSYNC_INVAL&t;0x2&t;/* flush and invalidate cached data */
DECL|macro|FSYNC_DATA
mdefine_line|#define FSYNC_DATA&t;0x4&t;/* synchronous fsync of data only */
multiline_comment|/*&n; * Tracking vnode activity.&n; */
macro_line|#if defined(XFS_VNODE_TRACE)
DECL|macro|VNODE_TRACE_SIZE
mdefine_line|#define&t;VNODE_TRACE_SIZE&t;16&t;&t;/* number of trace entries */
DECL|macro|VNODE_KTRACE_ENTRY
mdefine_line|#define&t;VNODE_KTRACE_ENTRY&t;1
DECL|macro|VNODE_KTRACE_EXIT
mdefine_line|#define&t;VNODE_KTRACE_EXIT&t;2
DECL|macro|VNODE_KTRACE_HOLD
mdefine_line|#define&t;VNODE_KTRACE_HOLD&t;3
DECL|macro|VNODE_KTRACE_REF
mdefine_line|#define&t;VNODE_KTRACE_REF&t;4
DECL|macro|VNODE_KTRACE_RELE
mdefine_line|#define&t;VNODE_KTRACE_RELE&t;5
r_extern
r_void
id|vn_trace_entry
c_func
(paren
r_struct
id|vnode
op_star
comma
r_char
op_star
comma
id|inst_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_trace_exit
c_func
(paren
r_struct
id|vnode
op_star
comma
r_char
op_star
comma
id|inst_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_trace_hold
c_func
(paren
r_struct
id|vnode
op_star
comma
r_char
op_star
comma
r_int
comma
id|inst_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_trace_ref
c_func
(paren
r_struct
id|vnode
op_star
comma
r_char
op_star
comma
r_int
comma
id|inst_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vn_trace_rele
c_func
(paren
r_struct
id|vnode
op_star
comma
r_char
op_star
comma
r_int
comma
id|inst_t
op_star
)paren
suffix:semicolon
DECL|macro|VN_TRACE
mdefine_line|#define&t;VN_TRACE(vp)&t;&t;&bslash;&n;&t;vn_trace_ref(vp, __FILE__, __LINE__, (inst_t *)__return_address)
macro_line|#else
DECL|macro|vn_trace_entry
mdefine_line|#define&t;vn_trace_entry(a,b,c)
DECL|macro|vn_trace_exit
mdefine_line|#define&t;vn_trace_exit(a,b,c)
DECL|macro|vn_trace_hold
mdefine_line|#define&t;vn_trace_hold(a,b,c,d)
DECL|macro|vn_trace_ref
mdefine_line|#define&t;vn_trace_ref(a,b,c,d)
DECL|macro|vn_trace_rele
mdefine_line|#define&t;vn_trace_rele(a,b,c,d)
DECL|macro|VN_TRACE
mdefine_line|#define&t;VN_TRACE(vp)
macro_line|#endif
macro_line|#endif&t;/* __XFS_VNODE_H__ */
eof
