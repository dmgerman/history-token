multiline_comment|/*&n; * Copyright (c) 2001-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SYSCTL_H__
DECL|macro|__XFS_SYSCTL_H__
mdefine_line|#define __XFS_SYSCTL_H__
macro_line|#include &lt;linux/sysctl.h&gt;
multiline_comment|/*&n; * Tunable xfs parameters&n; */
DECL|struct|xfs_sysctl_val
r_typedef
r_struct
id|xfs_sysctl_val
(brace
DECL|member|min
r_int
id|min
suffix:semicolon
DECL|member|val
r_int
id|val
suffix:semicolon
DECL|member|max
r_int
id|max
suffix:semicolon
DECL|typedef|xfs_sysctl_val_t
)brace
id|xfs_sysctl_val_t
suffix:semicolon
DECL|struct|xfs_param
r_typedef
r_struct
id|xfs_param
(brace
DECL|member|restrict_chown
id|xfs_sysctl_val_t
id|restrict_chown
suffix:semicolon
multiline_comment|/* Root/non-root can give away files.*/
DECL|member|sgid_inherit
id|xfs_sysctl_val_t
id|sgid_inherit
suffix:semicolon
multiline_comment|/* Inherit S_ISGID if process&squot; GID is&n;&t;&t;&t;&t;&t; * not a member of parent dir GID. */
DECL|member|symlink_mode
id|xfs_sysctl_val_t
id|symlink_mode
suffix:semicolon
multiline_comment|/* Link creat mode affected by umask */
DECL|member|panic_mask
id|xfs_sysctl_val_t
id|panic_mask
suffix:semicolon
multiline_comment|/* bitmask to cause panic on errors. */
DECL|member|error_level
id|xfs_sysctl_val_t
id|error_level
suffix:semicolon
multiline_comment|/* Degree of reporting for problems  */
DECL|member|syncd_timer
id|xfs_sysctl_val_t
id|syncd_timer
suffix:semicolon
multiline_comment|/* Interval between xfssyncd wakeups */
DECL|member|stats_clear
id|xfs_sysctl_val_t
id|stats_clear
suffix:semicolon
multiline_comment|/* Reset all XFS statistics to zero. */
DECL|member|inherit_sync
id|xfs_sysctl_val_t
id|inherit_sync
suffix:semicolon
multiline_comment|/* Inherit the &quot;sync&quot; inode flag. */
DECL|member|inherit_nodump
id|xfs_sysctl_val_t
id|inherit_nodump
suffix:semicolon
multiline_comment|/* Inherit the &quot;nodump&quot; inode flag. */
DECL|member|inherit_noatim
id|xfs_sysctl_val_t
id|inherit_noatim
suffix:semicolon
multiline_comment|/* Inherit the &quot;noatime&quot; inode flag. */
DECL|member|xfs_buf_timer
id|xfs_sysctl_val_t
id|xfs_buf_timer
suffix:semicolon
multiline_comment|/* Interval between xfsbufd wakeups. */
DECL|member|xfs_buf_age
id|xfs_sysctl_val_t
id|xfs_buf_age
suffix:semicolon
multiline_comment|/* Metadata buffer age before flush. */
DECL|member|inherit_nosym
id|xfs_sysctl_val_t
id|inherit_nosym
suffix:semicolon
multiline_comment|/* Inherit the &quot;nosymlinks&quot; flag. */
DECL|member|rotorstep
id|xfs_sysctl_val_t
id|rotorstep
suffix:semicolon
multiline_comment|/* inode32 AG rotoring control knob */
DECL|typedef|xfs_param_t
)brace
id|xfs_param_t
suffix:semicolon
multiline_comment|/*&n; * xfs_error_level:&n; *&n; * How much error reporting will be done when internal problems are&n; * encountered.  These problems normally return an EFSCORRUPTED to their&n; * caller, with no other information reported.&n; *&n; * 0&t;No error reports&n; * 1&t;Report EFSCORRUPTED errors that will cause a filesystem shutdown&n; * 5&t;Report all EFSCORRUPTED errors (all of the above errors, plus any&n; *&t;additional errors that are known to not cause shutdowns)&n; *&n; * xfs_panic_mask bit 0x8 turns the error reports into panics&n; */
r_enum
(brace
multiline_comment|/* XFS_REFCACHE_SIZE = 1 */
multiline_comment|/* XFS_REFCACHE_PURGE = 2 */
DECL|enumerator|XFS_RESTRICT_CHOWN
id|XFS_RESTRICT_CHOWN
op_assign
l_int|3
comma
DECL|enumerator|XFS_SGID_INHERIT
id|XFS_SGID_INHERIT
op_assign
l_int|4
comma
DECL|enumerator|XFS_SYMLINK_MODE
id|XFS_SYMLINK_MODE
op_assign
l_int|5
comma
DECL|enumerator|XFS_PANIC_MASK
id|XFS_PANIC_MASK
op_assign
l_int|6
comma
DECL|enumerator|XFS_ERRLEVEL
id|XFS_ERRLEVEL
op_assign
l_int|7
comma
DECL|enumerator|XFS_SYNCD_TIMER
id|XFS_SYNCD_TIMER
op_assign
l_int|8
comma
multiline_comment|/* XFS_PROBE_DMAPI = 9 */
multiline_comment|/* XFS_PROBE_IOOPS = 10 */
multiline_comment|/* XFS_PROBE_QUOTA = 11 */
DECL|enumerator|XFS_STATS_CLEAR
id|XFS_STATS_CLEAR
op_assign
l_int|12
comma
DECL|enumerator|XFS_INHERIT_SYNC
id|XFS_INHERIT_SYNC
op_assign
l_int|13
comma
DECL|enumerator|XFS_INHERIT_NODUMP
id|XFS_INHERIT_NODUMP
op_assign
l_int|14
comma
DECL|enumerator|XFS_INHERIT_NOATIME
id|XFS_INHERIT_NOATIME
op_assign
l_int|15
comma
DECL|enumerator|XFS_BUF_TIMER
id|XFS_BUF_TIMER
op_assign
l_int|16
comma
DECL|enumerator|XFS_BUF_AGE
id|XFS_BUF_AGE
op_assign
l_int|17
comma
multiline_comment|/* XFS_IO_BYPASS = 18 */
DECL|enumerator|XFS_INHERIT_NOSYM
id|XFS_INHERIT_NOSYM
op_assign
l_int|19
comma
DECL|enumerator|XFS_ROTORSTEP
id|XFS_ROTORSTEP
op_assign
l_int|20
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
DECL|macro|xfs_sysctl_register
macro_line|# define xfs_sysctl_register()&t;&t;do { } while (0)
DECL|macro|xfs_sysctl_unregister
macro_line|# define xfs_sysctl_unregister()&t;do { } while (0)
macro_line|#endif /* CONFIG_SYSCTL */
macro_line|#endif /* __XFS_SYSCTL_H__ */
eof
