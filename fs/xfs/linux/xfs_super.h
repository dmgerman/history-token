multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPER_H__
DECL|macro|__XFS_SUPER_H__
mdefine_line|#define __XFS_SUPER_H__
macro_line|#ifdef CONFIG_XFS_DMAPI
DECL|macro|vfs_insertdmapi
macro_line|# define vfs_insertdmapi(vfs)&t;vfs_insertops(vfsp, &amp;xfs_dmops)
DECL|macro|vfs_initdmapi
macro_line|# define vfs_initdmapi()&t;dmapi_init()
DECL|macro|vfs_exitdmapi
macro_line|# define vfs_exitdmapi()&t;dmapi_uninit()
macro_line|#else
DECL|macro|vfs_insertdmapi
macro_line|# define vfs_insertdmapi(vfs)&t;do { } while (0)
DECL|macro|vfs_initdmapi
macro_line|# define vfs_initdmapi()&t;do { } while (0)
DECL|macro|vfs_exitdmapi
macro_line|# define vfs_exitdmapi()&t;do { } while (0)
macro_line|#endif
macro_line|#ifdef CONFIG_XFS_QUOTA
DECL|macro|vfs_insertquota
macro_line|# define vfs_insertquota(vfs)&t;vfs_insertops(vfsp, &amp;xfs_qmops)
DECL|macro|vfs_initquota
macro_line|# define vfs_initquota()&t;xfs_qm_init()
DECL|macro|vfs_exitquota
macro_line|# define vfs_exitquota()&t;xfs_qm_exit()
macro_line|#else
DECL|macro|vfs_insertquota
macro_line|# define vfs_insertquota(vfs)&t;do { } while (0)
DECL|macro|vfs_initquota
macro_line|# define vfs_initquota()&t;do { } while (0)
DECL|macro|vfs_exitquota
macro_line|# define vfs_exitquota()&t;do { } while (0)
macro_line|#endif
macro_line|#ifdef CONFIG_XFS_POSIX_ACL
DECL|macro|XFS_ACL_STRING
macro_line|# define XFS_ACL_STRING&t;&t;&quot;ACLs, &quot;
DECL|macro|set_posix_acl_flag
macro_line|# define set_posix_acl_flag(sb)&t;((sb)-&gt;s_flags |= MS_POSIXACL)
macro_line|#else
DECL|macro|XFS_ACL_STRING
macro_line|# define XFS_ACL_STRING
DECL|macro|set_posix_acl_flag
macro_line|# define set_posix_acl_flag(sb)&t;do { } while (0)
macro_line|#endif
macro_line|#ifdef CONFIG_XFS_RT
DECL|macro|XFS_REALTIME_STRING
macro_line|# define XFS_REALTIME_STRING&t;&quot;realtime, &quot;
macro_line|#else
DECL|macro|XFS_REALTIME_STRING
macro_line|# define XFS_REALTIME_STRING
macro_line|#endif
macro_line|#if XFS_BIG_FILESYSTEMS
DECL|macro|XFS_BIGFS_STRING
macro_line|# define XFS_BIGFS_STRING&t;&quot;big filesystems, &quot;
macro_line|#else
DECL|macro|XFS_BIGFS_STRING
macro_line|# define XFS_BIGFS_STRING
macro_line|#endif
macro_line|#ifdef CONFIG_XFS_VNODE_TRACING
DECL|macro|XFS_VNTRACE_STRING
macro_line|# define XFS_VNTRACE_STRING&t;&quot;VN-trace, &quot;
macro_line|#else
DECL|macro|XFS_VNTRACE_STRING
macro_line|# define XFS_VNTRACE_STRING
macro_line|#endif
macro_line|#ifdef XFSDEBUG
DECL|macro|XFS_DBG_STRING
macro_line|# define XFS_DBG_STRING&t;&t;&quot;debug&quot;
macro_line|#else
DECL|macro|XFS_DBG_STRING
macro_line|# define XFS_DBG_STRING&t;&t;&quot;no debug&quot;
macro_line|#endif
DECL|macro|XFS_BUILD_OPTIONS
mdefine_line|#define XFS_BUILD_OPTIONS&t;XFS_ACL_STRING &bslash;&n;&t;&t;&t;&t;XFS_REALTIME_STRING &bslash;&n;&t;&t;&t;&t;XFS_BIGFS_STRING &bslash;&n;&t;&t;&t;&t;XFS_VNTRACE_STRING &bslash;&n;&t;&t;&t;&t;XFS_DBG_STRING /* DBG must be last */
DECL|macro|LINVFS_GET_VFS
mdefine_line|#define LINVFS_GET_VFS(s) &bslash;&n;&t;(vfs_t *)((s)-&gt;s_fs_info)
DECL|macro|LINVFS_SET_VFS
mdefine_line|#define LINVFS_SET_VFS(s, vfsp) &bslash;&n;&t;((s)-&gt;s_fs_info = vfsp)
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|pb_target
suffix:semicolon
r_struct
id|block_device
suffix:semicolon
r_extern
id|__uint64_t
id|xfs_max_file_offset
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_initialize_vnode
c_func
(paren
id|bhv_desc_t
op_star
comma
id|vnode_t
op_star
comma
id|bhv_desc_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_blkdev_get
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_const
r_char
op_star
comma
r_struct
id|block_device
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_blkdev_put
c_func
(paren
r_struct
id|block_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|pb_target
op_star
id|xfs_alloc_buftarg
c_func
(paren
r_struct
id|block_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_relse_buftarg
c_func
(paren
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_free_buftarg
c_func
(paren
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_flush_buftarg
c_func
(paren
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_readonly_buftarg
c_func
(paren
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_setsize_buftarg
c_func
(paren
r_struct
id|pb_target
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
r_int
r_int
id|xfs_getsize_buftarg
c_func
(paren
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_SUPER_H__ */
eof
