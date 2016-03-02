multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
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
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_itable.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode_item.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_da_btree.h&quot;
macro_line|#include &quot;xfs_attr.h&quot;
macro_line|#include &quot;xfs_attr_leaf.h&quot;
r_int
DECL|function|xfs_attr_fetch
id|xfs_attr_fetch
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_char
op_star
id|name
comma
r_char
op_star
id|value
comma
r_int
id|valuelen
)paren
(brace
id|xfs_da_args_t
id|args
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|XFS_IFORK_Q
c_func
(paren
id|ip
)paren
op_eq
l_int|0
)paren
r_return
id|ENOATTR
suffix:semicolon
multiline_comment|/*&n;&t; * Do the argument setup for the xfs_attr routines.&n;&t; */
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.dp
op_assign
id|ip
suffix:semicolon
id|args.flags
op_assign
id|ATTR_ROOT
suffix:semicolon
id|args.whichfork
op_assign
id|XFS_ATTR_FORK
suffix:semicolon
id|args.name
op_assign
id|name
suffix:semicolon
id|args.namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|args.value
op_assign
id|value
suffix:semicolon
id|args.valuelen
op_assign
id|valuelen
suffix:semicolon
id|args.hashval
op_assign
id|xfs_da_hashname
c_func
(paren
id|args.name
comma
id|args.namelen
)paren
suffix:semicolon
id|args.oknoent
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Decide on what work routines to call based on the inode size.&n;&t; */
r_if
c_cond
(paren
id|args.dp-&gt;i_d.di_aformat
op_eq
id|XFS_DINODE_FMT_LOCAL
)paren
id|error
op_assign
id|xfs_attr_shortform_getvalue
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|xfs_bmap_one_block
c_func
(paren
id|args.dp
comma
id|XFS_ATTR_FORK
)paren
)paren
id|error
op_assign
id|xfs_attr_leaf_get
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_else
id|error
op_assign
id|xfs_attr_node_get
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|EEXIST
)paren
id|error
op_assign
l_int|0
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
