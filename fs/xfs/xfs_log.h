multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_LOG_H__
DECL|macro|__XFS_LOG_H__
mdefine_line|#define __XFS_LOG_H__
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|LSN_FIELD_CYCLE
mdefine_line|#define LSN_FIELD_CYCLE(arch) (((arch)==ARCH_NOCONVERT)?1:0)
DECL|macro|LSN_FIELD_BLOCK
mdefine_line|#define LSN_FIELD_BLOCK(arch) (((arch)==ARCH_NOCONVERT)?0:1)
macro_line|#else
DECL|macro|LSN_FIELD_CYCLE
mdefine_line|#define LSN_FIELD_CYCLE(arch) (0)
DECL|macro|LSN_FIELD_BLOCK
mdefine_line|#define LSN_FIELD_BLOCK(arch) (1)
macro_line|#endif
multiline_comment|/* get lsn fields */
DECL|macro|CYCLE_LSN
mdefine_line|#define CYCLE_LSN(lsn,arch) (INT_GET(((uint *)&amp;(lsn))[LSN_FIELD_CYCLE(arch)], arch))
DECL|macro|BLOCK_LSN
mdefine_line|#define BLOCK_LSN(lsn,arch) (INT_GET(((uint *)&amp;(lsn))[LSN_FIELD_BLOCK(arch)], arch))
multiline_comment|/* this is used in a spot where we might otherwise double-endian-flip */
DECL|macro|CYCLE_LSN_NOCONV
mdefine_line|#define CYCLE_LSN_NOCONV(lsn,arch) (((uint *)&amp;(lsn))[LSN_FIELD_CYCLE(arch)])
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * By comparing each compnent, we don&squot;t have to worry about extra&n; * endian issues in treating two 32 bit numbers as one 64 bit number&n; */
r_static
macro_line|#ifdef __GNUC__
macro_line|# if !((__GNUC__ == 2) &amp;&amp; (__GNUC_MINOR__ == 95))
id|__inline__
macro_line|#endif
macro_line|#endif
DECL|function|_lsn_cmp
id|xfs_lsn_t
id|_lsn_cmp
c_func
(paren
id|xfs_lsn_t
id|lsn1
comma
id|xfs_lsn_t
id|lsn2
comma
id|xfs_arch_t
id|arch
)paren
(brace
r_if
c_cond
(paren
id|CYCLE_LSN
c_func
(paren
id|lsn1
comma
id|arch
)paren
op_ne
id|CYCLE_LSN
c_func
(paren
id|lsn2
comma
id|arch
)paren
)paren
r_return
(paren
id|CYCLE_LSN
c_func
(paren
id|lsn1
comma
id|arch
)paren
OL
id|CYCLE_LSN
c_func
(paren
id|lsn2
comma
id|arch
)paren
)paren
ques
c_cond
op_minus
l_int|999
suffix:colon
l_int|999
suffix:semicolon
r_if
c_cond
(paren
id|BLOCK_LSN
c_func
(paren
id|lsn1
comma
id|arch
)paren
op_ne
id|BLOCK_LSN
c_func
(paren
id|lsn2
comma
id|arch
)paren
)paren
r_return
(paren
id|BLOCK_LSN
c_func
(paren
id|lsn1
comma
id|arch
)paren
OL
id|BLOCK_LSN
c_func
(paren
id|lsn2
comma
id|arch
)paren
)paren
ques
c_cond
op_minus
l_int|999
suffix:colon
l_int|999
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|XFS_LSN_CMP_ARCH
mdefine_line|#define XFS_LSN_CMP_ARCH(x,y,arch)&t;_lsn_cmp(x, y, arch)
DECL|macro|XFS_LSN_CMP
mdefine_line|#define XFS_LSN_CMP(x,y) XFS_LSN_CMP_ARCH(x,y,ARCH_NOCONVERT)
DECL|macro|XFS_LSN_DIFF_ARCH
mdefine_line|#define XFS_LSN_DIFF_ARCH(x,y,arch)&t;_lsn_cmp(x, y, arch)
DECL|macro|XFS_LSN_DIFF
mdefine_line|#define XFS_LSN_DIFF(x,y) XFS_LSN_DIFF_ARCH(x,y,ARCH_NOCONVERT)
multiline_comment|/*&n; * Macros, structures, prototypes for interface to the log manager.&n; */
multiline_comment|/*&n; * Flags to xfs_log_mount&n; */
DECL|macro|XFS_LOG_RECOVER
mdefine_line|#define XFS_LOG_RECOVER&t;&t;0x1
multiline_comment|/*&n; * Flags to xfs_log_done()&n; */
DECL|macro|XFS_LOG_REL_PERM_RESERV
mdefine_line|#define XFS_LOG_REL_PERM_RESERV 0x1
multiline_comment|/*&n; * Flags to xfs_log_reserve()&n; *&n; *&t;XFS_LOG_SLEEP:&t; If space is not available, sleep (default)&n; *&t;XFS_LOG_NOSLEEP: If space is not available, return error&n; *&t;XFS_LOG_PERM_RESERV: Permanent reservation.  When writes are&n; *&t;&t;performed against this type of reservation, the reservation&n; *&t;&t;is not decreased.  Long running transactions should use this.&n; */
DECL|macro|XFS_LOG_SLEEP
mdefine_line|#define XFS_LOG_SLEEP&t;&t;0x0
DECL|macro|XFS_LOG_NOSLEEP
mdefine_line|#define XFS_LOG_NOSLEEP&t;&t;0x1
DECL|macro|XFS_LOG_PERM_RESERV
mdefine_line|#define XFS_LOG_PERM_RESERV&t;0x2
DECL|macro|XFS_LOG_RESV_ALL
mdefine_line|#define XFS_LOG_RESV_ALL&t;(XFS_LOG_NOSLEEP|XFS_LOG_PERM_RESERV)
multiline_comment|/*&n; * Flags to xfs_log_force()&n; *&n; *&t;XFS_LOG_SYNC:&t;Synchronous force in-core log to disk&n; *&t;XFS_LOG_FORCE:&t;Start in-core log write now.&n; *&t;XFS_LOG_URGE:&t;Start write within some window of time.&n; *&n; * Note: Either XFS_LOG_FORCE or XFS_LOG_URGE must be set.&n; */
DECL|macro|XFS_LOG_SYNC
mdefine_line|#define XFS_LOG_SYNC&t;&t;0x1
DECL|macro|XFS_LOG_FORCE
mdefine_line|#define XFS_LOG_FORCE&t;&t;0x2
DECL|macro|XFS_LOG_URGE
mdefine_line|#define XFS_LOG_URGE&t;&t;0x4
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/* Log Clients */
DECL|macro|XFS_TRANSACTION
mdefine_line|#define XFS_TRANSACTION&t;&t;0x69
DECL|macro|XFS_VOLUME
mdefine_line|#define XFS_VOLUME&t;&t;0x2
DECL|macro|XFS_LOG
mdefine_line|#define XFS_LOG&t;&t;&t;0xaa
DECL|struct|xfs_log_iovec
r_typedef
r_struct
id|xfs_log_iovec
(brace
DECL|member|i_addr
id|xfs_caddr_t
id|i_addr
suffix:semicolon
multiline_comment|/* beginning address of region */
DECL|member|i_len
r_int
id|i_len
suffix:semicolon
multiline_comment|/* length in bytes of region */
DECL|typedef|xfs_log_iovec_t
)brace
id|xfs_log_iovec_t
suffix:semicolon
DECL|typedef|xfs_log_ticket_t
r_typedef
r_void
op_star
id|xfs_log_ticket_t
suffix:semicolon
multiline_comment|/*&n; * Structure used to pass callback function and the function&squot;s argument&n; * to the log manager.&n; */
DECL|struct|xfs_log_callback
r_typedef
r_struct
id|xfs_log_callback
(brace
DECL|member|cb_next
r_struct
id|xfs_log_callback
op_star
id|cb_next
suffix:semicolon
DECL|member|cb_func
r_void
(paren
op_star
id|cb_func
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|cb_arg
r_void
op_star
id|cb_arg
suffix:semicolon
DECL|typedef|xfs_log_callback_t
)brace
id|xfs_log_callback_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Log manager interfaces */
r_struct
id|xfs_mount
suffix:semicolon
id|xfs_lsn_t
id|xfs_log_done
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_log_ticket_t
id|ticket
comma
r_void
op_star
op_star
id|iclog
comma
id|uint
id|flags
)paren
suffix:semicolon
r_int
id|xfs_log_force
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_lsn_t
id|lsn
comma
id|uint
id|flags
)paren
suffix:semicolon
r_int
id|xfs_log_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|xfs_log_mount
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|dev_t
id|log_dev
comma
id|xfs_daddr_t
id|start_block
comma
r_int
id|num_bblocks
)paren
suffix:semicolon
r_int
id|xfs_log_mount_finish
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_log_move_tail
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_lsn_t
id|tail_lsn
)paren
suffix:semicolon
r_int
id|xfs_log_notify
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_void
op_star
id|iclog
comma
id|xfs_log_callback_t
op_star
id|callback_entry
)paren
suffix:semicolon
r_int
id|xfs_log_reserve
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|length
comma
r_int
id|count
comma
id|xfs_log_ticket_t
op_star
id|ticket
comma
id|__uint8_t
id|clientid
comma
id|uint
id|flags
)paren
suffix:semicolon
r_int
id|xfs_log_write
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_log_iovec_t
id|region
(braket
)braket
comma
r_int
id|nentries
comma
id|xfs_log_ticket_t
id|ticket
comma
id|xfs_lsn_t
op_star
id|start_lsn
)paren
suffix:semicolon
r_int
id|xfs_log_unmount
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_log_unmount_write
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_void
id|xfs_log_unmount_dealloc
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_log_force_umount
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|logerror
)paren
suffix:semicolon
r_int
id|xfs_log_need_covered
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_void
id|xlog_iodone
c_func
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|xlog_debug
suffix:semicolon
multiline_comment|/* set to 1 to enable real log */
macro_line|#endif&t;/* __XFS_LOG_H__ */
eof
