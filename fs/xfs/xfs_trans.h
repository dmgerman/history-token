multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef&t;__XFS_TRANS_H__
DECL|macro|__XFS_TRANS_H__
mdefine_line|#define&t;__XFS_TRANS_H__
multiline_comment|/*&n; * This is the structure written in the log at the head of&n; * every transaction. It identifies the type and id of the&n; * transaction, and contains the number of items logged by&n; * the transaction so we know how many to expect during recovery.&n; *&n; * Do not change the below structure without redoing the code in&n; * xlog_recover_add_to_trans() and xlog_recover_add_to_cont_trans().&n; */
DECL|struct|xfs_trans_header
r_typedef
r_struct
id|xfs_trans_header
(brace
DECL|member|th_magic
id|uint
id|th_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|th_type
id|uint
id|th_type
suffix:semicolon
multiline_comment|/* transaction type */
DECL|member|th_tid
id|__int32_t
id|th_tid
suffix:semicolon
multiline_comment|/* transaction id (unused) */
DECL|member|th_num_items
id|uint
id|th_num_items
suffix:semicolon
multiline_comment|/* num items logged by trans */
DECL|typedef|xfs_trans_header_t
)brace
id|xfs_trans_header_t
suffix:semicolon
DECL|macro|XFS_TRANS_HEADER_MAGIC
mdefine_line|#define&t;XFS_TRANS_HEADER_MAGIC&t;0x5452414e&t;/* TRAN */
multiline_comment|/*&n; * Log item types.&n; */
DECL|macro|XFS_LI_5_3_BUF
mdefine_line|#define&t;XFS_LI_5_3_BUF&t;&t;0x1234&t;/* v1 bufs, 1-block inode buffers */
DECL|macro|XFS_LI_5_3_INODE
mdefine_line|#define&t;XFS_LI_5_3_INODE&t;0x1235&t;/* 1-block inode buffers */
DECL|macro|XFS_LI_EFI
mdefine_line|#define&t;XFS_LI_EFI&t;&t;0x1236
DECL|macro|XFS_LI_EFD
mdefine_line|#define&t;XFS_LI_EFD&t;&t;0x1237
DECL|macro|XFS_LI_IUNLINK
mdefine_line|#define&t;XFS_LI_IUNLINK&t;&t;0x1238
DECL|macro|XFS_LI_6_1_INODE
mdefine_line|#define&t;XFS_LI_6_1_INODE&t;0x1239&t;/* 4K non-aligned inode bufs */
DECL|macro|XFS_LI_6_1_BUF
mdefine_line|#define&t;XFS_LI_6_1_BUF&t;&t;0x123a&t;/* v1, 4K inode buffers */
DECL|macro|XFS_LI_INODE
mdefine_line|#define&t;XFS_LI_INODE&t;&t;0x123b&t;/* aligned ino chunks, var-size ibufs */
DECL|macro|XFS_LI_BUF
mdefine_line|#define&t;XFS_LI_BUF&t;&t;0x123c&t;/* v2 bufs, variable sized inode bufs */
DECL|macro|XFS_LI_DQUOT
mdefine_line|#define&t;XFS_LI_DQUOT&t;&t;0x123d
DECL|macro|XFS_LI_QUOTAOFF
mdefine_line|#define&t;XFS_LI_QUOTAOFF&t;&t;0x123e
multiline_comment|/*&n; * Transaction types.  Used to distinguish types of buffers.&n; */
DECL|macro|XFS_TRANS_SETATTR_NOT_SIZE
mdefine_line|#define XFS_TRANS_SETATTR_NOT_SIZE&t;1
DECL|macro|XFS_TRANS_SETATTR_SIZE
mdefine_line|#define XFS_TRANS_SETATTR_SIZE&t;&t;2
DECL|macro|XFS_TRANS_INACTIVE
mdefine_line|#define XFS_TRANS_INACTIVE&t;&t;3
DECL|macro|XFS_TRANS_CREATE
mdefine_line|#define XFS_TRANS_CREATE&t;&t;4
DECL|macro|XFS_TRANS_CREATE_TRUNC
mdefine_line|#define XFS_TRANS_CREATE_TRUNC&t;&t;5
DECL|macro|XFS_TRANS_TRUNCATE_FILE
mdefine_line|#define XFS_TRANS_TRUNCATE_FILE&t;&t;6
DECL|macro|XFS_TRANS_REMOVE
mdefine_line|#define XFS_TRANS_REMOVE&t;&t;7
DECL|macro|XFS_TRANS_LINK
mdefine_line|#define XFS_TRANS_LINK&t;&t;&t;8
DECL|macro|XFS_TRANS_RENAME
mdefine_line|#define XFS_TRANS_RENAME&t;&t;9
DECL|macro|XFS_TRANS_MKDIR
mdefine_line|#define XFS_TRANS_MKDIR&t;&t;&t;10
DECL|macro|XFS_TRANS_RMDIR
mdefine_line|#define XFS_TRANS_RMDIR&t;&t;&t;11
DECL|macro|XFS_TRANS_SYMLINK
mdefine_line|#define XFS_TRANS_SYMLINK&t;&t;12
DECL|macro|XFS_TRANS_SET_DMATTRS
mdefine_line|#define XFS_TRANS_SET_DMATTRS&t;&t;13
DECL|macro|XFS_TRANS_GROWFS
mdefine_line|#define XFS_TRANS_GROWFS&t;&t;14
DECL|macro|XFS_TRANS_STRAT_WRITE
mdefine_line|#define XFS_TRANS_STRAT_WRITE&t;&t;15
DECL|macro|XFS_TRANS_DIOSTRAT
mdefine_line|#define XFS_TRANS_DIOSTRAT&t;&t;16
DECL|macro|XFS_TRANS_WRITE_SYNC
mdefine_line|#define&t;XFS_TRANS_WRITE_SYNC&t;&t;17
DECL|macro|XFS_TRANS_WRITEID
mdefine_line|#define&t;XFS_TRANS_WRITEID&t;&t;18
DECL|macro|XFS_TRANS_ADDAFORK
mdefine_line|#define&t;XFS_TRANS_ADDAFORK&t;&t;19
DECL|macro|XFS_TRANS_ATTRINVAL
mdefine_line|#define&t;XFS_TRANS_ATTRINVAL&t;&t;20
DECL|macro|XFS_TRANS_ATRUNCATE
mdefine_line|#define&t;XFS_TRANS_ATRUNCATE&t;&t;21
DECL|macro|XFS_TRANS_ATTR_SET
mdefine_line|#define&t;XFS_TRANS_ATTR_SET&t;&t;22
DECL|macro|XFS_TRANS_ATTR_RM
mdefine_line|#define&t;XFS_TRANS_ATTR_RM&t;&t;23
DECL|macro|XFS_TRANS_ATTR_FLAG
mdefine_line|#define&t;XFS_TRANS_ATTR_FLAG&t;&t;24
DECL|macro|XFS_TRANS_CLEAR_AGI_BUCKET
mdefine_line|#define&t;XFS_TRANS_CLEAR_AGI_BUCKET&t;25
DECL|macro|XFS_TRANS_QM_SBCHANGE
mdefine_line|#define XFS_TRANS_QM_SBCHANGE&t;&t;26
multiline_comment|/*&n; * Dummy entries since we use the transaction type to index into the&n; * trans_type[] in xlog_recover_print_trans_head()&n; */
DECL|macro|XFS_TRANS_DUMMY1
mdefine_line|#define XFS_TRANS_DUMMY1&t;&t;27
DECL|macro|XFS_TRANS_DUMMY2
mdefine_line|#define XFS_TRANS_DUMMY2&t;&t;28
DECL|macro|XFS_TRANS_QM_QUOTAOFF
mdefine_line|#define XFS_TRANS_QM_QUOTAOFF&t;&t;29
DECL|macro|XFS_TRANS_QM_DQALLOC
mdefine_line|#define XFS_TRANS_QM_DQALLOC&t;&t;30
DECL|macro|XFS_TRANS_QM_SETQLIM
mdefine_line|#define XFS_TRANS_QM_SETQLIM&t;&t;31
DECL|macro|XFS_TRANS_QM_DQCLUSTER
mdefine_line|#define XFS_TRANS_QM_DQCLUSTER&t;&t;32
DECL|macro|XFS_TRANS_QM_QINOCREATE
mdefine_line|#define XFS_TRANS_QM_QINOCREATE&t;&t;33
DECL|macro|XFS_TRANS_QM_QUOTAOFF_END
mdefine_line|#define XFS_TRANS_QM_QUOTAOFF_END&t;34
DECL|macro|XFS_TRANS_SB_UNIT
mdefine_line|#define XFS_TRANS_SB_UNIT&t;&t;35
DECL|macro|XFS_TRANS_FSYNC_TS
mdefine_line|#define XFS_TRANS_FSYNC_TS&t;&t;36
DECL|macro|XFS_TRANS_GROWFSRT_ALLOC
mdefine_line|#define&t;XFS_TRANS_GROWFSRT_ALLOC&t;37
DECL|macro|XFS_TRANS_GROWFSRT_ZERO
mdefine_line|#define&t;XFS_TRANS_GROWFSRT_ZERO&t;&t;38
DECL|macro|XFS_TRANS_GROWFSRT_FREE
mdefine_line|#define&t;XFS_TRANS_GROWFSRT_FREE&t;&t;39
DECL|macro|XFS_TRANS_SWAPEXT
mdefine_line|#define&t;XFS_TRANS_SWAPEXT&t;&t;40
multiline_comment|/* new transaction types need to be reflected in xfs_logprint(8) */
macro_line|#ifdef __KERNEL__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_buftarg
suffix:semicolon
r_struct
id|xfs_efd_log_item
suffix:semicolon
r_struct
id|xfs_efi_log_item
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_item_ops
suffix:semicolon
r_struct
id|xfs_log_iovec
suffix:semicolon
r_struct
id|xfs_log_item
suffix:semicolon
r_struct
id|xfs_log_item_desc
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_struct
id|xfs_dquot_acct
suffix:semicolon
DECL|struct|xfs_ail_entry
r_typedef
r_struct
id|xfs_ail_entry
(brace
DECL|member|ail_forw
r_struct
id|xfs_log_item
op_star
id|ail_forw
suffix:semicolon
multiline_comment|/* AIL forw pointer */
DECL|member|ail_back
r_struct
id|xfs_log_item
op_star
id|ail_back
suffix:semicolon
multiline_comment|/* AIL back pointer */
DECL|typedef|xfs_ail_entry_t
)brace
id|xfs_ail_entry_t
suffix:semicolon
multiline_comment|/*&n; * This structure is passed as a parameter to xfs_trans_push_ail()&n; * and is used to track the what LSN the waiting processes are&n; * waiting to become unused.&n; */
DECL|struct|xfs_ail_ticket
r_typedef
r_struct
id|xfs_ail_ticket
(brace
DECL|member|at_lsn
id|xfs_lsn_t
id|at_lsn
suffix:semicolon
multiline_comment|/* lsn waitin for */
DECL|member|at_forw
r_struct
id|xfs_ail_ticket
op_star
id|at_forw
suffix:semicolon
multiline_comment|/* wait list ptr */
DECL|member|at_back
r_struct
id|xfs_ail_ticket
op_star
id|at_back
suffix:semicolon
multiline_comment|/* wait list ptr */
DECL|member|at_sema
id|sv_t
id|at_sema
suffix:semicolon
multiline_comment|/* wait sema */
DECL|typedef|xfs_ail_ticket_t
)brace
id|xfs_ail_ticket_t
suffix:semicolon
DECL|struct|xfs_log_item
r_typedef
r_struct
id|xfs_log_item
(brace
DECL|member|li_ail
id|xfs_ail_entry_t
id|li_ail
suffix:semicolon
multiline_comment|/* AIL pointers */
DECL|member|li_lsn
id|xfs_lsn_t
id|li_lsn
suffix:semicolon
multiline_comment|/* last on-disk lsn */
DECL|member|li_desc
r_struct
id|xfs_log_item_desc
op_star
id|li_desc
suffix:semicolon
multiline_comment|/* ptr to current desc*/
DECL|member|li_mountp
r_struct
id|xfs_mount
op_star
id|li_mountp
suffix:semicolon
multiline_comment|/* ptr to fs mount */
DECL|member|li_type
id|uint
id|li_type
suffix:semicolon
multiline_comment|/* item type */
DECL|member|li_flags
id|uint
id|li_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|li_bio_list
r_struct
id|xfs_log_item
op_star
id|li_bio_list
suffix:semicolon
multiline_comment|/* buffer item list */
DECL|member|li_cb
r_void
(paren
op_star
id|li_cb
)paren
(paren
r_struct
id|xfs_buf
op_star
comma
r_struct
id|xfs_log_item
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer item iodone */
multiline_comment|/* callback func */
DECL|member|li_ops
r_struct
id|xfs_item_ops
op_star
id|li_ops
suffix:semicolon
multiline_comment|/* function list */
DECL|typedef|xfs_log_item_t
)brace
id|xfs_log_item_t
suffix:semicolon
DECL|macro|XFS_LI_IN_AIL
mdefine_line|#define&t;XFS_LI_IN_AIL&t;0x1
DECL|macro|XFS_LI_ABORTED
mdefine_line|#define XFS_LI_ABORTED&t;0x2
DECL|struct|xfs_item_ops
r_typedef
r_struct
id|xfs_item_ops
(brace
DECL|member|iop_size
id|uint
(paren
op_star
id|iop_size
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_format
r_void
(paren
op_star
id|iop_format
)paren
(paren
id|xfs_log_item_t
op_star
comma
r_struct
id|xfs_log_iovec
op_star
)paren
suffix:semicolon
DECL|member|iop_pin
r_void
(paren
op_star
id|iop_pin
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_unpin
r_void
(paren
op_star
id|iop_unpin
)paren
(paren
id|xfs_log_item_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|iop_unpin_remove
r_void
(paren
op_star
id|iop_unpin_remove
)paren
(paren
id|xfs_log_item_t
op_star
comma
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
DECL|member|iop_trylock
id|uint
(paren
op_star
id|iop_trylock
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_unlock
r_void
(paren
op_star
id|iop_unlock
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_committed
id|xfs_lsn_t
(paren
op_star
id|iop_committed
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
suffix:semicolon
DECL|member|iop_push
r_void
(paren
op_star
id|iop_push
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_abort
r_void
(paren
op_star
id|iop_abort
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_pushbuf
r_void
(paren
op_star
id|iop_pushbuf
)paren
(paren
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
DECL|member|iop_committing
r_void
(paren
op_star
id|iop_committing
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
suffix:semicolon
DECL|typedef|xfs_item_ops_t
)brace
id|xfs_item_ops_t
suffix:semicolon
DECL|macro|IOP_SIZE
mdefine_line|#define IOP_SIZE(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_size)(ip)
DECL|macro|IOP_FORMAT
mdefine_line|#define IOP_FORMAT(ip,vp)&t;(*(ip)-&gt;li_ops-&gt;iop_format)(ip, vp)
DECL|macro|IOP_PIN
mdefine_line|#define IOP_PIN(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_pin)(ip)
DECL|macro|IOP_UNPIN
mdefine_line|#define IOP_UNPIN(ip, flags)&t;(*(ip)-&gt;li_ops-&gt;iop_unpin)(ip, flags)
DECL|macro|IOP_UNPIN_REMOVE
mdefine_line|#define IOP_UNPIN_REMOVE(ip,tp) (*(ip)-&gt;li_ops-&gt;iop_unpin_remove)(ip, tp)
DECL|macro|IOP_TRYLOCK
mdefine_line|#define IOP_TRYLOCK(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_trylock)(ip)
DECL|macro|IOP_UNLOCK
mdefine_line|#define IOP_UNLOCK(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_unlock)(ip)
DECL|macro|IOP_COMMITTED
mdefine_line|#define IOP_COMMITTED(ip, lsn)&t;(*(ip)-&gt;li_ops-&gt;iop_committed)(ip, lsn)
DECL|macro|IOP_PUSH
mdefine_line|#define IOP_PUSH(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_push)(ip)
DECL|macro|IOP_ABORT
mdefine_line|#define IOP_ABORT(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_abort)(ip)
DECL|macro|IOP_PUSHBUF
mdefine_line|#define IOP_PUSHBUF(ip)&t;&t;(*(ip)-&gt;li_ops-&gt;iop_pushbuf)(ip)
DECL|macro|IOP_COMMITTING
mdefine_line|#define IOP_COMMITTING(ip, lsn) (*(ip)-&gt;li_ops-&gt;iop_committing)(ip, lsn)
multiline_comment|/*&n; * Return values for the IOP_TRYLOCK() routines.&n; */
DECL|macro|XFS_ITEM_SUCCESS
mdefine_line|#define&t;XFS_ITEM_SUCCESS&t;0
DECL|macro|XFS_ITEM_PINNED
mdefine_line|#define&t;XFS_ITEM_PINNED&t;&t;1
DECL|macro|XFS_ITEM_LOCKED
mdefine_line|#define&t;XFS_ITEM_LOCKED&t;&t;2
DECL|macro|XFS_ITEM_FLUSHING
mdefine_line|#define&t;XFS_ITEM_FLUSHING&t;3
DECL|macro|XFS_ITEM_PUSHBUF
mdefine_line|#define XFS_ITEM_PUSHBUF&t;4
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * This structure is used to track log items associated with&n; * a transaction.  It points to the log item and keeps some&n; * flags to track the state of the log item.  It also tracks&n; * the amount of space needed to log the item it describes&n; * once we get to commit processing (see xfs_trans_commit()).&n; */
DECL|struct|xfs_log_item_desc
r_typedef
r_struct
id|xfs_log_item_desc
(brace
DECL|member|lid_item
id|xfs_log_item_t
op_star
id|lid_item
suffix:semicolon
DECL|member|lid_size
id|ushort
id|lid_size
suffix:semicolon
DECL|member|lid_flags
r_int
r_char
id|lid_flags
suffix:semicolon
DECL|member|lid_index
r_int
r_char
id|lid_index
suffix:semicolon
DECL|typedef|xfs_log_item_desc_t
)brace
id|xfs_log_item_desc_t
suffix:semicolon
DECL|macro|XFS_LID_DIRTY
mdefine_line|#define XFS_LID_DIRTY&t;&t;0x1
DECL|macro|XFS_LID_PINNED
mdefine_line|#define XFS_LID_PINNED&t;&t;0x2
DECL|macro|XFS_LID_BUF_STALE
mdefine_line|#define XFS_LID_BUF_STALE&t;0x8
multiline_comment|/*&n; * This structure is used to maintain a chunk list of log_item_desc&n; * structures. The free field is a bitmask indicating which descriptors&n; * in this chunk&squot;s array are free.  The unused field is the first value&n; * not used since this chunk was allocated.&n; */
DECL|macro|XFS_LIC_NUM_SLOTS
mdefine_line|#define&t;XFS_LIC_NUM_SLOTS&t;15
DECL|struct|xfs_log_item_chunk
r_typedef
r_struct
id|xfs_log_item_chunk
(brace
DECL|member|lic_next
r_struct
id|xfs_log_item_chunk
op_star
id|lic_next
suffix:semicolon
DECL|member|lic_free
id|ushort
id|lic_free
suffix:semicolon
DECL|member|lic_unused
id|ushort
id|lic_unused
suffix:semicolon
DECL|member|lic_descs
id|xfs_log_item_desc_t
id|lic_descs
(braket
id|XFS_LIC_NUM_SLOTS
)braket
suffix:semicolon
DECL|typedef|xfs_log_item_chunk_t
)brace
id|xfs_log_item_chunk_t
suffix:semicolon
DECL|macro|XFS_LIC_MAX_SLOT
mdefine_line|#define&t;XFS_LIC_MAX_SLOT&t;(XFS_LIC_NUM_SLOTS - 1)
DECL|macro|XFS_LIC_FREEMASK
mdefine_line|#define&t;XFS_LIC_FREEMASK&t;((1 &lt;&lt; XFS_LIC_NUM_SLOTS) - 1)
multiline_comment|/*&n; * Initialize the given chunk.  Set the chunk&squot;s free descriptor mask&n; * to indicate that all descriptors are free.  The caller gets to set&n; * lic_unused to the right value (0 matches all free).  The&n; * lic_descs.lid_index values are set up as each desc is allocated.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_INIT)
r_void
id|xfs_lic_init
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_INIT
mdefine_line|#define&t;XFS_LIC_INIT(cp)&t;xfs_lic_init(cp)
macro_line|#else
DECL|macro|XFS_LIC_INIT
mdefine_line|#define&t;XFS_LIC_INIT(cp)&t;((cp)-&gt;lic_free = XFS_LIC_FREEMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_INIT_SLOT)
r_void
id|xfs_lic_init_slot
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|macro|XFS_LIC_INIT_SLOT
mdefine_line|#define&t;XFS_LIC_INIT_SLOT(cp,slot)&t;xfs_lic_init_slot(cp, slot)
macro_line|#else
DECL|macro|XFS_LIC_INIT_SLOT
mdefine_line|#define&t;XFS_LIC_INIT_SLOT(cp,slot)&t;&bslash;&n;&t;((cp)-&gt;lic_descs[slot].lid_index = (unsigned char)(slot))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_VACANCY)
r_int
id|xfs_lic_vacancy
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_VACANCY
mdefine_line|#define&t;XFS_LIC_VACANCY(cp)&t;&t;xfs_lic_vacancy(cp)
macro_line|#else
DECL|macro|XFS_LIC_VACANCY
mdefine_line|#define&t;XFS_LIC_VACANCY(cp)&t;&t;(((cp)-&gt;lic_free) &amp; XFS_LIC_FREEMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_ALL_FREE)
r_void
id|xfs_lic_all_free
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_ALL_FREE
mdefine_line|#define&t;XFS_LIC_ALL_FREE(cp)&t;&t;xfs_lic_all_free(cp)
macro_line|#else
DECL|macro|XFS_LIC_ALL_FREE
mdefine_line|#define&t;XFS_LIC_ALL_FREE(cp)&t;&t;((cp)-&gt;lic_free = XFS_LIC_FREEMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_ARE_ALL_FREE)
r_int
id|xfs_lic_are_all_free
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_ARE_ALL_FREE
mdefine_line|#define&t;XFS_LIC_ARE_ALL_FREE(cp)&t;xfs_lic_are_all_free(cp)
macro_line|#else
DECL|macro|XFS_LIC_ARE_ALL_FREE
mdefine_line|#define&t;XFS_LIC_ARE_ALL_FREE(cp)&t;(((cp)-&gt;lic_free &amp; XFS_LIC_FREEMASK) ==&bslash;&n;&t;&t;&t;&t;&t;XFS_LIC_FREEMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_ISFREE)
r_int
id|xfs_lic_isfree
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|macro|XFS_LIC_ISFREE
mdefine_line|#define&t;XFS_LIC_ISFREE(cp,slot)&t;xfs_lic_isfree(cp,slot)
macro_line|#else
DECL|macro|XFS_LIC_ISFREE
mdefine_line|#define&t;XFS_LIC_ISFREE(cp,slot)&t;((cp)-&gt;lic_free &amp; (1 &lt;&lt; (slot)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_CLAIM)
r_void
id|xfs_lic_claim
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|macro|XFS_LIC_CLAIM
mdefine_line|#define&t;XFS_LIC_CLAIM(cp,slot)&t;&t;xfs_lic_claim(cp,slot)
macro_line|#else
DECL|macro|XFS_LIC_CLAIM
mdefine_line|#define&t;XFS_LIC_CLAIM(cp,slot)&t;&t;((cp)-&gt;lic_free &amp;= ~(1 &lt;&lt; (slot)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_RELSE)
r_void
id|xfs_lic_relse
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|macro|XFS_LIC_RELSE
mdefine_line|#define&t;XFS_LIC_RELSE(cp,slot)&t;&t;xfs_lic_relse(cp,slot)
macro_line|#else
DECL|macro|XFS_LIC_RELSE
mdefine_line|#define&t;XFS_LIC_RELSE(cp,slot)&t;&t;((cp)-&gt;lic_free |= 1 &lt;&lt; (slot))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_SLOT)
id|xfs_log_item_desc_t
op_star
id|xfs_lic_slot
c_func
(paren
id|xfs_log_item_chunk_t
op_star
id|cp
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|macro|XFS_LIC_SLOT
mdefine_line|#define&t;XFS_LIC_SLOT(cp,slot)&t;&t;xfs_lic_slot(cp,slot)
macro_line|#else
DECL|macro|XFS_LIC_SLOT
mdefine_line|#define&t;XFS_LIC_SLOT(cp,slot)&t;&t;(&amp;((cp)-&gt;lic_descs[slot]))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_DESC_TO_SLOT)
r_int
id|xfs_lic_desc_to_slot
c_func
(paren
id|xfs_log_item_desc_t
op_star
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_DESC_TO_SLOT
mdefine_line|#define&t;XFS_LIC_DESC_TO_SLOT(dp)&t;xfs_lic_desc_to_slot(dp)
macro_line|#else
DECL|macro|XFS_LIC_DESC_TO_SLOT
mdefine_line|#define&t;XFS_LIC_DESC_TO_SLOT(dp)&t;((uint)((dp)-&gt;lid_index))
macro_line|#endif
multiline_comment|/*&n; * Calculate the address of a chunk given a descriptor pointer:&n; * dp - dp-&gt;lid_index give the address of the start of the lic_descs array.&n; * From this we subtract the offset of the lic_descs field in a chunk.&n; * All of this yields the address of the chunk, which is&n; * cast to a chunk pointer.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LIC_DESC_TO_CHUNK)
id|xfs_log_item_chunk_t
op_star
id|xfs_lic_desc_to_chunk
c_func
(paren
id|xfs_log_item_desc_t
op_star
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_LIC_DESC_TO_CHUNK
mdefine_line|#define&t;XFS_LIC_DESC_TO_CHUNK(dp)&t;xfs_lic_desc_to_chunk(dp)
macro_line|#else
DECL|macro|XFS_LIC_DESC_TO_CHUNK
mdefine_line|#define&t;XFS_LIC_DESC_TO_CHUNK(dp)&t;((xfs_log_item_chunk_t*) &bslash;&n;&t;&t;&t;&t;&t;(((xfs_caddr_t)((dp) - (dp)-&gt;lid_index)) -&bslash;&n;&t;&t;&t;&t;&t;(xfs_caddr_t)(((xfs_log_item_chunk_t*) &bslash;&n;&t;&t;&t;&t;&t;0)-&gt;lic_descs)))
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This structure is used to maintain a list of block ranges that have been&n; * freed in the transaction.  The ranges are listed in the perag[] busy list&n; * between when they&squot;re freed and the transaction is committed to disk.&n; */
DECL|struct|xfs_log_busy_slot
r_typedef
r_struct
id|xfs_log_busy_slot
(brace
DECL|member|lbc_ag
id|xfs_agnumber_t
id|lbc_ag
suffix:semicolon
DECL|member|lbc_idx
id|ushort
id|lbc_idx
suffix:semicolon
multiline_comment|/* index in perag.busy[] */
DECL|typedef|xfs_log_busy_slot_t
)brace
id|xfs_log_busy_slot_t
suffix:semicolon
DECL|macro|XFS_LBC_NUM_SLOTS
mdefine_line|#define XFS_LBC_NUM_SLOTS&t;31
DECL|struct|xfs_log_busy_chunk
r_typedef
r_struct
id|xfs_log_busy_chunk
(brace
DECL|member|lbc_next
r_struct
id|xfs_log_busy_chunk
op_star
id|lbc_next
suffix:semicolon
DECL|member|lbc_free
id|uint
id|lbc_free
suffix:semicolon
multiline_comment|/* bitmask of free slots */
DECL|member|lbc_unused
id|ushort
id|lbc_unused
suffix:semicolon
multiline_comment|/* first unused */
DECL|member|lbc_busy
id|xfs_log_busy_slot_t
id|lbc_busy
(braket
id|XFS_LBC_NUM_SLOTS
)braket
suffix:semicolon
DECL|typedef|xfs_log_busy_chunk_t
)brace
id|xfs_log_busy_chunk_t
suffix:semicolon
DECL|macro|XFS_LBC_MAX_SLOT
mdefine_line|#define&t;XFS_LBC_MAX_SLOT&t;(XFS_LBC_NUM_SLOTS - 1)
DECL|macro|XFS_LBC_FREEMASK
mdefine_line|#define&t;XFS_LBC_FREEMASK&t;((1U &lt;&lt; XFS_LBC_NUM_SLOTS) - 1)
DECL|macro|XFS_LBC_INIT
mdefine_line|#define&t;XFS_LBC_INIT(cp)&t;((cp)-&gt;lbc_free = XFS_LBC_FREEMASK)
DECL|macro|XFS_LBC_CLAIM
mdefine_line|#define&t;XFS_LBC_CLAIM(cp, slot)&t;((cp)-&gt;lbc_free &amp;= ~(1 &lt;&lt; (slot)))
DECL|macro|XFS_LBC_SLOT
mdefine_line|#define&t;XFS_LBC_SLOT(cp, slot)&t;(&amp;((cp)-&gt;lbc_busy[(slot)]))
DECL|macro|XFS_LBC_VACANCY
mdefine_line|#define&t;XFS_LBC_VACANCY(cp)&t;(((cp)-&gt;lbc_free) &amp; XFS_LBC_FREEMASK)
DECL|macro|XFS_LBC_ISFREE
mdefine_line|#define&t;XFS_LBC_ISFREE(cp, slot) ((cp)-&gt;lbc_free &amp; (1 &lt;&lt; (slot)))
multiline_comment|/*&n; * This is the type of function which can be given to xfs_trans_callback()&n; * to be called upon the transaction&squot;s commit to disk.&n; */
DECL|typedef|xfs_trans_callback_t
r_typedef
r_void
(paren
op_star
id|xfs_trans_callback_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the structure maintained for every active transaction.&n; */
DECL|struct|xfs_trans
r_typedef
r_struct
id|xfs_trans
(brace
DECL|member|t_magic
r_int
r_int
id|t_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|t_logcb
id|xfs_log_callback_t
id|t_logcb
suffix:semicolon
multiline_comment|/* log callback struct */
DECL|member|t_forw
r_struct
id|xfs_trans
op_star
id|t_forw
suffix:semicolon
multiline_comment|/* async list pointers */
DECL|member|t_back
r_struct
id|xfs_trans
op_star
id|t_back
suffix:semicolon
multiline_comment|/* async list pointers */
DECL|member|t_type
r_int
r_int
id|t_type
suffix:semicolon
multiline_comment|/* transaction type */
DECL|member|t_log_res
r_int
r_int
id|t_log_res
suffix:semicolon
multiline_comment|/* amt of log space resvd */
DECL|member|t_log_count
r_int
r_int
id|t_log_count
suffix:semicolon
multiline_comment|/* count for perm log res */
DECL|member|t_blk_res
r_int
r_int
id|t_blk_res
suffix:semicolon
multiline_comment|/* # of blocks resvd */
DECL|member|t_blk_res_used
r_int
r_int
id|t_blk_res_used
suffix:semicolon
multiline_comment|/* # of resvd blocks used */
DECL|member|t_rtx_res
r_int
r_int
id|t_rtx_res
suffix:semicolon
multiline_comment|/* # of rt extents resvd */
DECL|member|t_rtx_res_used
r_int
r_int
id|t_rtx_res_used
suffix:semicolon
multiline_comment|/* # of resvd rt extents used */
DECL|member|t_ticket
id|xfs_log_ticket_t
id|t_ticket
suffix:semicolon
multiline_comment|/* log mgr ticket */
DECL|member|t_sema
id|sema_t
id|t_sema
suffix:semicolon
multiline_comment|/* sema for commit completion */
DECL|member|t_lsn
id|xfs_lsn_t
id|t_lsn
suffix:semicolon
multiline_comment|/* log seq num of start of&n;&t;&t;&t;&t;&t;&t; * transaction. */
DECL|member|t_commit_lsn
id|xfs_lsn_t
id|t_commit_lsn
suffix:semicolon
multiline_comment|/* log seq num of end of&n;&t;&t;&t;&t;&t;&t; * transaction. */
DECL|member|t_mountp
r_struct
id|xfs_mount
op_star
id|t_mountp
suffix:semicolon
multiline_comment|/* ptr to fs mount struct */
DECL|member|t_dqinfo
r_struct
id|xfs_dquot_acct
op_star
id|t_dqinfo
suffix:semicolon
multiline_comment|/* accting info for dquots */
DECL|member|t_callback
id|xfs_trans_callback_t
id|t_callback
suffix:semicolon
multiline_comment|/* transaction callback */
DECL|member|t_callarg
r_void
op_star
id|t_callarg
suffix:semicolon
multiline_comment|/* callback arg */
DECL|member|t_flags
r_int
r_int
id|t_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|t_icount_delta
r_int
id|t_icount_delta
suffix:semicolon
multiline_comment|/* superblock icount change */
DECL|member|t_ifree_delta
r_int
id|t_ifree_delta
suffix:semicolon
multiline_comment|/* superblock ifree change */
DECL|member|t_fdblocks_delta
r_int
id|t_fdblocks_delta
suffix:semicolon
multiline_comment|/* superblock fdblocks chg */
DECL|member|t_res_fdblocks_delta
r_int
id|t_res_fdblocks_delta
suffix:semicolon
multiline_comment|/* on-disk only chg */
DECL|member|t_frextents_delta
r_int
id|t_frextents_delta
suffix:semicolon
multiline_comment|/* superblock freextents chg*/
DECL|member|t_res_frextents_delta
r_int
id|t_res_frextents_delta
suffix:semicolon
multiline_comment|/* on-disk only chg */
DECL|member|t_ag_freeblks_delta
r_int
id|t_ag_freeblks_delta
suffix:semicolon
multiline_comment|/* debugging counter */
DECL|member|t_ag_flist_delta
r_int
id|t_ag_flist_delta
suffix:semicolon
multiline_comment|/* debugging counter */
DECL|member|t_ag_btree_delta
r_int
id|t_ag_btree_delta
suffix:semicolon
multiline_comment|/* debugging counter */
DECL|member|t_dblocks_delta
r_int
id|t_dblocks_delta
suffix:semicolon
multiline_comment|/* superblock dblocks change */
DECL|member|t_agcount_delta
r_int
id|t_agcount_delta
suffix:semicolon
multiline_comment|/* superblock agcount change */
DECL|member|t_imaxpct_delta
r_int
id|t_imaxpct_delta
suffix:semicolon
multiline_comment|/* superblock imaxpct change */
DECL|member|t_rextsize_delta
r_int
id|t_rextsize_delta
suffix:semicolon
multiline_comment|/* superblock rextsize chg */
DECL|member|t_rbmblocks_delta
r_int
id|t_rbmblocks_delta
suffix:semicolon
multiline_comment|/* superblock rbmblocks chg */
DECL|member|t_rblocks_delta
r_int
id|t_rblocks_delta
suffix:semicolon
multiline_comment|/* superblock rblocks change */
DECL|member|t_rextents_delta
r_int
id|t_rextents_delta
suffix:semicolon
multiline_comment|/* superblocks rextents chg */
DECL|member|t_rextslog_delta
r_int
id|t_rextslog_delta
suffix:semicolon
multiline_comment|/* superblocks rextslog chg */
DECL|member|t_items_free
r_int
r_int
id|t_items_free
suffix:semicolon
multiline_comment|/* log item descs free */
DECL|member|t_items
id|xfs_log_item_chunk_t
id|t_items
suffix:semicolon
multiline_comment|/* first log item desc chunk */
DECL|member|t_header
id|xfs_trans_header_t
id|t_header
suffix:semicolon
multiline_comment|/* header for in-log trans */
DECL|member|t_busy_free
r_int
r_int
id|t_busy_free
suffix:semicolon
multiline_comment|/* busy descs free */
DECL|member|t_busy
id|xfs_log_busy_chunk_t
id|t_busy
suffix:semicolon
multiline_comment|/* busy/async free blocks */
DECL|member|t_pflags
id|xfs_pflags_t
id|t_pflags
suffix:semicolon
multiline_comment|/* saved pflags state */
DECL|typedef|xfs_trans_t
)brace
id|xfs_trans_t
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
DECL|macro|XFS_TRANS_MAGIC
mdefine_line|#define&t;XFS_TRANS_MAGIC&t;&t;0x5452414E&t;/* &squot;TRAN&squot; */
multiline_comment|/*&n; * Values for t_flags.&n; */
DECL|macro|XFS_TRANS_DIRTY
mdefine_line|#define&t;XFS_TRANS_DIRTY&t;&t;0x01&t;/* something needs to be logged */
DECL|macro|XFS_TRANS_SB_DIRTY
mdefine_line|#define&t;XFS_TRANS_SB_DIRTY&t;0x02&t;/* superblock is modified */
DECL|macro|XFS_TRANS_PERM_LOG_RES
mdefine_line|#define&t;XFS_TRANS_PERM_LOG_RES&t;0x04&t;/* xact took a permanent log res */
DECL|macro|XFS_TRANS_SYNC
mdefine_line|#define&t;XFS_TRANS_SYNC&t;&t;0x08&t;/* make commit synchronous */
DECL|macro|XFS_TRANS_DQ_DIRTY
mdefine_line|#define XFS_TRANS_DQ_DIRTY&t;0x10&t;/* at least one dquot in trx dirty */
DECL|macro|XFS_TRANS_RESERVE
mdefine_line|#define XFS_TRANS_RESERVE&t;0x20    /* OK to use reserved data blocks */
multiline_comment|/*&n; * Values for call flags parameter.&n; */
DECL|macro|XFS_TRANS_NOSLEEP
mdefine_line|#define&t;XFS_TRANS_NOSLEEP&t;&t;0x1
DECL|macro|XFS_TRANS_WAIT
mdefine_line|#define&t;XFS_TRANS_WAIT&t;&t;&t;0x2
DECL|macro|XFS_TRANS_RELEASE_LOG_RES
mdefine_line|#define&t;XFS_TRANS_RELEASE_LOG_RES&t;0x4
DECL|macro|XFS_TRANS_ABORT
mdefine_line|#define&t;XFS_TRANS_ABORT&t;&t;&t;0x8
multiline_comment|/*&n; * Field values for xfs_trans_mod_sb.&n; */
DECL|macro|XFS_TRANS_SB_ICOUNT
mdefine_line|#define&t;XFS_TRANS_SB_ICOUNT&t;&t;0x00000001
DECL|macro|XFS_TRANS_SB_IFREE
mdefine_line|#define&t;XFS_TRANS_SB_IFREE&t;&t;0x00000002
DECL|macro|XFS_TRANS_SB_FDBLOCKS
mdefine_line|#define&t;XFS_TRANS_SB_FDBLOCKS&t;&t;0x00000004
DECL|macro|XFS_TRANS_SB_RES_FDBLOCKS
mdefine_line|#define&t;XFS_TRANS_SB_RES_FDBLOCKS&t;0x00000008
DECL|macro|XFS_TRANS_SB_FREXTENTS
mdefine_line|#define&t;XFS_TRANS_SB_FREXTENTS&t;&t;0x00000010
DECL|macro|XFS_TRANS_SB_RES_FREXTENTS
mdefine_line|#define&t;XFS_TRANS_SB_RES_FREXTENTS&t;0x00000020
DECL|macro|XFS_TRANS_SB_DBLOCKS
mdefine_line|#define&t;XFS_TRANS_SB_DBLOCKS&t;&t;0x00000040
DECL|macro|XFS_TRANS_SB_AGCOUNT
mdefine_line|#define&t;XFS_TRANS_SB_AGCOUNT&t;&t;0x00000080
DECL|macro|XFS_TRANS_SB_IMAXPCT
mdefine_line|#define&t;XFS_TRANS_SB_IMAXPCT&t;&t;0x00000100
DECL|macro|XFS_TRANS_SB_REXTSIZE
mdefine_line|#define&t;XFS_TRANS_SB_REXTSIZE&t;&t;0x00000200
DECL|macro|XFS_TRANS_SB_RBMBLOCKS
mdefine_line|#define&t;XFS_TRANS_SB_RBMBLOCKS&t;&t;0x00000400
DECL|macro|XFS_TRANS_SB_RBLOCKS
mdefine_line|#define&t;XFS_TRANS_SB_RBLOCKS&t;&t;0x00000800
DECL|macro|XFS_TRANS_SB_REXTENTS
mdefine_line|#define&t;XFS_TRANS_SB_REXTENTS&t;&t;0x00001000
DECL|macro|XFS_TRANS_SB_REXTSLOG
mdefine_line|#define&t;XFS_TRANS_SB_REXTSLOG&t;&t;0x00002000
multiline_comment|/*&n; * Various log reservation values.&n; * These are based on the size of the file system block&n; * because that is what most transactions manipulate.&n; * Each adds in an additional 128 bytes per item logged to&n; * try to account for the overhead of the transaction mechanism.&n; *&n; * Note:&n; * Most of the reservations underestimate the number of allocation&n; * groups into which they could free extents in the xfs_bmap_finish()&n; * call.  This is because the number in the worst case is quite high&n; * and quite unusual.  In order to fix this we need to change&n; * xfs_bmap_finish() to free extents in only a single AG at a time.&n; * This will require changes to the EFI code as well, however, so that&n; * the EFI for the extents not freed is logged again in each transaction.&n; * See bug 261917.&n; */
multiline_comment|/*&n; * Per-extent log reservation for the allocation btree changes&n; * involved in freeing or allocating an extent.&n; * 2 trees * (2 blocks/level * max depth - 1) * block size&n; */
DECL|macro|XFS_ALLOCFREE_LOG_RES
mdefine_line|#define&t;XFS_ALLOCFREE_LOG_RES(mp,nx) &bslash;&n;&t;((nx) * (2 * XFS_FSB_TO_B((mp), 2 * XFS_AG_MAXLEVELS(mp) - 1)))
DECL|macro|XFS_ALLOCFREE_LOG_COUNT
mdefine_line|#define&t;XFS_ALLOCFREE_LOG_COUNT(mp,nx) &bslash;&n;&t;((nx) * (2 * (2 * XFS_AG_MAXLEVELS(mp) - 1)))
multiline_comment|/*&n; * Per-directory log reservation for any directory change.&n; * dir blocks: (1 btree block per level + data block + free block) * dblock size&n; * bmap btree: (levels + 2) * max depth * block size&n; * v2 directory blocks can be fragmented below the dirblksize down to the fsb&n; * size, so account for that in the DAENTER macros.&n; */
DECL|macro|XFS_DIROP_LOG_RES
mdefine_line|#define&t;XFS_DIROP_LOG_RES(mp)&t;&bslash;&n;&t;(XFS_FSB_TO_B(mp, XFS_DAENTER_BLOCKS(mp, XFS_DATA_FORK)) + &bslash;&n;&t; (XFS_FSB_TO_B(mp, XFS_DAENTER_BMAPS(mp, XFS_DATA_FORK) + 1)))
DECL|macro|XFS_DIROP_LOG_COUNT
mdefine_line|#define&t;XFS_DIROP_LOG_COUNT(mp)&t;&bslash;&n;&t;(XFS_DAENTER_BLOCKS(mp, XFS_DATA_FORK) + &bslash;&n;&t; XFS_DAENTER_BMAPS(mp, XFS_DATA_FORK) + 1)
multiline_comment|/*&n; * In a write transaction we can allocate a maximum of 2&n; * extents.  This gives:&n; *    the inode getting the new extents: inode size&n; *    the inode&bslash;&squot;s bmap btree: max depth * block size&n; *    the agfs of the ags from which the extents are allocated: 2 * sector&n; *    the superblock free block counter: sector size&n; *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size&n; * And the bmap_finish transaction can free bmap blocks in a join:&n; *    the agfs of the ags containing the blocks: 2 * sector size&n; *    the agfls of the ags containing the blocks: 2 * sector size&n; *    the super block free block counter: sector size&n; *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_WRITE_LOG_RES
mdefine_line|#define XFS_CALC_WRITE_LOG_RES(mp) &bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK)) + &bslash;&n;&t;  (2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 2) + &bslash;&n;&t;  (128 * (4 + XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK) + XFS_ALLOCFREE_LOG_COUNT(mp, 2)))),&bslash;&n;&t; ((2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 2) + &bslash;&n;&t;  (128 * (5 + XFS_ALLOCFREE_LOG_COUNT(mp, 2))))))
DECL|macro|XFS_WRITE_LOG_RES
mdefine_line|#define&t;XFS_WRITE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_write)
multiline_comment|/*&n; * In truncating a file we free up to two extents at once.  We can modify:&n; *    the inode being truncated: inode size&n; *    the inode&bslash;&squot;s bmap btree: (max depth + 1) * block size&n; * And the bmap_finish transaction can free the blocks and bmap blocks:&n; *    the agf for each of the ags: 4 * sector size&n; *    the agfl for each of the ags: 4 * sector size&n; *    the super block to reflect the freed blocks: sector size&n; *    worst case split in allocation btrees per extent assuming 4 extents:&n; *&t;&t;4 exts * 2 trees * (2 * max depth - 1) * block size&n; *    the inode btree: max depth * blocksize&n; *    the allocation btrees: 2 trees * (max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_ITRUNCATE_LOG_RES
mdefine_line|#define&t;XFS_CALC_ITRUNCATE_LOG_RES(mp) &bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK) + 1) + &bslash;&n;&t;  (128 * (2 + XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK)))), &bslash;&n;&t; ((4 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (4 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 4) + &bslash;&n;&t;  (128 * (9 + XFS_ALLOCFREE_LOG_COUNT(mp, 4))) + &bslash;&n;&t;  (128 * 5) + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t;   (128 * (2 + XFS_IALLOC_BLOCKS(mp) + XFS_IN_MAXLEVELS(mp) + &bslash;&n;&t;    XFS_ALLOCFREE_LOG_COUNT(mp, 1))))))
DECL|macro|XFS_ITRUNCATE_LOG_RES
mdefine_line|#define&t;XFS_ITRUNCATE_LOG_RES(mp)   ((mp)-&gt;m_reservations.tr_itruncate)
multiline_comment|/*&n; * In renaming a files we can modify:&n; *    the four inodes involved: 4 * inode size&n; *    the two directory btrees: 2 * (max depth + v2) * dir block size&n; *    the two directory bmap btrees: 2 * max depth * block size&n; * And the bmap_finish transaction can free dir and bmap blocks (two sets&n; *&t;of bmap blocks) giving:&n; *    the agf for the ags in which the blocks live: 3 * sector size&n; *    the agfl for the ags in which the blocks live: 3 * sector size&n; *    the superblock for the free block count: sector size&n; *    the allocation btrees: 3 exts * 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_RENAME_LOG_RES
mdefine_line|#define&t;XFS_CALC_RENAME_LOG_RES(mp) &bslash;&n;&t;(MAX( &bslash;&n;&t; ((4 * (mp)-&gt;m_sb.sb_inodesize) + &bslash;&n;&t;  (2 * XFS_DIROP_LOG_RES(mp)) + &bslash;&n;&t;  (128 * (4 + 2 * XFS_DIROP_LOG_COUNT(mp)))), &bslash;&n;&t; ((3 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (3 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 3) + &bslash;&n;&t;  (128 * (7 + XFS_ALLOCFREE_LOG_COUNT(mp, 3))))))
DECL|macro|XFS_RENAME_LOG_RES
mdefine_line|#define&t;XFS_RENAME_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_rename)
multiline_comment|/*&n; * For creating a link to an inode:&n; *    the parent directory inode: inode size&n; *    the linked inode: inode size&n; *    the directory btree could split: (max depth + v2) * dir block size&n; *    the directory bmap btree could join or split: (max depth + v2) * blocksize&n; * And the bmap_finish transaction can free some bmap blocks giving:&n; *    the agf for the ag in which the blocks live: sector size&n; *    the agfl for the ag in which the blocks live: sector size&n; *    the superblock for the free block count: sector size&n; *    the allocation btrees: 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_LINK_LOG_RES
mdefine_line|#define&t;XFS_CALC_LINK_LOG_RES(mp) &bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_DIROP_LOG_RES(mp) + &bslash;&n;&t;  (128 * (2 + XFS_DIROP_LOG_COUNT(mp)))), &bslash;&n;&t; ((mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t;  (128 * (3 + XFS_ALLOCFREE_LOG_COUNT(mp, 1))))))
DECL|macro|XFS_LINK_LOG_RES
mdefine_line|#define&t;XFS_LINK_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_link)
multiline_comment|/*&n; * For removing a directory entry we can modify:&n; *    the parent directory inode: inode size&n; *    the removed inode: inode size&n; *    the directory btree could join: (max depth + v2) * dir block size&n; *    the directory bmap btree could join or split: (max depth + v2) * blocksize&n; * And the bmap_finish transaction can free the dir and bmap blocks giving:&n; *    the agf for the ag in which the blocks live: 2 * sector size&n; *    the agfl for the ag in which the blocks live: 2 * sector size&n; *    the superblock for the free block count: sector size&n; *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_REMOVE_LOG_RES
mdefine_line|#define&t;XFS_CALC_REMOVE_LOG_RES(mp)&t;&bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_DIROP_LOG_RES(mp) + &bslash;&n;&t;  (128 * (2 + XFS_DIROP_LOG_COUNT(mp)))), &bslash;&n;&t; ((2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 2) + &bslash;&n;&t;  (128 * (5 + XFS_ALLOCFREE_LOG_COUNT(mp, 2))))))
DECL|macro|XFS_REMOVE_LOG_RES
mdefine_line|#define&t;XFS_REMOVE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_remove)
multiline_comment|/*&n; * For symlink we can modify:&n; *    the parent directory inode: inode size&n; *    the new inode: inode size&n; *    the inode btree entry: 1 block&n; *    the directory btree: (max depth + v2) * dir block size&n; *    the directory inode&bslash;&squot;s bmap btree: (max depth + v2) * block size&n; *    the blocks for the symlink: 1 KB&n; * Or in the first xact we allocate some inodes giving:&n; *    the agi and agf of the ag getting the new inodes: 2 * sectorsize&n; *    the inode blocks allocated: XFS_IALLOC_BLOCKS * blocksize&n; *    the inode btree: max depth * blocksize&n; *    the allocation btrees: 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_SYMLINK_LOG_RES
mdefine_line|#define&t;XFS_CALC_SYMLINK_LOG_RES(mp)&t;&t;&bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_FSB_TO_B(mp, 1) + &bslash;&n;&t;  XFS_DIROP_LOG_RES(mp) + &bslash;&n;&t;  1024 + &bslash;&n;&t;  (128 * (4 + XFS_DIROP_LOG_COUNT(mp)))), &bslash;&n;&t; (2 * (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_IALLOC_BLOCKS((mp))) + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_IN_MAXLEVELS(mp)) + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t;  (128 * (2 + XFS_IALLOC_BLOCKS(mp) + XFS_IN_MAXLEVELS(mp) + &bslash;&n;&t;   XFS_ALLOCFREE_LOG_COUNT(mp, 1))))))
DECL|macro|XFS_SYMLINK_LOG_RES
mdefine_line|#define&t;XFS_SYMLINK_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_symlink)
multiline_comment|/*&n; * For create we can modify:&n; *    the parent directory inode: inode size&n; *    the new inode: inode size&n; *    the inode btree entry: block size&n; *    the superblock for the nlink flag: sector size&n; *    the directory btree: (max depth + v2) * dir block size&n; *    the directory inode&bslash;&squot;s bmap btree: (max depth + v2) * block size&n; * Or in the first xact we allocate some inodes giving:&n; *    the agi and agf of the ag getting the new inodes: 2 * sectorsize&n; *    the superblock for the nlink flag: sector size&n; *    the inode blocks allocated: XFS_IALLOC_BLOCKS * blocksize&n; *    the inode btree: max depth * blocksize&n; *    the allocation btrees: 2 trees * (max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_CREATE_LOG_RES
mdefine_line|#define&t;XFS_CALC_CREATE_LOG_RES(mp)&t;&t;&bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_FSB_TO_B(mp, 1) + &bslash;&n;&t;  XFS_DIROP_LOG_RES(mp) + &bslash;&n;&t;  (128 * (3 + XFS_DIROP_LOG_COUNT(mp)))), &bslash;&n;&t; (3 * (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_IALLOC_BLOCKS((mp))) + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_IN_MAXLEVELS(mp)) + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t;  (128 * (2 + XFS_IALLOC_BLOCKS(mp) + XFS_IN_MAXLEVELS(mp) + &bslash;&n;&t;   XFS_ALLOCFREE_LOG_COUNT(mp, 1))))))
DECL|macro|XFS_CREATE_LOG_RES
mdefine_line|#define&t;XFS_CREATE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_create)
multiline_comment|/*&n; * Making a new directory is the same as creating a new file.&n; */
DECL|macro|XFS_CALC_MKDIR_LOG_RES
mdefine_line|#define&t;XFS_CALC_MKDIR_LOG_RES(mp)&t;XFS_CALC_CREATE_LOG_RES(mp)
DECL|macro|XFS_MKDIR_LOG_RES
mdefine_line|#define&t;XFS_MKDIR_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_mkdir)
multiline_comment|/*&n; * In freeing an inode we can modify:&n; *    the inode being freed: inode size&n; *    the super block free inode counter: sector size&n; *    the agi hash list and counters: sector size&n; *    the inode btree entry: block size&n; *    the on disk inode before ours in the agi hash list: inode cluster size&n; *    the inode btree: max depth * blocksize&n; *    the allocation btrees: 2 trees * (max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_IFREE_LOG_RES
mdefine_line|#define&t;XFS_CALC_IFREE_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t; (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t; (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t; XFS_FSB_TO_B((mp), 1) + &bslash;&n;&t; MAX((__uint16_t)XFS_FSB_TO_B((mp), 1), XFS_INODE_CLUSTER_SIZE(mp)) + &bslash;&n;&t; (128 * 5) + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t;  (128 * (2 + XFS_IALLOC_BLOCKS(mp) + XFS_IN_MAXLEVELS(mp) + &bslash;&n;&t;   XFS_ALLOCFREE_LOG_COUNT(mp, 1))))
DECL|macro|XFS_IFREE_LOG_RES
mdefine_line|#define&t;XFS_IFREE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_ifree)
multiline_comment|/*&n; * When only changing the inode we log the inode and possibly the superblock&n; * We also add a bit of slop for the transaction stuff.&n; */
DECL|macro|XFS_CALC_ICHANGE_LOG_RES
mdefine_line|#define&t;XFS_CALC_ICHANGE_LOG_RES(mp)&t;((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;&t;&t;&t;&t; (mp)-&gt;m_sb.sb_sectsize + 512)
DECL|macro|XFS_ICHANGE_LOG_RES
mdefine_line|#define&t;XFS_ICHANGE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_ichange)
multiline_comment|/*&n; * Growing the data section of the filesystem.&n; *&t;superblock&n; *&t;agi and agf&n; *&t;allocation btrees&n; */
DECL|macro|XFS_CALC_GROWDATA_LOG_RES
mdefine_line|#define&t;XFS_CALC_GROWDATA_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_sectsize * 3 + &bslash;&n;&t; XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t; (128 * (3 + XFS_ALLOCFREE_LOG_COUNT(mp, 1))))
DECL|macro|XFS_GROWDATA_LOG_RES
mdefine_line|#define&t;XFS_GROWDATA_LOG_RES(mp)    ((mp)-&gt;m_reservations.tr_growdata)
multiline_comment|/*&n; * Growing the rt section of the filesystem.&n; * In the first set of transactions (ALLOC) we allocate space to the&n; * bitmap or summary files.&n; *&t;superblock: sector size&n; *&t;agf of the ag from which the extent is allocated: sector size&n; *&t;bmap btree for bitmap/summary inode: max depth * blocksize&n; *&t;bitmap/summary inode: inode size&n; *&t;allocation btrees for 1 block alloc: 2 * (2 * maxdepth - 1) * blocksize&n; */
DECL|macro|XFS_CALC_GROWRTALLOC_LOG_RES
mdefine_line|#define&t;XFS_CALC_GROWRTALLOC_LOG_RES(mp) &bslash;&n;&t;(2 * (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t; XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK)) + &bslash;&n;&t; (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t; XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t; (128 * &bslash;&n;&t;  (3 + XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK) + &bslash;&n;&t;   XFS_ALLOCFREE_LOG_COUNT(mp, 1))))
DECL|macro|XFS_GROWRTALLOC_LOG_RES
mdefine_line|#define&t;XFS_GROWRTALLOC_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_growrtalloc)
multiline_comment|/*&n; * Growing the rt section of the filesystem.&n; * In the second set of transactions (ZERO) we zero the new metadata blocks.&n; *&t;one bitmap/summary block: blocksize&n; */
DECL|macro|XFS_CALC_GROWRTZERO_LOG_RES
mdefine_line|#define&t;XFS_CALC_GROWRTZERO_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_blocksize + 128)
DECL|macro|XFS_GROWRTZERO_LOG_RES
mdefine_line|#define&t;XFS_GROWRTZERO_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_growrtzero)
multiline_comment|/*&n; * Growing the rt section of the filesystem.&n; * In the third set of transactions (FREE) we update metadata without&n; * allocating any new blocks.&n; *&t;superblock: sector size&n; *&t;bitmap inode: inode size&n; *&t;summary inode: inode size&n; *&t;one bitmap block: blocksize&n; *&t;summary blocks: new summary size&n; */
DECL|macro|XFS_CALC_GROWRTFREE_LOG_RES
mdefine_line|#define&t;XFS_CALC_GROWRTFREE_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t; 2 * (mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t; (mp)-&gt;m_sb.sb_blocksize + &bslash;&n;&t; (mp)-&gt;m_rsumsize + &bslash;&n;&t; (128 * 5))
DECL|macro|XFS_GROWRTFREE_LOG_RES
mdefine_line|#define&t;XFS_GROWRTFREE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_growrtfree)
multiline_comment|/*&n; * Logging the inode modification timestamp on a synchronous write.&n; *&t;inode&n; */
DECL|macro|XFS_CALC_SWRITE_LOG_RES
mdefine_line|#define&t;XFS_CALC_SWRITE_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_inodesize + 128)
DECL|macro|XFS_SWRITE_LOG_RES
mdefine_line|#define&t;XFS_SWRITE_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_swrite)
multiline_comment|/*&n; * Logging the inode timestamps on an fsync -- same as SWRITE&n; * as long as SWRITE logs the entire inode core&n; */
DECL|macro|XFS_FSYNC_TS_LOG_RES
mdefine_line|#define XFS_FSYNC_TS_LOG_RES(mp)        ((mp)-&gt;m_reservations.tr_swrite)
multiline_comment|/*&n; * Logging the inode mode bits when writing a setuid/setgid file&n; *&t;inode&n; */
DECL|macro|XFS_CALC_WRITEID_LOG_RES
mdefine_line|#define&t;XFS_CALC_WRITEID_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_inodesize + 128)
DECL|macro|XFS_WRITEID_LOG_RES
mdefine_line|#define&t;XFS_WRITEID_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_swrite)
multiline_comment|/*&n; * Converting the inode from non-attributed to attributed.&n; *&t;the inode being converted: inode size&n; *&t;agf block and superblock (for block allocation)&n; *&t;the new block (directory sized)&n; *&t;bmap blocks for the new directory block&n; *&t;allocation btrees&n; */
DECL|macro|XFS_CALC_ADDAFORK_LOG_RES
mdefine_line|#define&t;XFS_CALC_ADDAFORK_LOG_RES(mp)&t;&bslash;&n;&t;((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t; (mp)-&gt;m_sb.sb_sectsize * 2 + &bslash;&n;&t; (mp)-&gt;m_dirblksize + &bslash;&n;&t; (XFS_DIR_IS_V1(mp) ? 0 : &bslash;&n;&t;    XFS_FSB_TO_B(mp, (XFS_DAENTER_BMAP1B(mp, XFS_DATA_FORK) + 1))) + &bslash;&n;&t; XFS_ALLOCFREE_LOG_RES(mp, 1) + &bslash;&n;&t; (128 * (4 + &bslash;&n;&t;&t; (XFS_DIR_IS_V1(mp) ? 0 : &bslash;&n;&t;&t;&t; XFS_DAENTER_BMAP1B(mp, XFS_DATA_FORK) + 1) + &bslash;&n;&t;&t; XFS_ALLOCFREE_LOG_COUNT(mp, 1))))
DECL|macro|XFS_ADDAFORK_LOG_RES
mdefine_line|#define&t;XFS_ADDAFORK_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_addafork)
multiline_comment|/*&n; * Removing the attribute fork of a file&n; *    the inode being truncated: inode size&n; *    the inode&bslash;&squot;s bmap btree: max depth * block size&n; * And the bmap_finish transaction can free the blocks and bmap blocks:&n; *    the agf for each of the ags: 4 * sector size&n; *    the agfl for each of the ags: 4 * sector size&n; *    the super block to reflect the freed blocks: sector size&n; *    worst case split in allocation btrees per extent assuming 4 extents:&n; *&t;&t;4 exts * 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_ATTRINVAL_LOG_RES
mdefine_line|#define&t;XFS_CALC_ATTRINVAL_LOG_RES(mp)&t;&bslash;&n;&t;(MAX( &bslash;&n;&t; ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK)) + &bslash;&n;&t;  (128 * (1 + XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK)))), &bslash;&n;&t; ((4 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (4 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 4) + &bslash;&n;&t;  (128 * (9 + XFS_ALLOCFREE_LOG_COUNT(mp, 4))))))
DECL|macro|XFS_ATTRINVAL_LOG_RES
mdefine_line|#define&t;XFS_ATTRINVAL_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_attrinval)
multiline_comment|/*&n; * Setting an attribute.&n; *&t;the inode getting the attribute&n; *&t;the superblock for allocations&n; *&t;the agfs extents are allocated from&n; *&t;the attribute btree * max depth&n; *&t;the inode allocation btree&n; * Since attribute transaction space is dependent on the size of the attribute,&n; * the calculation is done partially at mount time and partially at runtime.&n; */
DECL|macro|XFS_CALC_ATTRSET_LOG_RES
mdefine_line|#define&t;XFS_CALC_ATTRSET_LOG_RES(mp)&t;&bslash;&n;&t;((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t; (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_DA_NODE_MAXDEPTH) + &bslash;&n;&t;  (128 * (2 + XFS_DA_NODE_MAXDEPTH)))
DECL|macro|XFS_ATTRSET_LOG_RES
mdefine_line|#define&t;XFS_ATTRSET_LOG_RES(mp, ext)&t;&bslash;&n;&t;((mp)-&gt;m_reservations.tr_attrset + &bslash;&n;&t; (ext * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t; (ext * XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK))) + &bslash;&n;&t; (128 * (ext + (ext * XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK)))))
multiline_comment|/*&n; * Removing an attribute.&n; *    the inode: inode size&n; *    the attribute btree could join: max depth * block size&n; *    the inode bmap btree could join or split: max depth * block size&n; * And the bmap_finish transaction can free the attr blocks freed giving:&n; *    the agf for the ag in which the blocks live: 2 * sector size&n; *    the agfl for the ag in which the blocks live: 2 * sector size&n; *    the superblock for the free block count: sector size&n; *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size&n; */
DECL|macro|XFS_CALC_ATTRRM_LOG_RES
mdefine_line|#define&t;XFS_CALC_ATTRRM_LOG_RES(mp)&t;&bslash;&n;&t;(MAX( &bslash;&n;&t;  ((mp)-&gt;m_sb.sb_inodesize + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_DA_NODE_MAXDEPTH) + &bslash;&n;&t;  XFS_FSB_TO_B((mp), XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK)) + &bslash;&n;&t;  (128 * (1 + XFS_DA_NODE_MAXDEPTH + XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK)))), &bslash;&n;&t; ((2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (2 * (mp)-&gt;m_sb.sb_sectsize) + &bslash;&n;&t;  (mp)-&gt;m_sb.sb_sectsize + &bslash;&n;&t;  XFS_ALLOCFREE_LOG_RES(mp, 2) + &bslash;&n;&t;  (128 * (5 + XFS_ALLOCFREE_LOG_COUNT(mp, 2))))))
DECL|macro|XFS_ATTRRM_LOG_RES
mdefine_line|#define&t;XFS_ATTRRM_LOG_RES(mp)&t;((mp)-&gt;m_reservations.tr_attrrm)
multiline_comment|/*&n; * Clearing a bad agino number in an agi hash bucket.&n; */
DECL|macro|XFS_CALC_CLEAR_AGI_BUCKET_LOG_RES
mdefine_line|#define&t;XFS_CALC_CLEAR_AGI_BUCKET_LOG_RES(mp) &bslash;&n;&t;((mp)-&gt;m_sb.sb_sectsize + 128)
DECL|macro|XFS_CLEAR_AGI_BUCKET_LOG_RES
mdefine_line|#define&t;XFS_CLEAR_AGI_BUCKET_LOG_RES(mp)  ((mp)-&gt;m_reservations.tr_clearagi)
multiline_comment|/*&n; * Various log count values.&n; */
DECL|macro|XFS_DEFAULT_LOG_COUNT
mdefine_line|#define&t;XFS_DEFAULT_LOG_COUNT&t;&t;1
DECL|macro|XFS_DEFAULT_PERM_LOG_COUNT
mdefine_line|#define&t;XFS_DEFAULT_PERM_LOG_COUNT&t;2
DECL|macro|XFS_ITRUNCATE_LOG_COUNT
mdefine_line|#define&t;XFS_ITRUNCATE_LOG_COUNT&t;&t;2
DECL|macro|XFS_INACTIVE_LOG_COUNT
mdefine_line|#define XFS_INACTIVE_LOG_COUNT&t;&t;2
DECL|macro|XFS_CREATE_LOG_COUNT
mdefine_line|#define&t;XFS_CREATE_LOG_COUNT&t;&t;2
DECL|macro|XFS_MKDIR_LOG_COUNT
mdefine_line|#define&t;XFS_MKDIR_LOG_COUNT&t;&t;3
DECL|macro|XFS_SYMLINK_LOG_COUNT
mdefine_line|#define&t;XFS_SYMLINK_LOG_COUNT&t;&t;3
DECL|macro|XFS_REMOVE_LOG_COUNT
mdefine_line|#define&t;XFS_REMOVE_LOG_COUNT&t;&t;2
DECL|macro|XFS_LINK_LOG_COUNT
mdefine_line|#define&t;XFS_LINK_LOG_COUNT&t;&t;2
DECL|macro|XFS_RENAME_LOG_COUNT
mdefine_line|#define&t;XFS_RENAME_LOG_COUNT&t;&t;2
DECL|macro|XFS_WRITE_LOG_COUNT
mdefine_line|#define&t;XFS_WRITE_LOG_COUNT&t;&t;2
DECL|macro|XFS_ADDAFORK_LOG_COUNT
mdefine_line|#define&t;XFS_ADDAFORK_LOG_COUNT&t;&t;2
DECL|macro|XFS_ATTRINVAL_LOG_COUNT
mdefine_line|#define&t;XFS_ATTRINVAL_LOG_COUNT&t;&t;1
DECL|macro|XFS_ATTRSET_LOG_COUNT
mdefine_line|#define&t;XFS_ATTRSET_LOG_COUNT&t;&t;3
DECL|macro|XFS_ATTRRM_LOG_COUNT
mdefine_line|#define&t;XFS_ATTRRM_LOG_COUNT&t;&t;3
multiline_comment|/*&n; * Here we centralize the specification of XFS meta-data buffer&n; * reference count values.  This determine how hard the buffer&n; * cache tries to hold onto the buffer.&n; */
DECL|macro|XFS_AGF_REF
mdefine_line|#define&t;XFS_AGF_REF&t;&t;4
DECL|macro|XFS_AGI_REF
mdefine_line|#define&t;XFS_AGI_REF&t;&t;4
DECL|macro|XFS_AGFL_REF
mdefine_line|#define&t;XFS_AGFL_REF&t;&t;3
DECL|macro|XFS_INO_BTREE_REF
mdefine_line|#define&t;XFS_INO_BTREE_REF&t;3
DECL|macro|XFS_ALLOC_BTREE_REF
mdefine_line|#define&t;XFS_ALLOC_BTREE_REF&t;2
DECL|macro|XFS_BMAP_BTREE_REF
mdefine_line|#define&t;XFS_BMAP_BTREE_REF&t;2
DECL|macro|XFS_DIR_BTREE_REF
mdefine_line|#define&t;XFS_DIR_BTREE_REF&t;2
DECL|macro|XFS_ATTR_BTREE_REF
mdefine_line|#define&t;XFS_ATTR_BTREE_REF&t;1
DECL|macro|XFS_INO_REF
mdefine_line|#define&t;XFS_INO_REF&t;&t;1
DECL|macro|XFS_DQUOT_REF
mdefine_line|#define&t;XFS_DQUOT_REF&t;&t;1
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * XFS transaction mechanism exported interfaces that are&n; * actually macros.&n; */
DECL|macro|xfs_trans_get_log_res
mdefine_line|#define&t;xfs_trans_get_log_res(tp)&t;((tp)-&gt;t_log_res)
DECL|macro|xfs_trans_get_log_count
mdefine_line|#define&t;xfs_trans_get_log_count(tp)&t;((tp)-&gt;t_log_count)
DECL|macro|xfs_trans_get_block_res
mdefine_line|#define&t;xfs_trans_get_block_res(tp)&t;((tp)-&gt;t_blk_res)
DECL|macro|xfs_trans_set_sync
mdefine_line|#define&t;xfs_trans_set_sync(tp)&t;&t;((tp)-&gt;t_flags |= XFS_TRANS_SYNC)
macro_line|#ifdef DEBUG
DECL|macro|xfs_trans_agblocks_delta
mdefine_line|#define&t;xfs_trans_agblocks_delta(tp, d)&t;((tp)-&gt;t_ag_freeblks_delta += (long)d)
DECL|macro|xfs_trans_agflist_delta
mdefine_line|#define&t;xfs_trans_agflist_delta(tp, d)&t;((tp)-&gt;t_ag_flist_delta += (long)d)
DECL|macro|xfs_trans_agbtree_delta
mdefine_line|#define&t;xfs_trans_agbtree_delta(tp, d)&t;((tp)-&gt;t_ag_btree_delta += (long)d)
macro_line|#else
DECL|macro|xfs_trans_agblocks_delta
mdefine_line|#define&t;xfs_trans_agblocks_delta(tp, d)
DECL|macro|xfs_trans_agflist_delta
mdefine_line|#define&t;xfs_trans_agflist_delta(tp, d)
DECL|macro|xfs_trans_agbtree_delta
mdefine_line|#define&t;xfs_trans_agbtree_delta(tp, d)
macro_line|#endif
multiline_comment|/*&n; * XFS transaction mechanism exported interfaces.&n; */
r_void
id|xfs_trans_init
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
id|xfs_trans_t
op_star
id|xfs_trans_alloc
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
id|xfs_trans_t
op_star
id|_xfs_trans_alloc
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
id|xfs_trans_t
op_star
id|xfs_trans_dup
c_func
(paren
id|xfs_trans_t
op_star
)paren
suffix:semicolon
r_int
id|xfs_trans_reserve
c_func
(paren
id|xfs_trans_t
op_star
comma
id|uint
comma
id|uint
comma
id|uint
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_callback
c_func
(paren
id|xfs_trans_t
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|xfs_trans_t
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_mod_sb
c_func
(paren
id|xfs_trans_t
op_star
comma
id|uint
comma
r_int
)paren
suffix:semicolon
r_struct
id|xfs_buf
op_star
id|xfs_trans_get_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buftarg
op_star
comma
id|xfs_daddr_t
comma
r_int
comma
id|uint
)paren
suffix:semicolon
r_int
id|xfs_trans_read_buf
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buftarg
op_star
comma
id|xfs_daddr_t
comma
r_int
comma
id|uint
comma
r_struct
id|xfs_buf
op_star
op_star
)paren
suffix:semicolon
r_struct
id|xfs_buf
op_star
id|xfs_trans_getsb
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_mount
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_trans_brelse
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_bjoin
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_bhold
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_binval
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_inode_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_inode_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_stale_inode_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_dquot_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_inode_alloc_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_int
id|xfs_trans_iget
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_trans_t
op_star
comma
id|xfs_ino_t
comma
id|uint
comma
id|uint
comma
r_struct
id|xfs_inode
op_star
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_ijoin
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_ihold
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_ihold_release
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_log_buf
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_buf
op_star
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_log_inode
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|uint
)paren
suffix:semicolon
r_struct
id|xfs_efi_log_item
op_star
id|xfs_trans_get_efi
c_func
(paren
id|xfs_trans_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_efi_release
c_func
(paren
r_struct
id|xfs_efi_log_item
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_log_efi_extent
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_efi_log_item
op_star
comma
id|xfs_fsblock_t
comma
id|xfs_extlen_t
)paren
suffix:semicolon
r_struct
id|xfs_efd_log_item
op_star
id|xfs_trans_get_efd
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_efi_log_item
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_trans_log_efd_extent
c_func
(paren
id|xfs_trans_t
op_star
comma
r_struct
id|xfs_efd_log_item
op_star
comma
id|xfs_fsblock_t
comma
id|xfs_extlen_t
)paren
suffix:semicolon
r_int
id|xfs_trans_commit
c_func
(paren
id|xfs_trans_t
op_star
comma
id|uint
id|flags
comma
id|xfs_lsn_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_cancel
c_func
(paren
id|xfs_trans_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_trans_ail_init
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
id|xfs_lsn_t
id|xfs_trans_push_ail
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_lsn_t
)paren
suffix:semicolon
id|xfs_lsn_t
id|xfs_trans_tail_ail
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_trans_unlocked_item
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
id|xfs_log_busy_slot_t
op_star
id|xfs_trans_add_busy
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_agnumber_t
id|ag
comma
id|xfs_extlen_t
id|idx
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_TRANS_H__ */
eof
