multiline_comment|/*&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SYSCTL_H__
DECL|macro|__XFS_SYSCTL_H__
mdefine_line|#define __XFS_SYSCTL_H__
macro_line|#include &lt;linux/sysctl.h&gt;
multiline_comment|/*&n; * Tunable xfs parameters&n; */
DECL|macro|XFS_PARAM
mdefine_line|#define XFS_PARAM&t;(sizeof(struct xfs_param) / sizeof(ulong))
DECL|struct|xfs_param
r_typedef
r_struct
id|xfs_param
(brace
DECL|member|stats_clear
id|ulong
id|stats_clear
suffix:semicolon
multiline_comment|/* Reset all XFS statistics to zero.     */
DECL|member|restrict_chown
id|ulong
id|restrict_chown
suffix:semicolon
multiline_comment|/* Root/non-root can give away files.    */
DECL|member|sgid_inherit
id|ulong
id|sgid_inherit
suffix:semicolon
multiline_comment|/* Inherit ISGID bit if process&squot; GID is  */
multiline_comment|/*  not a member of the parent dir GID.  */
DECL|member|symlink_mode
id|ulong
id|symlink_mode
suffix:semicolon
multiline_comment|/* Symlink creat mode affected by umask. */
DECL|typedef|xfs_param_t
)brace
id|xfs_param_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|XFS_STATS_CLEAR
id|XFS_STATS_CLEAR
op_assign
l_int|1
comma
DECL|enumerator|XFS_RESTRICT_CHOWN
id|XFS_RESTRICT_CHOWN
op_assign
l_int|2
comma
DECL|enumerator|XFS_SGID_INHERIT
id|XFS_SGID_INHERIT
op_assign
l_int|3
comma
DECL|enumerator|XFS_SYMLINK_MODE
id|XFS_SYMLINK_MODE
op_assign
l_int|4
comma
)brace
suffix:semicolon
r_extern
id|xfs_param_t
id|xfs_params
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_void
id|xfs_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|xfs_sysctl_register
r_static
id|__inline
r_void
id|xfs_sysctl_register
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
DECL|function|xfs_sysctl_unregister
r_static
id|__inline
r_void
id|xfs_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __XFS_SYSCTL_H__ */
eof
