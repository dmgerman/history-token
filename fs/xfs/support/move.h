multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_MOVE_H__
DECL|macro|__XFS_SUPPORT_MOVE_H__
mdefine_line|#define __XFS_SUPPORT_MOVE_H__
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|bzero
mdefine_line|#define bzero(p,s)&t;memset((p), 0, (s))
DECL|macro|bcopy
mdefine_line|#define bcopy(s,d,n)&t;memcpy((d),(s),(n))
DECL|macro|bcmp
mdefine_line|#define bcmp(s1,s2,l)&t;memcmp(s1,s2,l)
DECL|macro|ovbcopy
mdefine_line|#define ovbcopy(from,to,count)&t;memmove(to,from,count)
DECL|typedef|iovec_t
r_typedef
r_struct
id|iovec
id|iovec_t
suffix:semicolon
DECL|struct|uio
r_typedef
r_struct
id|uio
(brace
DECL|member|uio_iov
id|iovec_t
op_star
id|uio_iov
suffix:semicolon
multiline_comment|/* pointer to array of iovecs */
DECL|member|uio_iovcnt
r_int
id|uio_iovcnt
suffix:semicolon
multiline_comment|/* number of iovecs */
DECL|member|uio_fmode
r_int
id|uio_fmode
suffix:semicolon
multiline_comment|/* file mode flags */
DECL|member|uio_offset
id|xfs_off_t
id|uio_offset
suffix:semicolon
multiline_comment|/* file offset */
DECL|member|uio_segflg
r_int
id|uio_segflg
suffix:semicolon
multiline_comment|/* address space (kernel or user) */
DECL|member|uio_resid
id|ssize_t
id|uio_resid
suffix:semicolon
multiline_comment|/* residual count */
DECL|typedef|uio_t
)brace
id|uio_t
suffix:semicolon
multiline_comment|/*&n; * I/O direction.&n; */
DECL|enum|uio_rw
DECL|enumerator|UIO_READ
DECL|enumerator|UIO_WRITE
DECL|typedef|uio_rw_t
r_typedef
r_enum
id|uio_rw
(brace
id|UIO_READ
comma
id|UIO_WRITE
)brace
id|uio_rw_t
suffix:semicolon
multiline_comment|/*&n; * Segment flag values.&n; */
DECL|enum|uio_seg
r_typedef
r_enum
id|uio_seg
(brace
DECL|enumerator|UIO_USERSPACE
id|UIO_USERSPACE
comma
multiline_comment|/* uio_iov describes user space */
DECL|enumerator|UIO_SYSSPACE
id|UIO_SYSSPACE
comma
multiline_comment|/* uio_iov describes system space */
DECL|typedef|uio_seg_t
)brace
id|uio_seg_t
suffix:semicolon
r_extern
r_int
id|uiomove
(paren
r_void
op_star
comma
r_int
comma
id|uio_rw_t
comma
id|uio_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_SUPPORT_MOVE_H__ */
eof
