multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ERROR_H__
DECL|macro|__XFS_ERROR_H__
mdefine_line|#define __XFS_ERROR_H__
DECL|macro|prdev
mdefine_line|#define prdev(fmt,dev,args...) &bslash;&n;&t;printk(&quot;XFS: device 0x%x- &quot; fmt &quot;&bslash;n&quot;, (unsigned)dev, ## args)
DECL|macro|XFS_ERECOVER
mdefine_line|#define XFS_ERECOVER&t;1&t;/* Failure to recover log */
DECL|macro|XFS_ELOGSTAT
mdefine_line|#define XFS_ELOGSTAT&t;2&t;/* Failure to stat log in user space */
DECL|macro|XFS_ENOLOGSPACE
mdefine_line|#define XFS_ENOLOGSPACE 3&t;/* Reservation too large */
DECL|macro|XFS_ENOTSUP
mdefine_line|#define XFS_ENOTSUP&t;4&t;/* Operation not supported */
DECL|macro|XFS_ENOLSN
mdefine_line|#define XFS_ENOLSN&t;5&t;/* Can&squot;t find the lsn you asked for */
DECL|macro|XFS_ENOTFOUND
mdefine_line|#define XFS_ENOTFOUND&t;6
DECL|macro|XFS_ENOTXFS
mdefine_line|#define XFS_ENOTXFS&t;7&t;/* Not XFS filesystem */
macro_line|#ifdef DEBUG
DECL|macro|XFS_ERROR_NTRAP
mdefine_line|#define XFS_ERROR_NTRAP 10
r_extern
r_int
id|xfs_etrap
(braket
id|XFS_ERROR_NTRAP
)braket
suffix:semicolon
r_extern
r_int
id|xfs_error_trap
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|XFS_ERROR
mdefine_line|#define XFS_ERROR(e)&t;xfs_error_trap(e)
macro_line|#else
DECL|macro|XFS_ERROR
mdefine_line|#define XFS_ERROR(e)&t;(e)
macro_line|#endif
multiline_comment|/*&n; * error injection tags - the labels can be anything you want&n; * but each tag should have its own unique number&n; */
DECL|macro|XFS_ERRTAG_NOERROR
mdefine_line|#define XFS_ERRTAG_NOERROR&t;&t;&t;&t;0
DECL|macro|XFS_ERRTAG_IFLUSH_1
mdefine_line|#define XFS_ERRTAG_IFLUSH_1&t;&t;&t;&t;1
DECL|macro|XFS_ERRTAG_IFLUSH_2
mdefine_line|#define XFS_ERRTAG_IFLUSH_2&t;&t;&t;&t;2
DECL|macro|XFS_ERRTAG_IFLUSH_3
mdefine_line|#define XFS_ERRTAG_IFLUSH_3&t;&t;&t;&t;3
DECL|macro|XFS_ERRTAG_IFLUSH_4
mdefine_line|#define XFS_ERRTAG_IFLUSH_4&t;&t;&t;&t;4
DECL|macro|XFS_ERRTAG_IFLUSH_5
mdefine_line|#define XFS_ERRTAG_IFLUSH_5&t;&t;&t;&t;5
DECL|macro|XFS_ERRTAG_IFLUSH_6
mdefine_line|#define XFS_ERRTAG_IFLUSH_6&t;&t;&t;&t;6
DECL|macro|XFS_ERRTAG_DA_READ_BUF
mdefine_line|#define XFS_ERRTAG_DA_READ_BUF&t;&t;&t;&t;7
DECL|macro|XFS_ERRTAG_BTREE_CHECK_LBLOCK
mdefine_line|#define XFS_ERRTAG_BTREE_CHECK_LBLOCK&t;&t;&t;8
DECL|macro|XFS_ERRTAG_BTREE_CHECK_SBLOCK
mdefine_line|#define XFS_ERRTAG_BTREE_CHECK_SBLOCK&t;&t;&t;9
DECL|macro|XFS_ERRTAG_ALLOC_READ_AGF
mdefine_line|#define XFS_ERRTAG_ALLOC_READ_AGF&t;&t;&t;10
DECL|macro|XFS_ERRTAG_IALLOC_READ_AGI
mdefine_line|#define XFS_ERRTAG_IALLOC_READ_AGI&t;&t;&t;11
DECL|macro|XFS_ERRTAG_ITOBP_INOTOBP
mdefine_line|#define XFS_ERRTAG_ITOBP_INOTOBP&t;&t;&t;12
DECL|macro|XFS_ERRTAG_IUNLINK
mdefine_line|#define XFS_ERRTAG_IUNLINK&t;&t;&t;&t;13
DECL|macro|XFS_ERRTAG_IUNLINK_REMOVE
mdefine_line|#define XFS_ERRTAG_IUNLINK_REMOVE&t;&t;&t;14
DECL|macro|XFS_ERRTAG_DIR_INO_VALIDATE
mdefine_line|#define XFS_ERRTAG_DIR_INO_VALIDATE&t;&t;&t;15
DECL|macro|XFS_ERRTAG_BULKSTAT_READ_CHUNK
mdefine_line|#define XFS_ERRTAG_BULKSTAT_READ_CHUNK&t;&t;&t;16
DECL|macro|XFS_ERRTAG_IODONE_IOERR
mdefine_line|#define XFS_ERRTAG_IODONE_IOERR&t;&t;&t;&t;17
DECL|macro|XFS_ERRTAG_STRATREAD_IOERR
mdefine_line|#define XFS_ERRTAG_STRATREAD_IOERR&t;&t;&t;18
DECL|macro|XFS_ERRTAG_STRATCMPL_IOERR
mdefine_line|#define XFS_ERRTAG_STRATCMPL_IOERR&t;&t;&t;19
DECL|macro|XFS_ERRTAG_DIOWRITE_IOERR
mdefine_line|#define XFS_ERRTAG_DIOWRITE_IOERR&t;&t;&t;20
DECL|macro|XFS_ERRTAG_MAX
mdefine_line|#define XFS_ERRTAG_MAX&t;&t;&t;&t;&t;21
multiline_comment|/*&n; * Random factors for above tags, 1 means always, 2 means 1/2 time, etc.&n; */
DECL|macro|XFS_RANDOM_DEFAULT
mdefine_line|#define XFS_RANDOM_DEFAULT&t;&t;&t;&t;100
DECL|macro|XFS_RANDOM_IFLUSH_1
mdefine_line|#define XFS_RANDOM_IFLUSH_1&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IFLUSH_2
mdefine_line|#define XFS_RANDOM_IFLUSH_2&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IFLUSH_3
mdefine_line|#define XFS_RANDOM_IFLUSH_3&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IFLUSH_4
mdefine_line|#define XFS_RANDOM_IFLUSH_4&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IFLUSH_5
mdefine_line|#define XFS_RANDOM_IFLUSH_5&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IFLUSH_6
mdefine_line|#define XFS_RANDOM_IFLUSH_6&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_DA_READ_BUF
mdefine_line|#define XFS_RANDOM_DA_READ_BUF&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_BTREE_CHECK_LBLOCK
mdefine_line|#define XFS_RANDOM_BTREE_CHECK_LBLOCK&t;&t;&t;(XFS_RANDOM_DEFAULT/4)
DECL|macro|XFS_RANDOM_BTREE_CHECK_SBLOCK
mdefine_line|#define XFS_RANDOM_BTREE_CHECK_SBLOCK&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_ALLOC_READ_AGF
mdefine_line|#define XFS_RANDOM_ALLOC_READ_AGF&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IALLOC_READ_AGI
mdefine_line|#define XFS_RANDOM_IALLOC_READ_AGI&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_ITOBP_INOTOBP
mdefine_line|#define XFS_RANDOM_ITOBP_INOTOBP&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IUNLINK
mdefine_line|#define XFS_RANDOM_IUNLINK&t;&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IUNLINK_REMOVE
mdefine_line|#define XFS_RANDOM_IUNLINK_REMOVE&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_DIR_INO_VALIDATE
mdefine_line|#define XFS_RANDOM_DIR_INO_VALIDATE&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_BULKSTAT_READ_CHUNK
mdefine_line|#define XFS_RANDOM_BULKSTAT_READ_CHUNK&t;&t;&t;XFS_RANDOM_DEFAULT
DECL|macro|XFS_RANDOM_IODONE_IOERR
mdefine_line|#define XFS_RANDOM_IODONE_IOERR&t;&t;&t;&t;(XFS_RANDOM_DEFAULT/10)
DECL|macro|XFS_RANDOM_STRATREAD_IOERR
mdefine_line|#define XFS_RANDOM_STRATREAD_IOERR&t;&t;&t;(XFS_RANDOM_DEFAULT/10)
DECL|macro|XFS_RANDOM_STRATCMPL_IOERR
mdefine_line|#define XFS_RANDOM_STRATCMPL_IOERR&t;&t;&t;(XFS_RANDOM_DEFAULT/10)
DECL|macro|XFS_RANDOM_DIOWRITE_IOERR
mdefine_line|#define XFS_RANDOM_DIOWRITE_IOERR&t;&t;&t;(XFS_RANDOM_DEFAULT/10)
macro_line|#if (defined(DEBUG) || defined(INDUCE_IO_ERROR))
r_extern
r_int
id|xfs_error_test
c_func
(paren
r_int
comma
r_int
op_star
comma
r_char
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|xfs_error_test_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|XFS_NUM_INJECT_ERROR
mdefine_line|#define XFS_NUM_INJECT_ERROR&t;&t;&t;&t;10
macro_line|#ifdef __ANSI_CPP__
DECL|macro|XFS_TEST_ERROR
mdefine_line|#define XFS_TEST_ERROR(expr, mp, tag, rf)&t;&t;&bslash;&n;&t;((expr) || &bslash;&n;&t; xfs_error_test((tag), (mp)-&gt;m_fixedfsid, #expr, __LINE__, __FILE__, &bslash;&n;&t;&t;&t; (rf)))
macro_line|#else
DECL|macro|XFS_TEST_ERROR
mdefine_line|#define XFS_TEST_ERROR(expr, mp, tag, rf)&t;&t;&bslash;&n;&t;((expr) || &bslash;&n;&t; xfs_error_test((tag), (mp)-&gt;m_fixedfsid, &quot;expr&quot;, __LINE__, __FILE__, &bslash;&n;&t;&t;&t;(rf)))
macro_line|#endif /* __ANSI_CPP__ */
r_int
id|xfs_errortag_add
c_func
(paren
r_int
id|error_tag
comma
id|xfs_mount_t
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_errortag_clear
c_func
(paren
r_int
id|error_tag
comma
id|xfs_mount_t
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_errortag_clearall
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_errortag_clearall_umount
c_func
(paren
r_int64
id|fsid
comma
r_char
op_star
id|fsname
comma
r_int
id|loud
)paren
suffix:semicolon
macro_line|#else
DECL|macro|XFS_TEST_ERROR
mdefine_line|#define XFS_TEST_ERROR(expr, mp, tag, rf)&t;(expr)
DECL|macro|xfs_errortag_add
mdefine_line|#define xfs_errortag_add(tag, mp)&t;&t;(ENOSYS)
DECL|macro|xfs_errortag_clearall
mdefine_line|#define xfs_errortag_clearall(mp)&t;&t;(ENOSYS)
macro_line|#endif /* (DEBUG || INDUCE_IO_ERROR) */
multiline_comment|/*&n; * XFS panic tags -- allow a call to xfs_cmn_err() be turned into&n; *&t;&t;&t;a panic by setting xfs_panic_mask in a&n; *&t;&t;&t;sysctl.  update xfs_max[XFS_PARAM] if&n; *&t;&t;&t;more are added.&n; */
DECL|macro|XFS_NO_PTAG
mdefine_line|#define&t;&t;XFS_NO_PTAG&t;&t;&t;0LL
DECL|macro|XFS_PTAG_IFLUSH
mdefine_line|#define&t;&t;XFS_PTAG_IFLUSH&t;&t;&t;0x0000000000000001LL
DECL|macro|XFS_PTAG_LOGRES
mdefine_line|#define&t;&t;XFS_PTAG_LOGRES&t;&t;&t;0x0000000000000002LL
DECL|macro|XFS_PTAG_AILDELETE
mdefine_line|#define&t;&t;XFS_PTAG_AILDELETE&t;&t;0x0000000000000004LL
DECL|macro|XFS_PTAG_AVAILABLE
mdefine_line|#define&t;&t;XFS_PTAG_AVAILABLE&t;&t;0x0000000000000008LL
DECL|macro|XFS_PTAG_SHUTDOWN_CORRUPT
mdefine_line|#define&t;&t;XFS_PTAG_SHUTDOWN_CORRUPT&t;0x0000000000000010LL
DECL|macro|XFS_PTAG_SHUTDOWN_IOERROR
mdefine_line|#define&t;&t;XFS_PTAG_SHUTDOWN_IOERROR&t;0x0000000000000020LL
DECL|macro|XFS_PTAG_SHUTDOWN_LOGERROR
mdefine_line|#define&t;&t;XFS_PTAG_SHUTDOWN_LOGERROR&t;0x0000000000000040LL
r_struct
id|xfs_mount
suffix:semicolon
multiline_comment|/* PRINTFLIKE4 */
r_void
id|xfs_cmn_err
c_func
(paren
r_uint64
id|panic_tag
comma
r_int
id|level
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* PRINTFLIKE3 */
r_void
id|xfs_fs_cmn_err
c_func
(paren
r_int
id|level
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_ERROR_H__ */
eof
