multiline_comment|/*&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|xfs_min
id|STATIC
id|ulong
id|xfs_min
(braket
id|XFS_PARAM
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|xfs_max
id|STATIC
id|ulong
id|xfs_max
(braket
id|XFS_PARAM
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|127
comma
l_int|3
)brace
suffix:semicolon
DECL|variable|xfs_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|xfs_table_header
suffix:semicolon
id|STATIC
r_int
DECL|function|xfs_stats_clear_proc_handler
id|xfs_stats_clear_proc_handler
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|ret
comma
op_star
id|valp
op_assign
id|ctl-&gt;data
suffix:semicolon
id|__uint32_t
id|vn_active
suffix:semicolon
id|ret
op_assign
id|proc_doulongvec_minmax
c_func
(paren
id|ctl
comma
id|write
comma
id|filp
comma
id|buffer
comma
id|lenp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|write
op_logical_and
op_star
id|valp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XFS Clearing xfsstats&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* save vn_active, it&squot;s a universal truth! */
id|vn_active
op_assign
id|xfsstats.vn_active
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xfsstats
comma
l_int|0
comma
r_sizeof
(paren
id|xfsstats
)paren
)paren
suffix:semicolon
id|xfsstats.vn_active
op_assign
id|vn_active
suffix:semicolon
id|xfs_params.stats_clear
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|xfs_table
id|STATIC
id|ctl_table
id|xfs_table
(braket
)braket
op_assign
(brace
(brace
id|XFS_STATS_CLEAR
comma
l_string|&quot;stats_clear&quot;
comma
op_amp
id|xfs_params.stats_clear
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|xfs_stats_clear_proc_handler
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|0
)braket
comma
op_amp
id|xfs_max
(braket
l_int|0
)braket
)brace
comma
(brace
id|XFS_RESTRICT_CHOWN
comma
l_string|&quot;restrict_chown&quot;
comma
op_amp
id|xfs_params.restrict_chown
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_doulongvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|1
)braket
comma
op_amp
id|xfs_max
(braket
l_int|1
)braket
)brace
comma
(brace
id|XFS_SGID_INHERIT
comma
l_string|&quot;irix_sgid_inherit&quot;
comma
op_amp
id|xfs_params.sgid_inherit
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_doulongvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|2
)braket
comma
op_amp
id|xfs_max
(braket
l_int|2
)braket
)brace
comma
(brace
id|XFS_SYMLINK_MODE
comma
l_string|&quot;irix_symlink_mode&quot;
comma
op_amp
id|xfs_params.symlink_mode
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_doulongvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|3
)braket
comma
op_amp
id|xfs_max
(braket
l_int|3
)braket
)brace
comma
(brace
id|XFS_PANIC_MASK
comma
l_string|&quot;panic_mask&quot;
comma
op_amp
id|xfs_params.panic_mask
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_doulongvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|4
)braket
comma
op_amp
id|xfs_max
(braket
l_int|4
)braket
)brace
comma
(brace
id|XFS_ERRLEVEL
comma
l_string|&quot;error_level&quot;
comma
op_amp
id|xfs_params.error_level
comma
r_sizeof
(paren
id|ulong
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_doulongvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|xfs_min
(braket
l_int|5
)braket
comma
op_amp
id|xfs_max
(braket
l_int|5
)braket
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|xfs_dir_table
id|STATIC
id|ctl_table
id|xfs_dir_table
(braket
)braket
op_assign
(brace
(brace
id|FS_XFS
comma
l_string|&quot;xfs&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|xfs_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|xfs_root_table
id|STATIC
id|ctl_table
id|xfs_root_table
(braket
)braket
op_assign
(brace
(brace
id|CTL_FS
comma
l_string|&quot;fs&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|xfs_dir_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_void
DECL|function|xfs_sysctl_register
id|xfs_sysctl_register
c_func
(paren
r_void
)paren
(brace
id|xfs_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|xfs_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|xfs_sysctl_unregister
id|xfs_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xfs_table_header
)paren
id|unregister_sysctl_table
c_func
(paren
id|xfs_table_header
)paren
suffix:semicolon
)brace
eof
