multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#ifndef CONFIG_XFS_QUOTA
id|STATIC
r_struct
id|xfs_dquot
op_star
DECL|function|xfs_dqvopchown_default
id|xfs_dqvopchown_default
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_inode
op_star
id|ip
comma
r_struct
id|xfs_dquot
op_star
op_star
id|dqp
comma
r_struct
id|xfs_dquot
op_star
id|dq
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|xfs_qmcore_xfs
id|xfs_qmops_t
id|xfs_qmcore_xfs
op_assign
(brace
dot
id|xfs_qminit
op_assign
(paren
id|xfs_qminit_t
)paren
id|fs_noerr
comma
dot
id|xfs_qmdone
op_assign
(paren
id|xfs_qmdone_t
)paren
id|fs_noerr
comma
dot
id|xfs_qmmount
op_assign
(paren
id|xfs_qmmount_t
)paren
id|fs_noerr
comma
dot
id|xfs_qmunmount
op_assign
(paren
id|xfs_qmunmount_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqrele
op_assign
(paren
id|xfs_dqrele_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqattach
op_assign
(paren
id|xfs_dqattach_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqdetach
op_assign
(paren
id|xfs_dqdetach_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqpurgeall
op_assign
(paren
id|xfs_dqpurgeall_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqvopalloc
op_assign
(paren
id|xfs_dqvopalloc_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqvopcreate
op_assign
(paren
id|xfs_dqvopcreate_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqvoprename
op_assign
(paren
id|xfs_dqvoprename_t
)paren
id|fs_noerr
comma
dot
id|xfs_dqvopchown
op_assign
id|xfs_dqvopchown_default
comma
dot
id|xfs_dqvopchownresv
op_assign
(paren
id|xfs_dqvopchownresv_t
)paren
id|fs_noerr
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_XFS_QUOTA */
eof
