multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;xfs_types.h&gt;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;move.h&quot;
multiline_comment|/* Read from kernel buffer at src to user/kernel buffer defined&n; * by the uio structure. Advance the pointer in the uio struct&n; * as we go.&n; */
r_int
DECL|function|uio_read
id|uio_read
c_func
(paren
id|caddr_t
id|src
comma
r_int
id|len
comma
r_struct
id|uio
op_star
id|uio
)paren
(brace
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
id|u_int
id|cnt
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
op_logical_and
id|uio-&gt;uio_resid
)paren
(brace
id|iov
op_assign
id|uio-&gt;uio_iov
suffix:semicolon
id|cnt
op_assign
(paren
id|u_int
)paren
id|iov-&gt;iov_len
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OG
id|len
)paren
id|cnt
op_assign
(paren
id|u_int
)paren
id|len
suffix:semicolon
r_if
c_cond
(paren
id|uio-&gt;uio_segflg
op_eq
id|UIO_USERSPACE
)paren
(brace
id|error
op_assign
id|copy_to_user
c_func
(paren
id|iov-&gt;iov_base
comma
id|src
comma
id|cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|EFAULT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|uio-&gt;uio_segflg
op_eq
id|UIO_SYSSPACE
)paren
(brace
id|memcpy
c_func
(paren
id|iov-&gt;iov_base
comma
id|src
comma
id|cnt
)paren
suffix:semicolon
)brace
r_else
(brace
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|iov-&gt;iov_base
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|iov-&gt;iov_base
op_plus
id|cnt
)paren
suffix:semicolon
id|iov-&gt;iov_len
op_sub_assign
id|cnt
suffix:semicolon
id|uio-&gt;uio_resid
op_sub_assign
id|cnt
suffix:semicolon
id|uio-&gt;uio_offset
op_add_assign
id|cnt
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
