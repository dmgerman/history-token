multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_bit.h&quot;
macro_line|#include &quot;xfs_rtalloc.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_itable.h&quot;
macro_line|#include &quot;xfs_rw.h&quot;
macro_line|#include &quot;xfs_acl.h&quot;
macro_line|#include &quot;xfs_cap.h&quot;
macro_line|#include &quot;xfs_mac.h&quot;
macro_line|#include &quot;xfs_attr.h&quot;
macro_line|#include &quot;xfs_buf_item.h&quot;
macro_line|#include &quot;xfs_qm.h&quot;
DECL|variable|xqmstats
r_struct
id|xqmstats
id|xqmstats
suffix:semicolon
id|STATIC
r_int
DECL|function|xfs_qm_read_xfsquota
id|xfs_qm_read_xfsquota
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
multiline_comment|/* maximum; incore; ratio free to inuse; freelist */
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d&bslash;t%d&bslash;t%d&bslash;t%u&bslash;n&quot;
comma
id|ndquot
comma
id|xfs_Gqm
ques
c_cond
id|atomic_read
c_func
(paren
op_amp
id|xfs_Gqm-&gt;qm_totaldquots
)paren
suffix:colon
l_int|0
comma
id|xfs_Gqm
ques
c_cond
id|xfs_Gqm-&gt;qm_dqfree_ratio
suffix:colon
l_int|0
comma
id|xfs_Gqm
ques
c_cond
id|xfs_Gqm-&gt;qm_dqfreelist.qh_nelems
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|offset
)paren
OG
id|count
)paren
r_return
id|count
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_qm_read_stats
id|xfs_qm_read_stats
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
multiline_comment|/* quota performance statistics */
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;qm %u %u %u %u %u %u %u %u&bslash;n&quot;
comma
id|xqmstats.xs_qm_dqreclaims
comma
id|xqmstats.xs_qm_dqreclaim_misses
comma
id|xqmstats.xs_qm_dquot_dups
comma
id|xqmstats.xs_qm_dqcachemisses
comma
id|xqmstats.xs_qm_dqcachehits
comma
id|xqmstats.xs_qm_dqwants
comma
id|xqmstats.xs_qm_dqshake_reclaims
comma
id|xqmstats.xs_qm_dqinact_reclaims
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|offset
)paren
OG
id|count
)paren
r_return
id|count
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_void
DECL|function|xfs_qm_init_procfs
id|xfs_qm_init_procfs
c_func
(paren
r_void
)paren
(brace
id|create_proc_read_entry
c_func
(paren
l_string|&quot;fs/xfs/xqmstat&quot;
comma
l_int|0
comma
l_int|0
comma
id|xfs_qm_read_stats
comma
l_int|NULL
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;fs/xfs/xqm&quot;
comma
l_int|0
comma
l_int|0
comma
id|xfs_qm_read_xfsquota
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|xfs_qm_cleanup_procfs
id|xfs_qm_cleanup_procfs
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/xfs/xqm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/xfs/xqmstat&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
