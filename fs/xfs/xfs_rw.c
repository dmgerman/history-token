multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
multiline_comment|/*&n; * This is a subroutine for xfs_write() and other writers (xfs_ioctl)&n; * which clears the setuid and setgid bits when a file is written.&n; */
r_int
DECL|function|xfs_write_clear_setuid
id|xfs_write_clear_setuid
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
r_int
id|error
suffix:semicolon
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_WRITEID
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
l_int|0
comma
id|XFS_WRITEID_LOG_RES
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
id|ip-&gt;i_d.di_mode
op_and_assign
op_complement
id|ISUID
suffix:semicolon
multiline_comment|/*&n;&t; * Note that we don&squot;t have to worry about mandatory&n;&t; * file locking being disabled here because we only&n;&t; * clear the ISGID bit if the Group execute bit is&n;&t; * on, but if it was on then mandatory locking wouldn&squot;t&n;&t; * have been enabled.&n;&t; */
r_if
c_cond
(paren
id|ip-&gt;i_d.di_mode
op_amp
(paren
id|IEXEC
op_rshift
l_int|3
)paren
)paren
(brace
id|ip-&gt;i_d.di_mode
op_and_assign
op_complement
id|ISGID
suffix:semicolon
)brace
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
id|xfs_trans_set_sync
c_func
(paren
id|tp
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
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Force a shutdown of the filesystem instantly while keeping&n; * the filesystem consistent. We don&squot;t do an unmount here; just shutdown&n; * the shop, make sure that absolutely nothing persistent happens to&n; * this filesystem after this point.&n; */
r_void
DECL|function|xfs_do_force_shutdown
id|xfs_do_force_shutdown
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
r_int
id|flags
comma
r_char
op_star
id|fname
comma
r_int
id|lnnum
)paren
(brace
r_int
id|logerror
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|mp
op_assign
id|XFS_BHVTOM
c_func
(paren
id|bdp
)paren
suffix:semicolon
id|logerror
op_assign
id|flags
op_amp
id|XFS_LOG_IO_ERROR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_FORCE_UMOUNT
)paren
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_NOTE
comma
l_string|&quot;xfs_force_shutdown(%s,0x%x) called from line %d of file %s.  Return address = 0x%x&quot;
comma
id|mp-&gt;m_fsname
comma
id|flags
comma
id|lnnum
comma
id|fname
comma
id|__return_address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No need to duplicate efforts.&n;&t; */
r_if
c_cond
(paren
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
op_logical_and
op_logical_neg
id|logerror
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * This flags XFS_MOUNT_FS_SHUTDOWN, makes sure that we don&squot;t&n;&t; * queue up anybody new on the log reservations, and wakes up&n;&t; * everybody who&squot;s sleeping on log reservations and tells&n;&t; * them the bad news.&n;&t; */
r_if
c_cond
(paren
id|xfs_log_force_umount
c_func
(paren
id|mp
comma
id|logerror
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|XFS_CORRUPT_INCORE
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_ALERT
comma
l_string|&quot;Corruption of in-memory data detected.  Shutting down filesystem: %s&quot;
comma
id|mp-&gt;m_fsname
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_FORCE_UMOUNT
)paren
)paren
(brace
r_if
c_cond
(paren
id|logerror
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_ALERT
comma
l_string|&quot;Log I/O Error Detected.  Shutting down filesystem: %s&quot;
comma
id|mp-&gt;m_fsname
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_SHUTDOWN_REMOTE_REQ
)paren
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_ALERT
comma
l_string|&quot;I/O Error Detected.  Shutting down filesystem: %s&quot;
comma
id|mp-&gt;m_fsname
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_FORCE_UMOUNT
)paren
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_ALERT
comma
l_string|&quot;Please umount the filesystem, and rectify the problem(s)&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called when we want to stop a buffer from getting written or read.&n; * We attach the EIO error, muck with its flags, and call biodone&n; * so that the proper iodone callbacks get called.&n; */
r_int
DECL|function|xfs_bioerror
id|xfs_bioerror
c_func
(paren
id|xfs_buf_t
op_star
id|bp
)paren
(brace
macro_line|#ifdef XFSERRORDEBUG
id|ASSERT
c_func
(paren
id|XFS_BUF_ISREAD
c_func
(paren
id|bp
)paren
op_logical_or
id|bp-&gt;b_iodone
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * No need to wait until the buffer is unpinned.&n;&t; * We aren&squot;t flushing it.&n;&t; */
id|xfs_buftrace
c_func
(paren
l_string|&quot;XFS IOERROR&quot;
comma
id|bp
)paren
suffix:semicolon
id|XFS_BUF_ERROR
c_func
(paren
id|bp
comma
id|EIO
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We&squot;re calling biodone, so delete B_DONE flag. Either way&n;&t; * we have to call the iodone callback, and calling biodone&n;&t; * probably is the best way since it takes care of&n;&t; * GRIO as well.&n;&t; */
id|XFS_BUF_UNREAD
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_UNDELAYWRITE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_UNDONE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_STALE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_CLR_BDSTRAT_FUNC
c_func
(paren
id|bp
)paren
suffix:semicolon
id|xfs_biodone
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
(paren
id|EIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Same as xfs_bioerror, except that we are releasing the buffer&n; * here ourselves, and avoiding the biodone call.&n; * This is meant for userdata errors; metadata bufs come with&n; * iodone functions attached, so that we can track down errors.&n; */
r_int
DECL|function|xfs_bioerror_relse
id|xfs_bioerror_relse
c_func
(paren
id|xfs_buf_t
op_star
id|bp
)paren
(brace
r_int64
id|fl
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_BUF_IODONE_FUNC
c_func
(paren
id|bp
)paren
op_ne
id|xfs_buf_iodone_callbacks
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_BUF_IODONE_FUNC
c_func
(paren
id|bp
)paren
op_ne
id|xlog_iodone
)paren
suffix:semicolon
id|xfs_buftrace
c_func
(paren
l_string|&quot;XFS IOERRELSE&quot;
comma
id|bp
)paren
suffix:semicolon
id|fl
op_assign
id|XFS_BUF_BFLAGS
c_func
(paren
id|bp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * No need to wait until the buffer is unpinned.&n;&t; * We aren&squot;t flushing it.&n;&t; *&n;&t; * chunkhold expects B_DONE to be set, whether&n;&t; * we actually finish the I/O or not. We don&squot;t want to&n;&t; * change that interface.&n;&t; */
id|XFS_BUF_UNREAD
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_UNDELAYWRITE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_DONE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_STALE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_CLR_IODONE_FUNC
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_CLR_BDSTRAT_FUNC
c_func
(paren
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fl
op_amp
id|XFS_B_ASYNC
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Mark b_error and B_ERROR _both_.&n;&t;&t; * Lot&squot;s of chunkcache code assumes that.&n;&t;&t; * There&squot;s no reason to mark error for&n;&t;&t; * ASYNC buffers.&n;&t;&t; */
id|XFS_BUF_ERROR
c_func
(paren
id|bp
comma
id|EIO
)paren
suffix:semicolon
id|XFS_BUF_V_IODONESEMA
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
r_else
(brace
id|xfs_buf_relse
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
r_return
(paren
id|EIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Prints out an ALERT message about I/O error.&n; */
r_void
DECL|function|xfs_ioerror_alert
id|xfs_ioerror_alert
c_func
(paren
r_char
op_star
id|func
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_buf_t
op_star
id|bp
comma
id|xfs_daddr_t
id|blkno
)paren
(brace
id|cmn_err
c_func
(paren
id|CE_ALERT
comma
l_string|&quot;I/O error in filesystem (&bslash;&quot;%s&bslash;&quot;) meta-data dev 0x%x block 0x%llx&bslash;n&quot;
l_string|&quot;&t; (&bslash;&quot;%s&bslash;&quot;) error %d buf count %u&quot;
comma
(paren
op_logical_neg
id|mp
op_logical_or
op_logical_neg
id|mp-&gt;m_fsname
)paren
ques
c_cond
l_string|&quot;(fs name not set)&quot;
suffix:colon
id|mp-&gt;m_fsname
comma
id|XFS_BUF_TARGET_DEV
c_func
(paren
id|bp
)paren
comma
(paren
id|__uint64_t
)paren
id|blkno
comma
id|func
comma
id|XFS_BUF_GETERROR
c_func
(paren
id|bp
)paren
comma
id|XFS_BUF_COUNT
c_func
(paren
id|bp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This isn&squot;t an absolute requirement, but it is&n; * just a good idea to call xfs_read_buf instead of&n; * directly doing a read_buf call. For one, we shouldn&squot;t&n; * be doing this disk read if we are in SHUTDOWN state anyway,&n; * so this stops that from happening. Secondly, this does all&n; * the error checking stuff and the brelse if appropriate for&n; * the caller, so the code can be a little leaner.&n; */
r_int
DECL|function|xfs_read_buf
id|xfs_read_buf
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_buftarg_t
op_star
id|target
comma
id|xfs_daddr_t
id|blkno
comma
r_int
id|len
comma
id|uint
id|flags
comma
id|xfs_buf_t
op_star
op_star
id|bpp
)paren
(brace
id|xfs_buf_t
op_star
id|bp
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|flags
)paren
id|bp
op_assign
id|xfs_buf_read_flags
c_func
(paren
id|target
comma
id|blkno
comma
id|len
comma
id|flags
)paren
suffix:semicolon
r_else
id|bp
op_assign
id|xfs_buf_read
c_func
(paren
id|target
comma
id|blkno
comma
id|len
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EIO
)paren
suffix:semicolon
id|error
op_assign
id|XFS_BUF_GETERROR
c_func
(paren
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp
op_logical_and
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
(brace
op_star
id|bpp
op_assign
id|bp
suffix:semicolon
)brace
r_else
(brace
op_star
id|bpp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_ioerror_alert
c_func
(paren
l_string|&quot;xfs_read_buf&quot;
comma
id|mp
comma
id|bp
comma
id|XFS_BUF_ADDR
c_func
(paren
id|bp
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|XFS_ERROR
c_func
(paren
id|EIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bp
)paren
(brace
id|XFS_BUF_UNDONE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_UNDELAYWRITE
c_func
(paren
id|bp
)paren
suffix:semicolon
id|XFS_BUF_STALE
c_func
(paren
id|bp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * brelse clears B_ERROR and b_error&n;&t;&t;&t; */
id|xfs_buf_relse
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Wrapper around bwrite() so that we can trap&n; * write errors, and act accordingly.&n; */
r_int
DECL|function|xfs_bwrite
id|xfs_bwrite
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_struct
id|xfs_buf
op_star
id|bp
)paren
(brace
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * XXXsup how does this work for quotas.&n;&t; */
id|XFS_BUF_SET_BDSTRAT_FUNC
c_func
(paren
id|bp
comma
id|xfs_bdstrat_cb
)paren
suffix:semicolon
id|XFS_BUF_SET_FSPRIVATE3
c_func
(paren
id|bp
comma
id|mp
)paren
suffix:semicolon
id|XFS_BUF_WRITE
c_func
(paren
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|XFS_bwrite
c_func
(paren
id|bp
)paren
)paren
)paren
(brace
id|ASSERT
c_func
(paren
id|mp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Cannot put a buftrace here since if the buffer is not&n;&t;&t; * B_HOLD then we will brelse() the buffer before returning&n;&t;&t; * from bwrite and we could be tracing a buffer that has&n;&t;&t; * been reused.&n;&t;&t; */
id|xfs_force_shutdown
c_func
(paren
id|mp
comma
id|XFS_METADATA_IO_ERROR
)paren
suffix:semicolon
)brace
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * xfs_inval_cached_pages()&n; * This routine is responsible for keeping direct I/O and buffered I/O&n; * somewhat coherent.  From here we make sure that we&squot;re at least&n; * temporarily holding the inode I/O lock exclusively and then call&n; * the page cache to flush and invalidate any cached pages.  If there&n; * are no cached pages this routine will be very quick.&n; */
r_void
DECL|function|xfs_inval_cached_pages
id|xfs_inval_cached_pages
c_func
(paren
id|vnode_t
op_star
id|vp
comma
id|xfs_iocore_t
op_star
id|io
comma
id|xfs_off_t
id|offset
comma
r_int
id|write
comma
r_int
id|relock
)paren
(brace
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|VN_CACHED
c_func
(paren
id|vp
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|mp
op_assign
id|io-&gt;io_mount
suffix:semicolon
multiline_comment|/*&n;&t; * We need to get the I/O lock exclusively in order&n;&t; * to safely invalidate pages and mappings.&n;&t; */
r_if
c_cond
(paren
id|relock
)paren
(brace
id|XFS_IUNLOCK
c_func
(paren
id|mp
comma
id|io
comma
id|XFS_IOLOCK_SHARED
)paren
suffix:semicolon
id|XFS_ILOCK
c_func
(paren
id|mp
comma
id|io
comma
id|XFS_IOLOCK_EXCL
)paren
suffix:semicolon
)brace
multiline_comment|/* Writing beyond EOF creates a hole that must be zeroed */
r_if
c_cond
(paren
id|write
op_logical_and
(paren
id|offset
OG
id|XFS_SIZE
c_func
(paren
id|mp
comma
id|io
)paren
)paren
)paren
(brace
id|xfs_fsize_t
id|isize
suffix:semicolon
id|XFS_ILOCK
c_func
(paren
id|mp
comma
id|io
comma
id|XFS_ILOCK_EXCL
op_or
id|XFS_EXTSIZE_RD
)paren
suffix:semicolon
id|isize
op_assign
id|XFS_SIZE
c_func
(paren
id|mp
comma
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|isize
)paren
(brace
id|xfs_zero_eof
c_func
(paren
id|vp
comma
id|io
comma
id|offset
comma
id|isize
comma
id|offset
)paren
suffix:semicolon
)brace
id|XFS_IUNLOCK
c_func
(paren
id|mp
comma
id|io
comma
id|XFS_ILOCK_EXCL
op_or
id|XFS_EXTSIZE_RD
)paren
suffix:semicolon
)brace
id|VOP_FLUSHINVAL_PAGES
c_func
(paren
id|vp
comma
id|ctooff
c_func
(paren
id|offtoct
c_func
(paren
id|offset
)paren
)paren
comma
op_minus
l_int|1
comma
id|FI_REMAPF_LOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|relock
)paren
(brace
id|XFS_ILOCK_DEMOTE
c_func
(paren
id|mp
comma
id|io
comma
id|XFS_IOLOCK_EXCL
)paren
suffix:semicolon
)brace
)brace
DECL|variable|xfs_refcache_lock
id|spinlock_t
id|xfs_refcache_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|xfs_refcache
id|xfs_inode_t
op_star
op_star
id|xfs_refcache
suffix:semicolon
DECL|variable|xfs_refcache_size
r_int
id|xfs_refcache_size
suffix:semicolon
DECL|variable|xfs_refcache_index
r_int
id|xfs_refcache_index
suffix:semicolon
DECL|variable|xfs_refcache_busy
r_int
id|xfs_refcache_busy
suffix:semicolon
DECL|variable|xfs_refcache_count
r_int
id|xfs_refcache_count
suffix:semicolon
multiline_comment|/*&n; * Timer callback to mark SB dirty, make sure we keep purging refcache&n; */
r_void
DECL|function|xfs_refcache_sbdirty
id|xfs_refcache_sbdirty
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert the given inode into the reference cache.&n; */
r_void
DECL|function|xfs_refcache_insert
id|xfs_refcache_insert
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|vnode_t
op_star
id|vp
suffix:semicolon
id|xfs_inode_t
op_star
id|release_ip
suffix:semicolon
id|xfs_inode_t
op_star
op_star
id|refcache
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
(paren
id|ip-&gt;i_iolock
)paren
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If an unmount is busy blowing entries out of the cache,&n;&t; * then don&squot;t bother.&n;&t; */
r_if
c_cond
(paren
id|xfs_refcache_busy
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we tuned the refcache down to zero, don&squot;t do anything.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|xfs_refcache_size
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The inode is already in the refcache, so don&squot;t bother&n;&t; * with it.&n;&t; */
r_if
c_cond
(paren
id|ip-&gt;i_refcache
op_ne
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|vp
op_assign
id|XFS_ITOV
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/* ASSERT(vp-&gt;v_count &gt; 0); */
id|VN_HOLD
c_func
(paren
id|vp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We allocate the reference cache on use so that we don&squot;t&n;&t; * waste the memory on systems not being used as NFS servers.&n;&t; */
r_if
c_cond
(paren
id|xfs_refcache
op_eq
l_int|NULL
)paren
(brace
id|refcache
op_assign
(paren
id|xfs_inode_t
op_star
op_star
)paren
id|kmem_zalloc
c_func
(paren
id|XFS_REFCACHE_SIZE_MAX
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
r_else
(brace
id|refcache
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we allocated memory for the refcache above and it still&n;&t; * needs it, then use the memory we allocated.&t;Otherwise we&squot;ll&n;&t; * free the memory below.&n;&t; */
r_if
c_cond
(paren
id|refcache
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|xfs_refcache
op_eq
l_int|NULL
)paren
(brace
id|xfs_refcache
op_assign
id|refcache
suffix:semicolon
id|refcache
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * If an unmount is busy clearing out the cache, don&squot;t add new&n;&t; * entries to it.&n;&t; */
r_if
c_cond
(paren
id|xfs_refcache_busy
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|vp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we allocated memory for the refcache above but someone&n;&t;&t; * else beat us to using it, then free the memory now.&n;&t;&t; */
r_if
c_cond
(paren
id|refcache
op_ne
l_int|NULL
)paren
(brace
id|kmem_free
c_func
(paren
id|refcache
comma
id|XFS_REFCACHE_SIZE_MAX
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|release_ip
op_assign
id|xfs_refcache
(braket
id|xfs_refcache_index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|release_ip
op_ne
l_int|NULL
)paren
(brace
id|release_ip-&gt;i_refcache
op_assign
l_int|NULL
suffix:semicolon
id|xfs_refcache_count
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_ge
l_int|0
)paren
suffix:semicolon
)brace
id|xfs_refcache
(braket
id|xfs_refcache_index
)braket
op_assign
id|ip
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_refcache
op_eq
l_int|NULL
)paren
suffix:semicolon
id|ip-&gt;i_refcache
op_assign
op_amp
(paren
id|xfs_refcache
(braket
id|xfs_refcache_index
)braket
)paren
suffix:semicolon
id|xfs_refcache_count
op_increment
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_le
id|xfs_refcache_size
)paren
suffix:semicolon
id|xfs_refcache_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|xfs_refcache_index
op_eq
id|xfs_refcache_size
)paren
(brace
id|xfs_refcache_index
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Save the pointer to the inode to be released so that we can&n;&t; * VN_RELE it once we&squot;ve dropped our inode locks in xfs_rwunlock().&n;&t; * The pointer may be NULL, but that&squot;s OK.&n;&t; */
id|ip-&gt;i_release
op_assign
id|release_ip
suffix:semicolon
multiline_comment|/*&n;&t; * If we allocated memory for the refcache above but someone&n;&t; * else beat us to using it, then free the memory now.&n;&t; */
r_if
c_cond
(paren
id|refcache
op_ne
l_int|NULL
)paren
(brace
id|kmem_free
c_func
(paren
id|refcache
comma
id|XFS_REFCACHE_SIZE_MAX
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * If the given inode is in the reference cache, purge its entry and&n; * release the reference on the vnode.&n; */
r_void
DECL|function|xfs_refcache_purge_ip
id|xfs_refcache_purge_ip
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|vnode_t
op_star
id|vp
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re not pointing to our entry in the cache, then&n;&t; * we must not be in the cache.&n;&t; */
r_if
c_cond
(paren
id|ip-&gt;i_refcache
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_refcache
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Clear both our pointer to the cache entry and its pointer&n;&t; * back to us.&n;&t; */
id|ASSERT
c_func
(paren
op_star
(paren
id|ip-&gt;i_refcache
)paren
op_eq
id|ip
)paren
suffix:semicolon
op_star
(paren
id|ip-&gt;i_refcache
)paren
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;i_refcache
op_assign
l_int|NULL
suffix:semicolon
id|xfs_refcache_count
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_ge
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
id|vp
op_assign
id|XFS_ITOV
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/* ASSERT(vp-&gt;v_count &gt; 1); */
id|VOP_RELEASE
c_func
(paren
id|vp
comma
id|error
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|vp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called from the XFS unmount code to purge all entries for the&n; * given mount from the cache.&t;It uses the refcache busy counter to&n; * make sure that new entries are not added to the cache as we purge them.&n; */
r_void
DECL|function|xfs_refcache_purge_mp
id|xfs_refcache_purge_mp
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|vnode_t
op_star
id|vp
suffix:semicolon
r_int
id|error
comma
id|i
suffix:semicolon
id|xfs_inode_t
op_star
id|ip
suffix:semicolon
r_if
c_cond
(paren
id|xfs_refcache
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bumping the busy counter keeps new entries from being added&n;&t; * to the cache.  We use a counter since multiple unmounts could&n;&t; * be in here simultaneously.&n;&t; */
id|xfs_refcache_busy
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|xfs_refcache_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ip
op_assign
id|xfs_refcache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ip
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|ip-&gt;i_mount
op_eq
id|mp
)paren
)paren
(brace
id|xfs_refcache
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;i_refcache
op_assign
l_int|NULL
suffix:semicolon
id|xfs_refcache_count
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_ge
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
id|vp
op_assign
id|XFS_ITOV
c_func
(paren
id|ip
)paren
suffix:semicolon
id|VOP_RELEASE
c_func
(paren
id|vp
comma
id|error
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|vp
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
)brace
)brace
id|xfs_refcache_busy
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_busy
op_ge
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called from the XFS sync code to ensure that the refcache&n; * is emptied out over time.  We purge a small number of entries with&n; * each call.&n; */
r_void
DECL|function|xfs_refcache_purge_some
id|xfs_refcache_purge_some
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
r_int
id|error
comma
id|i
suffix:semicolon
id|xfs_inode_t
op_star
id|ip
suffix:semicolon
r_int
id|iplist_index
suffix:semicolon
id|xfs_inode_t
op_star
op_star
id|iplist
suffix:semicolon
r_int
id|purge_count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xfs_refcache
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|xfs_refcache_count
op_eq
l_int|0
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|iplist_index
op_assign
l_int|0
suffix:semicolon
id|purge_count
op_assign
id|xfs_params.refcache_purge
suffix:semicolon
id|iplist
op_assign
(paren
id|xfs_inode_t
op_star
op_star
)paren
id|kmem_zalloc
c_func
(paren
id|purge_count
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Store any inodes we find in the next several entries&n;&t; * into the iplist array to be released after dropping&n;&t; * the spinlock.  We always start looking from the currently&n;&t; * oldest place in the cache.  We move the refcache index&n;&t; * forward as we go so that we are sure to eventually clear&n;&t; * out the entire cache when the system goes idle.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|purge_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ip
op_assign
id|xfs_refcache
(braket
id|xfs_refcache_index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_ne
l_int|NULL
)paren
(brace
id|xfs_refcache
(braket
id|xfs_refcache_index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;i_refcache
op_assign
l_int|NULL
suffix:semicolon
id|xfs_refcache_count
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_ge
l_int|0
)paren
suffix:semicolon
id|iplist
(braket
id|iplist_index
)braket
op_assign
id|ip
suffix:semicolon
id|iplist_index
op_increment
suffix:semicolon
)brace
id|xfs_refcache_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|xfs_refcache_index
op_eq
id|xfs_refcache_size
)paren
(brace
id|xfs_refcache_index
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If there are still entries in the refcache,&n;&t; * set timer to mark the SB dirty to make sure that&n;&t; * we hit sync even if filesystem is idle, so that we&squot;ll&n;&t; * purge some more later.&n;&t; */
r_if
c_cond
(paren
id|xfs_refcache_count
)paren
(brace
id|del_timer_sync
c_func
(paren
op_amp
id|mp-&gt;m_sbdirty_timer
)paren
suffix:semicolon
id|mp-&gt;m_sbdirty_timer.data
op_assign
(paren
r_int
r_int
)paren
id|LINVFS_GET_IP
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|mp-&gt;m_rootip
)paren
)paren
op_member_access_from_pointer
id|i_sb
suffix:semicolon
id|mp-&gt;m_sbdirty_timer.expires
op_assign
id|jiffies
op_plus
l_int|2
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mp-&gt;m_sbdirty_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now drop the inodes we collected.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|iplist_index
suffix:semicolon
id|i
op_increment
)paren
(brace
id|VOP_RELEASE
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|iplist
(braket
id|i
)braket
)paren
comma
id|error
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|iplist
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|kmem_free
c_func
(paren
id|iplist
comma
id|purge_count
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when the refcache is dynamically resized&n; * via a sysctl.&n; *&n; * If the new size is smaller than the old size, purge all&n; * entries in slots greater than the new size, and move&n; * the index if necessary.&n; *&n; * If the refcache hasn&squot;t even been allocated yet, or the&n; * new size is larger than the old size, just set the value&n; * of xfs_refcache_size.&n; */
r_void
DECL|function|xfs_refcache_resize
id|xfs_refcache_resize
c_func
(paren
r_int
id|xfs_refcache_new_size
)paren
(brace
r_int
id|i
suffix:semicolon
id|xfs_inode_t
op_star
id|ip
suffix:semicolon
r_int
id|iplist_index
op_assign
l_int|0
suffix:semicolon
id|xfs_inode_t
op_star
op_star
id|iplist
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * If the new size is smaller than the current size,&n;&t; * purge entries to create smaller cache, and&n;&t; * reposition index if necessary.&n;&t; * Don&squot;t bother if no refcache yet.&n;&t; */
r_if
c_cond
(paren
id|xfs_refcache
op_logical_and
(paren
id|xfs_refcache_new_size
OL
id|xfs_refcache_size
)paren
)paren
(brace
id|iplist
op_assign
(paren
id|xfs_inode_t
op_star
op_star
)paren
id|kmem_zalloc
c_func
(paren
id|XFS_REFCACHE_SIZE_MAX
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|xfs_refcache_new_size
suffix:semicolon
id|i
OL
id|xfs_refcache_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ip
op_assign
id|xfs_refcache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_ne
l_int|NULL
)paren
(brace
id|xfs_refcache
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;i_refcache
op_assign
l_int|NULL
suffix:semicolon
id|xfs_refcache_count
op_decrement
suffix:semicolon
id|ASSERT
c_func
(paren
id|xfs_refcache_count
op_ge
l_int|0
)paren
suffix:semicolon
id|iplist
(braket
id|iplist_index
)braket
op_assign
id|ip
suffix:semicolon
id|iplist_index
op_increment
suffix:semicolon
)brace
)brace
id|xfs_refcache_size
op_assign
id|xfs_refcache_new_size
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Move index to beginning of cache if it&squot;s now past the end&n;&t;&t; */
r_if
c_cond
(paren
id|xfs_refcache_index
op_ge
id|xfs_refcache_new_size
)paren
id|xfs_refcache_index
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now drop the inodes we collected.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|iplist_index
suffix:semicolon
id|i
op_increment
)paren
(brace
id|VOP_RELEASE
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|iplist
(braket
id|i
)braket
)paren
comma
id|error
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|iplist
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|kmem_free
c_func
(paren
id|iplist
comma
id|XFS_REFCACHE_SIZE_MAX
op_star
r_sizeof
(paren
id|xfs_inode_t
op_star
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
id|xfs_refcache_size
op_assign
id|xfs_refcache_new_size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|xfs_refcache_lock
)paren
suffix:semicolon
)brace
)brace
eof
