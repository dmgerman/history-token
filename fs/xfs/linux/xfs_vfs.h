multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_VFS_H__
DECL|macro|__XFS_VFS_H__
mdefine_line|#define __XFS_VFS_H__
macro_line|#include &lt;linux/vfs.h&gt;
r_struct
id|fid
suffix:semicolon
r_struct
id|cred
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|kstatfs
suffix:semicolon
r_struct
id|seq_file
suffix:semicolon
r_struct
id|super_block
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
multiline_comment|/* file system ID */
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
multiline_comment|/* Linux superblock structure */
DECL|member|vfs_sync_task
r_struct
id|task_struct
op_star
id|vfs_sync_task
suffix:semicolon
DECL|member|vfs_wait_sync_task
id|wait_queue_head_t
id|vfs_wait_sync_task
suffix:semicolon
DECL|typedef|vfs_t
)brace
id|vfs_t
suffix:semicolon
DECL|macro|vfs_fbhv
mdefine_line|#define vfs_fbhv&t;&t;vfs_bh.bh_first&t;/* 1st on vfs behavior chain */
DECL|macro|bhvtovfs
mdefine_line|#define bhvtovfs(bdp)&t;&t;( (struct vfs *)BHV_VOBJ(bdp) )
DECL|macro|bhvtovfsops
mdefine_line|#define bhvtovfsops(bdp)&t;( (struct vfsops *)BHV_OPS(bdp) )
DECL|macro|VFS_BHVHEAD
mdefine_line|#define VFS_BHVHEAD(vfs)&t;( &amp;(vfs)-&gt;vfs_bh )
DECL|macro|VFS_REMOVEBHV
mdefine_line|#define VFS_REMOVEBHV(vfs, bdp)&t;( bhv_remove(VFS_BHVHEAD(vfs), bdp) )
DECL|macro|VFS_POSITION_BASE
mdefine_line|#define VFS_POSITION_BASE&t;BHV_POSITION_BASE&t;/* chain bottom */
DECL|macro|VFS_POSITION_TOP
mdefine_line|#define VFS_POSITION_TOP&t;BHV_POSITION_TOP&t;/* chain top */
DECL|macro|VFS_POSITION_INVALID
mdefine_line|#define VFS_POSITION_INVALID&t;BHV_POSITION_INVALID&t;/* invalid pos. num */
r_typedef
r_enum
(brace
DECL|enumerator|VFS_BHV_UNKNOWN
id|VFS_BHV_UNKNOWN
comma
multiline_comment|/* not specified */
DECL|enumerator|VFS_BHV_XFS
id|VFS_BHV_XFS
comma
multiline_comment|/* xfs */
DECL|enumerator|VFS_BHV_DM
id|VFS_BHV_DM
comma
multiline_comment|/* data migration */
DECL|enumerator|VFS_BHV_QM
id|VFS_BHV_QM
comma
multiline_comment|/* quota manager */
DECL|enumerator|VFS_BHV_IO
id|VFS_BHV_IO
comma
multiline_comment|/* IO path */
DECL|enumerator|VFS_BHV_END
id|VFS_BHV_END
multiline_comment|/* housekeeping end-of-range */
DECL|typedef|vfs_bhv_t
)brace
id|vfs_bhv_t
suffix:semicolon
DECL|macro|VFS_POSITION_XFS
mdefine_line|#define VFS_POSITION_XFS&t;(BHV_POSITION_BASE)
DECL|macro|VFS_POSITION_DM
mdefine_line|#define VFS_POSITION_DM&t;&t;(VFS_POSITION_BASE+10)
DECL|macro|VFS_POSITION_QM
mdefine_line|#define VFS_POSITION_QM&t;&t;(VFS_POSITION_BASE+20)
DECL|macro|VFS_POSITION_IO
mdefine_line|#define VFS_POSITION_IO&t;&t;(VFS_POSITION_BASE+30)
DECL|macro|VFS_RDONLY
mdefine_line|#define VFS_RDONLY&t;&t;0x0001&t;/* read-only vfs */
DECL|macro|VFS_GRPID
mdefine_line|#define VFS_GRPID&t;&t;0x0002&t;/* group-ID assigned from directory */
DECL|macro|VFS_DMI
mdefine_line|#define VFS_DMI&t;&t;&t;0x0004&t;/* filesystem has the DMI enabled */
DECL|macro|VFS_UMOUNT
mdefine_line|#define VFS_UMOUNT&t;&t;0x0008&t;/* unmount in progress */
DECL|macro|VFS_END
mdefine_line|#define VFS_END&t;&t;&t;0x0008&t;/* max flag */
DECL|macro|SYNC_ATTR
mdefine_line|#define SYNC_ATTR&t;&t;0x0001&t;/* sync attributes */
DECL|macro|SYNC_CLOSE
mdefine_line|#define SYNC_CLOSE&t;&t;0x0002&t;/* close file system down */
DECL|macro|SYNC_DELWRI
mdefine_line|#define SYNC_DELWRI&t;&t;0x0004&t;/* look at delayed writes */
DECL|macro|SYNC_WAIT
mdefine_line|#define SYNC_WAIT&t;&t;0x0008&t;/* wait for i/o to complete */
DECL|macro|SYNC_FSDATA
mdefine_line|#define SYNC_FSDATA&t;&t;0x0020&t;/* flush fs data (e.g. superblocks) */
DECL|macro|SYNC_BDFLUSH
mdefine_line|#define SYNC_BDFLUSH&t;&t;0x0010&t;/* BDFLUSH is calling -- don&squot;t block */
DECL|typedef|vfs_mount_t
r_typedef
r_int
(paren
op_star
id|vfs_mount_t
)paren
(paren
id|bhv_desc_t
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
DECL|typedef|vfs_parseargs_t
r_typedef
r_int
(paren
op_star
id|vfs_parseargs_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_struct
id|xfs_mount_args
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|vfs_showargs_t
r_typedef
r_int
(paren
op_star
id|vfs_showargs_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
DECL|typedef|vfs_unmount_t
r_typedef
r_int
(paren
op_star
id|vfs_unmount_t
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
DECL|typedef|vfs_mntupdate_t
r_typedef
r_int
(paren
op_star
id|vfs_mntupdate_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
op_star
comma
r_struct
id|xfs_mount_args
op_star
)paren
suffix:semicolon
DECL|typedef|vfs_root_t
r_typedef
r_int
(paren
op_star
id|vfs_root_t
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
DECL|typedef|vfs_statvfs_t
r_typedef
r_int
(paren
op_star
id|vfs_statvfs_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|kstatfs
op_star
comma
r_struct
id|vnode
op_star
)paren
suffix:semicolon
DECL|typedef|vfs_sync_t
r_typedef
r_int
(paren
op_star
id|vfs_sync_t
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
DECL|typedef|vfs_vget_t
r_typedef
r_int
(paren
op_star
id|vfs_vget_t
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
DECL|typedef|vfs_dmapiops_t
r_typedef
r_int
(paren
op_star
id|vfs_dmapiops_t
)paren
(paren
id|bhv_desc_t
op_star
comma
id|caddr_t
)paren
suffix:semicolon
DECL|typedef|vfs_quotactl_t
r_typedef
r_int
(paren
op_star
id|vfs_quotactl_t
)paren
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_int
comma
id|caddr_t
)paren
suffix:semicolon
DECL|typedef|vfs_init_vnode_t
r_typedef
r_void
(paren
op_star
id|vfs_init_vnode_t
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
DECL|typedef|vfs_force_shutdown_t
r_typedef
r_void
(paren
op_star
id|vfs_force_shutdown_t
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
DECL|struct|vfsops
r_typedef
r_struct
id|vfsops
(brace
DECL|member|vf_position
id|bhv_position_t
id|vf_position
suffix:semicolon
multiline_comment|/* behavior chain position */
DECL|member|vfs_mount
id|vfs_mount_t
id|vfs_mount
suffix:semicolon
multiline_comment|/* mount file system */
DECL|member|vfs_parseargs
id|vfs_parseargs_t
id|vfs_parseargs
suffix:semicolon
multiline_comment|/* parse mount options */
DECL|member|vfs_showargs
id|vfs_showargs_t
id|vfs_showargs
suffix:semicolon
multiline_comment|/* unparse mount options */
DECL|member|vfs_unmount
id|vfs_unmount_t
id|vfs_unmount
suffix:semicolon
multiline_comment|/* unmount file system */
DECL|member|vfs_mntupdate
id|vfs_mntupdate_t
id|vfs_mntupdate
suffix:semicolon
multiline_comment|/* update file system options */
DECL|member|vfs_root
id|vfs_root_t
id|vfs_root
suffix:semicolon
multiline_comment|/* get root vnode */
DECL|member|vfs_statvfs
id|vfs_statvfs_t
id|vfs_statvfs
suffix:semicolon
multiline_comment|/* file system statistics */
DECL|member|vfs_sync
id|vfs_sync_t
id|vfs_sync
suffix:semicolon
multiline_comment|/* flush files */
DECL|member|vfs_vget
id|vfs_vget_t
id|vfs_vget
suffix:semicolon
multiline_comment|/* get vnode from fid */
DECL|member|vfs_dmapiops
id|vfs_dmapiops_t
id|vfs_dmapiops
suffix:semicolon
multiline_comment|/* data migration */
DECL|member|vfs_quotactl
id|vfs_quotactl_t
id|vfs_quotactl
suffix:semicolon
multiline_comment|/* disk quota */
DECL|member|vfs_init_vnode
id|vfs_init_vnode_t
id|vfs_init_vnode
suffix:semicolon
multiline_comment|/* initialize a new vnode */
DECL|member|vfs_force_shutdown
id|vfs_force_shutdown_t
id|vfs_force_shutdown
suffix:semicolon
multiline_comment|/* crash and burn */
DECL|typedef|vfsops_t
)brace
id|vfsops_t
suffix:semicolon
multiline_comment|/*&n; * VFS&squot;s.  Operates on vfs structure pointers (starts at bhv head).&n; */
DECL|macro|VHEAD
mdefine_line|#define VHEAD(v)&t;&t;&t;((v)-&gt;vfs_fbhv)
DECL|macro|VFS_MOUNT
mdefine_line|#define VFS_MOUNT(v, ma,cr, rv)&t;&t;((rv) = vfs_mount(VHEAD(v), ma,cr))
DECL|macro|VFS_PARSEARGS
mdefine_line|#define VFS_PARSEARGS(v, o,ma,f, rv)&t;((rv) = vfs_parseargs(VHEAD(v), o,ma,f))
DECL|macro|VFS_SHOWARGS
mdefine_line|#define VFS_SHOWARGS(v, m, rv)&t;&t;((rv) = vfs_showargs(VHEAD(v), m))
DECL|macro|VFS_UNMOUNT
mdefine_line|#define VFS_UNMOUNT(v, f, cr, rv)&t;((rv) = vfs_unmount(VHEAD(v), f,cr))
DECL|macro|VFS_MNTUPDATE
mdefine_line|#define VFS_MNTUPDATE(v, fl, args, rv)&t;((rv) = vfs_mntupdate(VHEAD(v), fl, args))
DECL|macro|VFS_ROOT
mdefine_line|#define VFS_ROOT(v, vpp, rv)&t;&t;((rv) = vfs_root(VHEAD(v), vpp))
DECL|macro|VFS_STATVFS
mdefine_line|#define VFS_STATVFS(v, sp,vp, rv)&t;((rv) = vfs_statvfs(VHEAD(v), sp,vp))
DECL|macro|VFS_SYNC
mdefine_line|#define VFS_SYNC(v, flag,cr, rv)&t;((rv) = vfs_sync(VHEAD(v), flag,cr))
DECL|macro|VFS_VGET
mdefine_line|#define VFS_VGET(v, vpp,fidp, rv)&t;((rv) = vfs_vget(VHEAD(v), vpp,fidp))
DECL|macro|VFS_DMAPIOPS
mdefine_line|#define VFS_DMAPIOPS(v, p, rv)&t;&t;((rv) = vfs_dmapiops(VHEAD(v), p))
DECL|macro|VFS_QUOTACTL
mdefine_line|#define VFS_QUOTACTL(v, c,id,p, rv)&t;((rv) = vfs_quotactl(VHEAD(v), c,id,p))
DECL|macro|VFS_INIT_VNODE
mdefine_line|#define VFS_INIT_VNODE(v, vp,b,ul)&t;( vfs_init_vnode(VHEAD(v), vp,b,ul) )
DECL|macro|VFS_FORCE_SHUTDOWN
mdefine_line|#define VFS_FORCE_SHUTDOWN(v, fl,f,l)&t;( vfs_force_shutdown(VHEAD(v), fl,f,l) )
multiline_comment|/*&n; * PVFS&squot;s.  Operates on behavior descriptor pointers.&n; */
DECL|macro|PVFS_MOUNT
mdefine_line|#define PVFS_MOUNT(b, ma,cr, rv)&t;((rv) = vfs_mount(b, ma,cr))
DECL|macro|PVFS_PARSEARGS
mdefine_line|#define PVFS_PARSEARGS(b, o,ma,f, rv)&t;((rv) = vfs_parseargs(b, o,ma,f))
DECL|macro|PVFS_SHOWARGS
mdefine_line|#define PVFS_SHOWARGS(b, m, rv)&t;&t;((rv) = vfs_showargs(b, m))
DECL|macro|PVFS_UNMOUNT
mdefine_line|#define PVFS_UNMOUNT(b, f,cr, rv)&t;((rv) = vfs_unmount(b, f,cr))
DECL|macro|PVFS_MNTUPDATE
mdefine_line|#define PVFS_MNTUPDATE(b, fl, args, rv)&t;((rv) = vfs_mntupdate(b, fl, args))
DECL|macro|PVFS_ROOT
mdefine_line|#define PVFS_ROOT(b, vpp, rv)&t;&t;((rv) = vfs_root(b, vpp))
DECL|macro|PVFS_STATVFS
mdefine_line|#define PVFS_STATVFS(b, sp,vp, rv)&t;((rv) = vfs_statvfs(b, sp,vp))
DECL|macro|PVFS_SYNC
mdefine_line|#define PVFS_SYNC(b, flag,cr, rv)&t;((rv) = vfs_sync(b, flag,cr))
DECL|macro|PVFS_VGET
mdefine_line|#define PVFS_VGET(b, vpp,fidp, rv)&t;((rv) = vfs_vget(b, vpp,fidp))
DECL|macro|PVFS_DMAPIOPS
mdefine_line|#define PVFS_DMAPIOPS(b, p, rv)&t;&t;((rv) = vfs_dmapiops(b, p))
DECL|macro|PVFS_QUOTACTL
mdefine_line|#define PVFS_QUOTACTL(b, c,id,p, rv)&t;((rv) = vfs_quotactl(b, c,id,p))
DECL|macro|PVFS_INIT_VNODE
mdefine_line|#define PVFS_INIT_VNODE(b, vp,b2,ul)&t;( vfs_init_vnode(b, vp,b2,ul) )
DECL|macro|PVFS_FORCE_SHUTDOWN
mdefine_line|#define PVFS_FORCE_SHUTDOWN(b, fl,f,l)&t;( vfs_force_shutdown(b, fl,f,l) )
r_extern
r_int
id|vfs_mount
c_func
(paren
id|bhv_desc_t
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
r_extern
r_int
id|vfs_parseargs
c_func
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_struct
id|xfs_mount_args
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|vfs_showargs
c_func
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|vfs_unmount
c_func
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
r_extern
r_int
id|vfs_mntupdate
c_func
(paren
id|bhv_desc_t
op_star
comma
r_int
op_star
comma
r_struct
id|xfs_mount_args
op_star
)paren
suffix:semicolon
r_extern
r_int
id|vfs_root
c_func
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
r_extern
r_int
id|vfs_statvfs
c_func
(paren
id|bhv_desc_t
op_star
comma
r_struct
id|kstatfs
op_star
comma
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|vfs_sync
c_func
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
r_extern
r_int
id|vfs_vget
c_func
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
r_extern
r_int
id|vfs_dmapiops
c_func
(paren
id|bhv_desc_t
op_star
comma
id|caddr_t
)paren
suffix:semicolon
r_extern
r_int
id|vfs_quotactl
c_func
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_int
comma
id|caddr_t
)paren
suffix:semicolon
r_extern
r_void
id|vfs_init_vnode
c_func
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
r_extern
r_void
id|vfs_force_shutdown
c_func
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
DECL|struct|bhv_vfsops
r_typedef
r_struct
id|bhv_vfsops
(brace
DECL|member|bhv_common
r_struct
id|vfsops
id|bhv_common
suffix:semicolon
DECL|member|bhv_custom
r_void
op_star
id|bhv_custom
suffix:semicolon
DECL|typedef|bhv_vfsops_t
)brace
id|bhv_vfsops_t
suffix:semicolon
DECL|macro|vfs_bhv_lookup
mdefine_line|#define vfs_bhv_lookup(v, id)&t;( bhv_lookup_range(&amp;(v)-&gt;vfs_bh, (id), (id)) )
DECL|macro|vfs_bhv_custom
mdefine_line|#define vfs_bhv_custom(b)&t;( ((bhv_vfsops_t *)BHV_OPS(b))-&gt;bhv_custom )
DECL|macro|vfs_bhv_set_custom
mdefine_line|#define vfs_bhv_set_custom(b,o)&t;( (b)-&gt;bhv_custom = (void *)(o))
DECL|macro|vfs_bhv_clr_custom
mdefine_line|#define vfs_bhv_clr_custom(b)&t;( (b)-&gt;bhv_custom = NULL )
r_extern
id|vfs_t
op_star
id|vfs_allocate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vfs_deallocate
c_func
(paren
id|vfs_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vfs_insertops
c_func
(paren
id|vfs_t
op_star
comma
id|bhv_vfsops_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vfs_insertbhv
c_func
(paren
id|vfs_t
op_star
comma
id|bhv_desc_t
op_star
comma
id|vfsops_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bhv_insert_all_vfsops
c_func
(paren
r_struct
id|vfs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bhv_remove_all_vfsops
c_func
(paren
r_struct
id|vfs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bhv_remove_vfsops
c_func
(paren
r_struct
id|vfs
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_VFS_H__ */
eof
