multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
DECL|macro|MNTOPT_QUOTA
mdefine_line|#define MNTOPT_QUOTA&t;&quot;quota&quot;&t;&t;/* disk quotas (user) */
DECL|macro|MNTOPT_NOQUOTA
mdefine_line|#define MNTOPT_NOQUOTA&t;&quot;noquota&quot;&t;/* no quotas */
DECL|macro|MNTOPT_USRQUOTA
mdefine_line|#define MNTOPT_USRQUOTA&t;&quot;usrquota&quot;&t;/* user quota enabled */
DECL|macro|MNTOPT_GRPQUOTA
mdefine_line|#define MNTOPT_GRPQUOTA&t;&quot;grpquota&quot;&t;/* group quota enabled */
DECL|macro|MNTOPT_UQUOTA
mdefine_line|#define MNTOPT_UQUOTA&t;&quot;uquota&quot;&t;/* user quota (IRIX variant) */
DECL|macro|MNTOPT_GQUOTA
mdefine_line|#define MNTOPT_GQUOTA&t;&quot;gquota&quot;&t;/* group quota (IRIX variant) */
DECL|macro|MNTOPT_UQUOTANOENF
mdefine_line|#define MNTOPT_UQUOTANOENF &quot;uqnoenforce&quot;/* user quota limit enforcement */
DECL|macro|MNTOPT_GQUOTANOENF
mdefine_line|#define MNTOPT_GQUOTANOENF &quot;gqnoenforce&quot;/* group quota limit enforcement */
DECL|macro|MNTOPT_QUOTANOENF
mdefine_line|#define MNTOPT_QUOTANOENF  &quot;qnoenforce&quot;&t;/* same as uqnoenforce */
id|STATIC
r_int
DECL|function|xfs_qm_parseargs
id|xfs_qm_parseargs
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bhv
comma
r_char
op_star
id|options
comma
r_struct
id|xfs_mount_args
op_star
id|args
comma
r_int
id|update
)paren
(brace
r_int
id|length
suffix:semicolon
r_char
op_star
id|local_options
op_assign
id|options
suffix:semicolon
r_char
op_star
id|this_char
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|referenced
op_assign
id|update
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
c_func
(paren
op_amp
id|local_options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|length
op_assign
id|strlen
c_func
(paren
id|this_char
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_options
)paren
id|length
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_NOQUOTA
)paren
)paren
(brace
id|args-&gt;flags
op_and_assign
op_complement
(paren
id|XFSMNT_UQUOTAENF
op_or
id|XFSMNT_UQUOTA
)paren
suffix:semicolon
id|args-&gt;flags
op_and_assign
op_complement
(paren
id|XFSMNT_GQUOTAENF
op_or
id|XFSMNT_GQUOTA
)paren
suffix:semicolon
id|referenced
op_assign
id|update
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_QUOTA
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_UQUOTA
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_USRQUOTA
)paren
)paren
(brace
id|args-&gt;flags
op_or_assign
id|XFSMNT_UQUOTA
op_or
id|XFSMNT_UQUOTAENF
suffix:semicolon
id|referenced
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_QUOTANOENF
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_UQUOTANOENF
)paren
)paren
(brace
id|args-&gt;flags
op_or_assign
id|XFSMNT_UQUOTA
suffix:semicolon
id|args-&gt;flags
op_and_assign
op_complement
id|XFSMNT_UQUOTAENF
suffix:semicolon
id|referenced
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_GQUOTA
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_GRPQUOTA
)paren
)paren
(brace
id|args-&gt;flags
op_or_assign
id|XFSMNT_GQUOTA
op_or
id|XFSMNT_GQUOTAENF
suffix:semicolon
id|referenced
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|MNTOPT_GQUOTANOENF
)paren
)paren
(brace
id|args-&gt;flags
op_or_assign
id|XFSMNT_GQUOTA
suffix:semicolon
id|args-&gt;flags
op_and_assign
op_complement
id|XFSMNT_GQUOTAENF
suffix:semicolon
id|referenced
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|local_options
)paren
op_star
(paren
id|local_options
op_minus
l_int|1
)paren
op_assign
l_char|&squot;,&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_decrement
)paren
op_star
id|this_char
op_increment
op_assign
l_char|&squot;,&squot;
suffix:semicolon
)brace
id|PVFS_PARSEARGS
c_func
(paren
id|BHV_NEXT
c_func
(paren
id|bhv
)paren
comma
id|options
comma
id|args
comma
id|update
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|referenced
)paren
id|bhv_remove_vfsops
c_func
(paren
id|bhvtovfs
c_func
(paren
id|bhv
)paren
comma
id|VFS_POSITION_QM
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_qm_showargs
id|xfs_qm_showargs
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bhv
comma
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|bhvtovfs
c_func
(paren
id|bhv
)paren
suffix:semicolon
r_struct
id|xfs_mount
op_star
id|mp
op_assign
id|XFS_VFSTOM
c_func
(paren
id|vfsp
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;m_qflags
op_amp
id|XFS_UQUOTA_ACCT
)paren
(brace
(paren
id|mp-&gt;m_qflags
op_amp
id|XFS_UQUOTA_ENFD
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;,&quot;
id|MNTOPT_USRQUOTA
)paren
suffix:colon
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;,&quot;
id|MNTOPT_UQUOTANOENF
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp-&gt;m_qflags
op_amp
id|XFS_GQUOTA_ACCT
)paren
(brace
(paren
id|mp-&gt;m_qflags
op_amp
id|XFS_GQUOTA_ENFD
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;,&quot;
id|MNTOPT_GRPQUOTA
)paren
suffix:colon
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;,&quot;
id|MNTOPT_GQUOTANOENF
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mp-&gt;m_qflags
op_amp
(paren
id|XFS_UQUOTA_ACCT
op_or
id|XFS_GQUOTA_ACCT
)paren
)paren
)paren
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;,&quot;
id|MNTOPT_NOQUOTA
)paren
suffix:semicolon
id|PVFS_SHOWARGS
c_func
(paren
id|BHV_NEXT
c_func
(paren
id|bhv
)paren
comma
id|m
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_qm_mount
id|xfs_qm_mount
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bhv
comma
r_struct
id|xfs_mount_args
op_star
id|args
comma
r_struct
id|cred
op_star
id|cr
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|bhvtovfs
c_func
(paren
id|bhv
)paren
suffix:semicolon
r_struct
id|xfs_mount
op_star
id|mp
op_assign
id|XFS_VFSTOM
c_func
(paren
id|vfsp
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;flags
op_amp
(paren
id|XFSMNT_UQUOTA
op_or
id|XFSMNT_GQUOTA
)paren
)paren
id|xfs_qm_mount_quotainit
c_func
(paren
id|mp
comma
id|args-&gt;flags
)paren
suffix:semicolon
id|PVFS_MOUNT
c_func
(paren
id|BHV_NEXT
c_func
(paren
id|bhv
)paren
comma
id|args
comma
id|cr
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_qm_syncall
id|xfs_qm_syncall
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bhv
comma
r_int
id|flags
comma
id|cred_t
op_star
id|credp
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|bhvtovfs
c_func
(paren
id|bhv
)paren
suffix:semicolon
r_struct
id|xfs_mount
op_star
id|mp
op_assign
id|XFS_VFSTOM
c_func
(paren
id|vfsp
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Get the Quota Manager to flush the dquots.&n;&t; */
r_if
c_cond
(paren
id|XFS_IS_QUOTA_ON
c_func
(paren
id|mp
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|xfs_qm_sync
c_func
(paren
id|mp
comma
id|flags
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If we got an IO error, we will be shutting down.&n;&t;&t;&t; * So, there&squot;s nothing more for us to do here.&n;&t;&t;&t; */
id|ASSERT
c_func
(paren
id|error
op_ne
id|EIO
op_logical_or
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
(brace
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
)brace
)brace
id|PVFS_SYNC
c_func
(paren
id|BHV_NEXT
c_func
(paren
id|bhv
)paren
comma
id|flags
comma
id|credp
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|xfs_qmops_xfs
id|vfsops_t
id|xfs_qmops_xfs
op_assign
(brace
id|BHV_IDENTITY_INIT
c_func
(paren
id|VFS_BHV_QM
comma
id|VFS_POSITION_QM
)paren
comma
dot
id|vfs_parseargs
op_assign
id|xfs_qm_parseargs
comma
dot
id|vfs_showargs
op_assign
id|xfs_qm_showargs
comma
dot
id|vfs_mount
op_assign
id|xfs_qm_mount
comma
dot
id|vfs_sync
op_assign
id|xfs_qm_syncall
comma
dot
id|vfs_quotactl
op_assign
id|xfs_qm_quotactl
comma
)brace
suffix:semicolon
eof
