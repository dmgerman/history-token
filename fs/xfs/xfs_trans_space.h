multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_TRANS_SPACE_H__
DECL|macro|__XFS_TRANS_SPACE_H__
mdefine_line|#define __XFS_TRANS_SPACE_H__
multiline_comment|/*&n; * Components of space reservations.&n; */
DECL|macro|XFS_MAX_CONTIG_EXTENTS_PER_BLOCK
mdefine_line|#define XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp)&t;&bslash;&n;&t;&t;(((mp)-&gt;m_alloc_mxr[0]) - ((mp)-&gt;m_alloc_mnr[0]))
DECL|macro|XFS_EXTENTADD_SPACE_RES
mdefine_line|#define XFS_EXTENTADD_SPACE_RES(mp,w)&t;(XFS_BM_MAXLEVELS(mp,w) - 1)
DECL|macro|XFS_NEXTENTADD_SPACE_RES
mdefine_line|#define XFS_NEXTENTADD_SPACE_RES(mp,b,w)&bslash;&n;&t;(((b + XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp) - 1) / &bslash;&n;&t;  XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp)) * &bslash;&n;&t;  XFS_EXTENTADD_SPACE_RES(mp,w))
DECL|macro|XFS_DAENTER_1B
mdefine_line|#define XFS_DAENTER_1B(mp,w)&t;((w) == XFS_DATA_FORK ? (mp)-&gt;m_dirblkfsbs : 1)
DECL|macro|XFS_DAENTER_DBS
mdefine_line|#define XFS_DAENTER_DBS(mp,w)&t;&bslash;&n;&t;(XFS_DA_NODE_MAXDEPTH + &bslash;&n;&t; ((XFS_DIR_IS_V2(mp) &amp;&amp; (w) == XFS_DATA_FORK) ? 2 : 0))
DECL|macro|XFS_DAENTER_BLOCKS
mdefine_line|#define XFS_DAENTER_BLOCKS(mp,w)&t;&bslash;&n;&t;(XFS_DAENTER_1B(mp,w) * XFS_DAENTER_DBS(mp,w))
DECL|macro|XFS_DAENTER_BMAP1B
mdefine_line|#define XFS_DAENTER_BMAP1B(mp,w)&t;&bslash;&n;&t;XFS_NEXTENTADD_SPACE_RES(mp, XFS_DAENTER_1B(mp, w), w)
DECL|macro|XFS_DAENTER_BMAPS
mdefine_line|#define XFS_DAENTER_BMAPS(mp,w)&t;&t;&bslash;&n;&t;(XFS_DAENTER_DBS(mp,w) * XFS_DAENTER_BMAP1B(mp,w))
DECL|macro|XFS_DAENTER_SPACE_RES
mdefine_line|#define XFS_DAENTER_SPACE_RES(mp,w)&t;&bslash;&n;&t;(XFS_DAENTER_BLOCKS(mp,w) + XFS_DAENTER_BMAPS(mp,w))
DECL|macro|XFS_DAREMOVE_SPACE_RES
mdefine_line|#define XFS_DAREMOVE_SPACE_RES(mp,w)&t;XFS_DAENTER_BMAPS(mp,w)
DECL|macro|XFS_DIRENTER_MAX_SPLIT
mdefine_line|#define XFS_DIRENTER_MAX_SPLIT(mp,nl)&t;&bslash;&n;&t;(((mp)-&gt;m_sb.sb_blocksize == 512 &amp;&amp; &bslash;&n;&t;  XFS_DIR_IS_V1(mp) &amp;&amp; &bslash;&n;&t;  (nl) &gt;= XFS_DIR_LEAF_CAN_DOUBLE_SPLIT_LEN) ? 2 : 1)
DECL|macro|XFS_DIRENTER_SPACE_RES
mdefine_line|#define XFS_DIRENTER_SPACE_RES(mp,nl)&t;&bslash;&n;&t;(XFS_DAENTER_SPACE_RES(mp, XFS_DATA_FORK) * &bslash;&n;&t; XFS_DIRENTER_MAX_SPLIT(mp,nl))
DECL|macro|XFS_DIRREMOVE_SPACE_RES
mdefine_line|#define XFS_DIRREMOVE_SPACE_RES(mp)&t;&bslash;&n;&t;XFS_DAREMOVE_SPACE_RES(mp, XFS_DATA_FORK)
DECL|macro|XFS_IALLOC_SPACE_RES
mdefine_line|#define XFS_IALLOC_SPACE_RES(mp)&t;&bslash;&n;&t;(XFS_IALLOC_BLOCKS(mp) + XFS_IN_MAXLEVELS(mp)-1)
multiline_comment|/*&n; * Space reservation values for various transactions.&n; */
DECL|macro|XFS_ADDAFORK_SPACE_RES
mdefine_line|#define XFS_ADDAFORK_SPACE_RES(mp)&t;&bslash;&n;&t;((mp)-&gt;m_dirblkfsbs + &bslash;&n;&t; (XFS_DIR_IS_V1(mp) ? 0 : XFS_DAENTER_BMAP1B(mp, XFS_DATA_FORK)))
DECL|macro|XFS_ATTRRM_SPACE_RES
mdefine_line|#define XFS_ATTRRM_SPACE_RES(mp)&t;&bslash;&n;&t;XFS_DAREMOVE_SPACE_RES(mp, XFS_ATTR_FORK)
multiline_comment|/* This macro is not used - see inline code in xfs_attr_set */
DECL|macro|XFS_ATTRSET_SPACE_RES
mdefine_line|#define XFS_ATTRSET_SPACE_RES(mp, v)&t;&bslash;&n;&t;(XFS_DAENTER_SPACE_RES(mp, XFS_ATTR_FORK) + XFS_B_TO_FSB(mp, v))
DECL|macro|XFS_CREATE_SPACE_RES
mdefine_line|#define XFS_CREATE_SPACE_RES(mp,nl)&t;&bslash;&n;&t;(XFS_IALLOC_SPACE_RES(mp) + XFS_DIRENTER_SPACE_RES(mp,nl))
DECL|macro|XFS_DIOSTRAT_SPACE_RES
mdefine_line|#define XFS_DIOSTRAT_SPACE_RES(mp, v)&t;&bslash;&n;&t;(XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK) + (v))
DECL|macro|XFS_GROWFS_SPACE_RES
mdefine_line|#define XFS_GROWFS_SPACE_RES(mp)&t;&bslash;&n;&t;(2 * XFS_AG_MAXLEVELS(mp))
DECL|macro|XFS_GROWFSRT_SPACE_RES
mdefine_line|#define XFS_GROWFSRT_SPACE_RES(mp,b)&t;&bslash;&n;&t;((b) + XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK))
DECL|macro|XFS_LINK_SPACE_RES
mdefine_line|#define XFS_LINK_SPACE_RES(mp,nl)&t;&bslash;&n;&t;XFS_DIRENTER_SPACE_RES(mp,nl)
DECL|macro|XFS_MKDIR_SPACE_RES
mdefine_line|#define XFS_MKDIR_SPACE_RES(mp,nl)&t;&bslash;&n;&t;(XFS_IALLOC_SPACE_RES(mp) + XFS_DIRENTER_SPACE_RES(mp,nl))
DECL|macro|XFS_QM_DQALLOC_SPACE_RES
mdefine_line|#define XFS_QM_DQALLOC_SPACE_RES(mp)&t;&bslash;&n;&t;(XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK) + &bslash;&n;&t; XFS_DQUOT_CLUSTER_SIZE_FSB)
DECL|macro|XFS_QM_QINOCREATE_SPACE_RES
mdefine_line|#define XFS_QM_QINOCREATE_SPACE_RES(mp) &bslash;&n;&t;XFS_IALLOC_SPACE_RES(mp)
DECL|macro|XFS_REMOVE_SPACE_RES
mdefine_line|#define XFS_REMOVE_SPACE_RES(mp)&t;&bslash;&n;&t;XFS_DIRREMOVE_SPACE_RES(mp)
DECL|macro|XFS_RENAME_SPACE_RES
mdefine_line|#define XFS_RENAME_SPACE_RES(mp,nl)&t;&bslash;&n;&t;(XFS_DIRREMOVE_SPACE_RES(mp) + XFS_DIRENTER_SPACE_RES(mp,nl))
DECL|macro|XFS_SYMLINK_SPACE_RES
mdefine_line|#define XFS_SYMLINK_SPACE_RES(mp,nl,b)&t;&bslash;&n;&t;(XFS_IALLOC_SPACE_RES(mp) + XFS_DIRENTER_SPACE_RES(mp,nl) + (b))
macro_line|#endif&t;/* __XFS_TRANS_SPACE_H__ */
eof
