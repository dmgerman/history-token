multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_VFS_H__
DECL|macro|__XFS_VFS_H__
mdefine_line|#define __XFS_VFS_H__
macro_line|#include &lt;linux/vfs.h&gt;
r_struct
id|statfs
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|cred
suffix:semicolon
r_struct
id|super_block
suffix:semicolon
r_struct
id|fid
suffix:semicolon
r_struct
id|dm_fcntl_vector
suffix:semicolon
r_struct
id|xfs_mount_args
suffix:semicolon
DECL|struct|vfs
r_typedef
r_struct
id|vfs
(brace
DECL|member|vfs_flag
id|u_int
id|vfs_flag
suffix:semicolon
multiline_comment|/* flags */
DECL|member|vfs_fsid
id|fsid_t
id|vfs_fsid
suffix:semicolon
multiline_comment|/* file system id */
DECL|member|vfs_altfsid
id|fsid_t
op_star
id|vfs_altfsid
suffix:semicolon
multiline_comment|/* An ID fixed for life of FS */
DECL|member|vfs_bh
id|bhv_head_t
id|vfs_bh
suffix:semicolon
multiline_comment|/* head of vfs behavior chain */
DECL|member|vfs_super
r_struct
id|super_block
op_star
id|vfs_super
suffix:semicolon
multiline_comment|/* pointer to super block structure */
DECL|typedef|vfs_t
)brace
id|vfs_t
suffix:semicolon
DECL|macro|vfs_fbhv
mdefine_line|#define vfs_fbhv&t;vfs_bh.bh_first&t;&t;/* 1st on vfs behavior chain */
DECL|macro|VFS_FOPS
mdefine_line|#define VFS_FOPS(vfsp)&t;&bslash;&n;&t;((vfsops_t *)((vfsp)-&gt;vfs_fbhv-&gt;bd_ops))/* ops for 1st behavior */
DECL|macro|bhvtovfs
mdefine_line|#define bhvtovfs(bdp)&t;((struct vfs *)BHV_VOBJ(bdp))
DECL|macro|VFS_BHVHEAD
mdefine_line|#define VFS_BHVHEAD(vfsp) (&amp;(vfsp)-&gt;vfs_bh)
DECL|macro|VFS_RDONLY
mdefine_line|#define VFS_RDONLY&t;0x0001&t;&t;/* read-only vfs */
DECL|macro|VFS_GRPID
mdefine_line|#define VFS_GRPID&t;0x0002&t;&t;/* group-ID assigned from directory */
DECL|macro|VFS_DMI
mdefine_line|#define VFS_DMI&t;&t;0x0004&t;&t;/* filesystem has the DMI enabled */
DECL|macro|SYNC_ATTR
mdefine_line|#define SYNC_ATTR&t;0x0001&t;&t;/* sync attributes */
DECL|macro|SYNC_CLOSE
mdefine_line|#define SYNC_CLOSE&t;0x0002&t;&t;/* close file system down */
DECL|macro|SYNC_DELWRI
mdefine_line|#define SYNC_DELWRI&t;0x0004&t;&t;/* look at delayed writes */
DECL|macro|SYNC_WAIT
mdefine_line|#define SYNC_WAIT&t;0x0008&t;&t;/* wait for i/o to complete */
DECL|macro|SYNC_FSDATA
mdefine_line|#define SYNC_FSDATA&t;0x0020&t;&t;/* flush fs data (e.g. superblocks) */
DECL|macro|SYNC_BDFLUSH
mdefine_line|#define SYNC_BDFLUSH&t;0x0010&t;&t;/* BDFLUSH is calling -- don&squot;t block */
DECL|struct|vfsops
r_typedef
r_struct
id|vfsops
(brace
DECL|member|vfs_mount
r_int
(paren
op_star
id|vfs_mount
)paren
(paren
r_struct
id|vfs
op_star
comma
r_struct
id|xfs_mount_args
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
multiline_comment|/* mount file system */
DECL|member|vfs_unmount
r_int
(paren
op_star
id|vfs_unmount
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
multiline_comment|/* unmount file system */
DECL|member|vfs_root
r_int
(paren
op_star
id|vfs_root
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|vnode
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* get root vnode */
DECL|member|vfs_statvfs
r_int
(paren
op_star
id|vfs_statvfs
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|statfs
op_star
comma
r_struct
id|vnode
op_star
)paren
suffix:semicolon
multiline_comment|/* get file system statistics */
DECL|member|vfs_sync
r_int
(paren
op_star
id|vfs_sync
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
multiline_comment|/* flush files */
DECL|member|vfs_vget
r_int
(paren
op_star
id|vfs_vget
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|vnode
op_star
op_star
comma
r_struct
id|fid
op_star
)paren
suffix:semicolon
multiline_comment|/* get vnode from fid */
DECL|member|vfs_dmapi_mount
r_int
(paren
op_star
id|vfs_dmapi_mount
)paren
(paren
r_struct
id|vfs
op_star
comma
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* send dmapi mount event */
DECL|member|vfs_dmapi_fsys_vector
r_int
(paren
op_star
id|vfs_dmapi_fsys_vector
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|dm_fcntl_vector
op_star
)paren
suffix:semicolon
DECL|member|vfs_init_vnode
r_void
(paren
op_star
id|vfs_init_vnode
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|vnode
op_star
comma
id|bhv_desc_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|vfs_force_shutdown
r_void
(paren
op_star
id|vfs_force_shutdown
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vfsops_t
)brace
id|vfsops_t
suffix:semicolon
DECL|macro|VFS_UNMOUNT
mdefine_line|#define VFS_UNMOUNT(vfsp,f,cr, rv)&t;&bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_unmount))((vfsp)-&gt;vfs_fbhv, f, cr);&t;&t;&bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFS_ROOT
mdefine_line|#define VFS_ROOT(vfsp, vpp, rv)&t;&t;&bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_root))((vfsp)-&gt;vfs_fbhv, vpp);&t;&bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFS_STATVFS
mdefine_line|#define VFS_STATVFS(vfsp, sp, vp, rv)&t;&bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_statvfs))((vfsp)-&gt;vfs_fbhv, sp, vp);&t;&bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFS_SYNC
mdefine_line|#define VFS_SYNC(vfsp, flag, cr, rv) &bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_sync))((vfsp)-&gt;vfs_fbhv, flag, cr); &bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFS_VGET
mdefine_line|#define VFS_VGET(vfsp, vpp, fidp, rv) &bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_vget))((vfsp)-&gt;vfs_fbhv, vpp, fidp);  &bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFS_INIT_VNODE
mdefine_line|#define VFS_INIT_VNODE(vfsp, vp, bhv, unlock) &bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;(*(VFS_FOPS(vfsp)-&gt;vfs_init_vnode))((vfsp)-&gt;vfs_fbhv, vp, bhv, unlock);&bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
multiline_comment|/* No behavior lock here */
DECL|macro|VFS_FORCE_SHUTDOWN
mdefine_line|#define VFS_FORCE_SHUTDOWN(vfsp, flags) &bslash;&n;&t;(*(VFS_FOPS(vfsp)-&gt;vfs_force_shutdown))((vfsp)-&gt;vfs_fbhv, flags, __FILE__, __LINE__);
DECL|macro|VFS_DMAPI_FSYS_VECTOR
mdefine_line|#define VFS_DMAPI_FSYS_VECTOR(vfsp, df, rv) &bslash;&n;{&t;&bslash;&n;&t;BHV_READ_LOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;&t;rv = (*(VFS_FOPS(vfsp)-&gt;vfs_dmapi_fsys_vector))((vfsp)-&gt;vfs_fbhv, df);&t;      &bslash;&n;&t;BHV_READ_UNLOCK(&amp;(vfsp)-&gt;vfs_bh); &bslash;&n;}
DECL|macro|VFSOPS_DMAPI_MOUNT
mdefine_line|#define VFSOPS_DMAPI_MOUNT(vfs_op, vfsp, dir_name, fsname, rv) &bslash;&n;&t;rv = (*(vfs_op)-&gt;vfs_dmapi_mount)(vfsp, dir_name, fsname)
DECL|macro|VFSOPS_MOUNT
mdefine_line|#define VFSOPS_MOUNT(vfs_op, vfsp, args, cr, rv) &bslash;&n;&t;rv = (*(vfs_op)-&gt;vfs_mount)(vfsp, args, cr)
DECL|macro|VFS_REMOVEBHV
mdefine_line|#define VFS_REMOVEBHV(vfsp, bdp)&bslash;&n;{&t;&bslash;&n;&t;bhv_remove(VFS_BHVHEAD(vfsp), bdp); &bslash;&n;}
DECL|macro|PVFS_UNMOUNT
mdefine_line|#define PVFS_UNMOUNT(bdp,f,cr, rv)&t;&bslash;&n;{&t;&bslash;&n;&t;rv = (*((vfsops_t *)(bdp)-&gt;bd_ops)-&gt;vfs_unmount)(bdp, f, cr);&t;&bslash;&n;}
DECL|macro|PVFS_SYNC
mdefine_line|#define PVFS_SYNC(bdp, flag, cr, rv) &bslash;&n;{&t;&bslash;&n;&t;rv = (*((vfsops_t *)(bdp)-&gt;bd_ops)-&gt;vfs_sync)(bdp, flag, cr);&t;&bslash;&n;}
r_static
id|__inline
id|vfs_t
op_star
DECL|function|vfs_allocate
id|vfs_allocate
c_func
(paren
r_void
)paren
(brace
id|vfs_t
op_star
id|vfsp
suffix:semicolon
id|vfsp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|vfs_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfsp
)paren
(brace
id|memset
c_func
(paren
id|vfsp
comma
l_int|0
comma
r_sizeof
(paren
id|vfs_t
)paren
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
)brace
r_return
(paren
id|vfsp
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|vfs_deallocate
id|vfs_deallocate
c_func
(paren
id|vfs_t
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
id|kfree
c_func
(paren
id|vfsp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by fs dependent VFS_MOUNT code to link the VFS base file system&n; * dependent behavior with the VFS virtual object.&n; */
r_static
id|__inline
r_void
DECL|function|vfs_insertbhv
id|vfs_insertbhv
c_func
(paren
id|vfs_t
op_star
id|vfsp
comma
id|bhv_desc_t
op_star
id|bdp
comma
id|vfsops_t
op_star
id|vfsops
comma
r_void
op_star
id|mount
)paren
(brace
multiline_comment|/*&n;&t; * Initialize behavior desc with ops and data and then&n;&t; * attach it to the vfs.&n;&t; */
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
macro_line|#endif&t;/* __XFS_VFS_H__ */
eof
