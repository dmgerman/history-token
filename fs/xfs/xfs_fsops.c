multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
multiline_comment|/*&n; * File system operations&n; */
r_int
DECL|function|xfs_fs_geometry
id|xfs_fs_geometry
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_fsop_geom_t
op_star
id|geo
comma
r_int
id|new_version
)paren
(brace
id|geo-&gt;blocksize
op_assign
id|mp-&gt;m_sb.sb_blocksize
suffix:semicolon
id|geo-&gt;rtextsize
op_assign
id|mp-&gt;m_sb.sb_rextsize
suffix:semicolon
id|geo-&gt;agblocks
op_assign
id|mp-&gt;m_sb.sb_agblocks
suffix:semicolon
id|geo-&gt;agcount
op_assign
id|mp-&gt;m_sb.sb_agcount
suffix:semicolon
id|geo-&gt;logblocks
op_assign
id|mp-&gt;m_sb.sb_logblocks
suffix:semicolon
id|geo-&gt;sectsize
op_assign
id|mp-&gt;m_sb.sb_sectsize
suffix:semicolon
id|geo-&gt;inodesize
op_assign
id|mp-&gt;m_sb.sb_inodesize
suffix:semicolon
id|geo-&gt;imaxpct
op_assign
id|mp-&gt;m_sb.sb_imax_pct
suffix:semicolon
id|geo-&gt;datablocks
op_assign
id|mp-&gt;m_sb.sb_dblocks
suffix:semicolon
id|geo-&gt;rtblocks
op_assign
id|mp-&gt;m_sb.sb_rblocks
suffix:semicolon
id|geo-&gt;rtextents
op_assign
id|mp-&gt;m_sb.sb_rextents
suffix:semicolon
id|geo-&gt;logstart
op_assign
id|mp-&gt;m_sb.sb_logstart
suffix:semicolon
id|ASSERT
c_func
(paren
r_sizeof
(paren
id|geo-&gt;uuid
)paren
op_eq
r_sizeof
(paren
id|mp-&gt;m_sb.sb_uuid
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|geo-&gt;uuid
comma
op_amp
id|mp-&gt;m_sb.sb_uuid
comma
r_sizeof
(paren
id|mp-&gt;m_sb.sb_uuid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_version
op_ge
l_int|2
)paren
(brace
id|geo-&gt;sunit
op_assign
id|mp-&gt;m_sb.sb_unit
suffix:semicolon
id|geo-&gt;swidth
op_assign
id|mp-&gt;m_sb.sb_width
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_version
op_ge
l_int|3
)paren
(brace
id|geo-&gt;version
op_assign
id|XFS_FSOP_GEOM_VERSION
suffix:semicolon
id|geo-&gt;flags
op_assign
(paren
id|XFS_SB_VERSION_HASATTR
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_ATTR
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASNLINK
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_NLINK
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASQUOTA
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_QUOTA
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASALIGN
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_IALIGN
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASDALIGN
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_DALIGN
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASSHARED
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_SHARED
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASEXTFLGBIT
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_EXTFLG
suffix:colon
l_int|0
)paren
op_or
(paren
id|XFS_SB_VERSION_HASDIRV2
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_DIRV2
suffix:colon
l_int|0
)paren
suffix:semicolon
id|geo-&gt;logsectsize
op_assign
id|mp-&gt;m_sb.sb_sectsize
suffix:semicolon
multiline_comment|/* XXX */
id|geo-&gt;rtsectsize
op_assign
id|mp-&gt;m_sb.sb_sectsize
suffix:semicolon
multiline_comment|/* XXX */
id|geo-&gt;dirblocksize
op_assign
id|mp-&gt;m_dirblksize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_version
op_ge
l_int|4
)paren
(brace
id|geo-&gt;flags
op_or_assign
(paren
id|XFS_SB_VERSION_HASLOGV2
c_func
(paren
op_amp
id|mp-&gt;m_sb
)paren
ques
c_cond
id|XFS_FSOP_GEOM_FLAGS_LOGV2
suffix:colon
l_int|0
)paren
suffix:semicolon
id|geo-&gt;logsunit
op_assign
id|mp-&gt;m_sb.sb_logsunit
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xfs_growfs_data_private
id|xfs_growfs_data_private
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
multiline_comment|/* mount point for filesystem */
id|xfs_growfs_data_t
op_star
id|in
)paren
multiline_comment|/* growfs data input struct */
(brace
id|xfs_agf_t
op_star
id|agf
suffix:semicolon
id|xfs_agi_t
op_star
id|agi
suffix:semicolon
id|xfs_agnumber_t
id|agno
suffix:semicolon
id|xfs_extlen_t
id|agsize
suffix:semicolon
id|xfs_extlen_t
id|tmpsize
suffix:semicolon
id|xfs_alloc_rec_t
op_star
id|arec
suffix:semicolon
id|xfs_btree_sblock_t
op_star
id|block
suffix:semicolon
id|xfs_buf_t
op_star
id|bp
suffix:semicolon
r_int
id|bsize
suffix:semicolon
r_int
id|bucket
suffix:semicolon
id|xfs_daddr_t
id|disk_addr
suffix:semicolon
r_int
id|dpct
suffix:semicolon
r_int
id|error
suffix:semicolon
id|xfs_agnumber_t
id|nagcount
suffix:semicolon
id|xfs_rfsblock_t
id|nb
comma
id|nb_mod
suffix:semicolon
id|xfs_rfsblock_t
r_new
suffix:semicolon
id|xfs_rfsblock_t
id|nfree
suffix:semicolon
id|xfs_agnumber_t
id|oagcount
suffix:semicolon
r_int
id|pct
suffix:semicolon
id|xfs_sb_t
op_star
id|sbp
suffix:semicolon
r_int
id|sectbb
suffix:semicolon
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
id|nb
op_assign
id|in-&gt;newblocks
suffix:semicolon
id|pct
op_assign
id|in-&gt;imaxpct
suffix:semicolon
r_if
c_cond
(paren
id|nb
OL
id|mp-&gt;m_sb.sb_dblocks
op_logical_or
id|pct
template_param
l_int|100
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|dpct
op_assign
id|pct
op_minus
id|mp-&gt;m_sb.sb_imax_pct
suffix:semicolon
id|error
op_assign
id|xfs_read_buf
c_func
(paren
id|mp
comma
id|mp-&gt;m_ddev_targp
comma
id|XFS_FSB_TO_BB
c_func
(paren
id|mp
comma
id|nb
)paren
op_minus
l_int|1
comma
l_int|1
comma
l_int|0
comma
op_amp
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|ASSERT
c_func
(paren
id|bp
)paren
suffix:semicolon
id|xfs_buf_relse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_new
op_assign
id|nb
suffix:semicolon
multiline_comment|/* use new as a temporary here */
id|nb_mod
op_assign
id|do_div
c_func
(paren
r_new
comma
id|mp-&gt;m_sb.sb_agblocks
)paren
suffix:semicolon
id|nagcount
op_assign
r_new
op_plus
(paren
id|nb_mod
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nb_mod
op_logical_and
id|nb_mod
OL
id|XFS_MIN_AG_BLOCKS
)paren
(brace
id|nagcount
op_decrement
suffix:semicolon
id|nb
op_assign
id|nagcount
op_star
id|mp-&gt;m_sb.sb_agblocks
suffix:semicolon
r_if
c_cond
(paren
id|nb
OL
id|mp-&gt;m_sb.sb_dblocks
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_new
op_assign
id|in-&gt;newblocks
op_minus
id|mp-&gt;m_sb.sb_dblocks
suffix:semicolon
id|oagcount
op_assign
id|mp-&gt;m_sb.sb_agcount
suffix:semicolon
r_if
c_cond
(paren
id|nagcount
OG
id|oagcount
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|mp-&gt;m_peraglock
)paren
suffix:semicolon
id|mp-&gt;m_perag
op_assign
id|kmem_realloc
c_func
(paren
id|mp-&gt;m_perag
comma
r_sizeof
(paren
id|xfs_perag_t
)paren
op_star
id|nagcount
comma
r_sizeof
(paren
id|xfs_perag_t
)paren
op_star
id|oagcount
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mp-&gt;m_perag
(braket
id|oagcount
)braket
comma
l_int|0
comma
(paren
id|nagcount
op_minus
id|oagcount
)paren
op_star
r_sizeof
(paren
id|xfs_perag_t
)paren
)paren
suffix:semicolon
id|mp-&gt;m_flags
op_or_assign
id|XFS_MOUNT_32BITINODES
suffix:semicolon
id|xfs_initialize_perag
c_func
(paren
id|mp
comma
id|nagcount
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|mp-&gt;m_peraglock
)paren
suffix:semicolon
)brace
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_GROWFS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
id|XFS_GROWFS_SPACE_RES
c_func
(paren
id|mp
)paren
comma
id|XFS_GROWDATA_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* new ag&squot;s */
id|sectbb
op_assign
id|BTOBB
c_func
(paren
id|mp-&gt;m_sb.sb_sectsize
)paren
suffix:semicolon
id|bsize
op_assign
id|mp-&gt;m_sb.sb_blocksize
suffix:semicolon
id|nfree
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|agno
op_assign
id|nagcount
op_minus
l_int|1
suffix:semicolon
id|agno
op_ge
id|oagcount
suffix:semicolon
id|agno
op_decrement
comma
r_new
op_sub_assign
id|agsize
)paren
(brace
multiline_comment|/*&n;&t;&t; * AG freelist header block&n;&t;&t; */
id|disk_addr
op_assign
id|XFS_AG_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_AGF_DADDR
)paren
suffix:semicolon
id|bp
op_assign
id|xfs_buf_get
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|disk_addr
comma
id|sectbb
comma
l_int|0
)paren
suffix:semicolon
id|agf
op_assign
id|XFS_BUF_TO_AGF
c_func
(paren
id|bp
)paren
suffix:semicolon
id|memset
c_func
(paren
id|agf
comma
l_int|0
comma
id|mp-&gt;m_sb.sb_sectsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_magicnum
comma
id|ARCH_CONVERT
comma
id|XFS_AGF_MAGIC
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_versionnum
comma
id|ARCH_CONVERT
comma
id|XFS_AGF_VERSION
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_seqno
comma
id|ARCH_CONVERT
comma
id|agno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agno
op_eq
id|nagcount
op_minus
l_int|1
)paren
id|agsize
op_assign
id|nb
op_minus
(paren
id|agno
op_star
(paren
id|xfs_rfsblock_t
)paren
id|mp-&gt;m_sb.sb_agblocks
)paren
suffix:semicolon
r_else
id|agsize
op_assign
id|mp-&gt;m_sb.sb_agblocks
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_length
comma
id|ARCH_CONVERT
comma
id|agsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_roots
(braket
id|XFS_BTNUM_BNOi
)braket
comma
id|ARCH_CONVERT
comma
id|XFS_BNO_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_roots
(braket
id|XFS_BTNUM_CNTi
)braket
comma
id|ARCH_CONVERT
comma
id|XFS_CNT_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_levels
(braket
id|XFS_BTNUM_BNOi
)braket
comma
id|ARCH_CONVERT
comma
l_int|1
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_levels
(braket
id|XFS_BTNUM_CNTi
)braket
comma
id|ARCH_CONVERT
comma
l_int|1
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|agf-&gt;agf_flfirst
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_fllast
comma
id|ARCH_CONVERT
comma
id|XFS_AGFL_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|agf-&gt;agf_flcount
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|tmpsize
op_assign
id|agsize
op_minus
id|XFS_PREALLOC_BLOCKS
c_func
(paren
id|mp
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_freeblks
comma
id|ARCH_CONVERT
comma
id|tmpsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agf-&gt;agf_longest
comma
id|ARCH_CONVERT
comma
id|tmpsize
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * AG inode header block&n;&t;&t; */
id|disk_addr
op_assign
id|XFS_AG_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_AGI_DADDR
)paren
suffix:semicolon
id|bp
op_assign
id|xfs_buf_get
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|disk_addr
comma
id|sectbb
comma
l_int|0
)paren
suffix:semicolon
id|agi
op_assign
id|XFS_BUF_TO_AGI
c_func
(paren
id|bp
)paren
suffix:semicolon
id|memset
c_func
(paren
id|agi
comma
l_int|0
comma
id|mp-&gt;m_sb.sb_sectsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_magicnum
comma
id|ARCH_CONVERT
comma
id|XFS_AGI_MAGIC
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_versionnum
comma
id|ARCH_CONVERT
comma
id|XFS_AGI_VERSION
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_seqno
comma
id|ARCH_CONVERT
comma
id|agno
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_length
comma
id|ARCH_CONVERT
comma
id|agsize
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|agi-&gt;agi_count
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_root
comma
id|ARCH_CONVERT
comma
id|XFS_IBT_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_level
comma
id|ARCH_CONVERT
comma
l_int|1
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|agi-&gt;agi_freecount
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_newino
comma
id|ARCH_CONVERT
comma
id|NULLAGINO
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|agi-&gt;agi_dirino
comma
id|ARCH_CONVERT
comma
id|NULLAGINO
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bucket
op_assign
l_int|0
suffix:semicolon
id|bucket
OL
id|XFS_AGI_UNLINKED_BUCKETS
suffix:semicolon
id|bucket
op_increment
)paren
id|INT_SET
c_func
(paren
id|agi-&gt;agi_unlinked
(braket
id|bucket
)braket
comma
id|ARCH_CONVERT
comma
id|NULLAGINO
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * BNO btree root block&n;&t;&t; */
id|disk_addr
op_assign
id|XFS_AGB_TO_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_BNO_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|bp
op_assign
id|xfs_buf_get
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|disk_addr
comma
id|BTOBB
c_func
(paren
id|bsize
)paren
comma
l_int|0
)paren
suffix:semicolon
id|block
op_assign
id|XFS_BUF_TO_SBLOCK
c_func
(paren
id|bp
)paren
suffix:semicolon
id|memset
c_func
(paren
id|block
comma
l_int|0
comma
id|bsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_magic
comma
id|ARCH_CONVERT
comma
id|XFS_ABTB_MAGIC
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|block-&gt;bb_level
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_numrecs
comma
id|ARCH_CONVERT
comma
l_int|1
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_leftsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_rightsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|arec
op_assign
id|XFS_BTREE_REC_ADDR
c_func
(paren
id|bsize
comma
id|xfs_alloc
comma
id|block
comma
l_int|1
comma
id|mp-&gt;m_alloc_mxr
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|arec-&gt;ar_startblock
comma
id|ARCH_CONVERT
comma
id|XFS_PREALLOC_BLOCKS
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|arec-&gt;ar_blockcount
comma
id|ARCH_CONVERT
comma
id|agsize
op_minus
id|INT_GET
c_func
(paren
id|arec-&gt;ar_startblock
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * CNT btree root block&n;&t;&t; */
id|disk_addr
op_assign
id|XFS_AGB_TO_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_CNT_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|bp
op_assign
id|xfs_buf_get
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|disk_addr
comma
id|BTOBB
c_func
(paren
id|bsize
)paren
comma
l_int|0
)paren
suffix:semicolon
id|block
op_assign
id|XFS_BUF_TO_SBLOCK
c_func
(paren
id|bp
)paren
suffix:semicolon
id|memset
c_func
(paren
id|block
comma
l_int|0
comma
id|bsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_magic
comma
id|ARCH_CONVERT
comma
id|XFS_ABTC_MAGIC
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|block-&gt;bb_level
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_numrecs
comma
id|ARCH_CONVERT
comma
l_int|1
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_leftsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_rightsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|arec
op_assign
id|XFS_BTREE_REC_ADDR
c_func
(paren
id|bsize
comma
id|xfs_alloc
comma
id|block
comma
l_int|1
comma
id|mp-&gt;m_alloc_mxr
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|arec-&gt;ar_startblock
comma
id|ARCH_CONVERT
comma
id|XFS_PREALLOC_BLOCKS
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|arec-&gt;ar_blockcount
comma
id|ARCH_CONVERT
comma
id|agsize
op_minus
id|INT_GET
c_func
(paren
id|arec-&gt;ar_startblock
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|nfree
op_add_assign
id|INT_GET
c_func
(paren
id|arec-&gt;ar_blockcount
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * INO btree root block&n;&t;&t; */
id|disk_addr
op_assign
id|XFS_AGB_TO_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_IBT_BLOCK
c_func
(paren
id|mp
)paren
)paren
suffix:semicolon
id|bp
op_assign
id|xfs_buf_get
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|disk_addr
comma
id|BTOBB
c_func
(paren
id|bsize
)paren
comma
l_int|0
)paren
suffix:semicolon
id|block
op_assign
id|XFS_BUF_TO_SBLOCK
c_func
(paren
id|bp
)paren
suffix:semicolon
id|memset
c_func
(paren
id|block
comma
l_int|0
comma
id|bsize
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_magic
comma
id|ARCH_CONVERT
comma
id|XFS_IBT_MAGIC
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|block-&gt;bb_level
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_ZERO
c_func
(paren
id|block-&gt;bb_numrecs
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_leftsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|INT_SET
c_func
(paren
id|block-&gt;bb_rightsib
comma
id|ARCH_CONVERT
comma
id|NULLAGBLOCK
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
)brace
id|xfs_trans_agblocks_delta
c_func
(paren
id|tp
comma
id|nfree
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There are new blocks in the old last a.g.&n;&t; */
r_if
c_cond
(paren
r_new
)paren
(brace
multiline_comment|/*&n;&t;&t; * Change the agi length.&n;&t;&t; */
id|error
op_assign
id|xfs_ialloc_read_agi
c_func
(paren
id|mp
comma
id|tp
comma
id|agno
comma
op_amp
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|bp
)paren
suffix:semicolon
id|agi
op_assign
id|XFS_BUF_TO_AGI
c_func
(paren
id|bp
)paren
suffix:semicolon
id|INT_MOD
c_func
(paren
id|agi-&gt;agi_length
comma
id|ARCH_CONVERT
comma
r_new
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|nagcount
op_eq
id|oagcount
op_logical_or
id|INT_GET
c_func
(paren
id|agi-&gt;agi_length
comma
id|ARCH_CONVERT
)paren
op_eq
id|mp-&gt;m_sb.sb_agblocks
)paren
suffix:semicolon
id|xfs_ialloc_log_agi
c_func
(paren
id|tp
comma
id|bp
comma
id|XFS_AGI_LENGTH
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Change agf length.&n;&t;&t; */
id|error
op_assign
id|xfs_alloc_read_agf
c_func
(paren
id|mp
comma
id|tp
comma
id|agno
comma
l_int|0
comma
op_amp
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|bp
)paren
suffix:semicolon
id|agf
op_assign
id|XFS_BUF_TO_AGF
c_func
(paren
id|bp
)paren
suffix:semicolon
id|INT_MOD
c_func
(paren
id|agf-&gt;agf_length
comma
id|ARCH_CONVERT
comma
r_new
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|INT_GET
c_func
(paren
id|agf-&gt;agf_length
comma
id|ARCH_CONVERT
)paren
op_eq
id|INT_GET
c_func
(paren
id|agi-&gt;agi_length
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Free the new space.&n;&t;&t; */
id|error
op_assign
id|xfs_free_extent
c_func
(paren
id|tp
comma
id|XFS_AGB_TO_FSB
c_func
(paren
id|mp
comma
id|agno
comma
id|INT_GET
c_func
(paren
id|agf-&gt;agf_length
comma
id|ARCH_CONVERT
)paren
op_minus
r_new
)paren
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nagcount
OG
id|oagcount
)paren
id|xfs_trans_mod_sb
c_func
(paren
id|tp
comma
id|XFS_TRANS_SB_AGCOUNT
comma
id|nagcount
op_minus
id|oagcount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nb
OG
id|mp-&gt;m_sb.sb_dblocks
)paren
id|xfs_trans_mod_sb
c_func
(paren
id|tp
comma
id|XFS_TRANS_SB_DBLOCKS
comma
id|nb
op_minus
id|mp-&gt;m_sb.sb_dblocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfree
)paren
id|xfs_trans_mod_sb
c_func
(paren
id|tp
comma
id|XFS_TRANS_SB_FDBLOCKS
comma
id|nfree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dpct
)paren
id|xfs_trans_mod_sb
c_func
(paren
id|tp
comma
id|XFS_TRANS_SB_IMAXPCT
comma
id|dpct
)paren
suffix:semicolon
id|error
op_assign
id|xfs_trans_commit
c_func
(paren
id|tp
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp-&gt;m_sb.sb_imax_pct
)paren
(brace
id|__uint64_t
id|icount
op_assign
id|mp-&gt;m_sb.sb_dblocks
op_star
id|mp-&gt;m_sb.sb_imax_pct
suffix:semicolon
id|do_div
c_func
(paren
id|icount
comma
l_int|100
)paren
suffix:semicolon
id|mp-&gt;m_maxicount
op_assign
id|icount
op_lshift
id|mp-&gt;m_sb.sb_inopblog
suffix:semicolon
)brace
r_else
id|mp-&gt;m_maxicount
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|agno
op_assign
l_int|1
suffix:semicolon
id|agno
OL
id|nagcount
suffix:semicolon
id|agno
op_increment
)paren
(brace
id|error
op_assign
id|xfs_read_buf
c_func
(paren
id|mp
comma
id|mp-&gt;m_ddev_targp
comma
id|XFS_AGB_TO_DADDR
c_func
(paren
id|mp
comma
id|agno
comma
id|XFS_SB_BLOCK
c_func
(paren
id|mp
)paren
)paren
comma
id|sectbb
comma
l_int|0
comma
op_amp
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_fs_cmn_err
c_func
(paren
id|CE_WARN
comma
id|mp
comma
l_string|&quot;error %d reading secondary superblock for ag %d&quot;
comma
id|error
comma
id|agno
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sbp
op_assign
id|XFS_BUF_TO_SBP
c_func
(paren
id|bp
)paren
suffix:semicolon
id|xfs_xlatesb
c_func
(paren
id|sbp
comma
op_amp
id|mp-&gt;m_sb
comma
op_minus
l_int|1
comma
id|ARCH_CONVERT
comma
id|XFS_SB_ALL_BITS
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we get an error writing out the alternate superblocks,&n;&t;&t; * just issue a warning and continue.  The real work is&n;&t;&t; * already done and committed.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|xfs_bwrite
c_func
(paren
id|mp
comma
id|bp
)paren
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_else
(brace
id|xfs_fs_cmn_err
c_func
(paren
id|CE_WARN
comma
id|mp
comma
l_string|&quot;write error %d updating secondary superblock for ag %d&quot;
comma
id|error
comma
id|agno
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* no point in continuing */
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|error0
suffix:colon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
id|XFS_TRANS_ABORT
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|xfs_growfs_log_private
id|xfs_growfs_log_private
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
multiline_comment|/* mount point for filesystem */
id|xfs_growfs_log_t
op_star
id|in
)paren
multiline_comment|/* growfs log input struct */
(brace
id|xfs_extlen_t
id|nb
suffix:semicolon
id|nb
op_assign
id|in-&gt;newblocks
suffix:semicolon
r_if
c_cond
(paren
id|nb
OL
id|XFS_MIN_LOG_BLOCKS
op_logical_or
id|nb
OL
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
id|XFS_MIN_LOG_BYTES
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
id|mp-&gt;m_sb.sb_logblocks
op_logical_and
id|in-&gt;isint
op_eq
(paren
id|mp-&gt;m_sb.sb_logstart
op_ne
l_int|0
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Moving the log is hard, need new interfaces to sync&n;&t; * the log first, hold off all activity while moving it.&n;&t; * Can have shorter or longer log in the same space,&n;&t; * or transform internal to external log or vice versa.&n;&t; */
r_return
id|XFS_ERROR
c_func
(paren
id|ENOSYS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * protected versions of growfs function acquire and release locks on the mount&n; * point - exported through ioctls: XFS_IOC_FSGROWFSDATA, XFS_IOC_FSGROWFSLOG,&n; * XFS_IOC_FSGROWFSRT&n; */
r_int
DECL|function|xfs_growfs_data
id|xfs_growfs_data
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_growfs_data_t
op_star
id|in
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpsema
c_func
(paren
op_amp
id|mp-&gt;m_growlock
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EWOULDBLOCK
)paren
suffix:semicolon
id|error
op_assign
id|xfs_growfs_data_private
c_func
(paren
id|mp
comma
id|in
)paren
suffix:semicolon
id|vsema
c_func
(paren
op_amp
id|mp-&gt;m_growlock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_int
DECL|function|xfs_growfs_log
id|xfs_growfs_log
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_growfs_log_t
op_star
id|in
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpsema
c_func
(paren
op_amp
id|mp-&gt;m_growlock
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EWOULDBLOCK
)paren
suffix:semicolon
id|error
op_assign
id|xfs_growfs_log_private
c_func
(paren
id|mp
comma
id|in
)paren
suffix:semicolon
id|vsema
c_func
(paren
op_amp
id|mp-&gt;m_growlock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * exported through ioctl XFS_IOC_FSCOUNTS&n; */
r_int
DECL|function|xfs_fs_counts
id|xfs_fs_counts
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_fsop_counts_t
op_star
id|cnt
)paren
(brace
r_int
r_int
id|s
suffix:semicolon
id|s
op_assign
id|XFS_SB_LOCK
c_func
(paren
id|mp
)paren
suffix:semicolon
id|cnt-&gt;freedata
op_assign
id|mp-&gt;m_sb.sb_fdblocks
suffix:semicolon
id|cnt-&gt;freertx
op_assign
id|mp-&gt;m_sb.sb_frextents
suffix:semicolon
id|cnt-&gt;freeino
op_assign
id|mp-&gt;m_sb.sb_ifree
suffix:semicolon
id|cnt-&gt;allocino
op_assign
id|mp-&gt;m_sb.sb_icount
suffix:semicolon
id|XFS_SB_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * exported through ioctl XFS_IOC_SET_RESBLKS &amp; XFS_IOC_GET_RESBLKS&n; *&n; * xfs_reserve_blocks is called to set m_resblks&n; * in the in-core mount table. The number of unused reserved blocks&n; * is kept in m_resbls_avail.&n; *&n; * Reserve the requested number of blocks if available. Otherwise return&n; * as many as possible to satisfy the request. The actual number&n; * reserved are returned in outval&n; *&n; * A null inval pointer indicates that only the current reserved blocks&n; * available  should  be returned no settings are changed.&n; */
r_int
DECL|function|xfs_reserve_blocks
id|xfs_reserve_blocks
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|__uint64_t
op_star
id|inval
comma
id|xfs_fsop_resblks_t
op_star
id|outval
)paren
(brace
id|__uint64_t
id|lcounter
comma
id|delta
suffix:semicolon
id|__uint64_t
id|request
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
multiline_comment|/* If inval is null, report current values and return */
r_if
c_cond
(paren
id|inval
op_eq
(paren
id|__uint64_t
op_star
)paren
l_int|NULL
)paren
(brace
id|outval-&gt;resblks
op_assign
id|mp-&gt;m_resblks
suffix:semicolon
id|outval-&gt;resblks_avail
op_assign
id|mp-&gt;m_resblks_avail
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|request
op_assign
op_star
id|inval
suffix:semicolon
id|s
op_assign
id|XFS_SB_LOCK
c_func
(paren
id|mp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If our previous reservation was larger than the current value,&n;&t; * then move any unused blocks back to the free pool.&n;&t; */
r_if
c_cond
(paren
id|mp-&gt;m_resblks
OG
id|request
)paren
(brace
id|lcounter
op_assign
id|mp-&gt;m_resblks_avail
op_minus
id|request
suffix:semicolon
r_if
c_cond
(paren
id|lcounter
OG
l_int|0
)paren
(brace
multiline_comment|/* release unused blocks */
id|mp-&gt;m_sb.sb_fdblocks
op_add_assign
id|lcounter
suffix:semicolon
id|mp-&gt;m_resblks_avail
op_sub_assign
id|lcounter
suffix:semicolon
)brace
id|mp-&gt;m_resblks
op_assign
id|request
suffix:semicolon
)brace
r_else
(brace
id|delta
op_assign
id|request
op_minus
id|mp-&gt;m_resblks
suffix:semicolon
id|lcounter
op_assign
id|mp-&gt;m_sb.sb_fdblocks
suffix:semicolon
id|lcounter
op_sub_assign
id|delta
suffix:semicolon
r_if
c_cond
(paren
id|lcounter
OL
l_int|0
)paren
(brace
multiline_comment|/* We can&squot;t satisfy the request, just get what we can */
id|mp-&gt;m_resblks
op_add_assign
id|mp-&gt;m_sb.sb_fdblocks
suffix:semicolon
id|mp-&gt;m_resblks_avail
op_add_assign
id|mp-&gt;m_sb.sb_fdblocks
suffix:semicolon
id|mp-&gt;m_sb.sb_fdblocks
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|mp-&gt;m_sb.sb_fdblocks
op_assign
id|lcounter
suffix:semicolon
id|mp-&gt;m_resblks
op_assign
id|request
suffix:semicolon
id|mp-&gt;m_resblks_avail
op_add_assign
id|delta
suffix:semicolon
)brace
)brace
id|outval-&gt;resblks
op_assign
id|mp-&gt;m_resblks
suffix:semicolon
id|outval-&gt;resblks_avail
op_assign
id|mp-&gt;m_resblks_avail
suffix:semicolon
id|XFS_SB_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|xfs_fs_log_dummy
id|xfs_fs_log_dummy
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
id|xfs_inode_t
op_star
id|ip
suffix:semicolon
id|tp
op_assign
id|_xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_DUMMY1
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|mp-&gt;m_active_trans
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
l_int|0
comma
id|XFS_ICHANGE_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
(brace
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ip
op_assign
id|mp-&gt;m_rootip
suffix:semicolon
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ihold
c_func
(paren
id|tp
comma
id|ip
)paren
suffix:semicolon
id|xfs_trans_log_inode
c_func
(paren
id|tp
comma
id|ip
comma
id|XFS_ILOG_CORE
)paren
suffix:semicolon
id|xfs_trans_commit
c_func
(paren
id|tp
comma
id|XFS_TRANS_SYNC
comma
l_int|NULL
)paren
suffix:semicolon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
)brace
r_int
DECL|function|xfs_fs_freeze
id|xfs_fs_freeze
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|vfs_t
op_star
id|vfsp
suffix:semicolon
multiline_comment|/*REFERENCED*/
r_int
id|error
suffix:semicolon
id|vfsp
op_assign
id|XFS_MTOVFS
c_func
(paren
id|mp
)paren
suffix:semicolon
multiline_comment|/* Stop new writers */
id|xfs_start_freeze
c_func
(paren
id|mp
comma
id|XFS_FREEZE_WRITE
)paren
suffix:semicolon
multiline_comment|/* Flush delalloc and delwri data */
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|SYNC_DELWRI
op_or
id|SYNC_WAIT
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
multiline_comment|/* Pause transaction subsystem */
id|xfs_start_freeze
c_func
(paren
id|mp
comma
id|XFS_FREEZE_TRANS
)paren
suffix:semicolon
multiline_comment|/* Flush any remaining inodes into buffers */
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|SYNC_ATTR
op_or
id|SYNC_WAIT
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
multiline_comment|/* Push all buffers out to disk */
id|xfs_binval
c_func
(paren
id|mp-&gt;m_ddev_targp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;m_rtdev_targp
)paren
(brace
id|xfs_binval
c_func
(paren
id|mp-&gt;m_rtdev_targp
)paren
suffix:semicolon
)brace
multiline_comment|/* Push the superblock and write an unmount record */
id|xfs_log_unmount_write
c_func
(paren
id|mp
)paren
suffix:semicolon
id|xfs_unmountfs_writesb
c_func
(paren
id|mp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|xfs_fs_thaw
id|xfs_fs_thaw
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|xfs_finish_freeze
c_func
(paren
id|mp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
