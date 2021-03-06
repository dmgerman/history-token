multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_REFCACHE_H__
DECL|macro|__XFS_REFCACHE_H__
mdefine_line|#define __XFS_REFCACHE_H__
macro_line|#ifdef HAVE_REFCACHE
multiline_comment|/*&n; * Maximum size (in inodes) for the NFS reference cache&n; */
DECL|macro|XFS_REFCACHE_SIZE_MAX
mdefine_line|#define XFS_REFCACHE_SIZE_MAX&t;512
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_extern
r_void
id|xfs_refcache_insert
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_purge_ip
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_purge_mp
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_purge_some
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_resize
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_destroy
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_refcache_iunlock
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|uint
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_refcache_insert
mdefine_line|#define xfs_refcache_insert(ip)&t;&t;do { } while (0)
DECL|macro|xfs_refcache_purge_ip
mdefine_line|#define xfs_refcache_purge_ip(ip)&t;do { } while (0)
DECL|macro|xfs_refcache_purge_mp
mdefine_line|#define xfs_refcache_purge_mp(mp)&t;do { } while (0)
DECL|macro|xfs_refcache_purge_some
mdefine_line|#define xfs_refcache_purge_some(mp)&t;do { } while (0)
DECL|macro|xfs_refcache_resize
mdefine_line|#define xfs_refcache_resize(size)&t;do { } while (0)
DECL|macro|xfs_refcache_destroy
mdefine_line|#define xfs_refcache_destroy()&t;&t;do { } while (0)
DECL|macro|xfs_refcache_iunlock
mdefine_line|#define xfs_refcache_iunlock(ip, flags)&t;xfs_iunlock(ip, flags)
macro_line|#endif
macro_line|#endif&t;/* __XFS_REFCACHE_H__ */
eof
