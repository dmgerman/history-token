multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;MIPS specific IP/TCP/UDP checksumming routines&n; *&n; * Authors:&t;Ralf Baechle, &lt;ralf@waldorf-gmbh.de&gt;&n; *&t;&t;Lots of code moved from tcp.c and ip.c; see those files&n; *&t;&t;for more names.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * $Id: checksum.c,v 1.1 2002/09/28 14:58:40 gerg Exp $&n; */
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|from32to16
r_static
r_inline
r_int
r_int
id|from32to16
(paren
r_int
r_int
id|sum
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;        %0&t;&t;%1&n;&t;      hsw %1, %0&t;H     L&t;&t;L     H&n;&t;      add %1, %0&t;H     L&t;&t;H+L+C H+L&n;&t;*/
id|asm
(paren
l_string|&quot;hsw %1, %0; add %1, %0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
r_return
id|result
op_rshift
l_int|16
suffix:semicolon
)brace
DECL|function|do_csum
r_static
r_inline
r_int
r_int
id|do_csum
c_func
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
)paren
(brace
r_int
id|odd
comma
id|count
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|odd
op_assign
l_int|1
op_amp
(paren
r_int
r_int
)paren
id|buff
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
(brace
id|result
op_assign
id|be16_to_cpu
c_func
(paren
op_star
id|buff
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
id|buff
op_increment
suffix:semicolon
)brace
id|count
op_assign
id|len
op_rshift
l_int|1
suffix:semicolon
multiline_comment|/* nr of 16-bit words.. */
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
l_int|2
op_amp
(paren
r_int
r_int
)paren
id|buff
)paren
(brace
id|result
op_add_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|buff
op_add_assign
l_int|2
suffix:semicolon
)brace
id|count
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* nr of 32-bit words.. */
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
r_int
id|carry
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_int
r_int
id|w
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|buff
op_add_assign
l_int|4
suffix:semicolon
id|result
op_add_assign
id|carry
suffix:semicolon
id|result
op_add_assign
id|w
suffix:semicolon
id|carry
op_assign
(paren
id|w
OG
id|result
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|result
op_add_assign
id|carry
suffix:semicolon
id|result
op_assign
(paren
id|result
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|result
op_rshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|2
)paren
(brace
id|result
op_add_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|buff
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|1
)paren
id|result
op_add_assign
id|le16_to_cpu
c_func
(paren
op_star
id|buff
)paren
suffix:semicolon
id|result
op_assign
id|from32to16
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
id|result
op_assign
(paren
(paren
id|result
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|result
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; */
DECL|function|ip_fast_csum
r_int
r_int
id|ip_fast_csum
c_func
(paren
r_int
r_char
op_star
id|iph
comma
r_int
r_int
id|ihl
)paren
(brace
r_return
op_complement
id|do_csum
c_func
(paren
id|iph
comma
id|ihl
op_star
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
DECL|function|ip_compute_csum
r_int
r_int
id|ip_compute_csum
c_func
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
)paren
(brace
r_return
op_complement
id|do_csum
c_func
(paren
id|buff
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * computes a partial checksum, e.g. for TCP/UDP fragments&n; */
DECL|function|csum_partial
r_int
r_int
id|csum_partial
c_func
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
r_int
r_int
id|result
op_assign
id|do_csum
c_func
(paren
id|buff
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* add in old sum, and carry.. */
id|result
op_add_assign
id|sum
suffix:semicolon
r_if
c_cond
(paren
id|sum
OG
id|result
)paren
(brace
id|result
op_add_assign
l_int|1
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * copy while checksumming, otherwise like csum_partial&n; */
DECL|function|csum_partial_copy
r_int
r_int
id|csum_partial_copy
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
multiline_comment|/*&n;&t; * It&squot;s 2:30 am and I don&squot;t feel like doing it real ...&n;&t; * This is lots slower than the real thing (tm)&n;&t; */
id|sum
op_assign
id|csum_partial
c_func
(paren
id|src
comma
id|len
comma
id|sum
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy from userspace and compute checksum.  If we catch an exception&n; * then zero the rest of the buffer.&n; */
DECL|function|csum_partial_copy_from_user
r_int
r_int
id|csum_partial_copy_from_user
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_int
id|missing
suffix:semicolon
id|missing
op_assign
id|copy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|missing
)paren
(brace
id|memset
c_func
(paren
id|dst
op_plus
id|len
op_minus
id|missing
comma
l_int|0
comma
id|missing
)paren
suffix:semicolon
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|csum_partial
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
eof
