multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_LOG_RECOVER_H__
DECL|macro|__XFS_LOG_RECOVER_H__
mdefine_line|#define __XFS_LOG_RECOVER_H__
multiline_comment|/*&n; * Macros, structures, prototypes for internal log manager use.&n; */
DECL|macro|XLOG_RHASH_BITS
mdefine_line|#define XLOG_RHASH_BITS&t; 4
DECL|macro|XLOG_RHASH_SIZE
mdefine_line|#define XLOG_RHASH_SIZE 16
DECL|macro|XLOG_RHASH_SHIFT
mdefine_line|#define XLOG_RHASH_SHIFT 2
DECL|macro|XLOG_RHASH
mdefine_line|#define XLOG_RHASH(tid) &bslash;&n;&t;((((__uint32_t)tid)&gt;&gt;XLOG_RHASH_SHIFT) &amp; (XLOG_RHASH_SIZE-1))
DECL|macro|XLOG_MAX_REGIONS_IN_ITEM
mdefine_line|#define XLOG_MAX_REGIONS_IN_ITEM   (XFS_MAX_BLOCKSIZE / XFS_BLI_CHUNK / 2 + 1)
multiline_comment|/*&n; * item headers are in ri_buf[0].  Additional buffers follow.&n; */
DECL|struct|xlog_recover_item
r_typedef
r_struct
id|xlog_recover_item
(brace
DECL|member|ri_next
r_struct
id|xlog_recover_item
op_star
id|ri_next
suffix:semicolon
DECL|member|ri_prev
r_struct
id|xlog_recover_item
op_star
id|ri_prev
suffix:semicolon
DECL|member|ri_type
r_int
id|ri_type
suffix:semicolon
DECL|member|ri_cnt
r_int
id|ri_cnt
suffix:semicolon
multiline_comment|/* count of regions found */
DECL|member|ri_total
r_int
id|ri_total
suffix:semicolon
multiline_comment|/* total regions */
DECL|member|ri_buf
id|xfs_log_iovec_t
op_star
id|ri_buf
suffix:semicolon
multiline_comment|/* ptr to regions buffer */
DECL|typedef|xlog_recover_item_t
)brace
id|xlog_recover_item_t
suffix:semicolon
r_struct
id|xlog_tid
suffix:semicolon
DECL|struct|xlog_recover
r_typedef
r_struct
id|xlog_recover
(brace
DECL|member|r_next
r_struct
id|xlog_recover
op_star
id|r_next
suffix:semicolon
DECL|member|r_log_tid
id|xlog_tid_t
id|r_log_tid
suffix:semicolon
multiline_comment|/* log&squot;s transaction id */
DECL|member|r_theader
id|xfs_trans_header_t
id|r_theader
suffix:semicolon
multiline_comment|/* trans header for partial */
DECL|member|r_state
r_int
id|r_state
suffix:semicolon
multiline_comment|/* not needed */
DECL|member|r_lsn
id|xfs_lsn_t
id|r_lsn
suffix:semicolon
multiline_comment|/* xact lsn */
DECL|member|r_itemq
id|xlog_recover_item_t
op_star
id|r_itemq
suffix:semicolon
multiline_comment|/* q for items */
DECL|typedef|xlog_recover_t
)brace
id|xlog_recover_t
suffix:semicolon
DECL|macro|ITEM_TYPE
mdefine_line|#define ITEM_TYPE(i)&t;(*(ushort *)(i)-&gt;ri_buf[0].i_addr)
multiline_comment|/*&n; * This is the number of entries in the l_buf_cancel_table used during&n; * recovery.&n; */
DECL|macro|XLOG_BC_TABLE_SIZE
mdefine_line|#define XLOG_BC_TABLE_SIZE&t;64
DECL|macro|XLOG_RECOVER_PASS1
mdefine_line|#define XLOG_RECOVER_PASS1&t;1
DECL|macro|XLOG_RECOVER_PASS2
mdefine_line|#define XLOG_RECOVER_PASS2&t;2
macro_line|#endif&t;/* __XFS_LOG_RECOVER_H__ */
eof
