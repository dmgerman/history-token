multiline_comment|/*&n; *&t;iovec manipulation routines.&n; *&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Fixes:&n; *&t;&t;Andrew Lunn&t;:&t;Errors in iovec copying.&n; *&t;&t;Pedro Roque&t;:&t;Added memcpy_fromiovecend and&n; *&t;&t;&t;&t;&t;csum_..._fromiovecend.&n; *&t;&t;Andi Kleen&t;:&t;fixed error handling for 2.1&n; *&t;&t;Alexey Kuznetsov:&t;2.1 optimisations&n; *&t;&t;Andi Kleen&t;:&t;Fix csum*fromiovecend for IPv6.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/*&n; *&t;Verify iovec. The caller must ensure that the iovec is big enough&n; *&t;to hold the message iovec.&n; *&n; *&t;Save time not doing verify_area. copy_*_user will make this work&n; *&t;in any case.&n; */
DECL|function|verify_iovec
r_int
id|verify_iovec
c_func
(paren
r_struct
id|msghdr
op_star
id|m
comma
r_struct
id|iovec
op_star
id|iov
comma
r_char
op_star
id|address
comma
r_int
id|mode
)paren
(brace
r_int
id|size
comma
id|err
comma
id|ct
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;msg_namelen
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|VERIFY_READ
)paren
(brace
id|err
op_assign
id|move_addr_to_kernel
c_func
(paren
id|m-&gt;msg_name
comma
id|m-&gt;msg_namelen
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|m-&gt;msg_name
op_assign
id|address
suffix:semicolon
)brace
r_else
id|m-&gt;msg_name
op_assign
l_int|NULL
suffix:semicolon
)brace
id|size
op_assign
id|m-&gt;msg_iovlen
op_star
r_sizeof
(paren
r_struct
id|iovec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|iov
comma
id|m-&gt;msg_iov
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|m-&gt;msg_iov
op_assign
id|iov
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ct
op_assign
l_int|0
suffix:semicolon
id|ct
OL
id|m-&gt;msg_iovlen
suffix:semicolon
id|ct
op_increment
)paren
(brace
id|err
op_add_assign
id|iov
(braket
id|ct
)braket
dot
id|iov_len
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Goal is not to verify user data, but to prevent returning&n;&t;&t; * negative value, which is interpreted as errno.&n;&t;&t; * Overflow is still possible, but it is harmless.&n;&t;&t; */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Copy kernel to iovec. Returns -EFAULT on error.&n; *&n; *&t;Note: this modifies the original iovec.&n; */
DECL|function|memcpy_toiovec
r_int
id|memcpy_toiovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_char
op_star
id|kdata
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|iov-&gt;iov_len
)paren
(brace
r_int
id|copy
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|iov-&gt;iov_len
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|iov-&gt;iov_base
comma
id|kdata
comma
id|copy
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|kdata
op_add_assign
id|copy
suffix:semicolon
id|len
op_sub_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_len
op_sub_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_base
op_add_assign
id|copy
suffix:semicolon
)brace
id|iov
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;In kernel copy to iovec. Returns -EFAULT on error.&n; *&n; *&t;Note: this modifies the original iovec.&n; */
DECL|function|memcpy_tokerneliovec
r_void
id|memcpy_tokerneliovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_char
op_star
id|kdata
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|iov-&gt;iov_len
)paren
(brace
r_int
id|copy
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|iov-&gt;iov_len
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|iov-&gt;iov_base
comma
id|kdata
comma
id|copy
)paren
suffix:semicolon
id|kdata
op_add_assign
id|copy
suffix:semicolon
id|len
op_sub_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_len
op_sub_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_base
op_add_assign
id|copy
suffix:semicolon
)brace
id|iov
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Copy iovec to kernel. Returns -EFAULT on error.&n; *&n; *&t;Note: this modifies the original iovec.&n; */
DECL|function|memcpy_fromiovec
r_int
id|memcpy_fromiovec
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|iov-&gt;iov_len
)paren
(brace
r_int
id|copy
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
id|iov-&gt;iov_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kdata
comma
id|iov-&gt;iov_base
comma
id|copy
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_sub_assign
id|copy
suffix:semicolon
id|kdata
op_add_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_base
op_add_assign
id|copy
suffix:semicolon
id|iov-&gt;iov_len
op_sub_assign
id|copy
suffix:semicolon
)brace
id|iov
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;For use with ip_build_xmit&n; */
DECL|function|memcpy_fromiovecend
r_int
id|memcpy_fromiovecend
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|offset
comma
r_int
id|len
)paren
(brace
multiline_comment|/* Skip over the finished iovecs */
r_while
c_loop
(paren
id|offset
op_ge
id|iov-&gt;iov_len
)paren
(brace
id|offset
op_sub_assign
id|iov-&gt;iov_len
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|u8
op_star
id|base
op_assign
id|iov-&gt;iov_base
op_plus
id|offset
suffix:semicolon
r_int
id|copy
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
id|iov-&gt;iov_len
op_minus
id|offset
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kdata
comma
id|base
comma
id|copy
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_sub_assign
id|copy
suffix:semicolon
id|kdata
op_add_assign
id|copy
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;And now for the all-in-one: copy and checksum from a user iovec&n; *&t;directly to a datagram&n; *&t;Calls to csum_partial but the last must be in 32 bit chunks&n; *&n; *&t;ip_build_xmit must ensure that when fragmenting only the last&n; *&t;call to this function will be unaligned also.&n; */
DECL|function|csum_partial_copy_fromiovecend
r_int
id|csum_partial_copy_fromiovecend
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|offset
comma
r_int
r_int
id|len
comma
r_int
op_star
id|csump
)paren
(brace
r_int
id|csum
op_assign
op_star
id|csump
suffix:semicolon
r_int
id|partial_cnt
op_assign
l_int|0
comma
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Skip over the finished iovecs */
r_while
c_loop
(paren
id|offset
op_ge
id|iov-&gt;iov_len
)paren
(brace
id|offset
op_sub_assign
id|iov-&gt;iov_len
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|u8
op_star
id|base
op_assign
id|iov-&gt;iov_base
op_plus
id|offset
suffix:semicolon
r_int
id|copy
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
id|iov-&gt;iov_len
op_minus
id|offset
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* There is a remnant from previous iov. */
r_if
c_cond
(paren
id|partial_cnt
)paren
(brace
r_int
id|par_len
op_assign
l_int|4
op_minus
id|partial_cnt
suffix:semicolon
multiline_comment|/* iov component is too short ... */
r_if
c_cond
(paren
id|par_len
OG
id|copy
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kdata
comma
id|base
comma
id|copy
)paren
)paren
r_goto
id|out_fault
suffix:semicolon
id|kdata
op_add_assign
id|copy
suffix:semicolon
id|base
op_add_assign
id|copy
suffix:semicolon
id|partial_cnt
op_add_assign
id|copy
suffix:semicolon
id|len
op_sub_assign
id|copy
suffix:semicolon
id|iov
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
r_continue
suffix:semicolon
op_star
id|csump
op_assign
id|csum_partial
c_func
(paren
id|kdata
op_minus
id|partial_cnt
comma
id|partial_cnt
comma
id|csum
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kdata
comma
id|base
comma
id|par_len
)paren
)paren
r_goto
id|out_fault
suffix:semicolon
id|csum
op_assign
id|csum_partial
c_func
(paren
id|kdata
op_minus
id|partial_cnt
comma
l_int|4
comma
id|csum
)paren
suffix:semicolon
id|kdata
op_add_assign
id|par_len
suffix:semicolon
id|base
op_add_assign
id|par_len
suffix:semicolon
id|copy
op_sub_assign
id|par_len
suffix:semicolon
id|len
op_sub_assign
id|par_len
suffix:semicolon
id|partial_cnt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|copy
)paren
(brace
id|partial_cnt
op_assign
id|copy
op_mod
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|partial_cnt
)paren
(brace
id|copy
op_sub_assign
id|partial_cnt
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kdata
op_plus
id|copy
comma
id|base
op_plus
id|copy
comma
id|partial_cnt
)paren
)paren
r_goto
id|out_fault
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|copy
)paren
(brace
id|csum
op_assign
id|csum_and_copy_from_user
c_func
(paren
id|base
comma
id|kdata
comma
id|copy
comma
id|csum
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
)brace
id|len
op_sub_assign
id|copy
op_plus
id|partial_cnt
suffix:semicolon
id|kdata
op_add_assign
id|copy
op_plus
id|partial_cnt
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
op_star
id|csump
op_assign
id|csum
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_fault
suffix:colon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
eof
