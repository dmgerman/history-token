multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef&t;__XFS_LOG_PRIV_H__
DECL|macro|__XFS_LOG_PRIV_H__
mdefine_line|#define __XFS_LOG_PRIV_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|ktrace
suffix:semicolon
r_struct
id|log
suffix:semicolon
r_struct
id|xfs_buf_cancel
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
multiline_comment|/*&n; * Macros, structures, prototypes for internal log manager use.&n; */
DECL|macro|XLOG_MIN_ICLOGS
mdefine_line|#define XLOG_MIN_ICLOGS&t;&t;2
DECL|macro|XLOG_MED_ICLOGS
mdefine_line|#define XLOG_MED_ICLOGS&t;&t;4
DECL|macro|XLOG_MAX_ICLOGS
mdefine_line|#define XLOG_MAX_ICLOGS&t;&t;8
DECL|macro|XLOG_CALLBACK_SIZE
mdefine_line|#define XLOG_CALLBACK_SIZE&t;10
DECL|macro|XLOG_HEADER_MAGIC_NUM
mdefine_line|#define XLOG_HEADER_MAGIC_NUM&t;0xFEEDbabe&t;/* Invalid cycle number */
DECL|macro|XLOG_VERSION_1
mdefine_line|#define XLOG_VERSION_1&t;&t;1
DECL|macro|XLOG_VERSION_2
mdefine_line|#define XLOG_VERSION_2&t;&t;2&t;&t;/* Large IClogs, Log sunit */
DECL|macro|XLOG_VERSION_OKBITS
mdefine_line|#define XLOG_VERSION_OKBITS&t;(XLOG_VERSION_1 | XLOG_VERSION_2)
DECL|macro|XLOG_RECORD_BSIZE
mdefine_line|#define XLOG_RECORD_BSIZE&t;(16*1024)&t;/* eventually 32k */
DECL|macro|XLOG_BIG_RECORD_BSIZE
mdefine_line|#define XLOG_BIG_RECORD_BSIZE&t;(32*1024)&t;/* 32k buffers */
DECL|macro|XLOG_MAX_RECORD_BSIZE
mdefine_line|#define XLOG_MAX_RECORD_BSIZE&t;(256*1024)
DECL|macro|XLOG_HEADER_CYCLE_SIZE
mdefine_line|#define XLOG_HEADER_CYCLE_SIZE&t;(32*1024)&t;/* cycle data in header */
DECL|macro|XLOG_RECORD_BSHIFT
mdefine_line|#define XLOG_RECORD_BSHIFT&t;14&t;&t;/* 16384 == 1 &lt;&lt; 14 */
DECL|macro|XLOG_BIG_RECORD_BSHIFT
mdefine_line|#define XLOG_BIG_RECORD_BSHIFT&t;15&t;&t;/* 32k == 1 &lt;&lt; 15 */
DECL|macro|XLOG_MAX_RECORD_BSHIFT
mdefine_line|#define XLOG_MAX_RECORD_BSHIFT&t;18&t;&t;/* 256k == 1 &lt;&lt; 18 */
DECL|macro|XLOG_BTOLSUNIT
mdefine_line|#define XLOG_BTOLSUNIT(log, b)  (((b)+(log)-&gt;l_mp-&gt;m_sb.sb_logsunit-1) / &bslash;&n;                                 (log)-&gt;l_mp-&gt;m_sb.sb_logsunit)
DECL|macro|XLOG_LSUNITTOB
mdefine_line|#define XLOG_LSUNITTOB(log, su) ((su) * (log)-&gt;l_mp-&gt;m_sb.sb_logsunit)
DECL|macro|XLOG_HEADER_SIZE
mdefine_line|#define XLOG_HEADER_SIZE&t;512
DECL|macro|XLOG_REC_SHIFT
mdefine_line|#define XLOG_REC_SHIFT(log) &bslash;&n;&t;BTOBB(1 &lt;&lt; (XFS_SB_VERSION_HASLOGV2(&amp;log-&gt;l_mp-&gt;m_sb) ? &bslash;&n;&t; XLOG_MAX_RECORD_BSHIFT : XLOG_BIG_RECORD_BSHIFT))
DECL|macro|XLOG_TOTAL_REC_SHIFT
mdefine_line|#define XLOG_TOTAL_REC_SHIFT(log) &bslash;&n;&t;BTOBB(XLOG_MAX_ICLOGS &lt;&lt; (XFS_SB_VERSION_HASLOGV2(&amp;log-&gt;l_mp-&gt;m_sb) ? &bslash;&n;&t; XLOG_MAX_RECORD_BSHIFT : XLOG_BIG_RECORD_BSHIFT))
multiline_comment|/*&n; *  set lsns&n; */
DECL|macro|ASSIGN_LSN_CYCLE
mdefine_line|#define ASSIGN_LSN_CYCLE(lsn,cycle,arch) &bslash;&n;    INT_SET(((uint *)&amp;(lsn))[LSN_FIELD_CYCLE(arch)], arch, (cycle));
DECL|macro|ASSIGN_LSN_BLOCK
mdefine_line|#define ASSIGN_LSN_BLOCK(lsn,block,arch) &bslash;&n;    INT_SET(((uint *)&amp;(lsn))[LSN_FIELD_BLOCK(arch)], arch, (block));
DECL|macro|ASSIGN_ANY_LSN
mdefine_line|#define ASSIGN_ANY_LSN(lsn,cycle,block,arch)  &bslash;&n;    { &bslash;&n;&t;ASSIGN_LSN_CYCLE(lsn,cycle,arch); &bslash;&n;&t;ASSIGN_LSN_BLOCK(lsn,block,arch); &bslash;&n;    }
DECL|macro|ASSIGN_LSN
mdefine_line|#define ASSIGN_LSN(lsn,log,arch) &bslash;&n;    ASSIGN_ANY_LSN(lsn,(log)-&gt;l_curr_cycle,(log)-&gt;l_curr_block,arch);
DECL|macro|XLOG_SET
mdefine_line|#define XLOG_SET(f,b)&t;&t;(((f) &amp; (b)) == (b))
DECL|macro|GET_CYCLE
mdefine_line|#define GET_CYCLE(ptr, arch) &bslash;&n;    (INT_GET(*(uint *)(ptr), arch) == XLOG_HEADER_MAGIC_NUM ? &bslash;&n;&t; INT_GET(*((uint *)(ptr)+1), arch) : &bslash;&n;&t; INT_GET(*(uint *)(ptr), arch) &bslash;&n;    )
DECL|macro|BLK_AVG
mdefine_line|#define BLK_AVG(blk1, blk2)&t;((blk1+blk2) &gt;&gt; 1)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * get client id from packed copy.&n; *&n; * this hack is here because the xlog_pack code copies four bytes&n; * of xlog_op_header containing the fields oh_clientid, oh_flags&n; * and oh_res2 into the packed copy.&n; *&n; * later on this four byte chunk is treated as an int and the&n; * client id is pulled out.&n; *&n; * this has endian issues, of course.&n; */
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|GET_CLIENT_ID
mdefine_line|#define GET_CLIENT_ID(i,arch) &bslash;&n;    ((i) &amp; 0xff)
macro_line|#else
DECL|macro|GET_CLIENT_ID
mdefine_line|#define GET_CLIENT_ID(i,arch) &bslash;&n;    ((i) &gt;&gt; 24)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XLOG_GRANT_SUB_SPACE)
r_void
id|xlog_grant_sub_space
c_func
(paren
r_struct
id|log
op_star
id|log
comma
r_int
id|bytes
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|XLOG_GRANT_SUB_SPACE
mdefine_line|#define XLOG_GRANT_SUB_SPACE(log,bytes,type)&t;&bslash;&n;&t;xlog_grant_sub_space(log,bytes,type)
macro_line|#else
DECL|macro|XLOG_GRANT_SUB_SPACE
mdefine_line|#define XLOG_GRANT_SUB_SPACE(log,bytes,type)&t;&t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (type == &squot;w&squot;) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(log)-&gt;l_grant_write_bytes -= (bytes);&t;&t;&t;&bslash;&n;&t;&t;if ((log)-&gt;l_grant_write_bytes &lt; 0) {&t;&t;&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_write_bytes += (log)-&gt;l_logsize;&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_write_cycle--;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(log)-&gt;l_grant_reserve_bytes -= (bytes);&t;&t;&bslash;&n;&t;&t;if ((log)-&gt;l_grant_reserve_bytes &lt; 0) {&t;&t;&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_reserve_bytes += (log)-&gt;l_logsize;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_reserve_cycle--;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XLOG_GRANT_ADD_SPACE)
r_void
id|xlog_grant_add_space
c_func
(paren
r_struct
id|log
op_star
id|log
comma
r_int
id|bytes
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|XLOG_GRANT_ADD_SPACE
mdefine_line|#define XLOG_GRANT_ADD_SPACE(log,bytes,type)&t;&bslash;&n;&t;xlog_grant_add_space(log,bytes,type)
macro_line|#else
DECL|macro|XLOG_GRANT_ADD_SPACE
mdefine_line|#define XLOG_GRANT_ADD_SPACE(log,bytes,type)&t;&t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (type == &squot;w&squot;) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(log)-&gt;l_grant_write_bytes += (bytes);&t;&t;&t;&bslash;&n;&t;&t;if ((log)-&gt;l_grant_write_bytes &gt; (log)-&gt;l_logsize) {&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_write_bytes -= (log)-&gt;l_logsize;&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_write_cycle++;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(log)-&gt;l_grant_reserve_bytes += (bytes);&t;&t;&bslash;&n;&t;&t;if ((log)-&gt;l_grant_reserve_bytes &gt; (log)-&gt;l_logsize) {&t;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_reserve_bytes -= (log)-&gt;l_logsize;&bslash;&n;&t;&t;&t;(log)-&gt;l_grant_reserve_cycle++;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }
macro_line|#endif
DECL|macro|XLOG_INS_TICKETQ
mdefine_line|#define XLOG_INS_TICKETQ(q,tic)&t;&t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (q) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(tic)-&gt;t_next&t;    = (q);&t;&t;&bslash;&n;&t;&t;(tic)-&gt;t_prev&t;    = (q)-&gt;t_prev;&t;&bslash;&n;&t;&t;(q)-&gt;t_prev-&gt;t_next = (tic);&t;&t;&bslash;&n;&t;&t;(q)-&gt;t_prev&t;    = (tic);&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(tic)-&gt;t_prev = (tic)-&gt;t_next = (tic);&t;&bslash;&n;&t;&t;(q) = (tic);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(tic)-&gt;t_flags |= XLOG_TIC_IN_Q;&t;&t;&bslash;&n;    }
DECL|macro|XLOG_DEL_TICKETQ
mdefine_line|#define XLOG_DEL_TICKETQ(q,tic)&t;&t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((tic) == (tic)-&gt;t_next) {&t;&t;&t;&bslash;&n;&t;&t;(q) = NULL;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(q) = (tic)-&gt;t_next;&t;&t;&t;&bslash;&n;&t;&t;(tic)-&gt;t_next-&gt;t_prev = (tic)-&gt;t_prev;&t;&bslash;&n;&t;&t;(tic)-&gt;t_prev-&gt;t_next = (tic)-&gt;t_next;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(tic)-&gt;t_next = (tic)-&gt;t_prev = NULL;&t;&t;&bslash;&n;&t;(tic)-&gt;t_flags &amp;= ~XLOG_TIC_IN_Q;&t;&t;&bslash;&n;    }
DECL|macro|GRANT_LOCK
mdefine_line|#define GRANT_LOCK(log)&t;&t;mutex_spinlock(&amp;(log)-&gt;l_grant_lock)
DECL|macro|GRANT_UNLOCK
mdefine_line|#define GRANT_UNLOCK(log, s)&t;mutex_spinunlock(&amp;(log)-&gt;l_grant_lock, s)
DECL|macro|LOG_LOCK
mdefine_line|#define LOG_LOCK(log)&t;&t;mutex_spinlock(&amp;(log)-&gt;l_icloglock)
DECL|macro|LOG_UNLOCK
mdefine_line|#define LOG_UNLOCK(log, s)&t;mutex_spinunlock(&amp;(log)-&gt;l_icloglock, s)
DECL|macro|xlog_panic
mdefine_line|#define xlog_panic(args...)&t;cmn_err(CE_PANIC, ## args)
DECL|macro|xlog_exit
mdefine_line|#define xlog_exit(args...)&t;cmn_err(CE_PANIC, ## args)
DECL|macro|xlog_warn
mdefine_line|#define xlog_warn(args...)&t;cmn_err(CE_WARN, ## args)
multiline_comment|/*&n; * In core log state&n; */
DECL|macro|XLOG_STATE_ACTIVE
mdefine_line|#define XLOG_STATE_ACTIVE    0x0001 /* Current IC log being written to */
DECL|macro|XLOG_STATE_WANT_SYNC
mdefine_line|#define XLOG_STATE_WANT_SYNC 0x0002 /* Want to sync this iclog; no more writes */
DECL|macro|XLOG_STATE_SYNCING
mdefine_line|#define XLOG_STATE_SYNCING   0x0004 /* This IC log is syncing */
DECL|macro|XLOG_STATE_DONE_SYNC
mdefine_line|#define XLOG_STATE_DONE_SYNC 0x0008 /* Done syncing to disk */
DECL|macro|XLOG_STATE_DO_CALLBACK
mdefine_line|#define XLOG_STATE_DO_CALLBACK &bslash;&n;&t;&t;&t;     0x0010 /* Process callback functions */
DECL|macro|XLOG_STATE_CALLBACK
mdefine_line|#define XLOG_STATE_CALLBACK  0x0020 /* Callback functions now */
DECL|macro|XLOG_STATE_DIRTY
mdefine_line|#define XLOG_STATE_DIRTY     0x0040 /* Dirty IC log, not ready for ACTIVE status*/
DECL|macro|XLOG_STATE_IOERROR
mdefine_line|#define XLOG_STATE_IOERROR   0x0080 /* IO error happened in sync&squot;ing log */
DECL|macro|XLOG_STATE_ALL
mdefine_line|#define XLOG_STATE_ALL&t;     0x7FFF /* All possible valid flags */
DECL|macro|XLOG_STATE_NOTUSED
mdefine_line|#define XLOG_STATE_NOTUSED   0x8000 /* This IC log not being used */
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Flags to log operation header&n; *&n; * The first write of a new transaction will be preceded with a start&n; * record, XLOG_START_TRANS.  Once a transaction is committed, a commit&n; * record is written, XLOG_COMMIT_TRANS.  If a single region can not fit into&n; * the remainder of the current active in-core log, it is split up into&n; * multiple regions.  Each partial region will be marked with a&n; * XLOG_CONTINUE_TRANS until the last one, which gets marked with XLOG_END_TRANS.&n; *&n; */
DECL|macro|XLOG_START_TRANS
mdefine_line|#define XLOG_START_TRANS&t;0x01&t;/* Start a new transaction */
DECL|macro|XLOG_COMMIT_TRANS
mdefine_line|#define XLOG_COMMIT_TRANS&t;0x02&t;/* Commit this transaction */
DECL|macro|XLOG_CONTINUE_TRANS
mdefine_line|#define XLOG_CONTINUE_TRANS&t;0x04&t;/* Cont this trans into new region */
DECL|macro|XLOG_WAS_CONT_TRANS
mdefine_line|#define XLOG_WAS_CONT_TRANS&t;0x08&t;/* Cont this trans into new region */
DECL|macro|XLOG_END_TRANS
mdefine_line|#define XLOG_END_TRANS&t;&t;0x10&t;/* End a continued transaction */
DECL|macro|XLOG_UNMOUNT_TRANS
mdefine_line|#define XLOG_UNMOUNT_TRANS&t;0x20&t;/* Unmount a filesystem transaction */
DECL|macro|XLOG_SKIP_TRANS
mdefine_line|#define XLOG_SKIP_TRANS&t;&t;(XLOG_COMMIT_TRANS | XLOG_CONTINUE_TRANS | &bslash;&n;&t;&t;&t;&t; XLOG_WAS_CONT_TRANS | XLOG_END_TRANS | &bslash;&n;&t;&t;&t;&t; XLOG_UNMOUNT_TRANS)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Flags to log ticket&n; */
DECL|macro|XLOG_TIC_INITED
mdefine_line|#define XLOG_TIC_INITED&t;&t;0x1&t;/* has been initialized */
DECL|macro|XLOG_TIC_PERM_RESERV
mdefine_line|#define XLOG_TIC_PERM_RESERV&t;0x2&t;/* permanent reservation */
DECL|macro|XLOG_TIC_IN_Q
mdefine_line|#define XLOG_TIC_IN_Q&t;&t;0x4
macro_line|#endif&t;/* __KERNEL__ */
DECL|macro|XLOG_UNMOUNT_TYPE
mdefine_line|#define XLOG_UNMOUNT_TYPE&t;0x556e&t;/* Un for Unmount */
multiline_comment|/*&n; * Flags for log structure&n; */
DECL|macro|XLOG_CHKSUM_MISMATCH
mdefine_line|#define XLOG_CHKSUM_MISMATCH&t;0x1&t;/* used only during recovery */
DECL|macro|XLOG_ACTIVE_RECOVERY
mdefine_line|#define XLOG_ACTIVE_RECOVERY&t;0x2&t;/* in the middle of recovery */
DECL|macro|XLOG_RECOVERY_NEEDED
mdefine_line|#define&t;XLOG_RECOVERY_NEEDED&t;0x4&t;/* log was recovered */
DECL|macro|XLOG_IO_ERROR
mdefine_line|#define XLOG_IO_ERROR&t;&t;0x8&t;/* log hit an I/O error, and being&n;&t;&t;&t;&t;&t;   shutdown */
DECL|typedef|xlog_tid_t
r_typedef
id|__uint32_t
id|xlog_tid_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Below are states for covering allocation transactions.&n; * By covering, we mean changing the h_tail_lsn in the last on-disk&n; * log write such that no allocation transactions will be re-done during&n; * recovery after a system crash. Recovery starts at the last on-disk&n; * log write.&n; *&n; * These states are used to insert dummy log entries to cover&n; * space allocation transactions which can undo non-transactional changes&n; * after a crash. Writes to a file with space&n; * already allocated do not result in any transactions. Allocations&n; * might include space beyond the EOF. So if we just push the EOF a&n; * little, the last transaction for the file could contain the wrong&n; * size. If there is no file system activity, after an allocation&n; * transaction, and the system crashes, the allocation transaction&n; * will get replayed and the file will be truncated. This could&n; * be hours/days/... after the allocation occurred.&n; *&n; * The fix for this is to do two dummy transactions when the&n; * system is idle. We need two dummy transaction because the h_tail_lsn&n; * in the log record header needs to point beyond the last possible&n; * non-dummy transaction. The first dummy changes the h_tail_lsn to&n; * the first transaction before the dummy. The second dummy causes&n; * h_tail_lsn to point to the first dummy. Recovery starts at h_tail_lsn.&n; *&n; * These dummy transactions get committed when everything&n; * is idle (after there has been some activity).&n; *&n; * There are 5 states used to control this.&n; *&n; *  IDLE -- no logging has been done on the file system or&n; *&t;&t;we are done covering previous transactions.&n; *  NEED -- logging has occurred and we need a dummy transaction&n; *&t;&t;when the log becomes idle.&n; *  DONE -- we were in the NEED state and have committed a dummy&n; *&t;&t;transaction.&n; *  NEED2 -- we detected that a dummy transaction has gone to the&n; *&t;&t;on disk log with no other transactions.&n; *  DONE2 -- we committed a dummy transaction when in the NEED2 state.&n; *&n; * There are two places where we switch states:&n; *&n; * 1.) In xfs_sync, when we detect an idle log and are in NEED or NEED2.&n; *&t;We commit the dummy transaction and switch to DONE or DONE2,&n; *&t;respectively. In all other states, we don&squot;t do anything.&n; *&n; * 2.) When we finish writing the on-disk log (xlog_state_clean_log).&n; *&n; *&t;No matter what state we are in, if this isn&squot;t the dummy&n; *&t;transaction going out, the next state is NEED.&n; *&t;So, if we aren&squot;t in the DONE or DONE2 states, the next state&n; *&t;is NEED. We can&squot;t be finishing a write of the dummy record&n; *&t;unless it was committed and the state switched to DONE or DONE2.&n; *&n; *&t;If we are in the DONE state and this was a write of the&n; *&t;&t;dummy transaction, we move to NEED2.&n; *&n; *&t;If we are in the DONE2 state and this was a write of the&n; *&t;&t;dummy transaction, we move to IDLE.&n; *&n; *&n; * Writing only one dummy transaction can get appended to&n; * one file space allocation. When this happens, the log recovery&n; * code replays the space allocation and a file could be truncated.&n; * This is why we have the NEED2 and DONE2 states before going idle.&n; */
DECL|macro|XLOG_STATE_COVER_IDLE
mdefine_line|#define XLOG_STATE_COVER_IDLE&t;0
DECL|macro|XLOG_STATE_COVER_NEED
mdefine_line|#define XLOG_STATE_COVER_NEED&t;1
DECL|macro|XLOG_STATE_COVER_DONE
mdefine_line|#define XLOG_STATE_COVER_DONE&t;2
DECL|macro|XLOG_STATE_COVER_NEED2
mdefine_line|#define XLOG_STATE_COVER_NEED2&t;3
DECL|macro|XLOG_STATE_COVER_DONE2
mdefine_line|#define XLOG_STATE_COVER_DONE2&t;4
DECL|macro|XLOG_COVER_OPS
mdefine_line|#define XLOG_COVER_OPS&t;&t;5
DECL|struct|xlog_ticket
r_typedef
r_struct
id|xlog_ticket
(brace
DECL|member|t_sema
id|sv_t
id|t_sema
suffix:semicolon
multiline_comment|/* sleep on this semaphore&t; :20 */
DECL|member|t_next
r_struct
id|xlog_ticket
op_star
id|t_next
suffix:semicolon
multiline_comment|/*&t;&t;&t;         : 4 */
DECL|member|t_prev
r_struct
id|xlog_ticket
op_star
id|t_prev
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t; : 4 */
DECL|member|t_tid
id|xlog_tid_t
id|t_tid
suffix:semicolon
multiline_comment|/* transaction identifier&t; : 4 */
DECL|member|t_curr_res
r_int
id|t_curr_res
suffix:semicolon
multiline_comment|/* current reservation in bytes : 4 */
DECL|member|t_unit_res
r_int
id|t_unit_res
suffix:semicolon
multiline_comment|/* unit reservation in bytes    : 4 */
DECL|member|t_ocnt
id|__uint8_t
id|t_ocnt
suffix:semicolon
multiline_comment|/* original count&t;&t; : 1 */
DECL|member|t_cnt
id|__uint8_t
id|t_cnt
suffix:semicolon
multiline_comment|/* current count&t;&t; : 1 */
DECL|member|t_clientid
id|__uint8_t
id|t_clientid
suffix:semicolon
multiline_comment|/* who does this belong to;&t; : 1 */
DECL|member|t_flags
id|__uint8_t
id|t_flags
suffix:semicolon
multiline_comment|/* properties of reservation&t; : 1 */
DECL|typedef|xlog_ticket_t
)brace
id|xlog_ticket_t
suffix:semicolon
macro_line|#endif
DECL|struct|xlog_op_header
r_typedef
r_struct
id|xlog_op_header
(brace
DECL|member|oh_tid
id|xlog_tid_t
id|oh_tid
suffix:semicolon
multiline_comment|/* transaction id of operation&t;:  4 b */
DECL|member|oh_len
r_int
id|oh_len
suffix:semicolon
multiline_comment|/* bytes in data region&t;&t;:  4 b */
DECL|member|oh_clientid
id|__uint8_t
id|oh_clientid
suffix:semicolon
multiline_comment|/* who sent me this&t;&t;:  1 b */
DECL|member|oh_flags
id|__uint8_t
id|oh_flags
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;:  1 b */
DECL|member|oh_res2
id|ushort
id|oh_res2
suffix:semicolon
multiline_comment|/* 32 bit align&t;&t;&t;:  2 b */
DECL|typedef|xlog_op_header_t
)brace
id|xlog_op_header_t
suffix:semicolon
multiline_comment|/* valid values for h_fmt */
DECL|macro|XLOG_FMT_UNKNOWN
mdefine_line|#define XLOG_FMT_UNKNOWN  0
DECL|macro|XLOG_FMT_LINUX_LE
mdefine_line|#define XLOG_FMT_LINUX_LE 1
DECL|macro|XLOG_FMT_LINUX_BE
mdefine_line|#define XLOG_FMT_LINUX_BE 2
DECL|macro|XLOG_FMT_IRIX_BE
mdefine_line|#define XLOG_FMT_IRIX_BE  3
multiline_comment|/* our fmt */
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|XLOG_FMT
mdefine_line|#define XLOG_FMT XLOG_FMT_LINUX_LE
macro_line|#else
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|macro|XLOG_FMT
mdefine_line|#define XLOG_FMT XLOG_FMT_LINUX_BE
macro_line|#else
macro_line|#error unknown byte order
macro_line|#endif
macro_line|#endif
DECL|struct|xlog_rec_header
r_typedef
r_struct
id|xlog_rec_header
(brace
DECL|member|h_magicno
id|uint
id|h_magicno
suffix:semicolon
multiline_comment|/* log record (LR) identifier&t;&t;:  4 */
DECL|member|h_cycle
id|uint
id|h_cycle
suffix:semicolon
multiline_comment|/* write cycle of log&t;&t;&t;:  4 */
DECL|member|h_version
r_int
id|h_version
suffix:semicolon
multiline_comment|/* LR version&t;&t;&t;&t;:  4 */
DECL|member|h_len
r_int
id|h_len
suffix:semicolon
multiline_comment|/* len in bytes; should be 64-bit aligned: 4 */
DECL|member|h_lsn
id|xfs_lsn_t
id|h_lsn
suffix:semicolon
multiline_comment|/* lsn of this LR&t;&t;&t;:  8 */
DECL|member|h_tail_lsn
id|xfs_lsn_t
id|h_tail_lsn
suffix:semicolon
multiline_comment|/* lsn of 1st LR w/ buffers not committed: 8 */
DECL|member|h_chksum
id|uint
id|h_chksum
suffix:semicolon
multiline_comment|/* may not be used; non-zero if used&t;:  4 */
DECL|member|h_prev_block
r_int
id|h_prev_block
suffix:semicolon
multiline_comment|/* block number to previous LR&t;&t;:  4 */
DECL|member|h_num_logops
r_int
id|h_num_logops
suffix:semicolon
multiline_comment|/* number of log operations in this LR&t;:  4 */
DECL|member|h_cycle_data
id|uint
id|h_cycle_data
(braket
id|XLOG_HEADER_CYCLE_SIZE
op_div
id|BBSIZE
)braket
suffix:semicolon
multiline_comment|/* new fields */
DECL|member|h_fmt
r_int
id|h_fmt
suffix:semicolon
multiline_comment|/* format of log record                 :  4 */
DECL|member|h_fs_uuid
id|uuid_t
id|h_fs_uuid
suffix:semicolon
multiline_comment|/* uuid of FS                           : 16 */
DECL|member|h_size
r_int
id|h_size
suffix:semicolon
multiline_comment|/* iclog size&t;&t;&t;&t;:  4 */
DECL|typedef|xlog_rec_header_t
)brace
id|xlog_rec_header_t
suffix:semicolon
DECL|struct|xlog_rec_ext_header
r_typedef
r_struct
id|xlog_rec_ext_header
(brace
DECL|member|xh_cycle
id|uint
id|xh_cycle
suffix:semicolon
multiline_comment|/* write cycle of log&t;&t;&t;: 4 */
DECL|member|xh_cycle_data
id|uint
id|xh_cycle_data
(braket
id|XLOG_HEADER_CYCLE_SIZE
op_div
id|BBSIZE
)braket
suffix:semicolon
multiline_comment|/*&t;: 256 */
DECL|typedef|xlog_rec_ext_header_t
)brace
id|xlog_rec_ext_header_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * - A log record header is 512 bytes.  There is plenty of room to grow the&n; *&t;xlog_rec_header_t into the reserved space.&n; * - ic_data follows, so a write to disk can start at the beginning of&n; *&t;the iclog.&n; * - ic_forcesema is used to implement synchronous forcing of the iclog to disk.&n; * - ic_next is the pointer to the next iclog in the ring.&n; * - ic_bp is a pointer to the buffer used to write this incore log to disk.&n; * - ic_log is a pointer back to the global log structure.&n; * - ic_callback is a linked list of callback function/argument pairs to be&n; *&t;called after an iclog finishes writing.&n; * - ic_size is the full size of the header plus data.&n; * - ic_offset is the current number of bytes written to in this iclog.&n; * - ic_refcnt is bumped when someone is writing to the log.&n; * - ic_state is the state of the iclog.&n; */
DECL|struct|xlog_iclog_fields
r_typedef
r_struct
id|xlog_iclog_fields
(brace
DECL|member|ic_forcesema
id|sv_t
id|ic_forcesema
suffix:semicolon
DECL|member|ic_writesema
id|sv_t
id|ic_writesema
suffix:semicolon
DECL|member|ic_next
r_struct
id|xlog_in_core
op_star
id|ic_next
suffix:semicolon
DECL|member|ic_prev
r_struct
id|xlog_in_core
op_star
id|ic_prev
suffix:semicolon
DECL|member|ic_bp
r_struct
id|xfs_buf
op_star
id|ic_bp
suffix:semicolon
DECL|member|ic_log
r_struct
id|log
op_star
id|ic_log
suffix:semicolon
DECL|member|ic_callback
id|xfs_log_callback_t
op_star
id|ic_callback
suffix:semicolon
DECL|member|ic_callback_tail
id|xfs_log_callback_t
op_star
op_star
id|ic_callback_tail
suffix:semicolon
macro_line|#ifdef XFS_LOG_TRACE
DECL|member|ic_trace
r_struct
id|ktrace
op_star
id|ic_trace
suffix:semicolon
macro_line|#endif
DECL|member|ic_size
r_int
id|ic_size
suffix:semicolon
DECL|member|ic_offset
r_int
id|ic_offset
suffix:semicolon
DECL|member|ic_refcnt
r_int
id|ic_refcnt
suffix:semicolon
DECL|member|ic_bwritecnt
r_int
id|ic_bwritecnt
suffix:semicolon
DECL|member|ic_state
id|ushort_t
id|ic_state
suffix:semicolon
DECL|member|ic_datap
r_char
op_star
id|ic_datap
suffix:semicolon
multiline_comment|/* pointer to iclog data */
DECL|typedef|xlog_iclog_fields_t
)brace
id|xlog_iclog_fields_t
suffix:semicolon
DECL|union|xlog_in_core2
r_typedef
r_union
id|xlog_in_core2
(brace
DECL|member|hic_header
id|xlog_rec_header_t
id|hic_header
suffix:semicolon
DECL|member|hic_xheader
id|xlog_rec_ext_header_t
id|hic_xheader
suffix:semicolon
DECL|member|hic_sector
r_char
id|hic_sector
(braket
id|XLOG_HEADER_SIZE
)braket
suffix:semicolon
DECL|typedef|xlog_in_core_2_t
)brace
id|xlog_in_core_2_t
suffix:semicolon
DECL|struct|xlog_in_core
r_typedef
r_struct
id|xlog_in_core
(brace
DECL|member|hic_fields
id|xlog_iclog_fields_t
id|hic_fields
suffix:semicolon
DECL|member|hic_data
id|xlog_in_core_2_t
op_star
id|hic_data
suffix:semicolon
DECL|typedef|xlog_in_core_t
)brace
id|xlog_in_core_t
suffix:semicolon
multiline_comment|/*&n; * Defines to save our code from this glop.&n; */
DECL|macro|ic_forcesema
mdefine_line|#define&t;ic_forcesema&t;hic_fields.ic_forcesema
DECL|macro|ic_writesema
mdefine_line|#define ic_writesema&t;hic_fields.ic_writesema
DECL|macro|ic_next
mdefine_line|#define&t;ic_next&t;&t;hic_fields.ic_next
DECL|macro|ic_prev
mdefine_line|#define&t;ic_prev&t;&t;hic_fields.ic_prev
DECL|macro|ic_bp
mdefine_line|#define&t;ic_bp&t;&t;hic_fields.ic_bp
DECL|macro|ic_log
mdefine_line|#define&t;ic_log&t;&t;hic_fields.ic_log
DECL|macro|ic_callback
mdefine_line|#define&t;ic_callback&t;hic_fields.ic_callback
DECL|macro|ic_callback_tail
mdefine_line|#define&t;ic_callback_tail hic_fields.ic_callback_tail
DECL|macro|ic_trace
mdefine_line|#define&t;ic_trace&t;hic_fields.ic_trace
DECL|macro|ic_size
mdefine_line|#define&t;ic_size&t;&t;hic_fields.ic_size
DECL|macro|ic_offset
mdefine_line|#define&t;ic_offset&t;hic_fields.ic_offset
DECL|macro|ic_refcnt
mdefine_line|#define&t;ic_refcnt&t;hic_fields.ic_refcnt
DECL|macro|ic_bwritecnt
mdefine_line|#define&t;ic_bwritecnt&t;hic_fields.ic_bwritecnt
DECL|macro|ic_state
mdefine_line|#define&t;ic_state&t;hic_fields.ic_state
DECL|macro|ic_datap
mdefine_line|#define ic_datap&t;hic_fields.ic_datap
DECL|macro|ic_header
mdefine_line|#define ic_header&t;hic_data-&gt;hic_header
multiline_comment|/*&n; * The reservation head lsn is not made up of a cycle number and block number.&n; * Instead, it uses a cycle number and byte number.  Logs don&squot;t expect to&n; * overflow 31 bits worth of byte offset, so using a byte number will mean&n; * that round off problems won&squot;t occur when releasing partial reservations.&n; */
DECL|struct|log
r_typedef
r_struct
id|log
(brace
multiline_comment|/* The following block of fields are changed while holding icloglock */
DECL|member|l_flushsema
id|sema_t
id|l_flushsema
suffix:semicolon
multiline_comment|/* iclog flushing semaphore */
DECL|member|l_flushcnt
r_int
id|l_flushcnt
suffix:semicolon
multiline_comment|/* # of procs waiting on this&n;&t;&t;&t;&t;&t;&t; * sema */
DECL|member|l_ticket_cnt
r_int
id|l_ticket_cnt
suffix:semicolon
multiline_comment|/* free ticket count */
DECL|member|l_ticket_tcnt
r_int
id|l_ticket_tcnt
suffix:semicolon
multiline_comment|/* total ticket count */
DECL|member|l_covered_state
r_int
id|l_covered_state
suffix:semicolon
multiline_comment|/* state of &quot;covering disk&n;&t;&t;&t;&t;&t;&t; * log entries&quot; */
DECL|member|l_freelist
id|xlog_ticket_t
op_star
id|l_freelist
suffix:semicolon
multiline_comment|/* free list of tickets */
DECL|member|l_unmount_free
id|xlog_ticket_t
op_star
id|l_unmount_free
suffix:semicolon
multiline_comment|/* kmem_free these addresses */
DECL|member|l_tail
id|xlog_ticket_t
op_star
id|l_tail
suffix:semicolon
multiline_comment|/* free list of tickets */
DECL|member|l_iclog
id|xlog_in_core_t
op_star
id|l_iclog
suffix:semicolon
multiline_comment|/* head log queue&t;*/
DECL|member|l_icloglock
id|lock_t
id|l_icloglock
suffix:semicolon
multiline_comment|/* grab to change iclog state */
DECL|member|l_tail_lsn
id|xfs_lsn_t
id|l_tail_lsn
suffix:semicolon
multiline_comment|/* lsn of 1st LR with unflushed&n;&t;&t;&t;&t;&t;&t; * buffers */
DECL|member|l_last_sync_lsn
id|xfs_lsn_t
id|l_last_sync_lsn
suffix:semicolon
multiline_comment|/* lsn of last LR on disk */
DECL|member|l_mp
r_struct
id|xfs_mount
op_star
id|l_mp
suffix:semicolon
multiline_comment|/* mount point */
DECL|member|l_xbuf
r_struct
id|xfs_buf
op_star
id|l_xbuf
suffix:semicolon
multiline_comment|/* extra buffer for log&n;&t;&t;&t;&t;&t;&t; * wrapping */
DECL|member|l_targ
r_struct
id|xfs_buftarg
op_star
id|l_targ
suffix:semicolon
multiline_comment|/* buftarg of log */
DECL|member|l_logBBstart
id|xfs_daddr_t
id|l_logBBstart
suffix:semicolon
multiline_comment|/* start block of log */
DECL|member|l_logsize
r_int
id|l_logsize
suffix:semicolon
multiline_comment|/* size of log in bytes */
DECL|member|l_logBBsize
r_int
id|l_logBBsize
suffix:semicolon
multiline_comment|/* size of log in BB chunks */
DECL|member|l_curr_cycle
r_int
id|l_curr_cycle
suffix:semicolon
multiline_comment|/* Cycle number of log writes */
DECL|member|l_prev_cycle
r_int
id|l_prev_cycle
suffix:semicolon
multiline_comment|/* Cycle number before last&n;&t;&t;&t;&t;&t;&t; * block increment */
DECL|member|l_curr_block
r_int
id|l_curr_block
suffix:semicolon
multiline_comment|/* current logical log block */
DECL|member|l_prev_block
r_int
id|l_prev_block
suffix:semicolon
multiline_comment|/* previous logical log block */
DECL|member|l_iclog_size
r_int
id|l_iclog_size
suffix:semicolon
multiline_comment|/* size of log in bytes */
DECL|member|l_iclog_size_log
r_int
id|l_iclog_size_log
suffix:semicolon
multiline_comment|/* log power size of log */
DECL|member|l_iclog_bufs
r_int
id|l_iclog_bufs
suffix:semicolon
multiline_comment|/* number of iclog buffers */
multiline_comment|/* The following field are used for debugging; need to hold icloglock */
DECL|member|l_iclog_bak
r_char
op_star
id|l_iclog_bak
(braket
id|XLOG_MAX_ICLOGS
)braket
suffix:semicolon
multiline_comment|/* The following block of fields are changed while holding grant_lock */
DECL|member|l_grant_lock
id|lock_t
id|l_grant_lock
suffix:semicolon
DECL|member|l_reserve_headq
id|xlog_ticket_t
op_star
id|l_reserve_headq
suffix:semicolon
DECL|member|l_write_headq
id|xlog_ticket_t
op_star
id|l_write_headq
suffix:semicolon
DECL|member|l_grant_reserve_cycle
r_int
id|l_grant_reserve_cycle
suffix:semicolon
DECL|member|l_grant_reserve_bytes
r_int
id|l_grant_reserve_bytes
suffix:semicolon
DECL|member|l_grant_write_cycle
r_int
id|l_grant_write_cycle
suffix:semicolon
DECL|member|l_grant_write_bytes
r_int
id|l_grant_write_bytes
suffix:semicolon
multiline_comment|/* The following fields don&squot;t need locking */
macro_line|#ifdef XFS_LOG_TRACE
DECL|member|l_trace
r_struct
id|ktrace
op_star
id|l_trace
suffix:semicolon
DECL|member|l_grant_trace
r_struct
id|ktrace
op_star
id|l_grant_trace
suffix:semicolon
macro_line|#endif
DECL|member|l_flags
id|uint
id|l_flags
suffix:semicolon
DECL|member|l_quotaoffs_flag
id|uint
id|l_quotaoffs_flag
suffix:semicolon
multiline_comment|/* XFS_DQ_*, for QUOTAOFFs */
DECL|member|l_buf_cancel_table
r_struct
id|xfs_buf_cancel
op_star
op_star
id|l_buf_cancel_table
suffix:semicolon
DECL|member|l_iclog_hsize
r_int
id|l_iclog_hsize
suffix:semicolon
multiline_comment|/* size of iclog header */
DECL|member|l_iclog_heads
r_int
id|l_iclog_heads
suffix:semicolon
multiline_comment|/* # of iclog header sectors */
DECL|member|l_sectbb_log
id|uint
id|l_sectbb_log
suffix:semicolon
multiline_comment|/* log2 of sector size in BBs */
DECL|member|l_sectbb_mask
id|uint
id|l_sectbb_mask
suffix:semicolon
multiline_comment|/* sector size (in BBs)&n;&t;&t;&t;&t;&t;&t; * alignment mask */
DECL|typedef|xlog_t
)brace
id|xlog_t
suffix:semicolon
multiline_comment|/* common routines */
r_extern
id|xfs_lsn_t
id|xlog_assign_tail_lsn
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_extern
r_int
id|xlog_find_head
c_func
(paren
id|xlog_t
op_star
id|log
comma
id|xfs_daddr_t
op_star
id|head_blk
)paren
suffix:semicolon
r_extern
r_int
id|xlog_find_tail
c_func
(paren
id|xlog_t
op_star
id|log
comma
id|xfs_daddr_t
op_star
id|head_blk
comma
id|xfs_daddr_t
op_star
id|tail_blk
comma
r_int
id|readonly
)paren
suffix:semicolon
r_extern
r_int
id|xlog_recover
c_func
(paren
id|xlog_t
op_star
id|log
comma
r_int
id|readonly
)paren
suffix:semicolon
r_extern
r_int
id|xlog_recover_finish
c_func
(paren
id|xlog_t
op_star
id|log
comma
r_int
id|mfsi_flags
)paren
suffix:semicolon
r_extern
r_void
id|xlog_pack_data
c_func
(paren
id|xlog_t
op_star
id|log
comma
id|xlog_in_core_t
op_star
id|iclog
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xlog_recover_process_iunlinks
c_func
(paren
id|xlog_t
op_star
id|log
)paren
suffix:semicolon
r_extern
r_struct
id|xfs_buf
op_star
id|xlog_get_bp
c_func
(paren
id|xlog_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xlog_put_bp
c_func
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xlog_bread
c_func
(paren
id|xlog_t
op_star
comma
id|xfs_daddr_t
comma
r_int
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_extern
id|xfs_caddr_t
id|xlog_align
c_func
(paren
id|xlog_t
op_star
comma
id|xfs_daddr_t
comma
r_int
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
multiline_comment|/* iclog tracing */
DECL|macro|XLOG_TRACE_GRAB_FLUSH
mdefine_line|#define XLOG_TRACE_GRAB_FLUSH  1
DECL|macro|XLOG_TRACE_REL_FLUSH
mdefine_line|#define XLOG_TRACE_REL_FLUSH   2
DECL|macro|XLOG_TRACE_SLEEP_FLUSH
mdefine_line|#define XLOG_TRACE_SLEEP_FLUSH 3
DECL|macro|XLOG_TRACE_WAKE_FLUSH
mdefine_line|#define XLOG_TRACE_WAKE_FLUSH  4
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_LOG_PRIV_H__ */
eof
