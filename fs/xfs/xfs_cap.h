multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_CAP_H__
DECL|macro|__XFS_CAP_H__
mdefine_line|#define __XFS_CAP_H__
multiline_comment|/*&n; * Capabilities&n; */
DECL|typedef|xfs_cap_value_t
r_typedef
id|__uint64_t
id|xfs_cap_value_t
suffix:semicolon
DECL|struct|xfs_cap_set
r_typedef
r_struct
id|xfs_cap_set
(brace
DECL|member|cap_effective
id|xfs_cap_value_t
id|cap_effective
suffix:semicolon
multiline_comment|/* use in capability checks */
DECL|member|cap_permitted
id|xfs_cap_value_t
id|cap_permitted
suffix:semicolon
multiline_comment|/* combined with file attrs */
DECL|member|cap_inheritable
id|xfs_cap_value_t
id|cap_inheritable
suffix:semicolon
multiline_comment|/* pass through exec */
DECL|typedef|xfs_cap_set_t
)brace
id|xfs_cap_set_t
suffix:semicolon
multiline_comment|/* On-disk XFS extended attribute names */
DECL|macro|SGI_CAP_FILE
mdefine_line|#define SGI_CAP_FILE&t;&quot;SGI_CAP_FILE&quot;
DECL|macro|SGI_CAP_FILE_SIZE
mdefine_line|#define SGI_CAP_FILE_SIZE&t;(sizeof(SGI_CAP_FILE)-1)
DECL|macro|SGI_CAP_LINUX
mdefine_line|#define SGI_CAP_LINUX&t;&quot;SGI_CAP_LINUX&quot;
DECL|macro|SGI_CAP_LINUX_SIZE
mdefine_line|#define SGI_CAP_LINUX_SIZE&t;(sizeof(SGI_CAP_LINUX)-1)
multiline_comment|/*&n; * For Linux, we take the bitfields directly from capability.h&n; * and no longer attempt to keep this attribute ondisk compatible&n; * with IRIX.  Since this attribute is only set on exectuables,&n; * it just doesn&squot;t make much sense to try.  We do use a different&n; * named attribute though, to avoid confusion.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_FS_POSIX_CAP
macro_line|#include &lt;linux/posix_cap_xattr.h&gt;
r_struct
id|vnode
suffix:semicolon
r_extern
r_int
id|xfs_cap_vhascap
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_cap_vset
c_func
(paren
r_struct
id|vnode
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_cap_vget
c_func
(paren
r_struct
id|vnode
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_cap_vremove
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
suffix:semicolon
DECL|macro|_CAP_EXISTS
mdefine_line|#define _CAP_EXISTS&t;&t;xfs_cap_vhascap
macro_line|#else
DECL|macro|xfs_cap_vset
mdefine_line|#define xfs_cap_vset(v,p,sz)&t;(-EOPNOTSUPP)
DECL|macro|xfs_cap_vget
mdefine_line|#define xfs_cap_vget(v,p,sz)&t;(-EOPNOTSUPP)
DECL|macro|xfs_cap_vremove
mdefine_line|#define xfs_cap_vremove(v)&t;(-EOPNOTSUPP)
DECL|macro|_CAP_EXISTS
mdefine_line|#define _CAP_EXISTS&t;&t;(NULL)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_CAP_H__ */
eof
