multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * This file contains globals needed by XFS that were normally defined&n; * somewhere else in IRIX.&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_buf.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_clnt.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_imap.h&quot;
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
macro_line|#include &quot;xfs_da_btree.h&quot;
macro_line|#include &quot;xfs_dir_leaf.h&quot;
macro_line|#include &quot;xfs_dir2_data.h&quot;
macro_line|#include &quot;xfs_dir2_leaf.h&quot;
macro_line|#include &quot;xfs_dir2_block.h&quot;
macro_line|#include &quot;xfs_dir2_node.h&quot;
macro_line|#include &quot;xfs_dir2_trace.h&quot;
macro_line|#include &quot;xfs_acl.h&quot;
macro_line|#include &quot;xfs_cap.h&quot;
macro_line|#include &quot;xfs_mac.h&quot;
macro_line|#include &quot;xfs_attr.h&quot;
macro_line|#include &quot;xfs_attr_leaf.h&quot;
macro_line|#include &quot;xfs_inode_item.h&quot;
macro_line|#include &quot;xfs_buf_item.h&quot;
macro_line|#include &quot;xfs_extfree_item.h&quot;
macro_line|#include &quot;xfs_log_priv.h&quot;
macro_line|#include &quot;xfs_trans_priv.h&quot;
macro_line|#include &quot;xfs_trans_space.h&quot;
macro_line|#include &quot;xfs_utils.h&quot;
multiline_comment|/*&n; * System memory size - used to scale certain data structures in XFS.&n; */
DECL|variable|xfs_physmem
r_int
r_int
id|xfs_physmem
suffix:semicolon
multiline_comment|/*&n; * Tunable XFS parameters.  xfs_params is required even when CONFIG_SYSCTL=n,&n; * other XFS code uses these values.&n; */
DECL|variable|xfs_params
id|xfs_param_t
id|xfs_params
op_assign
(brace
multiline_comment|/*&t;MIN&t;DFLT&t;MAX&t;*/
dot
id|restrict_chown
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
)brace
comma
dot
id|sgid_inherit
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
dot
id|symlink_mode
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
dot
id|panic_mask
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|127
)brace
comma
dot
id|error_level
op_assign
(brace
l_int|0
comma
l_int|3
comma
l_int|11
)brace
comma
dot
id|sync_interval
op_assign
(brace
id|HZ
comma
l_int|30
op_star
id|HZ
comma
l_int|60
op_star
id|HZ
)brace
comma
dot
id|stats_clear
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
dot
id|inherit_sync
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
)brace
comma
dot
id|inherit_nodump
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
)brace
comma
dot
id|inherit_noatim
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Global system credential structure.&n; */
DECL|variable|sys_cred_val
DECL|variable|sys_cred
id|cred_t
id|sys_cred_val
comma
op_star
id|sys_cred
op_assign
op_amp
id|sys_cred_val
suffix:semicolon
multiline_comment|/*&n; * Export symbols used for XFS debugging&n; */
DECL|variable|xfs_next_bit
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_next_bit
)paren
suffix:semicolon
DECL|variable|xfs_contig_bits
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_contig_bits
)paren
suffix:semicolon
DECL|variable|xfs_bmbt_get_all
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmbt_get_all
)paren
suffix:semicolon
macro_line|#if ARCH_CONVERT != ARCH_NOCONVERT
DECL|variable|xfs_bmbt_disk_get_all
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmbt_disk_get_all
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Export symbols used for XFS tracing&n; */
macro_line|#ifdef XFS_ALLOC_TRACE
DECL|variable|xfs_alloc_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_alloc_trace_buf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef XFS_BMAP_TRACE
DECL|variable|xfs_bmap_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmap_trace_buf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef XFS_BMBT_TRACE
DECL|variable|xfs_bmbt_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmbt_trace_buf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef XFS_ATTR_TRACE
DECL|variable|xfs_attr_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_attr_trace_buf
)paren
suffix:semicolon
macro_line|#endif  
macro_line|#ifdef XFS_DIR2_TRACE
DECL|variable|xfs_dir2_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_dir2_trace_buf
)paren
suffix:semicolon
macro_line|#endif   
macro_line|#ifdef XFS_DIR_TRACE
DECL|variable|xfs_dir_trace_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_dir_trace_buf
)paren
suffix:semicolon
macro_line|#endif
eof
