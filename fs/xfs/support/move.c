multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;xfs_types.h&gt;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;move.h&quot;
multiline_comment|/*&n; * Move &quot;n&quot; bytes at byte address &quot;cp&quot;; &quot;rw&quot; indicates the direction&n; * of the move, and the I/O parameters are provided in &quot;uio&quot;, which is&n; * update to reflect the data which was moved.&t;Returns 0 on success or&n; * a non-zero errno on failure.&n; */
r_int
DECL|function|uiomove
id|uiomove
c_func
(paren
r_void
op_star
id|cp
comma
r_int
id|n
comma
r_enum
id|uio_rw
id|rw
comma
r_struct
id|uio
op_star
id|uio
)paren
(brace
r_register
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
r_while
c_loop
(paren
id|n
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
(brace
id|uio-&gt;uio_iov
op_increment
suffix:semicolon
id|uio-&gt;uio_iovcnt
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
OG
id|n
)paren
id|cnt
op_assign
(paren
id|u_int
)paren
id|n
suffix:semicolon
r_switch
c_cond
(paren
id|uio-&gt;uio_segflg
)paren
(brace
r_case
id|UIO_USERSPACE
suffix:colon
r_if
c_cond
(paren
id|rw
op_eq
id|UIO_READ
)paren
id|error
op_assign
id|copy_to_user
c_func
(paren
id|iov-&gt;iov_base
comma
id|cp
comma
id|cnt
)paren
suffix:semicolon
r_else
id|error
op_assign
id|copy_from_user
c_func
(paren
id|cp
comma
id|iov-&gt;iov_base
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
r_break
suffix:semicolon
r_case
id|UIO_SYSSPACE
suffix:colon
r_if
c_cond
(paren
id|rw
op_eq
id|UIO_READ
)paren
id|memcpy
c_func
(paren
id|iov-&gt;iov_base
comma
id|cp
comma
id|cnt
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|cp
comma
id|iov-&gt;iov_base
comma
id|cnt
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
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
id|cp
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
id|cp
op_plus
id|cnt
)paren
suffix:semicolon
id|n
op_sub_assign
id|cnt
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
