multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DQUOT_ITEM_H__
DECL|macro|__XFS_DQUOT_ITEM_H__
mdefine_line|#define __XFS_DQUOT_ITEM_H__
multiline_comment|/*&n; * These are the structures used to lay out dquots and quotaoff&n; * records on the log. Quite similar to those of inodes.&n; */
multiline_comment|/*&n; * log format struct for dquots.&n; * The first two fields must be the type and size fitting into&n; * 32 bits : log_recovery code assumes that.&n; */
DECL|struct|xfs_dq_logformat
r_typedef
r_struct
id|xfs_dq_logformat
(brace
DECL|member|qlf_type
id|__uint16_t
id|qlf_type
suffix:semicolon
multiline_comment|/* dquot log item type */
DECL|member|qlf_size
id|__uint16_t
id|qlf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|qlf_id
id|xfs_dqid_t
id|qlf_id
suffix:semicolon
multiline_comment|/* usr/grp id number : 32 bits */
DECL|member|qlf_blkno
id|__int64_t
id|qlf_blkno
suffix:semicolon
multiline_comment|/* blkno of dquot buffer */
DECL|member|qlf_len
id|__int32_t
id|qlf_len
suffix:semicolon
multiline_comment|/* len of dquot buffer */
DECL|member|qlf_boffset
id|__uint32_t
id|qlf_boffset
suffix:semicolon
multiline_comment|/* off of dquot in buffer */
DECL|typedef|xfs_dq_logformat_t
)brace
id|xfs_dq_logformat_t
suffix:semicolon
multiline_comment|/*&n; * log format struct for QUOTAOFF records.&n; * The first two fields must be the type and size fitting into&n; * 32 bits : log_recovery code assumes that.&n; * We write two LI_QUOTAOFF logitems per quotaoff, the last one keeps a pointer&n; * to the first and ensures that the first logitem is taken out of the AIL&n; * only when the last one is securely committed.&n; */
DECL|struct|xfs_qoff_logformat
r_typedef
r_struct
id|xfs_qoff_logformat
(brace
DECL|member|qf_type
r_int
r_int
id|qf_type
suffix:semicolon
multiline_comment|/* quotaoff log item type */
DECL|member|qf_size
r_int
r_int
id|qf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|qf_flags
r_int
r_int
id|qf_flags
suffix:semicolon
multiline_comment|/* USR and/or GRP */
DECL|member|qf_pad
r_char
id|qf_pad
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* padding for future */
DECL|typedef|xfs_qoff_logformat_t
)brace
id|xfs_qoff_logformat_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|xfs_dquot
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
DECL|struct|xfs_dq_logitem
r_typedef
r_struct
id|xfs_dq_logitem
(brace
DECL|member|qli_item
id|xfs_log_item_t
id|qli_item
suffix:semicolon
multiline_comment|/* common portion */
DECL|member|qli_dquot
r_struct
id|xfs_dquot
op_star
id|qli_dquot
suffix:semicolon
multiline_comment|/* dquot ptr */
DECL|member|qli_flush_lsn
id|xfs_lsn_t
id|qli_flush_lsn
suffix:semicolon
multiline_comment|/* lsn at last flush */
DECL|member|qli_pushbuf_flag
r_int
r_int
id|qli_pushbuf_flag
suffix:semicolon
multiline_comment|/* one bit used in push_ail */
macro_line|#ifdef DEBUG
DECL|member|qli_push_owner
r_uint64
id|qli_push_owner
suffix:semicolon
macro_line|#endif
DECL|member|qli_format
id|xfs_dq_logformat_t
id|qli_format
suffix:semicolon
multiline_comment|/* logged structure */
DECL|typedef|xfs_dq_logitem_t
)brace
id|xfs_dq_logitem_t
suffix:semicolon
DECL|struct|xfs_qoff_logitem
r_typedef
r_struct
id|xfs_qoff_logitem
(brace
DECL|member|qql_item
id|xfs_log_item_t
id|qql_item
suffix:semicolon
multiline_comment|/* common portion */
DECL|member|qql_start_lip
r_struct
id|xfs_qoff_logitem
op_star
id|qql_start_lip
suffix:semicolon
multiline_comment|/* qoff-start logitem, if any */
DECL|member|qql_format
id|xfs_qoff_logformat_t
id|qql_format
suffix:semicolon
multiline_comment|/* logged structure */
DECL|typedef|xfs_qoff_logitem_t
)brace
id|xfs_qoff_logitem_t
suffix:semicolon
r_extern
r_void
id|xfs_qm_dquot_logitem_init
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
id|xfs_qoff_logitem_t
op_star
id|xfs_qm_qoff_logitem_init
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_qoff_logitem_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
id|xfs_qoff_logitem_t
op_star
id|xfs_trans_get_qoff_item
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_qoff_logitem_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_log_quotaoff_item
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_qoff_logitem_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_DQUOT_ITEM_H__ */
eof
