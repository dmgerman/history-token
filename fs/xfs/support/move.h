multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; * &n; * Portions Copyright (c) 1982, 1986, 1993, 1994&n; *      The Regents of the University of California.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. All advertising materials mentioning features or use of this software&n; *    must display the following acknowledgement:&n; *      This product includes software developed by the University of&n; *      California, Berkeley and its contributors.&n; * 4. Neither the name of the University nor the names of its contributors&n; *    may be used to endorse or promote products derived from this software&n; *    without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef __XFS_SUPPORT_MOVE_H__
DECL|macro|__XFS_SUPPORT_MOVE_H__
mdefine_line|#define __XFS_SUPPORT_MOVE_H__
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Segment flag values. */
DECL|enum|uio_seg
r_enum
id|uio_seg
(brace
DECL|enumerator|UIO_USERSPACE
id|UIO_USERSPACE
comma
multiline_comment|/* from user data space */
DECL|enumerator|UIO_SYSSPACE
id|UIO_SYSSPACE
comma
multiline_comment|/* from system space */
)brace
suffix:semicolon
DECL|struct|uio
r_struct
id|uio
(brace
DECL|member|uio_iov
r_struct
id|iovec
op_star
id|uio_iov
suffix:semicolon
DECL|member|uio_iovcnt
r_int
id|uio_iovcnt
suffix:semicolon
DECL|member|uio_offset
id|xfs_off_t
id|uio_offset
suffix:semicolon
DECL|member|uio_resid
r_int
id|uio_resid
suffix:semicolon
DECL|member|uio_segflg
r_enum
id|uio_seg
id|uio_segflg
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|uio_t
r_typedef
r_struct
id|uio
id|uio_t
suffix:semicolon
DECL|typedef|iovec_t
r_typedef
r_struct
id|iovec
id|iovec_t
suffix:semicolon
r_extern
r_int
id|uio_read
(paren
id|caddr_t
comma
r_int
comma
id|uio_t
op_star
)paren
suffix:semicolon
macro_line|#endif  /* __XFS_SUPPORT_MOVE_H__ */
eof
